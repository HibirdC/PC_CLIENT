#include "playsound.h"
#include "TNMsgDetailModel.h"

PlaySound::PlaySound(QObject* parent) : QObject(parent){
    _thread = NULL;
    _stop = false;
    _device = NULL;
    _context = NULL;
    _tnDetailModel = NULL;
    connect(this,SIGNAL(PlayFinished(TNModelUserMessage)),this,SLOT(onPlayFinished(TNModelUserMessage)));
    start();
}

PlaySound::~PlaySound(){
    _stop = true;
    _thread->join();
    delete _thread;
    _thread = NULL;

    clean_openal();
}

PlaySound* PlaySound::getInstance(){
    static PlaySound instance;
    return &instance;
}

bool PlaySound::start()
{
    if(!init_openal()) return false;
    if(!define_openal_listener()) return false;

    _thread = new std::thread(function_t,this);
    return true;
}

void PlaySound::Play(TNModelUserMessage message)
{
    if(_currPlayMsgId == message.GetMsgID()){
        StopPlay();
        return;
    }else if(!_currPlayMsgId.isEmpty()){
        StopPlay();
    }
    _mutex.lock();
    _playList.push_back(message);
    _mutex.unlock();
}

void PlaySound::function_t(void *ptr)
{
    PlaySound* pThis = (PlaySound*)ptr;
    while(true){
        if(pThis->_stop)
            return;
        if(pThis->_playList.empty()){
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            continue;
        }
        pThis->_mutex.lock();
        TNModelUserMessage message = pThis->_playList.front();
        pThis->_playList.pop_front();
        pThis->_mutex.unlock();
        pThis->_currPlayMsgId = message.GetMsgID();
        pThis->use_openal_playwav(message.getFileLocalPath().toStdString());
        pThis->_currPlayMsgId = "";
        emit pThis->PlayFinished(message);
    }
}

void PlaySound::readFmtChunk(uint32_t chunkLen, FILE *wavfile, int *channels, int *sampleRate, int *bitsPerSample, int *bytesPerSample)
{
    assert(chunkLen >= 16);
    uint16_t fmttag = freadNum<uint16_t>(wavfile);
    assert(fmttag == 1 || fmttag == 3);
    *channels = freadNum<uint16_t>(wavfile);
    *sampleRate = freadNum<uint32_t>(wavfile);
    uint32_t byteRate = freadNum<uint32_t>(wavfile);
    uint16_t blockAlign = freadNum<uint16_t>(wavfile);
    *bitsPerSample = freadNum<uint16_t>(wavfile);

    *bytesPerSample = (*bitsPerSample) / 8;
    CHECK(byteRate == (*sampleRate) * (*channels) * (*bytesPerSample));
    CHECK(blockAlign == (*channels) * (*bytesPerSample));

    if(chunkLen > 16) {
        uint16_t extendedSize = freadNum<uint16_t>(wavfile);
        CHECK(chunkLen == 18 + extendedSize);
        fseek(wavfile, extendedSize, SEEK_CUR);
    }
}

char* PlaySound::readWavFile(const char *strFile, int *channels, int *sampleRate, int *bitsPerSample, int *bytesPerSample, int *dataSize)
{
    FILE* wavfile = fopen(strFile,"r");
    CHECK(wavfile != NULL);
    if(!wavfile){
        return NULL;
    }

    char* buffer = NULL;
    CHECK(freadStr(wavfile, 4) == "RIFF");

    uint32_t wavechunksize = freadNum<uint32_t>(wavfile);
    CHECK(freadStr(wavfile, 4) == "WAVE");
    while(true) {
        std::string chunkName = freadStr(wavfile, 4);
        uint32_t chunkLen = freadNum<uint32_t>(wavfile);
        if(chunkName == "fmt ")
            readFmtChunk(chunkLen,wavfile,channels,sampleRate,bitsPerSample,bytesPerSample);
        else if(chunkName == "data"){
            CHECK(*sampleRate != 0);
            CHECK(*channels > 0);
            CHECK(*bytesPerSample > 0);

            buffer = new char[chunkLen + 1];
            buffer[chunkLen] = '\0';

            *dataSize = chunkLen;
            fread(buffer,chunkLen,1,wavfile);
            break;
        }else{
            // skip chunk
            CHECK(fseek(wavfile, chunkLen, SEEK_CUR) == 0);
        }
    }
    fclose(wavfile);
    return buffer;
}

bool PlaySound::init_openal(){
    _device = alcOpenDevice(NULL);
    if(!_device) return false;
    _context = alcCreateContext(_device,NULL);
    if(!alcMakeContextCurrent(_context)){
        check_error();
        return false;
    }
    return true;
}

void PlaySound::clean_openal(){
    //device = alcGetContextsDevice(_context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(_context);
    alcCloseDevice(_device);
    _context = NULL;
    _device = NULL;
}

bool PlaySound::define_openal_listener()
{
    ALfloat listenerOri[] = {0.0f,0.0f,1.0f,0.0f,1.0f,1.0f};
    alListener3f(AL_POSITION,0,0,1.0f);
    if(!check_error()) return false;
    alListener3f(AL_VELOCITY,0,0,0);
    if(!check_error()) return false;
    alListenerfv(AL_ORIENTATION,listenerOri);
    if(!check_error()) return false;
    return true;
}

bool PlaySound::generate_openal_source()
{
    //生成一个单一来源,因此是1
    alGenSources(1,&_source);
    if(!check_error()) return false;
    //音调
    alSourcef(_source, AL_PITCH, 1);
    if(!check_error()) goto clean;
    //增益
    alSourcef(_source, AL_GAIN, 1);
    if(!check_error()) goto clean;
    //位置
    alSource3f(_source, AL_POSITION, 0, 0, 0);
    if(!check_error()) goto clean;
    //速度
    alSource3f(_source, AL_VELOCITY, 0, 0, 0);
    if(!check_error()) goto clean;
    //循环
    alSourcei(_source, AL_LOOPING, AL_FALSE);
    if(!check_error()) goto clean;
    return true;
clean:
    alDeleteSources(1,&_source);
    return false;
}

void PlaySound::use_openal_playwav(const std::string &wavfile)
{
    //生成资源
    if(!generate_openal_source()) return;
    //加载生成buffer
    ALuint buffer;
    alGenBuffers((ALuint)1, &buffer);

    int channels,sampleRate,bitsPerSample,bytesPerSample;
    int dataSize = 0;
    char* wav_raw_buffer = readWavFile(wavfile.c_str(),&channels,&sampleRate,&bitsPerSample,&bytesPerSample,&dataSize);
    if(!wav_raw_buffer){
        qInfo() << "[Notice] [PlaySound] readWavFile failed!";
        alDeleteSources(1, &_source);
        alDeleteBuffers(1, &buffer);
        return;
    }
    alBufferData(buffer, to_al_format(channels, bitsPerSample),
                 wav_raw_buffer, dataSize, sampleRate);
    if(!check_error()) {
        goto clean_source;
    }
    //Binding a source to a buffer
    alSourcei(_source,AL_BUFFER,buffer);

    alSourcePlay(_source);
    if(!check_error()) {
        goto clean_source;
    }
    ALint source_state;
    alGetSourcei(_source, AL_SOURCE_STATE, &source_state);
    if(!check_error()){
        goto clean_source;
    }
    while (source_state == AL_PLAYING) {
        alGetSourcei(_source, AL_SOURCE_STATE, &source_state);
        if(!check_error()){
            break;
        }
    }
clean_source:
    //释放资源
    delete [] wav_raw_buffer;
    alDeleteSources(1, &_source);
    alDeleteBuffers(1, &buffer);
}

void PlaySound::StopPlay()
{
    if(!_currPlayMsgId.isEmpty()){
        alSourceStop(_source);
        if (_tnDetailModel != NULL){
            _tnDetailModel->updateAudioDataReaded(_currPlayMsgId);
        }
        _currPlayMsgId = "";
    }
}

void PlaySound::setMsgDetailModel(TNMsgDetailModel *msgModel){
    _tnDetailModel = msgModel;
}

void PlaySound::onPlayFinished(TNModelUserMessage message){
    if (_tnDetailModel != NULL){
        _tnDetailModel->updateAudioDataReaded(message.GetMsgID());
    }
}

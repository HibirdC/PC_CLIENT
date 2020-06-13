#ifndef PLAYSOUND_H
#define PLAYSOUND_H
#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>
#include <string>
#include <assert.h>
#include <QDebug>
#include <list>
#include <thread>
#include <mutex>
#include <QObject>
#include "TNModelUserMessage.h"
class TNMsgDetailModel;

#define CHECK(x) { if(!(x)) {qInfo() << "[Notice] [PlaySound] " << __FILE__ << " failure at:" << __LINE__; }}
class PlaySound : public QObject
{
    Q_OBJECT
public:
    static PlaySound* getInstance();
    ~PlaySound();
    void Play(TNModelUserMessage message);
    void StopPlay();
    void setMsgDetailModel(TNMsgDetailModel* msgModel);
Q_SIGNALS:
    void PlayFinished(TNModelUserMessage message);
private slots:
    void onPlayFinished(TNModelUserMessage message);
private:
    PlaySound(QObject* parent = NULL);
    void readFmtChunk(uint32_t chunkLen,FILE* wavfile,int* channels,int* sampleRate,int* bitsPerSample,int* bytesPerSample);
    char* readWavFile(const char* strFile,int* channels,int* sampleRate,int* bitsPerSample,int* bytesPerSample,int* dataSize);
    bool check_error(){
        ALCenum error = alGetError();
        if(error != AL_NO_ERROR){
            qInfo() << "[Notice] [PlaySound] check_error code:" << error << " details:" << alGetString(error);
            return false;
        }
        return true;
    }

    template<typename T>
    T freadNum(FILE* f){
        T value;
        CHECK(fread(&value,sizeof(value),1,f) == 1);
        return value;
    }

    std::string freadStr(FILE* f,size_t len){
        std::string s(len,'\0');
        CHECK(fread(&s[0],1,len,f) == len);
        return s;
    }

    static inline ALenum to_al_format(short channels, short samples){
        bool stereo = (channels > 1);

        switch (samples) {
        case 16:
            if (stereo)
                return AL_FORMAT_STEREO16;
            else
                return AL_FORMAT_MONO16;
        case 8:
            if (stereo)
                return AL_FORMAT_STEREO8;
            else
                return AL_FORMAT_MONO8;
        default:
            return -1;
        }
    }
private:
    static void function_t(void* ptr);
    void use_openal_playwav(const std::string& wavfile);
    bool init_openal();
    void clean_openal();
    bool define_openal_listener();
    bool generate_openal_source();
    bool start();
private:
    std::list<TNModelUserMessage> _playList;
    std::thread*		   _thread;
    std::mutex			   _mutex;
    bool 				   _stop;
private:
    ALCdevice*			   _device;
    ALCcontext*			   _context;
    ALuint 				   _source;
    TNMsgDetailModel*	   _tnDetailModel;
    QString 			   _currPlayMsgId;
};
#endif

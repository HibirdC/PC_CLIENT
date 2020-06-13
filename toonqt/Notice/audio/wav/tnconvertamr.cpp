#include "tnconvertamr.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <QDebug>
#include <QFile>
#include "opencore-amrnb/interf_dec.h"
#include "wavwriter.h"
#include "tnwinconvert.h"

const int sizes[] = { 12, 13, 15, 17, 19, 20, 26, 31, 5, 6, 5, 5, 0, 0, 0, 0 };

TNConvertAmr::TNConvertAmr(QObject *parent)
	: QObject(parent)
{

}

TNConvertAmr::~TNConvertAmr()
{

}

bool TNConvertAmr::convertAmrToWav(const QString& srcFile, const QString& wavFile)
{
	FILE* in;
	char header[6];
	int n;
	void *wav, *amr;

#ifdef Q_OS_WIN32
    string s_srcFile = tnwinconvert::UnicodeToAscii(tnwinconvert::Utf8ToUnicode(srcFile.toStdString()));
    in = fopen(s_srcFile.c_str(), "rb");
#else
    in = fopen(srcFile.toStdString().c_str(), "rb");
#endif
    if (!in) {
        qDebug() << "Unable to oepn " + srcFile;
		return false;
	}
	n = fread(header, 1, 6, in);
	if (n != 6 || memcmp(header, "#!AMR\n", 6)) {
        qDebug() << "Amr Bad header";
        fclose(in);
		return false;
	}
#ifdef Q_OS_WIN32
    string to_File = tnwinconvert::UnicodeToAscii(tnwinconvert::Utf8ToUnicode(wavFile.toStdString()));
    wav = WavWriter::wav_write_open(to_File.c_str(), 8000, 16, 1);
#else
    wav = WavWriter::wav_write_open(wavFile.toStdString().c_str(), 8000, 16, 1);
#endif
	if (!wav) {
        qDebug() << "Unable to open " + wavFile;
        fclose(in);
		return false;
	}

	amr = Decoder_Interface_init();
	while (1) {
		uint8_t buffer[500], littleendian[320], *ptr;
		int size, i;
		int16_t outbuffer[160];
		/* Read the mode byte */
		n = fread(buffer, 1, 1, in);
		if (n <= 0)
			break;
		/* Find the packet size */
		size = sizes[(buffer[0] >> 3) & 0x0f];
		n = fread(buffer + 1, 1, size, in);
		if (n != size)
			break;

		/* Decode the packet */
		Decoder_Interface_Decode(amr, buffer, outbuffer, 0);

		/* Convert to little endian and write to wav */
		ptr = littleendian;
		for (i = 0; i < 160; i++) {
			*ptr++ = (outbuffer[i] >> 0) & 0xff;
			*ptr++ = (outbuffer[i] >> 8) & 0xff;
		}
		WavWriter::wav_write_data(wav, littleendian, 320);
	}
	fclose(in);
	Decoder_Interface_exit(amr);
	WavWriter::wav_write_close(wav);
	return true;
}

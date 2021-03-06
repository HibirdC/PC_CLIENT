﻿/* ------------------------------------------------------------------
 * Copyright (C) 2009 Martin Storsjo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */

#ifndef WAVWRITER_H
#define WAVWRITER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
class WavWriter
{
public:
	WavWriter();
	~WavWriter();
	static void* wav_write_open(const char *filename, int sample_rate, int bits_per_sample, int channels);
	static void wav_write_close(void* obj);
	static void wav_write_data(void* obj, const unsigned char* data, int length);
private:
	struct wav_writer {
		FILE *wav;
		int data_length;

		int sample_rate;
		int bits_per_sample;
		int channels;
	};
private:
	static void write_string(struct wav_writer* ww, const char *str);
	static void write_int32(struct wav_writer* ww, int value);
	static void write_int16(struct wav_writer* ww, int value);
	static void write_header(struct wav_writer* ww, int length);
};
#endif
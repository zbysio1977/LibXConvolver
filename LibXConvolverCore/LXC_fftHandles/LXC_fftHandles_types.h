#pragma once

/*	
 *		Copyright (C) 2014 Achim Turan, Achim.Turan@o2online.de
 *		https://github.com/AchimTuran/LibXConvolver
 *
 *	This file is part of LibXConvolver
 *
 *	LibXConvolver is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	LibXConvolver is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with LibXConvolver.  If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include <memory.h>
#include "../include/LXC_CommonTypes.h"


typedef enum {  LXC_fftModule_Min=0, 

                LXC_fftModule_fftwf,
                LXC_fftModule_KissFFT,

                LXC_fftModule_Max
} LXC_FFT_MODULE;


typedef struct LXC_FFT_PLAN
{
  uint LXC_fftSize;               // full fft length
  uint LXC_maxInputFrameLength;   // max input frame length in samples
  uint LXC_fftZeros;              // quantity of zeros (zero padding)
  float LXC_scaleFactor;          // scaling factor for ifft(X)
  void *LXC_specific_fftPlan;     // specific fftHandle

  LXC_FFT_PLAN()
  {
      LXC_fftSize = 0;
      LXC_maxInputFrameLength = 0;
      LXC_fftZeros = 0;
      LXC_scaleFactor = 1.0f;
      LXC_specific_fftPlan = NULL;
  }
} LXC_FFT_PLAN;


typedef struct LXC_FFT_CALLBACKS
{
	// fft functions
	LXC_ERROR_CODE	(*LXC_create_fft)(LXC_FFT_PLAN *fftPlan, uint FreqSize, uint TimeSize);
	LXC_ERROR_CODE	(*LXC_destroy_fft)(LXC_FFT_PLAN *fftHandle);
	LXC_ERROR_CODE	(*LXC_clearBuffers)(LXC_FFT_PLAN *fftPlan);
	LXC_ERROR_CODE	(*LXC_fft)(LXC_FFT_PLAN *fftHandle);
	LXC_ERROR_CODE	(*LXC_ifft)(LXC_FFT_PLAN *fftHandle);

	// format conversion functions
	LXC_ERROR_CODE	(*LXC_fmtc_external_TO_fft)(void *In, LXC_FFT_PLAN *fftHandle_out, uint Size);                    // outside LXC format to fft format
	LXC_ERROR_CODE	(*LXC_fmtc_fft_TO_external)(LXC_FFT_PLAN *fftHandle_in, void *Out, uint Size);                    // fft format to outside LXC format
	LXC_ERROR_CODE	(*LXC_fmtc_external_TO_fft_2Ch)(void *In1, void *In2, LXC_FFT_PLAN *fftHandle_out, uint Size);    // outside LXC format to fft format (2 Channels)
	LXC_ERROR_CODE	(*LXC_fmtc_fft_TO_external_2Ch)(LXC_FFT_PLAN *fftHandle_in, void *Out1, void *Out2, uint Size);   // fft format to outside LXC format (2 Channels)
	LXC_ERROR_CODE	(*LXC_fmtc_internal_TO_fft)(void *In, LXC_FFT_PLAN *fftHandle_out, uint Size);                    // intern LXC format to fft format
	LXC_ERROR_CODE	(*LXC_fmtc_fft_TO_internal)(LXC_FFT_PLAN *fftHandle_in, void *Out, uint Size);                    // fft format to intern LXC format

	LXC_FFT_CALLBACKS()
	{
	  LXC_create_fft = NULL;
	  LXC_destroy_fft = NULL;
	  LXC_clearBuffers = NULL;
	  LXC_fft = NULL;
	  LXC_ifft = NULL;

	  LXC_fmtc_external_TO_fft = NULL;
	  LXC_fmtc_fft_TO_external = NULL;
	  LXC_fmtc_external_TO_fft_2Ch = NULL;
	  LXC_fmtc_fft_TO_external_2Ch = NULL;
	  LXC_fmtc_internal_TO_fft = NULL;
	  LXC_fmtc_fft_TO_internal = NULL;
	}
} LXC_FFT_CALLBACKS;


typedef struct LXC_FFT_HANDLE
{
	LXC_FFT_CALLBACKS LXC_fftCallbacks;
	int LXC_fftModule;
	LXC_FFT_PLAN LXC_fftPlan;

	LXC_FFT_HANDLE()
	{
	  LXC_fftModule = LXC_fftModule_Min;
	}
} LXC_FFT_HANDLE;

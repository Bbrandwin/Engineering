//#ifdef FFTDLL_EXPORTS
#define FFTDLL_API __declspec(dllexport) 
/*#else
#define FFTDLL_API __declspec(dllimport) 
#endif*/
//   fft.h - declaration of class
//   of fast Fourier transform - FFT
//
//   The code is property of LIBROW
//   You can use it on your own
//   When utilizing credit LIBROW site

#ifndef _FFT_H_
#define _FFT_H_

//   Include complex numbers header
#include "complex.h"

class CFFT
{
public:
	//   FORWARD FOURIER TRANSFORM
	//     Input  - input data
	//     Output - transform result
	//     N      - length of both input data and result
	FFTDLL_API static bool Forward(const complex *const Input, complex *const Output, const unsigned int N);

	//   FORWARD FOURIER TRANSFORM, INPLACE VERSION
	//     Data - both input data and output
	//     N    - length of input data
	FFTDLL_API static bool Forward(complex *const Data, const unsigned int N);

	//   INVERSE FOURIER TRANSFORM
	//     Input  - input data
	//     Output - transform result
	//     N      - length of both input data and result
	//     Scale  - if to scale result
	FFTDLL_API static bool Inverse(const complex *const Input, complex *const Output, const unsigned int N, const bool Scale = true);

	//   INVERSE FOURIER TRANSFORM, INPLACE VERSION
	//     Data  - both input data and output
	//     N     - length of both input data and result
	//     Scale - if to scale result
	FFTDLL_API static bool Inverse(complex *const Data, const unsigned int N, const bool Scale = true);

protected:
	//   Rearrange function and its inplace version
	FFTDLL_API static void Rearrange(const complex *const Input, complex *const Output, const unsigned int N);
	FFTDLL_API static void Rearrange(complex *const Data, const unsigned int N);

	//   FFT implementation
	FFTDLL_API static void Perform(complex *const Data, const unsigned int N, const bool Inverse = false);

	//   Scaling of inverse FFT result
	FFTDLL_API static void Scale(complex *const Data, const unsigned int N);
};

#endif

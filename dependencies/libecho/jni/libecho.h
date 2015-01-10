/*
Copyright (c) 2014 Daniel Sobe

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/



#ifndef LIBECHO_H_INCLUDED
#define LIBECHO_H_INCLUDED

#ifdef _WIN32
#ifndef LIBECHO_NO_EXPORT_DLL_SYMBOLS
#ifdef LIBECHO_EXPORTS
#define EXPORT_FUNCTION __declspec(dllexport)
#else
#define EXPORT_FUNCTION __declspec(dllimport)
#endif
#else
#define EXPORT_FUNCTION
#endif
#endif

typedef signed char int8_t;
typedef short       int16_t;
typedef int         int32_t;

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

typedef struct EchoContext_t
{
	float    attenuationFactor;
	uint8_t  *inBuffer;
	uint8_t  *echoBuffer;
	uint32_t bufferSize;
	uint32_t echoBufferPtr;
} EchoContext;

EXPORT_FUNCTION int  Echo_init(EchoContext *pContext, 
							   uint8_t channels, 
							   uint8_t bytes_per_channel, 
							   uint16_t sampling_rate_hz,
							   float    attenuationFactor,
							   uint16_t echo_period_ms);
EXPORT_FUNCTION void Echo_free(EchoContext *pContext);
EXPORT_FUNCTION int  Echo_process(EchoContext *pContext,
				                  uint8_t     *buffer,
				                  uint32_t     len);

#endif

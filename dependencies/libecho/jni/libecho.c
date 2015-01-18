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


#include "libecho.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// #define DEBUG_WITH_FILE_IO
// #define DEBUG_WITH_PRINTF

int  Echo_init(EchoContext *pContext,
			   uint8_t channels, 
			   uint8_t bytes_per_channel, 
			   uint16_t sampling_rate_hz,
			   float    attenuationFactor,
			   uint16_t echo_period_ms)
{
	if ((bytes_per_channel != 1) && (bytes_per_channel != 2))
	{
		return -1;
	}

	pContext->bytes_per_channel = bytes_per_channel;
	pContext->attenuationFactor = attenuationFactor;

	pContext->bufferSize = (sampling_rate_hz * echo_period_ms) / 1000;
	pContext->bufferSize *= channels * bytes_per_channel;

	pContext->inBuffer = (uint8_t *) malloc(pContext->bufferSize);
	if (pContext->inBuffer == NULL)
	{
		return -1;
	}
	pContext->echoBuffer = (uint8_t *) malloc(pContext->bufferSize);
	if (pContext->echoBuffer == NULL)
	{
		free((void *) pContext->inBuffer);
		return -1;
	}

	memset((void *) pContext->echoBuffer, 0, pContext->bufferSize);

	pContext->echoBufferPtr = 0;

#ifdef DEBUG_WITH_PRINTF
	printf("Buffer size=%d.\n", pContext->bufferSize);
#endif

	return 0;
}

void Echo_free(EchoContext *pContext)
{
	free((void *) pContext->inBuffer);
	free((void *) pContext->echoBuffer);
	pContext->inBuffer = NULL;
	pContext->echoBuffer = NULL;
}

static void apply_s16le(int16_t *buffer, int16_t *echoBuffer, uint32_t offset, uint32_t len, float attenuationFactor)
{
	uint32_t i;
	int32_t sample;

	for (i = offset; i < (offset + len); i++)
	{
		sample = ((int32_t) (((float) buffer[i]) * (1.0f - attenuationFactor)));
		sample = sample + ((int16_t) (((float) echoBuffer[i]) * attenuationFactor));
		if (sample < -32768)
		{
			sample = -32768;
		}
		if (sample > 32767)
		{
			sample = 32767;
		}
		buffer[i]     = (int16_t) sample;
		echoBuffer[i] = buffer[i];
	}
}

int  Echo_process(EchoContext *pContext,
				  uint8_t     *buffer,
				  uint32_t     len)
{
	uint32_t bufferProcessed = 0;
	uint32_t currSize;
	uint32_t echoBufOffset = pContext->echoBufferPtr;
#ifdef DEBUG_WITH_FILE_IO

	FILE *fi;

#endif

#ifdef DEBUG_WITH_PRINTF
	printf("Echo start, offset=%d.\n", echoBufOffset);
#endif

	while (bufferProcessed < len)
	{
		currSize = len - bufferProcessed;
		if (currSize > (pContext->bufferSize - echoBufOffset))
		{
			currSize = pContext->bufferSize - echoBufOffset;
		}

#ifdef DEBUG_WITH_PRINTF
		printf("IN: Copy from %lx to %lx size %d.\n", buffer + bufferProcessed, pContext->inBuffer + echoBufOffset, currSize);
#endif

		memcpy(pContext->inBuffer + echoBufOffset, buffer + bufferProcessed, currSize);

#ifdef DEBUG_WITH_FILE_IO

		fi = fopen("echo_in.pcm", "ab");
		fwrite(pContext->inBuffer + echoBufOffset, 1, currSize, fi);
		fclose(fi);

#endif

		apply_s16le((int16_t *) pContext->inBuffer, (int16_t *) pContext->echoBuffer, echoBufOffset / 2, currSize / 2, pContext->attenuationFactor);

#ifdef DEBUG_WITH_FILE_IO

		fi = fopen("echo_out.pcm", "ab");
		fwrite(pContext->inBuffer + echoBufOffset, 1, currSize, fi);
		fclose(fi);

#endif

#ifdef DEBUG_WITH_PRINTF
		printf("OUT: Copy from %lx to %lx size %d.\n", pContext->inBuffer + echoBufOffset, buffer + bufferProcessed, currSize);
#endif

		memcpy(buffer + bufferProcessed, pContext->inBuffer + echoBufOffset, currSize);

		bufferProcessed += currSize;

		echoBufOffset = (echoBufOffset + currSize) % pContext->bufferSize;
	}

#ifdef DEBUG_WITH_PRINTF
	printf("Echo end, offset=%d.\n", echoBufOffset);
#endif

	pContext->echoBufferPtr = echoBufOffset;

	return 0;
}

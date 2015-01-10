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

	pContext->bufferSize = (sampling_rate_hz * 1000) / echo_period_ms;
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

	return 0;
}

void Echo_free(EchoContext *pContext)
{
	free((void *) pContext->inBuffer);
	free((void *) pContext->echoBuffer);
}

static void apply_s16le(uint16_t *buffer, uint32_t offset, uint32_t len)
{
	
}

int  Echo_process(EchoContext *pContext,
				  uint8_t     *buffer,
				  uint32_t     len)
{
	uint32_t processed = 0;
	uint32_t currSize;

	while (processed < len)
	{
		currSize = pContext->bufferSize;
		if (currSize > len - processed)
		{
			currSize = len - processed;
		}

		memcpy(pContext->inBuffer, buffer + processed, currSize);

		apply_s16le((uint16_t *) pContext->inBuffer, 0, currSize / 2);

		memcpy(buffer + processed, pContext->inBuffer, currSize);

		processed += currSize;
	}

	return 0;
}


#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "Wrapper/ReverbLibrary.h"

#define MAX_BUFSIZE 100000

char inbuf[MAX_BUFSIZE];
char outbuf[MAX_BUFSIZE];

char replydata[100];

#define FRAMECOUNT 1024

int main(void)
{
	int status, i, k;
	ReverbContext context;
	uint32_t replyCount;

	audio_buffer_t audio_in;
	audio_buffer_t audio_out;
	float tmp;

	for (i = 0; i < MAX_BUFSIZE; i++)
	{
		inbuf[i] = 0;
		outbuf[i] = 0;
	}


	context.hInstance  = NULL;
	context.auxiliary  = false;

    context.preset     = true;
    context.curPreset  = REVERB_PRESET_LAST + 1;
	context.nextPreset = REVERB_PRESET_SMALLROOM;

	status = Reverb_init(&context);

	printf("--Reverb init: %d.--\n", status);

	// no accumulation needed
	context.config.outputCfg.accessMode = EFFECT_BUFFER_ACCESS_WRITE;

	status = Reverb_setConfig(&context, &(context.config));

	printf("--Reverb set config: %d.--\n", status);

	audio_in.raw = inbuf;
	audio_out.raw = outbuf;

	audio_in.frameCount = FRAMECOUNT;
	audio_out.frameCount = FRAMECOUNT;

	for (i = 0; i < FRAMECOUNT; i += 2)
	{
		tmp = ((((float) i) / 40.0f) * 2 * 3.1415926f);
		audio_in.s16[i] = (int16_t) (sinf(tmp) * 32760.0f);
		tmp = ((((float) i) / 41.0f) * 2 * 3.1415926f);
		audio_in.s16[i + 1] = (int16_t) (sinf(tmp) * 32760.0f);
		// audio_in.s16[i] = (int16_t) i;
	}

    // Allocate memory for reverb process (*2 is for STEREO)
    context.InFrames32  = (LVM_INT32 *)malloc(LVREV_MAX_FRAME_SIZE * sizeof(LVM_INT32) * 2);
    context.OutFrames32 = (LVM_INT32 *)malloc(LVREV_MAX_FRAME_SIZE * sizeof(LVM_INT32) * 2);

    replyCount = sizeof(int);

    status = Reverb_command(&context, EFFECT_CMD_ENABLE, 0, NULL, &replyCount, replydata);

	printf("--Reverb command: %d.--\n", status);

	for (k = 0; k < 20; k++)
	{
		status = Reverb_process(&context, &audio_in, &audio_out);

		printf("--Reverb process: %d.--\n", status);

		for (i = 0; i < MAX_BUFSIZE; i++)
		{
			if (outbuf[i] != inbuf[i])
			{
				printf("%04X: %02X\n", i, (uint8_t) outbuf[i]);
			}
		}
	}

	/*
	for (i = 0; i < FRAMECOUNT; i++)
	{
		audio_in.s16[i] = 0;
	}
	*/

	for (k = 0; k < 10000; k++)
	{

		status = Reverb_process(&context, &audio_in, &audio_out);

		printf("--Reverb process iter %d: %d.--\n", k, status);

		for (i = 0; i < MAX_BUFSIZE; i++)
		{
			if (outbuf[i] != inbuf[i])
			{
				printf("%04X: %02X\n", i, (uint8_t) outbuf[i]);
			}
		}
		// printf("\n");
	}

	free(context.InFrames32);
	free(context.OutFrames32);

	Reverb_free(&context);

	return 0;
}

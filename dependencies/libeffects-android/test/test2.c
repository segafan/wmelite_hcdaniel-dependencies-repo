
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

	FILE *in = fopen("in.pcm", "rb");
	FILE *out = fopen("out.pcm", "wb");

	for (i = 0; i < MAX_BUFSIZE; i++)
	{
		inbuf[i] = 0;
		outbuf[i] = 0;
	}


	context.hInstance  = NULL;
	context.boolAuxiliary  = 0;

    context.boolPreset     = 1;
    context.curPreset  = REVERB_PRESET_LAST + 1;
	context.nextPreset = REVERB_PRESET_LARGEHALL;

	status = Reverb_init(&context);

	printf("--Reverb init: %d.--\n", status);

	// no accumulation needed
	context.config.outputCfg.accessMode = EFFECT_BUFFER_ACCESS_WRITE;

	//status = Reverb_setConfig(&context, &(context.config));

	//printf("--Reverb set config: %d.--\n", status);

	audio_in.raw = inbuf;
	audio_out.raw = outbuf;

	audio_in.frameCount = FRAMECOUNT;
	audio_out.frameCount = FRAMECOUNT;

    // Allocate memory for reverb process (*2 is for STEREO)
    context.InFrames32  = (LVM_INT32 *)malloc(LVREV_MAX_FRAME_SIZE * sizeof(LVM_INT32) * 2);
    context.OutFrames32 = (LVM_INT32 *)malloc(LVREV_MAX_FRAME_SIZE * sizeof(LVM_INT32) * 2);

    replyCount = sizeof(int);

    status = Reverb_command(&context, EFFECT_CMD_ENABLE, 0, NULL, &replyCount, replydata);

	printf("--Reverb command: %d.--\n", status);

	while ((i = fread(inbuf, 2, FRAMECOUNT, in)) == FRAMECOUNT)
	{
		status = Reverb_process(&context, &audio_in, &audio_out);

		printf("--Reverb process: %d.--\n", status);

		fwrite(outbuf, 2, FRAMECOUNT, out);
	}

	printf("Last i=%d.\n", i);

	free(context.InFrames32);
	free(context.OutFrames32);

	Reverb_free(&context);

	fclose(in);
	fclose(out);

	return 0;
}

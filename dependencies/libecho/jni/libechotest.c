
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include "libecho.h"

#define MAX_BUFSIZE 100000

char buf[MAX_BUFSIZE];

int main(void)
{
	int status, i;
	EchoContext context;
	FILE *in;
	FILE *out;

	in = fopen("O:\\wmelite-dependencies-for-linux-and-android\\dependencies\\libecho\\libecho\\libechotest\\in.pcm", "rb");

	if (in == NULL)
	{
		printf("Error! Infile not found, error=%d!\n", errno);
		return -1;
	}

	out = fopen("O:\\wmelite-dependencies-for-linux-and-android\\dependencies\\libecho\\libecho\\libechotest\\out.pcm", "wb");

	if (out == NULL)
	{
		printf("Error! Outfile not open, error=%d!\n", errno);
		return -1;
	}

	status = Echo_init(&context, 2, 2, 44100, 0.3f, 300);

	printf("--Echo init: %d.--\n", status);

	while ((i = fread(buf, 1, MAX_BUFSIZE, in)) > 0)
	{
		printf("--Echo before process: len=%d buf=%lx.\n", i, (uint32_t) buf);

		status = Echo_process(&context, buf, i);

		printf("--Echo process: %d.--\n", status);

		fwrite(buf, 1, i, out);
	}

	Echo_free(&context);

	fclose(in);
	fclose(out);

	return 0;
}

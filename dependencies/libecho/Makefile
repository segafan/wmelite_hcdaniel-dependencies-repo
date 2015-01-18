
CC=gcc
CPP=g++
RM=rm

OUTDIR=out/


OBJS=\
    $(OUTDIR)/libecho.o

TESTOBJS=\
    $(OUTDIR)/libechotest.o

INCS=\
    -Ijni/

ARCHFLAGS=-m32
CFLAGS=-fPIC -g -std=c99 $(ARCHFLAGS) -m32 -Wall
# LIBFLAGS=-shared -Wl,-soname,libreverbwrapper.so
LIBFLAGS=-fPIC -shared -Wl,-export-dynamic -lc

$(OUTDIR)/%.o: jni/%.c
	$(CC) $(INCS) -c -o $@ $< $(CFLAGS)

all: mkdirs $(OBJS) libs echotest

mkdirs:
	mkdir -p out/

libs:
	$(CC) $(LIBFLAGS) $(ARCHFLAGS) -o $(OUTDIR)/libecho.so $(OBJS)
	ar rcs $(OUTDIR)/libecho.a $(OBJS)

echotest: $(TESTOBJS) $(TESTOBJS2)
	$(CC) -fPIC -o $(OUTDIR)/echotest $(ARCHFLAGS) -L$(OUTDIR) $(TESTOBJS) -lecho -lm

clean:
	$(RM) -f $(OBJS) $(TESTOBJS) $(OUTDIR)/libecho* $(OUTDIR)/echo*

.PHONY: clean all


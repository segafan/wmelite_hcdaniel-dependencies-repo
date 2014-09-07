
CC=gcc
RM=rm

OUTDIR=out/


OBJS=\
    $(OUTDIR)/Reverb/src/LVREV_ApplyNewSettings.o \
    $(OUTDIR)/Reverb/src/LVREV_ClearAudioBuffers.o \
    $(OUTDIR)/Reverb/src/LVREV_GetControlParameters.o \
    $(OUTDIR)/Reverb/src/LVREV_GetInstanceHandle.o \
    $(OUTDIR)/Reverb/src/LVREV_GetMemoryTable.o \
    $(OUTDIR)/Reverb/src/LVREV_Process.o \
    $(OUTDIR)/Reverb/src/LVREV_SetControlParameters.o \
    $(OUTDIR)/Reverb/src/LVREV_Tables.o \
    $(OUTDIR)/Common/src/Abs_32.o \
    $(OUTDIR)/Common/src/InstAlloc.o \
    $(OUTDIR)/Common/src/LoadConst_16.o \
    $(OUTDIR)/Common/src/LoadConst_32.o \
    $(OUTDIR)/Common/src/From2iToMono_32.o \
    $(OUTDIR)/Common/src/Mult3s_32x16.o \
    $(OUTDIR)/Common/src/FO_1I_D32F32C31_TRC_WRA_01.o \
    $(OUTDIR)/Common/src/FO_1I_D32F32Cll_TRC_WRA_01_Init.o \
    $(OUTDIR)/Common/src/DelayAllPass_Sat_32x16To32.o \
    $(OUTDIR)/Common/src/Copy_16.o \
    $(OUTDIR)/Common/src/Mac3s_Sat_32x16.o \
    $(OUTDIR)/Common/src/DelayWrite_32.o \
    $(OUTDIR)/Common/src/Shift_Sat_v32xv32.o \
    $(OUTDIR)/Common/src/Add2_Sat_32x32.o \
    $(OUTDIR)/Common/src/JoinTo2i_32x32.o \
    $(OUTDIR)/Common/src/MonoTo2I_32.o \
    $(OUTDIR)/Common/src/LVM_FO_HPF.o \
    $(OUTDIR)/Common/src/LVM_FO_LPF.o \
    $(OUTDIR)/Common/src/LVM_Polynomial.o \
    $(OUTDIR)/Common/src/LVM_Power10.o \
    $(OUTDIR)/Common/src/LVM_GetOmega.o \
    $(OUTDIR)/Common/src/MixSoft_2St_D32C31_SAT.o \
    $(OUTDIR)/Common/src/MixSoft_1St_D32C31_WRA.o \
    $(OUTDIR)/Common/src/MixInSoft_D32C31_SAT.o \
    $(OUTDIR)/Common/src/LVM_Mixer_TimeConstant.o \
    $(OUTDIR)/Common/src/Core_MixHard_2St_D32C31_SAT.o \
    $(OUTDIR)/Common/src/Core_MixSoft_1St_D32C31_WRA.o \
    $(OUTDIR)/Common/src/Core_MixInSoft_D32C31_SAT.o \
    $(OUTDIR)/Wrapper/EffectReverb.o

INCS=\
    -Ijni/Reverb/lib \
    -Ijni/Reverb/src \
    -Ijni/Common/lib \
    -Ijni/Common/src \
    -Ijni/Wrapper    \
    -Ijni

CFLAGS=-fvisibility=hidden -fPIC


$(OUTDIR)/Common/src/%.o: jni/Common/src/%.c
	$(CC) $(INCS) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/Reverb/src/%.o: jni/Reverb/src/%.c
	$(CC) $(INCS) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/Wrapper/%.o: jni/Wrapper/%.cpp
	$(CC) $(INCS) -c -o $@ $< $(CFLAGS)

all: $(OBJS) libreverbwrapper

libreverbwrapper:
	$(CC) -o $(OUTDIR)/libreverbwrapper.so -shared $(OBJS)

clean:
	$(RM) -f $(OBJS) $(OUTDIR)/libreverbwrapper.so

.PHONY: clean all


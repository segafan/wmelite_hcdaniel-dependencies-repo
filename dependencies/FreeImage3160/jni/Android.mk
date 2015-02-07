
LOCAL_PATH              :=  $(call my-dir)
#
include $(CLEAR_VARS)

COMMON_INCLUDE_PATHS = \
-I. -ISource \
-ISource/Metadata \
-ISource/FreeImageToolkit \
-ISource/LibJPEG \
-ISource/LibPNG \
-ISource/LibTIFF4 \
-ISource/ZLib \
-ISource/OpenEXR -ISource/OpenEXR/Half -ISource/OpenEXR/Iex -ISource/OpenEXR/IlmImf -ISource/OpenEXR/IlmThread -ISource/OpenEXR/Imath
#-ISource/LibRawLite -ISource/LibRawLite/dcraw -ISource/LibRawLite/internal -ISource/LibRawLite/libraw -ISource/LibRawLite/src
#-ISource/LibJXR/jxrgluelib/ -ISource/LibJXR/image/sys/ -ISource/LibJXR/common/include/ \
#-ISource/LibOpenJPEG \

LOCAL_CFLAGS        +=  $(COMMON_INCLUDE_PATHS)

LOCAL_CPPFLAGS        += -fexceptions -frtti $(COMMON_INCLUDE_PATHS)

# LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES         :=  \
$(wildcard $(LOCAL_PATH)/Source/DeprecationManager/*.cpp) \
Source/FreeImage/BitmapAccess.cpp \
Source/FreeImage/CacheFile.cpp \
Source/FreeImage/ColorLookup.cpp \
Source/FreeImage/Conversion16_555.cpp \
Source/FreeImage/Conversion16_565.cpp \
Source/FreeImage/Conversion24.cpp \
Source/FreeImage/Conversion32.cpp \
Source/FreeImage/Conversion4.cpp \
Source/FreeImage/Conversion8.cpp \
Source/FreeImage/Conversion.cpp \
Source/FreeImage/ConversionFloat.cpp \
Source/FreeImage/ConversionRGB16.cpp \
Source/FreeImage/ConversionRGBF.cpp \
Source/FreeImage/ConversionType.cpp \
Source/FreeImage/ConversionUINT16.cpp \
Source/FreeImage/FreeImage.cpp \
Source/FreeImage/FreeImageIO.cpp \
Source/FreeImage/GetType.cpp \
Source/FreeImage/Halftoning.cpp \
Source/FreeImage/J2KHelper.cpp \
Source/FreeImage/MemoryIO.cpp \
Source/FreeImage/MNGHelper.cpp \
Source/FreeImage/MultiPage.cpp \
Source/FreeImage/NNQuantizer.cpp \
Source/FreeImage/PixelAccess.cpp \
Source/FreeImage/PluginBMP.cpp \
Source/FreeImage/Plugin.cpp \
Source/FreeImage/PluginCUT.cpp \
Source/FreeImage/PluginDDS.cpp \
Source/FreeImage/PluginEXR.cpp \
Source/FreeImage/PluginG3.cpp \
Source/FreeImage/PluginGIF.cpp \
Source/FreeImage/PluginHDR.cpp \
Source/FreeImage/PluginICO.cpp \
Source/FreeImage/PluginIFF.cpp \
Source/FreeImage/PluginJ2K.cpp \
Source/FreeImage/PluginJNG.cpp \
Source/FreeImage/PluginJP2.cpp \
Source/FreeImage/PluginJPEG.cpp \
Source/FreeImage/PluginKOALA.cpp \
Source/FreeImage/PluginMNG.cpp \
Source/FreeImage/PluginPCD.cpp \
Source/FreeImage/PluginPCX.cpp \
Source/FreeImage/PluginPFM.cpp \
Source/FreeImage/PluginPICT.cpp \
Source/FreeImage/PluginPNG.cpp \
Source/FreeImage/PluginPNM.cpp \
Source/FreeImage/PluginPSD.cpp \
Source/FreeImage/PluginRAS.cpp \
Source/FreeImage/PluginRAW.cpp \
Source/FreeImage/PluginSGI.cpp \
Source/FreeImage/PluginTARGA.cpp \
Source/FreeImage/PluginTIFF.cpp \
Source/FreeImage/PluginWBMP.cpp \
Source/FreeImage/PluginWebP.cpp \
Source/FreeImage/PluginXBM.cpp \
Source/FreeImage/PluginXPM.cpp \
Source/FreeImage/PSDParser.cpp \
Source/FreeImage/TIFFLogLuv.cpp \
Source/FreeImage/tmoColorConvert.cpp \
Source/FreeImage/tmoDrago03.cpp \
Source/FreeImage/tmoFattal02.cpp \
Source/FreeImage/tmoReinhard05.cpp \
Source/FreeImage/ToneMapping.cpp \
Source/FreeImage/WuQuantizer.cpp \
Source/FreeImage/ZLibInterface.cpp \
$(wildcard $(LOCAL_PATH)/Source/FreeImageToolkit/*.cpp) \
Source/LibJPEG/cdjpeg.c \
Source/LibJPEG/cjpeg.c \
Source/LibJPEG/ckconfig.c \
Source/LibJPEG/djpeg.c \
Source/LibJPEG/example.c \
Source/LibJPEG/jaricom.c \
Source/LibJPEG/jcapimin.c \
Source/LibJPEG/jcapistd.c \
Source/LibJPEG/jcarith.c \
Source/LibJPEG/jccoefct.c \
Source/LibJPEG/jccolor.c \
Source/LibJPEG/jcdctmgr.c \
Source/LibJPEG/jchuff.c \
Source/LibJPEG/jcinit.c \
Source/LibJPEG/jcmainct.c \
Source/LibJPEG/jcmarker.c \
Source/LibJPEG/jcmaster.c \
Source/LibJPEG/jcomapi.c \
Source/LibJPEG/jcparam.c \
Source/LibJPEG/jcprepct.c \
Source/LibJPEG/jcsample.c \
Source/LibJPEG/jctrans.c \
Source/LibJPEG/jdapimin.c \
Source/LibJPEG/jdapistd.c \
Source/LibJPEG/jdarith.c \
Source/LibJPEG/jdatadst.c \
Source/LibJPEG/jdatasrc.c \
Source/LibJPEG/jdcoefct.c \
Source/LibJPEG/jdcolor.c \
Source/LibJPEG/jddctmgr.c \
Source/LibJPEG/jdhuff.c \
Source/LibJPEG/jdinput.c \
Source/LibJPEG/jdmainct.c \
Source/LibJPEG/jdmarker.c \
Source/LibJPEG/jdmaster.c \
Source/LibJPEG/jdmerge.c \
Source/LibJPEG/jdpostct.c \
Source/LibJPEG/jdsample.c \
Source/LibJPEG/jdtrans.c \
Source/LibJPEG/jerror.c \
Source/LibJPEG/jfdctflt.c \
Source/LibJPEG/jfdctfst.c \
Source/LibJPEG/jfdctint.c \
Source/LibJPEG/jidctflt.c \
Source/LibJPEG/jidctfst.c \
Source/LibJPEG/jidctint.c \
Source/LibJPEG/jmemansi.c \
Source/LibJPEG/jmemmgr.c \
Source/LibJPEG/jmemname.c \
Source/LibJPEG/jmemnobs.c \
Source/LibJPEG/jpegtran.c \
Source/LibJPEG/jquant1.c \
Source/LibJPEG/jquant2.c \
Source/LibJPEG/jutils.c \
Source/LibJPEG/rdbmp.c \
Source/LibJPEG/rdcolmap.c \
Source/LibJPEG/rdgif.c \
Source/LibJPEG/rdjpgcom.c \
Source/LibJPEG/rdppm.c \
Source/LibJPEG/rdrle.c \
Source/LibJPEG/rdswitch.c \
Source/LibJPEG/rdtarga.c \
Source/LibJPEG/transupp.c \
Source/LibJPEG/wrbmp.c \
Source/LibJPEG/wrgif.c \
Source/LibJPEG/wrjpgcom.c \
Source/LibJPEG/wrppm.c \
Source/LibJPEG/wrrle.c \
Source/LibJPEG/wrtarga.c \
$(wildcard $(LOCAL_PATH)/Source/LibPNG/*.c) \
$(wildcard $(LOCAL_PATH)/Source/LibTIFF4/*.c) \
$(wildcard $(LOCAL_PATH)/Source/LibWebP/src/dec/*.c) \
$(wildcard $(LOCAL_PATH)/Source/LibWebP/src/demux/*.c) \
$(wildcard $(LOCAL_PATH)/Source/LibWebP/src/dsp/*.c) \
$(wildcard $(LOCAL_PATH)/Source/LibWebP/src/enc/*.c) \
$(wildcard $(LOCAL_PATH)/Source/LibWebP/src/mux/*.c) \
$(wildcard $(LOCAL_PATH)/Source/LibWebP/src/utils/*.c) \
$(wildcard $(LOCAL_PATH)/Source/Metadata/*.cpp) \
$(wildcard $(LOCAL_PATH)/Source/OpenEXR/Half/*.cpp) \
$(wildcard $(LOCAL_PATH)/Source/OpenEXR/Iex/*.cpp) \
$(wildcard $(LOCAL_PATH)/Source/OpenEXR/IlmImf/*.cpp) \
$(wildcard $(LOCAL_PATH)/Source/OpenEXR/IlmThread/*.cpp) \
$(wildcard $(LOCAL_PATH)/Source/OpenEXR/Imath/*.cpp)
#$(wildcard $(LOCAL_PATH)/Source/LibJXR/image/decode/*.c) \
#$(wildcard $(LOCAL_PATH)/Source/LibJXR/image/encode/*.c) \
#$(wildcard $(LOCAL_PATH)/Source/LibJXR/image/sys/*.c) \
#Source/FreeImage/PluginJXR.cpp
#Source/LibJPEG/ansi2knr.c
#Source/LibJPEG/jmemdos.c \
#Source/LibJPEG/jmemmac.c \
#$(wildcard $(LOCAL_PATH)/Source/LibOpenJPEG/*.c) \
#$(wildcard $(LOCAL_PATH)/Source/LibRawLite/dcraw/*.c) \
#$(wildcard $(LOCAL_PATH)/Source/LibRawLite/internal/*.cpp) \
#$(wildcard $(LOCAL_PATH)/Source/LibRawLite/internal/*.c) \
#$(wildcard $(LOCAL_PATH)/Source/LibRawLite/src/*.cpp) \


#
LOCAL_CFLAGS            += -O2

LOCAL_CPPFLAGS            += -O2
#
LOCAL_MODULE            := freeimage

#
LOCAL_LDLIBS            := -llog -lz

include $(BUILD_SHARED_LIBRARY)


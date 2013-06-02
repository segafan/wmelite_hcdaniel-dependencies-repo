# this is now the default FreeType build for Android
#
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libfreetype

# compile in ARM mode, since the glyph loader/renderer is a hotspot
# when loading complex pages in the browser
#
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES:= \
src/autofit/afangles.c \
src/autofit/afdummy.c \
src/autofit/afglobal.c \
src/autofit/afloader.c \
src/autofit/afpic.c \
src/autofit/afwarp.c \
src/autofit/autofit.c \
src/base/basepic.c \
src/base/ftadvanc.c \
src/base/ftapi.c \
src/base/ftbase.c \
src/base/ftbbox.c \
src/base/ftbdf.c \
src/base/ftbitmap.c \
src/base/ftcalc.c \
src/base/ftcid.c \
src/base/ftdbgmem.c \
src/base/ftdebug.c \
src/base/ftfstype.c \
src/base/ftgasp.c \
src/base/ftgloadr.c \
src/base/ftglyph.c \
src/base/ftgxval.c \
src/base/ftinit.c \
src/base/ftlcdfil.c \
src/base/ftmm.c \
src/base/ftobjs.c \
src/base/ftotval.c \
src/base/ftoutln.c \
src/base/ftpatent.c \
src/base/ftpfr.c \
src/base/ftpic.c \
src/base/ftrfork.c \
src/base/ftsnames.c \
src/base/ftstream.c \
src/base/ftstroke.c \
src/base/ftsynth.c \
src/base/ftsystem.c \
src/base/fttrigon.c \
src/base/fttype1.c \
src/base/ftutil.c \
src/base/ftwinfnt.c \
src/base/ftxf86.c \
src/base/md5.c \
src/bdf/bdf.c \
src/bdf/bdfdrivr.c \
src/bdf/bdflib.c \
src/bzip2/ftbzip2.c \
src/cache/ftcache.c \
src/cache/ftcbasic.c \
src/cache/ftccache.c \
src/cache/ftccmap.c \
src/cache/ftcglyph.c \
src/cache/ftcimage.c \
src/cache/ftcmanag.c \
src/cache/ftcmru.c \
src/cache/ftcsbits.c \
src/cff/cf2arrst.c \
src/cff/cf2blues.c \
src/cff/cf2error.c \
src/cff/cf2font.c \
src/cff/cf2ft.c \
src/cff/cf2hints.c \
src/cff/cf2intrp.c \
src/cff/cf2read.c \
src/cff/cf2stack.c \
src/cff/cff.c \
src/cff/cffcmap.c \
src/cff/cffdrivr.c \
src/cff/cffgload.c \
src/cff/cffload.c \
src/cff/cffobjs.c \
src/cff/cffparse.c \
src/cff/cffpic.c \
src/cid/cidgload.c \
src/cid/cidload.c \
src/cid/cidobjs.c \
src/cid/cidparse.c \
src/cid/cidriver.c \
src/cid/type1cid.c \
src/gxvalid/gxvalid.c \
src/gxvalid/gxvbsln.c \
src/gxvalid/gxvcommn.c \
src/gxvalid/gxvfeat.c \
src/gxvalid/gxvfgen.c \
src/gxvalid/gxvjust.c \
src/gxvalid/gxvkern.c \
src/gxvalid/gxvlcar.c \
src/gxvalid/gxvmod.c \
src/gxvalid/gxvmort0.c \
src/gxvalid/gxvmort1.c \
src/gxvalid/gxvmort2.c \
src/gxvalid/gxvmort4.c \
src/gxvalid/gxvmort5.c \
src/gxvalid/gxvmort.c \
src/gxvalid/gxvmorx0.c \
src/gxvalid/gxvmorx1.c \
src/gxvalid/gxvmorx2.c \
src/gxvalid/gxvmorx4.c \
src/gxvalid/gxvmorx5.c \
src/gxvalid/gxvmorx.c \
src/gxvalid/gxvopbd.c \
src/gxvalid/gxvprop.c \
src/gxvalid/gxvtrak.c \
src/lzw/ftlzw.c \
src/lzw/ftzopen.c \
src/otvalid/otvalid.c \
src/otvalid/otvbase.c \
src/otvalid/otvcommn.c \
src/otvalid/otvgdef.c \
src/otvalid/otvgpos.c \
src/otvalid/otvgsub.c \
src/otvalid/otvjstf.c \
src/otvalid/otvmath.c \
src/otvalid/otvmod.c \
src/pcf/pcf.c \
src/pcf/pcfdrivr.c \
src/pcf/pcfread.c \
src/pcf/pcfutil.c \
src/pfr/pfr.c \
src/pfr/pfrcmap.c \
src/pfr/pfrdrivr.c \
src/pfr/pfrgload.c \
src/pfr/pfrload.c \
src/pfr/pfrobjs.c \
src/pfr/pfrsbit.c \
src/psaux/afmparse.c \
src/psaux/psaux.c \
src/psaux/psauxmod.c \
src/psaux/psconv.c \
src/psaux/psobjs.c \
src/psaux/t1cmap.c \
src/psaux/t1decode.c \
src/pshinter/pshalgo.c \
src/pshinter/pshglob.c \
src/pshinter/pshinter.c \
src/pshinter/pshmod.c \
src/pshinter/pshpic.c \
src/pshinter/pshrec.c \
src/psnames/psmodule.c \
src/psnames/psnames.c \
src/psnames/pspic.c \
src/raster/ftraster.c \
src/raster/raster.c \
src/raster/rastpic.c \
src/sfnt/sfdriver.c \
src/sfnt/sfnt.c \
src/sfnt/sfntpic.c \
src/sfnt/sfobjs.c \
src/sfnt/ttbdf.c \
src/sfnt/ttcmap.c \
src/sfnt/ttkern.c \
src/sfnt/ttload.c \
src/sfnt/ttmtx.c \
src/sfnt/ttpost.c \
src/sfnt/ttsbit0.c \
src/sfnt/ttsbit.c \
src/smooth/ftgrays.c \
src/smooth/ftspic.c \
src/smooth/smooth.c \
src/tools/apinames.c \
src/tools/ftrandom/ftrandom.c \
src/tools/test_afm.c \
src/tools/test_bbox.c \
src/tools/test_trig.c \
src/truetype/truetype.c \
src/truetype/ttdriver.c \
src/truetype/ttgload.c \
src/truetype/ttgxvar.c \
src/truetype/ttinterp.c \
src/truetype/ttobjs.c \
src/truetype/ttpic.c \
src/truetype/ttpload.c \
src/truetype/ttsubpix.c \
src/type1/t1afm.c \
src/type1/t1driver.c \
src/type1/t1gload.c \
src/type1/t1load.c \
src/type1/t1objs.c \
src/type1/t1parse.c \
src/type1/type1.c \
src/type42/t42drivr.c \
src/type42/t42objs.c \
src/type42/t42parse.c \
src/type42/type42.c \
src/winfonts/winfnt.c \
src/gzip/ftgzip.c \

# src/autofit/aflatin2.c \
# src/base/ftmac.c \
#src/gzip/adler32.c \
#src/gzip/infblock.c \
#src/gzip/infcodes.c \
#src/gzip/inflate.c \
#src/gzip/inftrees.c \
#src/gzip/infutil.c \
#src/gzip/zutil.c \

#src/autofit/afindic.c \
#src/autofit/afcjk.c \
#src/autofit/aflatin.c \
#src/autofit/afmodule.c \
#src/autofit/afhints.c \
#src/smooth/ftsmooth.c \
#src/raster/ftrend1.c \


LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include/ \
	$(LOCAL_PATH)/include/freetype 
#	$(LOCAL_PATH)/include/freetype/config

LOCAL_CFLAGS += -W -Wall
LOCAL_CFLAGS += -fPIC -DPIC
# LOCAL_CFLAGS += "-DDARWIN_NO_CARBON"
LOCAL_CFLAGS += "-DFT2_BUILD_LIBRARY"
LOCAL_CFLAGS += -DFT_CONFIG_OPTION_SYSTEM_ZLIB -DFT_CONFIG_CONFIG_H="<ftconfig.h>"

LOCAL_CFLAGS += -O2

include $(BUILD_STATIC_LIBRARY)

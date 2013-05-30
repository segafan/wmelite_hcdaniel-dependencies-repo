#!/bin/sh

DIRLIST=". Source Source/Metadata Source/FreeImageToolkit Source/LibJPEG Source/LibPNG Source/LibTIFF4 Source/ZLib Source/LibOpenJPEG Source/OpenEXR Source/OpenEXR/Half Source/OpenEXR/Iex Source/OpenEXR/IlmImf Source/OpenEXR/IlmThread Source/OpenEXR/Imath Source/LibRawLite Source/LibRawLite/dcraw Source/LibRawLite/internal Source/LibRawLite/libraw Source/LibRawLite/src"

# echo "VER_MAJOR = 3" > Makefile.srcs
# echo "VER_MINOR = 15.4" >> Makefile.srcs

# echo -n "SRCS = " >> Makefile.srcs
echo > Android.mk.raw
for DIR in $DIRLIST; do
	VCPRJS=`echo $DIR/*.2008.vcproj`
	if [ "$VCPRJS" != "$DIR/*.2008.vcproj" ]; then
		egrep 'RelativePath=.*\.(c|cpp)' $DIR/*.2008.vcproj | cut -d'"' -f2 | tr '\\' '/' | awk '{print "'$DIR'/"$0}' | tr '\r\n' '\n' | tr -s ' ' >> Android.mk.raw
	fi
done
echo >> Android.mk.raw

#echo -n "INCLS = " >> Makefile.srcs
#find . -name "*.h" -print | xargs echo >> Makefile.srcs
#echo >> Makefile.srcs

#echo -n "INCLUDE =" >> Makefile.srcs
for DIR in $DIRLIST; do
	echo -n " -I$DIR" >> Android.mk.raw
done
echo >> Android.mk.raw



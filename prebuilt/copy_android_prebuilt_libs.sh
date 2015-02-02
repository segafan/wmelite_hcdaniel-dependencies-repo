#!/bin/bash

for i in armeabi armeabi-v7a x86 mips arm64-v8a mips64 x86_64; do
	cp ../dependencies/FreeImage3154/libs/$i/libfreeimage.so           android/$i/
	cp ../dependencies/libfreetype-android/obj/local/$i/libfreetype.a  android/$i/
	cp ../dependencies/SDL/libs/$i/libSDL2.so                          android/$i/
	cp ../dependencies/SDL_mixer/libs/$i/libSDL2_mixer.so              android/$i/
	cp ../dependencies/libeffects-android/libs/$i/libeffectsprivate.so android/$i/
	cp ../dependencies/libecho/libs/$i/libecho.so                      android/$i/
done


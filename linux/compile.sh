#!/bin/bash

SDLINCLUDE=-I/usr/local/include/SDL2/ 
BASSINCLUDE=-I/usr/local/bass/
FREETYPEINCLUDE=-I/usr/include/freetype2/

BASSLINK=-L/usr/local/bass/

SOURCES=

rm -rf *.o wmelite

for i in $(find ../src -name "*.cpp"); do
	g++ -Wno-write-strings -Wno-conversion-null $SDLINCLUDE $BASSINCLUDE $FREETYPEINCLUDE -c $i 
	# export SOURCES=$SOURCES" "$(echo $i | sed -e s/.cpp/.o/)
done

for i in $(find ../src -name "*.c"); do
	gcc $SDLINCLUDE $BASSINCLUDE $FREETYPEINCLUDE -c $i 
	# export SOURCES=$SOURCES" "$(echo $i | sed -e s/.c/.o/ | sed -e s/\.\.\/src\///)
done

g++ -o wmelite *.o -lSDL2 $BASSLINK -lbass -lboost_filesystem -lboost_system -lfreeimage -lfreetype


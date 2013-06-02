#!/bin/bash

reset
for i in $(find . -name "*"); do 
	echo $i; 
	cat $i | grep "__WIN32__"; 
	cat $i | grep "__MACOSX__"; 
	cat $i | grep "__IPHONEOS__"; 
	cat $i | grep "_MSC_VER"; 
	cat $i | grep "__APPLE__"; 
	cat $i | grep "__IPHONE__"; 
	cat $i | grep "__OBJC__"; 
done


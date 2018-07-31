#!/bin/bash
#Build and run
echo "Building"
g++ SmartCam.cpp ce_io.cpp `pkg-config --cflags --libs opencv` -std=c++11 -o SmartCam
echo "Running"
gksudo ./SmartCam



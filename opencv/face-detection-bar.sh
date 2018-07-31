#!/bin/bash
g++ face-detection.cpp `pkg-config --cflags --libs opencv` -o face-detection -std=c++11
gksudo ./face-detection

#!/bin/bash
g++ display.cpp `pkg-config --cflags --libs opencv` -o display
gksudo ./display



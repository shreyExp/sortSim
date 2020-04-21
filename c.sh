#!/bin/bash
g++ -o $1 $2 element.h `pkg-config --libs --cflags opencv4`

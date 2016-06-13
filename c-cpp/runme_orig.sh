#!/bin/sh

export np=`grep processor /proc/cpuinfo | wc -l`

./TEST -S 1 -f 1 -d 1 -t $np OPT_ARGS

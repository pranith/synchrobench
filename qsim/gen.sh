#!/bin/bash

for d in ../c-cpp/bin/*; do
    if [[ -x $d ]]; then
        cp $d .
        bench=`basename $d`
        sed "s/TEST/$bench/g" runme_orig.sh > runme.sh;
        tar -cf $bench.tar $bench runme.sh;
        rm -f $bench
    fi;
    rm -f runme.sh
done

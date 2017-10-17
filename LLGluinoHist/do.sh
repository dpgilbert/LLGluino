#!/bin/bash

declare -a CTAUS=(0p001 0p01 0p1 1 10 100 1000 100000 1e18)

INDIR=/nfs-6/userdata/mt2/LLGluino/
OUTDIR=../babymaker/data/

for CTAU in ${CTAUS[@]}; do
    eval 'nohup nice -n 10 ./LLGluinoHist.exe ${INDIR} ${CTAU} ${OUTDIR} >& logs/LL_${CTAU}_log.txt &'
done

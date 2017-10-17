#!/bin/bash

declare -a LLSamples=(0p001 10 1e18)
#declare -a LLSamples=(1e18)

INDIR=/hadoop/cms/store/user/dpgilber/mt2babies/LLGluino_
OUTDIR=output/

mkdir -p ${OUTDIR}

for SAMPLE in ${LLSamples[@]}; do
    eval 'nohup nice -n 10 ./T1qqqqSkim.exe ${INDIR}${SAMPLE} T1qqqq ${OUTDIR} ${SAMPLE} >& logs/LL_${SAMPLE}_log.txt &'
done

INDIR=/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/

eval 'nohup nice -n 10 ./T1qqqqSkim.exe ${INDIR} T1qqqq ${OUTDIR} >& logs/T1qqqq_log.txt &'
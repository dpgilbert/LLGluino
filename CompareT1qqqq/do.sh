#!/bin/bash

make -j 12 || return $?

MAXEVT=-1
OUTDIR=output/
LOGDIR=logs/
mkdir -p ${OUTDIR}
mkdir -p ${LOGDIR}

#most recent run2017
INDIR=../T1qqqqSkim/output/
declare -a Samples=(0p001 10 1e18 T1qqqq)
declare -a MassPoints=(1400_1200 1400_800 1400_200)

for SAMPLE in ${Samples[@]}; do
    for MASSPOINT in ${MassPoints[@]}; do
	eval "nohup nice -n 10 ./CompareT1qqqq.exe ${INDIR} ${SAMPLE}_${MASSPOINT} ${OUTDIR} ${MAXEVT} >& ${LOGDIR}/log_${SAMPLE}_${MASSPOINT}.txt &"
    done
done
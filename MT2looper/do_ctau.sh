#!/bin/bash

make -j12
if [[ $? != 0 ]]; then return $?; fi

OUTDIR=output/full2016_v16_Feb15
LOGDIR=logs/
mkdir -p ${OUTDIR}
mkdir -p ${LOGDIR}

INDIR=/nfs-6/userdata/mt2/LLGluino
declare -a CTAUS=(0p001 0p01 0p1 1 10 100 1000 10000 100000 1e18)
for CTAU in ${CTAUS[@]};
  do echo nice -n 10 ./runLooper ${INDIR} T1qqqq_ctau-${CTAU} ${OUTDIR}
     nohup nice -n 10 ./runLooper ${INDIR} T1qqqq_ctau-${CTAU} ${OUTDIR} >& ${LOGDIR}/log_T1qqqq_ctau-${CTAU}.txt &
done

INDIR=/nfs-6/userdata/mt2/V00-08-18_mc_skim_base_mt2gt200_ZinvV6_JECs/
echo nice -n 10 ./runLooper ${INDIR} T1qqqq ${OUTDIR}
nohup nice -n 10./runLooper ${INDIR} T1qqqq ${OUTDIR} >& ${LOGDIR}/log_T1qqqq.txt &
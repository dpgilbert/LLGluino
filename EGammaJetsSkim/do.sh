#!/bin/bash

declare -a RUNS=(data_Run2016B data_Run2016C data_Run2016D data_Run2016E data_Run2016F data_Run2016G data_Run2016H) 
#declare -a DATASETS=(DoubleEG DoubleMuon HTMHT JetHT MET MuonEG SingleElectron SingleMuon SinglePhoton)
declare -a DATASETS=(JetHT)

INDIR=/nfs-6/userdata/dpgilber/CMS3_Nebraska
OUTDIR=output/

mkdir -p ${OUTDIR}

for RUN in ${RUNS[@]}; do
    for DATASET in ${DATASETS[@]}; do
	SAMPLE=${RUN}_${DATASET}
	eval 'nohup nice -n 10 ./EGammaJetsSkim.exe ${INDIR} ${SAMPLE} ${OUTDIR} >& logs/${SAMPLE}_log.txt &'
    done
done


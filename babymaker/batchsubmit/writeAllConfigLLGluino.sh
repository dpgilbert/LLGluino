#!/bin/bash

#
# LLGluino CMS3 Samples
#

TAG="LLGluino"

#
# DATA
#

PREFIX="/hadoop/cms/store/user/dpgilber/AutoTwopler/"

./writeConfig.sh ${PREFIX}SMS-T1qqqq_ctau-0p001_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_SMS-T1qqqq_ctau-0p001_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_Gri/171006_211925/0000/merged ${TAG}_0p001
./writeConfig.sh ${PREFIX}SMS-T1qqqq_ctau-0p01_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_SMS-T1qqqq_ctau-0p01_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_Grid/171006_212041/0000/merged ${TAG}_0p01
./writeConfig.sh ${PREFIX}SMS-T1qqqq_ctau-0p1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_SMS-T1qqqq_ctau-0p1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_Gridp/171006_212154/0000/merged ${TAG}_0p1
./writeConfig.sh ${PREFIX}SMS-T1qqqq_ctau-1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_SMS-T1qqqq_ctau-1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_Gridpac/171006_212820/0000/merged ${TAG}_1
./writeConfig.sh ${PREFIX}SMS-T1qqqq_ctau-10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_SMS-T1qqqq_ctau-10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_Gridpa/171006_212719/0000/merged ${TAG}_10
./writeConfig.sh ${PREFIX}SMS-T1qqqq_ctau-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_SMS-T1qqqq_ctau-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_Gridp/171006_212616/0000/merged ${TAG}_100
./writeConfig.sh ${PREFIX}SMS-T1qqqq_ctau-1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_SMS-T1qqqq_ctau-1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_Grid/171006_212512/0000/merged ${TAG}_1000
./writeConfig.sh ${PREFIX}SMS-T1qqqq_ctau-10000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_SMS-T1qqqq_ctau-10000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_Gri/171006_212407/0000/merged ${TAG}_10000
./writeConfig.sh ${PREFIX}SMS-T1qqqq_ctau-100000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_SMS-T1qqqq_ctau-100000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_Gr/171006_212256/0000/merged ${TAG}_100000
./writeConfig.sh ${PREFIX}SMS-T1qqqq_ctau-1e18_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_SMS-T1qqqq_ctau-1e18_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_Grid/171006_212920/0000/merged ${TAG}_1e18

# --- write submit script ---
mkdir -p configs_${TAG}

mv condor_${TAG}*.cmd configs_${TAG}
echo "#!/bin/bash" > submitAll.sh
echo "voms-proxy-init -voms cms -valid 240:00" >> submitAll.sh
for file in configs_${TAG}/*.cmd
do 
    echo "condor_submit ${file}" >> submitAll.sh
done
chmod +x submitAll.sh
echo "[writeAllConfig] wrote submit script submitAll.sh"

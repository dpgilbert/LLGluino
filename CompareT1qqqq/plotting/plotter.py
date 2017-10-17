import pyRootPlotMaker as ppm
import ROOT
import sys

ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(False)

name0p001_200="../output/0p001_1400_200.root"
name0p001_800="../output/0p001_1400_800.root"
name0p001_1200="../output/0p001_1400_1200.root"

name10_200="../output/10_1400_200.root"
name10_800="../output/10_1400_800.root"
name10_1200="../output/10_1400_1200.root"

name1e18_200="../output/1e18_1400_200.root"
name1e18_800="../output/1e18_1400_800.root"
name1e18_1200="../output/1e18_1400_1200.root"

nameT1qqqq_200="../output/T1qqqq_1400_200.root"
nameT1qqqq_800="../output/T1qqqq_1400_800.root"
nameT1qqqq_1200="../output/T1qqqq_1400_1200.root"

f0p001_200 = ROOT.TFile(name0p001_200)
f0p001_800 = ROOT.TFile(name0p001_800)
f0p001_1200 = ROOT.TFile(name0p001_1200)

f10_200 = ROOT.TFile(name10_200)
f10_800 = ROOT.TFile(name10_800)
f10_1200 = ROOT.TFile(name10_1200)

f1e18_200 = ROOT.TFile(name1e18_200)
f1e18_800 = ROOT.TFile(name1e18_800)
f1e18_1200 = ROOT.TFile(name1e18_1200)

fT1qqqq_200 = ROOT.TFile(nameT1qqqq_200)
fT1qqqq_800 = ROOT.TFile(nameT1qqqq_800)
fT1qqqq_1200 = ROOT.TFile(nameT1qqqq_1200)

hists=["h_mt2","h_ht","h_nj","h_nb","h_met","h_j1pt","h_lep","h_diff","h_dphi"]

for hist in hists:

    h0p001_200 = f0p001_200.Get(hist)
    h0p001_800 = f0p001_800.Get(hist)
    h0p001_1200 = f0p001_1200.Get(hist)

    h10_200 = f10_200.Get(hist)
    h10_800 = f10_800.Get(hist)
    h10_1200 = f10_1200.Get(hist)

    h1e18_200 = f1e18_200.Get(hist)
    h1e18_800 = f1e18_800.Get(hist)
    h1e18_1200 = f1e18_1200.Get(hist)

    hT1qqqq_200 = fT1qqqq_200.Get(hist)
    hT1qqqq_800 = fT1qqqq_800.Get(hist)
    hT1qqqq_1200 = fT1qqqq_1200.Get(hist)

    h_T1qqqq_vec_200 = [hT1qqqq_200]
    h_T1qqqq_vec_800 = [hT1qqqq_800]
    h_T1qqqq_vec_1200 = [hT1qqqq_1200]
    h_T1qqqq_name = ["T1qqqq (standard)"]

    jet = "All-hadronic, 2+ Jets"

    if hist.find("h_mt2") != -1:
        xtitle="M_{T2}"
        xunit="GeV"
        log=True
    elif hist.find("h_met") != -1:
        xtitle="H_{T}"
        xunit="GeV"
        log=True
    elif hist.find("h_ht") != -1:
        xtitle="H_{T}"
        xunit="GeV"
        log=True
    elif hist.find("h_nb") != -1:
        xtitle="N_{Tag}"
        xunit=None
        log=False
    elif hist.find("h_nj") != -1:
        xtitle="N_{Jet}"
        xunit=None
        log=False
    elif hist.find("h_j1pt") != -1:
        xtitle="p_{T}^{Jet 1}"
        xunit="GeV"
        log=True
        jet="All-hadronic, 1 Jet"

    desc = "M_{glu} = 1400 GeV, M_{LSP} = 200 GeV"
    subtitles = [desc,jet]
    outputFile = "PNGs/0p001_200_"+hist+".png"
    ppm.plotDataMC(h_T1qqqq_vec_200,h_T1qqqq_name,h0p001_200,dataTitle="T1qqqq (ctau = 0.001 cm)",isLog = log,ratioTitle="LL / Std", subtitles=subtitles, 
                           xAxisTitle=xtitle, xAxisUnit=xunit, markerSize=1.1,energy=13,saveAs=outputFile)

    desc = "M_{glu} = 1400 GeV, M_{LSP} = 800 GeV"
    subtitles = [desc,jet]
    outputFile = "PNGs/0p001_800_"+hist+".png"
    ppm.plotDataMC(h_T1qqqq_vec_800,h_T1qqqq_name,h0p001_800,dataTitle="T1qqqq (ctau = 0.001 cm)",isLog = log,ratioTitle="LL / Std", subtitles=subtitles, 
                           xAxisTitle=xtitle, xAxisUnit=xunit, markerSize=1.1,energy=13,saveAs=outputFile)

    desc = "M_{glu} = 1400 GeV, M_{LSP} = 1200 GeV"
    subtitles = [desc,jet]
    outputFile = "PNGs/0p001_1200_"+hist+".png"
    ppm.plotDataMC(h_T1qqqq_vec_1200,h_T1qqqq_name,h0p001_1200,dataTitle="T1qqqq (ctau = 0.001 cm)",isLog = log,ratioTitle="LL / Std", subtitles=subtitles, 
                           xAxisTitle=xtitle, xAxisUnit=xunit, markerSize=1.1,energy=13,saveAs=outputFile)


    desc = "M_{glu} = 1400 GeV, M_{LSP} = 200 GeV"
    subtitles = [desc,jet]
    outputFile = "PNGs/10_200_"+hist+".png"
    ppm.plotDataMC(h_T1qqqq_vec_200,h_T1qqqq_name,h10_200,dataTitle="T1qqqq (ctau = 10 cm)",isLog = log,ratioTitle="LL / Std", subtitles=subtitles, 
                           xAxisTitle=xtitle, xAxisUnit=xunit, markerSize=1.1,energy=13,saveAs=outputFile)

    desc = "M_{glu} = 1400 GeV, M_{LSP} = 800 GeV"
    subtitles = [desc,jet]
    outputFile = "PNGs/10_800_"+hist+".png"
    ppm.plotDataMC(h_T1qqqq_vec_800,h_T1qqqq_name,h10_800,dataTitle="T1qqqq (ctau = 10 cm)",isLog = log,ratioTitle="LL / Std", subtitles=subtitles, 
                           xAxisTitle=xtitle, xAxisUnit=xunit, markerSize=1.1,energy=13,saveAs=outputFile)

    desc = "M_{glu} = 1400 GeV, M_{LSP} = 1200 GeV"
    subtitles = [desc,jet]
    outputFile = "PNGs/10_1200_"+hist+".png"
    ppm.plotDataMC(h_T1qqqq_vec_1200,h_T1qqqq_name,h10_1200,dataTitle="T1qqqq (ctau = 10 cm)",isLog = log,ratioTitle="LL / Std", subtitles=subtitles, 
                           xAxisTitle=xtitle, xAxisUnit=xunit, markerSize=1.1,energy=13,saveAs=outputFile)


    desc = "M_{glu} = 1400 GeV, M_{LSP} = 200 GeV"
    subtitles = [desc,jet]
    outputFile = "PNGs/1e18_200_"+hist+".png"
    ppm.plotDataMC(h_T1qqqq_vec_200,h_T1qqqq_name,h1e18_200,dataTitle="T1qqqq (ctau = 10^{18} cm)",isLog = log,ratioTitle="LL / Std", subtitles=subtitles, 
                           xAxisTitle=xtitle, xAxisUnit=xunit, markerSize=1.1,energy=13,saveAs=outputFile)

    desc = "M_{glu} = 1400 GeV, M_{LSP} = 800 GeV"
    subtitles = [desc,jet]
    outputFile = "PNGs/1e18_800_"+hist+".png"
    ppm.plotDataMC(h_T1qqqq_vec_800,h_T1qqqq_name,h1e18_800,dataTitle="T1qqqq (ctau = 10^{18} cm)",isLog = log,ratioTitle="LL / Std", subtitles=subtitles, 
                           xAxisTitle=xtitle, xAxisUnit=xunit, markerSize=1.1,energy=13,saveAs=outputFile)

    desc = "M_{glu} = 1400 GeV, M_{LSP} = 1200 GeV"
    subtitles = [desc,jet]
    outputFile = "PNGs/1e18_1200_"+hist+".png"
    ppm.plotDataMC(h_T1qqqq_vec_1200,h_T1qqqq_name,h1e18_1200,dataTitle="T1qqqq (ctau = 10^{18} cm)",isLog = log,ratioTitle="LL / Std", subtitles=subtitles, 
                           xAxisTitle=xtitle, xAxisUnit=xunit, markerSize=1.1,energy=13,saveAs=outputFile)


import ROOT
import ppmUtils as utils

ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(False)

def SavePlot (tcanvas, name="plot", extensions=["png","pdf"]):
    utils.DrawCmsText(canvas,text="CMS Preliminary",textFont=62,textSize=0.035)
    utils.DrawLumiText(canvas)
    for extension in extensions:
        tcanvas.SaveAs(extension+"s/"+name+"."+extension)

def GetHist (tfile, name, overflow = True, title=None, color=None):
    hist = tfile.Get(name)
    #hist.SetMarkerStyle(20)
    #hist.SetMarkerSize(0.9)
    hist.SetLineWidth(3)
    if overflow:
        utils.PutOverflowInLastBin(hist)
        err0 = hist.GetBinError(0)
        err1 = hist.GetBinError(1)
        hist.SetBinContent(0,hist.GetBinContent(0)+hist.GetBinContent(1))
        hist.SetBinError(0,ROOT.TMath.Sqrt(err0**2 + err1**2))
    if title != None:
        hist.SetTitle(title)
    if color != None:
        hist.SetLineColor(color)
    hist.SetTitleOffset(1.6, "y")
    return hist

def HistMax (histlist):
    maxval = 0.0
    for hist in histlist:
        if hist.GetMaximum() > maxval:
            maxval = hist.GetMaximum()
    return maxval / 0.8

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

hists=["h_mt2","h_ht","h_nj","h_nb","h_met","h_j1pt","h_lep","h_diff","h_dphi","h_j1eta","h_j1etapt","h_mht","h_metmht"]

canvas = ROOT.TCanvas()
canvas.SetCanvasSize(700,700)
canvas.SetTicks(1,2)
pads = [canvas]
pads[0].SetLeftMargin(0.12)
pads[0].SetTopMargin(0.12)
pads[0].SetRightMargin(0.12)
pads[0].cd()

ROOT.gStyle.SetLegendBorderSize(0) # borderless legend
tl = ROOT.TLegend(0.55,0.70,0.80,0.85)
tl.SetMargin(0.1)

for hist in hists:

    h0p001_200 = GetHist(f0p001_200,hist,title="c#tau = 0.001 cm, m_{LSP} = 200 GeV",color=ROOT.kRed)
    h0p001_800 = GetHist(f0p001_800,hist,title="c#tau = 0.001 cm, m_{LSP} = 800 GeV",color=ROOT.kRed)
    h0p001_1200 = GetHist(f0p001_1200,hist,title="c#tau=0.001 cm, m_{LSP} = 1200 GeV",color=ROOT.kRed)

    h10_200 = GetHist(f10_200,hist,title="c#tau = 10 cm, m_{LSP} = 200 GeV",color=ROOT.kBlue)
    h10_800 = GetHist(f10_800,hist,title="c#tau = 10 cm, m_{LSP} = 800 GeV",color=ROOT.kBlue)
    h10_1200 = GetHist(f10_1200,hist,title="c#tau=10 cm, m_{LSP} = 1200 GeV",color=ROOT.kBlue)

    h1e18_200 = GetHist(f1e18_200,hist,title="c#tau = 10^{18} cm, m_{LSP} = 200 GeV",color=ROOT.kGreen)
    h1e18_800 = GetHist(f1e18_800,hist,title="c#tau = 10^{18} cm, m_{LSP} = 800 GeV",color=ROOT.kGreen)
    h1e18_1200 = GetHist(f1e18_1200,hist,title="c#tau=10^{18} cm, m_{LSP} = 1200 GeV",color=ROOT.kGreen)

    hT1qqqq_200 = GetHist(fT1qqqq_200,hist,title="Standard, m_{LSP} = 200 GeV",color=ROOT.kBlack)
    hT1qqqq_800 = GetHist(fT1qqqq_800,hist,title="Standard, m_{LSP} = 800 GeV",color=ROOT.kBlack)
    hT1qqqq_1200 = GetHist(fT1qqqq_1200,hist,title="Standard, m_{LSP} = 1200 GeV",color=ROOT.kBlack)

    if hist.find("h_mt2") != -1:
        varname="M_{T2}"
        xunit="GeV"
        canvas.SetLogy(True)
    elif hist.find("h_metmht") != -1:
        print("got in")
        varname="MHT-MET"
        xunit="GeV"
        canvas.SetLogy(True)
    elif hist.find("h_met") != -1:
        varname="MET"
        xunit="GeV"
        canvas.SetLogy(True)
    elif hist.find("h_ht") != -1:
        varname="H_{T}"
        xunit="GeV"
        canvas.SetLogy(True)
    elif hist.find("h_nb") != -1:
        varname="N_{Tag}"
        xunit=None
        canvas.SetLogy(False)
    elif hist.find("h_nj") != -1:
        varname="N_{Jet}"
        xunit=None
        canvas.SetLogy(False)
    elif hist.find("h_j1pt") != -1:
        varname="p_{T}^{Jet 1}"
        xunit="GeV"
        canvas.SetLogy(True)
    elif hist.find("h_lep") != -1:
        varname="Lepton Veto Index"
        xunit=None
        canvas.SetLogy(False)
    elif hist.find("h_diff") != -1:
        varname="|MET-MHT|/MET"
        xunit=None
        canvas.SetLogy(False)
    elif hist.find("h_dphi") != -1:
        varname="#Delta#Phi_{Min}"
        xunit=None
        canvas.SetLogy(False)
    elif hist.find("h_j1eta") != -1:
        varname="#eta_{Jet 1} (Inclusive)"
        xunit="GeV"
        canvas.SetLogy(True)
    elif hist.find("h_j1etapt") != -1:
        varname="#eta_{Jet 1} (p_{T} > 30 GeV)"
        xunit="GeV"
        canvas.SetLogy(True)
    elif hist.find("h_mht") != -1:
        varname="MHT"
        xunit="GeV"
        canvas.SetLogy(True)

    if xunit == None:
        xtitle = varname
    else:
        xtitle= varname+" [{0}]".format(xunit)

    h0p001_200.SetTitle(varname+" (m_{LSP} = 200 GeV);"+xtitle+";Count / fb")
    h0p001_200.SetMaximum(HistMax([h0p001_200,h10_200,h1e18_200,hT1qqqq_200]))
    h0p001_800.SetTitle(varname+" (m_{LSP} = 800 GeV);"+xtitle+";Count / fb")
    h0p001_800.SetMaximum(HistMax([h0p001_800,h10_800,h1e18_800,hT1qqqq_800]))
    h0p001_1200.SetTitle(varname+" (m_{LSP} = 1200 GeV);"+xtitle+";Count / fb")
    h0p001_1200.SetMaximum(HistMax([h0p001_1200,h10_1200,h1e18_1200,hT1qqqq_1200]))

    tl.Clear()
    h0p001_200.Draw()
    h10_200.Draw("same")
    h1e18_200.Draw("same")
    hT1qqqq_200.Draw("same")
    tl.AddEntry(h0p001_200,"c#tau=0.001 cm")
    tl.AddEntry(h10_200,"c#tau=10 cm")
    tl.AddEntry(h1e18_200,"c#tau=10^{18} cm")
    tl.AddEntry(hT1qqqq_200,"Standard")
    tl.Draw()
    SavePlot(canvas,hist+"_200")

    tl.Clear()
    h0p001_800.Draw()
    h10_800.Draw("same")
    h1e18_800.Draw("same")
    hT1qqqq_800.Draw("same")
    tl.AddEntry(h0p001_800,"c#tau=0.001 cm")
    tl.AddEntry(h10_800,"c#tau=10 cm")
    tl.AddEntry(h1e18_800,"c#tau=10^{18} cm")
    tl.AddEntry(hT1qqqq_800,"Standard")
    tl.Draw()
    SavePlot(canvas,hist+"_800")

    tl.Clear()
    h0p001_1200.Draw()
    h10_1200.Draw("same")
    h1e18_1200.Draw("same")
    hT1qqqq_1200.Draw("same")
    tl.AddEntry(h0p001_1200,"c#tau=0.001 cm")
    tl.AddEntry(h10_1200,"c#tau=10 cm")
    tl.AddEntry(h1e18_1200,"c#tau=10^{18} cm")
    tl.AddEntry(hT1qqqq_1200,"Standard")
    tl.Draw()
    SavePlot(canvas,hist+"_1200")

    h0p001_200.Divide(hT1qqqq_200)
    h0p001_800.Divide(hT1qqqq_800)
    h0p001_1200.Divide(hT1qqqq_1200)

    h10_200.Divide(hT1qqqq_200)
    h10_800.Divide(hT1qqqq_800)
    h10_1200.Divide(hT1qqqq_1200)

    h1e18_200.Divide(hT1qqqq_200)
    h1e18_800.Divide(hT1qqqq_800)
    h1e18_1200.Divide(hT1qqqq_1200)

    canvas.SetLogy(False)

    h0p001_200.SetTitle(varname+" (m_{LSP} = 200 GeV);"+xtitle+";Ratio with Standard");
    h0p001_200.SetMinimum(0.0)
    h0p001_200.SetMaximum(2.0)
    h0p001_800.SetTitle(varname+" (m_{LSP} = 800 GeV);"+xtitle+";Ratio with Standard");
    h0p001_800.SetMinimum(0.0)
    h0p001_800.SetMaximum(2.0)
    h0p001_1200.SetTitle(varname+" (m_{LSP} = 1200 GeV);"+xtitle+";Ratio with Standard");
    h0p001_1200.SetMinimum(0.0)
    h0p001_1200.SetMaximum(2.0)

    tl.Clear()
    h0p001_200.Draw()
    h10_200.Draw("same")
    h1e18_200.Draw("same")
    tl.AddEntry(h0p001_200,"c#tau=0.001 cm")
    tl.AddEntry(h10_200,"c#tau=10 cm")
    tl.AddEntry(h1e18_200,"c#tau=10^{18} cm")
    tl.Draw()
    SavePlot(canvas,hist+"_200r")

    tl.Clear()
    h0p001_800.Draw()
    h10_800.Draw("same")
    h1e18_800.Draw("same")
    tl.AddEntry(h0p001_800,"c#tau=0.001 cm")
    tl.AddEntry(h10_800,"c#tau=10 cm")
    tl.AddEntry(h1e18_800,"c#tau=10^{18} cm")
    tl.Draw()
    SavePlot(canvas,hist+"_800r")

    tl.Clear()
    h0p001_1200.Draw()
    h10_1200.Draw("same")
    h1e18_1200.Draw("same")
    tl.AddEntry(h0p001_1200,"c#tau=0.001 cm")
    tl.AddEntry(h10_1200,"c#tau=10 cm")
    tl.AddEntry(h1e18_1200,"c#tau=10^{18} cm")
    tl.Draw()
    SavePlot(canvas,hist+"_1200r")

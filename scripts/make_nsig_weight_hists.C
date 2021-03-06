#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TString.h"

void make_nsig_weight_hists(TString dir, TString sample) {

  TChain* t = new TChain("mt2");
  t->Add(Form("%s/%s*.root",dir.Data(),sample.Data()));

  TFile* fout = new TFile(Form("nsig_weights_%s.root",sample.Data()),"RECREATE");

  // default: 25 GeV binning, m1 from 0-2500, m2 from 0-2100
  int x_nbins = 101;
  float x_min = -12.5;
  float x_max = 2512.5;
  int y_nbins = 85;
  float y_min = -12.5;
  float y_max = 2112.5;

  // for T2cc: 25 GeV in x, 5 GeV in y binning, m1 from 0-2000, m2 from 0-1000
  if (sample.Contains("T2cc")) {
    y_nbins = 201;
    y_min = -5.;
    y_max = 1005.;
  }
  
  TH2D* h_nsig = new TH2D("h_nsig",";mass1 [GeV];mass2 [GeV]", x_nbins, x_min, x_max, y_nbins, y_min, y_max);
  TH2D* h_avg_weight_btagsf = (TH2D*) h_nsig->Clone("h_avg_weight_btagsf");
  TH2D* h_avg_weight_btagsf_heavy_UP = (TH2D*) h_nsig->Clone("h_avg_weight_btagsf_heavy_UP");
  TH2D* h_avg_weight_btagsf_light_UP = (TH2D*) h_nsig->Clone("h_avg_weight_btagsf_light_UP");
  TH2D* h_avg_weight_btagsf_heavy_DN = (TH2D*) h_nsig->Clone("h_avg_weight_btagsf_heavy_DN");
  TH2D* h_avg_weight_btagsf_light_DN = (TH2D*) h_nsig->Clone("h_avg_weight_btagsf_light_DN");
  TH2D* h_avg_weight_isr = (TH2D*) h_nsig->Clone("h_avg_weight_isr");
  TH2D* h_avg_weight_isr_UP = (TH2D*) h_nsig->Clone("h_avg_weight_isr_UP");
  TH2D* h_avg_weight_isr_DN = (TH2D*) h_nsig->Clone("h_avg_weight_isr_DN");

  t->Draw("GenSusyMScan2:GenSusyMScan1>>h_nsig");
  t->Draw("GenSusyMScan2:GenSusyMScan1>>h_avg_weight_btagsf","(met_pt > -1.)*weight_btagsf" );
  t->Draw("GenSusyMScan2:GenSusyMScan1>>h_avg_weight_btagsf_heavy_UP","(met_pt > -1.)*weight_btagsf_heavy_UP" );
  t->Draw("GenSusyMScan2:GenSusyMScan1>>h_avg_weight_btagsf_light_UP","(met_pt > -1.)*weight_btagsf_light_UP" );
  t->Draw("GenSusyMScan2:GenSusyMScan1>>h_avg_weight_btagsf_heavy_DN","(met_pt > -1.)*weight_btagsf_heavy_DN" );
  t->Draw("GenSusyMScan2:GenSusyMScan1>>h_avg_weight_btagsf_light_DN","(met_pt > -1.)*weight_btagsf_light_DN" );
  t->Draw("GenSusyMScan2:GenSusyMScan1>>h_avg_weight_isr","(met_pt > -1.)*weight_isr" );
  t->Draw("GenSusyMScan2:GenSusyMScan1>>h_avg_weight_isr_UP","(met_pt > -1.)*weight_isr_UP" );
  t->Draw("GenSusyMScan2:GenSusyMScan1>>h_avg_weight_isr_DN","(met_pt > -1.)*weight_isr_DN" );

  h_avg_weight_btagsf->Divide(h_nsig);
  h_avg_weight_btagsf_heavy_UP->Divide(h_nsig);
  h_avg_weight_btagsf_light_UP->Divide(h_nsig);
  h_avg_weight_btagsf_heavy_DN->Divide(h_nsig);
  h_avg_weight_btagsf_light_DN->Divide(h_nsig);
  h_avg_weight_isr->Divide(h_nsig);
  h_avg_weight_isr_UP->Divide(h_nsig);
  h_avg_weight_isr_DN->Divide(h_nsig);
  
  fout->Write();
  fout->Close();

}

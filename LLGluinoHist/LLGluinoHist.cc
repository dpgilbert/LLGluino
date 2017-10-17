#include "LLGluinoHist.h"

using namespace std;
using namespace mt2;
using namespace duplicate_removal;

void LLGluinoHist::loop (const TChain * chain, const char* sample, const char* outdir, const int maxEvt) {
  TString outname = Form("%s/nsig_weights_T1qqqq_ctau-%s.root",outdir,sample);
  TFile * outfile = new TFile(outname.Data(), "RECREATE");

  //  const char* lumi17 = "11.379";

  TH1::SetDefaultSumw2(true);

  // bins have width 25, +/- 12 of the same central value map to a bin
  //  nbinsx,xmin,xmax,nbinxy,ymin,ymax => nbinsGLU,GLUmin,GLUmax,nbinsLSP,LSPmin,LSPmax
  TH2D h_nsig("h_nsig","",100,13,2513,100,13,2513);
  TTree * tree = (TTree*)chain->Clone("mt2");
  mt2tree mt2_tree;
  mt2_tree.Init(tree);

  int available = tree->GetEntries();
  int max_event = maxEvt < 0 ? available : min(maxEvt, available);
  
  cout << "Running on " << max_event << " events." << endl;
  cout << "Tree contains " << available << " events." << endl;

  outfile->cd();

  for (int event = 0; event < max_event; event++) {
    mt2_tree.GetEntry(event);

    h_nsig.Fill(mt2_tree.GenSusyMScan1,mt2_tree.GenSusyMScan2);

  } // Event Loop

  cout << "Finished event loop." << endl;

  h_nsig.Write();

  // Just copy T1qqqq hists for others
  TFile* T1qqqq_file = new TFile("../babymaker/data/nsig_weights_T1qqqq.root"); // Read-only by default
  T1qqqq_file->cd();
  TH2D* h_avg_weight_btagsf = (TH2D*)T1qqqq_file->Get("h_avg_weight_btagsf");
  TH2D* h_avg_weight_btagsf_heavy_UP = (TH2D*)T1qqqq_file->Get("h_avg_weight_btagsf_heavy_UP");
  TH2D* h_avg_weight_btagsf_heavy_DN = (TH2D*)T1qqqq_file->Get("h_avg_weight_btagsf_heavy_DN");
  TH2D* h_avg_weight_btagsf_light_UP = (TH2D*)T1qqqq_file->Get("h_avg_weight_btagsf_light_UP");
  TH2D* h_avg_weight_btagsf_light_DN = (TH2D*)T1qqqq_file->Get("h_avg_weight_btagsf_light_DN");
  TH2D* h_avg_weight_isr = (TH2D*)T1qqqq_file->Get("h_avg_weight_isr");
  TH2D* h_avg_weight_isr_UP = (TH2D*)T1qqqq_file->Get("h_avg_weight_isr_UP");
  TH2D* h_avg_weight_isr_DN = (TH2D*)T1qqqq_file->Get("h_avg_weight_isr_DN");

  outfile->cd();
  h_avg_weight_btagsf->Write();
  h_avg_weight_btagsf_heavy_UP->Write();
  h_avg_weight_btagsf_heavy_DN->Write();
  h_avg_weight_btagsf_light_UP->Write();
  h_avg_weight_btagsf_light_DN->Write();
  h_avg_weight_isr->Write();
  h_avg_weight_isr_UP->Write();
  h_avg_weight_isr_DN->Write();
  T1qqqq_file->Close();
  outfile->Close();

} // loop function


int main (int argc, char ** argv) {
  int maxEvt = -1;
  if (argc > 4) maxEvt = atoi(argv[4]);

  TChain* ch = new TChain("mt2");
  
  TString infile_name = Form("%s/*%s.root", argv[1], argv[2]);
  ch->Add(infile_name);

  LLGluinoHist * l = new LLGluinoHist();
  l->loop(ch, argv[2], argv[3], maxEvt);
  return 0;
}

LLGluinoHist::LLGluinoHist() {}

LLGluinoHist::~LLGluinoHist() {};

#include "CompareT1qqqq.h"

using namespace std;
using namespace mt2;
using namespace duplicate_removal;

void CompareT1qqqq::loop (const TChain * chain, const char* sample, const char* outdir, const int maxEvt) {
  TString outname = Form("%s/%s.root",outdir,sample);
  TFile * outfile = new TFile(outname.Data(), "RECREATE");

  //  const char* lumi17 = "11.379";

  TH1::SetDefaultSumw2(true);

  TH1F h_ht("h_ht","H_{T}",50,0,3000);
  TH1F h_nj("h_nj","N_{Jet}",12,0,12);
  TH1F h_nb("h_nb","N_{Tag}",4,0,4);
  TH1F h_met("h_met","MET",30,0,1500);
  TH1F h_mt2("h_mt2","M_{T2}",30,0,1500);
  TH1F h_j1pt("h_j1pt","p_{T}^{Jet 1}",30,0,1500);
  TH1F h_diff("h_diff","|MET-MHT|/MET",10,0,1);
  TH1F h_dphi("h_dphi","#Delta#Phi_{Min}",31,0,3.1);
  TH1F h_lep("h_lep","Lepton Veto Index",2,0,2);
  TH1F h_mht("h_mht","MHT",30,0,1500);
  TH1F h_metmht("h_metmht","MET-MHT",20,-40,40);
  TH1F h_j1eta("h_j1eta","#eta_{Jet 1} (Inclusive)",20,0,5);
  TH1F h_j1etapt("h_j1etapt","#eta_{Jet 1} (p_{T} > 30 GeV)",20,0,5);
  TTree * tree = (TTree*)chain->Clone("mt2");
  mt2tree mt2_tree;
  mt2_tree.Init(tree);

  int available = tree->GetEntries();
  int max_event = maxEvt < 0 ? available : min(maxEvt, available);
  
  cout << "Running on " << max_event << " events." << endl;
  cout << "Tree contains " << available << " events." << endl;

  outfile->cd();

  for (int event = 0; event < max_event; event++) {
    if ( (event+1) % 100000 == 0) cout << "Processing event " << event+1 << ", " << (100. * event) / max_event << "% complete" << endl;

    mt2_tree.GetEntry(event);

    if (mt2_tree.nVert == 0) continue;
    
    /*
    // Filters
    if (!mt2_tree.Flag_globalSuperTightHalo2016Filter) continue; 
    // if (!mt2_tree.Flag_badMuonFilterV2) continue;
    if (!mt2_tree.Flag_eeBadScFilter) continue; 

    if (!mt2_tree.Flag_goodVertices) continue;
    if (!mt2_tree.Flag_HBHENoiseFilter) continue;
    if (!mt2_tree.Flag_HBHENoiseIsoFilter) continue;
    if (!mt2_tree.Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
    // if (!mt2_tree.Flag_badChargedHadronFilterV2) continue; 
    */

    const float ht_ = mt2_tree.ht;

    if (isinf(ht_) || isnan(ht_)) continue;
    if (mt2_tree.jet_pt[0] > 13000.) continue;

    if (mt2_tree.met_miniaodPt / mt2_tree.met_caloPt > 5 || mt2_tree.nJet200MuFrac50DphiMet > 0) continue;

    const float w = 1000 * mt2_tree.evt_xsec / available;

    h_ht.Fill(ht_,w);
    h_nj.Fill(mt2_tree.nJet30,w);
    h_nb.Fill(mt2_tree.nBJet20,w);
    h_met.Fill(mt2_tree.met_pt,w);
    if (mt2_tree.nJet30 == 1) h_j1pt.Fill(mt2_tree.jet1_pt,w);
    else if (mt2_tree.nJet30 > 1) h_mt2.Fill(mt2_tree.mt2,w);
    h_lep.Fill((mt2_tree.nElectrons10 + mt2_tree.nMuons10 + mt2_tree.nPFLep5LowMT + mt2_tree.nPFHad10LowMT),w);
    h_diff.Fill(mt2_tree.diffMetMht / mt2_tree.met_pt,w);
    h_dphi.Fill(mt2_tree.deltaPhiMin,w);
    h_mht.Fill(mt2_tree.mht_pt,w);
    h_metmht.Fill(mt2_tree.mht_pt - mt2_tree.met_pt,w);
    h_j1eta.Fill(mt2_tree.jet_eta[0],w);
    if (mt2_tree.jet_pt[0] > 30) h_j1etapt.Fill(mt2_tree.jet_eta[0],w);

  } // Event Loop

  cout << "Finished event loop." << endl;

  h_ht.Write();
  h_nj.Write();
  h_nb.Write();
  h_met.Write();
  h_j1pt.Write();
  h_mt2.Write();
  h_dphi.Write();
  h_diff.Write();
  h_lep.Write();
  h_mht.Write();
  h_metmht.Write();
  h_j1eta.Write();
  h_j1etapt.Write();

  outfile->Close();

} // loop function


int main (int argc, char ** argv) {
  int maxEvt = -1;
  if (argc > 4) maxEvt = atoi(argv[4]);

  TChain* ch = new TChain("mt2");
  
  TString infile_name = Form("%s/%s*.root", argv[1], argv[2]);
  ch->Add(infile_name);

  CompareT1qqqq * l = new CompareT1qqqq();
  l->loop(ch, argv[2], argv[3], maxEvt);
  return 0;
}

CompareT1qqqq::CompareT1qqqq() {}

CompareT1qqqq::~CompareT1qqqq() {};

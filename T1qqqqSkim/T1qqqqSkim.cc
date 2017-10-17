// A looper to skim MCs for low Dphi events

#include <iostream>

#include "../CORE/Tools/utils.h"

#include "../MT2CORE/mt2tree.h"

using namespace std;

int main (int argc, char ** argv)
{
  if (argc < 4)
    {
      cout << "Usage: ./T1qqqqSkim <input_directory> <sample> <output_directory>" << endl;
      return 0;
    }

  TChain* chain = new TChain("mt2");
  TString inputs = Form("%s/%s*.root", argv[1], argv[2]);
  chain->Add(inputs);

  const char* sample = argc == 5 ? argv[4] : argv[2];
  const char* outdir = argv[3];
  
  // Skim

  // first mass point
  TString output_name = Form("%s%s_1400_200.root", outdir, sample);
  TFile * outfile = TFile::Open( output_name , "RECREATE" );

  char* mglu = "GenSusyMScan1 == 1400";
  char* mlsp = "GenSusyMScan2 == 200";
  
  char * selection_string = Form("%s && %s", mglu, mlsp);

  TTree * skimmed = chain->CopyTree ( selection_string );
  skimmed->Write();
  outfile->Close();

  // second mass point
  output_name = Form("%s%s_1400_800.root", outdir, sample);
  outfile = TFile::Open( output_name , "RECREATE" );

  mglu = "GenSusyMScan1 == 1400";
  mlsp = "GenSusyMScan2 == 800";
  
  selection_string = Form("%s && %s", mglu, mlsp);
  
  skimmed = chain->CopyTree ( selection_string );
  skimmed->Write();
  outfile->Close();
  
  // third mass point
  output_name = Form("%s%s_1400_1200.root", outdir, sample);
  outfile = TFile::Open( output_name , "RECREATE" );
  
  mglu = "GenSusyMScan1 == 1400";
  mlsp = "GenSusyMScan2 == 1200";
  
  selection_string = Form("%s && %s", mglu, mlsp);
  
  skimmed = chain->CopyTree ( selection_string );
  skimmed->Write();
  outfile->Close();

  
}

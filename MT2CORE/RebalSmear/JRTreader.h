#ifndef JRTREADER
#define JRTREADER

#include <vector>

#include "TROOT.h"
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TH1D.h"

#define N_PT_BINS 23
#define N_ETA_BINS 12

using namespace std;

class JRTreader {
 public:
    
    JRTreader(char *fname=0);
    ~JRTreader();
    int Init(char *fname);
    float GetRandomResponse(float pt, float eta, bool isBjet, bool CorrectDataResolution=false);
    float GetValue(float pt, float eta, bool isBjet, float smearfact, bool correctDataResolution=false);
    static float GetJERCorrection(float eta);
    static int GetPtBin(float pt);
    static int GetEtaBin(float eta);
    static void GetModifiedBins(int ptbin, int etabin, bool isBjet, int *new_ptbin, int *new_etabin);
    void SetCoreScale(float);
    void SetTailScale(float);
    void SetMeanShift(float);
    void TransformFit(TH1D *fit, TH1D *core, TH1D *tail);
    void UseRawHistograms(bool use=true);
    void SetBinWidth(float width);
    void Draw(int,int);

 private:
    vector< vector<TH1D*>* > *fits_b;
    vector< vector<TH1D*>* > *fits_nonb;
    bool useFits = true;
    float BINWIDTH = 0.02;
    float coreScale = 1.0;
    float tailScale = 1.0;
    float meanShift = 0.0;
};

#endif

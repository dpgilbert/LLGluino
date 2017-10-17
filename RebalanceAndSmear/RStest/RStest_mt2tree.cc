#include <vector>
#include <iostream>
#include <algorithm>

#include <TROOT.h>
#include <TH1D.h>
#include <TFile.h>
#include <TChain.h>
#include <TSystem.h>
#include <TTreeCache.h>
#include <TString.h>
#include <TDirectory.h>

#include "RStest_mt2tree.h"

#define NSMEARS 100
#define EVTRED 20

using namespace std;

RStest::RStest(){}
RStest::~RStest(){}

void RStest::loop(TChain *chain, JRTrebalTree rebalTree, JRTreader reader, string output_name)
{

    // open output file and initialize histograms
    TFile *fout = new TFile(output_name.c_str(), "RECREATE");

    string tags[] = {"reco","gen","gensmear","rebalance","rebalsmear"};
    vector<TH1D*> h_nJet30_vec;
    vector<TH1D*> h_met_vec;
    vector<TH1D*> h_ht_vec;
    vector<TH1D*> h_mht_vec;
    vector<TH1D*> h_diffMetMhtOverMet_vec;
    vector<TH1D*> h_j1pt_vec;
    vector<TH1D*> h_j2pt_vec;
    vector<TH1D*> h_deltaPhiMin_vec;
    for(int i=0; i<5; i++){
        h_nJet30_vec.push_back(new TH1D(("h_nJet30_"+tags[i]).c_str(),";nJet30",10,0,10));
        h_met_vec.push_back(new TH1D(("h_met_"+tags[i]).c_str(),";E_{T}^{miss} [GeV]",150,0,1500));
        h_ht_vec.push_back(new TH1D(("h_ht_"+tags[i]).c_str(), ";H_{T} [GeV]",150,0,1500));
        h_mht_vec.push_back(new TH1D(("h_mht_"+tags[i]).c_str(), ";H_{T}^{miss} [GeV]",150,0,1500));
        h_diffMetMhtOverMet_vec.push_back(new TH1D(("h_diffMetMhtOverMet_"+tags[i]).c_str(), ";diffMetMhtOverMet",150,0,10));
        h_j1pt_vec.push_back(new TH1D(("h_j1pt_"+tags[i]).c_str(), ";p_{T}(jet1) [GeV]",150,0,1500));
        h_j2pt_vec.push_back(new TH1D(("h_j2pt_"+tags[i]).c_str(), ";p_{T}(jet2) [GeV]",150,0,1500));
        h_deltaPhiMin_vec.push_back(new TH1D(("h_deltaPhiMin_"+tags[i]).c_str(), ";deltaPhiMin",150,0,3.141593));
    }
    
    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = chain->GetEntries();
    TObjArray *listOfFiles = chain->GetListOfFiles();
    TIter fileIter(listOfFiles);
    TFile *currentFile = 0;

    cout << "Processing " << nEventsChain << " events." << endl;

    while ( (currentFile = (TFile*)fileIter.Next()) ) {
        
        cout << currentFile->GetTitle() << endl;
        // Get File Content
        TFile *file = new TFile( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("mt2");
        TTreeCache::SetLearnEntries(10);
        tree->SetCacheSize(128*1024*1024);
        t.Init(tree);

        // branch for scale1fb is not in JRTTree
        float scale;
        tree->SetBranchAddress("evt_scale1fb", &scale);
        
        int nBadEvents = 0;


        unsigned int nEventsTree = tree->GetEntriesFast();
        cout << " Events in tree: " << nEventsTree << endl;
        unsigned int maxEvents = nEventsTree;
        maxEvents = nEventsTree;
        for( unsigned int event = 0; event < maxEvents; ++event) {
    
            if(event%EVTRED != 0)
                continue;

            cout << event << endl;


            // Get Event Content
            Long64_t tentry = tree->LoadTree(event);
            t.GetEntry(tentry);

            cout << t.njet << endl;

            if(doRebalance)
                rebalTree.GetEntry(nEventsTotal);

            cout << "TEST!!" << endl;
            ++nEventsTotal;

            scale *= EVTRED;

            //ANALYSIS CODE HERE
            
            // variables to store the met after subtracting recojets.
            // used to recompute the met with the smeared jets
            float met_sub_x = t.met_pt * cos(t.met_phi);
            float met_sub_y = t.met_pt * sin(t.met_phi);
            
            float jetVars[7]; //will hold ht, mht, diffMetMht/met

            // subtract reco jets from met to recompute using smeared jets
            for(int ir=0; ir<t.njet; ir++){
                float pt = t.jet_pt[ir];
                float phi = t.jet_phi[ir];

                // subtract reco jets from met
                if(pt > 10){
                    met_sub_x += pt * cos(phi);
                    met_sub_y += pt * sin(phi);
                }
            }// recojet loop


            // COMPUTE RECOJET QUANTITIES
            computeJetVars("reco", t.met_pt, t.met_phi, jetVars);
            h_nJet30_vec.at(0)->Fill(jetVars[0], scale);
            if(jetVars[0] >= 2 && t.met_pt>metCut){
                h_met_vec.at(0)->Fill(t.met_pt, scale);
                h_ht_vec.at(0)->Fill(jetVars[1], scale);
                h_mht_vec.at(0)->Fill(jetVars[2], scale);
                h_diffMetMhtOverMet_vec.at(0)->Fill(jetVars[3], scale);
                h_j1pt_vec.at(0)->Fill(jetVars[4], scale);
                h_j2pt_vec.at(0)->Fill(jetVars[5], scale);
                h_deltaPhiMin_vec.at(0)->Fill(jetVars[6], scale);
            }

            cout << "TEST!!" << endl;
            // // COMPUTE GENJET QUANTITIES //
            if(t.nJet30>=2)
                h_met_vec.at(1)->Fill(t.met_genPt, scale);
            // computeJetVars("gen", t.genmet_pt, t.genmet_phi, jetVars);
            // h_nJet30_vec.at(1)->Fill(jetVars[0], scale);
            // if(jetVars[0] >= 2){
            //     h_met_vec.at(1)->Fill(t.genmet_pt, scale);
            //     h_ht_vec.at(1)->Fill(jetVars[1], scale);
            //     h_mht_vec.at(1)->Fill(jetVars[2], scale);
            //     h_diffMetMhtOverMet_vec.at(1)->Fill(jetVars[3], scale);
            //     h_j1pt_vec.at(1)->Fill(jetVars[4], scale);
            //     h_j2pt_vec.at(1)->Fill(jetVars[5], scale);
            //     h_deltaPhiMin_vec.at(1)->Fill(jetVars[6], scale);
            // }

            // // SMEAR JETS AND COMPUTE QUANTITIES
            // for(int ismear=0; ismear < NSMEARS; ismear++){
            //     smearjet_pt.clear();
            //     smearjet_eta.clear();
            //     smearjet_phi.clear();

            //     // weird corrupt babies causing crashes
            //     if(t.genjet_flavour_cmssw->size() != t.genjet_pt->size()){
            //         nBadEvents++;
            //         break;
            //     }

            //     for(int ig=0; ig<t.n_genjet; ig++){
            //         int flavour = t.genjet_flavour_cmssw->at(ig);

            //         //either a leptonic or unidentifiable jet
            //         if(flavour < 1){
            //             continue;
            //             // flavour = 1;
            //         }

            //         bool isBjet = 0;
            //         if(flavour==5)
            //             isBjet = 1;

            //         // get the smearing factor
            //         float smearfact = reader.GetRandomResponse(t.genjet_pt->at(ig), t.genjet_eta->at(ig), isBjet);
            //         float smearpt = t.genjet_pt->at(ig) * smearfact;
                    
            //         //add the smeared jet to the list
            //         smearjet_pt.push_back(smearpt);
            //         smearjet_eta.push_back(t.genjet_eta->at(ig));
            //         smearjet_phi.push_back(t.genjet_phi->at(ig));

            //     }//genjet loop

            //     //recompute met with smeared jets
            //     float met_smear_x = met_sub_x;
            //     float met_smear_y = met_sub_y;
            //     for(unsigned int ij=0; ij<smearjet_pt.size(); ij++){
            //         float pt = smearjet_pt.at(ij);
            //         float phi = smearjet_phi.at(ij);

            //         if(pt > 10){
            //             met_smear_x -= pt * cos(phi);
            //             met_smear_y -= pt * sin(phi);
            //         }
                    
            //     }// loop over smeared jets

                
            //     float met_smear = sqrt(met_smear_x*met_smear_x + met_smear_y*met_smear_y);
            //     float met_smear_phi = atan2(met_smear_y, met_smear_x);
            //     // COMPUTE SMEARJET QUANTITIES //
            //     computeJetVars("smear", met_smear, met_smear_phi, jetVars);
            //     h_nJet30_vec.at(2)->Fill(jetVars[0], scale/NSMEARS);
            //     if(jetVars[0] >= 2 && met_smear>metCut){
            //         h_met_vec.at(2)->Fill(met_smear, scale/NSMEARS);
            //         h_ht_vec.at(2)->Fill(jetVars[1], scale/NSMEARS);
            //         h_mht_vec.at(2)->Fill(jetVars[2], scale/NSMEARS);
            //         h_diffMetMhtOverMet_vec.at(2)->Fill(jetVars[3], scale/NSMEARS);
            //         h_j1pt_vec.at(2)->Fill(jetVars[4], scale/NSMEARS);
            //         h_j2pt_vec.at(2)->Fill(jetVars[5], scale/NSMEARS);
            //         h_deltaPhiMin_vec.at(2)->Fill(jetVars[6], scale/NSMEARS);
            //     }

            // }// smearing loop


            if(!doRebalance)
                continue;

            nrebaljet = 0;

            if((unsigned int)t.njet != rebalTree.useJet->size()){
                cout << "WARNING: mismatched event! " << event << " " << nEventsTotal-1 << endl;
                continue;
            }

            float rebal_met_pt = t.met_pt;
            float rebal_met_phi = t.met_phi;
            float rebal_met_x = rebal_met_pt * cos(rebal_met_phi);
            float rebal_met_y = rebal_met_pt * sin(rebal_met_phi);

            int ireb = -1;
            for(int i=0; i<t.njet; i++){
                if(rebalTree.useJet->at(i) != 1)
                    continue;
                ireb += 1;

                float newpt = t.jet_pt[i] * rebalTree.rebalanceFactors->at(ireb);

                rebal_met_x += (t.jet_pt[i] - newpt) * cos(t.jet_phi[i]);
                rebal_met_y += (t.jet_pt[i] - newpt) * sin(t.jet_phi[i]);

                rebaljet_pt[ireb] = newpt;
                rebaljet_eta[ireb] = t.jet_eta[i];
                rebaljet_phi[ireb] = t.jet_phi[i];
                rebaljet_btagCSV[ireb] = t.jet_btagCSV[i];
            }
            nrebaljet = ireb + 1;

            rebal_met_pt = sqrt(rebal_met_x*rebal_met_x + rebal_met_y*rebal_met_y);
            rebal_met_phi = atan2(rebal_met_y, rebal_met_x);

            // COMPUTE REBALANCED JET QUANTITIES //
            computeJetVars("rebalance", rebal_met_pt, rebal_met_phi, jetVars);
            h_nJet30_vec.at(3)->Fill(jetVars[0], scale);
            if(jetVars[0] >= 2){
                h_met_vec.at(3)->Fill(rebal_met_pt, scale);
                h_ht_vec.at(3)->Fill(jetVars[1], scale);
                h_mht_vec.at(3)->Fill(jetVars[2], scale);
                h_diffMetMhtOverMet_vec.at(3)->Fill(jetVars[3], scale);
                h_j1pt_vec.at(3)->Fill(jetVars[4], scale);
                h_j2pt_vec.at(3)->Fill(jetVars[5], scale);
                h_deltaPhiMin_vec.at(3)->Fill(jetVars[6], scale);
            }

            // SMEAR THE REBALANCED JETS

            cout << event << " " << nEventsTotal-1 << " " << nrebaljet << endl;

            //recompute met with smeared jets
            for(int ismear=0; ismear<NSMEARS; ismear++){
                cout << ismear << endl;
                float met_smear_x = met_sub_x;
                float met_smear_y = met_sub_y;

                for(int ijet=0; ijet<nrebaljet; ijet++){
                    

                    RSjet_eta[ijet] = rebaljet_eta[ijet];
                    
                    // WHY DOES THIS LINE MAKE IT SEGFAULT???????? (but only on oddly specific events)
                    // forget about it for now and just use rebaljet_phi, since it's the same
                    // RSjet_phi[ijet] = rebaljet_phi[ijet];

                    bool isBjet = rebaljet_btagCSV[ijet] > 0.800;

                    float smearfact = reader.GetRandomResponse(rebaljet_pt[ijet], rebaljet_eta[ijet], isBjet);

                    RSjet_pt[ijet] = rebaljet_pt[ijet] * smearfact;

                    met_smear_x -= RSjet_pt[ijet] * cos(rebaljet_phi[ijet]);
                    met_smear_y -= RSjet_pt[ijet] * sin(rebaljet_phi[ijet]);

                }
                float met_smear = sqrt(met_smear_x*met_smear_x + met_smear_y*met_smear_y);
                float met_smear_phi = atan2(met_smear_y,met_smear_x);

                // COMPUTE SMEARJET QUANTITIES //
                computeJetVars("rebalsmear", met_smear, met_smear_phi, jetVars);
                h_nJet30_vec.at(4)->Fill(jetVars[0], scale/NSMEARS);
                if(jetVars[0] >= 2 && met_smear>metCut){
                    h_met_vec.at(4)->Fill(met_smear, scale/NSMEARS);
                    h_ht_vec.at(4)->Fill(jetVars[1], scale/NSMEARS);
                    h_mht_vec.at(4)->Fill(jetVars[2], scale/NSMEARS);
                    h_diffMetMhtOverMet_vec.at(4)->Fill(jetVars[3], scale/NSMEARS);
                    h_j1pt_vec.at(4)->Fill(jetVars[4], scale/NSMEARS);
                    h_j2pt_vec.at(4)->Fill(jetVars[5], scale/NSMEARS);
                    h_deltaPhiMin_vec.at(4)->Fill(jetVars[6], scale/NSMEARS);
                }
                
            }// smearing loop
            
            
        }//event loop
        
        cout << " nBadEvents: " << nBadEvents << endl;

    }//file loop

    fout->cd();
    for(int i=0; i<5; i++){
        TDirectory *d = fout->mkdir(tags[i].c_str());
        d->cd();
        h_nJet30_vec.at(i)->Write();
        h_met_vec.at(i)->Write();
        h_ht_vec.at(i)->Write();
        h_mht_vec.at(i)->Write();
        h_diffMetMhtOverMet_vec.at(i)->Write();
        h_j1pt_vec.at(i)->Write();
        h_j2pt_vec.at(i)->Write();
        h_deltaPhiMin_vec.at(i)->Write();
    }



    fout->Close();

}

// return indices of jets passing pt>30, eta<2.5
vector<int> getGoodJets(vector<float> &pt, vector<float> &eta){
    
    vector<int> ind;
    for(unsigned int i=0; i<pt.size(); i++){
        if(pt.at(i)>30 && eta.at(i)<2.5)
            ind.push_back(i);
    }
    return ind;

}

bool pairCompare(pair<float, float> p1, pair<float,float> p2){
    return p1.first > p2.first;
}

float DeltaPhi(float phi1, float phi2){
    float dphi = fabs(phi1-phi2);
    if(dphi > 3.14159265){
        dphi = 6.28318530 - dphi;
    }
    return dphi;
}

float DeltaR(float eta1, float phi1, float eta2, float phi2){
    float dphi = fabs(phi1-phi2);
    const float PI = 3.14159265359;
    if(dphi > PI)
        dphi = 2*PI - dphi;
    return sqrt((eta1-eta2)*(eta1-eta2) + dphi*dphi);
}


// compute nJet30, ht, mht, diffMetMht/met, jet1_pt, jet2_pt, deltaPhiMin
void RStest::computeJetVars(string jettype, float met_pt, float met_phi, float *results){
    float *pt = NULL;
    float *eta = NULL;
    float *phi = NULL;
    int njets = 0;
    // vector<int> *jetID = NULL;

    if(jettype=="reco"){
        pt = t.jet_pt;
        eta = t.jet_eta;
        phi = t.jet_phi;
        njets = t.njet;
        // jetID = t.jet_isLoosePFJet;
    }
    // if(jettype=="gen"){
    //     pt = t.genjet_pt;
    //     eta = t.genjet_eta;
    //     phi = t.genjet_phi;
    //     jetID = NULL;
    // }
    // if(jettype=="smear"){
    //     pt = &smearjet_pt;
    //     eta = &smearjet_eta;
    //     phi = &smearjet_phi;
    //     jetID = NULL;
    // }
    if(jettype=="rebalance"){
        pt = rebaljet_pt;
        eta = rebaljet_eta;
        phi = rebaljet_phi;
        njets = nrebaljet;
        // jetID = NULL;
    }
    if(jettype=="rebalsmear"){
        pt = RSjet_pt;
        eta = RSjet_eta;
        phi = rebaljet_phi;
        njets = nrebaljet;
        // jetID = NULL;
    }


    // int njets = pt->size();

    float ht=0;
    float mht_x = 0;
    float mht_y = 0;
    
    float met_x = met_pt * cos(met_phi);
    float met_y = met_pt * sin(met_phi);

    vector< pair<float,float> > ptphi;
    int nJet30 = 0;
    int nJet30FailId = 0;

    for(int ij=0; ij<njets; ij++){
        if(pt[ij] > 30 && eta[ij] < 2.5){
            // if(jettype=="reco" && jetID[ij]==0){
            //     nJet30FailId++;
            //     continue;                
            // }

            ht += pt[ij];
            mht_x -= pt[ij]*cos(phi[ij]);
            mht_y -= pt[ij]*sin(phi[ij]);
            ptphi.push_back(pair<float,float> (pt[ij], phi[ij]));
            nJet30++;


        }
    }

    float mht = sqrt(mht_x*mht_x + mht_y*mht_y);
    float diffMetMht = sqrt((met_x-mht_x)*(met_x-mht_x) + (met_y-mht_y)*(met_y*mht_y));
    
    sort(ptphi.begin(), ptphi.end(), pairCompare);

    results[0] = nJet30;
    results[1] = ht;
    results[2] = mht;
    results[3] = diffMetMht/met_pt;
    results[4] = 0;
    results[5] = 0;    
    if(nJet30 > 0)
        results[4] = ptphi.at(0).first;
    if(nJet30 > 1)
        results[5] = ptphi.at(1).first;

    results[6] = 999;
    for(int i=0; i<min(nJet30,4); i++){
        results[6] = min(results[6], DeltaPhi(met_phi, ptphi.at(i).second));
    }
    if(results[6]==999)
        results[6] = -1;


}

//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Feb  3 20:36:15 2013 by ROOT version 5.26/00e
// from TTree IWSMuonTree/IWSMuonTree
// found on file: run21982_Fast_neutron.root
//////////////////////////////////////////////////////////

#ifndef FastNeutron_h
#define FastNeutron_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

class FastNeutron : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           DetId;
   Double_t        TrigTime;
   Int_t           TrigSec;
   Int_t           TrigNanoSec;
   Int_t           NPmt;
   Double_t        TimeToLastIWSMuon;
   Int_t           CleanMuon;
   Int_t           FirstHitTime;
   Int_t           LastHitTime;
   vector<int>     *SpallDetId;
   vector<double>  *SpallTrigTime;
   vector<int>     *SpallTrigSec;
   vector<int>     *SpallTrigNanoSec;
   vector<float>   *SpallScaledE;
   vector<float>   *SpallEnergy;
   vector<float>   *SpallX;
   vector<float>   *SpallY;
   vector<float>   *SpallZ;
   vector<int>     *SpallFirstHitTime;
   vector<int>     *SpallLastHitTime;
   vector<int>     *SpallNPmt;
   vector<float>   *SpallMaxQ;
   vector<float>   *SpallQuadrant;
   vector<float>   *SpallMaxQ_2inchPMT;
   vector<int>     *SpallColumn_2inchPMT;
   vector<float>   *SpallMiddleTimeRMS;

   // List of branches
   TBranch        *b_DetId;   //!
   TBranch        *b_TrigTime;   //!
   TBranch        *b_TrigSec;   //!
   TBranch        *b_TrigNanoSec;   //!
   TBranch        *b_NPmt;   //!
   TBranch        *b_TimeToLastIWSMuon;   //!
   TBranch        *b_CleanMuon;   //!
   TBranch        *b_FirstHistTime;   //!
   TBranch        *b_LastHistTime;   //!
   TBranch        *b_SpallDetId;   //!
   TBranch        *b_SpallTrigTime;   //!
   TBranch        *b_SpallTrigSec;   //!
   TBranch        *b_SpallTrigNanoSec;   //!
   TBranch        *b_SpallScaledE;   //!
   TBranch        *b_SpallEnergy;   //!
   TBranch        *b_SpallX;   //!
   TBranch        *b_SpallY;   //!
   TBranch        *b_SpallZ;   //!
   TBranch        *b_SpallFirstHitTime;   //!
   TBranch        *b_SpallLastHitTime;   //!
   TBranch        *b_SpallNPmt;   //!
   TBranch        *b_SpallMaxQ;   //!
   TBranch        *b_SpallQuadrant;   //!
   TBranch        *b_SpallMaxQ_2inchPMT;   //!
   TBranch        *b_SpallColumn_2inchPMT;   //!
   TBranch        *b_SpallMiddleTimeRMS;   //!

   FastNeutron(TTree * /*tree*/ =0) { }
   virtual ~FastNeutron() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(FastNeutron,0);
};

#endif

#ifdef FastNeutron_cxx
void FastNeutron::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   SpallDetId = 0;
   SpallTrigTime = 0;
   SpallTrigSec = 0;
   SpallTrigNanoSec = 0;
   SpallScaledE = 0;
   SpallEnergy = 0;
   SpallX = 0;
   SpallY = 0;
   SpallZ = 0;
   SpallFirstHitTime = 0;
   SpallLastHitTime = 0;
   SpallNPmt = 0;
   SpallMaxQ = 0;
   SpallQuadrant = 0;
   SpallMaxQ_2inchPMT = 0;
   SpallColumn_2inchPMT = 0;
   SpallMiddleTimeRMS = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("DetId", &DetId, &b_DetId);
   fChain->SetBranchAddress("TrigTime", &TrigTime, &b_TrigTime);
   fChain->SetBranchAddress("TrigSec", &TrigSec, &b_TrigSec);
   fChain->SetBranchAddress("TrigNanoSec", &TrigNanoSec, &b_TrigNanoSec);
   fChain->SetBranchAddress("NPmt", &NPmt, &b_NPmt);
   fChain->SetBranchAddress("TimeToLastIWSMuon", &TimeToLastIWSMuon, &b_TimeToLastIWSMuon);
   fChain->SetBranchAddress("CleanMuon", &CleanMuon, &b_CleanMuon);
   fChain->SetBranchAddress("FirstHitTime", &FirstHitTime, &b_FirstHistTime);
   fChain->SetBranchAddress("LastHitTime", &LastHitTime, &b_LastHistTime);
   fChain->SetBranchAddress("SpallDetId", &SpallDetId, &b_SpallDetId);
   fChain->SetBranchAddress("SpallTrigTime", &SpallTrigTime, &b_SpallTrigTime);
   fChain->SetBranchAddress("SpallTrigSec", &SpallTrigSec, &b_SpallTrigSec);
   fChain->SetBranchAddress("SpallTrigNanoSec", &SpallTrigNanoSec, &b_SpallTrigNanoSec);
   fChain->SetBranchAddress("SpallScaledE", &SpallScaledE, &b_SpallScaledE);
   fChain->SetBranchAddress("SpallEnergy", &SpallEnergy, &b_SpallEnergy);
   fChain->SetBranchAddress("SpallX", &SpallX, &b_SpallX);
   fChain->SetBranchAddress("SpallY", &SpallY, &b_SpallY);
   fChain->SetBranchAddress("SpallZ", &SpallZ, &b_SpallZ);
   fChain->SetBranchAddress("SpallFirstHitTime", &SpallFirstHitTime, &b_SpallFirstHitTime);
   fChain->SetBranchAddress("SpallLastHitTime", &SpallLastHitTime, &b_SpallLastHitTime);
   fChain->SetBranchAddress("SpallNPmt", &SpallNPmt, &b_SpallNPmt);
   fChain->SetBranchAddress("SpallMaxQ", &SpallMaxQ, &b_SpallMaxQ);
   fChain->SetBranchAddress("SpallQuadrant", &SpallQuadrant, &b_SpallQuadrant);
   fChain->SetBranchAddress("SpallMaxQ_2inchPMT", &SpallMaxQ_2inchPMT, &b_SpallMaxQ_2inchPMT);
   fChain->SetBranchAddress("SpallColumn_2inchPMT", &SpallColumn_2inchPMT, &b_SpallColumn_2inchPMT);
   fChain->SetBranchAddress("SpallMiddleTimeRMS", &SpallMiddleTimeRMS, &b_SpallMiddleTimeRMS);
}

Bool_t FastNeutron::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef FastNeutron_cxx

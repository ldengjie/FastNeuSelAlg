//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Mar  3 18:01:00 2012 by ROOT version 5.26/00e
// from TTree IWSMuonTree/IWSMuonTree
// found on file: run16347_Fast_neutron.root
//////////////////////////////////////////////////////////

#ifndef FastNeuAna_h
#define FastNeuAna_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TSelector.h>

class FastNeuAna : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           DetId;
   Int_t           TrigSec;
   Int_t           TrigNanoSec;
   Int_t           FirstHitTime;
   Int_t           LastHitTime;
   Int_t           NPmt;
   Int_t           RunNum;
   Int_t           FileNum;
   Double_t        TimeToLastIWSMuon;
   Double_t        ShiftTime;
   vector<int>     *SpallDetId;
   vector<int>     *SpallTrigSec;
   vector<int>     *SpallTrigNanoSec;
   vector<int>     *SpallFirstHitTime;
   vector<int>     *SpallLastHitTime;
   vector<float>   *SpallScaledE;
   vector<float>   *SpallEnergy;
   vector<float>   *SpallX;
   vector<float>   *SpallY;
   vector<float>   *SpallZ;
   vector<int>     *SpallNPmt;
   vector<float>   *SpallMaxQ;
   vector<float>   *SpallQuadrant;
   vector<float>   *SpallMaxQ_2inchPMT;
   vector<int>     *SpallColumn_2inchPMT;
   vector<float>   *SpallMiddleTimeRMS;
   //vector<float>   *SpallTimePSD;
   //vector<float>   *SpallTimePSD1;
   //vector<float>   *SpallQ1;
   //vector<float>   *SpallQ2;
   //vector<float>   *SpallQ3;

   // List of branches
   TBranch        *b_DetId;   //!
   TBranch        *b_RunNum;   //!
   TBranch        *b_FileNum;   //!
   TBranch        *b_ShiftTime;   //!
   TBranch        *b_TrigSec;   //!
   TBranch        *b_TrigNanoSec;   //!
   TBranch        *b_FirstHitTime;   //!
   TBranch        *b_LastHitTime;   //!
   TBranch        *b_NPmt;   //!
   TBranch        *b_TimeToLastIWSMuon;   //!
   TBranch        *b_SpallDetId;   //!
   TBranch        *b_SpallTrigSec;   //!
   TBranch        *b_SpallTrigNanoSec;   //!
   TBranch        *b_SpallFirstHitTime;   //!
   TBranch        *b_SpallLastHitTime;   //!
   TBranch        *b_SpallScaledE;   //!
   TBranch        *b_SpallEnergy;   //!
   TBranch        *b_SpallX;   //!
   TBranch        *b_SpallY;   //!
   TBranch        *b_SpallZ;   //!
   TBranch        *b_SpallNPmt;   //!
   TBranch        *b_SpallMaxQ;   //!
   TBranch        *b_SpallQuadrant;   //!
   TBranch        *b_SpallMaxQ_2inchPMT;   //!
   TBranch        *b_SpallColumn_2inchPMT;   //!
   TBranch        *b_SpallMiddleTimeRMS;   //!
   //TBranch        *b_SpallTimePSD;         //!
   //TBranch        *b_SpallTimePSD1;        //!
   //TBranch        *b_SpallQ1;
   //TBranch        *b_SpallQ2;
   //TBranch        *b_SpallQ3;

   FastNeuAna(TTree * /*tree*/ =0) { }
   virtual ~FastNeuAna() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual void    FillHist(Int_t det,Int_t tag);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   double     TrigTime;
   vector<double>     spallTrigTime[4];
   //vector<int>     spallTrigSec[4];
   vector<int>     spallTrigNanoSec[4];
   vector<int>     spallFirstHitTime[4];
   vector<int>     spallLastHitTime[4];
   //vector<float>   spallScaledE[4];
   vector<float>   spallEnergy[4];
   vector<float>   spallX[4];
   vector<float>   spallY[4];
   vector<float>   spallZ[4];
   vector<float>   spallTimeRMS[4];
   vector<float>   spallMaxQ[4];
   vector<float>   spallQuadrant[4];

   Int_t  m_evt;
   Int_t  m_Fn;
   Int_t  c1num,c2num,c3num,c4num,c5num;
   TFile* m_file;

   //NPmt of the IWSMuon
   TH1F*  m_IWSMuonNPmt;
   TH1F*  m_IWSMuonToLastMuon;

   TString histname;
   TString adname;
   static const int tagnum=11;
   TH1F*  m_fnPT2MuLog[4][tagnum];
   TH1F*  m_fnPT2Mu[4][tagnum];
   TH1F*  m_fnPT2Mu2[4][tagnum];
   TH1F*  m_fnPFHT2Mu[4][tagnum];
   TH1F*  m_fnPFHT2MuLog[4][tagnum];
   TH1F*  m_fnPFHT2Mu2[4][tagnum];
   TH1F*  m_fnDFHT2Mu[4][tagnum];
   TH1F*  m_fnDFHT2MuLog[4][tagnum];
   TH1F*  m_fnDFHT2Mu2[4][tagnum];
   //TH1F*  m_fnPFHT2Mu3[4][tagnum];
   //TH1F*  m_fnPFHT2Mu3Log[4][tagnum];
   TH1F*  m_fnDFHT2PLog[4][tagnum];
   TH1F*  m_fnDFHT2P[4][tagnum];
   TH1F*  m_fnDT2MuLog[4][tagnum];
   TH1F*  m_fnDT2PLog[4][tagnum];
   TH2F*  m_fnPEvsDE[4][tagnum];
   TH2F*  m_fnPEvsT[4][tagnum];
   TH2F*  m_fnPEvsFHT[4][tagnum];
   TH2F*  m_fnPEvsDFHT[4][tagnum];
   TH2F*  m_fnDEvsFHT[4][tagnum];
   TH2F*  m_fnDEvsT[4][tagnum];
   TH2F*  m_fnPEvsT2[4][tagnum];
   TH2F*  m_fnPEvsFHT2[4][tagnum];
   TH2F*  m_fnDEvsFHT2[4][tagnum];
   TH2F*  m_fnDEvsT2[4][tagnum];
   //The energy spectrum of fast neutron
   TH1F*  m_fnPE[4][tagnum];
   TH1F*  m_fnDE[4][tagnum];
   TH1F*  m_fnDE2[4][tagnum];

   //The Vertex of fast neutron
   TH2F*  m_fnPVXY[4][tagnum];
   TH2F*  m_fnDVXY[4][tagnum];
   TH2F*  m_fnPVRZ[4][tagnum];
   TH2F*  m_fnDVRZ[4][tagnum];

   TH1F*  m_fnTimeInt[4][tagnum];
   TH1F*  m_fnPosInt[4][tagnum];
   TH2F*  m_fnPosInt_PT2Mu[4][tagnum];
   TH2F*  m_fnPosInt_PT2Mu2[4][tagnum];
//========================================
   TH1F*  m_fnDZAD1;
   //The time interval of prompt and delayed signal

   //The time interval of prompt and delayed signal to its IWSMuon
   TH1F*  m_fnToIWSMuonAD1;
   TH1F*  m_fnPToIWSMuonAD1;

   //The Middle time RMS of prompt and delayed signal
   TH1F*  m_fnPTRMSAD1;
   TH1F*  m_fnDTRMSAD1;

   //The Flasher of Pmpt and delayed signal
   TH2F*  m_fnPMaxQQuadrantAD1;
   TH2F*  m_fnDMaxQQuadrantAD1;

   TH2F*  m_fnPTimePSDVSEllipseAD1;
   TH2F*  m_fnDTimePSDVSEllipseAD1;

   TH2F*  m_fnPEVSVertexDtaRAD1;
   TH2F*  m_fnPIWSMuonDTimInAD1;  

   //======================================
   /*
   //The energy spectrum of fast neutron
   TH1F*  m_fnPEAD2;
   TH1F*  m_fnDEAD2;

   //The Vertex of fast neutron
   TH2F*  m_fnPVXYAD2;
   TH2F*  m_fnDVXYAD2;
   TH2F*  m_fnPVRZAD2;
   TH2F*  m_fnDVRZAD2;

   TH1F*  m_fnDZAD2;
   //The time interval of prompt and delayed signal
   TH1F*  m_fnTimeIntAD2;

   //The time interval of prompt and delayed signal to its IWSMuon
   TH1F*  m_fnToIWSMuonAD2;
   TH1F*  m_fnPToIWSMuonAD2;

   //The Middle time RMS of prompt and delayed signal
   TH1F*  m_fnPTRMSAD2;
   TH1F*  m_fnDTRMSAD2;

   //The Flasher of Pmpt and delayed signal
   TH2F*  m_fnPMaxQQuadrantAD2;
   TH2F*  m_fnDMaxQQuadrantAD2;

   TH2F*  m_fnPTimePSDVSEllipseAD2;
   TH2F*  m_fnDTimePSDVSEllipseAD2;

   TH2F*  m_fnPEVSVertexDtaRAD2;
   TH2F*  m_fnPIWSMuonDTimInAD2;
    */
   ClassDef(FastNeuAna,0);
};

#endif

#ifdef FastNeuAna_cxx
void FastNeuAna::Init(TTree *tree)
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
   SpallTrigSec = 0;
   SpallTrigNanoSec = 0;
   SpallFirstHitTime = 0;
   SpallLastHitTime = 0;
   SpallScaledE = 0;
   SpallEnergy = 0;
   SpallX = 0;
   SpallY = 0;
   SpallZ = 0;
   SpallNPmt = 0;
   SpallMaxQ = 0;
   SpallQuadrant = 0;
   SpallMaxQ_2inchPMT = 0;
   SpallColumn_2inchPMT = 0;
   SpallMiddleTimeRMS = 0;
   //SpallTimePSD = 0;
   //SpallTimePSD1 = 0;
   //SpallQ1 = 0;
   //SpallQ2 = 0;
   //SpallQ3 = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("DetId", &DetId, &b_DetId);
   fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
   fChain->SetBranchAddress("FileNum", &FileNum, &b_FileNum);
   fChain->SetBranchAddress("ShiftTime", &ShiftTime, &b_ShiftTime);
   fChain->SetBranchAddress("TrigSec", &TrigSec, &b_TrigSec);
   fChain->SetBranchAddress("TrigNanoSec", &TrigNanoSec, &b_TrigNanoSec);
   fChain->SetBranchAddress("FirstHitTime", &FirstHitTime, &b_FirstHitTime);
   fChain->SetBranchAddress("LastHitTime", &LastHitTime, &b_LastHitTime);
   fChain->SetBranchAddress("NPmt", &NPmt, &b_NPmt);
   fChain->SetBranchAddress("TimeToLastIWSMuon", &TimeToLastIWSMuon, &b_TimeToLastIWSMuon);
   fChain->SetBranchAddress("SpallDetId", &SpallDetId, &b_SpallDetId);
   fChain->SetBranchAddress("SpallTrigSec", &SpallTrigSec, &b_SpallTrigSec);
   fChain->SetBranchAddress("SpallTrigNanoSec", &SpallTrigNanoSec, &b_SpallTrigNanoSec);
   fChain->SetBranchAddress("SpallFirstHitTime", &SpallFirstHitTime, &b_SpallFirstHitTime);
   fChain->SetBranchAddress("SpallLastHitTime", &SpallLastHitTime, &b_SpallLastHitTime);
   fChain->SetBranchAddress("SpallScaledE", &SpallScaledE, &b_SpallScaledE);
   fChain->SetBranchAddress("SpallEnergy", &SpallEnergy, &b_SpallEnergy);
   fChain->SetBranchAddress("SpallX", &SpallX, &b_SpallX);
   fChain->SetBranchAddress("SpallY", &SpallY, &b_SpallY);
   fChain->SetBranchAddress("SpallZ", &SpallZ, &b_SpallZ);
   fChain->SetBranchAddress("SpallNPmt", &SpallNPmt, &b_SpallNPmt);
   fChain->SetBranchAddress("SpallMaxQ", &SpallMaxQ, &b_SpallMaxQ);
   fChain->SetBranchAddress("SpallQuadrant", &SpallQuadrant, &b_SpallQuadrant);
   fChain->SetBranchAddress("SpallMaxQ_2inchPMT", &SpallMaxQ_2inchPMT, &b_SpallMaxQ_2inchPMT);
   fChain->SetBranchAddress("SpallColumn_2inchPMT", &SpallColumn_2inchPMT, &b_SpallColumn_2inchPMT);
   fChain->SetBranchAddress("SpallMiddleTimeRMS", &SpallMiddleTimeRMS, &b_SpallMiddleTimeRMS);
   //fChain->SetBranchAddress("SpallTimePSD", &SpallTimePSD, &b_SpallTimePSD);
   //fChain->SetBranchAddress("SpallTimePSD1", &SpallTimePSD1, &b_SpallTimePSD1);
   //fChain->SetBranchAddress("SpallQ1", &SpallQ1, &b_SpallQ1);
   //fChain->SetBranchAddress("SpallQ2", &SpallQ2, &b_SpallQ2);
   //fChain->SetBranchAddress("SpallQ3", &SpallQ3, &b_SpallQ3);
}

Bool_t FastNeuAna::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef FastNeuAna_cxx

#define FastNeuAna_cxx
#include <iostream>
#include "FastNeuAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
using namespace std;

void FastNeuAna::Begin(TTree * /*tree*/)
{

   TString option = GetOption();
   std::cout<<"option  : "<<option<<endl;

   m_evt = -1;
   m_Fn = 0;
   c1num=0;
   c2num=0;
   c3num=0;
   c4num=0;
   c5num=0;

   TString strfile = "/afs/ihep.ac.cn/users/l/lidj/file/FastNeuSelAlg/job/P14A/";
   strfile += option;
   strfile += "_AS_tA_1.5.root";
   m_file = new TFile(strfile, "recreate");
   std::cout<<"begin to initialize hists"<<endl;

   //m_IWSMuonNPmt       = new TH1F("NPmt", "N Pmt Hit Signal for IWSMuon", 200, 0, 200);
   //m_IWSMuonToLastMuon = new TH1F("IWSMuonToLastMuon", "Time interval to Last IWSMuon", 1000, 0.0, 1.0);
   for( int i=0 ; i<1 ; i++ )
   {
       for( int j=0 ; j<tagnum ; j++ )
       {
            TString tagname;
            if( j==0 )
            {
                tagname="O";
            } else if (j==1)//c1 
            {
                tagname="R";
            }else if(j==2)
            {
                tagname="T";
            }else if(j==3)//c2 
            {
                tagname="RR";
            }else if (j==4)
            {
                tagname="RT";
            }else if (j==5)
            {
                tagname="RRR";//cut 3 
            }else if (j==6)
            {
                tagname="RRT";
            }else if (j==7)
            {
                tagname="RRRR";
            }else if (j==8)
            {
                tagname="RRRT";
            }else if (j==9)
            {
                tagname="RRRRR";
            
            }else if (j==10)
            {
                tagname="RRRRT";

            }else
            {
                continue;
            }
            adname="AD";
            adname+=i+1;
            histname=adname+"_PT2MuLog_"+tagname;
            m_fnPT2MuLog[i][j]= new TH1F(histname,"log10 time to last muon",560,-6,1);
            histname=adname+"_PT2Mu_"+tagname;
            //m_fnPT2Mu[i][j]= new TH1F(histname,"pro signal time to last muon",8000, 0.0, 200.);
            m_fnPT2Mu[i][j]= new TH1F(histname,"pro signal time to last muon",8080, -2.0, 200.);
            histname=adname+"_PT2Mu2_"+tagname;
            m_fnPT2Mu2[i][j]= new TH1F(histname,"fisrt hit time time between pro signal and last muon(ns)",1000, -500.0, 500.);
            histname=adname+"_PFHT2MuLog_"+tagname;
            m_fnPFHT2MuLog[i][j]= new TH1F(histname,"log10 time to last muon",560,-6,1);
            histname=adname+"_PFHT2Mu_"+tagname;
            m_fnPFHT2Mu[i][j]= new TH1F(histname,"fisrt hit time time between pro signal and last muon(ns)",2004, -400.0, 200000.);
            histname=adname+"_PFHT2Mu2_"+tagname;
            m_fnPFHT2Mu2[i][j]= new TH1F(histname,"fisrt hit time time between pro signal and last muon(ns)",1000, -500.0, 500.);
            histname=adname+"_DFHT2MuLog_"+tagname;
            m_fnDFHT2MuLog[i][j]= new TH1F(histname,"log10 time to last muon",560,-6,1);
            histname=adname+"_DFHT2Mu_"+tagname;
            m_fnDFHT2Mu[i][j]= new TH1F(histname,"fisrt hit time time between del signal and last muon(ns)",2004, -400.0, 200000.);
            histname=adname+"_DFHT2Mu2_"+tagname;
            m_fnDFHT2Mu2[i][j]= new TH1F(histname,"fisrt hit time time between del signal and last muon(ns)",1000, -500.0, 500.);
            histname=adname+"_DFHT2P_"+tagname;
            m_fnDFHT2P[i][j]= new TH1F(histname,"fisrt hit time time between pro signal and del signal(ns)",2004, -400.0, 200000.);
            histname=adname+"_DFHT2PLog_"+tagname;
            m_fnDFHT2PLog[i][j]= new TH1F(histname,"fisrt hit time time between pro signal and del signal(ns)",560, -6, 1);
            histname=adname+"_DT2MuLog_"+tagname;
            m_fnDT2MuLog[i][j]= new TH1F(histname,"log10 time to last muon",560,-6,1);
            histname=adname+"_DT2P_"+tagname;
            m_fnTimeInt[i][j]   = new TH1F(histname,   "Time interval of Pmpt and Dayed Signal",  800, 0.0, 200.);
            histname=adname+"_DT2PLog_"+tagname;
            m_fnDT2PLog[i][j]= new TH1F(histname,"log10 time between del and pro ",560,-6,1);
            histname=adname+"_PEvsDE_"+tagname;
            m_fnPEvsDE[i][j] = new TH2F(histname, "Pmpt Signal Position E&T",120, 0.0,12.0, 1000, 0.0, 100.0);
            histname=adname+"_PEvsT2Mu_"+tagname;
            m_fnPEvsT[i][j] = new TH2F(histname, "Pmpt Signal Position E&T",  200, -0.0, 100.0, 8080, -2.0, 200.0);
            histname=adname+"_PEvsFHT2Mu_"+tagname;
            m_fnPEvsFHT[i][j] = new TH2F(histname, "Pmpt Signal Position E&T",  200, -0.0, 100.0, 8080, -2.0, 200.0);
            histname=adname+"_PEvsDFHT2Mu_"+tagname;
            m_fnPEvsDFHT[i][j] = new TH2F(histname, "Pmpt Signal Position E&T",  200, -0.0, 100.0, 8080, -2.0, 200.0);
            histname=adname+"_DEvsFHT2Mu_"+tagname;
            m_fnDEvsFHT[i][j] = new TH2F(histname, "Del Signal Position E&T",  60, 6.0, 12.0, 8080, -2.0, 200.0);
            histname=adname+"_DEvsT2Mu_"+tagname;
            m_fnDEvsT[i][j] = new TH2F(histname, "Dmpt Signal Position E&T",  60, 6.0, 12.0, 8080, -2.0, 200.0);
            
            histname=adname+"_PEvsT2Mu2_"+tagname;
            m_fnPEvsT2[i][j] = new TH2F(histname, "Pmpt Signal Position E&T",  200, -0.0, 100.0, 4000, -2000.0, 2000.0);
            histname=adname+"_PEvsFHT2Mu2_"+tagname;
            m_fnPEvsFHT2[i][j] = new TH2F(histname, "Pmpt Signal Position E&T",  200, -0.0, 100.0, 4000, -2000.0, 2000.0);
            histname=adname+"_DEvsFHT2Mu2_"+tagname;
            m_fnDEvsFHT2[i][j] = new TH2F(histname, "Del Signal Position E&T",  60, 6.0, 12.0, 4000, -2000.0, 2000.0);
            histname=adname+"_DEvsT2Mu2_"+tagname;
            m_fnDEvsT2[i][j] = new TH2F(histname, "Dmpt Signal Position E&T",  60, 6.0, 12.0, 4000, -2000.0, 2000.0);

            histname=adname+"_PE_"+tagname;
            m_fnPE[i][j] = new TH1F(histname, "Energy of Pmpt Signal",  200, 0,  100);
            histname=adname+"_DE_"+tagname;
            m_fnDE[i][j] = new TH1F(histname, "Energy of Dayed Signal", 60, 6, 12);
            histname=adname+"_DE2_"+tagname;
            m_fnDE2[i][j] = new TH1F(histname, "Energy of Dayed Signal",120, 0, 12);
            histname=adname+"_PXvsY_"+tagname;
            m_fnPVXY[i][j] = new TH2F(histname, "Pmpt Signal Position X&Y",  200, -3.0, 3.0, 200, -3.0, 3.0);
            histname=adname+"_DXvsY_"+tagname;
            m_fnDVXY[i][j] = new TH2F(histname, "Dayed Signal Position X&Y", 200, -3.0, 3.0, 200, -3.0, 3.0);
            histname=adname+"_PRvsZ_"+tagname;
            m_fnPVRZ[i][j] = new TH2F(histname, "Pmpt Signal Position R&Z",  150, 0.0,  3.0, 200, -3.0, 3.0);
            histname=adname+"_DRvsZ_"+tagname;
            m_fnDVRZ[i][j] = new TH2F(histname, "Dayed Signal Position R&Z", 150, 0.0,  3.0, 200, -3.0, 3.0);
            histname=adname+"_IntPos_"+tagname;
            m_fnPosInt[i][j]   = new TH1F(histname,   "distance of Pmpt and Dayed Signal",  300, 0.0, 6.);
            histname=adname+"_IntPosvsPT2Mu2_"+tagname;
            m_fnPosInt_PT2Mu2[i][j] = new TH2F(histname,"distance of Pmpt and Dayed Signal VS pro time to last muon",300, 0.0, 6.,8080, -2.0, 200.0);
            histname=adname+"_IntPosvsPT2Mu_"+tagname;
            m_fnPosInt_PT2Mu[i][j] = new TH2F(histname,"distance of Pmpt and Dayed Signal VS pro time to last muon",300, 0.0, 6.,8000, 0.0, 200.0);
       }
       
   }
   
}

void FastNeuAna::SlaveBegin(TTree * /*tree*/)
{

   TString option = GetOption();

}


Bool_t FastNeuAna::Process(Long64_t entry)
{
  TrigTime=0.;
  for( int i=0 ; i<4 ; i++ )
  {
      spallTrigTime[i].clear();
      spallTrigNanoSec[i].clear();
      spallFirstHitTime[i].clear();
      spallLastHitTime[i].clear();
      spallEnergy[i].clear();
      spallX[i].clear();
      spallY[i].clear();
      spallZ[i].clear();
      spallTimeRMS[i].clear();
      spallMaxQ[i].clear();
      spallQuadrant[i].clear();
  }
  
   m_evt++;
   if(0 == m_evt%100000)
     cout<< "--------- "<< m_evt<< " ----------"<< endl;

   GetEntry(entry);

   TrigTime=(double)TrigSec+((double)TrigNanoSec)/1.0e9;
   for(vector<int>::size_type i = 0; i < SpallDetId->size(); i++)
   {
       /*
        spallEnergy[(*SpallDetId)[i]-1].push_back((*SpallScaledE)[i]);
        spallTrigNanoSec[(*SpallDetId)[i]-1].push_back((*SpallTrigNanoSec)[i]);
        spallFirstHitTime[(*SpallDetId)[i]-1].push_back((*SpallFirstHitTime)[i]);
        spallLastHitTime[(*SpallDetId)[i]-1].push_back((*SpallLastHitTime)[i]);
        spallX[(*SpallDetId)[i]-1].push_back((*SpallX)[i]);
        spallY[(*SpallDetId)[i]-1].push_back((*SpallY)[i]);
        spallZ[(*SpallDetId)[i]-1].push_back((*SpallZ)[i]);
        spallTimeRMS[(*SpallDetId)[i]-1].push_back((*SpallMiddleTimeRMS)[i]);
        spallMaxQ[(*SpallDetId)[i]-1].push_back((*SpallMaxQ)[i]);
        spallQuadrant[(*SpallDetId)[i]-1].push_back((*SpallQuadrant)[i]);
        spallTrigTime[(*SpallDetId)[i]-1].push_back((double)(*SpallTrigSec)[i]+((double)(*SpallTrigNanoSec)[i])/1.0e9);
        */
        spallEnergy[0].push_back((*SpallScaledE)[i]);
        spallTrigNanoSec[0].push_back((*SpallTrigNanoSec)[i]+(int)(-ShiftTime));
        spallFirstHitTime[0].push_back((*SpallFirstHitTime)[i]);
        spallLastHitTime[0].push_back((*SpallLastHitTime)[i]);
        spallX[0].push_back((*SpallX)[i]);
        spallY[0].push_back((*SpallY)[i]);
        spallZ[0].push_back((*SpallZ)[i]);
        spallTimeRMS[0].push_back((*SpallMiddleTimeRMS)[i]);
        spallMaxQ[0].push_back((*SpallMaxQ)[i]);
        spallQuadrant[0].push_back((*SpallQuadrant)[i]);
        spallTrigTime[0].push_back((double)(*SpallTrigSec)[i]+((double)(*SpallTrigNanoSec)[i])/1.0e9);
   }
   int mdet;
   if( 2 == spallEnergy[0].size()/* && spallEnergy[mdet][1]>6.0 && spallEnergy[mdet][1]<12.0*/)
   {
       mdet=0;
   }else if(2 == spallEnergy[1].size())
   {
       mdet=1;
   }else if(2 == spallEnergy[2].size())
    {
        mdet=2;
    }else
   {
       return true;
   }
   //std::cout<<"ShiftTime  : "<<ShiftTime<<endl;
   //if( spallEnergy[mdet][1]>12. /*|| spallEnergy[mdet][1]<6. */)
   if( spallEnergy[mdet][1]>12. || spallEnergy[mdet][1]<6. )
   {
       return true;
   }
   //if( /*FirstHitTime<-1650. || (*SpallFirstHitTime)[0]<-1650. ||(*SpallFirstHitTime)[1]<-1650. || */ShiftTime>1000)
   if( FirstHitTime<-1650. ||  FirstHitTime>-1250. || ShiftTime>1000)
   {
       return true;
   }
   if( spallTrigNanoSec[mdet][1]-spallTrigNanoSec[mdet][0]<1000 )
   {
       return true;
   }
   m_Fn++;
   FillHist(mdet,0); //original 
  //c1 : 
  //if( spallFirstHitTime[mdet][0]+spallTrigNanoSec[mdet][0] - (FirstHitTime+TrigNanoSec)<400 )
  if( spallFirstHitTime[mdet][0]+spallTrigNanoSec[mdet][0] - (FirstHitTime+TrigNanoSec)<200 )
  {
        FillHist(mdet,1); //R
        //c2 : 
        if((spallFirstHitTime[mdet][0]+spallTrigNanoSec[mdet][0] - (FirstHitTime+TrigNanoSec))>55)
        {
            FillHist(mdet,3);//RR
            //c3 : 
                    if((spallFirstHitTime[mdet][1]+spallTrigNanoSec[mdet][1] - (FirstHitTime+TrigNanoSec))>6600)
            {
                FillHist(mdet,5);//RRR
                //c4 :
            if(((TMath::Abs(spallZ[mdet][1]/1000.)<1.5&& TMath::Sqrt(spallX[mdet][1]*spallX[mdet][1] + spallY[mdet][1]*spallY[mdet][1])/1000<1.5)/* && TMath::Abs(spallZ[mdet][0]/1000.)<2.0 && TMath::Sqrt(spallX[mdet][0]*spallX[mdet][0] + spallY[mdet][0]*spallY[mdet][0])/1000<2.0*/))
                {
                    FillHist(mdet,7);//RRRR
                    //c5 :
                if(((TMath::Abs(spallZ[mdet][1]/1000.)<1.38&& TMath::Sqrt(spallX[mdet][1]*spallX[mdet][1] + spallY[mdet][1]*spallY[mdet][1])/1000<1.38)/* && TMath::Abs(spallZ[mdet][0]/1000.)<2.0 && TMath::Sqrt(spallX[mdet][0]*spallX[mdet][0] + spallY[mdet][0]*spallY[mdet][0])/1000<2.0*/))
                    {
                        FillHist(mdet,9);//RRRRR
                    }else
                    {
                        FillHist(mdet,10);//RRRRT
                        c5num++;
                    }
                }else
                {
                    FillHist(mdet,8);//RRRT
                    c4num++;
                }
            }else
            {
                FillHist(mdet,6);//RRT
                c3num++;
            }
        } else
        {
            FillHist(mdet,4);//RT
            c2num++;
        }
  }else
  {
        FillHist(mdet,2); //T
        c1num++;
  }

   return kTRUE;
}

void FastNeuAna::FillHist(Int_t det,Int_t tag)
{
      m_fnPT2MuLog[det][tag]->Fill(TMath::Log10(TMath::Abs((spallTrigNanoSec[det][0] - TrigNanoSec)/1.0e6)));
      //m_fnPT2Mu[det][tag]->Fill(TMath::Abs((spallTrigNanoSec[det][0] - TrigNanoSec)/1.0e3));
      m_fnPT2Mu[det][tag]->Fill((spallTrigNanoSec[det][0] - TrigNanoSec)/1.0e3);
      m_fnPT2Mu2[det][tag]->Fill(spallTrigNanoSec[det][0] - TrigNanoSec);
      m_fnPFHT2MuLog[det][tag]->Fill(TMath::Log10(TMath::Abs((spallFirstHitTime[det][0]+spallTrigNanoSec[det][0] - (FirstHitTime+TrigNanoSec))/1.0e6)));
      m_fnPFHT2Mu[det][tag]->Fill(spallFirstHitTime[det][0]+spallTrigNanoSec[det][0] - (FirstHitTime+TrigNanoSec));
      m_fnPFHT2Mu2[det][tag]->Fill(spallFirstHitTime[det][0]+spallTrigNanoSec[det][0] - (FirstHitTime+TrigNanoSec));
      m_fnDFHT2MuLog[det][tag]->Fill(TMath::Log10(TMath::Abs((spallFirstHitTime[det][1]+spallTrigNanoSec[det][1] - (FirstHitTime+TrigNanoSec))/1.0e6)));
      m_fnDFHT2Mu[det][tag]->Fill(spallFirstHitTime[det][1]+spallTrigNanoSec[det][1] - (FirstHitTime+TrigNanoSec));
      m_fnDFHT2Mu2[det][tag]->Fill(spallFirstHitTime[det][1]+spallTrigNanoSec[det][1] - (FirstHitTime+TrigNanoSec));
      //m_fnPFHT2Mu3[det][tag]->Fill(spallFirstHitTime[det][0]+spallTrigNanoSec[det][0] - (FirstHitTime+TrigNanoSec)+500);
      //m_fnPFHT2Mu3Log[det][tag]->Fill(TMath::Log10(spallFirstHitTime[det][0]+spallTrigNanoSec[det][0] - (FirstHitTime+TrigNanoSec)+500));
      m_fnDFHT2P[det][tag]->Fill(spallFirstHitTime[det][1]+spallTrigNanoSec[det][1] - (spallFirstHitTime[det][0]+spallTrigNanoSec[det][0]));
      m_fnDFHT2PLog[det][tag]->Fill(TMath::Log10(TMath::Abs((spallFirstHitTime[det][1]+spallTrigNanoSec[det][1] - (spallFirstHitTime[det][0]+spallTrigNanoSec[det][0]))/1.e6)));
      m_fnDT2MuLog[det][tag]->Fill(TMath::Log10(TMath::Abs((spallTrigNanoSec[det][1] - TrigNanoSec)/1.0e6)));
      m_fnDT2PLog[det][tag]->Fill(TMath::Log10(TMath::Abs((spallTrigNanoSec[det][1] - spallTrigNanoSec[det][0])/1.0e6)));
      m_fnTimeInt[det][tag]->Fill((spallTrigNanoSec[det][1] - spallTrigNanoSec[det][0])/1000.);
      m_fnPEvsDE[det][tag]->Fill(spallEnergy[det][1],spallEnergy[det][0]);
      m_fnPEvsT[det][tag]->Fill(spallEnergy[det][0],(spallTrigNanoSec[det][0] - TrigNanoSec)/1.0e3);
      m_fnPEvsFHT[det][tag]->Fill(spallEnergy[det][0],(spallFirstHitTime[det][0]+spallTrigNanoSec[det][0] - (FirstHitTime+TrigNanoSec))/1.0e3);
      m_fnPEvsDFHT[det][tag]->Fill(spallEnergy[det][0],(spallFirstHitTime[det][1]+spallTrigNanoSec[det][1] - (FirstHitTime+TrigNanoSec))/1.0e3);
      m_fnDEvsFHT[det][tag]->Fill(spallEnergy[det][1],(spallFirstHitTime[det][1]+spallTrigNanoSec[det][1] - (FirstHitTime+TrigNanoSec))/1.0e3);
      m_fnDEvsT[det][tag]->Fill(spallEnergy[det][1],(spallTrigNanoSec[det][1] - TrigNanoSec)/1.0e3);

      m_fnPEvsT2[det][tag]->Fill(spallEnergy[det][0],(spallTrigNanoSec[det][0] - TrigNanoSec));
      m_fnPEvsFHT2[det][tag]->Fill(spallEnergy[det][0],(spallFirstHitTime[det][0]+spallTrigNanoSec[det][0] - (FirstHitTime+TrigNanoSec)));
      m_fnDEvsFHT2[det][tag]->Fill(spallEnergy[det][1],(spallFirstHitTime[det][1]+spallTrigNanoSec[det][1] - (FirstHitTime+TrigNanoSec)));
      m_fnDEvsT2[det][tag]->Fill(spallEnergy[det][1],(spallTrigNanoSec[det][1] - TrigNanoSec));

      m_fnPE[det][tag]->Fill(spallEnergy[det][0]);
      m_fnDE[det][tag]->Fill(spallEnergy[det][1]);
      m_fnDE2[det][tag]->Fill(spallEnergy[det][1]);
      m_fnPVXY[det][tag]->Fill(spallX[det][0]/1000., spallY[det][0]/1000.);
      m_fnDVXY[det][tag]->Fill(spallX[det][1]/1000., spallY[det][1]/1000.);
      m_fnPVRZ[det][tag]->Fill(TMath::Sqrt(spallX[det][0]*spallX[det][0] + spallY[det][0]*spallY[det][0])/1000, spallZ[det][0]/1000);
      m_fnDVRZ[det][tag]->Fill(TMath::Sqrt(spallX[det][1]*spallX[det][1] + spallY[det][1]*spallY[det][1])/1000, spallZ[det][1]/1000);
      m_fnPosInt[det][tag]->Fill(TMath::Sqrt((spallX[det][0] - spallX[det][1])*(spallX[det][0] - spallX[det][1])+(spallY[det][0] - spallY[det][1])*(spallY[det][0] - spallY[det][1]) +(spallZ[det][0] - spallZ[det][1])*(spallZ[det][0] - spallZ[det][1]))/1000.0);
      m_fnPosInt_PT2Mu2[det][tag]->Fill(TMath::Sqrt((spallX[det][0] - spallX[det][1])*(spallX[det][0] - spallX[det][1])+(spallY[det][0] - spallY[det][1])*(spallY[det][0] - spallY[det][1]) +(spallZ[det][0] - spallZ[det][1])*(spallZ[det][0] - spallZ[det][1]))/1000.0,(spallTrigNanoSec[det][0] - TrigNanoSec)/1.0e3);
      m_fnPosInt_PT2Mu[det][tag]->Fill(TMath::Sqrt((spallX[det][0] - spallX[det][1])*(spallX[det][0] - spallX[det][1])+(spallY[det][0] - spallY[det][1])*(spallY[det][0] - spallY[det][1]) +(spallZ[det][0] - spallZ[det][1])*(spallZ[det][0] - spallZ[det][1]))/1000.0,TMath::Abs((spallTrigNanoSec[det][0] - TrigNanoSec)/1.0e3));

}

void FastNeuAna::SlaveTerminate()
{

}

void FastNeuAna::Terminate()
{
  cout<< "Total event: "<< m_evt<< endl;
  cout<< "Total fn: "<< m_Fn<< endl;
  std::cout<<"c1num  : -"<<c1num<<" =" <<m_Fn-c1num <<endl;
  std::cout<<"c2num  : -"<<c2num<<" =" <<m_Fn-c1num-c2num <<endl;
  std::cout<<"c3num  : -"<<c3num<<" =" <<m_Fn-c1num-c2num-c3num <<endl;
  std::cout<<"c4num  : -"<<c4num<<" =" <<m_Fn-c1num-c2num-c3num-c4num <<endl;
  std::cout<<"c5num  : -"<<c5num<<" =" <<m_Fn-c1num-c2num-c3num-c4num-c5num <<endl;

  m_file->Write();
  m_file->Close();
}

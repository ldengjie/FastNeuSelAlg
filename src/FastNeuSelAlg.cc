#include "FastNeuSelAlg.h"
#include "LafKernel/AlgFactory.h"
#include "LafKernel/GlobalVar.h"
#include "LafKernel/PhyEvent/RecReadout.h"
#include "LafKernel/PhyEvent/CalibReadout.h" 
#include <iostream>
#include "TMath.h"
#include "TNtuple.h"
#include <fstream>
#include  <map>

DECLARE_ALGORITHM(FastNeuSelAlg);

FastNeuSelAlg::FastNeuSelAlg(const std::string& name)
             : AlgBase(name)
{ 
    OptionParser::setOption(name,"RunNum",runNum);
    OptionParser::setOption(name,"ShiftTimeFile",shiftTimeFile);


  m_detId             = 0;
  //m_muonE             = 0.;
  m_trigTime           = 0.;
  m_trigSec           = 0;
  m_trigNanoSec       = 0;
  m_nPmt              = 0;
  m_timeToLastIWSMuon = 0.0;

  m_timeLastIWSMuon   = 0.0;
  m_cleanMuon         = 0;

  mp_spallDetId = &m_spallDetId;
  mp_spallDetId->clear();

  mp_spallTrigTime = &m_spallTrigTime;
  mp_spallTrigTime->clear();
  mp_spallTrigSec = &m_spallTrigSec;
  mp_spallTrigSec->clear();
  mp_spallTrigNanoSec = &m_spallTrigNanoSec;
  mp_spallTrigNanoSec->clear();

  mp_spallScaledE = &m_spallScaledE;
  mp_spallScaledE->clear();
  mp_spallEnergy = &m_spallEnergy;
  mp_spallEnergy->clear();

  mp_spallX = &m_spallX;
  mp_spallX->clear();
  mp_spallY = &m_spallY;
  mp_spallY->clear();
  mp_spallZ = &m_spallZ;
  mp_spallZ->clear();
  mp_spallFirstHitTime = &m_spallFirstHitTime;
  mp_spallFirstHitTime->clear();
  mp_spallLastHitTime = &m_spallLastHitTime;
  mp_spallLastHitTime->clear();
 
  mp_spallNPmt = &m_spallNPmt;
  mp_spallNPmt->clear();
  mp_spallMaxQ = &m_spallMaxQ;
  mp_spallMaxQ->clear();
  mp_spallQuadrant = &m_spallQuadrant;
  mp_spallQuadrant->clear();
  mp_spallMaxQ_2inchPMT = &m_spallMaxQ_2inchPMT;
  mp_spallMaxQ_2inchPMT->clear();
  mp_spallColumn_2inchPMT = &m_spallColumn_2inchPMT;
  mp_spallColumn_2inchPMT->clear();
  mp_spallMiddleTimeRMS = &m_spallMiddleTimeRMS;
  mp_spallMiddleTimeRMS->clear();
//  mp_spallTimePSD = &m_spallTimePSD;
//  mp_spallTimePSD->clear();
//  mp_spallTimePSD1 = &m_spallTimePSD1;
//  mp_spallTimePSD1->clear();
//  mp_spallQ1 = &m_spallQ1;
//  mp_spallQ1->clear();
//  mp_spallQ2 = &m_spallQ2;
//  mp_spallQ2->clear();
//  mp_spallQ3 = &m_spallQ3;
//  mp_spallQ3->clear();

  for(int det = 1; det <= GlobalVar::NumADs; det++)
  {
    m_spallEventBuffer[det].clear();
  }
}

bool FastNeuSelAlg::initialize()
{
  m_buffer = dynamic_cast<PhyEventBuf*>(service("Cycler"));

  // =======================================================================================
  m_IWSMuonTree = ntupleSvc()->bookTree("FILE2/IWSMuonTree/IWSMuonTree", "IWSMuonTree");

  m_IWSMuonTree->Branch("ShiftTime",             &shiftTime,             "shiftTime/D");
  m_IWSMuonTree->Branch("RunNum",             &runNum,             "RunNum/I");
  m_IWSMuonTree->Branch("FileNum",             &fileNum,             "FileNum/I");
  
  //Set Branch of IWSMuon
  m_IWSMuonTree->Branch("DetId",             &m_detId,             "DetId/I");
//  m_IWSMuonTree->Branch("MuonE",             &m_muonE,             "MuonE/F");
  m_IWSMuonTree->Branch("TrigTime",           &m_trigTime,           "TrigTime/D");
  m_IWSMuonTree->Branch("TrigSec",           &m_trigSec,           "TrigSec/I");
  m_IWSMuonTree->Branch("TrigNanoSec",       &m_trigNanoSec,       "TrigNanoSec/I");
  m_IWSMuonTree->Branch("NPmt",              &m_nPmt,              "NPmt/I");
  m_IWSMuonTree->Branch("TimeToLastIWSMuon", &m_timeToLastIWSMuon, "TimeToLastIWSMuon/D");
  m_IWSMuonTree->Branch("CleanMuon",         &m_cleanMuon,         "CleanMuon/I");
  m_IWSMuonTree->Branch("FirstHitTime",         &m_firstHitTime,         "FirstHistTime/I");
  m_IWSMuonTree->Branch("LastHitTime",         &m_lastHitTime,         "LastHistTime/I");

  //Set Branch of SpallEvents
  m_IWSMuonTree->Branch("SpallDetId",       "vector<int>",   &mp_spallDetId,       32000, 99);
  m_IWSMuonTree->Branch("SpallTrigTime",     "vector<double>",   &mp_spallTrigTime,     32000, 99);
  m_IWSMuonTree->Branch("SpallTrigSec",     "vector<int>",   &mp_spallTrigSec,     32000, 99);
  m_IWSMuonTree->Branch("SpallTrigNanoSec", "vector<int>",   &mp_spallTrigNanoSec, 32000, 99);
  m_IWSMuonTree->Branch("SpallScaledE",     "vector<float>", &mp_spallScaledE,     32000, 99);
  m_IWSMuonTree->Branch("SpallEnergy",      "vector<float>", &mp_spallEnergy,      32000, 99);
  m_IWSMuonTree->Branch("SpallX",           "vector<float>", &mp_spallX,           32000, 99);
  m_IWSMuonTree->Branch("SpallY",           "vector<float>", &mp_spallY,           32000, 99);
  m_IWSMuonTree->Branch("SpallZ",           "vector<float>", &mp_spallZ,           32000, 99);
  m_IWSMuonTree->Branch("SpallFirstHitTime",     "vector<int>",    &mp_spallFirstHitTime,         32000, 99);
  m_IWSMuonTree->Branch("SpallLastHitTime",     "vector<int>",    &mp_spallLastHitTime,       32000, 99);  

  m_IWSMuonTree->Branch("SpallNPmt",            "vector<int>",   &mp_spallNPmt,            32000, 99);
  m_IWSMuonTree->Branch("SpallMaxQ",            "vector<float>", &mp_spallMaxQ,            32000, 99);
  m_IWSMuonTree->Branch("SpallQuadrant",        "vector<float>", &mp_spallQuadrant,        32000, 99);
  m_IWSMuonTree->Branch("SpallMaxQ_2inchPMT",   "vector<float>", &mp_spallMaxQ_2inchPMT,   32000, 99);
  m_IWSMuonTree->Branch("SpallColumn_2inchPMT", "vector<int>",   &mp_spallColumn_2inchPMT, 32000, 99);
  m_IWSMuonTree->Branch("SpallMiddleTimeRMS",   "vector<float>", &mp_spallMiddleTimeRMS,   32000, 99);
//  m_IWSMuonTree->Branch("SpallTimePSD",         "vector<float>", &mp_spallTimePSD,         32000, 99);
//  m_IWSMuonTree->Branch("SpallTimePSD1",        "vector<float>", &mp_spallTimePSD1,        32000, 99);
//  m_IWSMuonTree->Branch("SpallQ1",              "vector<float>", &mp_spallQ1,              32000, 99); 
//  m_IWSMuonTree->Branch("SpallQ2",              "vector<float>", &mp_spallQ2,              32000, 99);
//  m_IWSMuonTree->Branch("SpallQ3",              "vector<float>", &mp_spallQ3,              32000, 99);
    ifstream ifile;
    std::cout<<"shiftTimeFile  : "<<shiftTimeFile<<endl;
    ifile.open(shiftTimeFile.c_str());
    if( ifile.good())
    {
	    while( !ifile.eof())
	    {
	        ifile>>runIndex;
	        ifile>>fileIndex;
	        ifile>>shiftTimeStruct.AD1;
	        ifile>>shiftTimeStruct.AD2;
	        ifile>>shiftTimeStruct.AD3;
	        ifile>>shiftTimeStruct.AD4;
	        ifile>>shiftTimeStruct.IWS;
	        ifile>>shiftTimeStruct.OWS;
	        ifile>>shiftTimeStruct.RPC;
	        shiftTimeMap[fileIndex]=shiftTimeStruct;
	    }
	    map<int,ShiftTimeStruct>::iterator it;
	    for( it=shiftTimeMap.begin() ; it!=shiftTimeMap.end() ; it++ )
	    {
	        std::cout<<it->first <<" : " <<it->second.AD1<<" "<<it->second.AD2<<" "<<it->second.AD3<<" "<<it->second.AD4<<" "<<it->second.IWS<<" "<<it->second.OWS<<" "<<it->second.RPC<<endl;
	        
	    }
    }else
    {
        std::cout<<shiftTimeFile <<"doesn't exists "<<endl;
    }
    ifile.close();
    
  std::cout<<"runNum : "<<runNum<<endl;
  return true;
}
bool FastNeuSelAlg::execute()
{
  PhyEvent* event = m_buffer->curEvt();
  
  //if(event->m_entry%100000==0) cout<< "-----------------entry: "<< event->m_entry<< " --------------------"<< endl;
  
  //Keep the current Event always being IWSMuon
  //cout<<"here det  : "<<event->m_det<<" energy : "<<event->energy()<<endl;
  if(5 != event->m_det || event->m_muonTag != PhyEvent::kWpMuon) 
  {
    return true;
  }
  //Check in the windows: IWSMuon(-202us, 202us) and make sure the effective IWSMuon
  //
  //Check in the windows: IWSMuon(-202us, 402us) and make sure the effective IWSMuon 2012.4.10
  bool ifBreak = false;
  bool ifFill  = false;
  PhyEventBuf::Iterator cit = m_buffer->current();
  for(PhyEventBuf::Iterator pit = m_buffer->begin(); pit != m_buffer->end(); pit++)
  {
    if(cit == pit) continue;

    PhyEvent* _evt = *pit;
    //cout<<"here det  : "<<_evt->m_det<<" energy : "<<_evt->energy()<<endl;
    if((5 == _evt->m_det && _evt->m_muonTag == PhyEvent::kWpMuon) ||
       _evt->m_muonTag == PhyEvent::kAdMuon ||
       _evt->m_muonTag == PhyEvent::kShowerMuon /*||
       (_evt->isAD() && event->m_trigTime - _evt->m_trigTime > 3.e-7)*/)
    {
        //cout<<"here det  : "<<_evt->m_det<<" energy : "<<_evt->energy()<<endl;
      ifBreak = true;
      break;
    }
    else //fill the fast neutron buffer for each AD
    {
        //cout<< "Not break yet!"<< endl;
        //cout<<"det  : "<< _evt->m_det<<endl;
      if(5 > _evt->m_det &&
         (/*2.e-6 > event->m_trigTime - _evt->m_trigTime &&*/ 4.e-4 > _evt->m_trigTime - event->m_trigTime) )
      {
          //cout<< "The detector Id: "<< _evt->m_det<< endl;
	//if(2.e-6 > event->m_trigTime - _evt->m_trigTime || 4.e-4 > _evt->m_trigTime - event->m_trigTime)
        m_spallEventBuffer[_evt->m_det].push_back(_evt);
      }else
      {
      }

    }
  }

  if(true == ifBreak)
  {
    for(int det = 1; det <= GlobalVar::NumADs; det++)
    {
      m_spallEventBuffer[det].clear(); 
    }
    return true;
  }else //select the fast neutron candidate
  {
    //m_timeLastIWSMuon = event->m_trigTime.AsDouble();
    for(int det = 1; det <= GlobalVar::NumADs; det++)
    {
      if(2 != m_spallEventBuffer[det].size())
      {
          //cout<<"size  : "<<m_spallEventBuffer[det].size()<<endl;
         m_spallEventBuffer[det].clear();
         continue;
      }else if((event->m_trigTime - m_spallEventBuffer[det][0]->m_trigTime > 2.e-6 && 
               event->m_trigTime - m_spallEventBuffer[det][0]->m_trigTime < 2.02e-4) ||
	      (m_spallEventBuffer[det][1]->m_trigTime - event->m_trigTime > 2.e-4 &&
               m_spallEventBuffer[det][1]->m_trigTime - event->m_trigTime < 4.e-4) ||  m_spallEventBuffer[det][1]->energy() >12.0
	     )
      {       
         m_spallEventBuffer[det].clear();
         continue;
      }
      else
      {
        //PhyEvent* delayEvent = m_spallEventBuffer[det][1];
        //if(3.e-7 < delayEvent->m_trigTime - event->m_trigTime)
        //{
           fillCoinc(det);
           ifFill = true;
           //cout<<"here "<<endl;
        //}
        
        m_spallEventBuffer[det].clear();
      }
    }

    if(true == ifFill)
    {
      fillIWSMuon(event);
      m_IWSMuonTree->Fill();
      //cout<<"Fill here "<<endl;
      cleanPara();
    }
   
    return true;
  }
}

bool FastNeuSelAlg::finalize()
{
    std::cout<<"fileNum : "<<fileNum<<endl;
    return true;

}

void FastNeuSelAlg::getShiftTime(PhyEvent* curEvt)
{

  if( fileName!=curEvt->getFileName() )
  {
    if(fileName!="") std::cout<<"fileNum : "<<fileNum<<endl;
  }
  fileName=curEvt->getFileName();
  fileSize=fileName.size();
  fileNum=atoi(fileName.substr(fileSize-9,4).c_str());
  map<int,ShiftTimeStruct>::iterator it = shiftTimeMap.find(fileNum);
  if( it != shiftTimeMap.end() )
  {
    if( curEvt->m_det==1 )
    {
        shiftTime=it->second.AD1;
    }
    if( curEvt->m_det==2 )
    {
        shiftTime=it->second.AD2;
    }
    if( curEvt->m_det==3 )
    {
        shiftTime=it->second.AD3;
    }
    if( curEvt->m_det==4 )
    {
        shiftTime=it->second.AD4;
    }
    if( curEvt->m_det==5 )
    {
        shiftTime=it->second.IWS;
    }
    if( curEvt->m_det==6)
    {
        shiftTime=it->second.OWS;
    }
    if( curEvt->m_det==7 )
    {
        shiftTime=it->second.RPC;
    }
  }else
  {
    shiftTime=9999;
  }
}

void FastNeuSelAlg::fillCoinc(int detId)
{
  //cout<< "In fillCoinc"<< endl;
  getShiftTime(m_spallEventBuffer[detId][0]);
  for(vector<PhyEvent*>::size_type i = 0; i < m_spallEventBuffer[detId].size(); i++)
  {
    mp_spallDetId->push_back(detId);
    mp_spallTrigTime->push_back(m_spallEventBuffer[detId][i]->m_trigTime.AsDouble());
    mp_spallTrigSec->push_back(m_spallEventBuffer[detId][i]->m_trigTime.GetSec());
    mp_spallTrigNanoSec->push_back(m_spallEventBuffer[detId][i]->m_trigTime.GetNanoSec());
    mp_spallScaledE->push_back(m_spallEventBuffer[detId][i]->energy());
    mp_spallEnergy->push_back(m_spallEventBuffer[detId][i]->m_energy);
    //cout<< "Address: "<< mp_spallX<< endl;
    //cout<< "X position: "<< m_spallEventBuffer[detId][i]->m_x<< endl;
    //cout<< "Spall vector size: "<< mp_spallX->size()<< endl;
    mp_spallX->push_back(m_spallEventBuffer[detId][i]->m_x);
    //cout<< "error!"<< endl;
    mp_spallY->push_back(m_spallEventBuffer[detId][i]->m_y);
    //cout<< "error!"<< endl;
    mp_spallZ->push_back(m_spallEventBuffer[detId][i]->m_z);
    getADhitTime(m_spallEventBuffer[detId][i]);
    //std::cout<<"firstTime  : "<<firstTime<<endl;
    //std::cout<<"lastTime  : "<<lastTime<<endl;
    mp_spallFirstHitTime->push_back(firstTime);
    mp_spallLastHitTime->push_back(lastTime);

    //cout<< "error!"<< endl;
    mp_spallNPmt->push_back(m_spallEventBuffer[detId][i]->m_nPmt);
    mp_spallMaxQ->push_back(m_spallEventBuffer[detId][i]->m_maxQ);
    mp_spallQuadrant->push_back(m_spallEventBuffer[detId][i]->m_quadrant);
    mp_spallMaxQ_2inchPMT->push_back(m_spallEventBuffer[detId][i]->m_maxQ_2inchPMT);
    mp_spallColumn_2inchPMT->push_back(m_spallEventBuffer[detId][i]->m_Column_2inchPMT);
    mp_spallMiddleTimeRMS->push_back(m_spallEventBuffer[detId][i]->m_MiddleTimeRMS);
//    mp_spallTimePSD->push_back(m_spallEventBuffer[detId][i]->m_time_PSD);
//    mp_spallTimePSD1->push_back(m_spallEventBuffer[detId][i]->m_time_PSD1);
//    mp_spallQ1->push_back(m_spallEventBuffer[detId][i]->m_Q1);
//    mp_spallQ2->push_back(m_spallEventBuffer[detId][i]->m_Q2);
//    mp_spallQ3->push_back(m_spallEventBuffer[detId][i]->m_Q3);
  }
}

void FastNeuSelAlg::fillIWSMuon(PhyEvent* curEvt)
{
  //cout<< "In fillIWSMuon"<< endl;
  m_detId             = curEvt->m_det;
  //m_muonE             = curEvt->m_energy;
  m_trigTime           = curEvt->m_trigTime.AsDouble();
  m_trigSec           = curEvt->m_trigTime.GetSec();
  m_trigNanoSec       = curEvt->m_trigTime.GetNanoSec();
  m_nPmt              = curEvt->m_nPmt;
  m_timeToLastIWSMuon = curEvt->m_trigTime.AsDouble() - m_timeLastIWSMuon;
  m_timeLastIWSMuon   = curEvt->m_trigTime.AsDouble();
  getWPhitTime(curEvt);
  //std::cout<<"m_firstHitTime  : "<<m_firstHitTime<<endl;
  //std::cout<<"m_lastHitTime  : "<<m_lastHitTime<<endl;
}
void FastNeuSelAlg::getADhitTime(PhyEvent* curEvt)
{
        int peakTime=30; 
        firstTime=0;
        lastTime=-10000;
        int hitTime[8][26][2];
        int isGood[8][26];
        CalibReadout* calib = curEvt->get<CalibReadout>("Event/CalibReadout/CalibReadoutHeader");
        
        if( calib->nHitsAD == 0 )
        {
            std::cout<<"someting is wrong,admuon's nHitsAD ==0 "<<endl;
        }
        for( int i=0 ; i<8 ; i++ )
        {
            for( int j=1 ; j<25 ; j++ )
            {
                hitTime[i][j][0]=0;
                hitTime[i][j][1]=0;
                isGood[i][j]=0;
            }
            hitTime[i][0][0]=0;
            hitTime[i][0][1]=0;
            isGood[i][0]=1;
            hitTime[i][25][0]=0;
            hitTime[i][25][1]=0;
            isGood[i][25]=1;

        }
        for( unsigned int i=0 ; i<calib->nHitsAD ; i++ )
        {
            if(hitTime[calib->ring.at(i)-1][calib->column.at(i)][0]==0)
            {
                hitTime[calib->ring.at(i)-1][calib->column.at(i)][0]=(int)calib->timeAD.at(i);
                isGood[calib->ring.at(i)-1][calib->column.at(i)]=1;
            }
            hitTime[calib->ring.at(i)-1][calib->column.at(i)][1]=(int)calib->timeAD.at(i);
        }
        for( int i=0 ; i<8 ; i++ )
        {
            for( int j=1 ; j<25 ; j++ )
            {
               if(isGood[i][j]==1)
               {
                    if(!(TMath::Abs(hitTime[i][j][0]-hitTime[i][j-1][0])>peakTime && TMath::Abs(hitTime[i][j][0]-hitTime[i][j+1][0])>peakTime) &&  hitTime[i][j][0]<firstTime )
                    {
                        firstTime=hitTime[i][j][0];
                    }
                    if( hitTime[i][j][1]>lastTime )
                    {
                        lastTime=hitTime[i][j][1];
                    }
               }
            }
        }
}

void FastNeuSelAlg::getWPhitTime(PhyEvent* curEvt)
{
        m_firstHitTime=0;
        m_lastHitTime=-10000;
        int hitTime[10][27][2];
        int isGood[10][27];
        CalibReadout* calib = curEvt->get<CalibReadout>("Event/CalibReadout/CalibReadoutHeader");
        
        if( calib->nHitsPool == 0 )
        {
            std::cout<<"someting is wrong,admuon's nHitsPool ==0 "<<endl;
        }

        for( int i=0 ; i<10 ; i++ )
        {
            for( int j=1 ; j<26 ; j++ )
            {
                hitTime[i][j][0]=0;
                hitTime[i][j][1]=0;
                isGood[i][j]=0;
            }
            hitTime[i][0][0]=0;
            hitTime[i][0][1]=0;
            isGood[i][0]=1;
            hitTime[i][26][0]=0;
            hitTime[i][26][1]=0;
            isGood[i][26]=1;

        }
        for( unsigned int i=0 ; i<calib->nHitsPool ; i++ )
        {
            //std::cout<<"(int)calib->timePool.at(i)  : "<<calib->timePool.at(i)<<endl;
            if(hitTime[calib->wallNumber.at(i)-1][calib->wallSpot.at(i)][0]==0)
            {
                hitTime[calib->wallNumber.at(i)-1][calib->wallSpot.at(i)][0]=(int)calib->timePool.at(i);
                isGood[calib->wallNumber.at(i)-1][calib->wallSpot.at(i)]=1;
            }
            hitTime[calib->wallNumber.at(i)-1][calib->wallSpot.at(i)][1]=(int)calib->timePool.at(i);
        }
        for( int i=0 ; i<10 ; i++ )
        {
            for( int j=1 ; j<26 ; j++ )
            {
               if(isGood[i][j]==1 )
               {
                    if( hitTime[i][j][0]<m_firstHitTime )
                    {
                        m_firstHitTime=hitTime[i][j][0];
                    }
                    if(hitTime[i][j][1]>m_lastHitTime )
                    {
                        m_lastHitTime=hitTime[i][j][1];
                    }
               }
            }
        }
}
void FastNeuSelAlg::cleanPara()
{
  //cout<< "In cleanPara"<< endl;
  m_detId = 0;
  //m_muonE = 0.;
  m_trigSec = 0;
  m_trigTime = 0;
  m_trigNanoSec = 0;
  m_nPmt = 0;
  m_timeToLastIWSMuon = 0.0;
  m_cleanMuon = 0;
  m_firstHitTime=0;
  m_lastHitTime=0;


  mp_spallDetId->clear();

  mp_spallTrigSec->clear();
  mp_spallTrigTime->clear();
  mp_spallTrigNanoSec->clear();

  mp_spallScaledE->clear();
  mp_spallEnergy->clear();

  mp_spallX->clear();
  mp_spallY->clear();
  mp_spallZ->clear();
  mp_spallFirstHitTime->clear();
  mp_spallLastHitTime->clear();

  mp_spallNPmt->clear();
  mp_spallMaxQ->clear();
  mp_spallQuadrant->clear();
  mp_spallMaxQ_2inchPMT->clear();
  mp_spallColumn_2inchPMT->clear();
  mp_spallMiddleTimeRMS->clear();
  //mp_spallTimePSD->clear();
  //mp_spallTimePSD1->clear();
  //mp_spallQ1->clear();
  //mp_spallQ2->clear();
  //mp_spallQ3->clear();
}

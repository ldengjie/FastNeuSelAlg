#include "IntervalTime.h"
//IWS AD1 AD2
int inwhere(float x,float y,float z)
{
    if( x>-2000)
    {
        return 1;
    }else
    {
        return 2;
    }
}
Event dumpEvent(int EventID,float x,float y,float z,float dE,float quenchedDepE,float time,int det)
{
    Event eventTmp;
    eventTmp.EventID=EventID;
    eventTmp.x=x;
    eventTmp.y=y;
    eventTmp.z=z;
    eventTmp.dE=dE;
    eventTmp.quenchedDepE=quenchedDepE;
    eventTmp.time=time;
    eventTmp.det=det;
    return eventTmp;
}
bool printEvt(Event evt)
{
    cout<<" EventID : "<<evt.EventID<<endl;
    cout<<" x : "<<evt.x<<" mm"<<endl;
    cout<<" y : "<<evt.y<<" mm"<<endl;
    cout<<" z : "<<evt.z<<" mm"<<endl;
    cout<<" dE : "<<evt.dE<<" MeV"<<endl;
    cout<<" quenchedDepE : "<<evt.quenchedDepE<<" MeV"<<endl;
    cout<<" time : @"<<evt.time<<" us"<<endl;
    TString detStr="AD";
    if( evt.det==5 )
    {
        detStr="IWS";
    }else
    {
        detStr+=evt.det;
    }
    cout<<" det : "<<evt.det<<" ["<<detStr<<"]"<<endl;
    return 1;
}
bool dump(vector<Event> adBuf)
{
    //cout<<"here is dump() size="<<adBuf.size()<<endl;
    if( adBuf.size()==2 )
    {
        if( adBuf[0].quenchedDepE<200.&&adBuf[0].quenchedDepE>0.7&&adBuf[1].quenchedDepE<12.&&adBuf[1].quenchedDepE>6.&&(adBuf[1].time-adBuf[0].time>1) )
        {
            fnPair.push_back(make_pair(adBuf[0],adBuf[1]));
        }
    }
    return true;

}

bool selectFn()
{
    muonNum++;
    //cout<<"here is selectFn() "<<endl;
    bool canThroughOneAd=0;
    bool throughThisAd[2]={0};
    if( eventBuf.size()>=2 )
    {
        vector<Event> adEventBuf[2];
        for( unsigned int i=0 ; i<eventBuf.size() ; i++ )
        {
            Event _evt=eventBuf[i];
            //1) AD event's energy >0.7MeV
            if(_evt.quenchedDepE<0.7) continue;
            ////2)AD muon,time to IWS muon<100ns
            //if(_evt.quenchedDepE>100&&_evt.det<5&&_evt.time<0.1)
            //2)AD muon,time to IWS muon<2us
            if(_evt.quenchedDepE>100&&_evt.det<5&&_evt.time<2)
            {
                if( canThroughOneAd )
                {
                    throughThisAd[_evt.det-1]=1;

                }else
                {
                    eventBuf.clear();
                    return false; 
                }
            } 
            //only loop AD events
            if(_evt.det>4) continue;
            if( !throughThisAd[_evt.det-1] )
            {
                //3) muon cut <400us ???
                if( _evt.time<400)
                {
                    if( adEventBuf[_evt.det-1].size()!=0 )
                    {
                        //4)timeInterval>200us
                        if( _evt.time-adEventBuf[_evt.det-1][adEventBuf[_evt.det-1].size()-1].time>200 )
                        {
                            //select fn
                            dump(adEventBuf[_evt.det-1]);
                            adEventBuf[_evt.det-1].clear();
                        }
                    }
                    adEventBuf[_evt.det-1].push_back(_evt);

                }else
                {
                    break;
                }

            }

        }
        //select fn
        for( int i=0 ; i<2 ; i++ )
        {
            if( !throughThisAd[i] )
            {
                dump(adEventBuf[i]);
                adEventBuf[i].clear();
            }
        }


    }
    eventBuf.clear();
    return true;
}

int main(int argc,char* args[])
{
    if(argc!=2) 
    {
        cout<<"wrong file number,please check like './IntervalTime 15'"<<endl;
        return 0;
    }
    int rootNum=atoi(args[1]);
    gInterpreter->EnableAutoLoading();

    cout<<"rootNum : "<<rootNum<<endl;
    int anaStopMuon=0;
    int anaMichelElectron=0;
    int anaFn=0;
    int anaSpa=1;

    float muonMass=105.65;//MeV
    int number=0;

    TH1F* h = new TH1F("stopMuonIntervalTime","stopMuonIntervalTime",400,0,400);
    //
    TH1F* timeIntervalGd = new TH1F("timeIntervalGd","timeIntervalGd",400,0,400);
    TH2F* timeIntervalvsInitEGd= new TH2F("timeIntervalvsInitEGd","timeIntervalvsInitEGd",400,0,400,1000,0,1000);
    TH1F* fnPElessGd=new TH1F("fnPElessGd","fn prompt energy less than 55ns",1000,0,1000);
    TH1F* fnPEmoreGd=new TH1F("fnPEmoreGd","fn prompt energy more than 55ns",1000,0,1000);
    TH1F* fnPEGd=new TH1F("fnPEGd","fn prompt energy",1000,0,1000);
    TH1F* fnInitEGd=new TH1F("fnInitEGd","fnInitEGd",1000,0,1000);
    TH2F* PEvsInitEGd=new TH2F("PEvsInitEGd","PEvsInitEGd",1000,0,1000,1000,0,1000);
    TH2F* PEvstimeIntervalGd=new TH2F("PEvstimeIntervalGd","PEvstimeIntervalGd",1000,0,1000,400,0,400);
    TH2F* PEvsRGd=new TH2F("PEvsRGd","PEvsRGd",1000,0,1000,1000,0,10000);
    TH2F* PEvsZGd=new TH2F("PEvsZGd","PEvsZGd",1000,0,1000,2000,-10000,10000);
    TH2F* PEvsPosTagGd=new TH2F("PEvsPosTagGd","PEvsPosTagGd",1000,0,1000,2,0,2);
    TH1F* PEwithThroughLSGd=new TH1F("PEwithThroughLSGd","PEwithThroughLSGd",1000,0,1000);
    TH1F* PEwithThroughGDGd=new TH1F("PEwithThroughGDGd","PEwithThroughGDGd",1000,0,1000);
    TH1F* fnPEtoyGd=new TH1F("fnPEtoyGd","fn prompt energy",10000,0,1000);
    TH1F* fnInitEtoyGd=new TH1F("fnInitEtoyGd","fnInitEtoyGd",10000,0,1000);

    TH1F* timeIntervalH = new TH1F("timeIntervalH","timeIntervalH",400,0,400);
    TH2F* timeIntervalvsInitEH= new TH2F("timeIntervalvsInitEH","timeIntervalvsInitEH",400,0,400,1000,0,1000);
    TH1F* fnPElessH=new TH1F("fnPElessH","fn prompt energy less than 55ns",1000,0,1000);
    TH1F* fnPEmoreH=new TH1F("fnPEmoreH","fn prompt energy more than 55ns",1000,0,1000);
    TH1F* fnPEH=new TH1F("fnPEH","fn prompt energy",1000,0,1000);
    TH1F* fnInitEH=new TH1F("fnInitEH","fnInitEH",1000,0,1000);
    TH2F* PEvsInitEH=new TH2F("PEvsInitEH","PEvsInitEH",1000,0,1000,1000,0,1000);
    TH2F* PEvstimeIntervalH=new TH2F("PEvstimeIntervalH","PEvstimeIntervalH",1000,0,1000,400,0,400);
    TH2F* PEvsRH=new TH2F("PEvsRH","PEvsRH",1000,0,1000,1000,0,10000);
    TH2F* PEvsZH=new TH2F("PEvsZH","PEvsZH",1000,0,1000,2000,-10000,10000);
    TH2F* PEvsPosTagH=new TH2F("PEvsPosTagH","PEvsPosTagH",1000,0,1000,2,0,2);
    TH1F* PEwithThroughLSH=new TH1F("PEwithThroughLSH","PEwithThroughLSH",1000,0,1000);
    TH1F* PEwithThroughGDH=new TH1F("PEwithThroughGDH","PEwithThroughGDH",1000,0,1000);
    TH1F* fnPEtoyH=new TH1F("fnPEtoyH","fn prompt energy",10000,0,1000);
    TH1F* fnInitEtoyH=new TH1F("fnInitEtoyH","fnInitEtoyH",10000,0,1000);

    TH1F* fnInitE=new TH1F("fnInitE","fnInitE",10000,0,1000);
    TH1F* fnPEtotal=new TH1F("fnPEtotal","fn prompt energy",1000,0,1000);
    TH1F* fnPEtoytotal=new TH1F("fnPEtoytotal","fn prompt energy",10000,0,1000);
    TH1F* posInterval=new TH1F("posInterval","posInterval",1000,0,10000);
    TH1F* EbeforeLS=new TH1F("EbeforeLS","EbeforeLS",10000,0,1000);
    TH1F* ELossbeforeLS=new TH1F("ELossbeforeLS","ELossbeforeLS",10000,0,1000);
    TH1F* timeIntervalAllfn = new TH1F("timeIntervalAllfn","timeIntervalAllfn",400,0,400);
    TH2F* timeIntervalAllfnvsInitE= new TH2F("timeIntervalAllfnvsInitE","timeIntervalAllfnvsInitE",400,0,400,1000,0,1000);

    TH1F* h3 = new TH1F("eIntervalTime","eIntervalTime",400,0,400);

    shiftTime=0. ;
    runNum=0 ;
    fileNum=0 ;
    m_detId =0 ;
    m_trigTime =0. ;
    m_trigSec =0 ;
    m_trigNanoSec =0 ;
    m_nPmt =0 ;
    m_timeToLastIWSMuon=0. ;
    m_cleanMuon =0 ;
    m_firstHitTime =0 ;
    m_lastHitTime =0 ;
    for( int i=0 ; i<2 ; i++ )
    {
        mp_spallDetId.push_back(0) ;
        mp_spallTrigTime.push_back(0.) ;
        mp_spallTrigSec.push_back(0) ;
        mp_spallEnergy.push_back(0.) ;

        mp_spallX.push_back(0.) ;
        mp_spallY.push_back(0.) ;
        mp_spallZ.push_back(0.) ;
        mp_spallScaledE.push_back(0.) ;
        mp_spallTrigNanoSec.push_back(0) ;
        mp_spallNPmt.push_back(0) ;

        mp_spallFirstHitTime.push_back(0) ;
        mp_spallLastHitTime.push_back(0) ;
        mp_spallMaxQ.push_back(0.) ;
        mp_spallQuadrant.push_back(0.) ;
        mp_spallMaxQ_2inchPMT.push_back(0.) ;
        mp_spallColumn_2inchPMT.push_back(0) ;
        mp_spallMiddleTimeRMS.push_back(0.) ;
    }


    TFile* fnFile=new TFile(Form("MCdata/fn_%d.root",rootNum),"RECREATE");
    fnTree=new TTree("fnTree","fast neutron tree");

    fnTree->Branch("ShiftTime", &shiftTime, "shiftTime/D");
    fnTree->Branch("RunNum", &runNum, "RunNum/I");
    fnTree->Branch("FileNum", &fileNum, "FileNum/I");
    //Set Branch of IWSMuon
    fnTree->Branch("DetId", &m_detId, "DetId/I");
    fnTree->Branch("TrigTime", &m_trigTime, "TrigTime/D");
    fnTree->Branch("TrigSec", &m_trigSec, "TrigSec/I");
    fnTree->Branch("TrigNanoSec", &m_trigNanoSec, "TrigNanoSec/I");
    fnTree->Branch("NPmt", &m_nPmt, "NPmt/I");
    fnTree->Branch("TimeToLastIWSMuon", &m_timeToLastIWSMuon, "TimeToLastIWSMuon/D");
    fnTree->Branch("CleanMuon", &m_cleanMuon, "CleanMuon/I");
    fnTree->Branch("FirstHitTime", &m_firstHitTime, "FirstHistTime/I");
    fnTree->Branch("LastHitTime", &m_lastHitTime, "LastHistTime/I");
    //Set Branch of SpallEvents
    fnTree->Branch("SpallDetId", "vector<int>", &mp_spallDetId, 32000, 99);
    fnTree->Branch("SpallTrigTime", "vector<double>", &mp_spallTrigTime, 32000, 99);
    //fnTree->Branch("SpallTrigSec", "vector<int>", &mp_spallTrigSec, 32000, 99);
    fnTree->Branch("SpallTrigNanoSec", "vector<int>", &mp_spallTrigNanoSec, 32000, 99);
    fnTree->Branch("SpallScaledE", "vector<float>", &mp_spallScaledE, 32000, 99);
    fnTree->Branch("SpallEnergy", "vector<float>", &mp_spallEnergy, 32000, 99);

    fnTree->Branch("SpallX", "vector<float>", &mp_spallX, 32000, 99);
    fnTree->Branch("SpallY", "vector<float>", &mp_spallY, 32000, 99);
    fnTree->Branch("SpallZ", "vector<float>", &mp_spallZ, 32000, 99);
    fnTree->Branch("SpallFirstHitTime", "vector<int>", &mp_spallFirstHitTime, 32000, 99);
    fnTree->Branch("SpallLastHitTime", "vector<int>", &mp_spallLastHitTime, 32000, 99); 
    fnTree->Branch("SpallNPmt", "vector<int>", &mp_spallNPmt, 32000, 99);
    fnTree->Branch("SpallMaxQ", "vector<float>", &mp_spallMaxQ, 32000, 99);
    fnTree->Branch("SpallQuadrant", "vector<float>", &mp_spallQuadrant, 32000, 99);
    fnTree->Branch("SpallMaxQ_2inchPMT", "vector<float>", &mp_spallMaxQ_2inchPMT, 32000, 99);
    fnTree->Branch("SpallColumn_2inchPMT", "vector<int>", &mp_spallColumn_2inchPMT, 32000, 99);
    fnTree->Branch("SpallMiddleTimeRMS", "vector<float>", &mp_spallMiddleTimeRMS, 32000, 99);

    for( int i=1 ; i<rootNum+1; i++ )
    {

        TString nameStr=Form("/publicfs/dyb/data/userdata/dyboffline/liuyb/MuonSimulation/Dyb/sim_%06d.root",i);
        if( i%100==0 )
        {
            std::cout<<"filename : "<<nameStr<<endl;
        } 
        TFile* f= new TFile(nameStr);
        if( f->IsZombie() )
        {
            std::cout<<"not exist "<<endl;
        }else
        {
            TTree* st=(TTree*)f->Get("Spallation");
            int stnum=st->GetEntries();
            int sEventID;
            float sx;
            float sy;
            float sz;
            float sdE;
            float stime;
            float squenchedDepE;
            st->SetBranchAddress("EventID",&sEventID);
            st->SetBranchAddress("x",&sx);
            st->SetBranchAddress("y",&sy);
            st->SetBranchAddress("z",&sz);
            st->SetBranchAddress("dE",&sdE);
            st->SetBranchAddress("time",&stime);
            st->SetBranchAddress("quenchedDepE",&squenchedDepE);

            TTree* et= (TTree*)f->Get("MichelElectron");
            int etnum=et->GetEntries();
            Int_t eEventID;
            float eKineE;
            float eMichelLocalTime;
            vector<TString>* eVolume = 0;
            et->SetBranchAddress("EventID",&eEventID);
            et->SetBranchAddress("VolName",&eVolume);
            et->SetBranchAddress("KineE",&eKineE);
            et->SetBranchAddress("MichelLocalTime",&eMichelLocalTime);

            TTree* mt= (TTree*)f->Get("Muon");
            int mtnum=mt->GetEntries();
            float muonInitTime;
            Int_t muonEventID;
            float muonTrackLength[100];
            float muonInitKineE;
            float muonQuenchedTotalEnergyDep[100];
            mt->SetBranchAddress("InitTime",&muonInitTime);
            mt->SetBranchAddress("EventID",&muonEventID);
            mt->SetBranchAddress("InitKineE",&muonInitKineE);
            mt->SetBranchAddress("TrackLength",muonTrackLength);
            mt->SetBranchAddress("QuenchedTotalEnergyDep",muonQuenchedTotalEnergyDep);
            //mt->SetBranchAddress("NumOfNeutron",&NumOfNeutron);

            TTree* t= (TTree*)f->Get("Neutron");
            int tnum=t->GetEntries();
            Int_t nNum=0;
            float intervalTime;
            vector<TString>* GenVolume = 0;
            vector<TString>* ColliVolume = 0;
            vector<TString>* CapTargetName=0;
            vector<TString>* CapVolumeName=0;
            float ColliEloss[100];
            float ColliTime[100];
            float ColliLocalX[100];
            float ColliLocalY[100];
            float ColliLocalZ[100];
            float BeforeColliKineE[100];
            Int_t ColliNum=0;
            Int_t EventID;
            float InitTime;
            float InitKineE;
            float CapGammaESum;
            float CapTime;
            float CapLocalX;
            float CapLocalY;
            float CapLocalZ;
            float InitLocalX;
            float InitLocalY;
            float InitLocalZ;
            t->SetBranchAddress("InitTime",&InitTime);
            t->SetBranchAddress("EventID",&EventID);
            t->SetBranchAddress("ColliEloss",ColliEloss);
            t->SetBranchAddress("BeforeColliKineE",BeforeColliKineE);
            t->SetBranchAddress("GenVolume",&GenVolume);
            t->SetBranchAddress("ColliVolume",&ColliVolume);
            t->SetBranchAddress("ColliNum",&ColliNum);
            t->SetBranchAddress("ColliTime",ColliTime);
            t->SetBranchAddress("ColliLocalX",ColliLocalX);
            t->SetBranchAddress("ColliLocalY",ColliLocalY);
            t->SetBranchAddress("ColliLocalZ",ColliLocalZ);
            t->SetBranchAddress("InitKineE",&InitKineE);
            t->SetBranchAddress("CapGammaESum",&CapGammaESum);
            t->SetBranchAddress("CapTargetName",&CapTargetName);
            t->SetBranchAddress("CapVolumeName",&CapVolumeName);
            t->SetBranchAddress("CapTime",&CapTime);
            t->SetBranchAddress("CapLocalX",&CapLocalX);
            t->SetBranchAddress("CapLocalY",&CapLocalY);
            t->SetBranchAddress("CapLocalZ",&CapLocalZ);
            t->SetBranchAddress("InitLocalX",&InitLocalX);
            t->SetBranchAddress("InitLocalY",&InitLocalY);
            t->SetBranchAddress("InitLocalZ",&InitLocalZ);

            map<int,int> muonIndex;
            for( int u=0 ; u<mtnum ; u++ )
            {
                mt->GetEntry(u);
                muonIndex.insert(std::pair<int,int>(muonEventID,u));
            }
            //Spallation
            if( anaSpa )
            {
                //event constructor
                int _eventID=0;
                float _x=0.;
                float _y=0.;
                float _z=0.;
                float _dE=0.;
                float _quenchedDepE=0.;
                float _time=0.;
                float _relTime=0.;
                int _det=999;

                for( int i=0 ; i<stnum ; i++ )
                {
                    st->GetEntry(i);
                    int detTmp=inwhere(sx,sy,sz);
                    //new event ,including "new muon"
                    if( _eventID!=0&&(sEventID!=_eventID|| stime*1000>100 || (_det!=detTmp&&_det!=999)))
                    {
                        Event eventTmp=dumpEvent(_eventID,_x,_y,_z,_dE,_quenchedDepE,_time,_det);
                        eventBuf.push_back(eventTmp);
                        _dE=0.;
                        _quenchedDepE=0.;
                    }
                    //new muon
                    if(sEventID!=_eventID )
                    {
                        //select fn from eventBuf
                        fnPair.clear();
                        selectFn();
                        if( !fnPair.empty() )
                        {
                            for( unsigned int k=0 ; k<fnPair.size() ; k++ )
                            {
                                //bool isMichelEletron=true;
                                bool delayedIsNetron=false;
                                string delayedCapVol;
                                float eventTag=6.; //fn:1 DoubleNeutron:2 MichelEletron:3 CornerMuon:4 other:5
                                float eventFirstHitTime=0.;//us
                                float eventFirstHitTimeAllNeutron=0.;//us
                                mt->GetEntry(muonIndex[fnPair[k].first.EventID]);
                                int NumOfNeutron=0;
                                //int NumOfMichelElectron=0;
                                vector<Event> mcNeutronList;
                                vector<Event> mcMichelElectronList;

                                //if( NumOfNeutron>0/*&&muonTrackLength[3*fnPair[k].first.det-1]=0.*/)//this muon doesn't pass through AD
                                //{
                                float pFTfromDN=0.;//first hit time of prompt signal that from this Delayed Signal Neutron
                                float pEfromDN=0.;//energy of prompt signal that from this Delayed Signal Neutron
                                float pEfromAN=0.;//energy of prompt signal that from all Neutron
                                for( int r=0 ; r<tnum ; r++ )
                                {
                                    t->GetEntry(r);
                                    if( muonEventID==EventID )
                                    {
                                        if( CapGammaESum>0 )
                                        {
                                            NumOfNeutron++;
                                            Event mcNeutronEvt;
                                            mcNeutronEvt.dE=CapGammaESum;
                                            mcNeutronEvt.time=CapTime;//us
                                            mcNeutronEvt.capVol=(*CapVolumeName)[0];
                                            mcNeutronEvt.genVol=(*GenVolume)[0];
                                            mcNeutronList.push_back(mcNeutronEvt);
                                            for( int s=0 ; s<ColliNum ; s++ )
                                            {
                                                //find delayed signal
                                                if( ((*CapTargetName)[0]=="/dd/Materials/Gd_157"||(*CapTargetName)[0]=="/dd/Materials/Gd_155"||(*CapVolumeName)[0]=="SST")&&(fnPair[k].second.time-CapTime<5))
                                                {
                                                    //isMichelEletron=false;
                                                    delayedIsNetron=true;
                                                    delayedCapVol=(*CapVolumeName)[0];
                                                    //get first hit time caused by this neutron
                                                    if((*ColliVolume)[s]=="LS" ||(*ColliVolume)[s]=="GD") 
                                                    {
                                                        if( pFTfromDN==0. )
                                                        {
                                                            pFTfromDN=ColliTime[s];
                                                        }else
                                                        {
                                                            pFTfromDN=pFTfromDN>ColliTime[s]?ColliTime[s]:pFTfromDN;
                                                        }
                                                        pEfromDN+=ColliEloss[s];
                                                    }

                                                }
                                            }
                                            double eventFirstHitTimeThisNeutron=0.;
                                            cout<<"... [InitE:"<<InitKineE <<"MeV @"<<(*GenVolume)[0] <<" CapedBy:"<<(*CapTargetName)[0] <<"] "<<"ColliVolume";
                                            for( int s=0 ; s<ColliNum ; s++ )
                                            {
                                                cout<<" ["<<s<<"/"<<ColliNum<<"]:"<<(*ColliVolume)[s]<<","<<ColliEloss[s]<<"MeV,"<<ColliTime[s]*1000<<"ns";
                                                if((*ColliVolume)[s]=="LS" ||(*ColliVolume)[s]=="GD") 
                                                {
                                                    if( eventFirstHitTimeAllNeutron==0. )
                                                    {
                                                        eventFirstHitTimeAllNeutron=ColliTime[s];
                                                    }else
                                                    {
                                                        eventFirstHitTimeAllNeutron=eventFirstHitTimeAllNeutron>ColliTime[s]?ColliTime[s]:eventFirstHitTimeAllNeutron;
                                                    }
                                                    if( eventFirstHitTimeThisNeutron==0. )
                                                    {
                                                        eventFirstHitTimeThisNeutron=ColliTime[s];
                                                    }else
                                                    {
                                                        eventFirstHitTimeThisNeutron=eventFirstHitTimeThisNeutron>ColliTime[s]?ColliTime[s]:eventFirstHitTimeThisNeutron;
                                                    }
                                                    pEfromAN+=ColliEloss[s];
                                                }
                                            }
                                            cout<<endl;
                                            cout<<"  >>:eventFirstHitTimeThisNeutron "<<eventFirstHitTimeThisNeutron*1000<<endl;
                                        }
                                    }
                                }

                                for( int o=0 ; o<etnum ; o++ )
                                {
                                    et->GetEntry(o);
                                    if(eEventID==muonEventID )
                                    {
                                        //NumOfMichelElectron++;   //cout<<"find one MichelEletron "<<endl;
                                        Event mcMichelElectronEvt;
                                        mcMichelElectronEvt.dE=eKineE;
                                        mcMichelElectronEvt.time=eMichelLocalTime;//us
                                        mcMichelElectronEvt.capVol=(*eVolume)[0];
                                        mcMichelElectronList.push_back(mcMichelElectronEvt);
                                        if( muonTrackLength[3*fnPair[k].first.det-1]>0. )
                                        {
                                            if( eKineE>=6.0 )
                                            {
                                                eventTag=3.;
                                            }else if(eKineE>=0.7&&eKineE<6.0)
                                            {
                                                eventTag=3.1;
                                            }else
                                            {
                                                eventTag=3.2;
                                            }
                                        }else
                                        {
                                            if( eKineE>=6.0 )
                                            {
                                                eventTag=3.3;
                                            }else if(eKineE>=0.7&&eKineE<6.0)
                                            {
                                                eventTag=3.4;
                                            }else
                                            {
                                                eventTag=3.5;
                                            }
                                        }
                                        break;
                                    }
                                    eventFirstHitTime=(muonTrackLength[0]+muonTrackLength[1])/1000/(0.3*sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))))/1000;
                                }

                                if( eventTag==6 )//is not MichelElectron,find corner muon
                                {
                                    if(muonTrackLength[3*fnPair[k].first.det-1]>0.)
                                    {
                                        if( delayedIsNetron )
                                        {
                                            eventTag=4.0;//don't where is the prompt signal from,and delayed signal is from neutron captured on GD or SST
                                        }else
                                        {
                                            eventTag=4.1;
                                        }
                                        eventFirstHitTime=(muonTrackLength[0]+muonTrackLength[1])/1000/(0.3*sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))))/1000;
                                    }else
                                    {
                                        if(delayedIsNetron)//delayed signal is neutron
                                        {
                                            if( eventFirstHitTimeAllNeutron!=0. )
                                            {
                                                if(pEfromDN!=0.&&pEfromAN==pEfromDN&&pFTfromDN==eventFirstHitTimeAllNeutron )//prompt and delayed signal from the same neutron
                                                {
                                                    if( delayedCapVol=="GD" )
                                                    {
                                                        eventTag=1.;
                                                    }else if(delayedCapVol=="SST")
                                                    {
                                                        eventTag=1.1;
                                                    }else
                                                    {
                                                        eventTag=1.2;//other
                                                    }
                                                }else if(eventFirstHitTimeAllNeutron<fnPair[k].first.time)
                                                {
                                                    eventTag=2.;
                                                }else
                                                {
                                                    eventTag=5.3;
                                                }
                                                if( eventTag<=2. )
                                                {
                                                    eventFirstHitTime=eventFirstHitTimeAllNeutron;//!!!!
                                                }
                                            }else
                                            {
                                                eventTag=5.;
                                            }
                                        }else
                                        {
                                            if( NumOfNeutron>0 )
                                            {
                                                eventTag=5.1;
                                            }else if( NumOfNeutron==0 )
                                            {
                                                eventTag=5.2;
                                            }else
                                            {
                                                eventTag=5.4;//other
                                            }
                                        }
                                        if( eventTag>=5.&&eventTag<6. )
                                        {
                                            eventFirstHitTime=fnPair[k].first.time;
                                        }
                                    }

                                }


                                //tag=5,(1)i don't where is the prompt signal from,and delayed signal is from neutron captured on GD or SST.(2)MichelEletron
                                fnPair[k].first.tag=eventTag;
                                fnPair[k].first.firstHitTime=eventFirstHitTime;
                                mp_spallScaledE[0]=fnPair[k].first.quenchedDepE;
                                mp_spallEnergy[0]=fnPair[k].first.dE;
                                mp_spallTrigNanoSec[0]=(int)(fnPair[k].first.time*1000);
                                mp_spallX[0]=fnPair[k].first.x+6000*(fnPair[k].first.det-1);
                                mp_spallY[0]=fnPair[k].first.y;
                                mp_spallZ[0]=fnPair[k].first.z;
                                mp_spallDetId[0]=fnPair[k].first.det;
                                //tag for event.
                                mp_spallQuadrant[0]=fnPair[k].first.tag;
                                mp_spallMaxQ[0]=muonInitKineE;
                                mp_spallFirstHitTime[0]=eventFirstHitTime*1000;

                                mp_spallScaledE[1]=fnPair[k].second.quenchedDepE;
                                mp_spallEnergy[1]=fnPair[k].first.dE;
                                mp_spallTrigNanoSec[1]=(int)(fnPair[k].second.time*1000);
                                mp_spallX[1]=fnPair[k].second.x+6000*(fnPair[k].second.det-1);
                                mp_spallY[1]=fnPair[k].second.y;
                                mp_spallZ[1]=fnPair[k].second.z;
                                mp_spallDetId[1]=fnPair[k].second.det;
                                fnTree->Fill();

                                eventFirstHitTime=0.;
                                eventTag=5;
                                mp_spallScaledE[0]=0.;
                                mp_spallEnergy[0]=0.;
                                mp_spallTrigNanoSec[0]=0;
                                mp_spallX[0]=0.;
                                mp_spallY[0]=0.;
                                mp_spallZ[0]=0.;
                                mp_spallDetId[0]=0;
                                //tag for event.
                                mp_spallQuadrant[0]=0;
                                mp_spallMaxQ[0]=0.;
                                mp_spallFirstHitTime[0]=0.;

                                mp_spallScaledE[1]=0.;
                                mp_spallEnergy[1]=0.;
                                mp_spallTrigNanoSec[1]=0.;
                                mp_spallX[1]=0.;
                                mp_spallY[1]=0.;
                                mp_spallZ[1]=0.;
                                mp_spallDetId[1]=0;

                                cout<<Form("[tag=%.1f det=%d evtID=%5d %3.2f->%3.2fMeV(%4.2fns->%4.2fns) %2.2f->%2.2fMeV(*us->%3.2fus)]",fnPair[k].first.tag,fnPair[k].first.det,muonEventID,fnPair[k].first.dE,fnPair[k].first.quenchedDepE,fnPair[k].first.firstHitTime*1000,fnPair[k].first.time*1000,fnPair[k].second.dE,fnPair[k].second.quenchedDepE,fnPair[k].second.time);

                                float muonFT=(muonTrackLength[0]+muonTrackLength[1])/1000/(0.3*sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))))/1000;
                                float muonFT2=(muonTrackLength[2])/1000/(0.3*sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))))/1000;
                                float muonFT3=(muonTrackLength[5])/1000/(0.3*sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))))/1000;
                                float muonQE=muonQuenchedTotalEnergyDep[0]+muonQuenchedTotalEnergyDep[1];
                                float muonQE2=muonQuenchedTotalEnergyDep[2]+muonQuenchedTotalEnergyDep[3];
                                cout<<endl;
                                cout<<Form("    mu(InitE:%3.2fMeV ad1:%3.8fMeV ad2:%3.8fMeV ws:%4.2fns mo1:%4.2fns mo2:%4.2fns)",muonInitKineE,muonQE,muonQE2,muonFT*1000,muonFT2*1000,muonFT3*1000);

                                int eNum=mcMichelElectronList.size();
                                float eE=0.;
                                float eT=0.;
                                string eP;
                                for( int n=0 ; n<eNum ; n++ )
                                {
                                    eE=mcMichelElectronList[n].dE;
                                    eT=mcMichelElectronList[n].time;
                                    eP=mcMichelElectronList[n].capVol;
                                    cout<<Form(" e(%3.8fMeV %4.2fus @%s)",eE,eT,eP.c_str());
                                }
                                int nNum=mcNeutronList.size();
                                float nE=0.;
                                float nT=0.;
                                string nP;
                                for( int n=0 ; n<nNum ; n++ )
                                {
                                    nE=mcNeutronList[n].dE;
                                    nT=mcNeutronList[n].time;
                                    nP=mcNeutronList[n].capVol;
                                    cout<<Form(" n(%3.2fMeV %4.2fus %3s)",nE,nT,nP.c_str());
                                }

                                cout<<endl;
                                cout<<endl;
                                mcNeutronList.clear();
                                mcMichelElectronList.clear();
                            }

                            }
                            _relTime=0.;
                        }
                        _relTime+=stime;
                        if( _dE==0. )
                        {
                            _time=_relTime; 
                        }
                        _eventID=sEventID;
                        _x=sx;
                        _y=sy;
                        _z=sz;
                        _dE+=sdE;
                        _quenchedDepE+=squenchedDepE;
                        _det=detTmp;

                    }

                }
                //MichelElectron 
                if( anaMichelElectron )
                {
                    for( int o=0 ; o<etnum ; o++ )
                    {
                        et->GetEntry(o);
                        if(!((*eVolume)[0]=="GD" || (*eVolume)[0]=="LS" ||(*eVolume)[0]=="MO")) continue;
                        for( int p=0 ; p<mtnum ; p++ )
                        {
                            mt->GetEntry(p);
                            float eMuonLength=0;
                            float eMuonIntervalTime=0;

                            if( muonEventID==eEventID )
                            { 
                                eMuonLength=muonTrackLength[1]+muonTrackLength[0];
                                //std::cout<<"eMuonLength : "<<eMuonLength<<endl;
                                if( eMuonLength!=0 )
                                {
                                    number++;
                                    //std::cout<<"number : "<<number<<endl;
                                    eMuonIntervalTime=eMuonLength/1000/(0.3*sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))));
                                    //std::cout<<"eMuonIntervalTime : "<<eMuonIntervalTime<<endl;
                                    h3->Fill(eMuonIntervalTime);
                                } 
                                break;
                            }
                        }
                    }
                }
                //fn
                if( anaFn )
                {
                    for( int r=0 ; r<tnum ; r++ )
                    {
                        t->GetEntry(r);
                        if(GenVolume->begin()==GenVolume->end()||ColliVolume->begin()==ColliVolume->end()) continue;
                        if( (*GenVolume)[0]=="IWS" )
                        {
                            if(!((*CapVolumeName)[0]=="GD"||(*CapVolumeName)[0]=="LS")) continue;
                            nNum++;
                            float colliTime=ColliTime[0];
                            colliTime+=0.;
                            float firstColliTimeInLSorGD=0.;
                            float totalColliEloss=0.;
                            int throughGD=0;
                            int ColliNumBeforeLS=999;
                            //float totalColliTime=ColliTime[0];
                            //cout<<"size of ColliEloss : "<<sizeof(ColliEloss)/sizeof(ColliEloss[0])<<endl;
                            //int sizeOfColliEloss=sizeof(ColliEloss)/sizeof(ColliEloss[0]);
                            //cout<<" "<<endl;
                            //cout<<"ColliNum("<<ColliNum<<") : ";
                            for( int s=0 ; s<ColliNum ; s++ )
                            {
                                //cout<<ColliEloss[s]<<"("<<(*ColliVolume)[s]<<","<<(ColliTime[s]-colliTime)*1000 <<") ";
                                colliTime=ColliTime[s];
                                if((*ColliVolume)[s]=="LS" ||(*ColliVolume)[s]=="GD") 
                                {
                                    if(firstColliTimeInLSorGD==0.) firstColliTimeInLSorGD=ColliTime[s];
                                    totalColliEloss+=ColliEloss[s]; 
                                    if((*ColliVolume)[s]=="GD") throughGD=1;
                                    if(ColliNumBeforeLS==999&&(*ColliVolume)[s]=="LS") ColliNumBeforeLS=s;
                                }
                                //totalColliTime=ColliTime[s]-ColliTime[0];

                            }
                            //if( totalColliEloss>0.7 )
                            //{
                            fnInitE->Fill(InitKineE);
                            if( firstColliTimeInLSorGD !=0.)
                            {
                                mt->GetEntry(muonIndex[EventID]);
                                intervalTime=firstColliTimeInLSorGD-muonInitTime; 
                                //if( CapGammaESum>6.0&&CapGammaESum<12.0 )
                                if((*CapTargetName)[0]=="/dd/Materials/Gd_157"||(*CapTargetName)[0]=="/dd/Materials/Gd_155")
                                {
                                    timeIntervalGd->Fill(intervalTime*1000);
                                    timeIntervalvsInitEGd->Fill(intervalTime*1000,InitKineE);
                                    fnPEGd->Fill(totalColliEloss);
                                    fnInitEGd->Fill(InitKineE);
                                    fnInitEtoyGd->Fill(InitKineE);
                                    PEvsInitEGd->Fill(totalColliEloss,InitKineE);
                                    PEvstimeIntervalGd->Fill(totalColliEloss,intervalTime*1000);
                                    PEvsRGd->Fill(totalColliEloss,sqrt(InitLocalX*InitLocalX+InitLocalY*InitLocalY));
                                    PEvsZGd->Fill(totalColliEloss,InitLocalZ);
                                    fnPEtoyGd->Fill(totalColliEloss);
                                    PEvsPosTagGd->Fill(totalColliEloss,throughGD);
                                    if( throughGD )
                                    {
                                        PEwithThroughGDGd->Fill(totalColliEloss); 
                                    } else
                                    {
                                        PEwithThroughLSGd->Fill(totalColliEloss);
                                    }
                                    if( intervalTime*1000>=55 )
                                    {
                                        fnPEmoreGd->Fill(totalColliEloss);
                                    } else
                                    {
                                        fnPElessGd->Fill(totalColliEloss);
                                    }
                                }
                                //if( CapGammaESum>1.8&&CapGammaESum<2.8 )
                                if((*CapTargetName)[0]=="/dd/Materials/TS_H_of_Water")
                                {
                                    timeIntervalH->Fill(intervalTime*1000);
                                    timeIntervalvsInitEH->Fill(intervalTime*1000,InitKineE);
                                    fnPEH->Fill(totalColliEloss);
                                    fnInitEH->Fill(InitKineE);
                                    fnInitEtoyH->Fill(InitKineE);
                                    PEvsInitEH->Fill(totalColliEloss,InitKineE);
                                    PEvstimeIntervalH->Fill(totalColliEloss,intervalTime*1000);
                                    PEvsRH->Fill(totalColliEloss,sqrt(InitLocalX*InitLocalX+InitLocalY*InitLocalY));
                                    PEvsZH->Fill(totalColliEloss,InitLocalZ);
                                    fnPEtoyH->Fill(totalColliEloss);
                                    PEvsPosTagH->Fill(totalColliEloss,throughGD);
                                    if( throughGD)
                                    {
                                        PEwithThroughGDH->Fill(totalColliEloss); 
                                    } else
                                    {
                                        PEwithThroughLSH->Fill(totalColliEloss);
                                    }
                                    if( intervalTime*1000>=55 )
                                    {
                                        fnPEmoreH->Fill(totalColliEloss);
                                    } else
                                    {
                                        fnPElessH->Fill(totalColliEloss);
                                    }
                                }
                                if( (*CapTargetName)[0]=="/dd/Materials/Gd_157"||(*CapTargetName)[0]=="/dd/Materials/Gd_155"||(*CapTargetName)[0]=="/dd/Materials/TS_H_of_Water" )
                                {
                                    posInterval->Fill(sqrt((CapLocalX-ColliLocalX[ColliNum-1])*(CapLocalX-ColliLocalX[ColliNum-1])+(CapLocalY-ColliLocalY[ColliNum-1])*(CapLocalY-ColliLocalY[ColliNum-1])+(CapLocalZ-ColliLocalZ[ColliNum-1])*(CapLocalZ-ColliLocalZ[ColliNum-1])));
                                    fnPEtotal->Fill(totalColliEloss);
                                    fnPEtoytotal->Fill(totalColliEloss);
                                }
                                timeIntervalAllfn->Fill(intervalTime*1000);
                                timeIntervalAllfnvsInitE->Fill(intervalTime*1000,InitKineE);
                                if( ColliNumBeforeLS!=999 )
                                {
                                    EbeforeLS->Fill(BeforeColliKineE[ColliNumBeforeLS]);
                                    ELossbeforeLS->Fill(InitKineE-BeforeColliKineE[ColliNumBeforeLS]);
                                }
                            }

                            //}
                            //cout<<"(colli "<<totalColliEloss<<"MeV,"<<totalColliTime*1000<<"ns) (Captured by ["<<(*CapTargetName)[0]<<"],in ["<<(*CapVolumeName)[0]<<"],gammaE "<<CapGammaESum<<"MeV,time "<<(CapTime-colliTime)*1000 <<"ns)"<<endl;
                            //cout<<"(Captured by ["<<(*CapTargetName)[0]<<"],in ["<<(*CapVolumeName)[0]<<"]"<<endl;
                        }
                    }
                    muonIndex.clear();
                }
                //stopmuon
                if( anaStopMuon )
                {
                    for( int v=0 ; v<mtnum ; v++ )
                    {
                        mt->GetEntry(v);
                        float stopMuonLength=0;
                        float stopMuonIntervalTime=0;
                        /*
                           if( muonTrackLength[3]>0 && muonTrackLength[3]<100 && muonTrackLength[6]==0 )
                           {
                           stopMuonLength=muonTrackLength[1]+muonTrackLength[2];
                           }
                           if( muonTrackLength[6]>0 && muonTrackLength[6]<100 && muonTrackLength[3]==0 )
                           {
                           stopMuonLength=muonTrackLength[1]+muonTrackLength[5];
                           }
                           */
                        stopMuonLength=muonTrackLength[1]+muonTrackLength[0];
                        if( stopMuonLength!=0 )
                        {
                            stopMuonIntervalTime=stopMuonLength/1000/(0.3*sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))));
                            //std::cout<<"stopMuonIntervalTime : "<<stopMuonIntervalTime<<endl;
                            //std::cout<<"stopMuonLength/1000 : "<<stopMuonLength/1000<<endl;
                            //std::cout<<" "<<endl;
                            h->Fill(stopMuonIntervalTime);
                            //h1->Fill(TMath::Sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))));
                        }

                    }

                }
            }
            fnFile->cd();
            f->Close();
        }

        // h->Draw();
        //h2->Draw();
        //h3->Draw();
        if( anaFn )
        {

            TFile* fr=new TFile(Form("MCdata/result_%d.root",rootNum),"RECREATE");
            fr->cd();
            timeIntervalGd->Write();
            timeIntervalvsInitEGd->Write();
            fnPElessGd->Write();
            fnPEmoreGd->Write();
            fnPEGd->Write();
            fnInitEGd->Write();
            PEvsInitEGd->Write();
            PEvstimeIntervalGd->Write();
            PEvsRGd->Write();
            PEvsZGd->Write();
            fnPEtoyGd->Write();
            PEvsPosTagGd->Write();
            PEwithThroughLSGd->Write();
            PEwithThroughGDGd->Write();
            fnInitEtoyGd->Write();

            timeIntervalH->Write();
            timeIntervalvsInitEH->Write();
            fnPElessH->Write();
            fnPEmoreH->Write();
            fnPEH->Write();
            fnInitEH->Write();
            PEvsInitEH->Write();
            PEvstimeIntervalH->Write();
            PEvsRH->Write();
            PEvsZH->Write();
            fnPEtoyH->Write();
            PEvsPosTagH->Write();
            PEwithThroughLSH->Write();
            PEwithThroughGDH->Write();
            fnInitEtoyH->Write();

            fnPEtotal->Write();
            fnPEtoytotal->Write();
            posInterval->Write();
            EbeforeLS->Write();
            ELossbeforeLS->Write();
            timeIntervalAllfn->Write();
            timeIntervalAllfnvsInitE->Write();
            fnInitE->Write();
            fr->Close();
        }
        fnFile->cd();
        gDirectory->mkdir("IWSMuonTree");
        gDirectory->cd("IWSMuonTree");
        fnTree->Write("IWSMuonTree");
        fnFile->Close();
        return 1;

    }

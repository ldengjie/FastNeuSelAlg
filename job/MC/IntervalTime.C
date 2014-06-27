#include  <iostream>
#include  <TH1F.h>
#include  <TH2F.h>
#include  <TFile.h>
#include  <TString.h>
#include  <TTree.h>
#include  <math.h>
using namespace std;

typedef struct event
{
    int EventID;
    float x;
    float y;
    float z;
    float dE;
    float quenchedDepE;
    float time;
    int det;
}Event;

vector<Event> eventBuf;

//IWS AD1 AD2
int inwhere(float x,float y,float z)
{
    if( x<2500&&x>-2500&&y<2500&&y>-2500&&z<2500&&z>-2500 )
    {
        return 1;
    }else if( x<-3500&&x>-8500&&y<2500&&y>-2500&&z<2500&&z>-2500 )
    {
        return 2;
    }else
    {
        return 5;
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
    cout<<"    EventID  : "<<evt.EventID<<endl;
    cout<<"    x  : "<<evt.x<<" mm"<<endl;
    cout<<"    y  : "<<evt.y<<" mm"<<endl;
    cout<<"    z  : "<<evt.z<<" mm"<<endl;
    cout<<"    dE  : "<<evt.dE<<" MeV"<<endl;
    cout<<"    quenchedDepE  : "<<evt.quenchedDepE<<" MeV"<<endl;
    cout<<"    time  : @"<<evt.time<<" us"<<endl;
    TString detStr="AD";
    if( evt.det==5 )
    {
        detStr="IWS";
    }else
    {
        detStr+=evt.det;
    }
    cout<<"    det  : "<<evt.det<<" ["<<detStr<<"]"<<endl;
    return 1;
}
bool dump(vector<Event> adBuf)
{
    cout<<"here is dump() size="<<adBuf.size()<<endl;
    if( adBuf.size()==2 )
    {
        if( adBuf[0].quenchedDepE<200.&&adBuf[0].quenchedDepE>0.7&&adBuf[1].quenchedDepE<12.&&adBuf[1].quenchedDepE>6. )
        {
            cout<<">>>Find one fast neutron "<<endl;
        }
    }
    return true;

}

int muonNum;
bool selectFn()
{
    muonNum++;
    //cout<<"here is selectFn() "<<endl;
    bool canThroughOneAd=0;
    bool throughThisAd[2]={0};
    if( eventBuf.size()>=3 )
    {
        vector<Event> adEventBuf[2];
    cout<<"========= muonID: "<<muonNum<<" event size:"<<eventBuf.size()<<" ========="<<endl;
        float muonInitTime=eventBuf[0].time;
        //cout<<">>>eventBuf[0].det ="<<eventBuf[0].det<<endl;
        //if(eventBuf[0].det!=5) 
        //{
        //cout<<">>>eventBuf[0].det!=5 ="<<eventBuf[0].det<<endl;
        //}
            cout<<" [0] ("<<eventBuf[0].det <<") "<<eventBuf[0].dE<<"->"<<eventBuf[0].quenchedDepE<<"MeV"<<"  to init "<<(eventBuf[0].time)*1000<<"ns"<<endl;
        for( unsigned int i=1 ; i<eventBuf.size() ; i++ )
        {
            Event _evt=eventBuf[i];
            cout<<" ["<<i<<"] ("<<_evt.det <<") "<<_evt.dE<<"->"<<_evt.quenchedDepE<<"MeV"<<"  to ["<<i-1 <<"] "<<(_evt.time-eventBuf[i-1].time)*1000<<"ns"<<endl;
            //printEvt(_evt);
            //1)
            if(_evt.quenchedDepE<0.7) continue;
            //2)AD muon
            if(_evt.quenchedDepE>200&&_evt.det<5&&(_evt.time-muonInitTime)<2)
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
                //3)
                if( _evt.time-muonInitTime <400)
                {
                    if( adEventBuf[_evt.det-1].size()!=0 )
                    {
                        //4)
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
    cout<<"rootNum : "<<rootNum<<endl;
    int anaStopMuon=0;
    int anaMichelElectron=0;
    int anaFn=0;
    int anaSpa=1;

    float muonMass=105.65;//MeV
    int number=0;

    TH1F* h = new TH1F("stopMuonIntervalTime","stopMuonIntervalTime",400,0,400);
    //TH1F* h1 = new TH1F("velocity","velocity",1000,0.9,1);
    //
    TH1F* timeIntervalGd = new TH1F("timeIntervalGd","timeIntervalGd",400,0,400);
    TH2F*  timeIntervalvsInitEGd= new TH2F("timeIntervalvsInitEGd","timeIntervalvsInitEGd",400,0,400,1000,0,1000);
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
    TH2F*  timeIntervalvsInitEH= new TH2F("timeIntervalvsInitEH","timeIntervalvsInitEH",400,0,400,1000,0,1000);
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
    TH2F*  timeIntervalAllfnvsInitE= new TH2F("timeIntervalAllfnvsInitE","timeIntervalAllfnvsInitE",400,0,400,1000,0,1000);

    TH1F* h3 = new TH1F("eIntervalTime","eIntervalTime",400,0,400);

    for( int i=1 ; i<rootNum+1; i++ )
    {

        TString nameStr=Form("/publicfs/dyb/data/userdata/dyboffline/liuyb/MuonSimulation/Dyb/sim_%06d.root",i);
        if( i%100==0 )
        {
            std::cout<<"filename  : "<<nameStr<<endl;
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
            vector<TString>* eVolume = 0;
            et->SetBranchAddress("EventID",&eEventID);
            et->SetBranchAddress("VolName",&eVolume);

            TTree* mt= (TTree*)f->Get("Muon");
            int mtnum=mt->GetEntries();
            float muonInitTime;
            Int_t muonEventID;
            float muonTrackLength[100];
            float muonInitKineE;
            mt->SetBranchAddress("InitTime",&muonInitTime);
            mt->SetBranchAddress("EventID",&muonEventID);
            mt->SetBranchAddress("InitKineE",&muonInitKineE);
            mt->SetBranchAddress("TrackLength",muonTrackLength);

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
            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
                    if(  _eventID!=0&&(sEventID!=_eventID|| stime*1000>100 || (_det!=detTmp&&_det!=999)))
                    {
                        Event eventTmp=dumpEvent(_eventID,_x,_y,_z,_dE,_quenchedDepE,_time,_det);
                        eventBuf.push_back(eventTmp);
                        _x=0.;
                        _y=0.;
                        _z=0.;
                        _dE=0.;
                        _quenchedDepE=0.;
                    }
                    //new muon
                    if(sEventID!=_eventID )
                    {
                        //select fn from eventBuf
                        selectFn();
                        _relTime=0.;
                    }
                    _relTime+=stime;
                    if( _x==0. )
                    {
                        _time=_relTime; 
                    }
                    _eventID=sEventID;
                    _x+=sx;
                    _y+=sy;
                    _z+=sz;
                    _dE+=sdE;
                    _quenchedDepE+=squenchedDepE;
                    _det=detTmp;

                }

            }
            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            //MichelElectron 
            if( anaMichelElectron )
            {
                for( int o=0 ; o<etnum ; o++ )
                {
                    et->GetEntry(o);
                    if(!((*eVolume)[0]=="GD" || (*eVolume)[0]=="LS" ||(*eVolume)[0]=="MO")) continue;
                    //std::cout<<"o  : "<<o<<endl;
                    for( int p=0 ; p<mtnum ; p++ )
                    {
                        mt->GetEntry(p);
                        float eMuonLength=0;
                        float eMuonIntervalTime=0;
                        if( muonEventID==eEventID )
                        {   
                            if( muonTrackLength[3]>0 && muonTrackLength[6]==0 )
                            {
                                eMuonLength=muonTrackLength[1]+muonTrackLength[2]+muonTrackLength[3];
                            }
                            if( muonTrackLength[6]>0  && muonTrackLength[3]==0 )
                            {
                                eMuonLength=muonTrackLength[1]+muonTrackLength[5]+muonTrackLength[6];
                            }
                            //std::cout<<"eMuonLength  : "<<eMuonLength<<endl;
                            if( eMuonLength!=0 )
                            {
                                number++;
                                //std::cout<<"number  : "<<number<<endl;
                                eMuonIntervalTime=eMuonLength/1000/(0.3*sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))));
                                //std::cout<<"eMuonIntervalTime  : "<<eMuonIntervalTime<<endl;
                                h3->Fill(eMuonIntervalTime);
                            }           
                            break;
                        }
                    }
                }
            }

            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            //fn
            if( anaFn )
            {
                map<int,int> muonIndex;
                for( int u=0 ; u<mtnum ; u++ )
                {
                    mt->GetEntry(u);
                    muonIndex.insert(std::pair<int,int>(muonEventID,u));
                }
                for( int r=0 ; r<tnum ; r++ )
                {
                    t->GetEntry(r);
                    if(GenVolume->begin()==GenVolume->end()||ColliVolume->begin()==ColliVolume->end()) continue;
                    if( (*GenVolume)[0]=="IWS" )
                    {
                        if(!((*CapVolumeName)[0]=="GD"||(*CapVolumeName)[0]=="LS")) continue;
                        nNum++;
                        float colliTime=ColliTime[0];

                        float firstColliTimeInLSorGD=0.;
                        float totalColliEloss=0.;
                        int throughGD=0;
                        int ColliNumBeforeLS=999;
                        //float totalColliTime=ColliTime[0];
                        //cout<<"size of ColliEloss  : "<<sizeof(ColliEloss)/sizeof(ColliEloss[0])<<endl;
                        //int sizeOfColliEloss=sizeof(ColliEloss)/sizeof(ColliEloss[0]);
                        //cout<<" "<<endl;
                        //cout<<"ColliNum("<<ColliNum<<") : ";
                        for( int s=0 ; s<ColliNum ; s++ )
                        {
                            //cout<<ColliEloss[s]<<"("<<(*ColliVolume)[s]<<","<<(ColliTime[s]-colliTime)*1000 <<")  ";
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
                            //if(  CapGammaESum>1.8&&CapGammaESum<2.8  )
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

            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            //stopmuon
            if( anaStopMuon )
            {
                for( int v=0 ; v<mtnum ; v++ )
                {
                    mt->GetEntry(v);
                    float stopMuonLength=0;
                    float stopMuonIntervalTime=0;
                    if( muonTrackLength[3]>0 && muonTrackLength[3]<100 && muonTrackLength[6]==0 )
                    {
                        stopMuonLength=muonTrackLength[1]+muonTrackLength[2];
                    }
                    if( muonTrackLength[6]>0 && muonTrackLength[6]<100 && muonTrackLength[3]==0 )
                    {
                        stopMuonLength=muonTrackLength[1]+muonTrackLength[5];
                    }
                    if( stopMuonLength!=0 )
                    {
                        stopMuonIntervalTime=stopMuonLength/1000/(0.3*sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))));
                        //std::cout<<"stopMuonIntervalTime  : "<<stopMuonIntervalTime<<endl;
                        //std::cout<<"stopMuonLength/1000  : "<<stopMuonLength/1000<<endl;
                        //std::cout<<" "<<endl;
                        h->Fill(stopMuonIntervalTime);
                        //h1->Fill(TMath::Sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))));
                    }

                }

            }

            //***********************************************************************

        }
        f->Close();
    }

        // h->Draw();
        //h2->Draw();
        //h3->Draw();
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

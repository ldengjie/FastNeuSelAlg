{
    float muonMass=105.65;//MeV
    /*
    TChain* chain = new TChain("Neutron");
    //chain->Add("*.root");
    chain->Add("sim_010931.root");
    chain->Add("sim_010932.root");
    TChain* muonChain = new TChain("Muon");
    //muonChain->Add("*.root");
    muonChain->Add("sim_010931.root");
    muonChain->Add("sim_010932.root");
    TChain* eChain = new TChain("MichelElectron");
    //muonChain->Add("*.root");
    eChain->Add("sim_010931.root");
    eChain->Add("sim_010932.root");

    Int_t muonentries = muonChain->GetEntries();
    std::cout<<"num of muon entry  : "<<muonentries<<endl;
    Int_t entries = chain->GetEntries();
    std::cout<<"num of entry  : "<<entries<<endl;
    Int_t eentries = eChain->GetEntries();
    std::cout<<"num of e entry  : "<<eentries<<endl;
*/

    TH1F* h = new TH1F("stopMuonIntervalTime","stopMuonIntervalTime",400,0,400);
    //TH1F* h1 = new TH1F("velocity","velocity",1000,0.9,1);
    TH1F* h2 = new TH1F("fnIntervalTime","fnMuonIntervalTime",400,0,400);
    TH1F* h3 = new TH1F("eIntervalTime","eIntervalTime",400,0,400);
/*
    Int_t eEventID;
    vector<TString>* eVolume = 0;
    eChain->SetBranchAddress("EventID",&eEventID);
    eChain->SetBranchAddress("VolName",&eVolume);

    float muonInitTime;
    Int_t muonEventID;
    float muonInitKineE;
    float muonTrackLength[8];
    float muonInitKineE;
    muonChain->SetBranchAddress("InitKineE",&muonInitKineE);
    muonChain->SetBranchAddress("InitTime",&muonInitTime);
    muonChain->SetBranchAddress("EventID",&muonEventID);
    muonChain->SetBranchAddress("InitKineE",&muonInitKineE);
    muonChain->SetBranchAddress("TrackLength",muonTrackLength);

    Int_t nNum=0;
    float intervalTime;
    vector<TString>* GenVolume = 0;
    vector<TString>* ColliVolume = 0;
    float ColliEloss[54];
    float ColliTime[54];
    Int_t ColliNum=0;
    Int_t EventID;
    float InitTime;
    float InitKineE;
    chain->SetBranchAddress("InitTime",&InitTime);
    chain->SetBranchAddress("EventID",&EventID);
    chain->SetBranchAddress("ColliEloss",ColliEloss);
    chain->SetBranchAddress("ColliTime",ColliTime);
    chain->SetBranchAddress("GenVolume",&GenVolume);
    chain->SetBranchAddress("ColliVolume",&ColliVolume);
    chain->SetBranchAddress("ColliNum",&ColliNum);
    chain->SetBranchAddress("InitKineE",&InitKineE);
  */
    ///*
    int totalnum=0;
    int fileNum=0;
    int totalNum[100];
    string fileName[100];
    for( int i=0 ; i<100 ; i++ )
    {
        totalNum[i]=0;
        fileName[i]="";
    }
    
    int number=0;
    for( int i=0 ; i<10 ; i++ )
    {
        for( int j=0 ; j<10 ; j++ )
        {
            stringstream filename;
            filename<<"/publicfs/dyb/data/userdata/dyboffline/liuyb/MuonSimulation/Dyb/sim_010";
            //filename<<"sim_010";
            filename<<"9";
            filename<<i;
            filename<<j;        
            filename<<".root";
            std::cout<<"filename  : "<<filename.str()<<endl;

            
            TFile* f= new TFile(filename.str().c_str());
            if( f.IsZombie() )
            {
                std::cout<<"not exist "<<endl;
            }else
            {
                TTree* t= (TTree*)f->Get("Neutron");
                int tnum=t->GetEntries();
                totalnum+=t->GetEntries();
                //totalNum[i*10+j]=totalnum;
                //fileName[i*10+j]=filename.str();
                TTree* et= (TTree*)f->Get("MichelElectron");
                int etnum=et->GetEntries();
                TTree* mt= (TTree*)f->Get("Muon");
                int mtnum=mt->GetEntries();
    Int_t eEventID;
    vector<TString>* eVolume = 0;
    et->SetBranchAddress("EventID",&eEventID);
    et->SetBranchAddress("VolName",&eVolume);

    float muonInitTime;
    Int_t muonEventID;
    float muonTrackLength[100];
    float muonInitKineE;
    mt->SetBranchAddress("InitTime",&muonInitTime);
    mt->SetBranchAddress("EventID",&muonEventID);
    mt->SetBranchAddress("InitKineE",&muonInitKineE);
    mt->SetBranchAddress("TrackLength",muonTrackLength);

    Int_t nNum=0;
    float intervalTime;
    vector<TString>* GenVolume = 0;
    vector<TString>* ColliVolume = 0;
    float ColliEloss[100];
    float ColliTime[100];
    Int_t ColliNum=0;
    Int_t EventID;
    float InitTime;
    float InitKineE;
    t->SetBranchAddress("InitTime",&InitTime);
    t->SetBranchAddress("EventID",&EventID);
    t->SetBranchAddress("ColliEloss",ColliEloss);
    t->SetBranchAddress("ColliTime",ColliTime);
    t->SetBranchAddress("GenVolume",&GenVolume);
    t->SetBranchAddress("ColliVolume",&ColliVolume);
    t->SetBranchAddress("ColliNum",&ColliNum);
    t->SetBranchAddress("InitKineE",&InitKineE);
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//MichelElectron 
/*
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
                    eMuonIntervalTime=eMuonLength/1000/(0.3*TMath::Sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))));
                    //std::cout<<"eMuonIntervalTime  : "<<eMuonIntervalTime<<endl;
                    h3->Fill(eMuonIntervalTime);
                }           
                break;
            }
        }
   }
*/

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//fn
///*
    for( int r=0 ; r<tnum ; r++ )
    {
        t->GetEntry(r);
        if( (*GenVolume)[0]=="IWS" && ((*ColliVolume)[0]=="GD"||(*ColliVolume)[0]=="LS") )
        {
            nNum++;
            for( int s=0 ; s<ColliNum ; s++ )
            {
                
              if( ColliEloss[s]>0.7 )
              {
                  for( int u=0 ; u<mtnum ; u++ )
                  {
                      mt->GetEntry(u);
                      if( EventID==muonEventID )
                      {
                         intervalTime=ColliTime[s]-muonInitTime; 
                         h2->Fill(intervalTime*1000);
                         break;
                      }
                  }
                    
                  //std::cout<<"intervalTime  : "<<intervalTime<<endl;
                  //std::cout<<"InitKineE  : "<<InitKineE<<endl;
                  //std::cout<<"ColliTime[j]  : "<<ColliTime[j]<<endl;
                  //std::cout<<"InitTime  : "<<InitTime<<endl;
                  //std::cout<<"muonInitTime  : "<<muonInitTime<<endl;
                  //std::cout<<"EventID  : "<<EventID<<endl;
                  //std::cout<<"muonEventID  : "<<muonEventID<<endl;
                  //std::cout<<" "<<endl;
                  break;
              }
              
            }
        }
    }
//*/

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//stopmuon
/*
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
           stopMuonIntervalTime=stopMuonLength/1000/(0.3*TMath::Sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))));
           //std::cout<<"stopMuonIntervalTime  : "<<stopMuonIntervalTime<<endl;
           //std::cout<<"stopMuonLength/1000  : "<<stopMuonLength/1000<<endl;
           //std::cout<<" "<<endl;
           h->Fill(stopMuonIntervalTime);
           //h1->Fill(TMath::Sqrt(1-1/((muonInitKineE/muonMass)*(muonInitKineE/muonMass))));
        }

    }
*/

//***********************************************************************

            }
            //std::cout<<"totalNum  : "<<totalnum<<endl;
        }

    }
   // h->Draw();
   h2->Draw();
   //h3->Draw();

}

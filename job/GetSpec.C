{
    TFile* f1=new TFile("P14A/EH1_AS_tA_1.5.root","read");
    TFile* f2=new TFile("P14A/EH2_AS_tA_1.5.root","read");
    TFile* f3=new TFile("P14A/EH3_AS_tA_1.5.root","read");
    TH1F* h1=f1->Get("AD1_PE_RRRRR");
    TH1F* h2=f2->Get("AD1_PE_RRRRR");
    TH1F* h3=f3->Get("AD1_PE_RRRRR");
    TH1F* h=new TH1F(*h1);
    h->Add(h,h,0,0);
    h->Add(h,h1,1,1);
    h->Add(h,h2,1,1);
    h->Add(h,h3,1,1);
    TFile* f=new TFile("AnaFN_iws.root","recreate");
    f->cd();
    h->Write();
    //f->close();
    //f1->close();
    //f2->close();
    //f3->close();
    
}

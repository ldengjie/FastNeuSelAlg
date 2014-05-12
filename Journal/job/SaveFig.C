{
    TFile* f= new TFile("EH1_AS_timeAlign.root");
    TCanvas * myC2 = new TCanvas("myC2","A Canvas",10,10,700,500);
    
    
    TH1F* h=(TH1F*)f->Get("AD1_PEvsFHT2Mu_O");
    h->GetXaxis()->CenterTitle(kTRUE);
    h->GetYaxis()->CenterTitle(kTRUE);
    h->SetXTitle("energy / Mev");
    h->SetYTitle("time / #mus");
    h->SetStats(kFALSE);
    h->Draw();
    TLine *l = new TLine(0,0.2,100,0.2);
    l->SetLineStyle(2);
    l->Draw();
    myC2->SetLogy(kTRUE);
    myC2->SaveAs("PEvsFHT2Mu-O.png");
    
   /* 
    TH1F* h=(TH1F*)f->Get("AD1_PE_RRR");
    h->SetStats(kFALSE);
    h->GetXaxis()->SetRange(h->FindBin(0),h->FindBin(50));
    h->GetXaxis()->CenterTitle(kTRUE);
    h->GetYaxis()->CenterTitle(kTRUE);
    h->SetXTitle("energy / Mev");
    h->SetYTitle("events");
    double height=h->GetMaximum();
    h->SetMaximum(2*height);
    h->SetMinimum(0);
    h->Draw();
    */
    /*
    TH1F* h=(TH1F*)f->Get("AD1_DRvsZ_RR");
    h->GetXaxis()->CenterTitle(kTRUE);
    h->GetYaxis()->CenterTitle(kTRUE);
    h->SetXTitle("R / m");
    h->SetYTitle("Z / m");
    h->SetStats(kFALSE);
    h->Draw();
    //l->SetLineStyle(2);
    TLine *l = new TLine(0,1.5,1.5,1.5);
    l->SetLineWidth(3);
    l->Draw();
    TLine *l2 = new TLine(1.5,1.5,1.5,-1.5);
    l2->SetLineWidth(3);
    l2->Draw();
    TLine *l3 = new TLine(0,-1.5,1.5,-1.5);
    l3->SetLineWidth(3);
    l3->Draw();
    */
}

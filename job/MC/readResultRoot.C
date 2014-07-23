{
    double maxX=0.;
    char nameStr[100];
    char nameStr2[100];
    TFile *f=new TFile("MCdata/fn_45000.root","READ");
    TTree *t=(TTree*)f->Get("IWSMuonTree/IWSMuonTree");
    TCanvas *c=new TCanvas("c","c",800,600);
    TLegend* tl;

    //tl=new TLegend(0.7,0.7,0.99,0.99);

    string hName[12] ={"SpallFirstHitTime","SpallScaledE","SpallScaledE","SpallScaledE","SpallScaledE","SpallScaledE","SpallScaledE","SpallFirstHitTime","SpallFirstHitTime","SpallFirstHitTime","SpallFirstHitTime","SpallFirstHitTime"};
    string epsSuf[12]={"PFT","PE","PE_fn","PE_dn","PE_me","PE_cm","PE_ot","PFT_fn","PFT_dn","PFT_me","PFT_cm","PFT_ot"};
    int binNum[12] ={100,100,100,100,100,100,100,100,100,100,100,100};
    double xMax[12]={200,100,100,100,100,100,100,200,200,200,200,200};

    string hTitle[12]={"First Hit Time of Prompt Signal","Prompt Signal Energy","Prompt Signal Energy of Fast Neutron","Prompt Signal Energy of Double Neutron","Prompt Signal Energy of MichelEletron","Prompt Signal Energy of CornerMuon","Prompt Signal Energy of Others","First Hit time of Fast Neutron","First Hit time of Double Neutron","First Hit time of MichelEletron","First Hit time of CornerMuon","First Hit time of Others"};
    string xTitle[12]={"First Hit Time (ns)","Prompt Signal Energy (MeV)","Prompt Signal Energy (MeV)","Prompt Signal Energy (MeV)","Prompt Signal Energy (MeV)","Prompt Signal Energy (MeV)","Prompt Signal Energy (MeV)","First Hit Time (ns)","First Hit Time (ns)","First Hit Time (ns)","First Hit Time (ns)","First Hit Time (ns)"};
    string yTitle[12]={"Entries/ns","Entries/MeV","Entries/MeV","Entries/MeV","Entries/MeV","Entries/MeV","Entries/MeV","Entries/ns","Entries/ns","Entries/ns","Entries/ns","Entries/ns"};

    TH1F* h[7];
    double n[7]={0.};
    char criteria[7][100];
    string tag[7];
    tag[0]="All";

    for( int j=0 ; j<12 ; j++ )
    {
        if( j<2 )
        {
            tag[1]="FastNeutron";
            tag[2]="DoubleNeutron";
            tag[3]="MichelEletron";
            tag[4]="CornerMuon";
            tag[5]="Others";
            tag[6]="";
        } else
        {
            for( int k=1 ; k<7 ; k++ )
            {
                sprintf(nameStr,"%d.%d",(j-2)%5+1,k-1);
                tag[k].assign(nameStr);
            }
        }
        tl=new TLegend(0.6,0.6,0.99,0.99);
        maxX=0.;
        for( int i=0 ; i<7 ; i++ )
        {
            if( i==0 )
            {
                if( j<2 )
                {
                    sprintf(criteria[0],"SpallQuadrant[0]>%d&&SpallQuadrant[0]<%d",0,9);
                } else
                {
                    sprintf(criteria[0],"SpallQuadrant[0]>%d.9&&SpallQuadrant[0]<%d.9",(j-2)%5,(j-2)%5+1);
                }
            } else
            {
                if( j<2 )
                {
                    sprintf(criteria[i],"SpallQuadrant[0]>%d.9&&SpallQuadrant[0]<%d.9",i-1,i);
                } else
                {
                    if( i==1 )
                    {
                        sprintf(criteria[i],"SpallQuadrant[0]>%d.95&&SpallQuadrant[0]<%d.05",(j-2)%5,(j-2)%5+1);
                    } else
                    {
                        sprintf(criteria[i],"SpallQuadrant[0]>%d.%d5&&SpallQuadrant[0]<%d.%d5",(j-2)%5+1,i-2,(j-2)%5+1,i-1);
                    }
                }
            }
            sprintf(nameStr,"%sh%d",epsSuf[j].c_str(),i);
            h[i]=new TH1F(nameStr,nameStr,binNum[j],0,xMax[j]);
            h[i]->SetName(nameStr);
            h[i]->SetTitle(hTitle[j].c_str());
            h[i]->SetXTitle(xTitle[j].c_str());
            h[i]->SetYTitle(yTitle[j].c_str());
            h[i]->SetStats(0);
            sprintf(nameStr,"%s[0]>>%sh%d",hName[j].c_str(),epsSuf[j].c_str(),i);
            sprintf(nameStr2,"%s",criteria[i]);
            t->Draw(nameStr,nameStr2);
            //cout<<"criteria["<<i<<"]  : "<<criteria[i]<<endl;
            n[i]=h[i]->GetEntries();
            //cout<<"n["<<i<<"]  : "<<n[i]<<endl;
            if( n[i]==0. )
            {
                continue;
            }
            sprintf(nameStr,"MCdata/eps/%s_%s.eps",epsSuf[j].c_str(),tag[i].c_str());
            //c->SaveAs(nameStr);
            double m=h[i]->GetMaximum();
            maxX=maxX>m?maxX:m;
        }

        TCanvas *c1=new TCanvas("c1","c1",800,600);
        c1->cd();
        h[0]->SetMaximum(maxX+5);
        h[0]->SetMinimum(1);
        h[0]->SetLineColor(1);
        h[0]->Draw();
        sprintf(nameStr,"%sh%d",epsSuf[j].c_str(),0);
        tl->AddEntry(nameStr,"All","l");
        for( int i=1 ; i<7 ; i++ )
        {
            if( n[i]==0. )
            {
                continue;
            }
            h[i]->SetLineColor(1+i);
            h[i]->Draw("same");
            sprintf(nameStr,"%sh%d",epsSuf[j].c_str(),i);
            //cout<<"n["<<i<<"]  : "<<n[i]<<endl;
            //cout<<"n[0]  : "<<n[0]<<endl;
            sprintf(nameStr2,"%.2f%% %s",n[i]/n[0]*100.,tag[i].c_str());
            tl->AddEntry(nameStr,nameStr2,"l");
        }
        tl->Draw("same");
        sprintf(nameStr,"MCdata/eps/%s_total.eps",epsSuf[j].c_str());
        c1->SaveAs(nameStr);
        gPad->SetLogy();
        sprintf(nameStr,"MCdata/eps/%s_total_logy.eps",epsSuf[j].c_str());
        c1->SaveAs(nameStr);

    }

}

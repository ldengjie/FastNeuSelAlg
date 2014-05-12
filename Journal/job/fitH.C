#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include    "RooDataSet.h"
#include    "RooGaussModel.h"
#include    "RooTruthModel.h"
#include    "RooDecay.h"
#include    "RooFormulaVar.h"
#include    "RooAbsReal.h"
#include    "RooResolutionModel.h"
#include    "TPaveText.h"
#include    "TText.h"
#include    "TPaveLabel.h"
#include    "RooFFTConvPdf.h"
#include    "RooLandau.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TH1F.h"
#include "TFile.h"
using namespace RooFit ;
int fitPFHT2Mu2()
{
    TFile* f= new TFile("/afs/ihep.ac.cn/users/l/lidj/file/FastNeuSelAlg/job/EH1_AS_timeAlign.root");
    TH1F* h = (TH1F*)f->Get("AD1_PFHT2Mu2_R");
    //h->Draw();
    RooRealVar x("x","x",-50,200);
    RooRealVar mean("mean_fn","mean",20,15,25);
    RooRealVar sigma("sigma_fn","sigma",13,8,18);
    RooRealVar mean2("mean_mu","mean2",70,50,120);
    RooRealVar sigma2("sigma_mu","sigma2",25,25,50);
    RooGaussian g1("g1","g1",x,mean,sigma);
    RooGaussian g2("g2","g2",x,mean2,sigma2);
    RooRealVar Nmuon("Nmuon","Nmuon",185000,170000,200000);
    RooRealVar Nfn("Nfn","Nfn",9000,0,20000);
    RooAddPdf sum("sum","sum",RooArgList(g1,g2),RooArgList(Nmuon,Nfn));
    RooDataHist* data= new RooDataHist("h","h",x,h);
    sum.fitTo(*data,Extended(kTRUE));
    RooPlot* xframe = x.frame();
    data->plotOn(xframe);
    sum.plotOn(xframe);
    //sum.paramOn(xframe);
    //data->statOn(xframe);
    //sum.plotOn(xframe,Components(RooArgList(g1,g2)),LineStyle(kDashed));
    sum.plotOn(xframe,Components(g1),LineStyle(kDashed));
    //sum.plotOn(xframe,Components(g2),LineStyle(kDashed));
    xframe->GetXaxis()->CenterTitle(kTRUE);
    xframe->GetYaxis()->CenterTitle(kTRUE);
    xframe->SetXTitle("time / ns");
    xframe->SetMarkerSize(0.5);
    xframe->SetLineWidth(1);
    //xframe->SetYTitle("time / #mus");
    xframe->Draw();
    return 0;
}
int test()
{
     
    // Observable 
    RooRealVar t("t","t",-10,10) ; 
     
    // Gaussian Resolution model 
    RooRealVar mean("mean","mean",0) ; 
    RooRealVar sigma("sigma","sigma",1) ; 
    RooGaussModel gaussm("gaussm","gaussm",t,mean,sigma) ; 
     
    // Decay p.d.f analytically convoluted with gaussm 
    RooRealVar tau("tau","lifetime",1.54) ; 
    RooDecay model("model","decay (x) gauss",t,tau,gaussm,RooDecay::SingleSided) ; 
     
    // --- Plot decay (x) gauss --- 
    RooPlot* frame = t.frame() ; 
    model.plotOn(frame) ; 
       
    // --- Overlay with decay (x) truth --- 
    RooTruthModel truthm("truthm","truth model",t) ; 
    RooDecay modelt("modelt","decay (x) delta",t,tau,truthm,RooDecay::SingleSided) ; 
    modelt.plotOn(frame,LineStyle(kDashed)) ; 
     
    frame->Draw() ; 
    return 0;
}
int fitIntervalTime()
{
    TFile* f= new TFile("/afs/ihep.ac.cn/users/l/lidj/file/IBDSel/job/mergedHistEH1.root");
    TH1F* h = (TH1F*)f->Get("zhangfh/ibdTimeIntervalAD1");
    h->Rebin(5);
    //h->Draw();
    RooRealVar x("x","x",0,200);

    RooRealVar mean("mean","mean",12,0,20);
    RooRealVar sigma("sigma","sigma",3,0,10);
    RooGaussModel gaussm("gaussm","gaussm",x,mean,sigma) ; 
    //RooGaussian g1("g1","g1",x,mean,sigma);

    //RooRealVar lambda("lambda","lambda",-0.04,-0.5,-0.02) ;
    //RooExponential e("e","e",x,lambda) ;
    RooRealVar tau("tau","lifetime",32,25,40) ; 
    RooDecay model("model","decay (x) gauss",x,tau,gaussm,RooDecay::SingleSided) ; 

    //RooFFTConvPdf conv("conv","gauss (x) exp",x,g1,e,0);
    //RooFFTConvPdf conv("conv","gauss (x) exp",x,e,g1);
    RooDataHist* data= new RooDataHist("h","h",x,h);
    //conv.fitTo(*data);
    model.fitTo(*data);

    //TCanvas *myC = new TCanvas("myC", "myC", 1); 
    RooPlot* xframe = x.frame();

    data->plotOn(xframe,Name("data"));
    model.plotOn(xframe,Name("conv"),LineColor(kRed),LineWidth(2));
    model.paramOn(xframe) ;
    //e.plotOn(xframe,LineStyle(kDashed));

    Double_t signalchi = xframe->chiSquare("conv","data",3); 
    cout << "chi2 = " << signalchi << endl;
    //TPaveLabel *t1 = new TPaveLabel(0.7,0.6,0.9,0.68, Form("#chi^{2} = %f", signalchi)); 
    //t1->Draw();
    xframe->Draw();
    //myC->Draw();
    return 0;
}
int fitDT2P()
{
    TFile* f= new TFile("/afs/ihep.ac.cn/users/l/lidj/file/FastNeuSelAlg/job/EH1_AS_timeAlign.root");
    TH1F* h = (TH1F*)f->Get("AD1_DT2P_RT");
    //h->Draw();
    //h->Rebin(2);
    //RooRealVar x("x","x",1,200);
    RooRealVar x("x","x",0,200);
    RooRealVar mean("mean_n_g","mean",14.775,5,20);
    RooRealVar sigma("sigma_n_g","sigma",2.265,0,5);
    //RooRealVar mean("mean","mean",14.775);
    //RooRealVar sigma("sigma","sigma",2.265);
    RooGaussModel g1("g1","g1",x,mean,sigma);
    //RooRealVar lambda("lambda","lambda",-0.0314,-0.05,-0.01) ;
    //RooRealVar lambda("lambda","lambda",-0.0314) ;
    //RooExponential e("e","e",x,lambda) ;
    //RooFFTConvPdf conv("conv","gauss (x) exp",x,e,g1);
    RooRealVar tau1("tau_n","lifetime",50,10,80) ; 
    RooDecay model1("model","decay (x) gauss",x,tau1,g1,RooDecay::SingleSided) ; 

    RooRealVar mean2("mean_e_g","mean",1,0,5);
    RooRealVar sigma2("sigma_e_g","sigma",2.265,0,5);
    RooGaussModel g2("g2","g2",x,mean2,sigma2);
    //RooRealVar lambda2("lambda2","lambda2",-0.43,-1,-0.1) ;
    //RooRealVar lambda2("lambda2","lambda2",-0.476) ;
    //RooExponential e2("e2","e2",x,lambda2) ;
    //RooFFTConvPdf conv2("conv2","gauss (x) exp",x,e2,g2);
    RooRealVar tau2("tau_e","lifetime",2.1) ; 
    RooDecay model2("mode2","decay (x) gauss",x,tau2,g2,RooDecay::SingleSided) ; 

    RooRealVar Ne("Ne","Ne",100000,0,200000);
    RooRealVar Nn("Nn","Nn",100000,0,200000);
    //RooRealVar Nn("Nn","Nn",10000);
    //RooAddPdf sum("sum","sum",RooArgList(e2,e),RooArgList(Ne,Nn));
    //RooAddPdf sum("sum","sum",RooArgList(e2,conv),RooArgList(Ne,Nn));
    //RooAddPdf sum("sum","sum",RooArgList(conv,e2),RooArgList(Nn,Ne));
    //RooAddPdf sum("sum","sum",RooArgList(conv2,conv),RooArgList(Ne,Nn));
    RooAddPdf sum("sum","sum",RooArgList(model2,model1),RooArgList(Ne,Nn));
    RooDataHist* data= new RooDataHist("h","h",x,h);
    sum.fitTo(*data,Extended(kTRUE));

    RooPlot* xframe = x.frame();

    data->plotOn(xframe,Name("data"));
    sum.plotOn(xframe,Name("sum"),LineColor(kRed),LineWidth(2));
    sum.paramOn(xframe) ;
    //model1.plotOn(xframe,LineStyle(kDashed),LineColor(kGreen),LineWidth(2));
    model2.plotOn(xframe,LineStyle(kDashed),LineColor(kBlue),LineWidth(2));
    //e2.plotOn(xframe,LineStyle(kDashed),LineColor(kBlue),LineWidth(2));
    //e.plotOn(xframe,LineStyle(kDashed),LineColor(kGreen));

    Double_t signalchi = xframe->chiSquare("sum","data",7); 
    cout << "chi2 = " << signalchi << endl;
    xframe->Draw();
    return 0;
}
int fitH(){
    fitPFHT2Mu2();
    //fitIntervalTime();
    //fitDT2P();
    //test();
    return 0;
}

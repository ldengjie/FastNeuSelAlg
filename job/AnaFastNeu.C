#include <iostream>
#include <sstream>
#include <string>
#include  <TFile.h>
#include  <TChain.h>
#include  <TROOT.h>
int AnaFastNeu(int siteNum)
{
  gROOT->ProcessLine(".L FastNeuAna.C+");
  string site;
	if( siteNum==1 )
	{
		site="EH1";
	} else if(siteNum==2)
	{
		site="EH2";
	}else if (siteNum==3)
	{
		site="EH3";
	}else
	{
		site="EH1";
	}

  TChain* chain = new TChain("IWSMuonTree/IWSMuonTree");
  //chain->Add("/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel/EH1_AdMu_100/*_neutron.root");
  //chain->Add("/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel/EH1_6_12/*_neutron.root");
  string chainFile;
  chainFile="/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel/";
  chainFile+=site;
  chainFile+="_AS_TimeAlign/*_neutron.root";
  //chain->Add("/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel/EH1_AS_TimeAlign/*_neutron.root");
  //chain->Add("/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel/EH2_AS_TimeAlign/*_neutron.root");
  //chain->Add("/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel/EH3_AS_TimeAlign/*_neutron.root");
  //site="All";
  chain->Add(chainFile.c_str());

  Int_t entries = chain->GetEntries();
  std::cout<<"num of entry  : "<<entries<<endl;
  chain->Process("FastNeuAna.C+",site.c_str());  //Process all events
  return 0;
}

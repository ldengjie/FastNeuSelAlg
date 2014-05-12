{
#include <iostream>
#include <sstream>
#include <string>

  gROOT->ProcessLine(".L FastNeuAna.C+");

  TChain* chain = new TChain("IWSMuonTree/IWSMuonTree");
  //chain->Add("/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel/EH1_AdMu_100/*_neutron.root");
  chain->Add("/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel/EH1_AdMu_100/*_neutron.root");

  Int_t entries = chain->GetEntries();
  std::cout<<"num of entry  : "<<entries<<endl;
  //chain->Draw("x:y");
  chain->Process("FastNeuAna.C+", "100Mev");  //Process all events
  //chain->Process("FastNeuAna", "_4_28_Michel_II", entries, 0);  //Process all events
  //chain.Process("MySelect","debug");  //Process all events in debug mode
  //chain.Process("MySelect","",1000);  //Process the first 1000 events
  //chain.Process("MySelect","debug",1000,100);  //Process 1000 events start with event 100 in debug mode
}

#include  <iostream>
#include  "TH1F.h"
#include  "TH2F.h"
#include  "TFile.h"
#include  "TString.h"
#include  "TTree.h"
#include  "math.h"
#include  <vector>
#include  "TInterpreter.h"
#include  <stdlib.h>
//#ifdef __MAKECINT__
//#pragma link C++ class vector<float>+;
//#endif
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
    float tag;//(1:fn)(2:DoubleNeutron)(3:MichelEletron)(4:CornerMuon)(5:other)
    float firstHitTime;
    string capVol;
    string genVol;
    event()
    {
        x=0.;
        y=0.;
        z=0.;
        dE=0.;
        quenchedDepE=0.;
        time=0.;
        firstHitTime=0.;
    }
}Event;

vector<Event> eventBuf;
vector< pair<Event,Event> > fnPair;

int muonNum;

TTree* fnTree;
double shiftTime ;
int runNum ;
int fileNum ;
int m_detId ;
double m_trigTime ;
int m_trigSec ;
int m_trigNanoSec ;
int m_nPmt ;
double m_timeToLastIWSMuon;
int m_cleanMuon ;
int m_firstHitTime ;
int m_lastHitTime ;
vector<int> mp_spallDetId ;
vector<double> mp_spallTrigTime;
vector<int> mp_spallTrigSec ;
vector<float> mp_spallEnergy ;

vector<float> mp_spallX ;
vector<float> mp_spallY ;
vector<float> mp_spallZ ;
vector<float> mp_spallScaledE ;
vector<int> mp_spallNPmt ;
vector<int> mp_spallTrigNanoSec;

vector<int> mp_spallFirstHitTime;
vector<int> mp_spallLastHitTime;
vector<float> mp_spallMaxQ ;
vector<float> mp_spallQuadrant ;
vector<float> mp_spallMaxQ_2inchPMT ;
vector<int> mp_spallColumn_2inchPMT ;
vector<float> mp_spallMiddleTimeRMS ;

#ifndef FASTNEUSELAGL_H
#define FASTNEUSELAGL_H

#include "LafKernel/AlgBase.h"
#include "LafKernel/PhyEventBuf.h"
#include "TTree.h"

#include <vector>
#include <map>
#include  <string>

using namespace std;

class FastNeuSelAlg : public AlgBase
{
  public:
    FastNeuSelAlg(const std::string& name);
    virtual ~FastNeuSelAlg(){}

    virtual bool initialize();
    virtual bool execute();
    virtual bool finalize();

  private:
    PhyEventBuf* m_buffer;
    TTree* m_IWSMuonTree;
    map<int, vector<PhyEvent*> > m_spallEventBuffer;

    //Properties of the SpallEvent;
    int runNum;
    int fileNum;
    string fileName;
    int fileSize;
    string shiftTimeFile;
    double shiftTime;
    struct ShiftTimeStruct
    {
        double AD1;
        double AD2;
        double AD3;
        double AD4;
        double IWS;
        double OWS;
        double RPC;
    }shiftTimeStruct;
    map<int,ShiftTimeStruct> shiftTimeMap;
    string runIndex;
    int fileIndex;

    int firstTime,lastTime;
    vector<int>    m_spallDetId;
    vector<int>*   mp_spallDetId;

    vector<int>    m_spallTrigSec;
    vector<double>    m_spallTrigTime;
    vector<double>*   mp_spallTrigTime;
    vector<int>*   mp_spallTrigSec;
    vector<int>    m_spallTrigNanoSec;
    vector<int>*   mp_spallTrigNanoSec;

    vector<float>  m_spallScaledE;
    vector<float>* mp_spallScaledE;
    vector<float>  m_spallEnergy;
    vector<float>* mp_spallEnergy;

    vector<float>  m_spallX;
    vector<float>* mp_spallX;
    vector<float>  m_spallY;
    vector<float>* mp_spallY;
    vector<float>  m_spallZ;
    vector<float>* mp_spallZ;
    vector<int> m_spallFirstHitTime;
    vector<int>* mp_spallFirstHitTime;
    vector<int> m_spallLastHitTime;
    vector<int>* mp_spallLastHitTime;
  
    vector<int>    m_spallNPmt;
    vector<int>*   mp_spallNPmt;
    vector<float>  m_spallMaxQ;
    vector<float>* mp_spallMaxQ;
    vector<float>  m_spallQuadrant;
    vector<float>* mp_spallQuadrant;
    vector<float>  m_spallMaxQ_2inchPMT;
    vector<float>* mp_spallMaxQ_2inchPMT;
    vector<int>    m_spallColumn_2inchPMT;
    vector<int>*   mp_spallColumn_2inchPMT;
    vector<float>  m_spallMiddleTimeRMS;
    vector<float>* mp_spallMiddleTimeRMS;
    vector<float>  m_spallTimePSD;
    vector<float>* mp_spallTimePSD;
    vector<float>  m_spallTimePSD1;
    vector<float>* mp_spallTimePSD1;
    vector<float>  m_spallQ1;
    vector<float>* mp_spallQ1;
    vector<float>  m_spallQ2;
    vector<float>* mp_spallQ2;
    vector<float>  m_spallQ3;
    vector<float>* mp_spallQ3;

    //Properties of the IWSMuon
    int            m_detId;
    float            m_muonE;
    double            m_trigTime;
    int            m_trigSec;
    int            m_trigNanoSec;
    int            m_nPmt;
    Double_t       m_timeToLastIWSMuon;
    int            m_cleanMuon;        

    Double_t       m_timeLastIWSMuon;
    int m_firstHitTime;
    int m_lastHitTime;
    
    
    void fillCoinc(int detId);
    void fillIWSMuon(PhyEvent* curEvt);
    void getADhitTime(PhyEvent* curEvt);
    void getWPhitTime(PhyEvent* curEvt);

    void cleanPara();
    void getShiftTime(PhyEvent* curEvt);
    //void updateVetoWindow(PhyEvent *event);
};

#endif //FASTNEUSELAGL_H

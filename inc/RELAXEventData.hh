///////////////////////////
// Nickolas Upole        //
// University of Chicago //
// Winter 2018           //
// RELAXEventData.hh     //
///////////////////////////

#ifndef RELAXEventData_h
#define RELAXEventData_h 1

#include "globals.hh"

#include <string>
#include <vector>

using std::string;
using std::vector;

class RELAXEventData
{
public:
    RELAXEventData();
    ~RELAXEventData();
    
    // List of Funcions
    void Clear();
    
    // List of Variables
    int iEventID;
    vector<int>* pTrackID;
    vector<int>* pParentID;
    vector<string>* pParticleType;
    vector<string>* pParentType;
    vector<string>* pCreatorProcess;
    vector<string>* pDepositingProcess;
    vector<string>* pVolume;
    vector<double>* pInitX;
    vector<double>* pInitY;
    vector<double>* pInitZ;
    vector<double>* pFinalX;
    vector<double>* pFinalY;
    vector<double>* pFinalZ;
    vector<double>* pInitKinEnergy;
    vector<double>* pFinalKinEnergy;
    vector<double>* pEnergyDeposited;
    vector<double>* pInitTime;
    vector<double>* pFinalTime;
    
    double dFirstInteractionTimeLXe;
    double dTotalEnergyDeposited;
    
    double dEnergyDepositedRegionX;
    double dEnergyDepositedActiveVolume;
    double dEnergyDepositedFiducialVolume;
    double dEnergyDepositedGateLXe;
    double dEnergyDepositedGateGXe;
    double dEnergyDepositedRegionY;
    
    int iTotalInteractionsRegionX;
    int iTotalInteractionsActiveVolume;
    int iTotalInteractionsFiducialVolume;
    int iTotalInteractionsGateLXe;
    int iTotalInteractionsGateGXe;
    int iTotalInteractionsRegionY;
    
    vector<double>* pInteractionXEJ301;
    vector<double>* pInteractionYEJ301;
    vector<double>* pInteractionZEJ301;
    vector<double>* pInteractionTimeEJ301;
    double dTotalEnergyDepositedEJ301;
    double dTotalPEEJ301;
    
    int iFoundFirstNeutronInteraction;
    int iFoundSecondNeutronInteraction;
    
    string sFirstNeutronInteractionProcess;
    string sFirstNeutronInteractionVolume;
    
    double dFirstNeutronInteractionX;
    double dFirstNeutronInteractionY;
    double dFirstNeutronInteractionZ;
    double dFirstNeutronInteractionTime;
    
    string sSecondNeutronInteractionProcess;
    string sSecondNeutronInteractionVolume;
    
    double dSecondNeutronInteractionX;
    double dSecondNeutronInteractionY;
    double dSecondNeutronInteractionZ;
    double dSecondNeutronInteractionTime;
    
    int iElasticScattersPTFE;
    int iElasticScattersSurroundingLXe;
    int iElasticScattersRegionX;
    int iElasticScattersActiveVolume;
    int iElasticScattersFiducialVolume;
    int iElasticScattersGateLXe;
    int iElasticScattersGateGXe;
    int iElasticScattersRegionY;
    int iElasticScattersSurroundingGXe;
    
    int iInelasticScattersPTFE;
    int iInelasticScattersSurroundingLXe;
    int iInelasticScattersRegionX;
    int iInelasticScattersActiveVolume;
    int iInelasticScattersFiducialVolume;
    int iInelasticScattersGateLXe;
    int iInelasticScattersGateGXe;
    int iInelasticScattersRegionY;
    int iInelasticScattersSurroundingGXe;
    
    int iNeutronCapturePTFE;
    int iNeutronCaptureSurroundingLXe;
    int iNeutronCaptureRegionX;
    int iNeutronCaptureActiveVolume;
    int iNeutronCaptureFiducialVolume;
    int iNeutronCaptureGateLXe;
    int iNeutronCaptureGateGXe;
    int iNeutronCaptureRegionY;
    int iNeutronCaptureSurroundingGXe;
    
    int iPEPTFE;
    int iPESurroundingLXe;
    int iPERegionX;
    int iPEActiveVolume;
    int iPEFiducialVolume;
    int iPEGateLXe;
    int iPEGateGXe;
    int iPERegionY;
    int iPESurroundingGXe;
    
    int iComptonScattersPTFE;
    int iComptonScattersSurroundingLXe;
    int iComptonScattersRegionX;
    int iComptonScattersActiveVolume;
    int iComptonScattersFiducialVolume;
    int iComptonScattersGateLXe;
    int iComptonScattersGateGXe;
    int iComptonScattersRegionY;
    int iComptonScattersSurroundingGXe;

    int photonsC;
};

#endif

///////////////////////////
// Nickolas Upole        //
// University of Chicago //
// Winter 2018           //
// RELAXEventData.cc     //
///////////////////////////

#include "RELAXEventData.hh"

RELAXEventData::RELAXEventData()
{
    iEventID = 0;
    
    pTrackID = new vector<int>;
    pParentID = new vector<int>;
    pParticleType = new vector<string>;
    pParentType = new vector<string>;
    pCreatorProcess = new vector<string>;
    pDepositingProcess = new vector<string>;
    pVolume = new vector<string>;
    pInitX = new vector<double>;
    pInitY = new vector<double>;
    pInitZ = new vector<double>;
    pFinalX = new vector<double>;
    pFinalY = new vector<double>;
    pFinalZ = new vector<double>;
    pInitKinEnergy = new vector<double>;
    pFinalKinEnergy = new vector<double>;
    pEnergyDeposited = new vector<double>;
    pInitTime = new vector<double>;
    pFinalTime = new vector<double>;
    
    dFirstInteractionTimeLXe = -1.0;
    dTotalEnergyDeposited = 0.0;
    dEnergyDepositedRegionX = 0.0;
    dEnergyDepositedActiveVolume = 0.0;
    dEnergyDepositedFiducialVolume = 0.0;
    dEnergyDepositedGateLXe = 0.0;
    dEnergyDepositedGateGXe = 0.0;
    dEnergyDepositedRegionY = 0.0;
    
    iTotalInteractionsRegionX = 0;
    iTotalInteractionsActiveVolume = 0;
    iTotalInteractionsFiducialVolume = 0;
    iTotalInteractionsGateLXe = 0;
    iTotalInteractionsGateGXe = 0;
    iTotalInteractionsRegionY = 0;
    
    pInteractionXEJ301 = new vector<double>;
    pInteractionYEJ301 = new vector<double>;
    pInteractionZEJ301 = new vector<double>;
    pInteractionTimeEJ301 = new vector<double>;
    dTotalEnergyDepositedEJ301 = 0.0;
    dTotalPEEJ301 = 0.0;
    
    iFoundFirstNeutronInteraction = 0;
    iFoundSecondNeutronInteraction = 0;
    
    sFirstNeutronInteractionProcess = "none";
    sFirstNeutronInteractionVolume = "none";
    
    dFirstNeutronInteractionX = 0.0;
    dFirstNeutronInteractionY = 0.0;
    dFirstNeutronInteractionZ = 0.0;
    dFirstNeutronInteractionTime = 0.0;
    
    sSecondNeutronInteractionProcess = "none";
    sSecondNeutronInteractionVolume = "none";
    
    dSecondNeutronInteractionX = 0.0;
    dSecondNeutronInteractionY = 0.0;
    dSecondNeutronInteractionZ = 0.0;
    dSecondNeutronInteractionTime = 0.0;
    
    iElasticScattersPTFE = 0;
    iElasticScattersSurroundingLXe = 0;
    iElasticScattersRegionX = 0;
    iElasticScattersActiveVolume = 0;
    iElasticScattersFiducialVolume = 0;
    iElasticScattersGateLXe = 0;
    iElasticScattersGateGXe = 0;
    iElasticScattersRegionY = 0;
    iElasticScattersSurroundingGXe = 0;
    
    iInelasticScattersPTFE = 0;
    iInelasticScattersSurroundingLXe = 0;
    iInelasticScattersRegionX = 0;
    iInelasticScattersActiveVolume = 0;
    iInelasticScattersFiducialVolume = 0;
    iInelasticScattersGateLXe = 0;
    iInelasticScattersGateGXe = 0;
    iInelasticScattersRegionY = 0;
    iInelasticScattersSurroundingGXe = 0;
    
    iNeutronCapturePTFE = 0;
    iNeutronCaptureSurroundingLXe = 0;
    iNeutronCaptureRegionX = 0;
    iNeutronCaptureActiveVolume = 0;
    iNeutronCaptureFiducialVolume = 0;
    iNeutronCaptureGateLXe = 0;
    iNeutronCaptureGateGXe = 0;
    iNeutronCaptureRegionY = 0;
    iNeutronCaptureSurroundingGXe = 0;
    
    iPEPTFE = 0;
    iPESurroundingLXe = 0;
    iPERegionX = 0;
    iPEActiveVolume = 0;
    iPEFiducialVolume = 0;
    iPEGateLXe = 0;
    iPEGateGXe = 0;
    iPERegionY = 0;
    iPESurroundingGXe = 0;
    
    iComptonScattersPTFE = 0;
    iComptonScattersSurroundingLXe = 0;
    iComptonScattersRegionX = 0;
    iComptonScattersActiveVolume = 0;
    iComptonScattersFiducialVolume = 0;
    iComptonScattersGateLXe = 0;
    iComptonScattersGateGXe = 0;
    iComptonScattersRegionY = 0;
    iComptonScattersSurroundingGXe = 0;

//////// Jimmy's Photon Capture Variable ////
    photonsC = 0; // Photons captured.
/////////////////////////////////////////////
}

RELAXEventData::~RELAXEventData()
{
    delete pTrackID;
    delete pParentID;
    delete pParticleType;
    delete pParentType;
    delete pCreatorProcess;
    delete pDepositingProcess;
    delete pVolume;
    delete pInitX;
    delete pInitY;
    delete pInitZ;
    delete pFinalX;
    delete pFinalY;
    delete pFinalZ;
    delete pInitKinEnergy;
    delete pFinalKinEnergy;
    delete pEnergyDeposited;
    delete pInitTime;
    delete pFinalTime;
    
    delete pInteractionXEJ301;
    delete pInteractionYEJ301;
    delete pInteractionZEJ301;
    delete pInteractionTimeEJ301;
}

void RELAXEventData::Clear()
{
    iEventID = 0;
    
    pTrackID->clear();
    pParentID->clear();
    pParticleType->clear();
    pParentType->clear();
    pCreatorProcess->clear();
    pDepositingProcess->clear();
    pVolume->clear();
    pInitX->clear();
    pInitY->clear();
    pInitZ->clear();
    pFinalX->clear();
    pFinalY->clear();
    pFinalZ->clear();
    pInitKinEnergy->clear();
    pFinalKinEnergy->clear();
    pEnergyDeposited->clear();
    pInitTime->clear();
    pFinalTime->clear();
    
    dFirstInteractionTimeLXe = -1.0;
    dTotalEnergyDeposited = 0.0;
    
    dEnergyDepositedRegionX = 0.0;
    dEnergyDepositedActiveVolume = 0.0;
    dEnergyDepositedFiducialVolume = 0.0;
    dEnergyDepositedGateLXe = 0.0;
    dEnergyDepositedGateGXe = 0.0;
    dEnergyDepositedRegionY = 0.0;
    
    iTotalInteractionsRegionX = 0;
    iTotalInteractionsActiveVolume = 0;
    iTotalInteractionsFiducialVolume = 0;
    iTotalInteractionsGateLXe = 0;
    iTotalInteractionsGateGXe = 0;
    iTotalInteractionsRegionY = 0;
    
    pInteractionXEJ301->clear();
    pInteractionYEJ301->clear();
    pInteractionZEJ301->clear();
    pInteractionTimeEJ301->clear();
    dTotalEnergyDepositedEJ301 = 0.0;
    dTotalPEEJ301 = 0.0;
    
    iFoundFirstNeutronInteraction = 0;
    iFoundSecondNeutronInteraction = 0;
    
    sFirstNeutronInteractionProcess = "none";
    sFirstNeutronInteractionVolume = "none";
    
    dFirstNeutronInteractionX = 0.0;
    dFirstNeutronInteractionY = 0.0;
    dFirstNeutronInteractionZ = 0.0;
    dFirstNeutronInteractionTime = 0.0;
    
    sSecondNeutronInteractionProcess = "none";
    sSecondNeutronInteractionVolume = "none";
    
    dSecondNeutronInteractionX = 0.0;
    dSecondNeutronInteractionY = 0.0;
    dSecondNeutronInteractionZ = 0.0;
    dSecondNeutronInteractionTime = 0.0;
    
    
    iElasticScattersPTFE = 0;
    iElasticScattersSurroundingLXe = 0;
    iElasticScattersRegionX = 0;
    iElasticScattersActiveVolume = 0;
    iElasticScattersFiducialVolume = 0;
    iElasticScattersGateLXe = 0;
    iElasticScattersGateGXe = 0;
    iElasticScattersRegionY = 0;
    iElasticScattersSurroundingGXe = 0;
    
    iInelasticScattersPTFE = 0;
    iInelasticScattersSurroundingLXe = 0;
    iInelasticScattersRegionX = 0;
    iInelasticScattersActiveVolume = 0;
    iInelasticScattersFiducialVolume = 0;
    iInelasticScattersGateLXe = 0;
    iInelasticScattersGateGXe = 0;
    iInelasticScattersRegionY = 0;
    iInelasticScattersSurroundingGXe = 0;
    
    iNeutronCapturePTFE = 0;
    iNeutronCaptureSurroundingLXe = 0;
    iNeutronCaptureRegionX = 0;
    iNeutronCaptureActiveVolume = 0;
    iNeutronCaptureFiducialVolume = 0;
    iNeutronCaptureGateLXe = 0;
    iNeutronCaptureGateGXe = 0;
    iNeutronCaptureRegionY = 0;
    iNeutronCaptureSurroundingGXe = 0;
    
    iPEPTFE = 0;
    iPESurroundingLXe = 0;
    iPERegionX = 0;
    iPEActiveVolume = 0;
    iPEFiducialVolume = 0;
    iPEGateLXe = 0;
    iPEGateGXe = 0;
    iPERegionY = 0;
    iPESurroundingGXe = 0;
    
    iComptonScattersPTFE = 0;
    iComptonScattersSurroundingLXe = 0;
    iComptonScattersRegionX = 0;
    iComptonScattersActiveVolume = 0;
    iComptonScattersFiducialVolume = 0;
    iComptonScattersGateLXe = 0;
    iComptonScattersGateGXe = 0;
    iComptonScattersRegionY = 0;
    iComptonScattersSurroundingGXe = 0;

    photonsC = 0;
}

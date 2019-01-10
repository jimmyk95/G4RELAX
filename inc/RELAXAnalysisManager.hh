/////////////////////////////
// Nickolas Upole          //
// University of Chicago   //
// Winter 2018             //
// RELAXAnalysisManager.hh //
/////////////////////////////

#ifndef RELAXAnalysisManager_h
#define RELAXAnalysisManager_h 1

#include "globals.hh"

#include "G4Run.hh"
#include "G4Event.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include "G4TrackVector.hh"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"

#include "RELAXAnalysisMessenger.hh"
#include "RELAXEventData.hh"

using std::map;

class RELAXAnalysisManager
{
public:
    RELAXAnalysisManager();
    ~RELAXAnalysisManager();
    
    // List of Functions
    void BeginOfRunAction(const G4Run* pRun);
    void BeginOfEventAction(const G4Event* pEvent);
    void SteppingAction(const G4Step* pStep);
    void EndOfEventAction(const G4Event* pEvent);
    void EndOfRunAction(const G4Run* pRun);
    
    void SetFilenameReference(G4String* mFilenameReference);
    
private:
    // List of Variables
    RELAXAnalysisMessenger* pRELAXAnalysisMessenger;
    
    G4String* pFilenameReference;
    
    TFile* pFile;
    TTree* pTree1;
    TTree* pTree2;
    TTree* pTree3;
    TTree* pTree4;
    TTree* pTree5;
    
    G4Track* pTrack;
    
    RELAXEventData* pRELAXEventData;
    
    G4String sParticleType;
    G4String sDepositingProcess;
    G4String sVolume;
    G4double dActiveVolumeX;
    G4double dActiveVolumeY;
    G4double dActiveVolumeZ;
    G4double dFiducialVolumeRadius;
    G4double dFiducialVolumeHeight;
    G4double dInteractionX;
    G4double dInteractionY;
    G4double dInteractionZ;
    G4double dInteractionRadius;
    G4double dInteractionTime;
    G4double dEnergyDeposited;
    
    const vector<const G4Track*>* pSecondaryTrackVector;
    G4String sSecondaryVolume;
    G4String sSecondaryParticle;
    G4String sSecondaryParticleName;
    G4String sSecondaryParticleType;
    
    map<int, G4String>* pMapParticleType;

    // Jimmy's added variables
    G4int photonsG;
    G4int photonsC;
    G4double pCaptured;
    G4int m_iPmtHitsCollectionID; 
    //G4int iNbPmtHits;
};

#endif

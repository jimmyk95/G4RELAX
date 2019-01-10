//////////////////////////////
// Nickolas Upole           //
// University of Chicago    //
// Winter 2018              //
// RELAXStackingAction.hh   //
//////////////////////////////

#ifndef RELAXStackingAction_h
#define RELAXStackingAction_h 1

#include "globals.hh"

#include "G4UserStackingAction.hh"
#include "G4Track.hh"

class RELAXStackingAction : public G4UserStackingAction
{
public:
    RELAXStackingAction();
    ~RELAXStackingAction();

    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* pTrack);
    
private:
    G4String sVolume;
    G4String sParticleType;
    G4String sParticleName;
};

#endif

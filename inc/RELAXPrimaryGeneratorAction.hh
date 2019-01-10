/////////////////////////////////////
// Nickolas Upole                  //
// University of Chicago           //
// WInter 2018                     //
// RELAXPrimaryGeneratorAction.hh" //
/////////////////////////////////////

#ifndef RELAXPrimaryGeneratorAction_h
#define RELAXPrimaryGeneratorAction_h 1

#include "globals.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"

class RELAXPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    RELAXPrimaryGeneratorAction();
    virtual ~RELAXPrimaryGeneratorAction();

    // List of Functions
    virtual void GeneratePrimaries(G4Event* pEvent);

    // List of Members
    G4GeneralParticleSource* pGeneralParticleSource;
};

#endif

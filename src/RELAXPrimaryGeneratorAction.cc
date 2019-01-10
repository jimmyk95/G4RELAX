////////////////////////////////////
// Nickolas Upole                 //
// University of Chicago          //
// Winter 2016                    //
// RELAXPrimaryGeneratorAction.cc //
////////////////////////////////////

#include "RELAXPrimaryGeneratorAction.hh"

RELAXPrimaryGeneratorAction::RELAXPrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
  pGeneralParticleSource = new G4GeneralParticleSource();
}

RELAXPrimaryGeneratorAction::~RELAXPrimaryGeneratorAction()
{
  delete pGeneralParticleSource;
}

void RELAXPrimaryGeneratorAction::GeneratePrimaries(G4Event* pEvent)
{
  pGeneralParticleSource->GeneratePrimaryVertex(pEvent);
}

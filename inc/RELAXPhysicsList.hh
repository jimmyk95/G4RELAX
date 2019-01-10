///////////////////////////
// Nickolas Upole        //
// University of Chicago //
// Winter 2018           //
// RELAXPhysicsList.hh   //
///////////////////////////

#ifndef RELAXPhysicsList_h
#define RELAXPhysicsList_h 1

#include "globals.hh"

#include "G4VUserPhysicsList.hh"

#include "RELAXPhysicsMessenger.hh"

class RELAXPhysicsList : public G4VUserPhysicsList
{
public:
    RELAXPhysicsList();
    ~RELAXPhysicsList();

    // List of Functions
    void ConstructParticle();
    void ConstructProcess();
    
    void SetScintillation(G4bool mScintillation);
    void SetCerenkov(G4bool mCerenkov);

private:
    // List of Functions
    void ConstructBosons();
    void ConstructLeptons();
    void ConstructHadrons();
    void ConstructShortLived();
    void ConstructEMPhysics();
    void ConstructHadronPhysics();
    void ConstructOpticalPhotonPhysics();
    void ConstructDecayPhysics();
    void AddTransportation();
    void SetCuts();
    
    // List of Variables
    RELAXPhysicsMessenger* pRELAXPhysicsMessenger;
    
    G4bool bScintillation;
    G4bool bCerenkov;
};

#endif

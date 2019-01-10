//////////////////////////////
// Nickolas Upole           //
// University of Chicago    //
// Winter 2018              //
// RELAXPhysicsMessenger.hh //
//////////////////////////////

#ifndef RELAXPhysicsMessenger_h
#define RELAXPhysicsMessenger_h 1

#include "globals.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithABool.hh"

class RELAXPhysicsList;

class RELAXPhysicsMessenger : public G4UImessenger
{
public:
    RELAXPhysicsMessenger(RELAXPhysicsList* RELAXPhysicsList);
    ~RELAXPhysicsMessenger();
    
    void SetNewValue(G4UIcommand* pG4UICommand, G4String sNewValue);
    
private:
    RELAXPhysicsList* pRELAXPhysics;
    
    G4UIdirectory* pRELAXPhysicsDir;
    
    G4UIcmdWithABool* pSetScintillationCmd;
    G4UIcmdWithABool* pSetCerenkovCmd;
};

#endif

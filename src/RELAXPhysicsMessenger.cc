//////////////////////////////
// Nickolas Upole           //
// University of Chicago    //
// Winter 2018              //
// RELAXPhysicsMessenger.cc //
//////////////////////////////

#include "RELAXPhysicsMessenger.hh"
#include "RELAXPhysicsList.hh"

RELAXPhysicsMessenger::RELAXPhysicsMessenger(RELAXPhysicsList* pRELAXPhysicsList) : pRELAXPhysics(pRELAXPhysicsList)
{
    ///////////////////////////////
    // Set the Physics Directory //
    ///////////////////////////////
    pRELAXPhysicsDir = new G4UIdirectory("/RELAX/physics/");
    pRELAXPhysicsDir->SetGuidance("Control of the RELAX Physics.");
    
    ///////////////////////////////
    // Set the Detector Commands //
    ///////////////////////////////
    pSetScintillationCmd = new G4UIcmdWithABool("/RELAX/physics/SetScintillation", this);
    pSetScintillationCmd->SetGuidance("Switch scintillation on (true) or off (false).");
    pSetScintillationCmd->SetDefaultValue(false);
    pSetScintillationCmd->AvailableForStates(G4State_PreInit);
    
    pSetCerenkovCmd = new G4UIcmdWithABool("/RELAX/physics/SetCerenkov", this);
    pSetCerenkovCmd->SetGuidance("Switch Cerenkov on (true) or off (false).");
    pSetCerenkovCmd->SetDefaultValue(false);
    pSetCerenkovCmd->AvailableForStates(G4State_PreInit);
}

RELAXPhysicsMessenger::~RELAXPhysicsMessenger()
{
    ///////////////////////////////////////
    // Delete the Commands and Directory //
    ///////////////////////////////////////
    delete pSetScintillationCmd;
    delete pSetCerenkovCmd;
    
    delete pRELAXPhysicsDir;
}

void RELAXPhysicsMessenger::SetNewValue(G4UIcommand* pG4UICommand, G4String sNewValue)
{
    ///////////////////////////////////
    // Update Value for Physics List //
    ///////////////////////////////////
    if(pG4UICommand == pSetScintillationCmd)
    {
        pRELAXPhysics->SetScintillation(&sNewValue);
    }
    
    else if(pG4UICommand == pSetCerenkovCmd)
    {
        pRELAXPhysics->SetCerenkov(&sNewValue);
    }
}

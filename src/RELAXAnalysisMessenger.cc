///////////////////////////////
// Nickolas Upole            //
// University of Chicago     //
// Winter 2018               //
// RELAXAnalysisMessenger.cc //
///////////////////////////////

#include "RELAXAnalysisMessenger.hh"
#include "RELAXAnalysisManager.hh"

RELAXAnalysisMessenger::RELAXAnalysisMessenger(RELAXAnalysisManager* pRELAXAnalysisManager) : pRELAXAM(pRELAXAnalysisManager)
{
    ////////////////////////////////
    // Set the Analysis Directory //
    ////////////////////////////////
    pRELAXAnalysisDir = new G4UIdirectory("/RELAX/analysis/");
    pRELAXAnalysisDir->SetGuidance("Control of the RELAX Analysis.");
    
    ///////////////////////////////
    // Set the Analysis Commands //
    ///////////////////////////////
    pSetFilenameReferenceCmd = new G4UIcmdWithAString("/RELAX/analysis/SetFilenameReference", this);
    pSetFilenameReferenceCmd->SetGuidance("Set the Root File Reference.");
    pSetFilenameReferenceCmd->SetDefaultValue("./Results/events.root");
    pSetFilenameReferenceCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

RELAXAnalysisMessenger::~RELAXAnalysisMessenger()
{
    ///////////////////////////////////////
    // Delete the Commands and Directory //
    ///////////////////////////////////////
    delete pSetFilenameReferenceCmd;
    
    delete pRELAXAnalysisDir;
}

void RELAXAnalysisMessenger::SetNewValue(G4UIcommand* pG4UICommand, G4String sNewValue)
{
    ////////////////////////////////////////////
    // Update Value for Detector Construction //
    ////////////////////////////////////////////
    if(pG4UICommand == pSetFilenameReferenceCmd)
    {
        pRELAXAM->SetFilenameReference(&sNewValue);

    }
}

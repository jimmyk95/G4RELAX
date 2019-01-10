///////////////////////////
// Nickolas Upole        //
// University of Chicago //
// Winter 2018           //
// RELAX.cc              //
///////////////////////////

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"

#include "RELAXDetectorConstruction.hh"
#include "RELAXPhysicsList.hh"
#include "RELAXPrimaryGeneratorAction.hh"
#include "RELAXRunAction.hh"
#include "RELAXEventAction.hh"
#include "RELAXSteppingAction.hh"
#include "RELAXStackingAction.hh"
#include "RELAXAnalysisManager.hh"

int main(int argc, char** argv)
{
    ////////////////////////////////////////////
    // Construct Run Manager/Analysis Manager //
    ////////////////////////////////////////////
    G4RunManager* pRunManager = new G4RunManager();
    RELAXAnalysisManager* pRELAXAnalysisManager = new RELAXAnalysisManager();

    ////////////////////////////////
    // Set Initialization Classes //
    ////////////////////////////////
    pRunManager->SetUserInitialization(new RELAXDetectorConstruction());
    pRunManager->SetUserInitialization(new RELAXPhysicsList());

    ////////////////////////
    // Set Action Classes //
    ////////////////////////
    pRunManager->SetUserAction(new RELAXPrimaryGeneratorAction());
    pRunManager->SetUserAction(new RELAXRunAction(pRELAXAnalysisManager));
    pRunManager->SetUserAction(new RELAXEventAction(pRELAXAnalysisManager));
    pRunManager->SetUserAction(new RELAXSteppingAction(pRELAXAnalysisManager));
    pRunManager->SetUserAction(new RELAXStackingAction());
    pRunManager->Initialize();

    /////////////////////////////////////
    // Construct Visualization Manager //
    /////////////////////////////////////
    G4VisManager* pVisualManager = new G4VisExecutive();
    pVisualManager->Initialize();

    //////////////////////////////////
    // Construct UI Manager/Session //
    //////////////////////////////////
    G4UImanager* pUIManager = G4UImanager::GetUIpointer();
    G4UIsession* pUISession = new G4UIterminal(new G4UItcsh());
    pUISession->SessionStart();

    ///////////////////
    // Terminate Job //
    ///////////////////
    delete pUISession;
    delete pRELAXAnalysisManager;
    delete pVisualManager;
    delete pRunManager;

    return 0;
}

///////////////////////////
// Nickolas Upole        //
// University of Chicago //
// Winter 2018           //
// RELAXEventAction.cc   //
///////////////////////////

#include "RELAXEventAction.hh"

RELAXEventAction::RELAXEventAction(RELAXAnalysisManager* pRELAXAM) : G4UserEventAction()
{
    pRELAXAnalysisManager = pRELAXAM;
}

RELAXEventAction::~RELAXEventAction()
{
    
}

void RELAXEventAction::BeginOfEventAction(const G4Event* pEvent)
{
    if(pEvent->GetEventID() % 10000 == 0)
    {
        G4cout << "Begin Event: " << pEvent->GetEventID() << G4endl;
    }
    
    if(pRELAXAnalysisManager)
    {
        pRELAXAnalysisManager->BeginOfEventAction(pEvent);
    }
}

void RELAXEventAction::EndOfEventAction(const G4Event* pEvent)
{
    if(pRELAXAnalysisManager)
    {
        pRELAXAnalysisManager->EndOfEventAction(pEvent);
    }
}

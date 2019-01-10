//////////////////////////////
// Nickolas Upole           //
// University of Chicago    //
// Winter 2018              //
// RELAXSteppingAction.cc   //
//////////////////////////////

#include "RELAXSteppingAction.hh"

RELAXSteppingAction::RELAXSteppingAction(RELAXAnalysisManager* pRELAXAM) : G4UserSteppingAction()
{
    pRELAXAnalysisManager = pRELAXAM;
}

RELAXSteppingAction::~RELAXSteppingAction()
{
    
}

void RELAXSteppingAction::UserSteppingAction(const G4Step* pStep)
{
    if(pRELAXAnalysisManager)
    {
        pRELAXAnalysisManager->SteppingAction(pStep);
    }
}

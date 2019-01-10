///////////////////////////
// Nickolas Upole        //
// University of Chicago //
// Winter 2018           //
// RELAXRunAction.cc     //
///////////////////////////

#include "RELAXRunAction.hh"

RELAXRunAction::RELAXRunAction(RELAXAnalysisManager* pRELAXAM) : G4UserRunAction()
{
    pRELAXAnalysisManager = pRELAXAM;
}

RELAXRunAction::~RELAXRunAction()
{
    
}

void RELAXRunAction::BeginOfRunAction(const G4Run* pRun)
{
    if(pRELAXAnalysisManager)
    {
        pRELAXAnalysisManager->BeginOfRunAction(pRun);
    }
}

void RELAXRunAction::EndOfRunAction(const G4Run* pRun)
{
    if(pRELAXAnalysisManager)
    {
        pRELAXAnalysisManager->EndOfRunAction(pRun);
    }
}

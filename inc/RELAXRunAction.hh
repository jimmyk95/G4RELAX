///////////////////////////
// Nickolas Upole        //
// University of Chicago //
// Winter 2018           //
// RELAXRunAction.hh     //
///////////////////////////

#ifndef RELAXRunAction_h
#define RELAXRunAction_h 1

#include "globals.hh"

#include "G4UserRunAction.hh"
#include "G4Run.hh"

#include "RELAXAnalysisManager.hh"

class RELAXRunAction : public G4UserRunAction
{
public:
    RELAXRunAction(RELAXAnalysisManager* pRELAXAM = 0);
    ~RELAXRunAction();
    
    // List of Functions
    virtual void BeginOfRunAction(const G4Run* pRun);
    virtual void EndOfRunAction(const G4Run* pRun);
    
private:
    // List of Variables
    RELAXAnalysisManager* pRELAXAnalysisManager;
};

#endif

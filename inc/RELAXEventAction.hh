///////////////////////////
// Nickolas Upole        //
// University of Chicago //
// Winter 2018           //
// RELAXEventAction.hh   //
///////////////////////////

#ifndef RELAXEventAction_h
#define RELAXEventAction_h 1

#include "globals.hh"

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "RELAXAnalysisManager.hh"

class RELAXEventAction : public G4UserEventAction
{
public:
    RELAXEventAction(RELAXAnalysisManager* pRELAXAM = 0);
    ~RELAXEventAction();
    
    // List of Functions
    virtual void BeginOfEventAction(const G4Event* pEvent);
    virtual void EndOfEventAction(const G4Event* pEvent);
    
private:
    // List of Variables
    RELAXAnalysisManager* pRELAXAnalysisManager;
};

#endif

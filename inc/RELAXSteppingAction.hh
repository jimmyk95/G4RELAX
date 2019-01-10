//////////////////////////////
// Nickolas Upole           //
// University of Chicago    //
// Winter 2018              //
// RELAXSteppingAction.hh   //
//////////////////////////////

#ifndef RELAXSteppingAction_h
#define RELAXSteppingAction_h 1

#include "globals.hh"

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "RELAXAnalysisManager.hh"

class RELAXSteppingAction : public G4UserSteppingAction
{
public:
    RELAXSteppingAction(RELAXAnalysisManager* pRELAXAM = 0);
    ~RELAXSteppingAction();
    
    // List of Functions
    virtual void UserSteppingAction(const G4Step* pStep);
    
private:
    // List of Variables
    RELAXAnalysisManager* pRELAXAnalysisManager;
};

#endif

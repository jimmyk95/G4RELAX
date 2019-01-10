///////////////////////////////
// Nickolas Upole            //
// University of Chicago     //
// Winter 2018               //
// RELAXAnalysisMessenger.cc //
///////////////////////////////

#ifndef RELAXAnalysisMessenger_h
#define RELAXAnalysisMessenger_h 1

#include "globals.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"

class RELAXAnalysisManager;

class RELAXAnalysisMessenger : public G4UImessenger
{
public:
    RELAXAnalysisMessenger(RELAXAnalysisManager* pRELAXAnalysisManager);
    ~RELAXAnalysisMessenger();
    
    void SetNewValue(G4UIcommand* pG4UICommand, G4String sNewValue);
    
private:
    RELAXAnalysisManager* pRELAXAM;
    
    G4UIdirectory* pRELAXAnalysisDir;
    
    G4UIcmdWithAString* pSetFilenameReferenceCmd;
};

#endif

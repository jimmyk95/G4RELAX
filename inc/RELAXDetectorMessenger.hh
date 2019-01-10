///////////////////////////////
// Nickolas Upole            //
// University of Chicago     //
// Winter 2018               //
// RELAXDetectorMessenger.hh //
///////////////////////////////

#ifndef RELAXDetectorMessenger_h
#define RELAXDetectorMessenger_h 1

#include "globals.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"

class RELAXDetectorConstruction;

class RELAXDetectorMessenger : public G4UImessenger
{
public:
    RELAXDetectorMessenger(RELAXDetectorConstruction* pRELAXDetectorConstruction);
    ~RELAXDetectorMessenger();

    void SetNewValue(G4UIcommand* pG4UICommand, G4String sNewValue);

private:
    RELAXDetectorConstruction* pRELAXDetector;

    G4UIdirectory* pRELAXDir;
    G4UIdirectory* pRELAXDetectorDir;

    G4UIcmdWithAString* pPTFEIndexOfRefractionDataCmd;
    G4UIcmdWithAString* pPTFEAbsorptionLengthDataCmd;
    G4UIcmdWithAString* pPTFEReflectivityDataCmd;
    G4UIcmdWithAString* pPTFESpecularLobeConstantDataCmd;
    G4UIcmdWithAString* pPTFESpecularSpikeConstantDataCmd;
    G4UIcmdWithAString* pPTFEBackscatterConstantDataCmd;
    G4UIcmdWithAString* pPTFEEfficiencyDataCmd;

    G4UIcmdWithAString* pLXeScintillationSpectrumDataCmd;
    G4UIcmdWithAString* pLXeIndexOfRefractionDataCmd;
    G4UIcmdWithAString* pLXeAbsorptionLengthDataCmd;
    G4UIcmdWithAString* pLXeRayleighScatteringLengthDataCmd;
    G4UIcmdWithADouble* pLXeFanoFactorCmd;
    G4UIcmdWithADoubleAndUnit* pLXeFastScintillationTimeConstantCmd;
    G4UIcmdWithADoubleAndUnit* pLXeSlowScintillationTimeConstantCmd;
    G4UIcmdWithAString* pLXeDensityDataCmd;

    G4UIcmdWithAString* pGXeScintillationSpectrumDataCmd;
    G4UIcmdWithAString* pGXeIndexOfRefractionDataCmd;
    G4UIcmdWithAString* pGXeAbsorptionLengthDataCmd;
    G4UIcmdWithAString* pGXeRayleighScatteringLengthDataCmd;
    G4UIcmdWithADouble* pGXeFanoFactorCmd;
    G4UIcmdWithADoubleAndUnit* pGXeFastScintillationTimeConstantCmd;
    G4UIcmdWithADoubleAndUnit* pGXeSlowScintillationTimeConstantCmd;
    G4UIcmdWithAString* pGXeDensityDataCmd;

    G4UIcmdWithADouble* pXePressureCmd;
};

#endif

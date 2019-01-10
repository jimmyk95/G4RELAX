//////////////////////////////////
// Bruno Petrucci               //
// University of Chicago        //
// Fall 2017                    //
// RELAXDetectorConstruction.hh //
//////////////////////////////////

#ifndef RELAXDetectorConstruction_h
#define RELAXDetectorConstruction_h 1

#include <math.h>
#include <vector>
#include <iostream>

#include "globals.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4Box.hh"
#include "G4GenericPolycone.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"

#include "RELAXDetectorMessenger.hh"

using namespace std;
using namespace CLHEP;

class RELAXDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    RELAXDetectorConstruction();
    virtual ~RELAXDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4String* pDummyString;
    ifstream* ifsDataFile;

    G4double dWavelength;
    G4double dEnergy;
    G4double dData;
    vector<G4double>* pEnergy;
    vector<G4double>* pData;

    G4String* pPTFEIndexOfRefractionData;
    G4String* pPTFEAbsorptionLengthData;
    G4String* pPTFEReflectivityData;
    G4String* pPTFESpecularLobeConstantData;
    G4String* pPTFESpecularSpikeConstantData;
    G4String* pPTFEBackscatterConstantData;
    G4String* pPTFEEfficiencyData;

    G4int dLXeMaterialCounter;
    G4double dLXePressure;
    G4double dLXeDensity;

    vector<G4double>* pLXePressure;
    vector<G4double>* pLXeDensity;

    G4int dLGXeMaterialCounter;
    G4double dGXePressure;
    G4double dGXeDensity;

    vector<G4double>* pGXePressure;
    vector<G4double>* pGXeDensity;

    G4String* pLXeScintillationSpectrumData;
    G4String* pLXeIndexOfRefractionData;
    G4String* pLXeAbsorptionLengthData;
    G4String* pLXeRayleighScatteringLengthData;
    G4double dLXeFanoFactor;
    G4double dLXeFastScintillationTimeConstant;
    G4double dLXeSlowScintillationTimeConstant;
    G4String* pLXeDensityData;

    G4String* pGXeScintillationSpectrumData;
    G4String* pGXeIndexOfRefractionData;
    G4String* pGXeAbsorptionLengthData;
    G4String* pGXeRayleighScatteringLengthData;
    G4double dGXeFanoFactor;
    G4double dGXeFastScintillationTimeConstant;
    G4double dGXeSlowScintillationTimeConstant;
    G4String* pGXeDensityData;

    G4String* pQuartzIndexOfRefractionData;
    G4String* pQuartzAbsorptionLengthData;

    G4double dXePressure;
    G4double dXeTemperature;

    RELAXDetectorMessenger* pRELAXDetectorMessenger;
    G4MaterialPropertiesTable* pMaterialPropertyTable;

    G4double LinearInterpolator();
    void SetPTFEIndexOfRefraction(G4String* mPTFEIndexOfRefractionData);
    void SetPTFEAbsorptionLengthData(G4String* mPTFEAbsorptionLengthData);
    void SetPTFEReflectivity(G4String* mPTFEReflectivityData);
    void SetPTFESpecularLobeConstant(G4String* mPTFESpecularLobeConstantData);
    void SetPTFESpecularSpikeConstant(G4String* mPTFESpecularSpikeConstantData);
    void SetPTFEBackscatterConstant(G4String* mPTFEBackscatterConstantData);
    void SetPTFEEfficiency(G4String* mPTFEEfficiencyData);

    void SetLXeScintillationSpectrumData(G4String* mLXeScintillationSpectrumData);
    void SetLXeIndexOfRefractionData(G4String* mLXeIndexOfRefractionData);
    void SetLXeAbsorptionLengthData(G4String* mLXeAbsorptionLengthData);
    void SetLXeRayleighScatteringLengthData(G4String* mLXeRayleighScatteringLengthData);
    void SetLXeFanoFactor(G4double mLXeFanoFactor);
    void SetLXeFastScintillationTimeConstant(G4double mLXeFastScintillationTimeConstant);
    void SetLXeSlowScintillationTimeConstant(G4double mLXeSlowScintillationTimeConstant);
    void SetLXeDensityData(G4String* mLXeDensityData);

    void SetGXeScintillationSpectrumData(G4String* mGXeScintillationSpectrumData);
    void SetGXeIndexOfRefractionData(G4String* mGXeIndexOfRefractionData);
    void SetGXeAbsorptionLengthData(G4String* mGXeAbsorptionLengthData);
    void SetGXeRayleighScatteringLengthData(G4String* mGXeRayleighScatteringLengthData);
    void SetGXeFanoFactor(G4double mGXeFanoFactor);
    void SetGXeFastScintillationTimeConstant(G4double mGXeFastScintillationTimeConstant);
    void SetGXeSlowScintillationTimeConstant(G4double mGXeSlowScintillationTimeConstant);
    void SetGXeDensityData(G4String* mGXeDensityData);

    void SetQuartzIndexOfRefraction(G4String* mQuartzIndexOfRefractionData);
    void SetQuartzAbsorptionLength(G4String* mQuartzAbsorptionLengthData);

    void SetXePressure(G4double mXePressure);

private:
    // List of Functions
    void DefineMaterials();
    void ConstructLaboratory();
    void ConstructCryostat();
    std::map<G4String, G4Material*>* GetMaterialTable();

    // List of Volumes
    G4LogicalVolume* pMotherLV;

    G4LogicalVolume* pLaboratoryLV;
    G4VPhysicalVolume* pLaboratoryPV;

    G4LogicalVolume* pPTFE00LV;
    G4VPhysicalVolume* pPTFE00PV;
    G4LogicalVolume* pPTFE01LV;
    G4VPhysicalVolume* pPTFE01PV;
    G4LogicalVolume* pPTFE02LV;
    G4VPhysicalVolume* pPTFE02PV;
    G4LogicalVolume* pPTFE03BLV;
    G4VPhysicalVolume* pPTFE03BPV;
    G4LogicalVolume* pPTFE03TLV;
    G4VPhysicalVolume* pPTFE03TPV;
    G4LogicalVolume* pPTFE04LV;
    G4VPhysicalVolume* pPTFE04PV;
    G4LogicalVolume* pPTFE05LV;
    G4VPhysicalVolume* pPTFE05PV;
    G4LogicalVolume* pPTFE06LV;
    G4VPhysicalVolume* pPTFE06PV;
    G4LogicalVolume* pPMTRingLV;
    G4VPhysicalVolume* pPMTRingPV;
    G4LogicalVolume* pGridLV;
    G4VPhysicalVolume* pCathodePV;
    G4VPhysicalVolume* pGatePV;
    G4VPhysicalVolume* pAnodePV;
    G4VPhysicalVolume* pScreeningMeshPV;

    G4double dLaboratoryHeight;
    G4double dFloorHeight;
};

#endif

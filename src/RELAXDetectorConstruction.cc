/////////////////////////////////////
// Nickolas Upole & Bruno Petrucci //
// University of Chicago           //
// Fall 2017                       //
// RELAXDetectorConstruction.cc    //
/////////////////////////////////////

#include "G4ios.hh"
#include "G4UnitsTable.hh"

#include "math.h"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"

#include "RELAXDetectorConstruction.hh"
#include "RELAXDetectorMessenger.hh"
#include "Xenon1tPmtSensitiveDetector.hh"
#include <G4SDManager.hh>

RELAXDetectorConstruction::RELAXDetectorConstruction() : G4VUserDetectorConstruction()
{
    pRELAXDetectorMessenger = new RELAXDetectorMessenger(this);

    pDummyString = new G4String();
    ifsDataFile = new ifstream();

    pEnergy = new vector<G4double>;
    pData = new vector<G4double>;

    pPTFEIndexOfRefractionData = new G4String("./data/PTFE/IndexOfRefraction.txt");
    pPTFEAbsorptionLengthData = new G4String("./data/PTFE/AbsorptionLength.txt");
    pPTFEReflectivityData = new G4String("./data/PTFE/Reflectivity.txt");
    pPTFESpecularLobeConstantData = new G4String("./data/PTFE/SpecularLobeConstant.txt");
    pPTFESpecularSpikeConstantData = new G4String("./data/PTFE/SpecularSpikeConstant.txt");
    pPTFEBackscatterConstantData = new G4String("./data/PTFE/BackscatterConstant.txt");
    pPTFEEfficiencyData = new G4String("./data/PTFE/Efficiency.txt");

    pLXeScintillationSpectrumData = new G4String("./data/LXe/ScintillationSpectrum.txt");
    pLXeIndexOfRefractionData = new G4String("./data/LXe/IndexOfRefraction.txt");
    pLXeAbsorptionLengthData = new G4String("./data/LXe/AbsorptionLength.txt");
    pLXeRayleighScatteringLengthData = new G4String("./data/LXe/RayleighScatteringLength.txt");
    pLXeDensityData = new G4String("./data/LXe/Density.txt");

    dLXeFanoFactor = 0.033;
    dLXeFastScintillationTimeConstant = 2.2*ns;
    dLXeSlowScintillationTimeConstant = 27.0*ns;

    pGXeScintillationSpectrumData = new G4String("./data/GXe/ScintillationSpectrum.txt");
    pGXeIndexOfRefractionData = new G4String("./data/GXe/IndexOfRefraction.txt");
    pGXeAbsorptionLengthData = new G4String("./data/GXe/AbsorptionLength.txt");
    pGXeRayleighScatteringLengthData = new G4String("./data/GXe/RayleighScatteringLength.txt");
    pGXeDensityData = new G4String("./data/GXe/Density.txt");

    dGXeFanoFactor = 0.033;
    dGXeFastScintillationTimeConstant = 2.2*ns;
    dGXeSlowScintillationTimeConstant = 27.0*ns;

    pQuartzIndexOfRefractionData = new G4String("./data/Quartz/IndexOfRefraction.txt");
    pQuartzAbsorptionLengthData = new G4String("./data/Quartz/AbsorptionLength.txt");

    new G4UnitDefinition("psi", "psi", "Pressure", 6894.76*pascal);

    // dXePressure = 17.35*psi;
    dXeTemperature = 168.00*kelvin;

    dLXeDensity = 2.9223*g/cm3;
    dGXeDensity = 0.011655*g/cm3;
}

RELAXDetectorConstruction::~RELAXDetectorConstruction()
{
    delete pRELAXDetectorMessenger;

    delete pDummyString;
    delete ifsDataFile;

    delete pEnergy;
    delete pData;

    delete pLXeScintillationSpectrumData;
    delete pLXeIndexOfRefractionData;
    delete pLXeAbsorptionLengthData;
    delete pLXeRayleighScatteringLengthData;
    delete pLXeDensityData;

    delete pGXeScintillationSpectrumData;
    delete pGXeIndexOfRefractionData;
    delete pGXeAbsorptionLengthData;
    delete pGXeRayleighScatteringLengthData;
    delete pGXeDensityData;
}

G4VPhysicalVolume* RELAXDetectorConstruction::Construct()
{
    DefineMaterials();
    ConstructLaboratory();
    ConstructCryostat();

    return pLaboratoryPV;
}

void RELAXDetectorConstruction::DefineMaterials()
{
    //////////////////////////////////////////////////////////////////////////////////
    // Create Isotopes - Do not delete G4Isotope, Geant4 handles the memory cleanup //
    //////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////
    // Create Hygrogen Isotopes //
    //////////////////////////////
    G4Isotope* pH1Isotope = new G4Isotope("H1", 1, 1, 1.007825*g/mole);
    G4Isotope* pH2Isotope = new G4Isotope("H2", 1, 2, 2.014102*g/mole);

    ///////////////////////////////
    // Create Beryllium Isotopes //
    ///////////////////////////////
    G4Isotope* pBe9Isotope = new G4Isotope("Be9", 4, 9, 9.012182*g/mole);

    ///////////////////////////
    // Create Boron Isotopes //
    ///////////////////////////
    G4Isotope* pB10Isotope = new G4Isotope("B10", 5, 10, 10.012937*g/mole);
    G4Isotope* pB11Isotope = new G4Isotope("B11", 5, 11, 11.009305*g/mole);

    ////////////////////////////
    // Create Carbon Isotopes //
    ////////////////////////////
    G4Isotope* pC12Isotope = new G4Isotope("C12", 6, 12, 12.000000*g/mole);
    G4Isotope* pC13Isotope = new G4Isotope("C13", 6, 13, 13.003355*g/mole);

    //////////////////////////////
    // Create Nitrogen Isotopes //
    //////////////////////////////
    G4Isotope* pN14Isotope = new G4Isotope("N14", 7, 14, 14.003074*g/mole);
    G4Isotope* pN15Isotope = new G4Isotope("N15", 7, 15, 15.000109*g/mole);

    ////////////////////////////
    // Create Oxygen Isotopes //
    ////////////////////////////
    G4Isotope* pO16Isotope = new G4Isotope("O16", 8, 16, 15.994915*g/mole);
    G4Isotope* pO17Isotope = new G4Isotope("O17", 8, 17, 16.999132*g/mole);
    G4Isotope* pO18Isotope = new G4Isotope("O18", 8, 18, 17.999160*g/mole);

    //////////////////////////////
    // Create Fluorine Isotopes //
    //////////////////////////////
    G4Isotope* pF19Isotope = new G4Isotope("F19", 9, 19, 18.998403*g/mole);

    ////////////////////////////
    // Create Sodium Isotopes //
    ////////////////////////////
    G4Isotope* pNa23Isotope = new G4Isotope("Na23", 11, 23, 22.989770*g/mole);

    ///////////////////////////////
    // Create Magnesium Isotopes //
    ///////////////////////////////
    G4Isotope* pMg24Isotope = new G4Isotope("Mg24", 12, 24, 23.985042*g/mole);
    G4Isotope* pMg25Isotope = new G4Isotope("Mg25", 12, 25, 24.985837*g/mole);
    G4Isotope* pMg26Isotope = new G4Isotope("Mg26", 12, 26, 25.982593*g/mole);

    //////////////////////////////
    // Create Aluminum Isotopes //
    //////////////////////////////
    G4Isotope* pAl27Isotope = new G4Isotope("Al27", 13, 27, 26.981538*g/mole);

    /////////////////////////////
    // Create Silicon Isotopes //
    /////////////////////////////
    G4Isotope* pSi28Isotope = new G4Isotope("Si28", 14, 28, 27.976927*g/mole);
    G4Isotope* pSi29Isotope = new G4Isotope("Si29", 14, 29, 28.976495*g/mole);
    G4Isotope* pSi30Isotope = new G4Isotope("Si30", 14, 30, 29.973770*g/mole);

    ////////////////////////////////
    // Create Phosphorus Isotopes //
    ////////////////////////////////
    G4Isotope* pP31Isotope = new G4Isotope("P31", 15, 31, 30.973762*g/mole);

    ////////////////////////////
    // Create Sulfur Isotopes //
    ////////////////////////////
    G4Isotope* pS32Isotope = new G4Isotope("S32", 16, 32, 31.972071*g/mole);
    G4Isotope* pS33Isotope = new G4Isotope("S33", 16, 33, 32.971458*g/mole);
    G4Isotope* pS34Isotope = new G4Isotope("S34", 16, 34, 33.967867*g/mole);
    G4Isotope* pS36Isotope = new G4Isotope("S36", 16, 36, 35.967081*g/mole);

    ///////////////////////////
    // Create Argon Isotopes //
    ///////////////////////////
    G4Isotope* pAr36Isotope = new G4Isotope("Ar36", 18, 36, 35.967546*g/mole);
    G4Isotope* pAr38Isotope = new G4Isotope("Ar38", 18, 38, 37.962732*g/mole);
    G4Isotope* pAr40Isotope = new G4Isotope("Ar40", 18, 40, 39.962383*g/mole);

    ///////////////////////////////
    // Create Potassium Isotopes //
    ///////////////////////////////
    G4Isotope* pK39Isotope = new G4Isotope("K39", 19, 39, 38.963707*g/mole);
    G4Isotope* pK40Isotope = new G4Isotope("K40", 19, 40, 39.963999*g/mole);
    G4Isotope* pK41Isotope = new G4Isotope("K41", 19, 41, 40.961826*g/mole);

    /////////////////////////////
    // Create Calcium Isotopes //
    /////////////////////////////
    G4Isotope* pCa40Isotope = new G4Isotope("Ca40", 20, 40, 39.962591*g/mole);
    G4Isotope* pCa42Isotope = new G4Isotope("Ca42", 20, 42, 41.958618*g/mole);
    G4Isotope* pCa43Isotope = new G4Isotope("Ca43", 20, 43, 42.958767*g/mole);
    G4Isotope* pCa44Isotope = new G4Isotope("Ca44", 20, 44, 43.955481*g/mole);
    G4Isotope* pCa46Isotope = new G4Isotope("Ca46", 20, 46, 45.953693*g/mole);
    G4Isotope* pCa48Isotope = new G4Isotope("Ca48", 20, 48, 47.952534*g/mole);

    //////////////////////////////
    // Create Titanium Isotopes //
    //////////////////////////////
    G4Isotope* pTi46Isotope = new G4Isotope("Ti46", 22, 46, 45.952629*g/mole);
    G4Isotope* pTi47Isotope = new G4Isotope("Ti47", 22, 47, 46.951764*g/mole);
    G4Isotope* pTi48Isotope = new G4Isotope("Ti48", 22, 48, 47.947947*g/mole);
    G4Isotope* pTi49Isotope = new G4Isotope("Ti49", 22, 49, 48.947871*g/mole);
    G4Isotope* pTi50Isotope = new G4Isotope("Ti50", 22, 50, 49.944792*g/mole);

    //////////////////////////////
    // Create Chromium Isotopes //
    //////////////////////////////
    G4Isotope* pCr50Isotope = new G4Isotope("Cr50", 24, 50, 49.946050*g/mole);
    G4Isotope* pCr52Isotope = new G4Isotope("Cr52", 24, 52, 51.940512*g/mole);
    G4Isotope* pCr53Isotope = new G4Isotope("Cr53", 24, 53, 52.940654*g/mole);
    G4Isotope* pCr54Isotope = new G4Isotope("Cr54", 24, 54, 53.938885*g/mole);

    ///////////////////////////////
    // Create Manganese Isotopes //
    ///////////////////////////////
    G4Isotope* pMn55Isotope = new G4Isotope("Mn55", 25, 55, 54.938050*g/mole);

    //////////////////////////
    // Create Iron Isotopes //
    //////////////////////////
    G4Isotope* pFe54Isotope = new G4Isotope("Fe54", 26, 54, 53.939615*g/mole);
    G4Isotope* pFe56Isotope = new G4Isotope("Fe56", 26, 56, 55.934942*g/mole);
    G4Isotope* pFe57Isotope = new G4Isotope("Fe57", 26, 57, 56.935399*g/mole);
    G4Isotope* pFe58Isotope = new G4Isotope("Fe58", 26, 58, 57.933280*g/mole);

    ////////////////////////////
    // Create Cobolt Isotopes //
    ////////////////////////////
    G4Isotope* pCo59Isotope = new G4Isotope("Co59", 27, 59, 58.933200*g/mole);

    ////////////////////////////
    // Create Nickel Isotopes //
    ////////////////////////////
    G4Isotope* pNi58Isotope = new G4Isotope("Ni58", 28, 58, 57.935348*g/mole);
    G4Isotope* pNi60Isotope = new G4Isotope("Ni60", 28, 60, 59.930791*g/mole);
    G4Isotope* pNi61Isotope = new G4Isotope("Ni61", 28, 61, 60.931060*g/mole);
    G4Isotope* pNi62Isotope = new G4Isotope("Ni62", 28, 62, 61.928349*g/mole);
    G4Isotope* pNi64Isotope = new G4Isotope("Ni64", 28, 64, 63.927970*g/mole);

    ////////////////////////////
    // Create Copper Isotopes //
    ////////////////////////////
    G4Isotope* pCu63Isotope = new G4Isotope("Cu63", 29, 63, 62.929601*g/mole);
    G4Isotope* pCu65Isotope = new G4Isotope("Cu65", 29, 65, 64.927794*g/mole);

    ////////////////////////////////
    // Create Molybdenum Isotopes //
    ////////////////////////////////
    G4Isotope* pMo92Isotope = new G4Isotope("Mo92",  42, 92, 91.906810*g/mole);
    G4Isotope* pMo94Isotope = new G4Isotope("Mo94",  42, 94, 93.905088*g/mole);
    G4Isotope* pMo95Isotope = new G4Isotope("Mo95",  42, 95, 94.905841*g/mole);
    G4Isotope* pMo96Isotope = new G4Isotope("Mo96",  42, 96, 95.904679*g/mole);
    G4Isotope* pMo97Isotope = new G4Isotope("Mo97",  42, 97, 96.906021*g/mole);
    G4Isotope* pMo98Isotope = new G4Isotope("Mo98",  42, 98, 97.905408*g/mole);
    G4Isotope* pMo100Isotope = new G4Isotope("Mo100", 42, 100, 99.907477*g/mole);

    //////////////////////////////
    // Create Antimony Isotopes //
    //////////////////////////////
    G4Isotope* pSb121Isotope = new G4Isotope("Sb121", 51, 121, 120.903818*g/mole);
    G4Isotope* pSb123Isotope = new G4Isotope("Sb123", 51, 123, 122.904216*g/mole);

    ///////////////////////////
    // Create Xenon Isotopes //
    ///////////////////////////
    G4Isotope* pXe124Isotope = new G4Isotope("Xe124", 54, 124, 123.905896*g/mole);
    G4Isotope* pXe126Isotope = new G4Isotope("Xe126", 54, 126, 125.904269*g/mole);
    G4Isotope* pXe128Isotope = new G4Isotope("Xe128", 54, 128, 127.903530*g/mole);
    G4Isotope* pXe129Isotope = new G4Isotope("Xe129", 54, 129, 128.904779*g/mole);
    G4Isotope* pXe130Isotope = new G4Isotope("Xe130", 54, 130, 129.903508*g/mole);
    G4Isotope* pXe131Isotope = new G4Isotope("Xe131", 54, 131, 130.905082*g/mole);
    G4Isotope* pXe132Isotope = new G4Isotope("Xe132", 54, 132, 131.904154*g/mole);
    G4Isotope* pXe134Isotope = new G4Isotope("Xe134", 54, 134, 133.905395*g/mole);
    G4Isotope* pXe136Isotope = new G4Isotope("Xe136", 54, 136, 135.907220*g/mole);

    //////////////////////////
    // Cretae Lead Isotopes //
    //////////////////////////
    G4Isotope* pPb204Isotope = new G4Isotope("Pb204", 82, 204, 203.973029*g/mole);
    G4Isotope* pPb206Isotope = new G4Isotope("Pb206", 82, 206, 205.974449*g/mole);
    G4Isotope* pPb207Isotope = new G4Isotope("Pb207", 82, 207, 206.975881*g/mole);
    G4Isotope* pPb208Isotope = new G4Isotope("Pb208", 82, 208, 207.976636*g/mole);

    //////////////////////////////////////////////////////////////////////////////////
    // Create Isotopes - Do not delete G4Element, Geant4 handles the memory cleanup //
    //////////////////////////////////////////////////////////////////////////////////

    /////////////////////
    // Create Hydrogen //
    /////////////////////
    G4Element* pHElement = new G4Element("Hydrogen", "H", 2);
    pHElement->AddIsotope(pH1Isotope, 99.9885*perCent);
    pHElement->AddIsotope(pH2Isotope,  0.0155*perCent);

    //////////////////////
    // Create Beryllium //
    //////////////////////
    G4Element* pBeElement = new G4Element("Beryllium", "Be", 1);
    pBeElement->AddIsotope(pBe9Isotope, 100*perCent);

    //////////////////
    // Create Boron //
    //////////////////
    G4Element* pBElement = new G4Element("Boron", "B", 2);
    pBElement->AddIsotope(pB10Isotope, 19.9000*perCent);
    pBElement->AddIsotope(pB11Isotope, 80.1000*perCent);

    ///////////////////
    // Create Carbon //
    ///////////////////
    G4Element* pCElement = new G4Element("Carbon", "C", 2);
    pCElement->AddIsotope(pC12Isotope, 98.9300*perCent);
    pCElement->AddIsotope(pC13Isotope,  1.0700*perCent);

    /////////////////////
    // Create Nitrogen //
    /////////////////////
    G4Element* pNElement = new G4Element("Nitrogen", "N", 2);
    pNElement->AddIsotope(pN14Isotope, 99.6320*perCent);
    pNElement->AddIsotope(pN15Isotope,  0.3680*perCent);

    ///////////////////
    // Create Oxygen //
    ///////////////////
    G4Element* pOElement = new G4Element("Oxygen", "O", 3);
    pOElement->AddIsotope(pO16Isotope, 99.757*perCent);
    pOElement->AddIsotope(pO17Isotope,  0.038*perCent);
    pOElement->AddIsotope(pO18Isotope,  0.205*perCent);

    /////////////////////
    // Create Fluorine //
    /////////////////////
    G4Element* pFElement = new G4Element("Fluorine", "F", 1);
    pFElement->AddIsotope(pF19Isotope, 100*perCent);

    ///////////////////
    // Create Sodium //
    ///////////////////
    G4Element* pNaElement = new G4Element("Sodium", "Na", 1);
    pNaElement->AddIsotope(pNa23Isotope, 100*perCent);

    //////////////////////
    // Create Magnesium //
    //////////////////////
    G4Element* pMgElement = new G4Element("Magnesium", "Mg", 3);
    pMgElement->AddIsotope(pMg24Isotope, 78.9900*perCent);
    pMgElement->AddIsotope(pMg25Isotope, 10.0000*perCent);
    pMgElement->AddIsotope(pMg26Isotope, 11.0100*perCent);

    /////////////////////
    // Create Aluminum //
    /////////////////////
    G4Element* pAlElement = new G4Element("Aluminum", "Al", 1);
    pAlElement->AddIsotope(pAl27Isotope, 100*perCent);

    ////////////////////
    // Create Silicon //
    ////////////////////
    G4Element* pSiElement = new G4Element("Silicon", "Si", 3);
    pSiElement->AddIsotope(pSi28Isotope, 92.2297*perCent);
    pSiElement->AddIsotope(pSi29Isotope,  4.6832*perCent);
    pSiElement->AddIsotope(pSi30Isotope,  3.0872*perCent);

    ///////////////////////
    // Create Phosphorus //
    ///////////////////////
    G4Element* pPElement = new G4Element("Phosphorus", "P", 1);
    pPElement->AddIsotope(pP31Isotope, 100*perCent);

    ///////////////////
    // Create Sulfur //
    ///////////////////
    G4Element* pSElement = new G4Element("Sulfur", "S", 4);
    pSElement->AddIsotope(pS32Isotope, 94.9300*perCent);
    pSElement->AddIsotope(pS33Isotope,  0.7600*perCent);
    pSElement->AddIsotope(pS34Isotope,  4.2900*perCent);
    pSElement->AddIsotope(pS36Isotope,  0.0200*perCent);

    //////////////////
    // Create Argon //
    //////////////////
    G4Element* pArElement = new G4Element("Argon", "Ar", 3);
    pArElement->AddIsotope(pAr36Isotope,  0.3365*perCent);
    pArElement->AddIsotope(pAr38Isotope,  0.0632*perCent);
    pArElement->AddIsotope(pAr40Isotope, 99.6003*perCent);

    //////////////////////
    // Create Potassium //
    //////////////////////
    G4Element* pKElement = new G4Element("Potassium", "K", 3);
    pKElement->AddIsotope(pK39Isotope, 93.2581*perCent);
    pKElement->AddIsotope(pK40Isotope,  0.0117*perCent);
    pKElement->AddIsotope(pK41Isotope,  6.7302*perCent);

    ////////////////////
    // Create Calcium //
    ////////////////////
    G4Element* pCaElement = new G4Element("Calcium", "Ca", 6);
    pCaElement->AddIsotope(pCa40Isotope, 96.9410*perCent);
    pCaElement->AddIsotope(pCa42Isotope,  0.6470*perCent);
    pCaElement->AddIsotope(pCa43Isotope,  0.1350*perCent);
    pCaElement->AddIsotope(pCa44Isotope,  2.0860*perCent);
    pCaElement->AddIsotope(pCa46Isotope,  0.0040*perCent);
    pCaElement->AddIsotope(pCa48Isotope,  0.1870*perCent);

    /////////////////////
    // Create Titanium //
    /////////////////////
    G4Element* pTiElement = new G4Element("Titanium", "Ti", 5);
    pTiElement->AddIsotope(pTi46Isotope,  8.2500*perCent);
    pTiElement->AddIsotope(pTi47Isotope,  7.4400*perCent);
    pTiElement->AddIsotope(pTi48Isotope, 73.7200*perCent);
    pTiElement->AddIsotope(pTi49Isotope,  5.4100*perCent);
    pTiElement->AddIsotope(pTi50Isotope,  5.1800*perCent);

    /////////////////////
    // Create Chromium //
    /////////////////////
    G4Element* pCrElement = new G4Element("Chromium", "Cr", 4);
    pCrElement->AddIsotope(pCr50Isotope,  4.3450*perCent);
    pCrElement->AddIsotope(pCr52Isotope, 83.7890*perCent);
    pCrElement->AddIsotope(pCr53Isotope,  9.5010*perCent);
    pCrElement->AddIsotope(pCr54Isotope,  2.3650*perCent);

    //////////////////////
    // Create Manganese //
    //////////////////////
    G4Element* pMnElement = new G4Element("Manganese", "Mn", 1);
    pMnElement->AddIsotope(pMn55Isotope, 100*perCent);

    /////////////////
    // Create Iron //
    /////////////////
    G4Element* pFeElement = new G4Element("Iron", "Fe", 4);
    pFeElement->AddIsotope(pFe54Isotope,  5.8450*perCent);
    pFeElement->AddIsotope(pFe56Isotope, 91.7540*perCent);
    pFeElement->AddIsotope(pFe57Isotope,  2.1190*perCent);
    pFeElement->AddIsotope(pFe58Isotope,  0.2820*perCent);

    ///////////////////
    // Create Cobalt //
    ///////////////////
    G4Element* pCoElement = new G4Element("Cobalt", "Co", 1);
    pCoElement->AddIsotope(pCo59Isotope, 100*perCent);

    ///////////////////
    // Create Nickel //
    ///////////////////
    G4Element* pNiElement = new G4Element("Nickel", "Ni", 5);
    pNiElement->AddIsotope(pNi58Isotope, 68.0769*perCent);
    pNiElement->AddIsotope(pNi60Isotope, 26.2231*perCent);
    pNiElement->AddIsotope(pNi61Isotope,  1.1399*perCent);
    pNiElement->AddIsotope(pNi62Isotope,  3.6345*perCent);
    pNiElement->AddIsotope(pNi64Isotope,  0.9256*perCent);

    ///////////////////
    // Create Copper //
    ///////////////////
    G4Element* pCuElement = new G4Element("Copper", "Cu", 2);
    pCuElement->AddIsotope(pCu63Isotope, 69.1700*perCent);
    pCuElement->AddIsotope(pCu65Isotope, 30.8300*perCent);

    ///////////////////////
    // Create Molybdenum //
    ///////////////////////
    G4Element* pMoElement = new G4Element("Molybdenum", "Mo", 7);
    pMoElement->AddIsotope(pMo92Isotope, 14.8400*perCent);
    pMoElement->AddIsotope(pMo94Isotope,  9.2500*perCent);
    pMoElement->AddIsotope(pMo95Isotope, 15.9200*perCent);
    pMoElement->AddIsotope(pMo96Isotope, 16.6800*perCent);
    pMoElement->AddIsotope(pMo97Isotope,  9.5500*perCent);
    pMoElement->AddIsotope(pMo98Isotope, 24.1300*perCent);
    pMoElement->AddIsotope(pMo100Isotope, 9.6300*perCent);

    /////////////////////
    // Create Antimony //
    /////////////////////
    G4Element* pSbElement = new G4Element("Antimony", "Sb", 2);
    pSbElement->AddIsotope(pSb121Isotope, 57.2100*perCent);
    pSbElement->AddIsotope(pSb123Isotope, 42.7900*perCent);

    //////////////////
    // Create Xenon //
    //////////////////
    G4Element* pXeElement = new G4Element("Xenon", "Xe", 9);
    pXeElement->AddIsotope(pXe124Isotope,  0.0900*perCent);
    pXeElement->AddIsotope(pXe126Isotope,  0.0900*perCent);
    pXeElement->AddIsotope(pXe128Isotope,  1.9200*perCent);
    pXeElement->AddIsotope(pXe129Isotope, 26.4400*perCent);
    pXeElement->AddIsotope(pXe130Isotope,  4.0800*perCent);
    pXeElement->AddIsotope(pXe131Isotope, 21.1800*perCent);
    pXeElement->AddIsotope(pXe132Isotope, 26.8900*perCent);
    pXeElement->AddIsotope(pXe134Isotope, 10.4400*perCent);
    pXeElement->AddIsotope(pXe136Isotope,  8.8700*perCent);

    /////////////////
    // Create Lead //
    /////////////////
    G4Element* pPbElement = new G4Element("Lead", "Pb", 4);
    pPbElement->AddIsotope(pPb204Isotope,  1.4000*perCent);
    pPbElement->AddIsotope(pPb206Isotope, 24.1000*perCent);
    pPbElement->AddIsotope(pPb207Isotope, 22.1000*perCent);
    pPbElement->AddIsotope(pPb208Isotope, 52.4000*perCent);

    ///////////////////////////////////////////////////////////////////////////////////
    // Create Materials - Do not delete G4Material, Geant4 handles the memory cleanup //
    ///////////////////////////////////////////////////////////////////////////////////

    ////////////////
    // Create Air //
    ////////////////
    G4Material* pAirMaterial = new G4Material("Air", 0.00120479*g/cm3, 4, kStateGas);
    pAirMaterial->AddElement( pNElement, 75.5268*perCent);
    pAirMaterial->AddElement( pOElement, 23.1781*perCent);
    pAirMaterial->AddElement(pArElement,  1.2827*perCent);
    pAirMaterial->AddElement( pCElement,  0.0124*perCent);

    /////////////////////
    // Create Concrete //
    /////////////////////
    G4Material* pConcreteMaterial = new G4Material("Concrete", 2.3000*g/cm3, 10, kStateSolid);
    pConcreteMaterial->AddElement( pOElement, 52.9107*perCent);
    pConcreteMaterial->AddElement(pSiElement, 33.7021*perCent);
    pConcreteMaterial->AddElement(pCaElement,  4.4000*perCent);
    pConcreteMaterial->AddElement(pAlElement,  3.3872*perCent);
    pConcreteMaterial->AddElement(pNaElement,  1.6000*perCent);
    pConcreteMaterial->AddElement(pFeElement,  1.4000*perCent);
    pConcreteMaterial->AddElement( pKElement,  1.3000*perCent);
    pConcreteMaterial->AddElement( pHElement,  1.0000*perCent);
    pConcreteMaterial->AddElement(pMgElement,  0.2000*perCent);
    pConcreteMaterial->AddElement( pCElement,  0.1000*perCent);

    /////////////////
    // Create Lead //
    /////////////////
    G4Material* pLeadMaterial = new G4Material("Lead", 11.3500*g/cm3, 1, kStateSolid);
    pLeadMaterial->AddElement(pPbElement, 100.0000*perCent);

    ///////////////////////////
    // Create Aluminum Oxide //
    ///////////////////////////
    G4Material* pAluminumOxideMaterial = new G4Material("AluminumOxide", 3.9500*g/cm3, 2, kStateSolid);
    pAluminumOxideMaterial->AddElement( pOElement, 3);
    pAluminumOxideMaterial->AddElement(pAlElement, 2);

    ////////////////////////////
    // Create Beryllium Oxide //
    ////////////////////////////
    G4Material* pBerylliumOxideMaterial = new G4Material("BerylliumOxide", 3.0100*g/cm3, 2, kStateSolid);
    pBerylliumOxideMaterial->AddElement(pBeElement, 1);
    pBerylliumOxideMaterial->AddElement( pOElement, 1);

    ///////////////////////////////
    // Create Borosilicate Glass //
    ///////////////////////////////
    G4Material* pBorosilicateGlassMaterial = new G4Material("BorosilicateGlass", 2.2300*g/cm3, 5, kStateSolid);
    pBorosilicateGlassMaterial->AddElement( pOElement, 60);
    pBorosilicateGlassMaterial->AddElement(pSiElement, 26);
    pBorosilicateGlassMaterial->AddElement( pBElement,  9);
    pBorosilicateGlassMaterial->AddElement(pNaElement,  3);
    pBorosilicateGlassMaterial->AddElement(pAlElement,  1);

    ////////////////////
    // Create JB Weld //
    ////////////////////
    G4Material* pJBWeldMaterial = new G4Material("JBWeld", 1.1600*g/cm3, 6, kStateSolid);
    pJBWeldMaterial->AddElement( pOElement, 28.4333*perCent);
    pJBWeldMaterial->AddElement( pCElement, 26.4333*perCent);
    pJBWeldMaterial->AddElement(pFeElement, 21.3334*perCent);
    pJBWeldMaterial->AddElement( pHElement, 15.6000*perCent);
    pJBWeldMaterial->AddElement(pCaElement,  8.0000*perCent);
    pJBWeldMaterial->AddElement( pNElement,  0.2000*perCent);

    ////////////////////
    // Create Acrylic //
    ////////////////////
    G4Material* pAcrylicMaterial = new G4Material("Acrylic", 1.180*g/cm3, 3, kStateSolid);
    pAcrylicMaterial->AddElement(pCElement, 59.98*perCent);
    pAcrylicMaterial->AddElement(pOElement, 31.96*perCent);
    pAcrylicMaterial->AddElement(pHElement,  8.05*perCent);

    ////////////////////////////
    // Create Stainless Steel //
    ////////////////////////////
    G4Material* pStainlessSteelMaterial = new G4Material("Stainless Steel", 8.0000*g/cm3, 10, kStateSolid);
    pStainlessSteelMaterial->AddElement(pFeElement, 65.4950*perCent);
    pStainlessSteelMaterial->AddElement(pCrElement, 17.0000*perCent);
    pStainlessSteelMaterial->AddElement(pNiElement, 12.0000*perCent);
    pStainlessSteelMaterial->AddElement(pMoElement,  2.5000*perCent);
    pStainlessSteelMaterial->AddElement(pMnElement,  2.0000*perCent);
    pStainlessSteelMaterial->AddElement(pSiElement,  0.7500*perCent);
    pStainlessSteelMaterial->AddElement( pNElement,  0.1000*perCent);
    pStainlessSteelMaterial->AddElement( pCElement,  0.0800*perCent);
    pStainlessSteelMaterial->AddElement( pPElement,  0.0450*perCent);
    pStainlessSteelMaterial->AddElement( pSElement,  0.0300*perCent);

    ///////////////////
    // Create Vacuum //
    ///////////////////
    G4Material* pVacuumMaterial = new G4Material("Vacuum", 1.0e-20*g/cm3, 4, kStateGas);
    pVacuumMaterial->AddElement( pNElement, 75.5268*perCent);
    pVacuumMaterial->AddElement( pOElement, 23.1781*perCent);
    pVacuumMaterial->AddElement(pArElement,  1.2827*perCent);
    pVacuumMaterial->AddElement( pCElement,  0.0124*perCent);

    ////////////////
    // Create GXe //
    ////////////////
    G4Material* pGXeMaterial = new G4Material("GXe", 0.0011655*g/cm3, 1, kStateGas);
    pGXeMaterial->AddElement(pXeElement, 100*perCent);

    G4MaterialPropertiesTable* pGXeMPT = new G4MaterialPropertiesTable();
    pGXeMaterial->SetMaterialPropertiesTable(pGXeMPT);

    SetGXeScintillationSpectrumData(pGXeScintillationSpectrumData);
    SetGXeFanoFactor(dGXeFanoFactor);
    SetGXeFastScintillationTimeConstant(dGXeFastScintillationTimeConstant);
    SetGXeSlowScintillationTimeConstant(dGXeSlowScintillationTimeConstant);
    SetGXeIndexOfRefractionData(pGXeIndexOfRefractionData);
    SetGXeAbsorptionLengthData(pGXeAbsorptionLengthData);
    SetGXeRayleighScatteringLengthData(pGXeRayleighScatteringLengthData);

    ////////////////
    // Create LXe //
    ////////////////
    G4Material* pLXeMaterial = new G4Material("LXe", 2.9223*g/cm3, 1, kStateLiquid);
    pLXeMaterial->AddElement(pXeElement, 100*perCent);

    G4MaterialPropertiesTable* pLXeMPT = new G4MaterialPropertiesTable();
    pLXeMaterial->SetMaterialPropertiesTable(pLXeMPT);

    SetLXeScintillationSpectrumData(pLXeScintillationSpectrumData);
    SetLXeFanoFactor(dLXeFanoFactor);
    SetLXeFastScintillationTimeConstant(dLXeFastScintillationTimeConstant);
    SetLXeSlowScintillationTimeConstant(dLXeSlowScintillationTimeConstant);
    SetLXeIndexOfRefractionData(pLXeIndexOfRefractionData);
    SetLXeAbsorptionLengthData(pLXeAbsorptionLengthData);
    SetLXeRayleighScatteringLengthData(pLXeRayleighScatteringLengthData);

    /////////////////
    // Create PTFE //
    /////////////////
    G4Material* pPTFEMaterial = new G4Material("PTFE", 2.200*g/cm3, 2, kStateSolid);
    pPTFEMaterial->AddElement(pFElement, 4);
    pPTFEMaterial->AddElement(pCElement, 2);

    G4MaterialPropertiesTable* pPTFEMPT = new G4MaterialPropertiesTable();
    pPTFEMaterial->SetMaterialPropertiesTable(pPTFEMPT);

    SetPTFEIndexOfRefraction(pPTFEIndexOfRefractionData);
    SetPTFEAbsorptionLengthData(pPTFEAbsorptionLengthData);
    SetPTFEReflectivity(pPTFEReflectivityData);
    SetPTFESpecularLobeConstant(pPTFESpecularLobeConstantData);
    SetPTFESpecularSpikeConstant(pPTFESpecularSpikeConstantData);
    SetPTFEBackscatterConstant(pPTFEBackscatterConstantData);
    SetPTFEEfficiency(pPTFEEfficiencyData);

    //////////////////
    // Create Kovar //
    //////////////////
    G4Material* pKovarMaterial = new G4Material("Kovar", 8.330*g/cm3, 6, kStateSolid);
    pKovarMaterial->AddElement(pFeElement, 53.4900*perCent);
    pKovarMaterial->AddElement(pNiElement, 29.0000*perCent);
    pKovarMaterial->AddElement(pCoElement, 17.0000*perCent);
    pKovarMaterial->AddElement(pMnElement,  0.3000*perCent);
    pKovarMaterial->AddElement(pSiElement,  0.2000*perCent);
    pKovarMaterial->AddElement( pCElement,  0.0100*perCent);

    ///////////////////
    // Create Quartz //
    ///////////////////
    G4Material* pQuartzMaterial = new G4Material("Quartz", 2.201*g/cm3, 2, kStateSolid);
    pQuartzMaterial->AddElement(pSiElement, 1);
    pQuartzMaterial->AddElement( pOElement, 2);

    G4MaterialPropertiesTable* pQuartzMPT = new G4MaterialPropertiesTable();
    pQuartzMaterial->SetMaterialPropertiesTable(pQuartzMPT);

    SetQuartzIndexOfRefraction(pQuartzIndexOfRefractionData);
    SetQuartzAbsorptionLength(pQuartzAbsorptionLengthData);

    /////////////////////////
    // Create Photocathode //
    /////////////////////////
    G4Material* pPhotocathodeMaterial = new G4Material("Photocathode", 8.000*g/cm3, 1, kStateSolid);
    pPhotocathodeMaterial->AddElement(pAlElement, 1);

    ////////////////////
    // Create Ceramic //
    ////////////////////
    G4Material* pCeramicMaterial = new G4Material("Ceramic", 4.000*g/cm3, 2, kStateSolid);
    pCeramicMaterial->AddElement( pOElement, 3);
    pCeramicMaterial->AddElement(pAlElement, 2);
}

void RELAXDetectorConstruction::ConstructLaboratory()
{
    //////////////////////////
    // Construct Laboratory //
    //////////////////////////

    // Set Laboratory Variables
    G4double dLaboratoryLength = 160.000 * cm;
    G4double dLaboratoryWidth  = 160.000 * cm;
    dLaboratoryHeight = 100.000 * cm;

    // Create Laboratory
    G4Box* pLaboratoryBox = new G4Box("LaboratoryBox", 0.5 * dLaboratoryLength, 0.5 * dLaboratoryWidth, 0.5 * dLaboratoryHeight);
    pLaboratoryLV         = new G4LogicalVolume(pLaboratoryBox, G4Material::GetMaterial("Air"), "LaboratoryLV");
    pLaboratoryPV         = new G4PVPlacement(0, G4ThreeVector(), pLaboratoryLV, "Laboratory", 0, false, 0);

    G4VisAttributes* pLaboratoryVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.0));
    pLaboratoryVisAtt->SetForceSolid(true);
    pLaboratoryLV->SetVisAttributes(pLaboratoryVisAtt);

    // Set Mother Logical Volume
    pMotherLV = pLaboratoryLV;

    /////////////////////
    // Construct Floor //
    /////////////////////

    // Set Floor variables
    G4double dFloorLength = dLaboratoryLength;
    G4double dFloorWidth  = dLaboratoryWidth;
    dFloorHeight = 15.00 * cm;

    G4double dFloorPlacementX = 0.00 * cm;
    G4double dFloorPlacementY = 0.00 * cm;
    G4double dFloorPlacementZ = 0.5 * (dFloorHeight - dLaboratoryHeight);

    G4ThreeVector dFloorXYZ(dFloorPlacementX, dFloorPlacementY, dFloorPlacementZ);

    // Create Laboratory
    G4Box* pFloorBox = new G4Box("FloorBox", 0.5 * dFloorLength, 0.5 * dFloorWidth, 0.5 * dFloorHeight);
    G4LogicalVolume* pFloorLV = new G4LogicalVolume(pFloorBox, G4Material::GetMaterial("Concrete"), "FloorLV");
    G4VPhysicalVolume* pFloorPV = new G4PVPlacement(0, dFloorXYZ, pFloorLV, "Floor", pMotherLV, false, 0);

    G4VisAttributes* pFloorVisAtt = new G4VisAttributes(G4Colour::Gray());
    pFloorVisAtt->SetForceSolid(true);
    pFloorLV->SetVisAttributes(pFloorVisAtt);
}

void RELAXDetectorConstruction::ConstructCryostat()
{
    ////////////////////////
    // Construct Cryostat //
    ////////////////////////

    // Set Cryostat variables
    G4double dOuterCryostatRadius1 = 0.0000*cm;
    G4double dOuterCryostatRadius2 = 10.4775*cm;
    G4double dOuterCryostatRadius3 = dOuterCryostatRadius2;
    G4double dOuterCryostatRadius4 = 6.4389*cm;
    G4double dOuterCryostatRadius5 = dOuterCryostatRadius4;
    G4double dOuterCryostatRadius6 = 6.1214*cm;
    G4double dOuterCryostatRadius7 = dOuterCryostatRadius6;
    G4double dOuterCryostatRadius8 = dOuterCryostatRadius1;
    G4double dOuterCryostatRadius9 = dOuterCryostatRadius1;

    G4double dOuterCryostatRadius10 = 11.4300*cm;


    G4double dOuterCryostatHeight1 = 42.2275*cm;
    G4double dOuterCryostatHeight2 = dOuterCryostatHeight1;
    G4double dOuterCryostatHeight3 = 37.7825*cm;
    G4double dOuterCryostatHeight4 = dOuterCryostatHeight3;
    G4double dOuterCryostatHeight5 = -dOuterCryostatHeight1;
    G4double dOuterCryostatHeight6 = -dOuterCryostatHeight1;
    G4double dOuterCryostatHeight7 = -41.9100*cm;
    G4double dOuterCryostatHeight8 = dOuterCryostatHeight7;
    G4double dOuterCryostatHeight9 = dOuterCryostatHeight1;

    G4double dOuterCryostatRadiusArray[] = { dOuterCryostatRadius1,
                                             dOuterCryostatRadius2,
                                             dOuterCryostatRadius3,
                                             dOuterCryostatRadius4,
                                             dOuterCryostatRadius5,
                                             dOuterCryostatRadius6,
                                             dOuterCryostatRadius7,
                                             dOuterCryostatRadius8,
                                             dOuterCryostatRadius9};

    G4double dOuterCryostatHeightArray[] = { dOuterCryostatHeight1,
                                             dOuterCryostatHeight2,
                                             dOuterCryostatHeight3,
                                             dOuterCryostatHeight4,
                                             dOuterCryostatHeight5,
                                             dOuterCryostatHeight6,
                                             dOuterCryostatHeight7,
                                             dOuterCryostatHeight8,
                                             dOuterCryostatHeight9};

    G4double dOuterCryostatSS1PlacementX = 0.0000*cm;
    G4double dOuterCryostatSS1PlacementY = 0.0000*cm;
    G4double dOuterCryostatSS1PlacementZ = dOuterCryostatHeight7 - cos(asin(dOuterCryostatRadius6 / dOuterCryostatRadius10)) * dOuterCryostatRadius10;

    G4double dOuterCryostatPlacementX = 0.0000*cm;
    G4double dOuterCryostatPlacementY = 0.0000*cm;
    G4double dOuterCryostatPlacementZ = 0.5 * ((2 * (dOuterCryostatHeight1 + dFloorHeight)) - dLaboratoryHeight);

    G4RotationMatrix dOuterCryostatRot;
    dOuterCryostatRot.rotateZ(0.00);

    G4ThreeVector dOuterCryostatSS1XYZ(dOuterCryostatSS1PlacementX, dOuterCryostatSS1PlacementY, dOuterCryostatSS1PlacementZ);
    G4Transform3D dOuterCryostatSS1Transform(dOuterCryostatRot, dOuterCryostatSS1XYZ);

    G4ThreeVector dOuterCryostatXYZ(dOuterCryostatPlacementX, dOuterCryostatPlacementY, dOuterCryostatPlacementZ);

    // Create Cryostat
    G4GenericPolycone* pOuterCryostatPolycone1 = new G4GenericPolycone("OuterCryostatPolycone1", 0.0, 2 * M_PI, 9, dOuterCryostatRadiusArray, dOuterCryostatHeightArray);
    G4Sphere* pOuterCryostatSphere2 = new G4Sphere("OuterCryostatSphere2", 0.0 * cm, dOuterCryostatRadius10, 0.0, 2 * M_PI, 0.0, asin(dOuterCryostatRadius6 / dOuterCryostatRadius10));
    G4SubtractionSolid* pOuterCryostat = new G4SubtractionSolid("OuterCryostat", pOuterCryostatPolycone1, pOuterCryostatSphere2, dOuterCryostatSS1Transform);

    G4LogicalVolume* pOuterCryostatLV = new G4LogicalVolume(pOuterCryostat, G4Material::GetMaterial("Stainless Steel"), "OuterCryostat");
    G4PVPlacement* pOuterCryostatPV = new G4PVPlacement(0, dOuterCryostatXYZ, pOuterCryostatLV, "OuterCryostat", pMotherLV, false, 0);

    G4VisAttributes* pOuterCryostatVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.15));
    pOuterCryostatVisAtt->SetForceSolid(true);
    pOuterCryostatLV->SetVisAttributes(pOuterCryostatVisAtt);

    // Set it as mother volume
    pMotherLV = pOuterCryostatLV;

    ///////////////////////////////
    // Construct Cryostat Vacuum //
    ///////////////////////////////

    G4double dCryostatVacuumRadius1 = 6.2865*cm;
    G4double dCryostatVacuumRadius2 = dOuterCryostatRadius10;

    G4double dCryostatVacuumHeight1 = dOuterCryostatHeight3 - dOuterCryostatHeight7 + 2.2225*cm - ((cos(asin(dCryostatVacuumRadius1 / dOuterCryostatRadius10)) - cos(asin(dOuterCryostatRadius6 / dOuterCryostatRadius10))) * dOuterCryostatRadius10 + 0.1524*cm);

    G4double dCryostatVacuumSS1PlacementX = 0.0000*cm;
    G4double dCryostatVacuumSS1PlacementY = 0.0000*cm;
    G4double dCryostatVacuumSS1PlacementZ = -0.5 * (dCryostatVacuumHeight1 + 2 * cos(asin(dCryostatVacuumRadius1 / dCryostatVacuumRadius2)) * dCryostatVacuumRadius2);

    G4double dCryostatVacuumPlacementX = 0.0000*cm;
    G4double dCryostatVacuumPlacementY = 0.0000*cm;
    G4double dCryostatVacuumPlacementZ = 0.5 * (2 * dOuterCryostatHeight3 + 4.4450*cm - dCryostatVacuumHeight1);

    G4RotationMatrix dCryostatVacuumRot;
    dCryostatVacuumRot.rotateZ(0.0);

    G4ThreeVector dCryostatVacuumSS1XYZ(dCryostatVacuumSS1PlacementX, dCryostatVacuumSS1PlacementY, dCryostatVacuumSS1PlacementZ);
    G4Transform3D dCryostatVacuumSS1Transform(dCryostatVacuumRot, dCryostatVacuumSS1XYZ);

    G4ThreeVector dCryostatVacuumXYZ(dCryostatVacuumPlacementX, dCryostatVacuumPlacementY, dCryostatVacuumPlacementZ);

    // Create Cryostat
    G4Tubs* pCryostatVacuumCylinder1 = new G4Tubs("CryostatVacuumCylinder1", 0.0 * cm, dCryostatVacuumRadius1, 0.5 * dCryostatVacuumHeight1, 0.0, 2 * M_PI);
    G4Sphere* pCryostatVacuumSphere2 = new G4Sphere("CryostatVacuumSphere1", 0.0 * cm, dCryostatVacuumRadius2, 0.0, 2 * M_PI, 0.0, asin(dCryostatVacuumRadius1 / dCryostatVacuumRadius2));
    G4SubtractionSolid* pCryostatVacuum = new G4SubtractionSolid("CryostatVacuum", pCryostatVacuumCylinder1, pCryostatVacuumSphere2, dCryostatVacuumSS1Transform);

    G4LogicalVolume* pCryostatVacuumLV = new G4LogicalVolume(pCryostatVacuum, G4Material::GetMaterial("Vacuum"), "CryostatVacuumLV");
    G4PVPlacement* pCryostatVacuumPV = new G4PVPlacement(0, dCryostatVacuumXYZ, pCryostatVacuumLV, "CryostatVacuum", pMotherLV, false, 0);

    G4VisAttributes* pCryostatVacuumVisAtt = new G4VisAttributes(G4Colour(0.0, 0.0, 0.1, 0.20));
    pCryostatVacuumVisAtt->SetForceSolid(true);
    pCryostatVacuumLV->SetVisAttributes(pCryostatVacuumVisAtt);

    // Set new MotherLV
    pMotherLV = pCryostatVacuumLV;

    //////////////////////////////
    // Construct Inner Cryostat //
    //////////////////////////////

    // Set Inner Cryostat variables
    G4double dInnerCryostatRadius1 = 0.0000 * cm;
    G4double dInnerCryostatRadius2 = dCryostatVacuumRadius1;
    G4double dInnerCryostatRadius3 = dCryostatVacuumRadius1;
    G4double dInnerCryostatRadius4 = 5.72516 * cm;
    G4double dInnerCryostatRadius5 = dInnerCryostatRadius4;
    G4double dInnerCryostatRadius6 = dInnerCryostatRadius1;
    G4double dInnerCryostatRadius7 = dInnerCryostatRadius1;

    G4double dInnerCryostatHeight1 = 38.4175 * cm;
    G4double dInnerCryostatHeight2 = dInnerCryostatHeight1;
    G4double dInnerCryostatHeight3 = 36.1950 * cm;
    G4double dInnerCryostatHeight4 = dInnerCryostatHeight3;
    G4double dInnerCryostatHeight5 = -dInnerCryostatHeight1;
    G4double dInnerCryostatHeight6 = -dInnerCryostatHeight1;
    G4double dInnerCryostatHeight7 = dInnerCryostatHeight1;


    G4double dInnerCryostatRadiusArray[] = {dInnerCryostatRadius1,
                                            dInnerCryostatRadius2,
                                            dInnerCryostatRadius3,
                                            dInnerCryostatRadius4,
                                            dInnerCryostatRadius5,
                                            dInnerCryostatRadius6,
                                            dInnerCryostatRadius7};

    G4double dInnerCryostatHeightArray[] = {dInnerCryostatHeight1,
                                            dInnerCryostatHeight2,
                                            dInnerCryostatHeight3,
                                            dInnerCryostatHeight4,
                                            dInnerCryostatHeight5,
                                            dInnerCryostatHeight6,
                                            dInnerCryostatHeight7};

    G4double dInnerCryostatRadius8 = dOuterCryostatRadius10;

    G4double dInnerCryostatUS1PlacementX = 0.0000 * cm;
    G4double dInnerCryostatUS1PlacementY = 0.0000 * cm;
    G4double dInnerCryostatUS1PlacementZ = -dInnerCryostatHeight1 + cos(asin(dInnerCryostatRadius4 / dInnerCryostatRadius8)) * dInnerCryostatRadius8 + 1.0*um; // 1.0 here, look into this

    G4double dInnerCryostatPlacementX = 0.0000 * cm;
    G4double dInnerCryostatPlacementY = 0.0000 * cm;
    G4double dInnerCryostatPlacementZ = 0.5 * dCryostatVacuumHeight1 - dInnerCryostatHeight1;

    G4ThreeVector dInnerCryostatXYZ(dInnerCryostatPlacementX, dInnerCryostatPlacementY, dInnerCryostatPlacementZ);

    G4RotationMatrix dInnerCryostatUS1Rot;
    dInnerCryostatUS1Rot.rotateZ(0.00);

    G4ThreeVector dInnerCryostatUS1XYZ(dInnerCryostatUS1PlacementX, dInnerCryostatUS1PlacementY, dInnerCryostatUS1PlacementZ);
    G4Transform3D dInnerCryostatUS1Transform(dInnerCryostatUS1Rot, dInnerCryostatUS1XYZ);

    // Create subtraction solids
    G4GenericPolycone* pInnerCryostatPolycone1 = new G4GenericPolycone("InnerCryostatPolycone1", 0.00, 2 * M_PI, 7, dInnerCryostatRadiusArray, dInnerCryostatHeightArray);
    G4Sphere* pInnerCryostatSphere2 = new G4Sphere("InnerCryostatSphere1", 0.0 * cm, dInnerCryostatRadius8, 0, 2 * M_PI, M_PI - asin(dInnerCryostatRadius4 / dInnerCryostatRadius8), asin(dInnerCryostatRadius4 / dInnerCryostatRadius8));

    G4UnionSolid* pInnerCryostat = new G4UnionSolid("InnerCryostat", pInnerCryostatPolycone1, pInnerCryostatSphere2, dInnerCryostatUS1Transform);

    // Create Inner Cryostat
    G4LogicalVolume* pInnerCryostatLV = new G4LogicalVolume(pInnerCryostat, G4Material::GetMaterial("Stainless Steel"), "InnerCryostatLV");
    G4PVPlacement* pInnerCryostatPV = new G4PVPlacement(0, dInnerCryostatXYZ, pInnerCryostatLV, "InnerCryostat", pMotherLV, false, 0);

    // Set Mother volume
    pMotherLV = pInnerCryostatLV;

    G4VisAttributes* pInnerCryostatVisAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.25));
    pInnerCryostatVisAtt->SetForceSolid(true);
    pInnerCryostatLV->SetVisAttributes(pInnerCryostatVisAtt);

    ///////////////////////////
    // Construct GXe and LXe //
    ///////////////////////////

    // Set GXe and LXe variables
    G4double dGXeAndLXeRadius = 5.66420 * cm;
    G4double dGXeAndLXeHeight = 2 * dInnerCryostatHeight1 + dInnerCryostatRadius8 * (cos(asin(dGXeAndLXeRadius / dInnerCryostatRadius8)) - cos(asin(dInnerCryostatRadius4 / dInnerCryostatRadius8))) - 0.06096 * cm;

    ///////////////////
    // Construct GXe //
    ///////////////////

    // Set GXe variables
    G4double dGXeRadius = dGXeAndLXeRadius;
    G4double dGXeHeight = 47.00000*cm;

    G4double dGXePlacementX = 0.00000 * cm;
    G4double dGXePlacementY = 0.00000 * cm;
    G4double dGXePlacementZ = dInnerCryostatHeight1 - 0.5 * dGXeHeight;

    G4double dGXePTFE03PlacementX = 0.00 * cm;
    G4double dGXePTFE03PlacementY = 0.00 * cm;
    G4double dGXePTFE03PlacementZ = -0.5 * dGXeHeight;

    G4ThreeVector dGXeXYZ(dGXePlacementX, dGXePlacementY, dGXePlacementZ);

    // Create Subtraction solids
    G4Tubs* pGXe = new G4Tubs("GXeCylinder", 0.0*cm, dGXeRadius, 0.5 * dGXeHeight, 0.0, 2 * M_PI);

    // Create GXe
    G4LogicalVolume* pGXeLV = new G4LogicalVolume(pGXe, G4Material::GetMaterial("GXe"), "GXeLV");
    G4PVPlacement* pGXePV = new G4PVPlacement(0, dGXeXYZ, pGXeLV, "GXe", pMotherLV, false, 0);

    ///////////////////
    // Construct LXe //
    ///////////////////

    // Set LXe variables
    G4double dLXeRadius1 = dGXeAndLXeRadius;
    G4double dLXeHeight1 = dGXeAndLXeHeight - dGXeHeight;
    G4double dLXeRadius2 = dInnerCryostatRadius8;

    G4double dLXeUS1PlacementX = 0.00000 * cm;
    G4double dLXeUS1PlacementY = 0.00000 * cm;
    G4double dLXeUS1PlacementZ = -0.5 * dLXeHeight1 + cos(asin(dLXeRadius1 / dLXeRadius2)) * dLXeRadius2;

    G4double dLXePlacementX = 0.00000*cm;
    G4double dLXePlacementY = 0.00000*cm;
    G4double dLXePlacementZ = dInnerCryostatHeight1 - dGXeHeight - 0.5 * dLXeHeight1;

    G4double dLXePTFE03PlacementX = 0.00 * cm;
    G4double dLXePTFE03PlacementY = 0.00 * cm;
    G4double dLXePTFE03PlacementZ = 0.5 * dLXeHeight1;

    G4ThreeVector dLXePlacementXYZ(dLXePlacementX, dLXePlacementY, dLXePlacementZ);

    G4RotationMatrix dLXeUS1Rot;
    dLXeUS1Rot.rotateZ(0.00);
    G4ThreeVector dLXeUS1XYZ(dLXeUS1PlacementX, dLXeUS1PlacementY, dLXeUS1PlacementZ);
    G4Transform3D dLXeUS1Transform(dLXeUS1Rot, dLXeUS1XYZ);

    // Create subtraction solids
    G4Tubs* pLXeCylinder1 = new G4Tubs("LXeCylinder1", 0.0 * cm, dLXeRadius1, 0.5 * dLXeHeight1, 0.0, 2 * M_PI);
    G4Sphere* pLXeSphere2 = new G4Sphere("LXeSphere2", 0.0 * cm, dLXeRadius2, 0.0, 2 * M_PI, M_PI - asin(dLXeRadius1 / dLXeRadius2), asin(dLXeRadius1 / dLXeRadius2));

    G4UnionSolid* pLXe = new G4UnionSolid("LXe", pLXeCylinder1, pLXeSphere2, dLXeUS1Transform);

    // Create LXe
    G4LogicalVolume* pLXeLV = new G4LogicalVolume(pLXe, G4Material::GetMaterial("LXe"), "LXeLV");
    G4PVPlacement* pLXePV = new G4PVPlacement(0, dLXePlacementXYZ, pLXeLV, "LXe", pMotherLV, false, 0);

    G4VisAttributes* pLXeVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.30));
    pLXeVisAtt->SetForceSolid(true);
    pLXeLV->SetVisAttributes(pLXeVisAtt);

    pMotherLV = pLXeLV;

    ///////////////////////
    // Construct PTFE03B //
    ///////////////////////

    // Set PTFE03B Variables
    G4double dPTFE03BRadius1 = 32.00 * mm;
    G4double dPTFE03BRadius2 = 54.00 * mm;
    G4double dPTFE03BRadius3 = dPTFE03BRadius2;
    G4double dPTFE03BRadius4 = 43.00 * mm;
    G4double dPTFE03BRadius5 = dPTFE03BRadius4;
    G4double dPTFE03BRadius6 = 35.00 * mm;
    G4double dPTFE03BRadius7 = dPTFE03BRadius6;
    G4double dPTFE03BRadius8 = dPTFE03BRadius1;

    G4double dPTFE03BRadiusArray[] = {dPTFE03BRadius1,
                                      dPTFE03BRadius2,
                                      dPTFE03BRadius3,
                                      dPTFE03BRadius4,
                                      dPTFE03BRadius5,
                                      dPTFE03BRadius6,
                                      dPTFE03BRadius7,
                                      dPTFE03BRadius8};

    G4double dPTFE03BHeight1 = 0.00 * mm;
    G4double dPTFE03BHeight2 = dPTFE03BHeight1;
    G4double dPTFE03BHeight3 = -2.50 * mm;
    G4double dPTFE03BHeight4 = dPTFE03BHeight3;
    G4double dPTFE03BHeight5 = -1.00 * mm;
    G4double dPTFE03BHeight6 = dPTFE03BHeight5;
    G4double dPTFE03BHeight7 = -2.40 * mm;
    G4double dPTFE03BHeight8 = dPTFE03BHeight7;

    G4double dPTFE03BHeightArray[] = {dPTFE03BHeight1,
                                      dPTFE03BHeight2,
                                      dPTFE03BHeight3,
                                      dPTFE03BHeight4,
                                      dPTFE03BHeight5,
                                      dPTFE03BHeight6,
                                      dPTFE03BHeight7,
                                      dPTFE03BHeight8};

    G4double dPTFE03BPlacementX = 0.00 * mm;
    G4double dPTFE03BPlacementY = 0.00 * mm;
    G4double dPTFE03BPlacementZ = 0.5 * dLXeHeight1;

    G4ThreeVector dPTFE03BPlacement(dPTFE03BPlacementX, dPTFE03BPlacementY, dPTFE03BPlacementZ);

    G4GenericPolycone* pPTFE03B = new G4GenericPolycone("pPTFE03B", 0, 2 * M_PI, 8, dPTFE03BRadiusArray, dPTFE03BHeightArray);
    pPTFE03BLV = new G4LogicalVolume(pPTFE03B, G4Material::GetMaterial("PTFE"), "PTFE03B");
    pPTFE03BPV = new G4PVPlacement(0, dPTFE03BPlacement, pPTFE03BLV, "PTFE03B", pMotherLV, false, 0);

    //////////////////////
    // Construct PTFE02 //
    //////////////////////

    // Set PTFE02 Variables
    G4double dPTFE02Radius1  = dPTFE03BRadius1;
    G4double dPTFE02Radius2  = dPTFE03BRadius6;
    G4double dPTFE02Radius3  = dPTFE03BRadius6;
    G4double dPTFE02Radius4  = dPTFE03BRadius4;
    G4double dPTFE02Radius5  = dPTFE03BRadius4;
    G4double dPTFE02Radius6  = dPTFE03BRadius2;
    G4double dPTFE02Radius7  = dPTFE03BRadius2;
    G4double dPTFE02Radius8  = 36.00 * mm;
    G4double dPTFE02Radius9  = dPTFE02Radius8;
    G4double dPTFE02Radius10 = dPTFE03BRadius6;
    G4double dPTFE02Radius11 = dPTFE03BRadius6;
    G4double dPTFE02Radius12 = dPTFE02Radius8;
    G4double dPTFE02Radius13 = dPTFE02Radius8;
    G4double dPTFE02Radius14 = dPTFE03BRadius2;
    G4double dPTFE02Radius15 = dPTFE03BRadius2;
    G4double dPTFE02Radius16 = dPTFE03BRadius4;
    G4double dPTFE02Radius17 = dPTFE03BRadius4;
    G4double dPTFE02Radius18 = dPTFE03BRadius6;
    G4double dPTFE02Radius19 = dPTFE03BRadius6;
    G4double dPTFE02Radius20 = dPTFE03BRadius1;

    G4double dPTFE02RadiusArray[] = {dPTFE02Radius1,
                                     dPTFE02Radius2,
                                     dPTFE02Radius3,
                                     dPTFE02Radius4,
                                     dPTFE02Radius5,
                                     dPTFE02Radius6,
                                     dPTFE02Radius7,
                                     dPTFE02Radius8,
                                     dPTFE02Radius9,
                                     dPTFE02Radius10,
                                     dPTFE02Radius11,
                                     dPTFE02Radius12,
                                     dPTFE02Radius13,
                                     dPTFE02Radius14,
                                     dPTFE02Radius15,
                                     dPTFE02Radius16,
                                     dPTFE02Radius17,
                                     dPTFE02Radius18,
                                     dPTFE02Radius19,
                                     dPTFE02Radius20};

    G4double dPTFE02Height1  = 19.90 * mm;
    G4double dPTFE02Height2  = dPTFE02Height1;
    G4double dPTFE02Height3  = 18.50 * mm;
    G4double dPTFE02Height4  = dPTFE02Height3;
    G4double dPTFE02Height5  = 20.00 * mm;
    G4double dPTFE02Height6  = dPTFE02Height5;
    G4double dPTFE02Height7  = 14.50 * mm;
    G4double dPTFE02Height8  = dPTFE02Height7;
    G4double dPTFE02Height9  = 15.50 * mm;
    G4double dPTFE02Height10 = dPTFE02Height9;
    G4double dPTFE02Height11 = -15.50 * mm;
    G4double dPTFE02Height12 = dPTFE02Height11;
    G4double dPTFE02Height13 = -14.50 * mm;
    G4double dPTFE02Height14 = dPTFE02Height13;
    G4double dPTFE02Height15 = -dPTFE02Height5;
    G4double dPTFE02Height16 = -dPTFE02Height5;
    G4double dPTFE02Height17 = -dPTFE02Height3;
    G4double dPTFE02Height18 = -dPTFE02Height3;
    G4double dPTFE02Height19 = -dPTFE02Height1;
    G4double dPTFE02Height20 = -dPTFE02Height1;

    G4double dPTFE02HeightArray[] = {dPTFE02Height1,
                                     dPTFE02Height2,
                                     dPTFE02Height3,
                                     dPTFE02Height4,
                                     dPTFE02Height5,
                                     dPTFE02Height6,
                                     dPTFE02Height7,
                                     dPTFE02Height8,
                                     dPTFE02Height9,
                                     dPTFE02Height10,
                                     dPTFE02Height11,
                                     dPTFE02Height12,
                                     dPTFE02Height13,
                                     dPTFE02Height14,
                                     dPTFE02Height15,
                                     dPTFE02Height16,
                                     dPTFE02Height17,
                                     dPTFE02Height18,
                                     dPTFE02Height19,
                                     dPTFE02Height20};

    G4double dPTFE02PlacementX = 0.00 * mm;
    G4double dPTFE02PlacementY = 0.00 * mm;
    G4double dPTFE02PlacementZ = 0.5 * dLXeHeight1 + dPTFE03BHeight3 - dPTFE02Height5;

    G4ThreeVector dPTFE02Placement(dPTFE02PlacementX, dPTFE02PlacementY, dPTFE02PlacementZ);

    G4GenericPolycone* pPTFE02 = new G4GenericPolycone("PTFE02", 0, 2 * M_PI, 20, dPTFE02RadiusArray, dPTFE02HeightArray);

    pPTFE02LV = new G4LogicalVolume(pPTFE02, G4Material::GetMaterial("PTFE"), "PTFE02");
    pPTFE02PV = new G4PVPlacement(0, dPTFE02Placement, pPTFE02LV, "PTFE02", pMotherLV, false, 0);

    /////////////////////
    // Consruct PTFE01 //
    /////////////////////

    // Set PTFE01 variables
    G4double dPTFE01Radius1  = dPTFE03BRadius1;
    G4double dPTFE01Radius2  = dPTFE03BRadius6;
    G4double dPTFE01Radius3  = dPTFE03BRadius6;
    G4double dPTFE01Radius4  = dPTFE03BRadius4;
    G4double dPTFE01Radius5  = dPTFE03BRadius4;
    G4double dPTFE01Radius6  = dPTFE03BRadius2;
    G4double dPTFE01Radius7  = dPTFE03BRadius2;
    G4double dPTFE01Radius8  = dPTFE03BRadius4;
    G4double dPTFE01Radius9  = dPTFE03BRadius4;
    G4double dPTFE01Radius10 = dPTFE03BRadius6;
    G4double dPTFE01Radius11 = dPTFE03BRadius6;
    G4double dPTFE01Radius12 = dPTFE03BRadius1;

    G4double dPTFE01RadiusArray[] = {dPTFE01Radius1,
                                     dPTFE01Radius2,
                                     dPTFE01Radius3,
                                     dPTFE01Radius4,
                                     dPTFE01Radius5,
                                     dPTFE01Radius6,
                                     dPTFE01Radius7,
                                     dPTFE01Radius8,
                                     dPTFE01Radius9,
                                     dPTFE01Radius10,
                                     dPTFE01Radius11,
                                     dPTFE01Radius12};

    G4double dPTFE01Height1  = 26.525 * mm;
    G4double dPTFE01Height2  = dPTFE01Height1;
    G4double dPTFE01Height3  = 25.125 * mm;
    G4double dPTFE01Height4  = dPTFE01Height3;
    G4double dPTFE01Height5  = 26.625 * mm;
    G4double dPTFE01Height6  = dPTFE01Height5;
    G4double dPTFE01Height7  = -dPTFE01Height5;
    G4double dPTFE01Height8  = -dPTFE01Height5;
    G4double dPTFE01Height9  = 22.875 * mm;
    G4double dPTFE01Height10 = dPTFE01Height9;
    G4double dPTFE01Height11 = 21.475 * mm;
    G4double dPTFE01Height12 = dPTFE01Height11;

    G4double dPTFE01HeightArray[] = {dPTFE01Height1,
                                     dPTFE01Height2,
                                     dPTFE01Height3,
                                     dPTFE01Height4,
                                     dPTFE01Height5,
                                     dPTFE01Height6,
                                     dPTFE01Height7,
                                     dPTFE01Height8,
                                     dPTFE01Height9,
                                     dPTFE01Height10,
                                     dPTFE01Height11,
                                     dPTFE01Height12};

    G4double dPTFE01PlacementX = 0.00 * mm;
    G4double dPTFE01PlacementY = 0.00 * mm;
    G4double dPTFE01PlacementZ = dPTFE02PlacementZ - dPTFE02Height5 - dPTFE01Height5;

    G4ThreeVector dPTFE01Placement(dPTFE01PlacementX, dPTFE01PlacementY, dPTFE01PlacementZ);

    G4GenericPolycone* pPTFE01 = new G4GenericPolycone("PTFE01", 0, 2 * M_PI, 12, dPTFE01RadiusArray, dPTFE01HeightArray);

    pPTFE01LV = new G4LogicalVolume(pPTFE01, G4Material::GetMaterial("PTFE"), "PTFE01");
    pPTFE01PV = new G4PVPlacement(0, dPTFE01Placement, pPTFE01LV, "PTFE01", pMotherLV, false, 0);

    //////////////////////
    // Construct PTFE00 //
    //////////////////////

    // Set PTFE00 Variables
    G4double dPTFE00Radius1 = 29.00 * mm;;
    G4double dPTFE00Radius2 = dPTFE03BRadius2;
    G4double dPTFE00Radius3 = dPTFE03BRadius2;
    G4double dPTFE00Radius4 = 37.65 * mm;
    G4double dPTFE00Radius5 = dPTFE00Radius4;
    G4double dPTFE00Radius6 = dPTFE00Radius1;

    G4double dPTFE00RadiusArray[] = {dPTFE00Radius1,
                                     dPTFE00Radius2,
                                     dPTFE00Radius3,
                                     dPTFE00Radius4,
                                     dPTFE00Radius5,
                                     dPTFE00Radius6};

    G4double dPTFE00Height1 = 15.00 * mm;
    G4double dPTFE00Height2 = dPTFE00Height1;
    G4double dPTFE00Height3 = 10.00 * mm;
    G4double dPTFE00Height4 = dPTFE00Height3;
    G4double dPTFE00Height5 = -dPTFE00Height1;
    G4double dPTFE00Height6 = -dPTFE00Height1;

    G4double dPTFE00HeightArray[] = {dPTFE00Height1,
                                     dPTFE00Height2,
                                     dPTFE00Height3,
                                     dPTFE00Height4,
                                     dPTFE00Height5,
                                     dPTFE00Height6};

    G4double dPTFE00PlacementX = 0.00 * mm;
    G4double dPTFE00PlacementY = 0.00 * mm;
    G4double dPTFE00PlacementZ = dPTFE01PlacementZ - dPTFE01Height5 - dPTFE00Height1;

    G4ThreeVector dPTFE00Placement(dPTFE00PlacementX, dPTFE00PlacementY, dPTFE00PlacementZ);

    G4GenericPolycone* pPTFE00 = new G4GenericPolycone("PTFE00", 0, 2 * M_PI, 6, dPTFE00RadiusArray, dPTFE00HeightArray);

    pPTFE00LV = new G4LogicalVolume(pPTFE00, G4Material::GetMaterial("PTFE"), "PTFE00");
    pPTFE00PV = new G4PVPlacement(0, dPTFE00Placement, pPTFE00LV, "PTFE00", pMotherLV, false, 0);

    ////////////////////////
    // Construct PMT Ring //
    ////////////////////////

    // Set PMT Ring variables
    G4double dPMTRingRadius1 = 37.69 * mm;
    G4double dPMTRingRadius2 = 41.50 * mm;
    G4double dPMTRingHeight  =  2.48 * mm;

    G4double dPMTRingPlacementX = 0.00 * mm;
    G4double dPMTRingPlacementY = 0.00 * mm;
    G4double dPMTRingPlacementZ = dPTFE01PlacementZ + dPTFE01Height9 - 0.5 * dPMTRingHeight;

    G4ThreeVector dPMTRingPlacement(dPMTRingPlacementX, dPMTRingPlacementY, dPMTRingPlacementZ);

    G4Tubs* pPMTRing = new G4Tubs("PMTRing", dPMTRingRadius1, dPMTRingRadius2, 0.5 * dPMTRingHeight, 0, 2 * M_PI);
    pPMTRingLV = new G4LogicalVolume(pPMTRing, G4Material::GetMaterial("Stainless Steel"), "PMTRing");
    pPMTRingPV = new G4PVPlacement(0, dPMTRingPlacement, pPMTRingLV, "PMTRing", pMotherLV, false, 0);

    ///////////////////
    // Construct PMT //
    ///////////////////

    // Set PMT variables
    G4double dPMTRadius1  = 0.000 * cm;
    G4double dPMTRadius2  = 3.500 * cm;
    G4double dPMTRadius3  = dPMTRadius2;
    G4double dPMTRadius4  = 3.800 * cm;
    G4double dPMTRadius5  = dPMTRadius4;
    G4double dPMTRadius6  = 3.875 * cm;
    G4double dPMTRadius7  = dPMTRadius6;
    G4double dPMTRadius8  = dPMTRadius4;
    G4double dPMTRadius9  = dPMTRadius4;
    G4double dPMTRadius10 = 2.665 * cm;
    G4double dPMTRadius11 = dPMTRadius10;
    G4double dPMTRadius12 = 2.715 * cm;
    G4double dPMTRadius13 = dPMTRadius12;
    G4double dPMTRadius14 = dPMTRadius10;
    G4double dPMTRadius15 = dPMTRadius10;
    G4double dPMTRadius16 = dPMTRadius12;
    G4double dPMTRadius17 = dPMTRadius12;
    G4double dPMTRadius18 = dPMTRadius10;
    G4double dPMTRadius19 = dPMTRadius10;
    G4double dPMTRadius20 = dPMTRadius1;

    G4double dPMTRadiusArray[] = {dPMTRadius1,
                                  dPMTRadius2,
                                  dPMTRadius3,
                                  dPMTRadius4,
                                  dPMTRadius5,
                                  dPMTRadius6,
                                  dPMTRadius7,
                                  dPMTRadius8,
                                  dPMTRadius9,
                                  dPMTRadius10,
                                  dPMTRadius11,
                                  dPMTRadius12,
                                  dPMTRadius13,
                                  dPMTRadius14,
                                  dPMTRadius15,
                                  dPMTRadius16,
                                  dPMTRadius17,
                                  dPMTRadius18,
                                  dPMTRadius19,
                                  dPMTRadius20};

    G4double dPMTHeight1  = 5.700 * cm;
    G4double dPMTHeight2  = dPMTHeight1;
    G4double dPMTHeight3  = 5.650 * cm;
    G4double dPMTHeight4  = dPMTHeight3;
    G4double dPMTHeight5  = 4.800 * cm;
    G4double dPMTHeight6  = dPMTHeight5;
    G4double dPMTHeight7  = 4.300 * cm;
    G4double dPMTHeight8  = dPMTHeight7;
    G4double dPMTHeight9  = 3.120 * cm;
    G4double dPMTHeight10 = 1.940 * cm;
    G4double dPMTHeight11 = 0.940 * cm;
    G4double dPMTHeight12 = dPMTHeight11;
    G4double dPMTHeight13 = 0.840 * cm;
    G4double dPMTHeight14 = dPMTHeight13;
    G4double dPMTHeight15 = 5.100 * cm;
    G4double dPMTHeight16 = dPMTHeight15;
    G4double dPMTHeight17 = 5.200 * cm;
    G4double dPMTHeight18 = dPMTHeight17;
    G4double dPMTHeight19 = -dPMTHeight1;
    G4double dPMTHeight20 = -dPMTHeight1;

    G4double dPMTHeightArray[] = {dPMTHeight1,
                                  dPMTHeight2,
                                  dPMTHeight3,
                                  dPMTHeight4,
                                  dPMTHeight5,
                                  dPMTHeight6,
                                  dPMTHeight7,
                                  dPMTHeight8,
                                  dPMTHeight9,
                                  dPMTHeight10,
                                  dPMTHeight11,
                                  dPMTHeight12,
                                  dPMTHeight13,
                                  dPMTHeight14,
                                  dPMTHeight15,
                                  dPMTHeight16,
                                  dPMTHeight17,
                                  dPMTHeight18,
                                  dPMTHeight19,
                                  dPMTHeight20};

    G4double dPMTPlacementX = 0.000 * cm;
    G4double dPMTPlacementY = 0.000 ;
    G4double dPMTPlacementZ = dPMTRingPlacementZ - 0.5 * dPMTRingHeight - dPMTHeight3;

    G4ThreeVector dPMTPlacement(dPMTPlacementX, dPMTPlacementY, dPMTPlacementZ);

    G4GenericPolycone* pPMT = new G4GenericPolycone("PMT", 0, 2 * M_PI, 20, dPMTRadiusArray, dPMTHeightArray);

  	G4LogicalVolume* pPMTLV = new G4LogicalVolume(pPMT, G4Material::GetMaterial("Kovar"), "PMT");
  	G4PVPlacement* pPMTPV = new G4PVPlacement(0, dPMTPlacement, pPMTLV, "PMT", pMotherLV, false, 0);

    pMotherLV = pPMTLV;

    //////////////////////////
    // Construct PMT Vacuum //
    //////////////////////////

    // Set PMT Vacuum Variables
    G4double dPMTVacuumRadius1 = dPMTRadius1;
    G4double dPMTVacuumRadius2 = dPMTRadius2;
    G4double dPMTVacuumRadius3 = dPMTRadius3;
    G4double dPMTVacuumRadius4 = 3.700 * cm;
    G4double dPMTVacuumRadius5 = dPMTVacuumRadius4;
    G4double dPMTVacuumRadius6 = 2.565 * cm;
    G4double dPMTVacuumRadius7 = dPMTVacuumRadius6;
    G4double dPMTVacuumRadius8 = dPMTRadius20;

    G4double dPMTVacuumHeight1 = dPMTHeight1;
    G4double dPMTVacuumHeight2 = dPMTHeight2;
    G4double dPMTVacuumHeight3 = 5.550 * cm;
    G4double dPMTVacuumHeight4 = dPMTVacuumHeight3;
    G4double dPMTVacuumHeight5 = dPMTHeight9;
    G4double dPMTVacuumHeight6 = dPMTHeight10;
    G4double dPMTVacuumHeight7 = dPMTHeight20;
    G4double dPMTVacuumHeight8 = dPMTHeight20;

    G4double dPMTVacuumRadiusArray[] = {dPMTVacuumRadius1,
    									dPMTVacuumRadius2,
    									dPMTVacuumRadius3,
    									dPMTVacuumRadius4,
    									dPMTVacuumRadius5,
    									dPMTVacuumRadius6,
    									dPMTVacuumRadius7,
    									dPMTVacuumRadius8};

    G4double dPMTVacuumHeightArray[] = {dPMTVacuumHeight1,
    									dPMTVacuumHeight2,
    									dPMTVacuumHeight3,
    									dPMTVacuumHeight4,
    									dPMTVacuumHeight5,
    									dPMTVacuumHeight6,
    									dPMTVacuumHeight7,
    									dPMTVacuumHeight8};

    // Create PMT Vacuum
    G4GenericPolycone* pPMTVacuum = new G4GenericPolycone("PMTVacuum", 0, 2 * M_PI, 8, dPMTVacuumRadiusArray, dPMTVacuumHeightArray);
    G4LogicalVolume* pPMTVacuumLV = new G4LogicalVolume(pPMTVacuum, G4Material::GetMaterial("Vacuum"), "PMTVacuum");
    G4PVPlacement* pPMTVacuumPV = new G4PVPlacement(0, G4ThreeVector(), pPMTVacuumLV, "PMTVacuum", pPMTLV, false, 0);

    pMotherLV = pPMTVacuumLV;

  	//////////////////////////
    // Construct PMT Window //
    //////////////////////////

    // Set PMT Window Variables
    G4double dPMTWindowRadius = dPMTRadius2;

    G4double dPMTWindowHeight = 0.500 * cm;

    G4double dPMTWindowPlacementX = 0.0 * cm;
    G4double dPMTWindowPlacementY = 0.0 * cm;
    G4double dPMTWindowPlacementZ = -0.5 * dPMTWindowHeight + dPMTHeight2;

    G4ThreeVector dPMTWindowPlacement(dPMTWindowPlacementX, dPMTWindowPlacementY, dPMTWindowPlacementZ);

    // Create PMT Window
    G4Tubs* pPMTWindow = new G4Tubs("PMTWindow", 0, dPMTWindowRadius, 0.5 * dPMTWindowHeight, 0, 2 * M_PI);
    G4LogicalVolume* pPMTWindowLV = new G4LogicalVolume(pPMTWindow, G4Material::GetMaterial("Quartz"), "PMTWindow");
    G4PVPlacement* pPMTWindowPV = new G4PVPlacement(0, dPMTWindowPlacement, pPMTWindowLV, "PMTWindow", pMotherLV, false, 0);

///////////////////////////////////////////////////////////////////////////
/////////////// Print Out Z Centers of PMT, GXe, and LXe //////////////////
G4cout << "PMT Center: " << dPMTPlacementZ + dLXePlacementZ + dInnerCryostatPlacementZ + dCryostatVacuumPlacementZ + dOuterCryostatPlacementZ << endl;
G4cout << "GXe Center: " << dGXePlacementZ + dInnerCryostatPlacementZ + dCryostatVacuumPlacementZ + dOuterCryostatPlacementZ << endl;
G4cout << "LXe Center: " << dLXePlacementZ + dInnerCryostatPlacementZ + dCryostatVacuumPlacementZ + dOuterCryostatPlacementZ << endl;
G4cout << "Liquid-Gas Interface: " << dGXePlacementZ + dInnerCryostatPlacementZ + dCryostatVacuumPlacementZ + dOuterCryostatPlacementZ - 0.5*dGXeHeight << endl; 
G4cout << "Second Check of Liquid-Gas Interface: " << dLXePlacementZ + dInnerCryostatPlacementZ + dCryostatVacuumPlacementZ + dOuterCryostatPlacementZ + 0.5*dLXeHeight1 << endl;
G4cout << "Top of PMT: " << dPMTPlacementZ + dLXePlacementZ + dInnerCryostatPlacementZ + dCryostatVacuumPlacementZ + dOuterCryostatPlacementZ + dPMTHeight1 << endl;
G4cout << "Distance from PMT Center to Top of PMT: " << dPMTHeight1 << endl;

/////////////////////////////////////////////////////
//Creation of Sensitive Detector ////////////////////
/////////////////////////////////////////////////////

   G4SDManager * pSDManager = G4SDManager::GetSDMpointer();
   Xenon1tPmtSensitiveDetector * pPMTWindowSD;
   pPMTWindowSD = new Xenon1tPmtSensitiveDetector("Xenon1t/PMTWindowSD");
   pSDManager->AddNewDetector(pPMTWindowSD);
   pPMTWindowLV->SetSensitiveDetector(pPMTWindowSD);

  	////////////////////////////////
    // Construct PMT Photocathode //
    ////////////////////////////////

    // Set PMT Photocathode Variables
    G4double dPMTPhotocathodeRadius = 3.200 * cm;
    G4double dPMTPhotocathodeHeight = 0.100 * cm;

    G4double dPMTPhotocathodePlacementX = 0.0 * cm;
    G4double dPMTPhotocathodePlacementY = 0.0 * cm;
    G4double dPMTPhotocathodePlacementZ = 4.950 * cm;

    G4ThreeVector dPMTPhotocathodePlacement(dPMTPhotocathodePlacementX, dPMTPhotocathodePlacementY, dPMTPhotocathodePlacementZ);

    // Create PMT Photocathode
    G4Tubs* pPMTPhotocathode = new G4Tubs("PMTPhotocathode", 0, dPMTPhotocathodeRadius, 0.5 * dPMTPhotocathodeHeight, 0, 2 * M_PI);
    G4LogicalVolume* pPMTPhotocathodeLV = new G4LogicalVolume(pPMTPhotocathode, G4Material::GetMaterial("Photocathode"), "PMTPhotocathode");
    G4PVPlacement* pPMTPhotocathodePV = new G4PVPlacement(0, dPMTPhotocathodePlacement, pPMTPhotocathodeLV, "PMTPhotocathode", pMotherLV, false, 0);

    ///////////////////////////
    // Construct PMT Ceramic //
    ///////////////////////////

    // Set PMT Ceramic Variables
    G4double dPMTCeramicRadius = dPMTVacuumRadius6;
    G4double dPMTCeramicHeight = 0.400 * cm;

    G4double dPMTCeramicPlacementX = 0.0 * cm;
    G4double dPMTCeramicPlacementY = 0.0 * cm;
    G4double dPMTCeramicPlacementZ = 0.5 * dPMTCeramicHeight + dPMTHeight19;

    G4ThreeVector dPMTCeramicPlacement(dPMTCeramicPlacementX, dPMTCeramicPlacementY, dPMTCeramicPlacementZ);

    // Create PMT Ceramic
    G4Tubs* pPMTCeramic = new G4Tubs("PMTCeramic", 0, dPMTCeramicRadius, 0.5 * dPMTCeramicHeight, 0, 2 * M_PI);
    G4LogicalVolume* pPMTCeramicLV = new G4LogicalVolume(pPMTCeramic, G4Material::GetMaterial("Ceramic"), "PMTCeramic");
    G4PVPlacement* pPMTCeramicPV = new G4PVPlacement(0, dPMTCeramicPlacement, pPMTCeramicLV, "PMTCeramic", pMotherLV, false, 0);

    //////////////////////
    // Set new MotherLV //
    //////////////////////

    pMotherLV = pGXeLV;

    ///////////////////////
    // Construct PTFE03T //
    ///////////////////////

    // Set PTFE03T Variables
    G4double dPTFE03TRadius1 = dPTFE03BRadius1;
    G4double dPTFE03TRadius2 = dPTFE03BRadius6;
    G4double dPTFE03TRadius3 = dPTFE03BRadius6;
    G4double dPTFE03TRadius4 = dPTFE03BRadius4;
    G4double dPTFE03TRadius5 = dPTFE03BRadius4;
    G4double dPTFE03TRadius6 = dPTFE03BRadius2;
    G4double dPTFE03TRadius7 = dPTFE03BRadius2;
    G4double dPTFE03TRadius8 = dPTFE03BRadius1;

    G4double dPTFE03TRadiusArray[] = {dPTFE03TRadius1,
                                      dPTFE03TRadius2,
                                      dPTFE03TRadius3,
                                      dPTFE03TRadius4,
                                      dPTFE03TRadius5,
                                      dPTFE03TRadius6,
                                      dPTFE03TRadius7,
                                      dPTFE03TRadius8};

    G4double dPTFE03THeight1 = -dPTFE03BHeight7;
    G4double dPTFE03THeight2 = -dPTFE03BHeight7;
    G4double dPTFE03THeight3 = -dPTFE03BHeight5;
    G4double dPTFE03THeight4 = -dPTFE03BHeight5;
    G4double dPTFE03THeight5 = -dPTFE03BHeight3;
    G4double dPTFE03THeight6 = -dPTFE03BHeight3;
    G4double dPTFE03THeight7 = dPTFE03BHeight1;
    G4double dPTFE03THeight8 = dPTFE03BHeight1;

    G4double dPTFE03THeightArray[] = {dPTFE03THeight1,
                                      dPTFE03THeight2,
                                      dPTFE03THeight3,
                                      dPTFE03THeight4,
                                      dPTFE03THeight5,
                                      dPTFE03THeight6,
                                      dPTFE03THeight7,
                                      dPTFE03THeight8};

    G4double dPTFE03TPlacementX = 0.00 * mm;
    G4double dPTFE03TPlacementY = 0.00 * mm;
    G4double dPTFE03TPlacementZ = -0.5 * dGXeHeight;

    G4ThreeVector dPTFE03TPlacement(dPTFE03TPlacementX, dPTFE03TPlacementY, dPTFE03TPlacementZ);

    G4GenericPolycone* pPTFE03T = new G4GenericPolycone("pPTFE03T", 0, 2 * M_PI, 8, dPTFE03TRadiusArray, dPTFE03THeightArray);
    pPTFE03TLV = new G4LogicalVolume(pPTFE03T, G4Material::GetMaterial("PTFE"), "PTFE03T");
    pPTFE03TPV = new G4PVPlacement(0, dPTFE03TPlacement, pPTFE03TLV, "PTFE03T", pMotherLV, false, 0);

    //////////////////////
    // Construct PTFE04 //
    //////////////////////

    // Set PTFE04 Variables
    G4double dPTFE04Radius1  = dPTFE03TRadius1;
    G4double dPTFE04Radius2  = dPTFE03TRadius2;
    G4double dPTFE04Radius3  = dPTFE03TRadius2;
    G4double dPTFE04Radius4  = dPTFE03TRadius4;
    G4double dPTFE04Radius5  = dPTFE03TRadius4;
    G4double dPTFE04Radius6  = dPTFE03TRadius6;
    G4double dPTFE04Radius7  = dPTFE03TRadius6;
    G4double dPTFE04Radius8  = dPTFE03TRadius4;
    G4double dPTFE04Radius9  = dPTFE03TRadius4;
    G4double dPTFE04Radius10 = dPTFE03TRadius2;
    G4double dPTFE04Radius11 = dPTFE03TRadius2;
    G4double dPTFE04Radius12 = dPTFE03TRadius1;

    G4double dPTFE04RadiusArray[] = {dPTFE04Radius1,
                                     dPTFE04Radius2,
                                     dPTFE04Radius3,
                                     dPTFE04Radius4,
                                     dPTFE04Radius5,
                                     dPTFE04Radius6,
                                     dPTFE04Radius7,
                                     dPTFE04Radius8,
                                     dPTFE04Radius9,
                                     dPTFE04Radius10,
                                     dPTFE04Radius11,
                                     dPTFE04Radius12};

    G4double dPTFE04Height1  = 4.90 * mm;
    G4double dPTFE04Height2  = dPTFE04Height1;
    G4double dPTFE04Height3  = 3.50 * mm;
    G4double dPTFE04Height4  = dPTFE04Height3;
    G4double dPTFE04Height5  = 5.00 * mm;
    G4double dPTFE04Height6  = dPTFE04Height5;
    G4double dPTFE04Height7  = -dPTFE04Height5;
    G4double dPTFE04Height8  = -dPTFE04Height5;
    G4double dPTFE04Height9  = -dPTFE04Height3;
    G4double dPTFE04Height10 = -dPTFE04Height3;
    G4double dPTFE04Height11 = -dPTFE04Height1;
    G4double dPTFE04Height12 = -dPTFE04Height1;

    G4double dPTFE04HeightArray[] = {dPTFE04Height1,
                                     dPTFE04Height2,
                                     dPTFE04Height3,
                                     dPTFE04Height4,
                                     dPTFE04Height5,
                                     dPTFE04Height6,
                                     dPTFE04Height7,
                                     dPTFE04Height8,
                                     dPTFE04Height9,
                                     dPTFE04Height10,
                                     dPTFE04Height11,
                                     dPTFE04Height12};

    G4double dPTFE04PlacementX = 0.000 * mm;
    G4double dPTFE04PlacementY = 0.000 * mm;
    G4double dPTFE04PlacementZ = -0.5 * dGXeHeight + dPTFE03THeight5 + dPTFE04Height5;

    G4ThreeVector dPTFE04Placement(dPTFE04PlacementX, dPTFE04PlacementY, dPTFE04PlacementZ);

    G4GenericPolycone* pPTFE04 = new G4GenericPolycone("PTFE04", 0, 2 * M_PI, 12, dPTFE04RadiusArray, dPTFE04HeightArray);

    // Create PTFE04
    pPTFE04LV = new G4LogicalVolume(pPTFE04, G4Material::GetMaterial("PTFE"), "PTFE04");
    pPTFE04PV = new G4PVPlacement(0, dPTFE04Placement, pPTFE04LV, "PTFE04", pMotherLV, false, 0);

    //////////////////////
    // Construct PTFE05 //
    //////////////////////

    // Set PTFE05 Variables
    G4double  dPTFE05Radius1  = 0.0 * mm;
    G4double  dPTFE05Radius2  = 46.0 * mm;
    G4double  dPTFE05Radius3  = dPTFE05Radius2;
    G4double  dPTFE05Radius4  = dPTFE03TRadius6;
    G4double  dPTFE05Radius5  = dPTFE03TRadius6;
    G4double  dPTFE05Radius6  = dPTFE03TRadius4;
    G4double  dPTFE05Radius7  = dPTFE03TRadius4;
    G4double  dPTFE05Radius8  = dPTFE03TRadius2;
    G4double  dPTFE05Radius9  = dPTFE03TRadius2;
    G4double  dPTFE05Radius10 = dPTFE05Radius1;

    G4double dPTFE05RadiusArray[] = {dPTFE05Radius1,
                                     dPTFE05Radius2,
                                     dPTFE05Radius3,
                                     dPTFE05Radius4,
                                     dPTFE05Radius5,
                                     dPTFE05Radius6,
                                     dPTFE05Radius7,
                                     dPTFE05Radius8,
                                  	 dPTFE05Radius9,
                                  	 dPTFE05Radius10};

    G4double  dPTFE05Height1  = 14.0 * mm;
    G4double  dPTFE05Height2  = dPTFE05Height1;
    G4double  dPTFE05Height3  = -8.5 * mm;
    G4double  dPTFE05Height4  = dPTFE05Height3;
    G4double  dPTFE05Height5  = -dPTFE05Height1;
    G4double  dPTFE05Height6  = -dPTFE05Height1;
    G4double  dPTFE05Height7  = -12.5 * mm;
    G4double  dPTFE05Height8  = dPTFE05Height7;
    G4double  dPTFE05Height9  = -13.9 * mm;
    G4double  dPTFE05Height10 = dPTFE05Height9;

    G4double dPTFE05HeightArray[] = {dPTFE05Height1,
                                     dPTFE05Height2,
                                     dPTFE05Height3,
                                     dPTFE05Height4,
                                     dPTFE05Height5,
                                     dPTFE05Height6,
                                     dPTFE05Height7,
                                     dPTFE05Height8,
                                  	 dPTFE05Height9,
                                  	 dPTFE05Height10};

    G4double dPTFE05PlacementX = 0.000 * mm;
    G4double dPTFE05PlacementY = 0.000 * mm;
    G4double dPTFE05PlacementZ = dPTFE04PlacementZ + dPTFE04Height5 + dPTFE05Height1;
    G4ThreeVector dPTFE05Placement(dPTFE05PlacementX, dPTFE05PlacementY, dPTFE05PlacementZ);

    G4GenericPolycone* pPTFE05 = new G4GenericPolycone("PTFE05", 0, 2 * M_PI, 10, dPTFE05RadiusArray, dPTFE05HeightArray);

    pPTFE05LV = new G4LogicalVolume(pPTFE05, G4Material::GetMaterial("PTFE"), "PTFE05");
    pPTFE05PV = new G4PVPlacement(0, dPTFE05Placement, pPTFE05LV, "PTFE05", pMotherLV, false, 0);

    G4OpticalSurface* pXeXeOpticalSurface = new G4OpticalSurface("XeXeOpticalSurface", unified, polished, dielectric_dielectric);

    G4LogicalBorderSurface* pGXeLXeLogicalBorderSurface = new G4LogicalBorderSurface("GXeLXeLogicalBorderSurface", pLXePV, pGXePV, pXeXeOpticalSurface);

    G4OpticalSurface* pPTFEXeOpticalSurface = new G4OpticalSurface("PTFEXeOpticalSurface", unified, groundbackpainted, dielectric_dielectric, 0.1);
    pPTFEXeOpticalSurface->SetMaterialPropertiesTable(G4Material::GetMaterial("PTFE")->GetMaterialPropertiesTable());

    G4LogicalBorderSurface* pPTFE00XeLogicalBorderSurface = new G4LogicalBorderSurface("PTFE00XeLogicalBorderSurface", pLXePV, pPTFE00PV, pPTFEXeOpticalSurface);
    G4LogicalBorderSurface* pPTFE01XeLogicalBorderSurface = new G4LogicalBorderSurface("PTFE01XeLogicalBorderSurface", pLXePV, pPTFE01PV, pPTFEXeOpticalSurface);
    G4LogicalBorderSurface* pPTFE02XeLogicalBorderSurface = new G4LogicalBorderSurface("PTFE02XeLogicalBorderSurface", pLXePV, pPTFE02PV, pPTFEXeOpticalSurface);
    G4LogicalBorderSurface* pPTFE03BXeLogicalBorderSurface = new G4LogicalBorderSurface("PTFE03BXeLogicalBorderSurface", pLXePV, pPTFE03BPV, pPTFEXeOpticalSurface);

    G4LogicalBorderSurface* pPTFE03TXeLogicalBorderSurface = new G4LogicalBorderSurface("PTFE03TXeLogicalBorderSurface", pGXePV, pPTFE03TPV, pPTFEXeOpticalSurface);
    G4LogicalBorderSurface* pPTFE04XeLogicalBorderSurface = new G4LogicalBorderSurface("PTFE04XeLogicalBorderSurface", pLXePV, pPTFE00PV, pPTFEXeOpticalSurface);
    G4LogicalBorderSurface* pPTFE05XeLogicalBorderSurface = new G4LogicalBorderSurface("PTFE05XeLogicalBorderSurface", pLXePV, pPTFE00PV, pPTFEXeOpticalSurface);
}

void RELAXDetectorConstruction::SetPTFEIndexOfRefraction(G4String* mPTFEIndexOfRefractionData)
{
    pPTFEIndexOfRefractionData = mPTFEIndexOfRefractionData;

    ifsDataFile->open(pPTFEIndexOfRefractionData->c_str(), ios::in);

    G4Material* pPTFEMaterial = G4Material::GetMaterial("PTFE");

    if((ifsDataFile->is_open()) && (pPTFEMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pPTFEMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("RINDEX");

        pMaterialPropertyTable->AddProperty("RINDEX", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the PTFE index of refraction data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetPTFEAbsorptionLengthData(G4String* mPTFEAbsorptionLengthData)
{
    pPTFEAbsorptionLengthData = mPTFEAbsorptionLengthData;

    ifsDataFile->open(pPTFEAbsorptionLengthData->c_str(), ios::in);

    G4Material* pPTFEMaterial = G4Material::GetMaterial("PTFE");

    if((ifsDataFile->is_open()) && (pPTFEMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);
            dData *= cm;

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pPTFEMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("ABSLENGTH");

        pMaterialPropertyTable->AddProperty("ABSLENGTH", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the PTFE absorption length data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetPTFEReflectivity(G4String* mPTFEReflectivityData)
{
    pPTFEReflectivityData = mPTFEReflectivityData;

    ifsDataFile->open(pPTFEReflectivityData->c_str(), ios::in);

    G4Material* pPTFEMaterial = G4Material::GetMaterial("PTFE");

    if((ifsDataFile->is_open()) && (pPTFEMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pPTFEMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("REFLECTIVITY");

        pMaterialPropertyTable->AddProperty("REFLECTIVITY", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the PTFE reflectivity data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetPTFESpecularLobeConstant(G4String* mPTFESpecularLobeConstantData)
{
    pPTFESpecularLobeConstantData = mPTFESpecularLobeConstantData;

    ifsDataFile->open(pPTFESpecularLobeConstantData->c_str(), ios::in);

    G4Material* pPTFEMaterial = G4Material::GetMaterial("PTFE");

    if((ifsDataFile->is_open()) && (pPTFEMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pPTFEMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("SPECULARLOBECONSTANT");

        pMaterialPropertyTable->AddProperty("SPECULARLOBECONSTANT", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the PTFE specular lobe constant data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetPTFESpecularSpikeConstant(G4String* mPTFESpecularSpikeConstantData)
{
    pPTFESpecularSpikeConstantData = mPTFESpecularSpikeConstantData;

    ifsDataFile->open(pPTFESpecularSpikeConstantData->c_str(), ios::in);

    G4Material* pPTFEMaterial = G4Material::GetMaterial("PTFE");

    if((ifsDataFile->is_open()) && (pPTFEMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pPTFEMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("SPECULARSPIKECONSTANT");

        pMaterialPropertyTable->AddProperty("SPECULARSPIKECONSTANT", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the PTFE specular spike constant data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetPTFEBackscatterConstant(G4String* mPTFEBackscatterConstantData)
{
    pPTFEBackscatterConstantData = mPTFEBackscatterConstantData;

    ifsDataFile->open(pPTFEBackscatterConstantData->c_str(), ios::in);

    G4Material* pPTFEMaterial = G4Material::GetMaterial("PTFE");

    if((ifsDataFile->is_open()) && (pPTFEMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pPTFEMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("BACKSCATTERCONSTANT");

        pMaterialPropertyTable->AddProperty("BACKSCATTERCONSTANT", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the PTFE backscatter data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetPTFEEfficiency(G4String* mPTFEEfficiencyData)
{
    pPTFEEfficiencyData = mPTFEEfficiencyData;

    ifsDataFile->open(pPTFEEfficiencyData->c_str(), ios::in);

    G4Material* pPTFEMaterial = G4Material::GetMaterial("PTFE");

    if((ifsDataFile->is_open()) && (pPTFEMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pPTFEMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("EFFICIENCY");

        pMaterialPropertyTable->AddProperty("EFFICIENCY", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the PTFE efficiency data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetLXeScintillationSpectrumData(G4String* mLXeScintillationSpectrumData)
{
    pLXeScintillationSpectrumData = mLXeScintillationSpectrumData;

    ifsDataFile->open(pLXeScintillationSpectrumData->c_str(), ios::in);

    G4Material* pLXeMaterial = G4Material::GetMaterial("LXe");

    if((ifsDataFile->is_open()) && (pLXeMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pLXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("FASTCOMPONENT");
        pMaterialPropertyTable->RemoveProperty("SLOWCOMPONENT");

        pMaterialPropertyTable->AddProperty("FASTCOMPONENT", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
        pMaterialPropertyTable->AddProperty("SLOWCOMPONENT", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the LXe scintillation spectrum data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetLXeIndexOfRefractionData(G4String* mLXeIndexOfRefractionData)
{
    pLXeIndexOfRefractionData = mLXeIndexOfRefractionData;

    ifsDataFile->open(pLXeIndexOfRefractionData->c_str(), ios::in);

    G4Material* pLXeMaterial = G4Material::GetMaterial("LXe");

    if((ifsDataFile->is_open()) && (pLXeMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pLXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("RINDEX");

        pMaterialPropertyTable->AddProperty("RINDEX", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the LXe index of refraction data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetLXeAbsorptionLengthData(G4String* mLXeAbsorptionLengthData)
{
    pLXeAbsorptionLengthData = mLXeAbsorptionLengthData;

    ifsDataFile->open(pLXeAbsorptionLengthData->c_str(), ios::in);

    G4Material* pLXeMaterial = G4Material::GetMaterial("LXe");

    if((ifsDataFile->is_open()) && (pLXeMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);
            dData *= m;

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pLXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("ABSLENGTH");

        pMaterialPropertyTable->AddProperty("ABSLENGTH", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the LXe absorption length data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetLXeRayleighScatteringLengthData(G4String* mLXeRayleighScatteringLengthData)
{
    pLXeRayleighScatteringLengthData = mLXeRayleighScatteringLengthData;

    ifsDataFile->open(pLXeRayleighScatteringLengthData->c_str(), ios::in);

    G4Material* pLXeMaterial = G4Material::GetMaterial("LXe");

    if((ifsDataFile->is_open()) && (pLXeMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);
            dData *= m;

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pLXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("RAYLEIGH");

        pMaterialPropertyTable->AddProperty("RAYLEIGH", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the LXe Rayleigh scattering length data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetLXeFanoFactor(G4double mLXeFanoFactor)
{
    dLXeFanoFactor = mLXeFanoFactor;

    G4Material* pLXeMaterial = G4Material::GetMaterial("LXe");

    if(pLXeMaterial)
    {
        pMaterialPropertyTable = pLXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("RESOLUTIONSCALE");

        pMaterialPropertyTable->AddConstProperty("RESOLUTIONSCALE", dLXeFanoFactor);
    }
}

void RELAXDetectorConstruction::SetLXeFastScintillationTimeConstant(G4double mLXeFastScintillationTimeConstant)
{
    dLXeFastScintillationTimeConstant = mLXeFastScintillationTimeConstant;

    G4Material* pLXeMaterial = G4Material::GetMaterial("LXe");

    if(pLXeMaterial)
    {
        pMaterialPropertyTable = pLXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("FASTTIMECONSTANT");

        pMaterialPropertyTable->AddConstProperty("FASTTIMECONSTANT", dLXeFastScintillationTimeConstant);
    }

    else
    {
        G4cout << "Could not find the LXe material." << G4endl;
    }
}

void RELAXDetectorConstruction::SetLXeSlowScintillationTimeConstant(G4double mLXeSlowScintillationTimeConstant)
{
    dLXeSlowScintillationTimeConstant = mLXeSlowScintillationTimeConstant;

    G4Material* pLXeMaterial = G4Material::GetMaterial("LXe");

    if(pLXeMaterial)
    {
        pMaterialPropertyTable = pLXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("SLOWTIMECONSTANT");

        pMaterialPropertyTable->AddConstProperty("SLOWTIMECONSTANT", dLXeSlowScintillationTimeConstant);
    }

    else
    {
        G4cout << "Could not find the LXe material." << G4endl;
    }
}

void RELAXDetectorConstruction::SetLXeDensityData(G4String* mLXeDensityData)
{
    pLXeDensityData = mLXeDensityData;

    ifsDataFile->open(pLXeDensityData->c_str(), ios::in);
    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetGXeScintillationSpectrumData(G4String* mGXeScintillationSpectrumData)
{
    pGXeScintillationSpectrumData = mGXeScintillationSpectrumData;

    ifsDataFile->open(pGXeScintillationSpectrumData->c_str(), ios::in);

    G4Material* pGXeMaterial = G4Material::GetMaterial("GXe");

    if((ifsDataFile->is_open()) && (pGXeMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pGXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("FASTCOMPONENT");
        pMaterialPropertyTable->RemoveProperty("SLOWCOMPONENT");

        pMaterialPropertyTable->AddProperty("FASTCOMPONENT", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
        pMaterialPropertyTable->AddProperty("SLOWCOMPONENT", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the GXe scintillation spectrum data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetGXeIndexOfRefractionData(G4String* mGXeIndexOfRefractionData)
{
    pGXeIndexOfRefractionData = mGXeIndexOfRefractionData;

    ifsDataFile->open(pGXeIndexOfRefractionData->c_str(), ios::in);

    G4Material* pGXeMaterial = G4Material::GetMaterial("GXe");

    if((ifsDataFile->is_open()) && (pGXeMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pGXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("RINDEX");

        pMaterialPropertyTable->AddProperty("RINDEX", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the GXe index of refraction data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetGXeAbsorptionLengthData(G4String* mGXeAbsorptionLengthData)
{
    pGXeAbsorptionLengthData = mGXeAbsorptionLengthData;

    ifsDataFile->open(pGXeAbsorptionLengthData->c_str(), ios::in);

    G4Material* pGXeMaterial = G4Material::GetMaterial("GXe");

    if((ifsDataFile->is_open()) && (pGXeMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);
            dData *= m;

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pGXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("ABSLENGTH");

        pMaterialPropertyTable->AddProperty("ABSLENGTH", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the GXe absorption length data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetGXeRayleighScatteringLengthData(G4String* mGXeRayleighScatteringLengthData)
{
    pGXeRayleighScatteringLengthData = mGXeRayleighScatteringLengthData;

    ifsDataFile->open(pGXeRayleighScatteringLengthData->c_str(), ios::in);

    G4Material* pGXeMaterial = G4Material::GetMaterial("GXe");

    if((ifsDataFile->is_open()) && (pGXeMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);
            dData *= m;

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pGXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("RAYLEIGH");

        pMaterialPropertyTable->AddProperty("RAYLEIGH", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the GXe Rayleigh scattering length data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetGXeFanoFactor(G4double mGXeFanoFactor)
{
    dGXeFanoFactor = mGXeFanoFactor;

    G4Material* pGXeMaterial = G4Material::GetMaterial("GXe");

    if(pGXeMaterial)
    {
        pMaterialPropertyTable = pGXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("RESOLUTIONSCALE");

        pMaterialPropertyTable->AddConstProperty("RESOLUTIONSCALE", dGXeFanoFactor);
    }

    else
    {
        G4cout << "Could not find the GXe material." << G4endl;
        G4cout << "Using the previously loaded data file." << G4endl;
    }
}

void RELAXDetectorConstruction::SetGXeFastScintillationTimeConstant(G4double mGXeFastScintillationTimeConstant)
{
    dGXeFastScintillationTimeConstant = mGXeFastScintillationTimeConstant;

    G4Material* pGXeMaterial = G4Material::GetMaterial("GXe");

    if(pGXeMaterial)
    {
        pMaterialPropertyTable = pGXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("FASTTIMECONSTANT");

        pMaterialPropertyTable->AddConstProperty("FASTTIMECONSTANT", dGXeFastScintillationTimeConstant);
    }

    else
    {
        G4cout << "Could not find the GXe material." << G4endl;
    }
}

void RELAXDetectorConstruction::SetGXeSlowScintillationTimeConstant(G4double mGXeSlowScintillationTimeConstant)
{
    dGXeSlowScintillationTimeConstant = mGXeSlowScintillationTimeConstant;

    G4Material* pGXeMaterial = G4Material::GetMaterial("GXe");

    if(pGXeMaterial)
    {
        pMaterialPropertyTable = pGXeMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("SLOWTIMECONSTANT");

        pMaterialPropertyTable->AddConstProperty("SLOWTIMECONSTANT", dGXeSlowScintillationTimeConstant);
    }

    else
    {
        G4cout << "Could not find the GXe material." << G4endl;
    }
}

void RELAXDetectorConstruction::SetGXeDensityData(G4String* mGXeDensityData)
{
    pGXeDensityData = mGXeDensityData;

    ifsDataFile->open(pGXeDensityData->c_str(), ios::in);
    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetQuartzIndexOfRefraction(G4String* mQuartzIndexOfRefractionData)
{
    pQuartzIndexOfRefractionData = mQuartzIndexOfRefractionData;

    ifsDataFile->open(pQuartzIndexOfRefractionData->c_str(), ios::in);

    G4Material* pQuartzMaterial = G4Material::GetMaterial("Quartz");

    if((ifsDataFile->is_open()) && (pQuartzMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pQuartzMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("RINDEX");

        pMaterialPropertyTable->AddProperty("RINDEX", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the Quartz index of refraction data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetQuartzAbsorptionLength(G4String* mQuartzAbsorptionLengthData)
{
    pQuartzAbsorptionLengthData = mQuartzAbsorptionLengthData;

    ifsDataFile->open(pQuartzAbsorptionLengthData->c_str(), ios::in);

    G4Material* pQuartzMaterial = G4Material::GetMaterial("Quartz");

    if((ifsDataFile->is_open()) && (pQuartzMaterial))
    {
        getline((*ifsDataFile), (*pDummyString));

        while(true)
        {
            (*ifsDataFile) >> dWavelength >> dData;

            if(ifsDataFile->eof())
            {
                break;
            }

            dWavelength *= nm;
            dEnergy = (h_Planck * c_light / dWavelength);
            dData *= m;

            pEnergy->push_back(dEnergy);
            pData->push_back(dData);
        }

        pMaterialPropertyTable = pQuartzMaterial->GetMaterialPropertiesTable();

        pMaterialPropertyTable->RemoveProperty("ABSLENGTH");

        pMaterialPropertyTable->AddProperty("ABSLENGTH", &((*pEnergy)[0]), &((*pData)[0]), pEnergy->size());
    }

    else
    {
        G4cout << "Could not find the Quartz absorption length data." << G4endl;
        G4cout << "Using previously loaded data file." << G4endl;
    }

    pEnergy->clear();
    pData->clear();

    ifsDataFile->close();
    ifsDataFile->clear();
}

void RELAXDetectorConstruction::SetXePressure(G4double mXePressure)
{
    dXePressure = mXePressure;
}

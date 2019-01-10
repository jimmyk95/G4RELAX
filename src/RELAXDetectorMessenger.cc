///////////////////////////////
// Nickolas Upole            //
// University of Chicago     //
// Winter 2018               //
// RELAXDetectorMessenger.cc //
///////////////////////////////

#include "RELAXDetectorMessenger.hh"
#include "RELAXDetectorConstruction.hh"

RELAXDetectorMessenger::RELAXDetectorMessenger(RELAXDetectorConstruction* pRELAXDetectorConstruction) : pRELAXDetector(pRELAXDetectorConstruction)
{
    ////////////////////////////////
    // Set the Detector Directory //
    ////////////////////////////////
    pRELAXDir = new G4UIdirectory("/RELAX/");
    pRELAXDir->SetGuidance("Control of the RELAX Simulation.");

    pRELAXDetectorDir = new G4UIdirectory("/RELAX/detector/");
    pRELAXDetectorDir->SetGuidance("Control of the RELAX Detector.");

    ///////////////////////////////
    // Set the Detector Commands //
    ///////////////////////////////
    pPTFEIndexOfRefractionDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetPTFEIndexOfRefractionData", this);
    pPTFEIndexOfRefractionDataCmd->SetGuidance("Set the PTFE index of refraction data.");
    pPTFEIndexOfRefractionDataCmd->SetDefaultValue("./data/PTFE/IndexOfRefraction.txt");
    pPTFEIndexOfRefractionDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pPTFEAbsorptionLengthDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetPTFEAbsorptionLengthData", this);
    pPTFEAbsorptionLengthDataCmd->SetGuidance("Set the PTFE absorption length data.");
    pPTFEAbsorptionLengthDataCmd->SetDefaultValue("./data/PTFE/AbsorptionLength.txt");
    pPTFEAbsorptionLengthDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pPTFEReflectivityDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetPTFEReflectivityData", this);
    pPTFEIndexOfRefractionDataCmd->SetGuidance("Set the PTFE reflectivity data.");
    pPTFEIndexOfRefractionDataCmd->SetDefaultValue("./data/PTFE/Reflectivity.txt");
    pPTFEIndexOfRefractionDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pPTFESpecularLobeConstantDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetPTFESpecularLobeConstantData", this);
    pPTFESpecularLobeConstantDataCmd->SetGuidance("Set the PTFE specular lobe constant data.");
    pPTFESpecularLobeConstantDataCmd->SetDefaultValue("./data/PTFE/SpecularLobeConstant.txt");
    pPTFESpecularLobeConstantDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pPTFESpecularSpikeConstantDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetPTFESpecularSpikeConstantData", this);
    pPTFESpecularSpikeConstantDataCmd->SetGuidance("Set the PTFE specular spike constant data.");
    pPTFESpecularSpikeConstantDataCmd->SetDefaultValue("./data/PTFE/SpecularSpikeConstant.txt");
    pPTFESpecularSpikeConstantDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pPTFEBackscatterConstantDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetPTFEBackscatterConstantData", this);
    pPTFEBackscatterConstantDataCmd->SetGuidance("Set the PTFE backscatter constant data.");
    pPTFEBackscatterConstantDataCmd->SetDefaultValue("./data/PTFE/BackscatterConstant.txt");
    pPTFEBackscatterConstantDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pPTFEEfficiencyDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetPTFEEfficiencyData", this);
    pPTFEEfficiencyDataCmd->SetGuidance("Set the PTFE efficiency data.");
    pPTFEEfficiencyDataCmd->SetDefaultValue("./data/PTFE/Effiency.txt");
    pPTFEEfficiencyDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pLXeScintillationSpectrumDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetLXeScintillationSpectrumData", this);
    pLXeScintillationSpectrumDataCmd->SetGuidance("Set the LXe scintillation spectrum data.");
    pLXeScintillationSpectrumDataCmd->SetDefaultValue("./data/LXe/ScintillationSpectrum.txt");
    pLXeScintillationSpectrumDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pLXeIndexOfRefractionDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetLXeIndexOfRefractionData", this);
    pLXeIndexOfRefractionDataCmd->SetGuidance("Set the LXe index of refraction data.");
    pLXeIndexOfRefractionDataCmd->SetDefaultValue("./data/LXe/IndexOfRefraction.txt");
    pLXeIndexOfRefractionDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pLXeAbsorptionLengthDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetLXeAbsorptionLengthData", this);
    pLXeAbsorptionLengthDataCmd->SetGuidance("Set the LXe absorption length data.");
    pLXeAbsorptionLengthDataCmd->SetDefaultValue("./data/LXe/AbsorptionLength.txt");
    pLXeAbsorptionLengthDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pLXeRayleighScatteringLengthDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetLXeRayleighScatteringLengthData", this);
    pLXeRayleighScatteringLengthDataCmd->SetGuidance("Set the LXe Rayleigh scattering length data.");
    pLXeRayleighScatteringLengthDataCmd->SetDefaultValue("./data/LXe/RayleighScatteringLength.txt");
    pLXeRayleighScatteringLengthDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pLXeFanoFactorCmd = new G4UIcmdWithADouble("/RELAX/detector/SetLXeFanoFactor", this);
    pLXeFanoFactorCmd->SetGuidance("Set the LXe fano factor.");
    pLXeFanoFactorCmd->SetDefaultValue(0.033);
    pLXeFanoFactorCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pLXeFastScintillationTimeConstantCmd = new G4UIcmdWithADoubleAndUnit("/RELAX/detector/SetLXeFastScintillationTimeConstant", this);
    pLXeFastScintillationTimeConstantCmd->SetGuidance("Set the LXe fast scintillation time constant.");
    pLXeFastScintillationTimeConstantCmd->SetUnitCategory("Time");
    pLXeFastScintillationTimeConstantCmd->SetDefaultValue(2.2*ns);
    pLXeFastScintillationTimeConstantCmd->SetDefaultUnit("ns");
    pLXeFastScintillationTimeConstantCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pLXeSlowScintillationTimeConstantCmd = new G4UIcmdWithADoubleAndUnit("/RELAX/detector/SetLXeSlowScintillationTimeConstant", this);
    pLXeSlowScintillationTimeConstantCmd->SetGuidance("Set the LXe slow scintillation time constant.");
    pLXeSlowScintillationTimeConstantCmd->SetUnitCategory("Time");
    pLXeSlowScintillationTimeConstantCmd->SetDefaultValue(27.0*ns);
    pLXeSlowScintillationTimeConstantCmd->SetDefaultUnit("ns");
    pLXeSlowScintillationTimeConstantCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pLXeDensityDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetLXeDensityData", this);
    pLXeDensityDataCmd->SetGuidance("Set the LXe density data.");
    pLXeDensityDataCmd->SetDefaultValue("./data/LXe/Density.txt");
    pLXeDensityDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pGXeScintillationSpectrumDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetGXeScintillationSpectrumData", this);
    pGXeScintillationSpectrumDataCmd->SetGuidance("Set the GXe scintillation spectrum data.");
    pGXeScintillationSpectrumDataCmd->SetDefaultValue("./data/LXe/ScintillationSpectrum.txt");
    pGXeScintillationSpectrumDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pGXeIndexOfRefractionDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetGXeIndexOfRefractionData", this);
    pGXeIndexOfRefractionDataCmd->SetGuidance("Set the GXe index of refraction data.");
    pGXeIndexOfRefractionDataCmd->SetDefaultValue("./data/GXe/IndexOfRefraction.txt");
    pGXeIndexOfRefractionDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pGXeAbsorptionLengthDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetGXeAbsorptionLengthData", this);
    pGXeAbsorptionLengthDataCmd->SetGuidance("Set the GXe absorption length data.");
    pGXeAbsorptionLengthDataCmd->SetDefaultValue("./data/GXe/AbsorptionLength.txt");
    pGXeAbsorptionLengthDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pGXeRayleighScatteringLengthDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetGXeRayleighScatteringLengthData", this);
    pGXeRayleighScatteringLengthDataCmd->SetGuidance("Set the GXe Rayleigh scattering length data.");
    pGXeRayleighScatteringLengthDataCmd->SetDefaultValue("./data/GXe/RayleighScatteringLength.txt");
    pGXeRayleighScatteringLengthDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pGXeFanoFactorCmd = new G4UIcmdWithADouble("/RELAX/detector/SetGXeFanoFactor", this);
    pGXeFanoFactorCmd->SetGuidance("Set the GXe fano factor.");
    pGXeFanoFactorCmd->SetDefaultValue(0.033);
    pGXeFanoFactorCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pGXeFastScintillationTimeConstantCmd = new G4UIcmdWithADoubleAndUnit("/RELAX/detector/SetGXeFastScintillationTimeConstant", this);
    pGXeFastScintillationTimeConstantCmd->SetGuidance("Set the GXe fast scintillation time constant.");
    pGXeFastScintillationTimeConstantCmd->SetUnitCategory("Time");
    pGXeFastScintillationTimeConstantCmd->SetDefaultValue(2.2*ns);
    pGXeFastScintillationTimeConstantCmd->SetDefaultUnit("ns");
    pGXeFastScintillationTimeConstantCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pGXeSlowScintillationTimeConstantCmd = new G4UIcmdWithADoubleAndUnit("/RELAX/detector/SetGXeSlowScintillationTimeConstant", this);
    pGXeSlowScintillationTimeConstantCmd->SetGuidance("Set the GXe slow scintillation time constant.");
    pGXeSlowScintillationTimeConstantCmd->SetUnitCategory("Time");
    pGXeSlowScintillationTimeConstantCmd->SetDefaultValue(27.0*ns);
    pGXeSlowScintillationTimeConstantCmd->SetDefaultUnit("ns");
    pGXeSlowScintillationTimeConstantCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pGXeDensityDataCmd = new G4UIcmdWithAString("/RELAX/detector/SetGXeDensityData", this);
    pGXeDensityDataCmd->SetGuidance("Set the GXe density data.");
    pGXeDensityDataCmd->SetDefaultValue("./data/GXe/Density.txt");
    pGXeDensityDataCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    pXePressureCmd = new G4UIcmdWithADouble("/RELAX/detector/SetXePressure", this);
    pXePressureCmd->SetGuidance("Set the pressure of the liquid and gaseous xenon in psi.");
    pXePressureCmd->SetDefaultValue(17.35);
    pXePressureCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

RELAXDetectorMessenger::~RELAXDetectorMessenger()
{
    ///////////////////////////////////////
    // Delete the Commands and Directory //
    ///////////////////////////////////////
    delete pPTFEIndexOfRefractionDataCmd;
    delete pPTFEAbsorptionLengthDataCmd;
    delete pPTFEReflectivityDataCmd;
    delete pPTFESpecularLobeConstantDataCmd;
    delete pPTFESpecularSpikeConstantDataCmd;
    delete pPTFEBackscatterConstantDataCmd;
    delete pPTFEEfficiencyDataCmd;

    delete pLXeScintillationSpectrumDataCmd;
    delete pLXeIndexOfRefractionDataCmd;
    delete pLXeAbsorptionLengthDataCmd;
    delete pLXeRayleighScatteringLengthDataCmd;
    delete pLXeFanoFactorCmd;
    delete pLXeFastScintillationTimeConstantCmd;
    delete pLXeSlowScintillationTimeConstantCmd;
    delete pLXeDensityDataCmd;

    delete pGXeScintillationSpectrumDataCmd;
    delete pGXeIndexOfRefractionDataCmd;
    delete pGXeAbsorptionLengthDataCmd;
    delete pGXeRayleighScatteringLengthDataCmd;
    delete pGXeFanoFactorCmd;
    delete pGXeFastScintillationTimeConstantCmd;
    delete pGXeSlowScintillationTimeConstantCmd;
    delete pGXeDensityDataCmd;

    delete pXePressureCmd;

    delete pRELAXDetectorDir;
}

void RELAXDetectorMessenger::SetNewValue(G4UIcommand* pG4UICommand, G4String sNewValue)
{
    ////////////////////////////////////////////
    // Update Value for Detector Construction //
    ////////////////////////////////////////////
    if(pG4UICommand == pPTFEIndexOfRefractionDataCmd)
    {
        pRELAXDetector->SetPTFEIndexOfRefraction(&sNewValue);
    }

    else if(pG4UICommand == pPTFEAbsorptionLengthDataCmd)
    {
        pRELAXDetector->SetPTFEAbsorptionLengthData(&sNewValue);
    }

    else if(pG4UICommand == pPTFEReflectivityDataCmd)
    {
        pRELAXDetector->SetPTFEReflectivity(&sNewValue);
    }

    else if(pG4UICommand == pPTFESpecularLobeConstantDataCmd)
    {
        pRELAXDetector->SetPTFESpecularLobeConstant(&sNewValue);
    }

    else if(pG4UICommand == pPTFESpecularSpikeConstantDataCmd)
    {
        pRELAXDetector->SetPTFESpecularSpikeConstant(&sNewValue);
    }

    else if(pG4UICommand == pPTFEBackscatterConstantDataCmd)
    {
        pRELAXDetector->SetPTFEBackscatterConstant(&sNewValue);
    }

    else if(pG4UICommand == pPTFEEfficiencyDataCmd)
    {
        pRELAXDetector->SetPTFEEfficiency(&sNewValue);
    }

    else if(pG4UICommand == pLXeScintillationSpectrumDataCmd)
    {
        pRELAXDetector->SetLXeScintillationSpectrumData(&sNewValue);
    }

    else if(pG4UICommand == pLXeIndexOfRefractionDataCmd)
    {
        pRELAXDetector->SetLXeIndexOfRefractionData(&sNewValue);
    }

    else if(pG4UICommand == pLXeAbsorptionLengthDataCmd)
    {
        pRELAXDetector->SetLXeAbsorptionLengthData(&sNewValue);
    }

    else if(pG4UICommand == pLXeRayleighScatteringLengthDataCmd)
    {
        pRELAXDetector->SetLXeRayleighScatteringLengthData(&sNewValue);
    }

    else if(pG4UICommand == pLXeFanoFactorCmd)
    {
        pRELAXDetector->SetLXeFanoFactor(pLXeFanoFactorCmd->GetNewDoubleValue(sNewValue));
    }

    else if(pG4UICommand == pLXeFastScintillationTimeConstantCmd)
    {
        pRELAXDetector->SetLXeFastScintillationTimeConstant(pLXeFastScintillationTimeConstantCmd->GetNewDoubleValue(sNewValue));
    }

    else if(pG4UICommand == pLXeSlowScintillationTimeConstantCmd)
    {
        pRELAXDetector->SetLXeSlowScintillationTimeConstant(pLXeSlowScintillationTimeConstantCmd->GetNewDoubleValue(sNewValue));
    }

    else if(pG4UICommand == pLXeDensityDataCmd)
    {
        pRELAXDetector->SetLXeDensityData(&sNewValue);
    }

    else if(pG4UICommand == pGXeScintillationSpectrumDataCmd)
    {
        pRELAXDetector->SetGXeScintillationSpectrumData(&sNewValue);
    }

    else if(pG4UICommand == pGXeIndexOfRefractionDataCmd)
    {
        pRELAXDetector->SetGXeIndexOfRefractionData(&sNewValue);
    }

    else if(pG4UICommand == pGXeAbsorptionLengthDataCmd)
    {
        pRELAXDetector->SetGXeAbsorptionLengthData(&sNewValue);
    }

    else if(pG4UICommand == pGXeRayleighScatteringLengthDataCmd)
    {
        pRELAXDetector->SetGXeRayleighScatteringLengthData(&sNewValue);
    }

    else if(pG4UICommand == pGXeFanoFactorCmd)
    {
        pRELAXDetector->SetGXeFanoFactor(pGXeFanoFactorCmd->GetNewDoubleValue(sNewValue));
    }

    else if(pG4UICommand == pGXeFastScintillationTimeConstantCmd)
    {
        pRELAXDetector->SetGXeFastScintillationTimeConstant(pGXeFastScintillationTimeConstantCmd->GetNewDoubleValue(sNewValue));
    }

    else if(pG4UICommand == pGXeSlowScintillationTimeConstantCmd)
    {
        pRELAXDetector->SetGXeSlowScintillationTimeConstant(pGXeSlowScintillationTimeConstantCmd->GetNewDoubleValue(sNewValue));
    }

    else if(pG4UICommand == pGXeDensityDataCmd)
    {
        pRELAXDetector->SetGXeDensityData(&sNewValue);
    }

    else if(pG4UICommand == pXePressureCmd)
    {
        pRELAXDetector->SetXePressure(pXePressureCmd->GetNewDoubleValue(sNewValue));
    }
}

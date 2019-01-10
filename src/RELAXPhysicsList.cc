///////////////////////////
// Nickolas Upole        //
// University of Chicago //
// Winter 2018           //
// RELAXPhysicsList.cc   //
///////////////////////////

#include "RELAXPhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

RELAXPhysicsList::RELAXPhysicsList() : G4VUserPhysicsList()
{
    pRELAXPhysicsMessenger = new RELAXPhysicsMessenger(this);

    bScintillation = false;
    bCerenkov = false;
}

RELAXPhysicsList::~RELAXPhysicsList()
{

}

void RELAXPhysicsList::ConstructParticle()
{
    ConstructBosons();
    ConstructLeptons();
    ConstructHadrons();
    ConstructShortLived();
}

#include "G4Geantino.hh"

#include "G4Gamma.hh"
#include "G4OpticalPhoton.hh"

void RELAXPhysicsList::ConstructBosons()
{
    G4Geantino::Geantino();

    G4Gamma::Gamma();
    G4OpticalPhoton::OpticalPhoton();
}

#include "G4Electron.hh"
#include "G4Positron.hh"

#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"

#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"

#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoMu.hh"

void RELAXPhysicsList::ConstructLeptons()
{
    G4Electron::Electron();
    G4Positron::Positron();

    G4NeutrinoE::NeutrinoE();
    G4AntiNeutrinoE::AntiNeutrinoE();

    G4MuonPlus::MuonPlusDefinition();
    G4MuonMinus::MuonMinusDefinition();

    G4NeutrinoMu::NeutrinoMu();
    G4AntiNeutrinoMu::AntiNeutrinoMu();
}

#include "G4Neutron.hh"
#include "G4Proton.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4GenericIon.hh"

void RELAXPhysicsList::ConstructHadrons()
{
    G4Neutron::Neutron();
    G4Proton::Proton();
    G4MesonConstructor::ConstructParticle();
    G4BaryonConstructor::ConstructParticle();
    G4GenericIon::GenericIon();
}

void RELAXPhysicsList::ConstructShortLived()
{

}

void RELAXPhysicsList::ConstructProcess()
{
    ConstructEMPhysics();
    ConstructHadronPhysics();
    ConstructOpticalPhotonPhysics();
    ConstructDecayPhysics();
    AddTransportation();
}

#include "G4VPhysicsConstructor.hh"
#include "G4EmLivermorePhysics.hh"

void RELAXPhysicsList::ConstructEMPhysics()
{
    G4VPhysicsConstructor* pEMPhysicsList;
    pEMPhysicsList = new G4EmLivermorePhysics();
    pEMPhysicsList->ConstructProcess();
}

#include "G4HadronElasticProcess.hh"
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4NeutronHPInelasticData.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4NeutronHPCapture.hh"
#include "G4NeutronHPCaptureData.hh"

void RELAXPhysicsList::ConstructHadronPhysics()
{
    // Reset the particle iterator
    theParticleIterator->reset();

    // Loop over all particles
    while((*theParticleIterator)())
    {
        // Get loop variables
        G4ParticleDefinition* pParticleDefinition = theParticleIterator->value();
        G4String sParticleName = pParticleDefinition->GetParticleName();
        G4ProcessManager* pProcessManager = pParticleDefinition->GetProcessManager();

        if(sParticleName == "pi+")
        {

        }

        else if(sParticleName == "neutron")
        {
            // Elastic Scattering Processes
            G4HadronElasticProcess* pNeutronElasticProcess = new G4HadronElasticProcess();
            G4NeutronHPElastic* pNeutronHPElasticModel = new G4NeutronHPElastic();
            G4NeutronHPElasticData* pNeutronHPElasticData = new G4NeutronHPElasticData();

            pNeutronElasticProcess->RegisterMe(pNeutronHPElasticModel);
            pNeutronElasticProcess->AddDataSet(pNeutronHPElasticData);
            pProcessManager->AddDiscreteProcess(pNeutronElasticProcess);

            // Inelastic Scattering Processes
            G4NeutronInelasticProcess* pNeutronInelasticProcess = new G4NeutronInelasticProcess();
            G4NeutronHPInelastic* pNeutronHPInelasticModel = new G4NeutronHPInelastic();
            G4NeutronHPInelasticData* pNeutronHPInelasticData = new G4NeutronHPInelasticData();

            pNeutronInelasticProcess->RegisterMe(pNeutronHPInelasticModel);
            pNeutronInelasticProcess->AddDataSet(pNeutronHPInelasticData);
            pProcessManager->AddDiscreteProcess(pNeutronInelasticProcess);

            // Capture Processes
            G4HadronCaptureProcess* pNeutronCaptureProcess = new G4HadronCaptureProcess();
            G4NeutronHPCapture* pNeutronHPCaptureModel = new G4NeutronHPCapture();
            G4NeutronHPCaptureData* pNeutronHPCaptureData = new G4NeutronHPCaptureData();

            pNeutronCaptureProcess->RegisterMe(pNeutronHPCaptureModel);
            pNeutronCaptureProcess->AddDataSet(pNeutronHPCaptureData);
            pProcessManager->AddDiscreteProcess(pNeutronCaptureProcess);
        }
    }
}

#include "G4Scintillation.hh"
#include "G4Cerenkov.hh"

#include "G4OpBoundaryProcess.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"

void RELAXPhysicsList::ConstructOpticalPhotonPhysics()
{
    G4Scintillation* pScintillation = new G4Scintillation();
    pScintillation->SetTrackSecondariesFirst(true);

    G4Cerenkov* pCerenkov = new G4Cerenkov();

    G4OpBoundaryProcess* pOpBoundaryProcess = new G4OpBoundaryProcess();
    G4OpAbsorption* pOpAbsorption = new G4OpAbsorption();
    G4OpRayleigh* pOpRayleigh = new G4OpRayleigh();

    theParticleIterator->reset();

    while((*theParticleIterator)())
    {
        // Get loop variables
        G4ParticleDefinition* pParticleDefinition = theParticleIterator->value();
        G4String sParticleName = pParticleDefinition->GetParticleName();
        G4ProcessManager* pProcessManager = pParticleDefinition->GetProcessManager();

        if(pScintillation->IsApplicable(*pParticleDefinition) && bScintillation)
        {
            pProcessManager->AddProcess(pScintillation);
            pProcessManager->SetProcessOrderingToLast(pScintillation, idxAtRest);
            pProcessManager->SetProcessOrderingToLast(pScintillation, idxPostStep);
        }

        if(pCerenkov->IsApplicable(*pParticleDefinition) && bCerenkov)
        {
            pProcessManager->AddDiscreteProcess(pCerenkov);
        }

        if(sParticleName == "opticalphoton")
        {
            pProcessManager->AddDiscreteProcess(pOpBoundaryProcess);
            pProcessManager->AddDiscreteProcess(pOpAbsorption);
            pProcessManager->AddDiscreteProcess(pOpRayleigh);
        }
    }
}

#include "G4Decay.hh"
#include "G4RadioactiveDecay.hh"

void RELAXPhysicsList::ConstructDecayPhysics()
{
    G4Decay* pDecay = new G4Decay();
    G4RadioactiveDecay* pRadioactiveDecay = new G4RadioactiveDecay();

    theParticleIterator->reset();

    while((*theParticleIterator)())
    {
        // Get loop variables
        G4ParticleDefinition* pParticleDefinition = theParticleIterator->value();
        G4String sParticleName = pParticleDefinition->GetParticleName();
        G4ProcessManager* pProcessManager = pParticleDefinition->GetProcessManager();

        if(pDecay->IsApplicable(*pParticleDefinition))
        {
            pProcessManager->AddProcess(pDecay);
        }

        if(pRadioactiveDecay->IsApplicable(*pParticleDefinition))
        {
            pProcessManager->AddDiscreteProcess(pRadioactiveDecay);
        }
    }
}

void RELAXPhysicsList::AddTransportation()
{
    G4VUserPhysicsList::AddTransportation();
}

void RELAXPhysicsList::SetCuts()
{
    // G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(0.1*keV, 1*GeV);

    // SetCutValue(5.0*nm, "gamma");
    // SetCutValue(5.0*nm, "proton");
    // SetCutValue(5.0*nm, "nucleus");
    // SetCutValue(0.01*um, "electron");
    // SetCutValue(0.01*um, "Neutron");
}

void RELAXPhysicsList::SetScintillation(G4bool mScintillation)
{
    bScintillation = mScintillation;
}

void RELAXPhysicsList::SetCerenkov(G4bool mCerenkov)
{
    bCerenkov = mCerenkov;
}

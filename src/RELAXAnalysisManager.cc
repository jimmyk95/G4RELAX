/////////////////////////////
// Nickolas Upole          //
// University of Chicago   //
// Winter 2018             //
// RELAXAnalysisManager.cc //
/////////////////////////////

#include "RELAXAnalysisManager.hh"
#include <G4SDManager.hh>
#include "Xenon1tPmtHit.hh"

RELAXAnalysisManager::RELAXAnalysisManager()
{
    pRELAXAnalysisMessenger = new RELAXAnalysisMessenger(this);
    
    pFilenameReference = new G4String("./Results/events.root");

    pMapParticleType = new map<int, G4String>;
    pRELAXEventData = new RELAXEventData();
    
    dActiveVolumeX = 0.0000;
    dActiveVolumeY = 0.0000;
    dActiveVolumeZ = -92.67471*mm;
    
    dFiducialVolumeRadius = 25.0000*mm;
    dFiducialVolumeHeight = 20.0000*mm;
    m_iPmtHitsCollectionID = -1;
}

RELAXAnalysisManager::~RELAXAnalysisManager()
{
    delete pRELAXAnalysisMessenger;
    
    delete pFilenameReference;
    
    delete pMapParticleType;
    delete pRELAXEventData;
}

void RELAXAnalysisManager::BeginOfRunAction(const G4Run* pRun)
{
    pFile = new TFile(pFilenameReference->c_str(), "RECREATE", "Results of RELAX Simulation");
    pTree1 = new TTree("t1", "Tree containing raw data from the RELAX Simulation");
    pTree2 = new TTree("t2", "Tree containing processed data from the RELAX Simulation");
    pTree3 = new TTree("t3", "Tree containing nuclear recoil data from the RELAX Simulation");
    pTree4 = new TTree("t4", "Tree containing electronic recoil data from the RELAX Simulation");
    pTree5 = new TTree("t5", "Tree containing hit data from PMTs");
    
    gROOT->ProcessLine("#include <vector>");
    
    pTree1->Branch("eventid", &(pRELAXEventData->iEventID), "eventid/I");
    pTree1->Branch("trackid", "vector<int>", &pRELAXEventData->pTrackID);
    pTree1->Branch("parentid", "vector<int>", &pRELAXEventData->pParentID);
    pTree1->Branch("particletype", "vector<string>", &pRELAXEventData->pParticleType);
    pTree1->Branch("parenttype", "vector<string>", &pRELAXEventData->pParentType);
    pTree1->Branch("creatorprocess", "vector<string>", &pRELAXEventData->pCreatorProcess);
    pTree1->Branch("depositprocess", "vector<string>", &pRELAXEventData->pDepositingProcess);
    pTree1->Branch("volume", "vector<string>", &pRELAXEventData->pVolume);
    pTree1->Branch("initx", "vector<double>", &pRELAXEventData->pInitX);
    pTree1->Branch("inity", "vector<double>", &pRELAXEventData->pInitY);
    pTree1->Branch("initz", "vector<double>", &pRELAXEventData->pInitZ);
    pTree1->Branch("finalx", "vector<double>", &pRELAXEventData->pFinalX);
    pTree1->Branch("finaly", "vector<double>", &pRELAXEventData->pFinalY);
    pTree1->Branch("finalz", "vector<double>", &pRELAXEventData->pFinalZ);
    pTree1->Branch("initkinenergy", "vector<double>", &pRELAXEventData->pInitKinEnergy);
    pTree1->Branch("finalkinenergy", "vector<double>", &pRELAXEventData->pFinalKinEnergy);
    pTree1->Branch("energydeposited", "vector<double>", &pRELAXEventData->pEnergyDeposited);
    pTree1->Branch("inittime", "vector<double>", &pRELAXEventData->pInitTime);
    pTree1->Branch("finaltime", "vector<double>", &pRELAXEventData->pFinalTime);
    pTree1->Branch("photonsC", &(pRELAXEventData->photonsC), "photonsC/I");
    
    pTree2->Branch("eventid", &(pRELAXEventData->iEventID), "eventid/I");
    pTree2->Branch("firstinteractiontimelxe", &(pRELAXEventData->dFirstInteractionTimeLXe), "firstinteractiontimelxe/D");
    pTree2->Branch("totalenergydeposited", &(pRELAXEventData->dTotalEnergyDeposited), "totalenergydeposited/D");
    pTree2->Branch("energydepositedregionx", &(pRELAXEventData->dEnergyDepositedRegionX), "energydepositedregionx/D");
    pTree2->Branch("energydepositedactivevolume", &(pRELAXEventData->dEnergyDepositedActiveVolume), "energydepositedactivevolume/D");
    pTree2->Branch("energydepositedfiducialvolume", &(pRELAXEventData->dEnergyDepositedFiducialVolume), "energydepositedfiducialvolume/D");
    pTree2->Branch("energydepositedgatelxe", &(pRELAXEventData->dEnergyDepositedGateLXe), "energydepositedgatelxe/D");
    pTree2->Branch("energydepositedgategxe", &(pRELAXEventData->dEnergyDepositedGateGXe), "energydepositedgategxe/D");
    pTree2->Branch("energydepositedregiony", &(pRELAXEventData->dEnergyDepositedRegionY), "energydepositedregiony/D");
    pTree2->Branch("totalinteractionsregionx", &(pRELAXEventData->iTotalInteractionsRegionX), "totalinteractionsregionx/I");
    pTree2->Branch("totalinteractionsactivevolume", &(pRELAXEventData->iTotalInteractionsActiveVolume), "totalinteractionsactivevolume/I");
    pTree2->Branch("totalinteractionsfiducialvolume", &(pRELAXEventData->iTotalInteractionsFiducialVolume), "totalinteractionsfiducialvolume/I");
    pTree2->Branch("totalinteractionsgatelxe", &(pRELAXEventData->iTotalInteractionsGateLXe), "totalinteractionsgatelxe/I");
    pTree2->Branch("totalinteractionsgategxe", &(pRELAXEventData->iTotalInteractionsGateGXe), "totalinteractionsgategxe/I");
    pTree2->Branch("totalinteractionsregiony", &(pRELAXEventData->iTotalInteractionsRegionY), "totalinteractionsregiony/I");
    pTree2->Branch("interactionxej301", "vector<double>", &(pRELAXEventData->pInteractionXEJ301));
    pTree2->Branch("interactionyej301", "vector<double>", &(pRELAXEventData->pInteractionYEJ301));
    pTree2->Branch("interactionzej301", "vector<double>", &(pRELAXEventData->pInteractionZEJ301));
    pTree2->Branch("interactiontimeej301", "vector<double>", &(pRELAXEventData->pInteractionTimeEJ301));
    pTree2->Branch("totalenergydepositedej301", &(pRELAXEventData->dTotalEnergyDepositedEJ301), "totalenergydepositedej301/D");
    pTree2->Branch("totalpeej301", &(pRELAXEventData->dTotalPEEJ301), "totalpeej301/D");
    
    pTree3->Branch("eventid", &(pRELAXEventData->iEventID), "eventid/I");
    pTree3->Branch("firstneutroninteractionprocess", "string", &(pRELAXEventData->sFirstNeutronInteractionProcess));
    pTree3->Branch("firstneutroninteractionvolume", "string", &(pRELAXEventData->sFirstNeutronInteractionVolume));
    pTree3->Branch("firstneutroninteractionx", &(pRELAXEventData->dFirstNeutronInteractionX), "firstneutroninteractionx/D");
    pTree3->Branch("firstneutroninteractiony", &(pRELAXEventData->dFirstNeutronInteractionY), "firstneutroninteractiony/D");
    pTree3->Branch("firstneutroninteractionz", &(pRELAXEventData->dFirstNeutronInteractionZ), "firstneutroninteractionz/D");
    pTree3->Branch("firstneutroninteractiontime", &(pRELAXEventData->dFirstNeutronInteractionTime), "firstneutroninteractiontime/D");
    pTree3->Branch("secondneutroninteractionprocess", "string", &(pRELAXEventData->sSecondNeutronInteractionProcess));
    pTree3->Branch("secondneutroninteractionvolume", "string", &(pRELAXEventData->sSecondNeutronInteractionVolume));
    pTree3->Branch("secondneutroninteractionx", &(pRELAXEventData->dSecondNeutronInteractionX), "secondneutroninteractionx/D");
    pTree3->Branch("secondneutroninteractiony", &(pRELAXEventData->dSecondNeutronInteractionY), "secondneutroninteractiony/D");
    pTree3->Branch("secondneutroninteractionz", &(pRELAXEventData->dSecondNeutronInteractionZ), "secondneutroninteractionz/D");
    pTree3->Branch("secondneutroninteractiontime", &(pRELAXEventData->dSecondNeutronInteractionTime), "secondneutroninteractiontime/D");
    pTree3->Branch("elasticscattersptfe", &(pRELAXEventData->iElasticScattersPTFE), "elasticscattersptfe/I");
    pTree3->Branch("elasticscatterssurroundinglxe", &(pRELAXEventData->iElasticScattersSurroundingLXe), "elasticscatterssurroundinglxe/I");
    pTree3->Branch("elasticscattersregionx", &(pRELAXEventData->iElasticScattersRegionX), "elasticscattersregionx/I");
    pTree3->Branch("elasticscattersactivevolume", &(pRELAXEventData->iElasticScattersActiveVolume), "elasticscattersactivevolume/I");
    pTree3->Branch("elasticscattersfiducialvolume", &(pRELAXEventData->iElasticScattersFiducialVolume), "elasticscattersfiducialvolume/I");
    pTree3->Branch("elasticscattersgatelxe", &(pRELAXEventData->iElasticScattersGateLXe), "elasticscattersgatelxe/I");
    pTree3->Branch("elasticscattersgategxe", &(pRELAXEventData->iElasticScattersGateGXe), "elasticscattersgategxe/I");
    pTree3->Branch("elasticscattersregiony", &(pRELAXEventData->iElasticScattersRegionY), "elasticscattersregiony/I");
    pTree3->Branch("elasticscatterssurroundinggxe", &(pRELAXEventData->iElasticScattersSurroundingGXe), "elasticscatterssurroundinggxe/I");
    pTree3->Branch("inelasticscattersptfe", &(pRELAXEventData->iInelasticScattersPTFE), "inelasticscattersptfe/I");
    pTree3->Branch("inelasticscatterssurroundinglxe", &(pRELAXEventData->iInelasticScattersSurroundingLXe), "inelasticscatterssurroundinglxe/I");
    pTree3->Branch("inelasticscattersregionx", &(pRELAXEventData->iInelasticScattersRegionX), "inelasticscattersregionx/I");
    pTree3->Branch("inelasticscattersactivevolume", &(pRELAXEventData->iInelasticScattersActiveVolume), "inelasticscattersactivevolume/I");
    pTree3->Branch("inelasticscattersfiducialvolume", &(pRELAXEventData->iInelasticScattersFiducialVolume), "inelasticscattersfiducialvolume/I");
    pTree3->Branch("inelasticscattersgatelxe", &(pRELAXEventData->iInelasticScattersGateLXe), "inelasticscattersgatelxe/I");
    pTree3->Branch("inelasticscattersgategxe", &(pRELAXEventData->iInelasticScattersGateGXe), "inelasticscattersgategxe/I");
    pTree3->Branch("inelasticscattersregiony", &(pRELAXEventData->iInelasticScattersRegionY), "inelasticscattersregiony/I");
    pTree3->Branch("inelasticscatterssurroundinggxe", &(pRELAXEventData->iInelasticScattersSurroundingGXe), "inelasticscatterssurroundinggxe/I");
    pTree3->Branch("neutroncaptureptfe", &(pRELAXEventData->iNeutronCapturePTFE), "neutroncaptureptfe/I");
    pTree3->Branch("neutroncapturesurroundinglxe", &(pRELAXEventData->iNeutronCaptureSurroundingLXe), "neutroncapturesurroundinglxe/I");
    pTree3->Branch("neutroncaptureregionx", &(pRELAXEventData->iNeutronCaptureRegionX), "neutroncaptureregionx/I");
    pTree3->Branch("neutroncaptureactivevolume", &(pRELAXEventData->iNeutronCaptureActiveVolume), "neutroncaptureactivevolume/I");
    pTree3->Branch("neutroncapturefiducialvolume", &(pRELAXEventData->iNeutronCaptureFiducialVolume), "neutroncapturefiducialvolume/I");
    pTree3->Branch("neutroncapturegatelxe", &(pRELAXEventData->iNeutronCaptureGateLXe), "neutroncapturegatelxe/I");
    pTree3->Branch("neutroncapturegategxe", &(pRELAXEventData->iNeutronCaptureGateGXe), "neutroncapturegategxe/I");
    pTree3->Branch("neutroncaptureregiony", &(pRELAXEventData->iNeutronCaptureRegionY), "neutroncaptureregiony/I");
    pTree3->Branch("neutroncapturesurroundinggxe", &(pRELAXEventData->iNeutronCaptureSurroundingGXe), "neutroncapturesurroundinggxe/I");
    
    pTree4->Branch("eventid", &(pRELAXEventData->iEventID), "eventid/I");
    pTree4->Branch("peptfe", &(pRELAXEventData->iPEPTFE), "peptfe/I");
    pTree4->Branch("pesurroundinglxe", &(pRELAXEventData->iPESurroundingLXe), "pesurroundinglxe/I");
    pTree4->Branch("peregionx", &(pRELAXEventData->iPERegionX), "peregionx/I");
    pTree4->Branch("peactivevolume", &(pRELAXEventData->iPEActiveVolume), "peactivevolume/I");
    pTree4->Branch("pefiducialvolume", &(pRELAXEventData->iPEFiducialVolume), "pefiducialvolume/I");
    pTree4->Branch("pegatelxe", &(pRELAXEventData->iPEGateLXe), "pegatelxe/I");
    pTree4->Branch("pegategxe", &(pRELAXEventData->iPEGateGXe), "pegategxe/I");
    pTree4->Branch("peregiony", &(pRELAXEventData->iPERegionY), "peregiony/I");
    pTree4->Branch("pesurroundinggxe", &(pRELAXEventData->iPESurroundingGXe), "pesurroundinggxe/I");
    pTree4->Branch("comptonscattersptfe", &(pRELAXEventData->iComptonScattersPTFE), "comptonscattersptfe/I");
    pTree4->Branch("comptonscatterssurroundinglxe", &(pRELAXEventData->iComptonScattersSurroundingLXe), "comptonscatterssurroundinglxe/I");
    pTree4->Branch("comptonscattersregionx", &(pRELAXEventData->iComptonScattersRegionX), "comptonscattersregionx/I");
    pTree4->Branch("comptonscattersactivevolume", &(pRELAXEventData->iComptonScattersActiveVolume), "comptonscattersactivevolume/I");
    pTree4->Branch("comptonscattersfiducialvolume", &(pRELAXEventData->iComptonScattersFiducialVolume), "comptonscattersfiducialvolume/I");
    pTree4->Branch("comptonscattersgatelxe", &(pRELAXEventData->iComptonScattersGateLXe), "comptonscattersgatelxe/I");
    pTree4->Branch("comptonscattersgategxe", &(pRELAXEventData->iComptonScattersGateGXe), "comptonscattersgategxe/I");
    pTree4->Branch("comptonscattersregiony", &(pRELAXEventData->iComptonScattersRegionY), "comptonscattersregiony/I");
    pTree4->Branch("comptonscatterssurroundinggxe", &(pRELAXEventData->iComptonScattersSurroundingGXe), "comptonscatterssurroundinggxe/I");
    pTree5->Branch("photonsC", &(pRELAXEventData->photonsC), "photonsC/I");
    //G4int iNbPmtHits = 0;
    G4int photonsC = 0;
}

void RELAXAnalysisManager::BeginOfEventAction(const G4Event* pEvent)
{
    pRELAXEventData->iEventID = pEvent->GetEventID();
    if (m_iPmtHitsCollectionID == -1)
      {
      G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
      m_iPmtHitsCollectionID = pSDManager->GetCollectionID("PmtHitsCollection");
      G4cout << "!!!!!!!!!1m_iPmtHitsCollectionID = " << m_iPmtHitsCollectionID << G4endl;
}
}
void RELAXAnalysisManager::SteppingAction(const G4Step* pStep)
{
    pTrack = pStep->GetTrack();
    
    pRELAXEventData->pTrackID->push_back(pTrack->GetTrackID());
    pRELAXEventData->pParentID->push_back(pTrack->GetParentID());
    pRELAXEventData->pParticleType->push_back(sParticleType = pTrack->GetDefinition()->GetParticleName());
    
    if(pTrack->GetParentID())
    {
        pRELAXEventData->pParentType->push_back((*pMapParticleType)[pTrack->GetParentID()]);
    }
    
    else
    {
        pRELAXEventData->pParentType->push_back(G4String("none"));
    }
    
    if(pTrack->GetCreatorProcess())
    {
        pRELAXEventData->pCreatorProcess->push_back(pTrack->GetCreatorProcess()->GetProcessName());
    }
    
    else
    {
        pRELAXEventData->pCreatorProcess->push_back(G4String("none"));
    }
    
    pRELAXEventData->pDepositingProcess->push_back(sDepositingProcess = pStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
    pRELAXEventData->pVolume->push_back(sVolume = pStep->GetPreStepPoint()->GetPhysicalVolume()->GetName());
    pRELAXEventData->pInitX->push_back(pStep->GetPreStepPoint()->GetPosition().x()/mm);
    pRELAXEventData->pInitY->push_back(pStep->GetPreStepPoint()->GetPosition().y()/mm);
    pRELAXEventData->pInitZ->push_back(pStep->GetPreStepPoint()->GetPosition().z()/mm);
    pRELAXEventData->pFinalX->push_back(dInteractionX = pStep->GetPostStepPoint()->GetPosition().x()/mm);
    pRELAXEventData->pFinalY->push_back(dInteractionY = pStep->GetPostStepPoint()->GetPosition().y()/mm);
    pRELAXEventData->pFinalZ->push_back(dInteractionZ = pStep->GetPostStepPoint()->GetPosition().z()/mm);
    pRELAXEventData->pInitKinEnergy->push_back(pStep->GetPreStepPoint()->GetKineticEnergy()/keV);
    pRELAXEventData->pFinalKinEnergy->push_back(pStep->GetPostStepPoint()->GetKineticEnergy()/keV);
    pRELAXEventData->pInitTime->push_back(pStep->GetPreStepPoint()->GetGlobalTime()/ns);
    pRELAXEventData->pFinalTime->push_back(dInteractionTime = pStep->GetPostStepPoint()->GetGlobalTime()/ns);
    
    dEnergyDeposited = pStep->GetTotalEnergyDeposit()/keV;
    
    pSecondaryTrackVector = pStep->GetSecondaryInCurrentStep();
    
    for(int iCounter1 = 0; iCounter1 < pSecondaryTrackVector->size(); iCounter1++)
    {
        sSecondaryVolume = (*pSecondaryTrackVector)[iCounter1]->GetVolume()->GetName();
        
        if((sSecondaryVolume == "RegionX") || (sSecondaryVolume == "LXeActiveVolume") || (sSecondaryVolume == "GateLXe") || (sSecondaryVolume == "GateGXe") || (sSecondaryVolume == "RegionY"))
        {
            sSecondaryParticleType = (*pSecondaryTrackVector)[iCounter1]->GetDefinition()->GetParticleType();
            
            if(sSecondaryParticleType == "nucleus")
            {
                dEnergyDeposited += (*pSecondaryTrackVector)[iCounter1]->GetKineticEnergy()/keV;
            }
        }
        
        else if(sSecondaryVolume == "EJ301")
        {
            sSecondaryParticleName = (*pSecondaryTrackVector)[iCounter1]->GetDefinition()->GetParticleName();
            
            if((sSecondaryParticleName == "proton") || (sSecondaryParticleName == "deuteron") || (sSecondaryParticleName == "C12") || (sSecondaryParticleName == "C13"))
            {
                dEnergyDeposited += (*pSecondaryTrackVector)[iCounter1]->GetKineticEnergy()/keV;
                pRELAXEventData->dTotalPEEJ301 += 0.084 * 1.7 * (*pSecondaryTrackVector)[iCounter1]->GetKineticEnergy()/keV;
            }
            
            else if(sSecondaryParticleName == "gamma")
            {
                dEnergyDeposited += (*pSecondaryTrackVector)[iCounter1]->GetKineticEnergy()/keV;
                pRELAXEventData->dTotalPEEJ301 += 1.7 * (*pSecondaryTrackVector)[iCounter1]->GetKineticEnergy()/keV;
            }
        }
    }
    
    pRELAXEventData->pEnergyDeposited->push_back(dEnergyDeposited);
    
    if(sDepositingProcess != "Transportation")
    {
        if(sVolume == "RegionX")
        {
            pRELAXEventData->iTotalInteractionsRegionX++;
            pRELAXEventData->dEnergyDepositedRegionX += dEnergyDeposited;
            pRELAXEventData->dTotalEnergyDeposited += dEnergyDeposited;
            
            if(sParticleType == "neutron")
            {
                if(sDepositingProcess == "hadElastic")
                {
                    pRELAXEventData->iElasticScattersRegionX++;
                }
                
                else if(sDepositingProcess == "neutronInelastic")
                {
                    pRELAXEventData->iInelasticScattersRegionX++;
                }
                
                else if(sDepositingProcess == "nCapture")
                {
                    pRELAXEventData->iNeutronCaptureRegionX++;
                }

            }
            
            else if(sParticleType == "gamma")
            {
                if(sDepositingProcess == "phot")
                {
                    pRELAXEventData->iPERegionX++;
                }
                
                else if(sDepositingProcess == "compt")
                {
                    pRELAXEventData->iComptonScattersRegionX++;
                }
            }
            
            if(((pRELAXEventData->dFirstInteractionTimeLXe) < 0) || (dInteractionTime < (pRELAXEventData->dFirstInteractionTimeLXe)))
            {
                (pRELAXEventData->dFirstInteractionTimeLXe) = dInteractionTime;
            }
        }
        
        else if(sVolume == "LXeActiveVolume")
        {
            pRELAXEventData->iTotalInteractionsActiveVolume++;
            pRELAXEventData->dEnergyDepositedActiveVolume += dEnergyDeposited;
            pRELAXEventData->dTotalEnergyDeposited += dEnergyDeposited;
            
            if(sParticleType == "neutron")
            {
                if(sDepositingProcess == "hadElastic")
                {
                    pRELAXEventData->iElasticScattersActiveVolume++;
                }
                
                else if(sDepositingProcess == "neutronInelastic")
                {
                    pRELAXEventData->iInelasticScattersActiveVolume++;
                }
                
                else if(sDepositingProcess == "nCapture")
                {
                    pRELAXEventData->iNeutronCaptureActiveVolume++;
                }

            }
            
            else if(sParticleType == "gamma")
            {
                if(sDepositingProcess == "phot")
                {
                    pRELAXEventData->iPEActiveVolume++;
                }
                
                else if(sDepositingProcess == "compt")
                {
                    pRELAXEventData->iComptonScattersActiveVolume++;
                }
            }
            
            if(((pRELAXEventData->dFirstInteractionTimeLXe) < 0) || (dInteractionTime < (pRELAXEventData->dFirstInteractionTimeLXe)))
            {
                (pRELAXEventData->dFirstInteractionTimeLXe) = dInteractionTime;
            }
            
            dInteractionRadius = TMath::Sqrt(TMath::Power(dInteractionX - dActiveVolumeX, 2) + TMath::Power(dInteractionY - dActiveVolumeY, 2));
            
            if((dInteractionRadius < dFiducialVolumeRadius) && (dInteractionZ > (dActiveVolumeZ - 0.5 * dFiducialVolumeHeight)) && (dInteractionZ < (dActiveVolumeZ + 0.5 * dFiducialVolumeHeight)))
            {
                pRELAXEventData->iTotalInteractionsFiducialVolume++;
                pRELAXEventData->dEnergyDepositedFiducialVolume += dEnergyDeposited;
                
                if(sParticleType == "neutron")
                {
                    if(sDepositingProcess == "hadElastic")
                    {
                        pRELAXEventData->iElasticScattersFiducialVolume++;
                    }
                    
                    else if(sDepositingProcess == "neutronInelastic")
                    {
                        pRELAXEventData->iInelasticScattersFiducialVolume++;
                    }
                    
                    else if(sDepositingProcess == "nCapture")
                    {
                        pRELAXEventData->iNeutronCaptureFiducialVolume++;
                    }
                }
                
                else if(sParticleType == "gamma")
                {
                    if(sDepositingProcess == "phot")
                    {
                        pRELAXEventData->iPEFiducialVolume++;
                    }
                    
                    else if(sDepositingProcess == "compt")
                    {
                        pRELAXEventData->iComptonScattersFiducialVolume++;
                    }
                }
            }
        }
        
        else if(sVolume == "GateLXe")
        {
            pRELAXEventData->iTotalInteractionsGateLXe++;
            pRELAXEventData->dEnergyDepositedGateLXe += dEnergyDeposited;
            pRELAXEventData->dTotalEnergyDeposited += dEnergyDeposited;
            
            if(sParticleType == "neutron")
            {
                if(sDepositingProcess == "hadElastic")
                {
                    pRELAXEventData->iElasticScattersGateLXe++;
                }
                
                else if(sDepositingProcess == "neutronInelastic")
                {
                    pRELAXEventData->iInelasticScattersGateLXe++;
                }
                
                else if(sDepositingProcess == "nCapture")
                {
                    pRELAXEventData->iNeutronCaptureGateLXe++;
                }
            }
            
            else if(sParticleType == "gamma")
            {
                if(sDepositingProcess == "phot")
                {
                    pRELAXEventData->iPEGateLXe++;
                }
                
                else if(sDepositingProcess == "compt")
                {
                    pRELAXEventData->iComptonScattersGateLXe++;
                }
            }
            
            if(((pRELAXEventData->dFirstInteractionTimeLXe) < 0) || (dInteractionTime < (pRELAXEventData->dFirstInteractionTimeLXe)))
            {
                (pRELAXEventData->dFirstInteractionTimeLXe) = dInteractionTime;
            }
        }
        
        else if(sVolume == "GateGXe")
        {
            pRELAXEventData->iTotalInteractionsGateGXe++;
            pRELAXEventData->dEnergyDepositedGateGXe += dEnergyDeposited;
            pRELAXEventData->dTotalEnergyDeposited += dEnergyDeposited;
        
            if(sParticleType == "neutron")
            {
                if(sDepositingProcess == "hadElastic")
                {
                    pRELAXEventData->iElasticScattersGateGXe++;
                }
                
                else if(sDepositingProcess == "neutronInelastic")
                {
                    pRELAXEventData->iInelasticScattersGateGXe++;
                }
                
                else if(sDepositingProcess == "nCapture")
                {
                    pRELAXEventData->iNeutronCaptureGateGXe++;
                }
            }
            
            else if(sParticleType == "gamma")
            {
                if(sDepositingProcess == "phot")
                {
                    pRELAXEventData->iPEGateGXe++;
                }
                
                else if(sDepositingProcess == "compt")
                {
                    pRELAXEventData->iComptonScattersGateGXe++;
                }
            }
            
            if(((pRELAXEventData->dFirstInteractionTimeLXe) < 0) || (dInteractionTime < (pRELAXEventData->dFirstInteractionTimeLXe)))
            {
                (pRELAXEventData->dFirstInteractionTimeLXe) = dInteractionTime;
            }
        }
        
        else if(sVolume == "RegionY")
        {
            pRELAXEventData->iTotalInteractionsRegionY++;
            pRELAXEventData->dEnergyDepositedRegionY += dEnergyDeposited;
            pRELAXEventData->dTotalEnergyDeposited += dEnergyDeposited;
            
            if(sParticleType == "neutron")
            {
                if(sDepositingProcess == "hadElastic")
                {
                    pRELAXEventData->iElasticScattersRegionY++;
                }
                
                else if(sDepositingProcess == "neutronInelastic")
                {
                    pRELAXEventData->iInelasticScattersRegionY++;
                }
                
                else if(sDepositingProcess == "nCapture")
                {
                    pRELAXEventData->iNeutronCaptureRegionY++;
                }
            }
            
            else if(sParticleType == "gamma")
            {
                if(sDepositingProcess == "phot")
                {
                    pRELAXEventData->iPERegionY++;
                }
                
                else if(sDepositingProcess == "compt")
                {
                    pRELAXEventData->iComptonScattersRegionY++;
                }
            }
            
            if(((pRELAXEventData->dFirstInteractionTimeLXe) < 0) || (dInteractionTime < (pRELAXEventData->dFirstInteractionTimeLXe)))
            {
                (pRELAXEventData->dFirstInteractionTimeLXe) = dInteractionTime;
            }
        }
    
        else if(sVolume == "LXe")
        {
            if(sParticleType == "neutron")
            {
                if(sDepositingProcess == "hadElastic")
                {
                    pRELAXEventData->iElasticScattersSurroundingLXe++;
                }
                
                else if(sDepositingProcess == "neutronInelastic")
                {
                    pRELAXEventData->iInelasticScattersSurroundingLXe++;
                }
                
                else if(sDepositingProcess == "nCapture")
                {
                    pRELAXEventData->iNeutronCaptureSurroundingLXe++;
                }
            }
            
            else if(sParticleType == "gamma")
            {
                if(sDepositingProcess == "phot")
                {
                    pRELAXEventData->iPESurroundingLXe++;
                }
                
                else if(sDepositingProcess == "compt")
                {
                    pRELAXEventData->iComptonScattersSurroundingLXe++;
                }
            }
        }
    
        else if(sVolume == "GXe")
        {
            if(sParticleType == "neutron")
            {
                if(sDepositingProcess == "hadElastic")
                {
                    pRELAXEventData->iElasticScattersSurroundingGXe++;
                }
                
                else if(sDepositingProcess == "neutronInelastic")
                {
                    pRELAXEventData->iInelasticScattersSurroundingGXe++;
                }
                
                else if(sDepositingProcess == "nCapture")
                {
                    pRELAXEventData->iNeutronCaptureSurroundingGXe++;
                }
            }
            
            else if(sParticleType == "gamma")
            {
                if(sDepositingProcess == "phot")
                {
                    pRELAXEventData->iPESurroundingGXe++;
                }
                
                else if(sDepositingProcess == "compt")
                {
                    pRELAXEventData->iComptonScattersSurroundingGXe++;
                }
            }
        }
        
        else if((sVolume == "BottomPTFE") || (sVolume == "TopPTFE"))
        {
            if(sParticleType == "neutron")
            {
                if(sDepositingProcess == "hadElastic")
                {
                    pRELAXEventData->iElasticScattersPTFE++;
                }
        
                else if(sDepositingProcess == "neutronInelastic")
                {
                    pRELAXEventData->iInelasticScattersPTFE++;
                }
                
                else if(sDepositingProcess == "nCapture")
                {
                    pRELAXEventData->iNeutronCapturePTFE++;
                }

            }
            
            else if(sParticleType == "gamma")
            {
                if(sDepositingProcess == "phot")
                {
                    pRELAXEventData->iPEPTFE++;
                }
                
                else if(sDepositingProcess == "compt")
                {
                    pRELAXEventData->iComptonScattersPTFE++;
                }
            }
        }
        
        else if(sVolume == "EJ301")
        {
            pRELAXEventData->pInteractionXEJ301->push_back(dInteractionX);
            pRELAXEventData->pInteractionYEJ301->push_back(dInteractionY);
            pRELAXEventData->pInteractionZEJ301->push_back(dInteractionZ);
            pRELAXEventData->pInteractionTimeEJ301->push_back(dInteractionTime);
            pRELAXEventData->dTotalEnergyDepositedEJ301 += dEnergyDeposited;
            
            /*if(sParticleType == "proton")
            {
                pG4XCDEventData->dTotalPEEJ301 += 0.084 * 1.7 * dEnergyDeposited;
            }*/
        }
        
        if((!pRELAXEventData->iFoundFirstNeutronInteraction) && (sParticleType == "neutron"))
        {
            pRELAXEventData->sFirstNeutronInteractionProcess = sDepositingProcess;
            pRELAXEventData->sFirstNeutronInteractionVolume = sVolume;
            
            dInteractionRadius = TMath::Sqrt(TMath::Power(dInteractionX - dActiveVolumeX, 2) + TMath::Power(dInteractionY - dActiveVolumeY, 2));
            
            if((sVolume == "LXeActiveVolume") && (dInteractionRadius < dFiducialVolumeRadius) && (dInteractionZ > (dActiveVolumeZ - 0.5 * dFiducialVolumeHeight)) && (dInteractionZ < (dActiveVolumeZ + 0.5 * dFiducialVolumeHeight)))
            {
                pRELAXEventData->sFirstNeutronInteractionVolume = "FiducialVolume";
            }
            
            pRELAXEventData->dFirstNeutronInteractionX = dInteractionX;
            pRELAXEventData->dFirstNeutronInteractionY = dInteractionY;
            pRELAXEventData->dFirstNeutronInteractionZ = dInteractionZ;
            pRELAXEventData->dFirstNeutronInteractionTime = dInteractionTime;
            
            pRELAXEventData->iFoundFirstNeutronInteraction = 1;
        }
        
        else if((!pRELAXEventData->iFoundSecondNeutronInteraction) && (sParticleType == "neutron"))
        {
            pRELAXEventData->sSecondNeutronInteractionProcess = sDepositingProcess;
            pRELAXEventData->sSecondNeutronInteractionVolume = sVolume;
            
            dInteractionRadius = TMath::Sqrt(TMath::Power(dInteractionX - dActiveVolumeX, 2) + TMath::Power(dInteractionY - dActiveVolumeY, 2));
            
            if((sVolume == "LXeActiveVolume") && (dInteractionRadius < dFiducialVolumeRadius) && (dInteractionZ > (dActiveVolumeZ - 0.5 * dFiducialVolumeHeight)) && (dInteractionZ < (dActiveVolumeZ + 0.5 * dFiducialVolumeHeight)))
            {
                pRELAXEventData->sSecondNeutronInteractionVolume = "FiducialVolume";
            }
            
            pRELAXEventData->dSecondNeutronInteractionX = dInteractionX;
            pRELAXEventData->dSecondNeutronInteractionY = dInteractionY;
            pRELAXEventData->dSecondNeutronInteractionZ = dInteractionZ;
            pRELAXEventData->dSecondNeutronInteractionTime = dInteractionTime;
            
            pRELAXEventData->iFoundSecondNeutronInteraction = 1;
        }
    }
}

void RELAXAnalysisManager::EndOfEventAction(const G4Event* pEvent)
{
    G4int iNbPmtHits = 0;
    G4HCofThisEvent *pHCofThisEvent = pEvent->GetHCofThisEvent();

    Xenon1tPmtHitsCollection *pPmtHitsCollection = 0;

 //   G4int iNbPmtHits = 0;

    if (pHCofThisEvent) {
          if (m_iPmtHitsCollectionID != -1) {
      pPmtHitsCollection = (Xenon1tPmtHitsCollection *)(pHCofThisEvent->GetHC(m_iPmtHitsCollectionID));
      iNbPmtHits = (pPmtHitsCollection) ? (pPmtHitsCollection->entries()) : (0);
      pRELAXEventData->photonsC = iNbPmtHits;
      photonsC += iNbPmtHits;
    }
      }
    pTree1->Fill();
    pTree2->Fill();
    pTree3->Fill();
    pTree4->Fill();
    pTree5->Fill();    
 
    pMapParticleType->clear();
    pRELAXEventData->Clear();
}

void RELAXAnalysisManager::EndOfRunAction(const G4Run* pRun)
{
    G4cout << "photonsC = " << photonsC << G4endl;
    pFile->Write();
    pFile->Close();
}

void RELAXAnalysisManager::SetFilenameReference(G4String* mFilenameReference)
{
    pFilenameReference = mFilenameReference;
}

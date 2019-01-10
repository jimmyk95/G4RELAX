// XENON Header Files
#include "Xenon1tPmtSensitiveDetector.hh"
#include "Xenon1tPmtHit.hh"

using namespace std;
// Additional Header Files
#include <map>

using namespace std;

// G4 Header FIles
#include <G4HCofThisEvent.hh>
#include <G4SDManager.hh>
#include <G4Step.hh>
#include <G4ThreeVector.hh>
#include <G4VProcess.hh>
#include <G4ios.hh>
#include <G4SystemOfUnits.hh>
#if GEANTVERSION >= 10
#include <G4SystemOfUnits.hh>
#endif

Xenon1tPmtSensitiveDetector::Xenon1tPmtSensitiveDetector(G4String hName)
    : G4VSensitiveDetector(hName) {
  collectionName.insert("PmtHitsCollection");
}

Xenon1tPmtSensitiveDetector::~Xenon1tPmtSensitiveDetector() {}

void Xenon1tPmtSensitiveDetector::Initialize(
    G4HCofThisEvent *pHitsCollectionOfThisEvent) {
  m_pPmtHitsCollection =
      new Xenon1tPmtHitsCollection(SensitiveDetectorName, collectionName[0]);

  static G4int iHitsCollectionID = -1;

  if (iHitsCollectionID < 0)
    iHitsCollectionID =
        G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

  pHitsCollectionOfThisEvent->AddHitsCollection(iHitsCollectionID,
                                                m_pPmtHitsCollection);
}

G4bool Xenon1tPmtSensitiveDetector::ProcessHits(G4Step *pStep,
                                                G4TouchableHistory *) {
  G4Track *pTrack = pStep->GetTrack();

  G4double radius = sqrt(pStep->GetPreStepPoint()->GetPosition().x() *
                             pStep->GetPreStepPoint()->GetPosition().x() +
                         pStep->GetPreStepPoint()->GetPosition().y() *
                             pStep->GetPreStepPoint()->GetPosition().y());

  if (pTrack->GetDefinition()->GetParticleName() == "opticalphoton") {
    Xenon1tPmtHit *pHit = new Xenon1tPmtHit();

    pHit->SetPosition(pStep->GetPreStepPoint()->GetPosition());
    pHit->SetTime(pTrack->GetGlobalTime());
    pHit->SetDirection(pStep->GetPreStepPoint()->GetMomentumDirection());
    pHit->SetVolumeName(pTrack->GetTouchable()->GetVolume(0)->GetName());

    if (radius < 1000. * mm) {
      // G4cout << "Pmt hit ---> in TPC " <<
      // pTrack->GetTouchable()->GetVolume(2)->GetCopyNo() << G4endl;
      pHit->SetPmtNb(pTrack->GetTouchable()->GetVolume(2)->GetCopyNo());
    } else {
      // G4cout << "Pmt hit ---> in VETO " <<
      // pTrack->GetTouchable()->GetVolume(1)->GetCopyNo() << G4endl;
      pHit->SetPmtNb(pTrack->GetTouchable()->GetVolume(1)->GetCopyNo());
    }

    pHit->SetTrackId(pTrack->GetTrackID());

    m_pPmtHitsCollection->insert(pHit);

    //		pHit->Print();
    //		pHit->Draw();
    return true;
  } else {
    return false;
  }
}

void Xenon1tPmtSensitiveDetector::EndOfEvent(G4HCofThisEvent *) {
  //  if (verboseLevel>0) {
  //     G4int NbHits = trackerCollection->entries();
  //     G4cout << "\n-------->Hits Collection: in this event they are " <<
  //     NbHits
  //            << " hits in the tracker chambers: " << G4endl;
  //     for (G4int i=0;i<NbHits;i++) (*trackerCollection)[i]->Print();
  //    }
}

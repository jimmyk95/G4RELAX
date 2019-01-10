#ifndef __XENONPMTSENSITIVEDETECTOR_H__
#define __XENONPMTSENSITIVEDETECTOR_H__

// XENON Header Files
#include "Xenon1tPmtHit.hh"

// G4 Header FIles
#include <G4VSensitiveDetector.hh>

class G4Step;
class G4HCofThisEvent;

class Xenon1tPmtSensitiveDetector : public G4VSensitiveDetector {
 public:
  Xenon1tPmtSensitiveDetector(G4String hName);
  ~Xenon1tPmtSensitiveDetector();

  void Initialize(G4HCofThisEvent *pHitsCollectionOfThisEvent);
  G4bool ProcessHits(G4Step *pStep, G4TouchableHistory *pHistory);
  void EndOfEvent(G4HCofThisEvent *pHitsCollectionOfThisEvent);

 private:
  Xenon1tPmtHitsCollection *m_pPmtHitsCollection;
};

#endif

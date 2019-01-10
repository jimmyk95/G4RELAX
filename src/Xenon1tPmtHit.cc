#if GEANTVERSION >= 10
#include <G4SystemOfUnits.hh>
#endif

#include <G4SystemOfUnits.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4VisAttributes.hh>
#include <G4SystemOfUnits.hh>

#include "Xenon1tPmtHit.hh"

G4Allocator<Xenon1tPmtHit> Xenon1tPmtHitAllocator;

G4int Xenon1tPmtHit::operator==(const Xenon1tPmtHit &hXenon1tPmtHit) const {
  return ((this == &hXenon1tPmtHit) ? (1) : (0));
}

void Xenon1tPmtHit::Draw() {
  //    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  //
  //    if(pVVisManager)
  //    {
  //        G4Circle hCircle(m_hPosition);
  //        G4Colour hColour(1.000, 0.973, 0.184);
  //        G4VisAttributes hVisAttributes(hColour);
  //
  //        hCircle.SetScreenSize(0.1);
  //        hCircle.SetFillStyle(G4Circle::filled);
  //        hCircle.SetVisAttributes(hVisAttributes);
  //        pVVisManager->Draw(hCircle);
  //    }
}

void Xenon1tPmtHit::Print() {
  G4cout << "Pmt hit ---> "
         << "Pmt#" << m_iPmtNb << " Position: " << m_hPosition.x() / mm << " "
         << m_hPosition.y() / mm << " " << m_hPosition.z() / mm << " mm"
         << " Time: " << m_dTime / s << " s" << G4endl;
}

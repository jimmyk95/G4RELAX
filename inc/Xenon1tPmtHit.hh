#ifndef __XENON10PPMTHIT_H__
#define __XENON10PPMTHIT_H__

#include <G4Allocator.hh>
#include <G4THitsCollection.hh>
#include <G4ThreeVector.hh>
#include <G4VHit.hh>

class Xenon1tPmtHit : public G4VHit {
 public:
  G4int operator==(const Xenon1tPmtHit &) const;

  inline void *operator new(size_t);
  inline void operator delete(void *);

  void Draw();
  void Print();

 public:
  void SetPosition(G4ThreeVector hPosition) { m_hPosition = hPosition; }
  void SetDirection(G4ThreeVector hDirection) { m_hDirection = hDirection; }
  void SetTime(G4double dTime) { m_dTime = dTime; }
  void SetPmtNb(G4int iPmtNb) { m_iPmtNb = iPmtNb; }
  void SetTrackId(G4int iTrackId) { m_iTrackId = iTrackId; }
  void SetVolumeName(const G4String &hVolumeName) {
    m_pVolumeName = hVolumeName;
  }

  G4ThreeVector GetPosition() const { return m_hPosition; }
  G4ThreeVector GetDirection() const { return m_hDirection; }
  G4double GetTime() const { return m_dTime; }
  G4int GetPmtNb() const { return m_iPmtNb; }
  G4int GetTrackId() const { return m_iTrackId; }
  const G4String &GetVolumeName() const { return m_pVolumeName; }

 private:
  G4ThreeVector m_hPosition;
  G4ThreeVector m_hDirection;
  G4double m_dTime;
  G4int m_iPmtNb;
  G4int m_iTrackId;
  G4String m_pVolumeName;
};

typedef G4THitsCollection<Xenon1tPmtHit> Xenon1tPmtHitsCollection;

extern G4Allocator<Xenon1tPmtHit> Xenon1tPmtHitAllocator;

inline void *Xenon1tPmtHit::operator new(size_t) {
  return ((void *)Xenon1tPmtHitAllocator.MallocSingle());
}

inline void Xenon1tPmtHit::operator delete(void *pXenon1tPmtHit) {
  Xenon1tPmtHitAllocator.FreeSingle((Xenon1tPmtHit *)pXenon1tPmtHit);
}

#endif  // __XENON10PPMTHIT_H__

#ifndef StPicoTrack_h
#define StPicoTrack_h

#include <cmath>

#include "TObject.h"
#include "StarClassLibrary/StThreeVectorF.hh"
#include "StarClassLibrary/StThreeVectorD.hh"
#include "StarClassLibrary/StPhysicalHelixD.hh"
#include "StarClassLibrary/SystemOfUnits.h"
#include "StEvent/StDcaGeometry.h"

class StMuTrack;
class StDcaGeometry;

class StPicoTrack : public TObject
{
public:
  StPicoTrack();
  StPicoTrack(StMuTrack const* globalTrack, StMuTrack const* primaryTrack, double magField, StThreeVectorD const& pVtx, StDcaGeometry const& dcaG);
  virtual ~StPicoTrack() {}

  // This class doesn't allocate any data on the heap so the default copy ctor
  // and assignment operators are sufficient. The compiler will generate them
  // by default for this class because the destructor is explicitely defined.
  // But please note that this auto-generation feature is deprecated, i.e.
  // it might disappear from future compiler implementations.
  // Explicitely requesting the defaults as done below is the way to go, however
  // it currently doesn't work with STAR version of rootcint which is needed for
  // ROOT I/O on this object.
  //StPicoTrack(StPicoTrack const&) = default;
  //StPicoTrack& operator=(StPicoTrack const&) = default;

  virtual void Print(Char_t const* option = "") const;  ///< Print track info

  Int_t   id() const;
  Float_t chi2() const;
  Float_t gPt() const;
  Float_t gPtot() const;
  StThreeVectorF const& pMom() const;
  StThreeVectorF const& gMom() const;
  StThreeVectorF gMom(StThreeVectorF const& pVtx, float B) const;
  StThreeVectorF const& origin() const;
  StThreeVectorF const& dca() const;
  Short_t charge() const;
  Int_t   nHitsFit() const;
  Int_t   nHitsMax() const;
  Int_t   nHitsDedx() const;
  UInt_t  hftHitsMap() const;
  Float_t dEdx() const;
  Float_t nSigmaPion() const;
  Float_t nSigmaKaon() const;
  Float_t nSigmaProton() const;
  Float_t nSigmaElectron() const;

  UInt_t  map0() const;
  UInt_t  map1() const;

  StPhysicalHelixD helix(float B) const;
  bool isHFTTrack() const;

  /** Checks whether this track is associated with a primary vertex. */
  bool isPrimary() const;

  // MTD pid traits
  void setEmcPidTraitsIndex(Int_t index);
  void setBTofPidTraitsIndex(Int_t index);
  void setMtdPidTraitsIndex(Int_t index);

  Int_t emcPidTraitsIndex() const;
  Int_t bTofPidTraitsIndex() const;
  Int_t mtdPidTraitsIndex() const;

protected:
  UShort_t mId;               // track Id
  UShort_t mChi2;             // chi2*1000
  StThreeVectorF mPMomentum;  // primary momentum, (0.,0.,0.) if none
  StThreeVectorF mGMomentum;  // global momentum at dca to primary vertex
  StThreeVectorF mOrigin;     // origin at dca to primary vertex
  UShort_t mDedx;             // dEdx*1000
  Char_t   mNHitsFit;         // q*nHitsFit - TPC
  Char_t   mNHitsMax;         // nHitsMax - TPC
  UChar_t  mNHitsDedx;        // nHitsDedx - TPC
  Short_t  mNSigmaPion;       // nsigmaPi * 100
  Short_t  mNSigmaKaon;       // nsigmaK * 100
  Short_t  mNSigmaProton;     // nsigmaP * 100
  Short_t  mNSigmaElectron;   // nsigmaE * 100
  UInt_t   mMap0;             // TopologyMap data0
  UInt_t   mMap1;             // TopologyMap data1

  // pidTraits
  Short_t  mEmcPidTraitsIndex;  // index of the EMC  pidTratis in the event
  Short_t  mBTofPidTraitsIndex; // index of the BTOF pidTratis in the event
  Short_t  mMtdPidTraitsIndex;  // index of the MTD  pidTratis in the event

  ClassDef(StPicoTrack, 1)
};

inline void StPicoTrack::setEmcPidTraitsIndex(Int_t index) { mEmcPidTraitsIndex = (Short_t)index; }
inline void StPicoTrack::setBTofPidTraitsIndex(Int_t index) { mBTofPidTraitsIndex = (Short_t)index; }
inline void StPicoTrack::setMtdPidTraitsIndex(Int_t index) { mMtdPidTraitsIndex = (Short_t)index; }
inline Int_t   StPicoTrack::id() const { return mId; }
inline Float_t StPicoTrack::chi2() const { return mChi2 / 1000.f; }
inline Float_t StPicoTrack::gPt() const { return mGMomentum.perp(); }
inline Float_t StPicoTrack::gPtot() const { return mGMomentum.mag(); }
inline StThreeVectorF const& StPicoTrack::pMom() const { return mPMomentum; }
inline StThreeVectorF const& StPicoTrack::gMom() const { return mGMomentum; }
inline StThreeVectorF const& StPicoTrack::origin() const { return mOrigin; }
inline StThreeVectorF const& StPicoTrack::dca() const { return mOrigin; }
inline Short_t StPicoTrack::charge() const { return (mNHitsFit > 0) ? +1 : -1; }
inline Int_t   StPicoTrack::nHitsFit() const { return (mNHitsFit > 0) ? (Int_t)mNHitsFit : (Int_t)(-1 * mNHitsFit); }
inline Int_t   StPicoTrack::nHitsMax() const { return mNHitsMax; }
inline Int_t   StPicoTrack::nHitsDedx() const { return mNHitsDedx; }
inline UInt_t  StPicoTrack::hftHitsMap() const { return mMap0 >> 1 & 0x7F; }
inline Float_t StPicoTrack::dEdx() const { return mDedx / 1000.f; }
inline Float_t StPicoTrack::nSigmaPion() const { return mNSigmaPion / 100.f; }
inline Float_t StPicoTrack::nSigmaKaon() const { return mNSigmaKaon / 100.f; }
inline Float_t StPicoTrack::nSigmaProton() const { return mNSigmaProton / 100.f; }
inline Float_t StPicoTrack::nSigmaElectron() const { return mNSigmaElectron / 100.f; }
inline UInt_t  StPicoTrack::map0() const { return mMap0; }
inline UInt_t  StPicoTrack::map1() const { return mMap1; }
inline Int_t   StPicoTrack::emcPidTraitsIndex() const { return mEmcPidTraitsIndex; }
inline Int_t   StPicoTrack::bTofPidTraitsIndex() const { return mBTofPidTraitsIndex; }
inline Int_t   StPicoTrack::mtdPidTraitsIndex() const { return mMtdPidTraitsIndex; }

inline bool StPicoTrack::isHFTTrack() const
{
  UInt_t const hitsMap = hftHitsMap();
  return (hitsMap >> 0 & 0x1) && (hitsMap >> 1 & 0x3) && (hitsMap >> 3 & 0x3);
}

/**
 * The default "primary" momentum is (0, 0, 0) but it is expected to have
 * a non-zero length when the track is associated with a primary vertex.
 */
inline bool StPicoTrack::isPrimary() const
{
  return mPMomentum.magnitude() > 0;
}

/// Return the global momentum at the dca point to the pVtx (usually it is the primary vertex.   B - magnetic field from PicoEvent::bField()
inline StThreeVectorF StPicoTrack::gMom(StThreeVectorF const& pVtx, float const B) const
{
  StPhysicalHelixD gHelix = helix(B);
  return gHelix.momentumAt(gHelix.pathLength(pVtx), B * kilogauss);
}

inline StPhysicalHelixD StPicoTrack::helix(float const B) const
{
  return StPhysicalHelixD(mGMomentum, mOrigin, B * kilogauss, static_cast<float>(charge()));
}
#endif

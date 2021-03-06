#include <limits>
#include "TMath.h"
#include "St_base/StMessMgr.h"

#include "StPicoEvent/StPicoEmcPidTraits.h"


//----------------------------------------------------------------------------------
StPicoEmcPidTraits::StPicoEmcPidTraits() :
  mTrackIndex(-1),
  mBEMCId(-9999), mBTOWADC0(-9999), mBTOWE0(-9999), mBTOWE(-9999),
  mBEMCDistZ(-9999), mBEMCDistPhi(-9999),
  mBSMDNEta(std::numeric_limits<unsigned char>::max()), mBSMDNPhi(std::numeric_limits<unsigned char>::max()),
  mBTOWId(-9999), mBTOWId23(std::numeric_limits<unsigned char>::max()),
  mBTOWE1(-9999), mBTOWE2(-9999), mBTOWE3(-9999),
  mBTOWDistEta(-9999), mBTOWDistPhi(-9999)
{
  // constructor
}

//----------------------------------------------------------------------------------
StPicoEmcPidTraits::StPicoEmcPidTraits(Int_t index, Int_t id, Int_t adc0, Float_t const* e, Float_t const* dist, Int_t const* nhit, Int_t const* ntow): StPicoEmcPidTraits()
{
  mTrackIndex = (index > std::numeric_limits<short>::max()) ? -1 : (Short_t)index;

  mBEMCId       = (id > std::numeric_limits<short>::max()) ? -1 : (Short_t)id;
  mBTOWADC0     = (adc0 > std::numeric_limits<unsigned short>::max()) ? std::numeric_limits<unsigned short>::max() : (UShort_t)adc0;
  mBTOWE0       = (e[0] * 1000. > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(e[0] * 1000.));
  mBTOWE        = (e[1] * 1000. > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(e[1] * 1000.));
  mBEMCDistZ    = (fabs(dist[0] * 100.) > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(dist[0] * 100.));
  mBEMCDistPhi  = (fabs(dist[1] * 10000.) > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(dist[1] * 10000.));
  mBSMDNEta     = (nhit[0] > std::numeric_limits<unsigned char>::max()) ? std::numeric_limits<unsigned char>::max() : (UChar_t)(nhit[0]);
  mBSMDNPhi     = (nhit[1] > std::numeric_limits<unsigned char>::max()) ? std::numeric_limits<unsigned char>::max() : (UChar_t)(nhit[1]);

  mBTOWId       = (ntow[0] <= 0 || ntow[0] > 4800) ? -1 : (Short_t)ntow[0];
  mBTOWId23     = (ntow[1] < 0 || ntow[1] >= 9 || ntow[2] < 0 || ntow[2] >= 9) ? -1 : (Char_t)(ntow[1] * 10 + ntow[2]);
  mBTOWE1       = (e[2] * 1000. > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(e[2] * 1000.));
  mBTOWE2       = (e[3] * 1000. > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(e[3] * 1000.));
  mBTOWE3       = (e[4] * 1000. > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(e[4] * 1000.));
  mBTOWDistEta  = (fabs(dist[2] * 10000.) > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(dist[2] * 10000.));
  mBTOWDistPhi  = (fabs(dist[3] * 10000.) > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(dist[3] * 10000.));
}

//----------------------------------------------------------------------------------
StPicoEmcPidTraits::~StPicoEmcPidTraits()
{
  // destructor
}

//----------------------------------------------------------------------------------
void StPicoEmcPidTraits::Print(const Char_t* option) const
{
  LOG_INFO << "Matched track index = " << mTrackIndex << endm;
  LOG_INFO << " BEMC Id = " << bemcId() << " BTOW ADC0 = " << adc0() << " energy0 = " << e0() << " e = " << e() << endm;
  LOG_INFO << " BEMC distz = " << zDist() << " distphi = " << phiDist() << endm;
  LOG_INFO << " BSMD nEta/nPhi = " << nEta() << "/" << nPhi() << endm;
  LOG_INFO << " BTOW Id = " << btowId() << " tower Id 2/3 = " << btowId2() << " " << btowId3() << endm;
  LOG_INFO << " BTOW energy = " << e1() << " " << e2() << " " << e3() << endm;
  LOG_INFO << " BTOW position to center = " << etaTowDist() << " " << phiTowDist() << endm;
}

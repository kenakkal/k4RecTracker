// VTXdigi_Modular/include/IChargeCollector.h
#pragma once

#include "TGeoMatrix.h"

struct VTXdigi_Modular;

namespace VTXdigi_tools {
  
  class SimHitWrapper; // forward-declare things in include/VTXdigi_tools.h -> forward-declare : tells compiler tehse classes exists but details are elsewhere
  class HitMap; // forward-declare; Allows using pointers/references without including full headers; reduces compilation dependencies

class IChargeCollector { //abstract base class
public:
  virtual ~IChargeCollector() = default; // virtual destructor 
  // Don't need full definition of SimHitWrapper, just a reference. // If we included the full header, compilation would be slower
  virtual void FillHit(const SimHitWrapper& simHit, HitMap& hitMap, const TGeoHMatrix& trafoMatrix) const = 0; //pure virtual function (=0)
  float GetChargeCollectionDepthCenter() const { return m_chargeCollectionDepthCenter; }

protected:
  explicit IChargeCollector(const VTXdigi_Modular& digitizer) : m_digitizer(digitizer) {}

  const VTXdigi_Modular& m_digitizer;
  float m_chargeCollectionDepthCenter=0; // Defines the vertical center of the charge collection region in the sensitive volume. Needed for correct digiHit positions (and residual plots) with LUTs where the charge collection varies along their depth (like TPSCo 65nm CIS). in mm, wrt. the sensor local w coordinate (w=0 at center of sensitive volume)
};

std::unique_ptr<IChargeCollector> CreateChargeCollector(const VTXdigi_Modular& digitizer, const std::string& algorithm);

} // namespace VTXdigi_tools
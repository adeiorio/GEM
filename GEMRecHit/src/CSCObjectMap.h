#ifndef RecoLocalMuon_GEMRecHit_CSCObjectMap_h
#define RecoLocalMuon_GEMRecHit_CSCObjectMap_h

#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "RecoLocalMuon/GEMRecHit/src/CSCStationIndex.h"

#include <set>
#include <map>

class CSCObjectMap {
public:
  CSCObjectMap(MuonGeometryRecord const& record);

  std::set<GEMDetId> const& getRolls(CSCStationIndex index) const;

private:
  std::map<CSCStationIndex,std::set<GEMDetId>> rollstore;
}; 

#endif // RecoLocalMuon_GEMRecHit_CSCObjectMap_h

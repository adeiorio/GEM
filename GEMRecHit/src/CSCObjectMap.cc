#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/CommonDetUnit/interface/TrackingGeometry.h"
#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
//#include "Geometry/GEMGeometry/interface/GEMGeomServ.h"
#include "Geometry/GEMGeometry/interface/GEMChamber.h"
#include "Geometry/GEMGeometry/interface/GEMEtaPartition.h"
#include "Geometry/GEMGeometry/interface/GEMRing.h"
#include "Geometry/CSCGeometry/interface/CSCGeometry.h"
#include "RecoLocalMuon/GEMRecHit/src/CSCObjectMap.h"
#include "RecoLocalMuon/GEMRecHit/src/CSCStationIndex.h"

CSCObjectMap::CSCObjectMap(MuonGeometryRecord const& record){
  edm::ESHandle<GEMGeometry> gemGeo;
  record.get(gemGeo);

  edm::ESHandle<CSCGeometry> cscGeo;
  record.get(cscGeo);
  
  for (TrackingGeometry::DetContainer::const_iterator it=gemGeo->dets().begin();it<gemGeo->dets().end();it++){
    if(dynamic_cast< const GEMChamber* >( *it ) != nullptr ){
      auto ch = dynamic_cast< const GEMChamber* >( *it ); 
      std::vector< const GEMEtaPartition*> roles = (ch->etaPartitions());
      for(std::vector<const GEMEtaPartition*>::const_iterator r = roles.begin(); r != roles.end(); ++r){
	GEMDetId gemId = (*r)->id();
	int region=gemId.region();
	if(region!=0){
	  int station=gemId.station();
          int ring=gemId.ring();
          int chamber=gemId.chamber();
          int cscring=ring;
          int cscstation=station;
          int cscchamber=chamber;
	  /*	  GEMGeomServ gemsrv(gemId);
	  int gemsegment = gemsrv.segment();
	  int cscchamber = gemsegment; //FIX THIS ACCORDING TO GEMGeomServ::segment()Definition
          if((station==2||station==3)&&ring==3){//Adding Ring 3 of GEM to the CSC Ring 2
            cscring = 2;
	    }*/
	  CSCStationIndex ind(region,cscstation,cscring,cscchamber);
          std::set<GEMDetId> myrolls;
	  if (rollstore.find(ind)!=rollstore.end()) myrolls=rollstore[ind];
	  myrolls.insert(gemId);
          rollstore[ind]=myrolls;
	}
      }
    }
  }
}

std::set<GEMDetId> const& CSCObjectMap::getRolls(CSCStationIndex index) const
{
  // FIXME
  // the present implementation allows for NOT finding the given index in the map;
  // a muon expert should check that this is the intended behaviour.
  static const std::set<GEMDetId> empty;
  return (rollstore.find(index) == rollstore.end()) ? empty : rollstore.at(index);
}

// register the class with the typelookup system used by the EventSetup
#include "FWCore/Utilities/interface/typelookup.h"
TYPELOOKUP_DATA_REG(CSCObjectMap);

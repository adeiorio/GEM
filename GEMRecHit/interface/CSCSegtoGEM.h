#ifndef  CSCSEGTOGEM_H
#define  CSCSEGTOGEM_H

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHit.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"

#include <memory>

class CSCSegtoGEM {
public:
  CSCSegtoGEM(CSCSegmentCollection const* allCSCSegments, edm::EventSetup const& iSetup, bool debug, double eyr);
  ~CSCSegtoGEM();
  std::unique_ptr<GEMRecHitCollection> && thePoints(){ return std::move(_ThePoints); }
   
private:
  std::unique_ptr<GEMRecHitCollection> _ThePoints; 
  edm::OwnVector<GEMRecHit> GEMPointVector;
  bool inclcsc;
  double MaxD;
};

#endif

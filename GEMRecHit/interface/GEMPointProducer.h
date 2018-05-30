#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/global/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHit.h"
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
//#include "RecoLocalMuon/GEMRecHit/interface/DTSegtoGEM.h"
#include "RecoLocalMuon/GEMRecHit/interface/CSCSegtoGEM.h"
//#include "RecoLocalMuon/GEMRecHit/interface/TracktoGEM.h" 

//
// class decleration
//

class GEMPointProducer : public edm::global::EDProducer<> {
   public:
      explicit GEMPointProducer(const edm::ParameterSet&);

   private:
      void produce(edm::StreamID, edm::Event&, const edm::EventSetup&) const override;

      const edm::EDGetTokenT<CSCSegmentCollection> cscSegments;
      const edm::EDGetTokenT<DTRecSegment4DCollection> dt4DSegments;
      //      const edm::EDGetTokenT<reco::TrackCollection> tracks; la libreria trackcollection viene importata in tracktoGEM.h CAPIRE A COSA SERVE E COSA FA
      const edm::InputTag tracks_;

      const bool incldt;
      const bool inclcsc;
      const bool incltrack; 
      const bool debug;
      const double MinCosAng;
      const double MaxD;
      const double MaxDrb4;
      const double ExtrapolatedRegion;
      const edm::ParameterSet trackTransformerParam;
};


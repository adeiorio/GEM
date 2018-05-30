import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
#  8 eta partitions :: command line option :: --geometry Geometry/GEMGeometry/cmsExtendedGeometryPostLS1plusGEMr08v01XML_cfi.py
# 10 eta partitions :: command line option :: --geometry Geometry/GEMGeometry/cmsExtendedGeometryPostLS1plusGEMr10v01XML_cfi.py
# process.load('Geometry.GEMGeometry.cmsExtendedGeometryPostLS1plusGEMr08v01XML_cfi')
# process.load('Geometry.GEMGeometry.cmsExtendedGeometryPostLS1plusGEMr10v01XML_cfi')
process.load('Configuration.Geometry.GeometryExtended2015MuonGEMDevReco_cff')
process.load('Configuration.Geometry.GeometryExtended2015MuonGEMDev_cff')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:step2.root'
    )
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("miniTreesGem.root"))

process.demo = cms.EDAnalyzer('TestGEMRecHitAnalyzer',
                              RootFileName = cms.untracked.string("TestGEMRecHitHistograms.root"),
)


process.p = cms.Path(process.demo)

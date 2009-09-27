import FWCore.ParameterSet.Config as cms

isolatedElectrons = cms.EDFilter("HWWElectronIsolation",
                                 src = cms.InputTag("selectedElectrons"),
                                 TrackIsolCut = cms.double(6.0), # GeV: absolute isolation
                                 absolute = cms.bool(True)
                                 )

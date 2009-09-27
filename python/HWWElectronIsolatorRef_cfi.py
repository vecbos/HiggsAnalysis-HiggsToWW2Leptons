import FWCore.ParameterSet.Config as cms

isolatedElectronsRef = cms.EDFilter("HWWElectronIsolationRef",
                                    src = cms.InputTag("selectedElectrons"),
                                    TrackIsolCut = cms.double(6.0), # GeV: absolute isolation
                                    absolute = cms.bool(True)
                                    )

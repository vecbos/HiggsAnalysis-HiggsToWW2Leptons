import FWCore.ParameterSet.Config as cms

isolatedElectrons = cms.EDFilter("HWWElectronIsolation",
                                 src = cms.InputTag("pixelMatchGsfElectrons"),
                                 SelectedElectronRefCollectionLabel = cms.InputTag("selectedElectronsRef"),
                                 TrackIsolationProducerLabel = cms.InputTag("egammaTrackerIsolationLoose"),
                                 TrackIsolCut = cms.double(6.0), # GeV: absolut isolation
                                 doRefCheck = cms.bool(True)
                                 )

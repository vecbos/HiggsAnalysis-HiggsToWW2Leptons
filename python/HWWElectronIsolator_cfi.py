import FWCore.ParameterSet.Config as cms

isolatedElectrons = cms.EDFilter("HWWElectronIsolation",
                                 src = cms.InputTag("pixelMatchGsfElectrons"),
                                 SelectedElectronRefCollectionLabel = cms.InputTag("selectedElectronsRef"),
                                 TrackIsolationProducerLabel = cms.InputTag("egammaTrackerIsolationLoose"),
                                 TrackIsolCut = cms.double(0.1),
                                 doRefCheck = cms.bool(True)
                                 )

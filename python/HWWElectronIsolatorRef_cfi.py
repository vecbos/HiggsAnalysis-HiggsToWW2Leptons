import FWCore.ParameterSet.Config as cms

isolatedElectronsRef = cms.EDFilter("HWWElectronIsolationRef",
                                    src = cms.InputTag("pixelMatchGsfElectrons"),
                                    SelectedElectronRefCollectionLabel = cms.InputTag("selectedElectronsRef"),
                                    TrackIsolationProducerLabel = cms.InputTag("egammaTrackerIsolationLoose"),
                                    TrackIsolCut = cms.double(0.1),
                                    doRefCheck = cms.bool(True)
                                    )

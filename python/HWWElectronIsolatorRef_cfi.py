import FWCore.ParameterSet.Config as cms

isolatedElectronsRef = cms.EDFilter("HWWElectronIsolationRef",
                                    src = cms.InputTag("pixelMatchGsfElectrons"),
                                    SelectedElectronRefCollectionLabel = cms.InputTag("selectedElectronsRef"),
                                    TrackIsolationProducerLabel = cms.InputTag("egammaTrackerIsolationLoose"),
                                    TrackIsolCut = cms.double(6.0), # GeV, absolut isolation
                                    doRefCheck = cms.bool(True)
                                    )

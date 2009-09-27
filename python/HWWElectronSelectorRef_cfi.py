import FWCore.ParameterSet.Config as cms

selectedElectronsRef = cms.EDFilter("HWWElectronSelectionRef",
                                    src = cms.InputTag("gsfElectrons"),
                                    electronIdCutsLabel = cms.InputTag("eidLoose")
                                    )

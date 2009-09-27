import FWCore.ParameterSet.Config as cms

selectedElectrons = cms.EDFilter("HWWElectronSelection",
                                 src = cms.InputTag("gsfElectrons"),
                                 electronIdCutsLabel = cms.InputTag("eidLoose")
                                 )

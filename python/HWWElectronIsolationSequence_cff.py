import FWCore.ParameterSet.Config as cms

import EgammaAnalysis.EgammaIsolationProducers.egammaElectronTkRelIsolation_cfi
egammaTrackerIsolationLoose = EgammaAnalysis.EgammaIsolationProducers.egammaElectronTkRelIsolation_cfi.egammaElectronTkRelIsolation.clone()
egammaTrackerIsolationLoose.intRadius = 0.015
egammaTrackerIsolationLoose.extRadius = 0.2
egammaTrackerIsolationLoosemaxVtxDist = 0.2

# not used in preselection
import EgammaAnalysis.EgammaIsolationProducers.egammaTowerIsolation_cfi
egammaCaloIsolationLoose = EgammaAnalysis.EgammaIsolationProducers.egammaTowerIsolation_cfi.egammaTowerIsolation.clone()
egammaCaloIsolationLoose.etMin = 0.0
egammaCaloIsolationLoose.intRadius = 0.15
egammaCaloIsolationLoose.extRadius = 0.30
egammaCaloIsolationLoose.absolut = False

HWWElectronIsolationSequence = cms.Sequence( egammaTrackerIsolationLoose + egammaCaloIsolationLoose )


import FWCore.ParameterSet.Config as cms

process = cms.Process("addMVAid")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration/StandardSequences/MagneticField_38T_cff")
process.load("Configuration/StandardSequences/FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.Services_cff")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.MessageLogger.cerr.FwkReport.reportEvery = 1


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
                                      '/store/relval/CMSSW_7_2_0/RelValZEE_13/GEN-SIM-RECO/PRE_LS172_V15-v2/00000/32D0DE7C-C159-E411-ABE4-0025905B85D0.root'
    )
)

process.GlobalTag.globaltag = 'PRE_LS172_V15::All'

process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring(
                                                                      'drop *',
                                                                      'keep *_*_*_addMVAid'),
                               fileName = cms.untracked.string('testRECOouput.root')
                               )


process.exampleAnalyzer = cms.EDAnalyzer('ExampleElectronMVAid',
            electronsCollection       	= cms.InputTag("gedGsfElectrons","","RECO"),
            MVAId                       = cms.InputTag("mvaNonTrigV050nsCSA14","","addMVAid"),
            trigMap                     = cms.InputTag("egmGsfElectronIDs:cutBasedElectronTrigID-CSA14-V0"),
#            trigMap                       = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID_CSA14_PU20bx25_V0_standalone_tight"),
            outputFile		        = cms.string("ElecMVAtree.root")
                                                            )






process.load("EgammaAnalysis.ElectronTools.electronIdMVAProducer_CSA14_cfi")
process.load("RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cff")

process.p = cms.Path(process.egmGsfElectronIDSequence + process.mvaTrigV050nsCSA14+process.mvaNonTrigV050nsCSA14+process.mvaNonTrigV025nsCSA14+process.exampleAnalyzer)

#process.outpath = cms.EndPath(process.out)

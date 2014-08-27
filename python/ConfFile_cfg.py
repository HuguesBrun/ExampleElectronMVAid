import FWCore.ParameterSet.Config as cms

process = cms.Process("addMVAid")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration/StandardSequences/MagneticField_38T_cff")
process.load("Configuration/StandardSequences/FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.Services_cff")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(50) )

process.MessageLogger.cerr.FwkReport.reportEvery = 1


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
                                      '/store/relval/CMSSW_7_0_0/RelValTTbar_13/GEN-SIM-RECO/PU50ns_POSTLS170_V4-v2/00000/265B9219-FF98-E311-BF4A-02163E00EA95.root'
    )
)

process.GlobalTag.globaltag = 'POSTLS170_V5::All'

process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring(
                                                                      'drop *',
                                                                      'keep *_*_*_addMVAid'),
                               fileName = cms.untracked.string('testRECOouput.root')
                               )


process.exampleAnalyzer = cms.EDAnalyzer('ExampleElectronMVAid',
            electronsCollection       	= cms.InputTag("gedGsfElectrons","","RECO"),
            MVAId                       = cms.InputTag("mvaTrigV050nsCSA14","","addMVAid"),
            outputFile		        = cms.string("ElecMVAtree.root")
                                                            )






process.load("EgammaAnalysis.ElectronTools.electronIdMVAProducer_CSA14_cfi")
process.p = cms.Path(process.mvaTrigV050nsCSA14+process.exampleAnalyzer)

#process.outpath = cms.EndPath(process.out)

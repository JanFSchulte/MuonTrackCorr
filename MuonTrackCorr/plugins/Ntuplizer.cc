#ifndef NTUPLIZER_H
#define NTUPLIZER_H


#include <cmath>

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefVector.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/L1Trigger/interface/Muon.h"
#include "DataFormats/L1TrackTrigger/interface/TTTrack.h"
#include "DataFormats/L1TrackTrigger/interface/TTTypes.h"
#include "DataFormats/L1TMuon/interface/EMTFTrack.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenStatusFlags.h"

//#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticle.h"
//#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticleFwd.h"

#include "L1Trigger/L1TMuon/interface/MicroGMTConfiguration.h"
//#include "SimTracker/TrackTriggerAssociation/interface/TTTrackAssociationMap.h"

#include "DataFormats/L1TCorrelator/interface/TkMuon.h"
#include "DataFormats/L1TCorrelator/interface/TkMuonFwd.h"
#include "DataFormats/L1TMuonPhase2/interface/TrackerMuon.h"
#include "DataFormats/L1TMuonPhase2/interface/MuonStub.h"

#include "SimTracker/TrackTriggerAssociation/interface/TTTrackAssociationMap.h"

#include "TTree.h"
#include "L1Trigger/L1TMuonEndCapPhase2/interface/EMTFTypes.h"

#include "MuonTrackCorr/MuonTrackCorr/interface/SubsystemMCTruth.h"

using namespace edm;
using namespace l1t;
using namespace reco;

// From L1Trigger/L1TMuonEndCap/interface/MuonTriggerPrimitive.h
class TriggerPrimitive {
public:
  enum subsystem_type{kDT,kCSC,kRPC,kGEM,kME0,kNSubsystems};
};

class Ntuplizer : public edm::one::EDAnalyzer<edm::one::SharedResources> {
    public:

        typedef TTTrack< Ref_Phase2TrackerDigi_ >  L1TTTrackType;
        typedef std::vector< L1TTTrackType >       L1TTTrackCollectionType;
        typedef std::vector< GenParticle >         GenParticleCollection;

        explicit Ntuplizer(const edm::ParameterSet&);
        virtual ~Ntuplizer();

    private:
        //----edm control---
        virtual void beginJob() ;
        virtual void beginRun(edm::Run const&, edm::EventSetup const&);
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob();
        virtual void endRun(edm::Run const&, edm::EventSetup const&);
        void initialize();

        // const edm::EDGetTokenT< MuonBxCollection > muTokenPos;
        // const edm::EDGetTokenT< MuonBxCollection > muTokenNeg;
        const edm::EDGetTokenT< l1t::phase2::EMTFTrackCollection > muToken;
        const edm::EDGetTokenT< l1t::phase2::EMTFHitCollection >   mu_hitToken;
        const edm::EDGetTokenT< std::vector< TTTrack< Ref_Phase2TrackerDigi_ > > > trackToken;
        const edm::EDGetTokenT< std::vector< reco::GenParticle > > genPartToken;
        const edm::EDGetTokenT< l1t::TrackerMuonCollection > tkMuToken;
        const edm::EDGetTokenT< MuonStubCollection > tkMuStubToken;
        const edm::EDGetTokenT< l1t::RegionalMuonCandBxCollection > muBarrelToken;
        const edm::EDGetTokenT< l1t::RegionalMuonCandBxCollection > muOvrlapToken;
        const edm::EDGetTokenT< TTTrackAssociationMap< Ref_Phase2TrackerDigi_ > > trackTruthToken;

        edm::EDGetTokenT<TrackingParticleCollection> trk_part_token_;
        SubsystemMCTruth subsystem_mc_truth_;

        const static int nTrkPars = 4; // number of parameters in the trk fit -- eventually to be made configurable

        //
        bool save_all_trks_;
        bool prompt_mu_only_;
        bool mu_from_tau_only_;
        bool save_tau_3mu_;
        //

        //-----output---
        TTree *tree_;

        unsigned int n_EMTF_mu_;
        std::vector<float> EMTF_mu_pt_;
        std::vector<float> EMTF_mu_eta_;
        std::vector<float> EMTF_mu_phi_;
        std::vector<int>   EMTF_mu_charge_;
        std::vector<int>   EMTF_mu_endcap_;
        std::vector<int>   EMTF_mu_sector_;
        std::vector<int>   EMTF_mu_bx_;

        unsigned int n_barrel_mu_;
        std::vector<float> barrel_mu_pt_;
        std::vector<float> barrel_mu_eta_;
        std::vector<float> barrel_mu_phi_;
        std::vector<int>   barrel_mu_charge_;
        std::vector<int>   barrel_mu_qual_;

        unsigned int n_ovrlap_mu_;
        std::vector<float> ovrlap_mu_pt_;
        std::vector<float> ovrlap_mu_eta_;
        std::vector<float> ovrlap_mu_phi_;
        std::vector<int>   ovrlap_mu_charge_;
        std::vector<int>   ovrlap_mu_qual_;

        unsigned int n_L1TT_trk_;
        std::vector<float> L1TT_trk_pt_;
        std::vector<float> L1TT_trk_eta_;
        std::vector<float> L1TT_trk_phi_;
        std::vector<int>   L1TT_trk_charge_;
        std::vector<float> L1TT_trk_p_;
        std::vector<float> L1TT_trk_z_;
        std::vector<float> L1TT_trk_chi2_;
        std::vector<int>   L1TT_trk_nstubs_;
        std::vector<int>   L1TT_trk_gen_qual_;
        std::vector<int>   L1TT_trk_gen_TP_ID_;
        std::vector<float> L1TT_trk_gen_TP_pt_;
        std::vector<float> L1TT_trk_gen_TP_eta_;
        std::vector<float> L1TT_trk_gen_TP_phi_;
        std::vector<float> L1TT_trk_gen_TP_m_;

        unsigned int n_L1_TkMu_;
        std::vector<float> L1_TkMu_gmt_pt_;
        std::vector<float> L1_TkMu_gmt_eta_;
        std::vector<float> L1_TkMu_gmt_phi_;
        std::vector<int>   L1_TkMu_gmt_dz_;
        std::vector<int>   L1_TkMu_gmt_dxy_;
        std::vector<int>   L1_TkMu_gmt_charge_;
        std::vector<int>   L1_TkMu_charge_;
        std::vector<float> L1_TkMu_p_;
        std::vector<float> L1_TkMu_z_;
        std::vector<float> L1_TkMu_chi2_;
        std::vector<int>   L1_TkMu_nstubs_;
        std::vector<int>   L1_TkMu_mudetID_;
        std::vector<int>   L1_TkMu_gen_qual_;
        std::vector<int>   L1_TkMu_gen_TP_ID_;
        std::vector<float> L1_TkMu_gen_TP_pt_;
        std::vector<float> L1_TkMu_gen_TP_eta_;
        std::vector<float> L1_TkMu_gen_TP_phi_;
        std::vector<float> L1_TkMu_gen_TP_m_;



        unsigned int n_L1_MuStub_;
        std::vector<float> L1_MuStub_eta1_; 
        std::vector<float> L1_MuStub_eta2_; 
        std::vector<float> L1_MuStub_phi_; 
        std::vector<float> L1_MuStub_phiBend_; // bending angle  only in barrel for now
        std::vector<int> L1_MuStub_quality_; 
        std::vector<int> L1_MuStub_etaQuality_; 
        std::vector<int> L1_MuStub_id_; // stub id in case of more stubs per chamber
        std::vector<int> L1_MuStub_bx_;
        std::vector<int> L1_MuStub_etaRegion_; //In the barrel this is wheel. In the endcap it is 6-ring
        std::vector<int> L1_MuStub_phiRegion_; //In the barrel it is sector. In the endcap it is chamber
        std::vector<int> L1_MuStub_station_;
        std::vector<int> L1_MuStub_tfLayer_;
        std::vector<int> L1_MuStub_type_;
        
        unsigned int n_gen_mu_;
        std::vector<float> gen_mu_pt_;
        std::vector<float> gen_mu_eta_;
        std::vector<float> gen_mu_phi_;
        std::vector<float> gen_mu_e_;
        std::vector<int>   gen_mu_charge_;
        std::vector<int>   gen_mu_gentauidx_;

        unsigned int n_gen_tau_;
        std::vector<float> gen_tau_pt_;
        std::vector<float> gen_tau_eta_;
        std::vector<float> gen_tau_phi_;
        std::vector<float> gen_tau_e_;
        std::vector<int>   gen_tau_charge_;

        // hits
        // format taken from : https://github.com/jiafulow/L1TMuonSimulationsMar2017/blob/master/Analyzers/plugins/NtupleMaker.cc
        unsigned int n_mu_hit_;
        std::vector<int16_t>  mu_hit_endcap_;
        std::vector<int16_t>  mu_hit_station_;
        std::vector<int16_t>  mu_hit_ring_;
        std::vector<int16_t>  mu_hit_sector_;
        std::vector<int16_t>  mu_hit_subsector_;
        std::vector<int16_t>  mu_hit_chamber_;
        std::vector<int16_t>  mu_hit_cscid_;
        std::vector<int16_t>  mu_hit_bx_;
        std::vector<int16_t>  mu_hit_type_;  // subsystem: DT=0,CSC=1,RPC=2,GEM=3
        std::vector<int16_t>  mu_hit_neighbor_;

        std::vector<int16_t>  mu_hit_strip_;
        std::vector<int16_t>  mu_hit_wire_;
        std::vector<int16_t>  mu_hit_roll_;
        std::vector<int16_t>  mu_hit_quality_;
        std::vector<int16_t>  mu_hit_pattern_;
        std::vector<int16_t>  mu_hit_bend_;
        std::vector<int16_t>  mu_hit_time_;
        std::vector<int16_t>  mu_hit_fr_;
        std::vector<int32_t>  mu_hit_emtf_phi_;
        std::vector<int32_t>  mu_hit_emtf_theta_;
        std::vector<int32_t>  mu_hit_truth_;

        std::vector<float>  mu_hit_global_phi_;
        std::vector<float>  mu_hit_global_theta_;
        std::vector<float>  mu_hit_global_eta_;
        std::vector<float>  mu_hit_global_r_;
        std::vector<float>  mu_hit_global_z_;
        std::vector<float>  mu_hit_global_time_;
};

void Ntuplizer::initialize()
{
    n_EMTF_mu_  = 0;
    EMTF_mu_pt_.clear();
    EMTF_mu_eta_.clear();
    EMTF_mu_phi_.clear();
    EMTF_mu_charge_.clear();
    EMTF_mu_endcap_.clear();
    EMTF_mu_sector_.clear();
    EMTF_mu_bx_.clear();

    n_barrel_mu_ = 0;
    barrel_mu_pt_.clear();
    barrel_mu_eta_.clear();
    barrel_mu_phi_.clear();
    barrel_mu_charge_.clear();
    barrel_mu_qual_.clear();

    n_ovrlap_mu_ = 0;
    ovrlap_mu_pt_.clear();
    ovrlap_mu_eta_.clear();
    ovrlap_mu_phi_.clear();
    ovrlap_mu_charge_.clear();
    ovrlap_mu_qual_.clear();


    n_L1TT_trk_ = 0;
    L1TT_trk_pt_.clear();
    L1TT_trk_eta_.clear();
    L1TT_trk_phi_.clear();
    L1TT_trk_charge_.clear();
    L1TT_trk_p_.clear();
    L1TT_trk_z_.clear();
    L1TT_trk_chi2_.clear();
    L1TT_trk_nstubs_.clear();
    L1TT_trk_gen_qual_.clear();
    L1TT_trk_gen_TP_ID_.clear();
    L1TT_trk_gen_TP_pt_.clear();
    L1TT_trk_gen_TP_eta_.clear();
    L1TT_trk_gen_TP_phi_.clear();
    L1TT_trk_gen_TP_m_.clear();

    n_L1_TkMu_ = 0;
    L1_TkMu_gmt_pt_.clear();
    L1_TkMu_gmt_eta_.clear();
    L1_TkMu_gmt_phi_.clear();
    L1_TkMu_gmt_dz_.clear();
    L1_TkMu_gmt_dxy_.clear();
    L1_TkMu_gmt_charge_.clear();
    L1_TkMu_charge_.clear();
    L1_TkMu_p_.clear();
    L1_TkMu_z_.clear();
    L1_TkMu_chi2_.clear();
    L1_TkMu_nstubs_.clear();
    L1_TkMu_mudetID_.clear();
    L1_TkMu_gen_qual_.clear();
    L1_TkMu_gen_TP_ID_.clear();
    L1_TkMu_gen_TP_pt_.clear();
    L1_TkMu_gen_TP_eta_.clear();
    L1_TkMu_gen_TP_phi_.clear();
    L1_TkMu_gen_TP_m_.clear();

    n_L1_MuStub_ = 0;
    L1_MuStub_eta1_.clear();
    L1_MuStub_eta2_.clear();
    L1_MuStub_phi_.clear();
    L1_MuStub_phiBend_.clear();
    L1_MuStub_quality_.clear();
    L1_MuStub_etaQuality_.clear();
    L1_MuStub_id_.clear();
    L1_MuStub_bx_.clear();
    L1_MuStub_etaRegion_.clear();
    L1_MuStub_phiRegion_.clear();
    L1_MuStub_station_.clear();
    L1_MuStub_tfLayer_.clear();
    L1_MuStub_type_.clear();


    n_gen_mu_   = 0;
    gen_mu_pt_.clear();
    gen_mu_eta_.clear();
    gen_mu_phi_.clear();
    gen_mu_e_.clear();
    gen_mu_charge_.clear();
    gen_mu_gentauidx_.clear();

    n_gen_tau_   = 0;
    gen_tau_pt_.clear();
    gen_tau_eta_.clear();
    gen_tau_phi_.clear();
    gen_tau_e_.clear();
    gen_tau_charge_.clear();

    n_mu_hit_ = 0;
    mu_hit_endcap_.clear();
    mu_hit_station_.clear();
    mu_hit_ring_.clear();
    mu_hit_sector_.clear();
    mu_hit_subsector_.clear();
    mu_hit_chamber_.clear();
    mu_hit_cscid_.clear();
    mu_hit_bx_.clear();
    mu_hit_type_.clear();
    mu_hit_neighbor_.clear();
    //
    mu_hit_strip_.clear();
    mu_hit_wire_.clear();
    mu_hit_roll_.clear();
    mu_hit_quality_.clear();
    mu_hit_pattern_.clear();
    mu_hit_bend_.clear();
    mu_hit_time_.clear();
    mu_hit_fr_.clear();
    mu_hit_emtf_phi_.clear();
    mu_hit_emtf_theta_.clear();
    mu_hit_truth_.clear();

    mu_hit_global_phi_.clear();
    mu_hit_global_theta_.clear();
    mu_hit_global_eta_.clear();
    mu_hit_global_r_.clear();
    mu_hit_global_z_.clear();
    mu_hit_global_time_.clear();

}

Ntuplizer::Ntuplizer(const edm::ParameterSet& iConfig):
    // muTokenPos(consumes< MuonBxCollection >           (iConfig.getParameter<edm::InputTag>("L1MuonPosInputTag"))),
    // muTokenNeg(consumes< MuonBxCollection >           (iConfig.getParameter<edm::InputTag>("L1MuonNegInputTag"))),
    muToken         (consumes< l1t::phase2::EMTFTrackCollection >                      (iConfig.getParameter<edm::InputTag>("L1MuonEMTFInputTag"))),
    mu_hitToken     (consumes< l1t::phase2::EMTFHitCollection >                        (iConfig.getParameter<edm::InputTag>("L1EMTFHitInputTag"))),
    trackToken      (consumes< L1TTTrackCollectionType >                  (iConfig.getParameter<edm::InputTag>("L1TrackInputTag"))),
    genPartToken    (consumes< GenParticleCollection >                    (iConfig.getParameter<edm::InputTag>("GenParticleInputTag"))),
    tkMuToken       (consumes< TrackerMuonCollection >               (iConfig.getParameter<edm::InputTag>("TkMuInputTag"))),
    tkMuStubToken   (consumes< MuonStubCollection >               (iConfig.getParameter<edm::InputTag>("MuStubInputTag"))),
    muBarrelToken   (consumes< RegionalMuonCandBxCollection >             (iConfig.getParameter<edm::InputTag>("L1BarrelMuonInputTag"))),
    muOvrlapToken   (consumes< RegionalMuonCandBxCollection >             (iConfig.getParameter<edm::InputTag>("L1OverlapMuonInputTag"))),
    trackTruthToken (consumes< TTTrackAssociationMap< Ref_Phase2TrackerDigi_ > >  (iConfig.getParameter<edm::InputTag>("L1TrackTruthInputTag"))),
    trk_part_token_(consumes<TrackingParticleCollection>(iConfig.getParameter<edm::InputTag>("TrkPartTag"))),
    subsystem_mc_truth_(iConfig, consumesCollector())
{
    save_all_trks_    =  iConfig.getParameter<bool>("save_all_L1TTT");
    prompt_mu_only_   =  iConfig.getParameter<bool>("prompt_mu_only");
    mu_from_tau_only_ =  iConfig.getParameter<bool>("mu_from_tau_only");
    save_tau_3mu_     =  iConfig.getParameter<bool>("save_tau_3mu");
    initialize();
}

Ntuplizer::~Ntuplizer()
{}

void Ntuplizer::beginJob()
{
    edm::Service<TFileService> fs;
    tree_ = fs -> make<TTree>("MuonTrackTree", "MuonTrackTree");

    tree_->Branch("n_EMTF_mu", &n_EMTF_mu_);
    tree_->Branch("EMTF_mu_pt", &EMTF_mu_pt_);
    tree_->Branch("EMTF_mu_eta", &EMTF_mu_eta_);
    tree_->Branch("EMTF_mu_phi", &EMTF_mu_phi_);
    tree_->Branch("EMTF_mu_charge", &EMTF_mu_charge_);
    tree_->Branch("EMTF_mu_endcap", &EMTF_mu_endcap_);
    tree_->Branch("EMTF_mu_sector", &EMTF_mu_sector_);
    tree_->Branch("EMTF_mu_bx", &EMTF_mu_bx_);

    tree_->Branch("n_barrel_mu",      &n_barrel_mu_);
    tree_->Branch("barrel_mu_pt",     &barrel_mu_pt_);
    tree_->Branch("barrel_mu_eta",    &barrel_mu_eta_);
    tree_->Branch("barrel_mu_phi",    &barrel_mu_phi_);
    tree_->Branch("barrel_mu_charge", &barrel_mu_charge_);
    tree_->Branch("barrel_mu_qual",   &barrel_mu_qual_);

    tree_->Branch("n_ovrlap_mu",      &n_ovrlap_mu_);
    tree_->Branch("ovrlap_mu_pt",     &ovrlap_mu_pt_);
    tree_->Branch("ovrlap_mu_eta",    &ovrlap_mu_eta_);
    tree_->Branch("ovrlap_mu_phi",    &ovrlap_mu_phi_);
    tree_->Branch("ovrlap_mu_charge", &ovrlap_mu_charge_);
    tree_->Branch("ovrlap_mu_qual",   &ovrlap_mu_qual_);

    // tree_->Branch("EMTF_mu_e", &EMTF_mu_e_);

    tree_->Branch("n_L1TT_trk", &n_L1TT_trk_);
    tree_->Branch("L1TT_trk_pt", &L1TT_trk_pt_);
    tree_->Branch("L1TT_trk_eta", &L1TT_trk_eta_);
    tree_->Branch("L1TT_trk_phi", &L1TT_trk_phi_);
    tree_->Branch("L1TT_trk_charge", &L1TT_trk_charge_);
    tree_->Branch("L1TT_trk_p", &L1TT_trk_p_);
    tree_->Branch("L1TT_trk_z", &L1TT_trk_z_);
    tree_->Branch("L1TT_trk_chi2", &L1TT_trk_chi2_);
    tree_->Branch("L1TT_trk_nstubs", &L1TT_trk_nstubs_);
    tree_->Branch("L1TT_trk_gen_qual",   &L1TT_trk_gen_qual_);
    tree_->Branch("L1TT_trk_gen_TP_ID",  &L1TT_trk_gen_TP_ID_);
    tree_->Branch("L1TT_trk_gen_TP_pt",  &L1TT_trk_gen_TP_pt_);
    tree_->Branch("L1TT_trk_gen_TP_eta", &L1TT_trk_gen_TP_eta_);
    tree_->Branch("L1TT_trk_gen_TP_phi", &L1TT_trk_gen_TP_phi_);
    tree_->Branch("L1TT_trk_gen_TP_m",   &L1TT_trk_gen_TP_m_);

    //
    tree_->Branch("n_L1_TkMu", &n_L1_TkMu_);
    tree_->Branch("L1_TkMu_gmt_pt", &L1_TkMu_gmt_pt_);
    tree_->Branch("L1_TkMu_gmt_eta", &L1_TkMu_gmt_eta_);
    tree_->Branch("L1_TkMu_gmt_phi", &L1_TkMu_gmt_phi_);
    tree_->Branch("L1_TkMu_gmt_dxy", &L1_TkMu_gmt_dxy_);
    tree_->Branch("L1_TkMu_gmt_dz", &L1_TkMu_gmt_dz_);
    tree_->Branch("L1_TkMu_gmt_charge", &L1_TkMu_gmt_charge_);
    tree_->Branch("L1_TkMu_charge", &L1_TkMu_charge_);
    tree_->Branch("L1_TkMu_p", &L1_TkMu_p_);
    tree_->Branch("L1_TkMu_z", &L1_TkMu_z_);
    tree_->Branch("L1_TkMu_chi2", &L1_TkMu_chi2_);
    tree_->Branch("L1_TkMu_nstubs", &L1_TkMu_nstubs_);
    tree_->Branch("L1_TkMu_mudetID", &L1_TkMu_mudetID_);
    tree_->Branch("L1_TkMu_gen_qual", &L1_TkMu_gen_qual_);
    tree_->Branch("L1_TkMu_gen_TP_ID", &L1_TkMu_gen_TP_ID_);
    tree_->Branch("L1_TkMu_gen_TP_pt", &L1_TkMu_gen_TP_pt_);
    tree_->Branch("L1_TkMu_gen_TP_eta", &L1_TkMu_gen_TP_eta_);
    tree_->Branch("L1_TkMu_gen_TP_phi", &L1_TkMu_gen_TP_phi_);
    tree_->Branch("L1_TkMu_gen_TP_m", &L1_TkMu_gen_TP_m_);

    tree_->Branch("n_L1_MuStub", &n_L1_MuStub_);
    tree_->Branch("L1_MuStub_eta1_", &L1_MuStub_eta1_);
    tree_->Branch("L1_MuStub_eta2_", &L1_MuStub_eta2_);
    tree_->Branch("L1_MuStub_phi_", &L1_MuStub_phi_);
    tree_->Branch("L1_MuStub_phiBend_", &L1_MuStub_phiBend_);
    tree_->Branch("L1_MuStub_quality_", &L1_MuStub_quality_);
    tree_->Branch("L1_MuStub_etaQuality_", &L1_MuStub_etaQuality_);
    tree_->Branch("L1_MuStub_id_", &L1_MuStub_id_);
    tree_->Branch("L1_MuStub_bx_", &L1_MuStub_bx_);
    tree_->Branch("L1_MuStub_etaRegion_", &L1_MuStub_etaRegion_);
    tree_->Branch("L1_MuStub_phiRegion_", &L1_MuStub_phiRegion_);
    tree_->Branch("L1_MuStub_station_", &L1_MuStub_station_);
    tree_->Branch("L1_MuStub_tfLayer_", &L1_MuStub_tfLayer_);
    tree_->Branch("L1_MuStub_type_", &L1_MuStub_type_);

    tree_->Branch("n_gen_mu", &n_gen_mu_);
    tree_->Branch("gen_mu_pt", &gen_mu_pt_);
    tree_->Branch("gen_mu_eta", &gen_mu_eta_);
    tree_->Branch("gen_mu_phi", &gen_mu_phi_);
    tree_->Branch("gen_mu_e", &gen_mu_e_);
    tree_->Branch("gen_mu_charge", &gen_mu_charge_);
    if (save_tau_3mu_)
        tree_->Branch("gen_mu_gentauidx", &gen_mu_gentauidx_);

    // hit info
    tree_->Branch("n_mu_hit", &n_mu_hit_);
    tree_->Branch("mu_hit_endcap", &mu_hit_endcap_);
    tree_->Branch("mu_hit_station", &mu_hit_station_);
    tree_->Branch("mu_hit_ring", &mu_hit_ring_);
    tree_->Branch("mu_hit_sector", &mu_hit_sector_);
    tree_->Branch("mu_hit_subsector", &mu_hit_subsector_);
    tree_->Branch("mu_hit_chamber", &mu_hit_chamber_);
    tree_->Branch("mu_hit_cscid", &mu_hit_cscid_);
    tree_->Branch("mu_hit_bx", &mu_hit_bx_);
    tree_->Branch("mu_hit_type", &mu_hit_type_);
    tree_->Branch("mu_hit_truth", &mu_hit_truth_);
    tree_->Branch("mu_hit_neighbor", &mu_hit_neighbor_);
    //
    tree_->Branch("mu_hit_strip", &mu_hit_strip_);
    tree_->Branch("mu_hit_wire", &mu_hit_wire_);
    tree_->Branch("mu_hit_roll", &mu_hit_roll_);
    tree_->Branch("mu_hit_quality", &mu_hit_quality_);
    tree_->Branch("mu_hit_pattern", &mu_hit_pattern_);
    tree_->Branch("mu_hit_bend", &mu_hit_bend_);
    tree_->Branch("mu_hit_time", &mu_hit_time_);
    tree_->Branch("mu_hit_fr", &mu_hit_fr_);
    tree_->Branch("mu_hit_emtf_phi", &mu_hit_emtf_phi_);
    tree_->Branch("mu_hit_emtf_theta", &mu_hit_emtf_theta_);

    tree_->Branch("mu_hit_global_phi", &mu_hit_global_phi_);
    tree_->Branch("mu_hit_global_theta", &mu_hit_global_theta_);
    tree_->Branch("mu_hit_global_eta", &mu_hit_global_eta_);
    tree_->Branch("mu_hit_global_r", &mu_hit_global_r_);
    tree_->Branch("mu_hit_global_z", &mu_hit_global_z_);
    tree_->Branch("mu_hit_global_time", &mu_hit_global_time_);

    //
    if (save_tau_3mu_)
    {
        tree_->Branch("n_gen_tau", &n_gen_tau_);
        tree_->Branch("gen_tau_pt", &gen_tau_pt_);
        tree_->Branch("gen_tau_eta", &gen_tau_eta_);
        tree_->Branch("gen_tau_phi", &gen_tau_phi_);
        tree_->Branch("gen_tau_e", &gen_tau_e_);
        tree_->Branch("gen_tau_charge", &gen_tau_charge_);   
    }
  
}

void Ntuplizer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{}

void Ntuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{


    subsystem_mc_truth_.update(iEvent, iSetup);


    auto get_time = [](const auto& hit) {
      float time = hit.globTime();
      return static_cast<int>(std::round(time*16/25));  // integer unit is 25ns/16 (4-bit)
    };

    auto isFront_detail = [](int subsystem, int station, int ring, int chamber, int subsector) {
      bool result = false;
  
      if (subsystem == TriggerPrimitive::kCSC) {
        bool isOverlapping = !(station == 1 && ring == 3);
        // not overlapping means back
        if(isOverlapping)
        {
          bool isEven = (chamber % 2 == 0);
          // odd chambers are bolted to the iron, which faces
          // forward in 1&2, backward in 3&4, so...
          result = (station < 3) ? isEven : !isEven;
        }
      } else if (subsystem == TriggerPrimitive::kRPC) {
        //// 10 degree rings have even subsectors in front
        //// 20 degree rings have odd subsectors in front
        //bool is_10degree = !((station == 3 || station == 4) && (ring == 1));
        //bool isEven = (subsector % 2 == 0);
        //result = (is_10degree) ? isEven : !isEven;
  
        // Use the equivalent CSC chamber F/R
        bool isEven = (chamber % 2 == 0);
        result = (station < 3) ? isEven : !isEven;
      } else if (subsystem == TriggerPrimitive::kGEM) {
        //
        result = (chamber % 2 == 0);
      } else if (subsystem == TriggerPrimitive::kME0) {
        //
        result = (chamber % 2 == 0);
      } else if (subsystem == TriggerPrimitive::kDT) {
        //
        result = (chamber % 2 == 0);
      }
      return result;
    };

    auto isFront = [&](const auto& hit) {
      return isFront_detail(hit.subsystem(), hit.station(), hit.ring(), hit.chamber(), hit.subsector());
    };

    // --------------------------------------------------------------

    initialize();

    // // the L1Muons objects - plus side
    // edm::Handle<MuonBxCollection> l1musPosH;
    // iEvent.getByToken(muTokenPos, l1musPosH);  
    // const MuonBxCollection& l1musPos = (*l1musPosH.product());

    // // the L1Muons objects - minus side
    // edm::Handle<MuonBxCollection> l1musNegH;
    // iEvent.getByToken(muTokenNeg, l1musNegH);  
    // const MuonBxCollection& l1musNeg = (*l1musNegH.product());

    // the L1Muons objects - directly frtom EMTF
    edm::Handle<l1t::phase2::EMTFTrackCollection> l1musH;
    iEvent.getByToken(muToken, l1musH);  
    const l1t::phase2::EMTFTrackCollection& l1mus = (*l1musH.product());

    edm::Handle<l1t::phase2::EMTFHitCollection> l1muhitsH;
    iEvent.getByToken(mu_hitToken, l1muhitsH);  
    const l1t::phase2::EMTFHitCollection& l1muhits = (*l1muhitsH.product());


    edm::Handle<RegionalMuonCandBxCollection> l1musBarrelH;
    iEvent.getByToken(muBarrelToken, l1musBarrelH);  
    const RegionalMuonCandBxCollection& l1musBarrel = (*l1musBarrelH.product());

    edm::Handle<RegionalMuonCandBxCollection> l1musOvrlapH;
    iEvent.getByToken(muOvrlapToken, l1musOvrlapH);  
    const RegionalMuonCandBxCollection& l1musOvrlap = (*l1musOvrlapH.product());

    // the L1Tracks
    edm::Handle<L1TTTrackCollectionType> l1tksH;
    iEvent.getByToken(trackToken, l1tksH);
    const L1TTTrackCollectionType& l1tks = (*l1tksH.product());

    edm::Handle<TTTrackAssociationMap< Ref_Phase2TrackerDigi_ > > l1tksTruthH;
    iEvent.getByToken(trackTruthToken, l1tksTruthH);
    const auto &l1tkstruth = (*l1tksTruthH.product());

    // the gen particles
    edm::Handle<GenParticleCollection> genpartH;
    iEvent.getByToken(genPartToken, genpartH);
    const GenParticleCollection& genparts = (*genpartH.product());

    // the mu+trk objects
    edm::Handle<TrackerMuonCollection> tkmuH;
    iEvent.getByToken(tkMuToken, tkmuH);
    const TrackerMuonCollection& tkmus = (*tkmuH.product());

    edm::Handle<MuonStubCollection> tkmustubH;
    iEvent.getByToken(tkMuStubToken, tkmustubH);
    const MuonStubCollection& tkmustubs = (*tkmustubH.product());

    // ------------------------------------------------------

    // for the  tau->3mu cross-linking
    std::vector<int> selected_muons;
    std::vector<int> selected_taus;

    for (auto genpartit = genparts.begin(); genpartit != genparts.end(); ++genpartit)
    {
        int apdgid = abs(genpartit->pdgId());
        // if (apdgid != 13 && (apdgid != 15 && save_tau_3mu_) )
        //     continue;
        if (apdgid != 13 && apdgid != 15)
            continue;

        // save the muons
        if (apdgid == 13)
        {

            if (prompt_mu_only_) // to be activated in the cfg. On only if interested in mu gun on Zmumu, off for muons in bjets
            {
                // keep only hard scatter stuff (processing Z->mumu)
                if (!genpartit->statusFlags().isPrompt())      continue;
                // if (!genpartit->statusFlags().isHardProcess()) continue; // do not apply this (missing muons in Z->mumu)
                if (!genpartit->statusFlags().isLastCopy())    continue;
            }

            if (mu_from_tau_only_) // to be activated in the cfg. On only if interested in mu from tau->3mu samples
            {
                if (abs(genpartit->mother(0)->pdgId()) != 15)      continue;
            }

            ++n_gen_mu_;
            gen_mu_pt_.push_back(genpartit->pt());
            gen_mu_eta_.push_back(genpartit->eta());
            gen_mu_phi_.push_back(genpartit->phi());
            gen_mu_e_.push_back(genpartit->energy());
            gen_mu_charge_.push_back(genpartit->charge());
            // cout << genpartit->status() << endl;
            // the single mu sample has 2 muons, back-to-back

            selected_muons.push_back(std::distance(genparts.begin(), genpartit));
        }

        // save the taus
        if (apdgid == 15 && save_tau_3mu_)
        {
            // only tau -> 3mu
            if (genpartit->numberOfDaughters() != 3)
                continue;

            int apdgiddau1 = abs(genpartit->daughter(0)->pdgId());
            int apdgiddau2 = abs(genpartit->daughter(1)->pdgId());
            int apdgiddau3 = abs(genpartit->daughter(2)->pdgId());

            bool istau3mu = (apdgiddau1 == 13 && apdgiddau2 == 13 && apdgiddau3 == 13);
            if (istau3mu)
            {
                ++n_gen_tau_;
                gen_tau_pt_.push_back(genpartit->pt());
                gen_tau_eta_.push_back(genpartit->eta());
                gen_tau_phi_.push_back(genpartit->phi());
                gen_tau_e_.push_back(genpartit->energy());
                gen_tau_charge_.push_back(genpartit->charge());

                selected_taus.push_back(std::distance(genparts.begin(), genpartit));
            }
        }
    }

    // now cross-link mu candidates and taus
    if (save_tau_3mu_)
    {
        for (uint igenmu = 0; igenmu < selected_muons.size(); ++igenmu)
        {
            int idxgenmu = selected_muons.at(igenmu);
            auto muonit = genparts.begin() + idxgenmu;
            auto muonmotherit = muonit->mother(0);

            int itau_match = -1;
            for (uint igentau = 0; igentau < selected_taus.size(); ++igentau)
            {
                int idxgentau = selected_taus.at(igentau);
                auto tauit = genparts.begin() + idxgentau;

                // if the mu mother is the tau, save it index
                if (&(*muonmotherit) == &(*tauit))
                {
                    itau_match = igentau;
                    break;
                }
            }
            // store the idx - will point to the position in the tau vector
            gen_mu_gentauidx_.push_back(itau_match);            
        }
    }


    n_L1TT_trk_ = l1tks.size();

    const auto &truthmap = l1tkstruth.getTTTrackToTrackingParticleMap();
    for (auto l1trkit = l1tks.begin(); l1trkit != l1tks.end(); ++l1trkit)
    {
        int itrk = std::distance(l1tks.begin(), l1trkit);
        ++n_L1TT_trk_;
        if (save_all_trks_) // keep the branch structure but do not fill vectors
        {
            L1TT_trk_pt_ .push_back(l1trkit->momentum().perp());
            L1TT_trk_eta_.push_back(l1trkit->momentum().eta());
            L1TT_trk_phi_.push_back(l1trkit->momentum().phi());
            int l1tttq = (l1trkit->rInv() > 0 ? 1 : -1);
            L1TT_trk_charge_.push_back(l1tttq);
            L1TT_trk_p_     .push_back(l1trkit->momentum().mag());
            L1TT_trk_z_     .push_back(l1trkit->POCA().z());
            L1TT_trk_chi2_  .push_back(l1trkit->chi2());
            L1TT_trk_nstubs_.push_back(l1trkit->getStubRefs().size());

            const edm::Ptr<L1TTTrackType> trkEdmPtr(l1tksH, itrk);

            int trkgenqual = 0;
            if (l1tkstruth.isGenuine(trkEdmPtr))
               trkgenqual |= (1 << 0);

            if (l1tkstruth.isCombinatoric(trkEdmPtr))
               trkgenqual |= (1 << 1);

            if (l1tkstruth.isUnknown(trkEdmPtr))
               trkgenqual |= (1 << 2);

            L1TT_trk_gen_qual_.push_back(trkgenqual);


            bool has_matched_trk = (truthmap.find(trkEdmPtr) != truthmap.end());

            int   gen_TP_ID   = -999;
            float gen_TP_pt   = -999.; 
            float gen_TP_eta  = -999.;  
            float gen_TP_phi  = -999.;  
            float gen_TP_m    = -999.; 
            
            if (has_matched_trk)
            {
                const auto matchedTP = truthmap.at(trkEdmPtr);
                gen_TP_ID  = matchedTP->pdgId() ;
                gen_TP_pt  = matchedTP->p4().pt() ;
                gen_TP_eta = matchedTP->p4().eta() ;
                gen_TP_phi = matchedTP->p4().phi() ;
                gen_TP_m   = matchedTP->p4().mass() ;
            }

            L1TT_trk_gen_TP_ID_  . push_back (gen_TP_ID);
            L1TT_trk_gen_TP_pt_  . push_back (gen_TP_pt);
            L1TT_trk_gen_TP_eta_ . push_back (gen_TP_eta);
            L1TT_trk_gen_TP_phi_ . push_back (gen_TP_phi);
            L1TT_trk_gen_TP_m_   . push_back (gen_TP_m);

        }

    }

    for (auto l1muit = l1mus.begin(); l1muit != l1mus.end(); ++l1muit)
    {

        if (l1muit->bx() != 0)
            continue;
        ++n_EMTF_mu_;
        EMTF_mu_pt_.push_back(l1muit->emtfPt());
        EMTF_mu_eta_.push_back(l1muit->modelEta());
        EMTF_mu_phi_.push_back(l1muit->modelPhi());
        EMTF_mu_charge_.push_back(l1muit->emtfQ());
        EMTF_mu_endcap_.push_back(l1muit->endcap());
        EMTF_mu_sector_.push_back(l1muit->sector());
        EMTF_mu_bx_.push_back(l1muit->bx());
    }

    // barrel muons
    // NB: convertions taken from https://github.com/cms-l1t-offline/cmssw/blob/l1t-phase2-v2.22.1-CMSSW_10_6_1_patch2/L1Trigger/L1TTrackMatch/plugins/L1TkMuonProducer.cc
    for (auto l1mubarrit = l1musBarrel.begin(0); l1mubarrit != l1musBarrel.end(0); ++l1mubarrit)
    {
        ++n_barrel_mu_;
        
        barrel_mu_pt_.push_back(l1mubarrit->hwPt() * 0.5);
        barrel_mu_eta_.push_back(l1mubarrit->hwEta() * 0.010875);
        float this_l1mu_phi = MicroGMTConfiguration::calcGlobalPhi( l1mubarrit->hwPhi(), l1mubarrit->trackFinderType(), l1mubarrit->processor() )*2*M_PI/576.;
        barrel_mu_phi_.push_back(this_l1mu_phi);
        int hwsign = l1mubarrit->hwSign();
        int charge = (hwsign == 0 ? 1 : -1); // charge sign bit (charge = (-1)^(sign))
        barrel_mu_charge_.push_back(charge);
        barrel_mu_qual_.push_back(l1mubarrit->hwQual());
    }

    // overlap muons
    for (auto l1muovrlit = l1musOvrlap.begin(0); l1muovrlit != l1musOvrlap.end(0); ++l1muovrlit)
    {
        ++n_ovrlap_mu_;
        
        ovrlap_mu_pt_.push_back(l1muovrlit->hwPt() * 0.5);
        ovrlap_mu_eta_.push_back(l1muovrlit->hwEta() * 0.010875);
        float this_l1mu_phi = MicroGMTConfiguration::calcGlobalPhi( l1muovrlit->hwPhi(), l1muovrlit->trackFinderType(), l1muovrlit->processor() )*2*M_PI/576.;
        ovrlap_mu_phi_.push_back(this_l1mu_phi);
        int hwsign = l1muovrlit->hwSign();
        int charge =  (hwsign == 0 ? 1 : -1); // charge sign bit (charge = (-1)^(sign))
        ovrlap_mu_charge_.push_back(charge);
        ovrlap_mu_qual_.push_back(l1muovrlit->hwQual());
    }

    /// mu + trks
    // cout << "--- this event has " << tkmus.size() << " muons" << endl;
    for (const auto& tkmu : tkmus)
    {
        ++n_L1_TkMu_;
        L1_TkMu_gmt_pt_  . push_back(tkmu.phPt());
        L1_TkMu_gmt_eta_ . push_back(tkmu.phEta());
        L1_TkMu_gmt_phi_ . push_back(tkmu.phPhi());
        L1_TkMu_gmt_charge_ . push_back(tkmu.phCharge());
        L1_TkMu_gmt_dz_ . push_back(tkmu.phZ0());
        L1_TkMu_gmt_dxy_ . push_back(tkmu.phD0());

        // get the associated track and get properties
        // const edm::Ptr< L1TTTrackType >& getTrkPtr() const
        auto matchedTrk =  tkmu.trkPtr();
        int l1tttq = (matchedTrk->rInv() > 0 ? 1 : -1);
        L1_TkMu_charge_  . push_back(l1tttq);
        L1_TkMu_p_       . push_back(matchedTrk->momentum().mag());
        L1_TkMu_z_       . push_back(matchedTrk->POCA().z());
        L1_TkMu_chi2_    . push_back(matchedTrk->chi2());
        L1_TkMu_nstubs_  . push_back(matchedTrk->getStubRefs().size());


        int trkgenqual = 0;
        if (l1tkstruth.isGenuine(matchedTrk))
           trkgenqual |= (1 << 0);

        if (l1tkstruth.isCombinatoric(matchedTrk))
           trkgenqual |= (1 << 1);

        if (l1tkstruth.isUnknown(matchedTrk))
           trkgenqual |= (1 << 2);

        L1_TkMu_gen_qual_.push_back(trkgenqual);


        bool has_matched_trk = (truthmap.find(matchedTrk) != truthmap.end());
        int   gen_TP_ID   = -999;
        float gen_TP_pt   = -999.; 
        float gen_TP_eta  = -999.;  
        float gen_TP_phi  = -999.;  
        float gen_TP_m    = -999.; 
        
        if (has_matched_trk)
        {
            const auto matchedTP = truthmap.at(matchedTrk);
            gen_TP_ID  = matchedTP->pdgId() ;
            gen_TP_pt  = matchedTP->p4().pt() ;
            gen_TP_eta = matchedTP->p4().eta() ;
            gen_TP_phi = matchedTP->p4().phi() ;
            gen_TP_m   = matchedTP->p4().mass() ;
        }

        L1_TkMu_gen_TP_ID_  . push_back (gen_TP_ID);
        L1_TkMu_gen_TP_pt_  . push_back (gen_TP_pt);
        L1_TkMu_gen_TP_eta_ . push_back (gen_TP_eta);
        L1_TkMu_gen_TP_phi_ . push_back (gen_TP_phi);
        L1_TkMu_gen_TP_m_   . push_back (gen_TP_m);

    }

    /// trk + stubs
    for (const auto& tkmustub : tkmustubs)
    {
        ++n_L1_MuStub_;
        L1_MuStub_eta1_ . push_back(tkmustub.offline_eta1());;
        L1_MuStub_eta2_ . push_back(tkmustub.offline_eta2());;
        L1_MuStub_phi_ . push_back(tkmustub.offline_coord1());;
        L1_MuStub_phiBend_ . push_back(tkmustub.offline_coord2());;
        L1_MuStub_quality_ . push_back(tkmustub.quality());;
        L1_MuStub_etaQuality_ . push_back(tkmustub.etaQuality());;
        L1_MuStub_id_ . push_back(tkmustub.id());;
        L1_MuStub_bx_ . push_back(tkmustub.bxNum());;
        L1_MuStub_etaRegion_ . push_back(tkmustub.etaRegion());;
        L1_MuStub_phiRegion_ . push_back(tkmustub.phiRegion());;
        L1_MuStub_station_ . push_back(tkmustub.depthRegion());;
        L1_MuStub_tfLayer_ . push_back(tkmustub.tfLayer());;
        L1_MuStub_type_ . push_back(tkmustub.type());;

    }


    auto trk_part_col_handle = iEvent.getHandle(trk_part_token_);
    auto trk_part_col        = trk_part_col_handle.product();

    /// hits
    for (const auto& hit : l1muhits)
    {
        const auto [sim_tp1, sim_tp2] = subsystem_mc_truth_.findTrackingParticlesFromEMTFHit(hit);
        ++n_mu_hit_;
        mu_hit_endcap_     . push_back(hit.endcap());
        mu_hit_station_    . push_back(hit.station());
        mu_hit_ring_       . push_back(hit.ring());
        mu_hit_sector_     . push_back(hit.sector());
        mu_hit_subsector_  . push_back(hit.subsector());
        mu_hit_chamber_    . push_back(hit.chamber());
        mu_hit_cscid_      . push_back(hit.cscId());
        mu_hit_bx_         . push_back(hit.bx());
        mu_hit_type_       . push_back(hit.subsystem());
        mu_hit_neighbor_   . push_back(hit.flagNeighbor());
        
        mu_hit_strip_      . push_back(hit.strip());
        mu_hit_wire_       . push_back(hit.wire1());
        mu_hit_roll_       . push_back(hit.roll());
        mu_hit_quality_    . push_back(hit.quality());
        mu_hit_pattern_    . push_back(hit.pattern());
        mu_hit_bend_       . push_back(hit.bend());
        mu_hit_time_       . push_back(get_time(hit));     // modified
        mu_hit_fr_         . push_back(isFront(hit));
        mu_hit_emtf_phi_   . push_back(hit.emtfPhi());
        mu_hit_emtf_theta_ . push_back(hit.emtfTheta1());
        
        mu_hit_global_phi_ . push_back(hit.globPhi());
        mu_hit_global_theta_ . push_back(hit.globTheta());
        mu_hit_global_eta_ . push_back(-log(tan(hit.globTheta()*M_PI/(2*180))));
        mu_hit_global_r_ . push_back(hit.globPerp());
        mu_hit_global_z_ . push_back(hit.globZ());
        mu_hit_global_time_ . push_back(hit.globTime());

        if (sim_tp1 >=0 and sim_tp2 < 0){
           TrackingParticle tp = trk_part_col->at(sim_tp1);
           TrackingParticle::genp_iterator j, b = tp.genParticle_begin(), e = tp.genParticle_end();
           bool isMu = false;
           bool isFromTau3Mu = false;
           for (j = b; j != e; ++j) {
               const reco::GenParticle *p = j->get();
               if (abs(p -> pdgId()) == 13) isMu = true;
               if (abs(p -> mother(0) -> pdgId()) == 15 && abs(p -> pdgId()) == 13) isFromTau3Mu = true;
           }
           if (isFromTau3Mu) mu_hit_truth_ . push_back(3);
           else if (isMu) mu_hit_truth_ . push_back(2);
           else mu_hit_truth_ . push_back(1);
        }
        else if (sim_tp1 < 0 and sim_tp2 >= 0){
           TrackingParticle tp = trk_part_col->at(sim_tp2);
           TrackingParticle::genp_iterator j, b = tp.genParticle_begin(), e = tp.genParticle_end();
           bool isMu = false;
           bool isFromTau3Mu = false;
           for (j = b; j != e; ++j) {
               const reco::GenParticle *p = j->get();
               if (abs(p -> pdgId()) == 13) isMu = true;
               if (abs(p -> mother(0) -> pdgId()) == 15 && abs(p -> pdgId()) == 13) isFromTau3Mu = true;
           }
           if (isFromTau3Mu) mu_hit_truth_ . push_back(3);
           else if (isMu) mu_hit_truth_ . push_back(2);
           else mu_hit_truth_ . push_back(1);
        }
        else if (sim_tp1 >=0 and sim_tp2 >=0){
           TrackingParticle tp1 = trk_part_col->at(sim_tp1);
           TrackingParticle tp2 = trk_part_col->at(sim_tp2);
           TrackingParticle::genp_iterator j1, b1 = tp1.genParticle_begin(), e1 = tp1.genParticle_end();
           TrackingParticle::genp_iterator j2, b2 = tp2.genParticle_begin(), e2 = tp2.genParticle_end();
           bool isMu = false;
           bool isFromTau3Mu = false;
           for (j1 = b1; j1 != e1; ++j1) {
               const reco::GenParticle *p = j1->get();
               if (abs(p -> pdgId()) == 13) isMu = true;
               if (abs(p -> mother(0) -> pdgId()) == 15 && abs(p -> pdgId()) == 13) isFromTau3Mu = true;
           }
           for (j2 = b2; j2 != e2; ++j2) {
               const reco::GenParticle *p = j2->get();
               if (abs(p -> pdgId()) == 13) isMu = true;
               if (abs(p -> mother(0) -> pdgId()) == 15 && abs(p -> pdgId()) == 13) isFromTau3Mu = true;
           }
           if (isFromTau3Mu) mu_hit_truth_ . push_back(3);
           else if (isMu) mu_hit_truth_ . push_back(2);
           else mu_hit_truth_ . push_back(1);
        }
        else mu_hit_truth_ . push_back(0);

    }

    tree_->Fill();
}

void Ntuplizer::endJob()
{}

void Ntuplizer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{}


#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(Ntuplizer);

#endif // NTUPLIZER_H

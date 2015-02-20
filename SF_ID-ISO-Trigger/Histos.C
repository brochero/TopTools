void Histos(){

  //TFile *MuSF = TFile::Open("muonEffTop2D.root"); // Mu
  //TFile *MuSF = TFile::Open("ElecSF_tight_inclerrs.root"); // EG
  //TFile *MuSF = TFile::Open("triggerSummary_ee_tightleps.root"); // Trigger ee
  TFile *MuSF = TFile::Open("triggerSummary_emu_tightleps.root"); // Trigger emu
  //TFile *MuSF = TFile::Open("triggerSummary_mumu_tightleps.root"); // Trigger mumu

  TH2F *hmuSF;
  //hmuSF = (TH2F*) MuSF->Get("eff_pt_eta_fullwithtrackerr")->Clone("muSF"); // Mu
  //hmuSF = (TH2F*) MuSF->Get("GlobalSF")->Clone("muSF"); // EG
  hmuSF = (TH2F*) MuSF->Get("scalefactor_eta2d_with_syst")->Clone("muSF"); // Trigger

  int nbin_XpT  = hmuSF->GetNbinsX();
  int nbin_Yeta = hmuSF->GetNbinsY();

  cout << "pT bins= "  << nbin_XpT  << endl; 
  cout << "eta bins= " << nbin_Yeta << endl; 

  std::vector<float> vmuYEta; // muon Eta values
  std::vector<float> vmuXPt; // muon Pt values

  for(int nbx=1; nbx <= nbin_XpT; nbx++){
    cout <<  "bin " << nbx << " width pT= "   << hmuSF->GetXaxis()->GetBinWidth(nbx) 
	 << " starting at " << hmuSF->GetXaxis()->GetBinLowEdge(nbx) << endl;
  }

  for(int nby=1; nby <= nbin_Yeta; nby++){
    cout <<  "bin " << nby << " width eta = " << hmuSF->GetYaxis()->GetBinWidth(nby) 
	 << " starting at " << hmuSF->GetYaxis()->GetBinLowEdge(nby) << endl;
  }

  //int nbin=  hmuSF->GetBin(2,2);

  //GetBinContent(binmuEta+1,binmuPt+1)
  //GetBinError(binmuEta+1,binmuPt+1)


  // float hbinmuYeta[] = {-2.4 , -2.1 , -1.2 , -0.9 , 0.0 , 0.9 , 1.2 , 2.1 , 2.4}; // muon Eta values
  // float hbinmuXpT [] = {10, 20 , 25 , 30 , 35 , 40 , 50, 60 , 90, 140 , 300}; // muon Pt values

  // TH2F *GlobalSF;
  // GlobalSF    = new TH2F("GlobalSF","SF_{ID,ISO}^{#mu}(#eta,p_{t}) ",8,hbinmuYeta,10,hbinmuXpT);

  // for(int nbx=1; nbx <= 10; nbx++){
  //   for(int nby=1; nby <= 4; nby++){
   
  //     cout << "(" << nbx << ","<< nby << ") = " << hmuSF->GetBinContent (nbx,nby) << endl;

  //     GlobalSF->SetBinContent (nby,nbx,hmuSF->GetBinContent (nbx,nby));
  //     GlobalSF->SetBinError   (nby,nbx,hmuSF->GetBinError   (nbx,nby));

  //     GlobalSF->SetBinContent (9-nby,nbx,hmuSF->GetBinContent (nbx,nby));
  //     GlobalSF->SetBinError   (9-nby,nbx,hmuSF->GetBinError   (nbx,nby));

  //     cout << "(" << nby << ","<< nbx << ") = " << GlobalSF->GetBinContent (nby,nbx) << endl;

  //   }
  // }

  // TFile *target  = new TFile("Output_SFmu.root","RECREATE");
  // GlobalSF->Write();

  // target->Close();
}

#include <TGraphErrors.h>
#include <TF1.h>
#include <TMath.h>

#include <General.h>
#include <Routin_CF.h>

void Routin_CF() {

     Routin_CF("mumu","NPV");
     Routin_CF("mumu","NJets");
     Routin_CF("ee","NPV");
     Routin_CF("ee","NJets");

}

int Routin_CF(TString channel, TString plot){
  
  gStyle->SetPadRightMargin(0.13);
  gStyle->SetPadLeftMargin(0.13);
  
  TCanvas *c1 = new TCanvas("c1", "plots",400,400,800,600);
  c1->Divide(1,1);
  c1->SetFillColor(10);
  c1->SetFillStyle(4000);
  c1->SetBorderSize(2); 
  c1->SetLogy(0);

  // All MC
  TFile *f_mc   = TFile::Open("TopResults/h"+fl+"_AllMC.root");  
  // MC: DYJets + ZJets
  TFile *f_dy   = TFile::Open("TopResults/h"+fl+"_ZDY.root");
  // Data
  TFile *f_data = NULL;
  if ( channel == "mumu" ) {
       f_data = TFile::Open("TopResults/h"+fl+"_DataMu12.root");
  }
  else if ( channel == "ee" ) {
       f_data = TFile::Open("TopResults/h"+fl+"_DataEG12.root");
  }

  TString htitle  = "hDY_vs_" + plot + "_" + channel + "_dilepton";

  TH2F *All_MC  = (TH2F*) f_mc->Get(htitle);
  TH2F *DY_MC   = (TH2F*) f_dy->Get(htitle);
  TH2F *DY_Data = (TH2F*) f_data->Get(htitle);
 
  int npoint = DY_Data->GetNbinsY(); // NPV or NJets
   
  double Routin_Data[npoint];
  double Routin_MC[npoint];
  double NVarPlot[npoint];

  double RoutinErr_Data[npoint];
  double RoutinErr_MC[npoint];
  double NVarPlotErr[npoint];
  
  double controlRatio[npoint];
  double controlRatioErr[npoint];
  
  for(int biny=1; biny<DY_Data->GetNbinsY()+1; biny++){
    double num   = 0.;
    double denom = 0.;
    
    for(int binx=1; binx < (DY_Data->GetNbinsX()+1); binx++){
      int last_biny = biny+1;
      if(plot == "NJets") last_biny = (DY_Data->GetNbinsY()+1);

      for(int biny2=biny; biny2 < last_biny; biny2++){
	if( binx <= 76 || binx >= 106 )  num+= DY_Data->GetBinContent(binx, biny2);
	if( binx > 76 && binx <  106  )  denom+= DY_Data->GetBinContent(binx, biny2);
      }
    }

    Routin_Data[biny-1]    = num/denom;
    RoutinErr_Data[biny-1] = pow( pow((1/denom)*pow(num,0.5),2) +  pow((num/(denom*denom))*pow(denom, 0.5),2), 0.5);
    
    NVarPlot[biny-1] = (biny-1);
    if(num   == 0) Routin_MC[biny-1] = -1;
    if(denom == 0) Routin_MC[biny-1] = -1;
    if(denom == 0 || num   == 0) NVarPlot[biny-1] = -10;
    NVarPlotErr[biny-1] = 0.;
  }

  for(int biny=1; biny<All_MC->GetNbinsY()+1; biny++){
    double num   = 0;
    double denom = 0;
    
    double ntot=0;
    double nZ = 0;
    
    for(int binx=1; binx < (All_MC->GetNbinsX()+1); binx++){
       if( binx <= 76 || binx >= 106 )   num+= All_MC->GetBinContent(binx, biny);
       if( binx > 76 && binx <  106 )  denom+= All_MC->GetBinContent(binx, biny);
     
       ntot += All_MC->GetBinContent(binx, biny);
       nZ   += DY_MC->GetBinContent(binx, biny);
    }


    //cout << "num(MC)=" << num <<endl;
    //cout << "denom(MC)=" << denom <<endl;
    
    Routin_MC[biny-1] = num/denom;
    RoutinErr_MC[biny-1] = pow( pow((1/denom)*pow(num,0.5),2) +  pow((num/(denom*denom))*pow(denom, 0.5),2), 0.5);
    NVarPlot[biny-1] = (biny-1);
   
    controlRatio[biny-1]    = nZ/ntot;
    controlRatioErr[biny-1] =  pow(controlRatio[biny-1]*(1-controlRatio[biny-1])/ntot,0.5);
    
    if(num   == 0) Routin_MC[biny-1] = -1;
    if(denom == 0) Routin_MC[biny-1] = -1;
    if(denom == 0 || num   == 0) NVarPlot[biny-1] = -10;
    NVarPlotErr[biny-1] = 0;
  }

  if (plot == "NJets") {  // >= 2 jets
      cout << "Rout/in in Data = " << Routin_Data[2] << endl;
      cout << "Rout/in in MC   = " << Routin_MC[2] << endl;
      cout << "CF Rout/in      = " << Routin_Data[2]/Routin_MC[2] << " +/- " 
                                  << (Routin_Data[2]/Routin_MC[2]) * sqrt ( (RoutinErr_Data[2]/Routin_Data[2])*(RoutinErr_Data[2]/Routin_Data[2]) + 
                                                                            (RoutinErr_MC[2]/Routin_MC[2])*(RoutinErr_MC[2]/Routin_MC[2]) ) << endl;
  }
  if (plot == "NPV") { 
      double Mean_Routin_Data = 0.; 
      double Mean_Routin_MC = 0.; 
      double Err2_Mean_Routin_Data = 0.; 
      double Err2_Mean_Routin_MC = 0.; 
      for(int biny=1; biny<DY_Data->GetNbinsY()+1; biny++)  { 
          Mean_Routin_Data += Routin_Data[biny]; Err2_Mean_Routin_Data += RoutinErr_Data[biny]*RoutinErr_Data[biny]/(npoint*npoint); }
      for(int biny=1; biny<DY_MC->GetNbinsY()+1; biny++)  { 
          Mean_Routin_MC += Routin_MC[biny]; Err2_Mean_Routin_MC += RoutinErr_MC[biny]*RoutinErr_MC[biny]/(npoint*npoint); }
      cout << "Rout/in in Data = " << Mean_Routin_Data/npoint << endl;
      cout << "Rout/in in MC   = " << Mean_Routin_MC/npoint << endl;
      cout << "CF Rout/in      = " << Mean_Routin_Data/Mean_Routin_MC << " +/- " 
                                   << (Mean_Routin_Data/Mean_Routin_MC) * sqrt ( Err2_Mean_Routin_Data/(Mean_Routin_Data*Mean_Routin_Data) + 
                                      Err2_Mean_Routin_MC/(Mean_Routin_MC*Mean_Routin_MC) ) << endl;
  }

  TGraphErrors * theGraphData  = new TGraphErrors(npoint, NVarPlot, Routin_Data,   NVarPlotErr,   RoutinErr_Data);
  TGraphErrors * theGraphMC    = new TGraphErrors(npoint, NVarPlot, Routin_MC,     NVarPlotErr,   RoutinErr_MC);
  TGraphErrors * theGraphMC_SN = new TGraphErrors(npoint, NVarPlot, controlRatio,  NVarPlotErr,   controlRatioErr);
  
  TH1F *histo = new TH1F ("histo", " ",  DY_Data->GetNbinsY() , DY_Data->GetYaxis()->GetXmin(), DY_Data->GetYaxis()->GetXmax());
  histo->Draw();
  
  theGraphData->SetMarkerStyle(20);
  theGraphMC->SetMarkerStyle(20);
  theGraphMC->SetMarkerColor(2);
  theGraphMC_SN->SetMarkerStyle(22);
  theGraphMC_SN->SetMarkerColor(4);
  
  if(plot == "NJets") { 
      histo->GetXaxis()->SetTitle("jet multiplicity");
      histo->GetXaxis()->SetBinLabel(1,"#geq 0");
      histo->GetXaxis()->SetBinLabel(2,"#geq 1");
      histo->GetXaxis()->SetBinLabel(3,"#geq 2");
      histo->GetXaxis()->SetBinLabel(4,"#geq 3");
      histo->GetXaxis()->SetBinLabel(5,"#geq 4");
  }

  if(plot == "NPV")  histo->GetXaxis()->SetTitle("number of primary vertices");
  histo->GetYaxis()->SetTitle("R_{out/in}");

  /*if (plot == "NPV") { 
  TF1 *Pol_Data = new TF1("Pol_Data", "0.1*[0]", 1, 30);
  theGraphData->Fit("Pol_Data");
  TF1 *Pol_MC = new TF1("Pol_MC", "0.1*[0]", 1, 30); Pol_MC->SetLineColor(2);
  theGraphMC->Fit("Pol_MC");
  }*/
  theGraphData->Draw("ep");
  theGraphMC->Draw("ep"); 
  theGraphMC_SN->Draw("ep"); 

  TLegend* qw = new TLegend(0.20,0.55,0.35,0.75);
  qw->AddEntry(theGraphData,  "R_{out/in} Data" ,    "p");
  qw->AddEntry(theGraphMC,    "R_{out/in} MC" ,  "p");
  qw->AddEntry(theGraphMC_SN, "N_{Z}/N_{tot}  MC" ,  "p");
  
  qw->Draw();

  c1->SaveAs(Form("TopResults/%s_fit.eps",htitle.Data()));
  c1->SaveAs(Form("TopResults/%s_fit.pdf",htitle.Data()));

  return 0;
}

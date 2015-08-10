#include "../inc/StatisticTools.h"
#include <TGraphErrors.h>
#include <TF1.h>
#include <TFile.h>
#include <TCanvas.h>


StatBox::StatBox(std::vector<Sensor> sensPack)
{

	h1pullSlope = new TH1D("h1pullSlope", "Slope pull;pull;events",100, 0, 0);
	h1pullOffset = new TH1D("h1pullOffset", "Offset pull;pull;events", 100, 0, 0);
	h1residual = new TH1D("h1residual", "Residual pull;res;events", 100, 0,0);
	h1chi2 = new TH1D("h1chi2", "Chi2;#chi^{2};events", 40, 0, 80);
	h1slopeerror = new TH1D("h1slopeerror", "Slope error;res;events", 100, 0,0);
	h1offerror = new TH1D("h1offerror", "Offset error;events", 100, 0,0);

	//pack all histos
	tArray = new TObjArray(0);
	tArray->Add(h1pullSlope);
	tArray->Add(h1pullOffset);
	tArray->Add(h1residual);
	tArray->Add(h1chi2);
	tArray->Add(h1slopeerror);
	tArray->Add(h1offerror);

	zMin = sensPack.front().globalPos.Z();
	zMax = sensPack.back().globalPos.Z();

	zMean = 0;
	zMean2 = 0;
	zNum = sensPack.size();

	for (Sensor s : sensPack){
		zMean += s.globalPos.Z();
		zMean2 += s.globalPos.Z()*s.globalPos.Z();
	}

	zMean /= zNum;
	zMean2 /= zNum;

}

StatBox::~StatBox(){delete tArray;}

void StatBox::pushEvent(Event ev){
	Int_t nHits = ev.hits.size();
	TGraphErrors graph(nHits);

	for (Int_t i=0; i<nHits; ++i){
		graph.SetPoint(i, ev.hits[i].z, ev.hits[i].x );
//std::cout<<ev.hits[i].z <<" "<<ev.hits[i].x <<std::endl;// <<<<---------- ------------------------ --------------- !!!!!!!!!
		graph.SetPointError(i, ev.hits[i].errZ, ev.hits[i].errX );
	}

	TF1 f("f", "[0]*x+[1]", zMin, zMax);
	graph.Fit(&f, "Q");//quiet
//
//	if(f.GetChisquare()>80){
//	TCanvas *cnvt = new TCanvas("cnvt","cnvt", 600 , 400);
//	graph.Draw();
//	cnvt->Print("test.pdf");}
//
	Double_t pullSlope = (f.GetParameter(0)-ev.trk->slope)/f.GetParError(0);
	Double_t pullOffset = (f.GetParameter(1)-ev.trk->offset)/f.GetParError(1);

	h1pullSlope->Fill(pullSlope);
	h1pullOffset->Fill(pullOffset);
	h1chi2->Fill(f.GetChisquare());
	h1slopeerror->Fill(f.GetParError(0));
	h1offerror->Fill(f.GetParError(1));

//std::cout<<f.GetChisquare()<<std::endl;// <<<<---------- ------------------------ --------------- !!!!!!!!!
	for (Hit h : ev.hits)//mean for hits!!!
	{
		Double_t z = h.z;
		Double_t err_b = f.GetParError(1);
		Double_t var_x = (err_b*err_b/zNum)*(zMean2-2*zMean*z+z*z)/(zMean2-zMean*zMean);
//std::cout<< h.x << " " << f.Eval(z) << " : " << h.x - f.Eval(z) <<std::endl;// <<<<---------- ------------------------ --------------- !!!!!!!!!
		Double_t res = (h.x - f.Eval(z) )/sqrt(var_x);
		h1residual->Fill(res);
	}


}


void StatBox::makeOutput(TString dirForResults){

	TCanvas *cnv = new TCanvas("cnv","cnv", 600 , 400);
	TCanvas *cnvG = new TCanvas("cnvG","cnvG", 600 , 400);
	cnvG->Divide(2,2);
	
	cnvG->cd(1);
	h1pullSlope->DrawCopy();
	cnv->cd();
	h1pullSlope->DrawCopy();
	cnv->Print(dirForResults+"/pull_slope.pdf");

	cnvG->cd(2);
	h1pullOffset->DrawCopy();
	cnv->cd();
	h1pullOffset->DrawCopy();
	cnv->Print(dirForResults+"/pull_offset.pdf");

	cnvG->cd(3);
	h1residual->DrawCopy();
	cnv->cd();
	h1residual->DrawCopy();
	cnv->Print(dirForResults+"/residual.pdf");

	cnvG->cd(4);
	h1chi2->DrawCopy();
	cnv->cd();
	h1chi2->DrawCopy();
	cnv->Print(dirForResults+"/chi2.pdf");

	cnv->cd();
	h1slopeerror->DrawCopy();
	cnv->Print(dirForResults+"/slope_error.pdf");

	h1offerror->DrawCopy();
	cnv->Print(dirForResults+"/off_error.pdf");


	cnvG->Print(dirForResults+"/all.pdf");


	TFile *tFile = new TFile(dirForResults+"/output.root", "recreate");
	tArray->Write();
	tFile->Close();
}



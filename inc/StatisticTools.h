#ifndef STATTOOLS_H
#define STATTOOLS_H

#include <TH1D.h>
#include "EventUtils.h"
#include "Detector.h"
#include <vector>
#include <TObject.h>
#include <TString.h>
#include <iostream>
class Experiment;

class StatBox{
	friend Experiment;
	private:
		StatBox(std::vector<Sensor> sensPack);
		~StatBox();

		TH1D *h1pullSlope;
		TH1D *h1pullOffset;
		TH1D *h1residual;
		TH1D *h1chi2;
		TH1D *h1slopeerror;
		TH1D *h1offerror;

		TObjArray *tArray;

		Double_t zMin;
		Double_t zMax;
		Double_t zMean;
		Double_t zMean2;
		Double_t zNum;

		void pushEvent(Event ev);
		void makeOutput(TString dirForResults);

};

#endif

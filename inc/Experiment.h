#ifndef EXPERIMENT_H
#define EXPERIMENT_H
#include "Detector.h"
#include "StatisticTools.h"

#include <TRandom3.h>
class Experiment{
	public://Experiment( rozpatrywany detektor)
		Experiment(const Detector& detectorPattern);
		~Experiment();

		//ustawia rozmiar celu i zakres przelotu - funkcja zwalnia tryger wiec obligatoryjnie musi byc wywolana
		//setParameters( pozycja srodka x , z , szerokosc w x , z , kat min , max )
		void setParameters(Double_t xArg, Double_t zArg, Double_t xW, Double_t zW, Double_t minA, Double_t maxA);
		void run(Int_t nEvt);
		void keepEvents(Bool_t var){keepEvt=var;}
		void saveStat(TString dirPath){stat.makeOutput(dirPath);}

	private:
		Detector det;
		Bool_t trigger;

		//Target variables
		Double_t x , z;
		Double_t xWidth , zWidth;
		Double_t minAngle , maxAngle;

		TRandom3 *rnd;

		//Events storage
		Bool_t keepEvt;
		std::vector<Event> events;
		
		//Stat operations
		StatBox stat;


		//Generator functions - utils
		Track trkGen(); // Generator sladow 
		std::vector<Hit> getHits(Track trk);
		Event createEvent();
};

#endif


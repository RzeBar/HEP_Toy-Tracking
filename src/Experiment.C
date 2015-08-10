#include "../inc/Experiment.h"
#include <iostream>
#include <ctime>

void printStartInfo();
void printParamWarning();
void printLastProgressLine(Int_t nEvt);
void printProgress(Int_t iEvt, Int_t nEvt);


Experiment::Experiment(const Detector& detectorPattern)
: det(detectorPattern), rnd(new TRandom3(time(NULL))), keepEvt(0)
, stat( StatBox(det.sensor) )
{trigger=false;}


Experiment::~Experiment(){
	delete rnd;
}

void Experiment::setParameters(Double_t xArg, Double_t zArg, Double_t xW, Double_t zW, Double_t minA, Double_t maxA){
	x =  xArg ; z = zArg;
	xWidth = xW ; zWidth = zW;
	minAngle = minA; maxAngle = maxA;
	trigger=true;
	std::cout<< "\033[1;35m" <<"..::: "<< "\033[1;32m" <<"Experiment has been prepared successfully!"<< "\033[1;35m" <<" :::.."<<"\033[0m"<<std::endl;

}

Track Experiment::trkGen(){

	Double_t x0 = rnd->Uniform(x-xWidth/2.,x+xWidth/2.);
	Double_t z0 = rnd->Uniform(z-zWidth/2.,z+zWidth/2.);
	Double_t angle = rnd->Uniform(minAngle, maxAngle);
	Double_t slope = tan(angle*M_PI/180.);
	Double_t offset = x0 - slope*z0;

	return Track(slope, offset);
}

std::vector<Hit> Experiment::getHits(Track trk){
	std::vector<Hit> hitsVec;

	//Collecting hits for each sensor
	for (Sensor sens : det.sensor){
		//Get single hit with variance

		Double_t jerkX = rnd->Uniform( trk.getX( sens.globalPos.Z() ) - sens.channelHeight,
                                               trk.getX( sens.globalPos.Z() ) + sens.channelHeight);

		//Check range
		if ( jerkX < sens.channelPosGlobal[0].X() + sens.channelHeight &&
                     jerkX > sens.channelPosGlobal[sens.nChannels-1].X() - sens.channelHeight )  

		//if ok find channel and create hit
		for (Int_t chIdx=0; chIdx<sens.nChannels ; ++chIdx){
		
			if (jerkX >  (sens.channelPosGlobal[chIdx].X() - sens.channelHeight) ){
				Double_t error = 2.*sens.channelHeight/sqrt(12.);
				hitsVec.push_back(Hit(sens.channelPosGlobal[chIdx].X(), error, sens.globalPos.Z(), 0));
//std::cout<<  jerkX << " " << sens.channelPosGlobal[chIdx].X() <<std::endl;// <<<<---------- ------------------------ --------------- !!!!!!!!!
				break;

			}
		}
	}

	return hitsVec;
}

Event Experiment::createEvent(){
	Track t = trkGen();
	std::vector<Hit> hitsVec = getHits(t);
	Event evt(t,hitsVec);
	if(keepEvt)
	events.push_back(evt);
	return evt;
}

void Experiment::run(Int_t nEvt){
	if(trigger){
		printStartInfo();

		for(Int_t iEvt=0 ; iEvt<nEvt ; ++iEvt){
			if(iEvt%(nEvt/10)==0)	printProgress(iEvt,nEvt);// generuje segfaulta dla malych nevt
			Event evt = createEvent();
			stat.pushEvent(evt);
		}
		printLastProgressLine(nEvt);
	}
	else printParamWarning();
	
}

void printStartInfo(){
std::cout<< "\033[1;35m" <<"..::: "<< "\033[1;33m" <<"Experiment has started! Please wait ..."<< "\033[1;35m" <<" :::.."<<"\033[0m"<<std::endl;
}

void printParamWarning(){
std::cout<< "\033[1;35m" <<"..::: "<< "\033[1;31m" <<"Experiment not prepared! Set parameters!"<< "\033[1;35m" <<" :::.."<<"\033[0m"<<std::endl;
}

void printLastProgressLine(Int_t nEvt){
std::cout<< "\033[1;35m" <<"~~~ "<< "\t\t\033[1;33m" <<100<< "% " <<" \033[1;30m"<<"("<<nEvt<<"/"<<nEvt<<")"<<" \033[1;35m\t\t" <<" ~~~"<<"\033[0m"<<std::endl;
std::cout<< "\033[1;35m" <<"..::: "<< "\033[1;32m" <<"Experiment finished successfully!"<< "\033[1;35m" <<" :::.."<<"\033[0m"<<std::endl;
}

void printProgress(Int_t iEvt, Int_t nEvt){
std::cout<< "\033[1;35m" <<"~~~ "<< "\t\t\033[1;33m" <<iEvt*100./nEvt<< "% " <<" \033[1;30m"<<"("<<iEvt<<"/"<<nEvt<<")"<<" \033[1;35m\t\t" <<" ~~~"<<"\033[0m"<<std::endl;
}

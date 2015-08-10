#include "../inc/Detector.h"


Detector::Detector():nSensors(0){}


Detector::Detector(const Sensor& senPattern, Int_t nSensArg , TVector3 frontGap , TVector3 sensGap )
: nSensors(nSensArg){

	for(Int_t i=0 ; i<nSensors ; ++i){
		sensor.push_back(senPattern); // ciekawe czy uzyje konstruktora kopiujacego ? >> użył :)
		sensor[i].SetGlobalPos(sensGap*i+frontGap);	
	}
}

Detector::~Detector(){}

Detector::Detector(const Detector& other)
:nSensors(other.nSensors), sensor(other.sensor)
{}


void Detector::addSensor(const Sensor& sen, TVector3 glbPos){
	Int_t i = sensor.size();
	sensor.push_back(sen);
	sensor[i].SetGlobalPos(glbPos);
}



void Detector::pushSensor(const Sensor& sen, TVector3 relPos){
	if(sensor.size() != 0){
		Int_t i = sensor.size();
		sensor.push_back(sen);
		sensor[i].SetGlobalPos(relPos+sensor[i-1].globalPos);
	}
	else throw 0;

}

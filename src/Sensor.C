#include "../inc/Sensor.h"


Sensor::Sensor( Double_t heightArg, Double_t depthArg , Double_t widthArg , Int_t nChanArg )
: height(heightArg) , x(&height), depth(depthArg) , y(&depth) 
, width(widthArg) , z(&width) , nChannels(nChanArg) {

	channelHeight = height/nChannels/2. ;
	channelDepth = depth/nChannels/2. ;
	channelWidth = width/nChannels/2. ;

	channelPosLocal = new TVector3[nChannels];

	for(Int_t i=0;  i < nChannels  ; ++i){
		channelPosLocal[i].SetXYZ  ((nChannels-1-2*i)*channelHeight,0,0);
	}

	channelPosGlobal = new TVector3[nChannels];


} 


Sensor::~Sensor( ){

	delete[] channelPosLocal;
	delete[] channelPosGlobal;

}

Sensor::Sensor(const Sensor& other)
: height(other.height) , x(&height), depth(other.depth) , y(&depth) 
, width(other.width) , z(&width) , globalPos(other.globalPos)
, nChannels(other.nChannels), channelHeight(other.channelHeight) , channelDepth(other.channelDepth) 
, channelWidth(other.channelWidth)
{
	channelPosLocal = new TVector3[nChannels];
	channelPosGlobal = new TVector3[nChannels];

	for(Int_t i=0;  i < nChannels  ; ++i){
		channelPosLocal[i]=other.channelPosLocal[i];
		channelPosGlobal[i]=other.channelPosGlobal[i];
	}

}

void Sensor::SetGlobalPos(TVector3 glbPosArg){
	globalPos = glbPosArg;
	for(Int_t i=0;  i < nChannels  ; ++i){
		channelPosGlobal[i].SetX  ( glbPosArg.X() + channelPosLocal[i].X() );
		channelPosGlobal[i].SetY  ( glbPosArg.Y() + channelPosLocal[i].Y() );
		channelPosGlobal[i].SetZ  ( glbPosArg.Z() + channelPosLocal[i].Z() );
	}
}

//Sensor& Sensor::operator=(const Sensor& other){}

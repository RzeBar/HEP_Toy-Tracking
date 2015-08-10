#ifndef SENSOR_H
#define SENSOR_H

#include <Rtypes.h>
#include <TVector3.h>
#include <TVector2.h>
class Detector;
class Experiment;
class StatBox;

class Sensor{
	friend Detector;
	friend Experiment;
	friend StatBox;
	public:// Sensor( wysokosc x, glebokosc y, szerokosc z , ilosc kanalow )
		Sensor( Double_t heightArg, Double_t depthArg , Double_t widthArg , Int_t nChanArg );
		~Sensor( );

		Sensor(const Sensor& other); // copy constructor

		void SetGlobalPos(TVector3 glbPosArg);

//		Sensor& operator=(const Sensor& other);// not important now
	private:

		Double_t height; Double_t *x;	// x dim in [mm]
		Double_t depth;  Double_t *y;	// y dim in [mm]	//w razie rozszerzenia 3d
		Double_t width;  Double_t *z;	// z dim in [mm]

		TVector3 globalPos; 		//position of the sensor center

		Int_t nChannels;

		Double_t channelHeight , channelDepth , channelWidth; //half - lengths
		TVector3 *channelPosLocal;	//position of the channel center iterated from the top according to sensor center
		TVector3 *channelPosGlobal;	//will be setted after installation in detector frame
};
#endif

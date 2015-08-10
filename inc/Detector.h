#ifndef DETECTOR_H
#define DETECTOR_H
#include "Sensor.h"
#include <vector>
class Experiment;

class Detector{
	friend Experiment;
	public:
		Detector();// empty detector - add sensors manually
		// Detector( szablon sensora , ilosc , odleglosc od poczatku, przerwy miedzy sensorami)
		Detector(const Sensor& senPattern, Int_t nSensArg , TVector3 frontGap , TVector3 sensGap );// fill by sensors pattern
		~Detector();

		Detector(const Detector& other);

		void addSensor(const Sensor& sen, TVector3 glbPos); // add a sensor according to the detector global position
		void pushSensor(const Sensor& sen, TVector3 relPos); // add a sensor according to the position of the last one
	//	void popSensor(); // delete last one // not important but "to do"

	private:
		Int_t nSensors;
		std::vector<Sensor> sensor;





};
#endif

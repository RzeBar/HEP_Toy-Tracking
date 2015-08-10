#ifndef EVTUTILS_H
#define EVTUTILS_H
#include <Rtypes.h>
#include <vector>

class Event;
class StatBox;

class Hit{
	friend Event;
	friend StatBox;

	public:
		Hit(Double_t xArg, Double_t errXarg, Double_t zArg, Double_t errZarg);//copy normal
		~Hit(){}
	private:
		Double_t x ;
		Double_t errX ;
		Double_t z ;
		Double_t errZ ;
};

class Track{
	friend Event;
	friend StatBox;
	public:
		Track(Double_t slope, Double_t offset);//copy normal
		~Track(){}

		Double_t getX(Double_t z);
	private:
		Double_t slope ;
		Double_t offset ;
};

class Event{
	friend StatBox;

	public:
		Event(const Track& trkArg, std::vector<Hit> hitsVecArg);
		~Event();
		Event(const Event& other);

	private:
		Track *trk;
		std::vector<Hit> hits;
	

};

#endif

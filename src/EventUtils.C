#include "../inc/EventUtils.h"

Hit::Hit(Double_t xArg, Double_t errXarg, Double_t zArg, Double_t errZarg)
:x(xArg), errX(errXarg), z(zArg), errZ(errZarg)
{}

Track::Track(Double_t slopeArg, Double_t offsetArg)
:slope(slopeArg), offset(offsetArg)
{}

Double_t Track::getX(Double_t z){
	return slope*z + offset;
}


Event::Event(const Track& trkArg, std::vector<Hit> hitsVecArg)
:trk(new Track(trkArg)), hits(hitsVecArg)
{}

Event::~Event()
{delete trk;}

Event::Event(const Event& other)
:trk(new Track(other.trk->slope,other.trk->offset)),hits(other.hits)
{}

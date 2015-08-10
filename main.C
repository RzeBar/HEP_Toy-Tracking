
#include "inc/Experiment.h"
#include <iostream>

int main(){// wszystko rozpatrywane jest wzgledem ukladu o srodku 0,0,0
	Sensor stripe(100,0,0,400);// [mm]
	TVector3 frontGap(0,0,40);
	TVector3 sensGap(0,0,30);
	
	Detector det(stripe,9,frontGap,sensGap);


	Experiment toy(det);

	toy.setParameters(0,0,4,4,-14,14);
	toy.run(10000); // segment dla printa z < 10 evt
	toy.saveStat("results");
}

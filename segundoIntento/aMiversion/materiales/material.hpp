#pragma once


#include "../color/rgb.hpp"
#include "../escena/luz.hpp"

class Material {
    public:
    RGB kd, ks, kt, kl;
    float nRefraction;
    char majorCh;


    Material(const RGB& diffuse, const RGB& reflex,	const RGB& refract,
             const RGB& light, const float nCoef) : kd(diffuse), ks(reflex),
             kt(refract), kl(light), nRefraction(nCoef) {

		// Gets the channel with the maximum contribution.
		char lD, lS, lT, lL;
		double maxD = diffuse.maxC(lD);
		double maxS = reflex.maxC(lS);
		double maxT = refract.maxC(lT);
		double maxL = light.maxC(lL);
		double maxDS = max(maxD, maxS);
		double maxTL = max(maxT, maxL);
		double maxContribution = max(maxDS, maxTL);
		if(maxD == maxContribution) majorCh = lD;
		else if(maxS == maxContribution) majorCh = lS;
		else if(maxT == maxContribution) majorCh = lT;
		else majorCh = lL;

		// Checks that the sum of the color coeficients is 1 or less.
		for (int i = 0; i < 3; ++i)
			if (kd[i] + ks[i] + kt[i] + kl[i] > 1) {
				cout << "Error: the sum of figure color coeficients must be for channel, as much, 1.\n";
				exit(1);
		}
		
	}
};
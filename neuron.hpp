#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include "constant.hpp"

using namespace std;

class Neuron
{
	public :
		//constructor
		Neuron ();
		
		//update method
		void update(double time, double dt, double extCurrent);
		//the formula
		void formula(double dt, double extCurrent);
		
		//getters
		vector <double> getSpikes() const;
		size_t getNumSpikes() const;
		double getSpikeTime(size_t tab) const;
		double getPot() const;
	
	private :
		//neuron potential (V)
		double pot_;
		//each time at which a spike occurs is stored 
		vector <double> spikes_;		
};

#endif

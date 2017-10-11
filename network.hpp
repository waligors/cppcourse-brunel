#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include "constant.hpp"
#include "neuron.hpp"

using namespace std;

class Network
{
	public :
		//constructor
		Network ();
		
		//update method
		void update(double dt, double extCurrent);
	
	private :
		//each neuron of our simulation
		vector <Neuron> neurons_;		
};

#endif

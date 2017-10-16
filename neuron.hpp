#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include "constant.hpp"
#include "buffer.hpp"

using namespace std;

class Neuron
{
	public :
		//constructor
		Neuron ();
		Neuron (unsigned int i,vector <unsigned int> connections);
		Neuron (unsigned int i);
		
		//update method
		bool update(double dt, double extCurrent, double j);
		//the formula
		void formula(double dt, double extCurrent, double j);
		
		//getters
		vector <unsigned int> getSpikes() const;
		size_t getNumSpikes() const;
		unsigned int getSpikeTime(size_t tab) const;
		double getPot() const;
		double stepToTimeMs(double c);
		unsigned int getClock() const;
		Buffer* getBuffer();
		void addConnection(unsigned int con);
		vector <unsigned int> getConnections() const;
		
	private :
		//neuron potential (V)
		double pot_;
		//each time at which a spike occurs is stored 
		vector <unsigned int> spikes_;	
		
		Buffer buffer_;	
		unsigned int clock_;
		
		bool refractory_;
		
		vector <unsigned int> connections_;
		
		unsigned int neuron_num_;
};

#endif

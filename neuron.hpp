#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include "constant.hpp"

class Neuron
{
	public :
		//constructor
		Neuron ();
		Neuron (bool excitatory);
		Neuron (bool excitatory, std::vector <unsigned int> connections);
		
		//update method
		bool update(double extCurrent, double lambda = 0.0);
		//the formula
		void updatePotential(double extCurrent, double lambda);
		
		//getters
		std::vector <unsigned int> getSpikes() const;
		size_t getNumSpikes() const;
		unsigned int getSpikeTime(size_t tab) const;
		double getPotential() const;
		static double stepToTime(unsigned int steps);
		unsigned int getClock() const;
		
		void addConnection(unsigned int con);
		std::vector <unsigned int> getConnections() const;
		bool isExcitatory() const;
		void printSpikes() const;
		double poissonDistribution(double lambda) const;
		
		void setBuffer(size_t t, bool excitatory);
		double getAndEraseBuffer (size_t t);
		double getBuffer (size_t t) const;
		void printBuffer () const;
		static unsigned int timeToStep(double time);
		void setPotential(double pot);
		bool didSpike() const;
		
	private :
		//neuron potential (V)
		double pot_;
		unsigned int clock_;
		bool refractory_;		
		bool isExcitatory_;
		std::vector <unsigned int> spikes_;	
		std::vector <unsigned int> connections_;
		std::vector <double> buffer_;
};

#endif

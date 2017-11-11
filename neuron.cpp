#include <iostream>
#include <cmath>
#include <random>
#include <cassert>
#include "neuron.hpp"

Neuron::Neuron () : Neuron(true)
{}

Neuron::Neuron (bool excitatory)
:	pot_(v_reset),
	clock_(0),
	refractory_(false),
	isExcitatory_(excitatory)
{
	spikes_.clear();
	connections_.clear();
	buffer_.clear();
	for(size_t i = 0; i < buffer_size ;i++)
	{
		buffer_.push_back(0.0);
	}
}

Neuron::Neuron (bool excitatory, std::vector <unsigned int> connections) : Neuron (excitatory)
{
	/**
	 * Copying the connections
	 * Using the vector's operator=
	 */
	connections_ = connections;
}

bool Neuron::update(double extCurrent, double lambda)
{
	//if the threshold is reached
	if(pot_ >= thresh)
	{	
		//store the actual time to the spikes vector, reset the potential
		//set refractory to true and return true value bc the neuron is actually spiking
		spikes_.push_back(clock_);
		refractory_=true;
		pot_= v_reset;
		clock_++;
		return true;
	}
	//if the neuron is refractory	
	else if(refractory_)
	{
		if(spikes_.back() + time_rest <= clock_)
		{
			refractory_=false;
		}
	}
	//else compute the formula
	else 
	{		
		updatePotential(extCurrent,lambda);	
	}
	
	//increment the clock and return false bc there is no spiking
	clock_++;
	return false;
}

void Neuron::updatePotential(double extCurrent, double lambda)
{
	pot_= (const1*pot_) + (extCurrent*const2) + getAndEraseBuffer(clock_+1) + j_exc*poissonDistribution(lambda);
}

std::vector <unsigned int> Neuron::getSpikes() const
{
	return spikes_;
}

size_t Neuron::getNumSpikes() const
{
	return spikes_.size();
}

unsigned int Neuron::getSpikeTime(size_t tab) const
{
	assert(tab<spikes_.size());
	return spikes_[tab];
}

double Neuron::getPotential() const
{
	return pot_;
}

double Neuron::stepToTime(unsigned int steps)
{
	return steps*dt;
}

unsigned int Neuron::getClock() const
{
	return clock_;
}

void Neuron::addConnection(unsigned int con)
{
	connections_.push_back(con);
}

std::vector <unsigned int> Neuron::getConnections() const
{
	return connections_;
}

bool Neuron::isExcitatory() const
{
	return isExcitatory_;
}

void Neuron::printSpikes() const
{
	for(auto spike : spikes_)
	{
		std::cout << spike << '\t';
	}
	std::cout << std::endl << "Number of spikes : " << getNumSpikes() << std::endl;
}

double Neuron::poissonDistribution(double lambda) const
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::poisson_distribution<int> distribution (lambda);
	return (double) distribution(gen);
}

void Neuron::setBuffer(size_t t, bool excitatory)
{
	if(excitatory)
	{
		buffer_[(t+delay)%buffer_size]+=j_exc;
	}
	else
	{
		buffer_[(t+delay)%buffer_size]+=j_inh;
	}
}

double Neuron::getAndEraseBuffer (size_t t)
{
	double a(buffer_[t%buffer_size]);
	buffer_[t%buffer_size]= 0.0;
	return a;
}

double Neuron::getBuffer (size_t t) const
{
	return buffer_[t%buffer_size];
}

void Neuron::printBuffer () const
{
	std::cout << "BUFFER" << std::endl;
	for(auto b : buffer_)
	{
		std::cout << b << '\t';
	}
	std::cout << std::endl;
}

unsigned int Neuron::timeToStep(double time)
{
	return static_cast<unsigned long>(std::ceil(time/dt));
}

void Neuron::setPotential(double pot)
{
	pot_=pot;
}

bool Neuron::didSpike() const
{
	return !spikes_.empty();
}

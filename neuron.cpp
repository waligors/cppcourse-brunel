#include "neuron.hpp"
#include <iostream>
#include <cmath>

Neuron::Neuron ()
:	pot_(v_reset),
	clock_(0),
	refractory_(false)
{
	spikes_.clear();
	connections_.clear();
}

Neuron::Neuron (unsigned int i,vector <unsigned int> connections)
:	pot_(v_reset),
	clock_(0),
	refractory_(false),
	neuron_num_(i),
	connections_(connections)
{
	spikes_.clear();
	connections_.clear();
}

Neuron::Neuron (unsigned int i)
:	pot_(v_reset),
	clock_(0),
	refractory_(false),
	neuron_num_(i)
{
	spikes_.clear();
	connections_.clear();
}

bool Neuron::update(double dt, double extCurrent, double j)
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
	
	if(refractory_)
	{
		if(spikes_.back() + time_rest <= clock_)
		{
			refractory_=false;
		}
	}
	else
	{
		//compute the formula
		formula(dt, extCurrent, j);
	}
	
	clock_++;
	return false;
}

void Neuron::formula(double dt, double extCurrent, double j)
{
	double const1(exp(-(dt/tau)));
	double const2((tau/cap)*(1-const1));
	pot_= (const1*pot_) + (extCurrent*const2) + j;
}

vector <unsigned int> Neuron::getSpikes() const
{
	return spikes_;
}

size_t Neuron::getNumSpikes() const
{
	return spikes_.size();
}

unsigned int Neuron::getSpikeTime(size_t tab) const
{
	return spikes_[tab];
}

double Neuron::getPot() const
{
	return pot_;
}

double Neuron::stepToTimeMs(double c)
{
	return c/10;
}

unsigned int Neuron::getClock() const
{
	return clock_;
}

Buffer* Neuron::getBuffer()
{
	return &buffer_;
}

void Neuron::addConnection(unsigned int con)
{
	bool a=false;
	for(auto c : connections_)
	{
		if(con==c) { a=true; }
	}
	if(!a) { connections_.push_back(con); }
}

vector <unsigned int> Neuron::getConnections() const
{
	return connections_;
}

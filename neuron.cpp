#include "neuron.hpp"
#include <iostream>
#include <cmath>

Neuron::Neuron ()
:	pot_(v_reset)
{
	spikes_.clear();
}

void Neuron::update(double time, double dt, double extCurrent)
{
	//if the threshold is reached
	if(pot_ >= thresh)
	{	
		//store the actual time to the spikes vector and reset the potential
		spikes_.push_back(time);
		pot_= v_reset;	
	}	
	
	//if at least one spike occured
	if(!spikes_.empty())
	{	
		//if we are not in the refractory period
		if(spikes_.back() + time_rest <= time )
		{
			//compute the formula
			formula(dt, extCurrent);
			cout << pot_*1000 <<" mV at time " << time*1000 << " ms." << endl;	
		}
		else
		{
			cout << "refractory time!" << endl;
		}
	}
	
	//no spike occured (yet)
	else
	{
		//compute the fromula
		formula(dt, extCurrent);
		cout << pot_*1000 <<" mV at time " << time*1000 << " ms." << endl;
	}
}

void Neuron::formula(double dt, double extCurrent)
{
	double const1(exp(-(dt/tau)));
	double const2((tau/cond)*(1-const1));
	pot_= (const1*pot_) + (extCurrent*const2);
}

vector <double> Neuron::getSpikes() const
{
	return spikes_;
}

size_t Neuron::getNumSpikes() const
{
	return spikes_.size();
}

double Neuron::getSpikeTime(size_t tab) const
{
	return spikes_[tab];
}

double Neuron::getPot() const
{
	return pot_;
}



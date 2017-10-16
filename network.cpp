#include "network.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Network::Network (unsigned int n_neurons)
{
	for(size_t i = 0; i < n_neurons ;i++)
	{
		neurons_.push_back(Neuron(i));
	}
	//Manually setting connections (for now)
	neurons_[0].addConnection(1);
	
	//Manually setting neurons that get the I external (for now)
	neurons_Iext_.push_back(0);
}

void Network::update(double dt, double extCurrent)
{
	//Browsing Iext neurons
	for(auto i : neurons_Iext_)
	{
		if(neurons_[i].update(dt,extCurrent,0.0))
		{
			cout << "Neuron " << i << " spiking at time : " << neurons_[i].getClock()-1 << endl;
			for(auto con : neurons_[i].getConnections())
			{
				neurons_[con].getBuffer()->set(neurons_[i].getClock()-1,j_const);
			}
		}
	}
	
	//Browsing not Iext_neurons
	for(size_t i = 0; i < neurons_.size(); i++)
	{
		bool is_Iext_neuron = false;
		for(auto j : neurons_Iext_)
		{
			if(i==j) { is_Iext_neuron = true; }
		}
		if(!is_Iext_neuron)
		{
			//cout << "Current stored in buffer at time "<< neurons_[i].getClock() << " : " << neurons_[i].getBuffer()->get(neurons_[i].getClock()) << endl;
			if(neurons_[i].update(dt,0.0,neurons_[i].getBuffer()->get(neurons_[i].getClock()+1)))
			{
				cout << "Neuron " << i << " spiking at time : " << neurons_[i].getClock()-1 << endl;
			}
		}
	}
		
}

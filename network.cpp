#include "network.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Network::Network ()
{
	for(size_t i = 0; i < n_neurons;i++)
	{
		neurons_.push_back(Neuron());
	}
}

void Network::update(double dt, double extCurrent)
{
	//assuming we only have 2 neurons and the current only goes to neuron '0'
	if(neurons_[0].update(dt,extCurrent,0.0))
	{
		if(neurons_[1].update(dt,0.0,j_const))
		{
			cout << "AAAAAAAAAAAAAA" << endl;
			//cout << "Neuron 2 spiking at step :" << neurons_[1].getClock() << endl;
		}
		else
		{
			//cout <<"Neuron 1 spiked but not Neuron 2" << endl << "Neuron 2 pot : " << neurons_[1].getPot() << endl ;
		}
	}
	else
	{
		neurons_[1].update(dt,0.0,0.0);
		//cout << "Neuron 1 didnt spike .." << endl << "Neuron 2 pot : " << neurons_[1].getPot() << endl;
	}
	
	//neurons_[0].update(dt,extCurrent,0.0);
	//cout << "Neuron 1 pot : " << neurons_[0].getPot() << endl;
	for(auto s : neurons_[0].getSpikes())
	{
		cout << "Neuron 1 spike time : " << s << endl;
	}
	for(auto s : neurons_[1].getSpikes())
	{
		cout << "Neuron 2 spike time : " << s << endl;
	}
}

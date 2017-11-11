#include "network.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <cassert>
#include <time.h>

/**
 * Default constructor
 * Calls another constructor with the default number of neurons (delegation)
 */
Network::Network() : Network(numNeuronsDefault)
{}

/**
 * Constructor
 */
Network::Network (unsigned int numNeurons, bool areConnectionsGenerated)
{
	/**
	 * Setting some constants
	 */
	runTime_ = 0;
	globalClock_ = 0;
	assert(numNeurons>1);
	numNeurons_ = numNeurons;
	/**
	 * Finding the optimal number of excitatory neuron based on a ratio
	 * and the total number of neurons
	 */
	numExcitatory_= findIndexFromRatio(numNeurons,5);
	numInhibitory_= numNeurons-numExcitatory_;
	numExcitatoryConnections_ = ceil(numExcitatory_/10);
	numInhibitoryConnections_ = ceil(numInhibitory_/10);
	mu_thr_ = teta/(numExcitatoryConnections_*j_exc*tau/10); // why/10?
	mu_ext_ = 2*mu_thr_;
	lambda_=mu_ext_*numExcitatoryConnections_*dt*j_exc;
	
	/**
	 * Making excitatory and inhibitory neurons
	 */
	for(unsigned int i = 0; i < numExcitatory_ ; i++)
	{
		neurons_.push_back(Neuron(true));
	}
	for(unsigned int i = numExcitatory_; i < numNeurons_ ; i++)
	{
		neurons_.push_back(Neuron(false));
	}
	
	/**
	 * Calling the method that generates all the connections in the network
	 * (if wanted)
	 */
	if(areConnectionsGenerated)
	{
		generateConnections();
	}
	std::cout << "Network of " << numNeurons_ << " neurons generated "
		      << (areConnectionsGenerated ? "with" : "without") << " connections." << std::endl;
}

/**
 * The simulation method that we use in the main
 */
void Network::simulation(unsigned int runTime, double extCurrent, bool poissonDistribution)
{
	/**
	 * realTime is a little add-on that shows the time the program spent
	 * doing the simulation
	 */
	clock_t realTime;
	runTime_=runTime;
	realTime=clock();
	std::cout << "Simulation starts now." << std::endl;
	/**
	 * The main loop that updates the network
	 */
	while(globalClock_<runTime_)
	{
		update(extCurrent, poissonDistribution);
		/**
		 * since dt is 0.1 ms and global clock is in steps (10 steps = 1ms)
		 * we increment by one
		 */
		globalClock_++;
	}
	realTime = clock() - realTime;
	std::cout << "End of the simulation." << std::endl << "It took " << ((float)realTime/CLOCKS_PER_SEC) 
			  << " sec to emulate " << Neuron::stepToTime(runTime_) << " ms of simulation." << std::endl;
}

/**
 * The simulation method that we use in the main
 */
void Network::update(double extCurrent, bool poissonDistribution)
{
	/**
	 * This boolean is created for optimisation purposes
	 * We store the neuron state(excitatory or inhibitory) once for each neuron
	 * so we don't have to calculate it using a getter for each connections
	 */
	bool currentNeuronState;
	for(unsigned int i = 0; i < numNeurons_; i++)
	{
		/**
		 * For each neuron, we update it and check if it spiked
		 */
		if(neurons_[i].update(extCurrent,((poissonDistribution) ? lambda_ : 0.0)))
		{
			currentNeuronState = neurons_[i].isExcitatory();
			/**
			 * we iterate on each of its connections
			 */
			 //ASSERT if no connections?
			for(auto con : neurons_[i].getConnections())
			{
				/**
				 * we set the buffer of the neuron that is connected
				 */
				neurons_[con].setBuffer(globalClock_,currentNeuronState);
			}
		}
	}
}

void Network::print() const
{
	int ex(0),inh(0);
	for(auto n : neurons_)
	{
		if(n.isExcitatory())
		{
			ex++;
		}
		else
		{
			inh++;
		}
	}
	std::cout <<"Excitatory neurons : " << ex << std::endl << "Inhibitory neurons : " << inh << std::endl;
	printSpikesForOneNeuron(uniformDistribution(0,(int) numNeurons_-1));
}

void Network::printSpikesForOneNeuron(unsigned int index) const
{
	assert(index < numNeurons_);
	std::cout << "Randomly picked neuron : " << index << std::endl << "--Spike Table--" << std::endl;
	neurons_[index].printSpikes();
}

int Network::uniformDistribution(int a,int b) const
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> distribution (a,b);
	return distribution(gen);
}

int Network::findIndexFromRatio(unsigned int number, unsigned int ratio) const
{
	assert(ratio>1);
	return ceil((number*(ratio-1))/ratio);
}

void Network::outputFile() const
{
	outputFile("spikes.gdf");
}
void Network::outputFile(std::string filename) const
{
	std::ofstream data;
	data.open(filename.c_str());
	if(data.fail())
	{
		std::cerr << "Error whilst opening the file." << std::endl;
	}
	else
	{
		for(unsigned int i(0);i<neurons_.size();i++)
		{
			for(auto spiketime : neurons_[i].getSpikes())
			{
				data << spiketime << '\t' <<  i << '\n';
			}
		}
	}
	data.close();
	std::cout <<"The output file '" << filename << "' was successfully created." << std::endl;
}

void Network::generateConnections()
{
	for(unsigned int i = 0; i < numNeurons_ ;i++)
	{
		/**
		 * For each neuron we create the excitatory and inhibitory connections
		 * that it receives
		 */
		for(unsigned int j = 0; j < numExcitatoryConnections_; j++)
		{
			unsigned int a(0);
			do 
			{
				a = uniformDistribution(0,numNeurons_-1);
				assert(a < numNeurons_);
			} while(a == i || !neurons_[a].isExcitatory());
			neurons_[a].addConnection(i);
		}
		for(unsigned int j = 0; j < numInhibitoryConnections_; j++)
		{
			unsigned int a(0);
			do 
			{
				a = uniformDistribution(0,numNeurons_-1);
				assert(a < numNeurons_);
			} while(a == i || neurons_[a].isExcitatory());
			neurons_[a].addConnection(i);
		}
	}
}

bool Network::isNeuronExcitatory(unsigned int index)
{
	assert(index<neurons_.size());
	return neurons_[index].isExcitatory();
}

void Network::setNeuronPotential(unsigned int index, double pot)
{
	assert(index<neurons_.size());
	neurons_[index].setPotential(pot);
}

void Network::addNeuronConnection(unsigned int index, unsigned int connection)
{
	assert(index<neurons_.size());
	assert(connection<neurons_.size());
	neurons_[index].addConnection(connection);
}

double Network::getNeuronPotential(unsigned int index) const
{
	assert(index<neurons_.size());
	return neurons_[index].getPotential();
}

void Network::setNeuronBuffer(unsigned int index, unsigned int time, bool excitatory)
{
	assert(index<neurons_.size());
	neurons_[index].setBuffer(time,excitatory);
}

unsigned int Network::getNeuronClock(unsigned int index) const
{
	assert(index<neurons_.size());
	return neurons_[index].getClock();
}

bool Network::didOneNeuronSpiked() const
{
	bool spike = false;
	for(auto neuron : neurons_)
	{
		if(neuron.didSpike())
		{
			spike = true;
		}
	}
	return spike;
}


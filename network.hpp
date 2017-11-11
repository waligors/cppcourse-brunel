#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>
#include "constant.hpp"
#include "neuron.hpp"

/**
 * 	Neuron class
 */
class Network
{
	public :
		/**
		 * @brief Default constructor
		 * It created the network with the default number of neurons which here is 12'500
		 * It uses the other constructor
		 * @see Network::Network (unsigned int numNeurons)
		 */
		Network ();
		/**
		 * @brief Constructor
		 * It created the network with a wanted number of neurons
		 * @param numNeurons the number of neurons we want in our network
		 * @param areConnectionsGenerated a bool that tells the constructor if it has to 
		 * generate the connection automatically for all the neurons, by default = true
		 */
		Network (unsigned int numNeurons, bool areConnectionsGenerated = true);
		
		/**
		 * @brief Simulation method
		 * This is the main method where we update our network until a wanted runTime
		 * @see void Network::update(double dt, double extCurrent)
		 * @see int Network::findIndexFromRatio(unsigned int number, unsigned int ratio) const
		 * @param runTime the time in steps we want our simulation to run, by default = 10'000 steps
		 * @param extCurrent the external current that we apply to all our neurons in the network, by default = 0.0
		 * @param poissonDistribution a bool that tells the method if the network uses the external noise
		 * generated by a Poisson Distribution for a whole simulation, by default = true
		 */
		void simulation(unsigned int runTime = 10000, double extCurrent = 0.0, bool poissonDistribution = true);
		
		/**
		 * @brief Update method
		 * It updates our network by a small step in time dt
		 * It calls each Neuron's update method to do so
		 * @see bool Neuron::update(double dt, double extCurrent, double j, double lambda)
		 * @param extCurrent the same external current that is transfered from the simulation method, by default = 0.0
		 * @param poissonDistribution a bool that tells the method if the network uses the external noise
		 * generated by a Poisson Distribution, by default = true
		 */
		void update(double extCurrent = 0.0, bool poissonDistribution = true);
		
		/**
		 * @brief Print method
		 * Just a small optional print method that checks if we truely created our network
		 * that displays the number of excitatory and inhibitory neurons of our network
		 * then, it calls printSpikesForOneNeuron to display the spikes of a random neuron
		 * @see void Network::printSpikesForOneNeuron(unsigned int index) const
		 */
		void print() const;
		
		/**
		 * @brief Calculation method
		 * It finds the optimal number of excitatory neurons from a total neuron number
		 * and a ratio -> we have ratio-1 excitatory neuron for 1 inhibitory neuron 
		 * It is called in the network constructor
		 * @param  number the total number of neuron in the network
		 * @param the ratio (ratio-1 excitatory neuron:1 inhibitory neuron)
		 * @return the optiaml number of excitatory neurons
		 */
		int findIndexFromRatio(unsigned int number, unsigned int ratio) const;
		
		/**
		 * @brief Uniform int Distribution method
		 * It generated a random number between a and b (both included)
		 * Each number in the range has the same probability of being chosen
		 * @param a the lower boundary
		 * @param b the upper boundary
		 * @return the random number
		 */
		int uniformDistribution(int a,int b) const;
		
		/**
		 * @brief Print Method
		 * It prints all the spikes that one neuron had in the simulation
		 * Basically, it calls printSpikes of the Neuron class
		 * @see void Neuron::printSpikes() const
		 * @param index the wanted neuron's index
		 */
		void printSpikesForOneNeuron(unsigned int index) const;
		
		/**
		 * @brief Method that makes an output file
		 * It writes all the spikes of all the neuron in the network
		 * in a file (spikes.txt) in the follwing format : spikes time '\t' index of the neuron '\n'
		 * This files is then used to make the plot of our neurons
		 * @param filename the name in which we write the data
		 */
		void outputFile(std::string filename) const;
		
		/**
		 * @brief Method that makes an output file
		 * It calls the other overload method with the default filename spikes.txt
		 * @see void Network::outputFile(std::string filename) const
		 */
		void outputFile() const;
		
		/**
		 * @brief Method that generates all the neuron connections
		 * ...
		 */
		void generateConnections();
		
		/**
		 * @brief Getter that gets the state (excitatory or inhibiory) of one neuron in the network
		 * @param index the index of the neuron in the network
		 * @return a boolean if that neuron is excitatory
		 */
		bool isNeuronExcitatory(unsigned int index);
		
		/**
		 * @brief Setter for the potential of one neuron in the network
		 * @param index the index of the neuron in the network
		 * @param pot the wanted potential 
		 */
		void setNeuronPotential(unsigned int index, double pot);
		
		/**
		 * @brief Method that adds a connection to one neuron in the network
		 * @param index the index of the neuron in the network
		 * @param connection the index of the other neuron that receives the spikes
		 */
		void addNeuronConnection(unsigned int index, unsigned int connection);
		
		/**
		 * @brief Getter that gets the potential of one neuron in the network
		 * @param index the index of the neuron in the network
		 * @return the potential of that neuron
		 */
		double getNeuronPotential(unsigned int index) const;
		
		/**
		 * @brief Setter that sets the buffer of one neuron in a particular time
		 * and tells that buffer if the incoming spike is excitatory or inhibitory
		 * @param index the index of the neuron in the network
		 * @param time ...
		 */
		void setNeuronBuffer(unsigned int index, unsigned int time, bool excitatory);
		
		/**
		 * @brief Getter that gets the clock in steps of a neuron in the network
		 * @param index the index of the neuron in the network
		 * @return the clock which is an unsigned int
		 */
		unsigned int getNeuronClock(unsigned int index) const;
		
		/**
		 * @brief Method that checks if at least one neuron spiked during a simulation
		 * @return boolean, true if it did
		 */
		bool didOneNeuronSpiked() const;

	private :

		unsigned int globalClock_; /**< the global clock of the network that increases until the end of a simulation*/
		std::vector <Neuron> neurons_; /**< a vector that contains all the neurons in our network*/
		unsigned int runTime_; /**< the time of the simulation in steps (1 step = 0.1ms) */
		unsigned int numNeurons_; /**< the total number of neurons in the network */
		unsigned int numExcitatory_; /**< the number of excitatory neurons in the network*/
		unsigned int numInhibitory_; /**< the number of inhibitory neurons in the network*/
		unsigned int numExcitatoryConnections_; /**< the number of excitatory connections in the network */
		unsigned int numInhibitoryConnections_; /**< the number of inhibitory connections in the network*/
		double mu_thr_; /**< */
		double mu_ext_; /**< */
		double lambda_; /**< the average number of spikes/step that one neuron receives apart of its connections*/
};

#endif /* NETWORK_HPP */


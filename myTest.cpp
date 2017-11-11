#include "gtest/gtest.h"
#include "neuron.hpp"
#include "network.hpp"

TEST(SingleNeuron,SimpleUpdate)
{
	Neuron n;
	n.update(1.0);
	EXPECT_EQ(n.getPotential(), (20.0)*(1-exp(-0.005)));
}

TEST(SingleNeuron,MultipleUpdate)
{
	Neuron n;
	for(int i(0);i<10000;i++)
	{
		n.update(1.0);
	}
	EXPECT_NEAR(n.getPotential(),20.0,0.1);
}

TEST(SingleNeuron,PotentialDecrease)
{
	Neuron n;
	n.setPotential(10.0);
	for(int i(0);i<10000;i++)
	{
		n.update(0.0);
	}
	EXPECT_NEAR(n.getPotential(),0.0,0.01);
}

TEST(SingleNeuron,SpikeNumber)
{
	Neuron n;
	for(int i (0);i<5000;i++)
	{
		n.update(1.01);
	}
	EXPECT_EQ(n.getNumSpikes(),5);
	EXPECT_EQ(n.getSpikeTime(0),924);
	EXPECT_EQ(n.getSpikeTime(1),1869);
	EXPECT_EQ(n.getSpikeTime(2),2814);
	EXPECT_EQ(n.getSpikeTime(3),3759);
	EXPECT_EQ(n.getSpikeTime(4),4704);
}

TEST(SingleNeuron,Buffer)
{
	Neuron n;
	n.setBuffer(3,true);
	for(int i(0);i<3;i++)
	{
		n.update(0.0,0.0);
	}
	EXPECT_NEAR(n.getPotential(),0.1,0.001);
}

TEST(TwoNeurons,NeuronStateDistribution)
{
	Network network(2);
	
	EXPECT_EQ(network.isNeuronExcitatory(0),true);
	EXPECT_EQ(network.isNeuronExcitatory(1),false);
}

TEST(TwoNeurons,SpikeTransmissionInNetwork)
{
	Network network(2,false);
	network.addNeuronConnection(0,1);
	network.setNeuronPotential(0, 500.0);
	network.setNeuronPotential(1, 0.0);
	network.simulation(15,false);
	EXPECT_EQ(network.getNeuronPotential(1),j_exc);
}

TEST(FullNetwork,NeuronStateDistribution)
{
	Network network(12500);
	
	for(int i(0);i<10000;i++)
	{
		EXPECT_EQ(network.isNeuronExcitatory(i),true);
	}	
	for(int i(10000);i<12500;i++)
	{
		EXPECT_EQ(network.isNeuronExcitatory(i),false);
	}
}

TEST(FullNetwork,PoissonDistribution)
{
	Network network(12500,false);
	network.simulation(1000,0.0,true);
	EXPECT_EQ(network.didOneNeuronSpiked(),true);
}


int main (int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

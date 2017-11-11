#include <cassert>
#include "network.hpp"

int main (int argc, char* argv[])
{
	Network network;
	network.simulation(10000);
	network.print();
	network.outputFile();
	return EXIT_SUCCESS;
}

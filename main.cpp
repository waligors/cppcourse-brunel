#include <iostream>
#include <fstream>
#include "neuron.hpp"
#include "network.hpp"
#include <cassert>

using namespace std;


//note : all the units are standard (sec, Volt, farad, ohms, etc..) so there's no issue with the formula
//the values are then adapted in ms, mV, mA form for the user
int main (int argc, char* argv[])
{
	Network network_;
	unsigned int time (0), time_a(0), time_b(0);
	double current(0.0);
	do
	{
		cout << endl << "Enter the External Current : (mA)..." << endl;
		cin >> current;
	} while(current == 0.0);
	current*=10; //mA to 10^-4A
	
	do
	{
		cout << endl << "Enter the Time a (between 0 and " << time_stop/10 << ") : (ms)" << endl;
		cin >> time_a;
		assert(time_a >= 0);
	} while(time_a*10 > time_stop);
	time_a*=10; //ms to 10^-4sec
	
	do
	{
		cout << endl << "Enter the Time b (between " << time_a/10 << " and " << time_stop/10 << ") : (ms)" << endl;
		cin >> time_b;
		assert(time_b >= 0);
	} while(time_b*10<=time_a && time_b*10 > time_stop);
	time_b*=10; //ms to 10^-4sec
	
	//main while-loop 
	while(time<time_stop)
	{
		if(time<time_a || time>time_b)
		{
			//updating the neuron with current = 0mA
			network_.update(dt,0.0);				
		}
		else
		{
			//updating the neuron with the current from the user
			network_.update(dt,current);						
		}
		//computing time
		//cout << "step :" << time << endl;
		time++;
	}
	
	return 0;
}


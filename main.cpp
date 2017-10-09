#include <iostream>
#include <fstream>
#include "neuron.hpp"

using namespace std;


//note : all the units are standard (sec, Volt, farad, ohms, etc..) so there's no issue with the formula
//the values are then adapted in ms, mV, mA form for the user
int main (int argc, char* argv[])
{
	Neuron neuron;
	double time (0.0), current(0.0), time_a(0.0), time_b(0.0), time_stop(0.5); //all in sec
	
	do
	{
		cout << endl << "Enter the External Current : (mA)..." << endl;
		cin >> current;
	} while(current == 0.0);
	current/=1000; //mA to A
	
	do
	{
		cout << endl << "Enter the Time a (between 0 and " << time_stop << ") : (sec)" << endl;
		cin >> time_a;
	} while(time_a < 0.0 && time_a < time_stop);
	
	do
	{
		cout << endl << "Enter the Time b (between " << time_a << " and " << time_stop << ") : (sec)" << endl;
		cin >> time_b;
	} while(time_b<=time_a && time_b < time_stop);
	
	//opening the file
	ofstream cVar;
	cVar.open("variable.txt");
	if(cVar.fail())
	{
		cout << "Error while opening the file" << endl;
	}
	else
	{			
		cout << "Your file could be opened." << endl;
		
		//main while-loop 
		while(time<time_stop)
		{
			if(time<time_a || time>time_b)
			{
				//updating the neuron with current = 0mA
				neuron.update(time,dt,0.0);				
			}
			else
			{
				//updating the neuron with the current from the user
				neuron.update(time,dt,current);						
			}
			//wrting in the file the potential at given time (ex: 0.1 mV at time 54.8 ms.)
			cVar << neuron.getPot()*1000 << " mV at time " << time*1000 << " ms." << endl;
			
			//computing time
			time+=dt;
		}
		
		cVar << endl << "--SPIKES--" << endl;
		for(size_t i = 0; i < neuron.getNumSpikes(); i++)
		{
			//wrinting in the file all the spikes that occured at their respective time (ex: Spike 8 at 40.2 ms.)
			cVar << "Spike " << i+1 << " at " << neuron.getSpikeTime(i) << " ms." << endl;
		}
		
	}
	
	//closing the time
	cVar.close();
	
	return 0;
}


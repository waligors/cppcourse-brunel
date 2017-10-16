#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vector>
#include "constant.hpp"

using namespace std;

class Buffer
{
	public :
		//constructor
		Buffer ();
		void set(size_t c,double current);
		double get(size_t c);
		void print() const;
		
	private :
		vector <double> buffer_;
};

#endif



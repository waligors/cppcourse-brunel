#include "buffer.hpp"
#include <cmath>
#include <iostream>

using namespace std;

Buffer::Buffer ()
{
	for(size_t i = 0; i < buffer_size ;i++)
	{
		buffer_.push_back(0.0);
	}
}

void Buffer::set(size_t t,double current)
{
	buffer_[(t+delay)%buffer_size]+=current;
	//cout << "t : " << t <<". delay : " << delay << ". buffsize : " << buffer_size << endl;
	//cout << "buffer at time " << (t+delay)%buffer_size << " : " << buffer_[(t+delay)%buffer_size] << endl;
}

double Buffer::get (size_t t)
{
	double a(buffer_[t%buffer_size]);
	//cout <<"time : " << t << " buffer : " << buffer_[t%buffer_size] << endl;
	buffer_[t%buffer_size]= 0.0;
	return a;
}

void Buffer::print () const
{
	cout << "BUFFER" << endl;
	for(auto b : buffer_)
	{
		cout << b << endl;
	}
}

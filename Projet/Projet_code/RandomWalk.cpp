#include "RandomWalk.h"

// Default constructor 
RandomWalk::RandomWalk() {
	_size = 0;
	_mean = 0;
}

// Constructor with parameters 
RandomWalk::RandomWalk(int size, std::vector<double> vec, Distribution dist)
{
	_size = size;
	_values = vec;
	_mean = computeMean();
	_distribution = dist;
}

RandomWalk::~RandomWalk() {
	// Destructor
}

// Mean of the values of random walk 
double RandomWalk::computeMean() const{
	double sum = 0;
	for (int i = 0; i < _size; i++) {
		sum += _values.at(i);
	}
	return sum / (double)_size;
}

// Mean = computed mean
void RandomWalk::setMean() {
	_mean = computeMean();
}

// Setter with parameter
void RandomWalk::setMean(double mean) {
	_mean = mean;
}

/* GETTERS */
double RandomWalk::getMean() const {
	return _mean;
}

int RandomWalk::getSize() const {
	return _size;
}

double RandomWalk::getVariance() const{
	double sum = 0;
	for (int i = 0; i < _size; i++) {
		sum += (_values.at(i) - _mean)*(_values.at(i) - _mean);
	}
	return sum / (double)_size;
}

double RandomWalk::getSD() const {
	return sqrt(getVariance());
}

// Overloading the brackets 
double RandomWalk::operator[](int index) const {
	if (index < 0 || index >= _size) {
		std::cout << "Out of range" << std::endl;
		return NULL;
	}
	try
	{
		return _values.at(index);
	}
	catch (int error)
	{
		std::cout << "Invalid index" << std::endl;
		return NULL;
	}

}

#pragma once

#include <random>
#include <ctime>


// Object that generates random numbers between two limits.
class GeneradorAleatorios {

	// Random number generator.
	std::mt19937 gen;
	std::uniform_real_distribution<double> dist;

public:

	// Constructor.
	GeneradorAleatorios(double a, double b) : gen(std::time(0)), dist(a, b) {}

	// Returns a random number between the object limits.
	double get() { return dist(gen); }

};

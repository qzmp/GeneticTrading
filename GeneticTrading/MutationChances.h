#pragma once

#include <string>
using namespace std;

class MutationChances
{
private:

	// InternalNodes
	double cycleChance;
	double cutChance;
	double splitChance;
	double swapChance;

public:
	MutationChances(double cycleChance, double cutChance, double splitChance, double swapChance);
	MutationChances(double params);
	~MutationChances();

	double getCycleChance();
	double getCutChance();
	double getSplitChance();
	double getSwapChance();


	string toString();
};


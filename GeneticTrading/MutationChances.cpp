#include "MutationChances.h"



MutationChances::MutationChances(double cycleChance, double cutChance, double splitChance, double swapChance)
{
	this->cycleChance = cycleChance;
	this->cutChance = cutChance;
	this->splitChance = splitChance;
	this->swapChance = swapChance;

}

MutationChances::MutationChances(double params)
{
	this->cycleChance = params;
	this->cutChance = params;
	this->splitChance = params;
	this->swapChance = params;
}

MutationChances::~MutationChances()
{
}

double MutationChances::getCycleChance()
{
	return this->cycleChance;
}

double MutationChances::getCutChance()
{
	return this->cutChance;
}

double MutationChances::getSplitChance()
{
	return this->splitChance;
}

double MutationChances::getSwapChance()
{
	return this->swapChance;
}

string MutationChances::toString()
{
	return "oc;" + to_string(cycleChance) + " c;" + to_string(cutChance) + " s;" + to_string(splitChance) + " sw;" + to_string(swapChance);
}

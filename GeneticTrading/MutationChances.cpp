#include "MutationChances.h"



MutationChances::MutationChances(double operatorChangeChance, double cutChance, double splitChance, double swapChance, double valueChangeChance, double comparatorChangeChance, double indicatorChangeChance)
{
	// InternalNodes
	this->operatorChangeChance = operatorChangeChance;
	this->cutChance = cutChance;
	this->splitChance = splitChance;
	this->swapChance = swapChance;

	// LeafNodes
	this->valueChangeChance = valueChangeChance;
	this->comparatorChangeChance = comparatorChangeChance;
	this->indicatorChangeChance = indicatorChangeChance;

}

MutationChances::~MutationChances()
{
}

double MutationChances::getOperatorChangeChance()
{
	return this->operatorChangeChance;
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

double MutationChances::getValueChangeChance()
{
	return this->valueChangeChance;
}

double MutationChances::getComparatorChangeChance()
{
	return this->comparatorChangeChance;
}

double MutationChances::getIndicatorChangeChance()
{
	return this->indicatorChangeChance;
}

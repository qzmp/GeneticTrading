#pragma once

#include <string>
using namespace std;

class MutationChances
{
private:

	// InternalNodes
	double operatorChangeChance;
	double cutChance;
	double splitChance;
	double swapChance;

	// LeafNodes
	double valueChangeChance;
	double comparatorChangeChance;
	double indicatorChangeChance;

public:
	MutationChances(double operatorChangeChance, double cutChance, double splitChance, double swapChance, double valueChangeChance, double comparatorChangeChance, double indicatorChangeChance);
	~MutationChances();

	double getOperatorChangeChance();
	double getCutChance();
	double getSplitChance();
	double getSwapChance();

	double getValueChangeChance();
	double getComparatorChangeChance();
	double getIndicatorChangeChance();

	string toString();
};


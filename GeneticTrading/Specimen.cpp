#include "Specimen.h"



Specimen::Specimen(vector<shared_ptr<Indicator>> * indicators, MutationChances * mutationChances, int treeHeight) : bullTree(indicators, mutationChances, treeHeight), bearTree(indicators, mutationChances, treeHeight)
{
	bullTree.generateRandom();
	bearTree.generateRandom();
}


Specimen::~Specimen()
{
}

bool Specimen::bullActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return bullTree.isActive(currentPrice, indicatorValues);
}

bool Specimen::bearActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return bearTree.isActive(currentPrice, indicatorValues);
}

void Specimen::cross(Specimen & other)
{
	Tree & tempTree = this->bullTree;
	this->bullTree = other.bullTree;
	other.bullTree = tempTree;

	tempTree = this->bearTree;
	this->bearTree = other.bearTree;
	other.bearTree = tempTree;
}

void Specimen::mutate()
{
	bullTree.mutate();
	bearTree.mutate();
}

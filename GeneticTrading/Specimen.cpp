#include "Specimen.h"



Specimen::Specimen()
{
}

Specimen::Specimen(vector<shared_ptr<Indicator>> * indicators, MutationChances * mutationChances, int treeHeight) : bullTree(indicators, mutationChances, treeHeight), bearTree(indicators, mutationChances, treeHeight)
{
	bullTree.generateRandom();
	bearTree.generateRandom();
}

Specimen::Specimen(Tree bullTree, Tree bearTree) : bullTree(bullTree), bearTree(bearTree)
{
}

Specimen::Specimen(const Specimen & other) : bullTree(other.bullTree), bearTree(other.bearTree)
{ 
	
}

Specimen::~Specimen()
{
	//cout << "specimen destroyed" << endl;
}

bool Specimen::bullActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return bullTree.isActive(currentPrice, indicatorValues);
}

bool Specimen::bearActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return bearTree.isActive(currentPrice, indicatorValues);
}

Specimen Specimen::cross(Specimen &other)
{
	return Specimen(this->bullTree, other.bearTree);
}

void Specimen::mutate()
{
	bullTree.mutate();
	bearTree.mutate();
}
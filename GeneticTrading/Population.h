#pragma once

#include "Specimen.h"
class Population
{
private:
	vector<Specimen> specimens;
public:
	Population();
	~Population();

	vector<Specimen> select();
};


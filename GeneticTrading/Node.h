#pragma once

#include <memory>
#include "Indicator.h"
#include <vector>
#include <map>

using namespace std;

class Node
{
public:
	Node();
	~Node();

	virtual bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues) = 0;
};


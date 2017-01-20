#pragma once

#include "DataSet.h"
#include "SimpleMovingAverage.h"
#include "RateOfChange.h"
#include "RelativeStrengthIndex.h"
#include "Specimen.h"
#include "Backtester.h"
#include "GeneticController.h"

class Controller
{
public:
	Controller();
	~Controller();

	void testParameters();
};

int main();
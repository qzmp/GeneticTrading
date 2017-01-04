#include "DataPreprocessor.h"



int DataPreprocessor::addHeaders(string currentHeaders, list<shared_ptr<Indicator>>& indicators, ofstream & outputStream)
{
	if (outputStream.is_open())
	{
		stringstream ss;
		ss << currentHeaders;
		for (auto& ind : indicators)
		{
			ss << "," << ind->getName() << "(" << ind->getPeriod() << ")";
		}
		outputStream << ss.str() << "\n";
		return 0;
	}
	return -1;
}

void DataPreprocessor::addIndicatorValues(ofstream & outputStream)
{
	for (auto& ind : indicators)
	{
		if (ind->hasEnoughData(closePrices.size()))
		{
			outputStream << "," << ind->calculate(closePrices);
		}
		else
		{
			outputStream << ", ";
		}
	}
	outputStream << "\n";
}


DataPreprocessor::DataPreprocessor(list<shared_ptr<Indicator>>& indicators)
{
	this->indicators = indicators;
}

DataPreprocessor::~DataPreprocessor()
{
}

int DataPreprocessor::addIndicators(string fileName)
{
	ifstream inputStream;
	inputStream.open(fileName);

	ofstream outputStream;
	outputStream.open(fileName + string("_preprocessed.csv"));

	if (inputStream.is_open() && outputStream.is_open())
	{
		int closePriceIndex = 4;
		int volumeIndex = 5;
		int storedPricesCount = 200;
		closePrices = list<double>();

		string token;
		string line;

		istringstream ss;

		int i;
		getline(inputStream, line);
		addHeaders(line, indicators, outputStream);

		while (getline(inputStream, line))
		{
			ss = istringstream(line);
			i = 0;
			outputStream << line;
			while (getline(ss, token, ','))
			{
				if (i == closePriceIndex)
				{
					if (closePrices.size() == storedPricesCount)
					{
						closePrices.pop_front();
					}
					closePrices.push_back(stod(token));
				}
				i++;
			}
			addIndicatorValues(outputStream);
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

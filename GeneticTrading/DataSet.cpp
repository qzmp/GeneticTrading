#include "DataSet.h"



int DataSet::getNeededLinesCount()
{
	int neededCount = 0;
	for (auto& ind : *(indicatorHolder.getAllIndicators()))
	{
		if (ind->getNeededDataCount() > neededCount) {
			neededCount = ind->getNeededDataCount();
		}
	}
	return neededCount;
}

void DataSet::saveLine(istringstream & ss)
{
	string token;
	getline(ss, token, ',');

}

void DataSet::countIndicators(list<double> & lastClosePrices)
{
	if (indicatorHolder.hasEnoughDataPoints(lastClosePrices.size()))
	{
		map<shared_ptr<Indicator>, double> newMap;
		indicators.push_back(newMap);
		for (auto& ind : *(indicatorHolder.getAllIndicators()))
		{
			indicators.back()[ind] = ind->calculate(lastClosePrices);
		}
	}
}

int DataSet::findStartIndex(string & filename, DateTime & start)
{
	ifstream inputStream;
	inputStream.open(filename);

	int i = 1;
	if (inputStream.is_open())
	{
		string line;
		string token;
		istringstream ss;

		getline(inputStream, line); // labels
		while (getline(inputStream, line)) 
		{
			ss = istringstream(line);
			getline(ss, token, ';');
			if (start < DateTime(token))
			{
				return i;
			}
			i++;
		}
	}
	else return -1;
}

DataSet::DataSet()
{
}

DataSet::DataSet(const DataSet & other) : start(other.start), end(other.end), timeStamps(other.timeStamps), openPrices(other.openPrices), closePrices(other.closePrices),
highPrices(other.highPrices), lowPrices(other.lowPrices), indicators(other.indicators), indicatorHolder(other.indicatorHolder)
{
}


DataSet::~DataSet()
{
}

int DataSet::loadData(string & fileName, DateTime & start, DateTime & end, IndicatorHolder & indicatorHolder)
{
	this->start = start;
	this->end = end;

	int startIndex = findStartIndex(fileName, start);
	if (startIndex < 0)
	{
		return -1;
	}

	ifstream inputStream;
	inputStream.open(fileName);

	this->indicatorHolder = indicatorHolder;

	int linesNeededForIndicators = getNeededLinesCount();
	if (startIndex - linesNeededForIndicators < 0)
	{
		return -2;
	}

	if (inputStream.is_open())
	{		
		list<double> lastClosePrices;
		string lastDateTimeString;
		double lastOpenPrice;
		double lastHighPrice;
		double lastLowPrice;
		double lastClosePrice;
		double previousLastClosePrice = 0;

		string token;
		string line;

		bool endReached = false;

		istringstream ss;
		
		int i;
		getline(inputStream, line); // labels
		int currentLineIndex = 1;
		while (getline(inputStream, line))
		{
			ss = istringstream(line);
			i = 0;
			if (currentLineIndex >= startIndex - linesNeededForIndicators + 1 && !endReached)
			{
				while (getline(ss, token, ';'))
				{
					switch (i)
					{
					case 0:
						lastDateTimeString = token;
						break;
					case 1:
						lastOpenPrice = stod(token);
						break;
					case 2:
						lastHighPrice = stod(token);
						break;
					case 3:
						lastLowPrice = stod(token);
						break;
					case 4:
						lastClosePrice = stod(token);
						
						if (lastClosePrices.size() == linesNeededForIndicators)
						{
							lastClosePrices.pop_front();
						}
						if (previousLastClosePrice != 0)
						{
							lastClosePrices.push_back(previousLastClosePrice);
						}
						previousLastClosePrice = lastClosePrice;
					}
					i++;
				}
				if (currentLineIndex > startIndex + 1)
				{
					DateTime lastDateTime(lastDateTimeString);
					if (!(lastDateTime < end))
					{
						endReached = true;
						break;
					}
					timeStamps.push_back(DateTime(lastDateTime));
					openPrices.push_back(lastOpenPrice);
					highPrices.push_back(lastHighPrice);
					lowPrices.push_back(lastLowPrice);
					closePrices.push_back(lastClosePrice);

					countIndicators(lastClosePrices);
				}
			}
			currentLineIndex++;
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

int DataSet::getSize()
{
	return closePrices.size();
}

double DataSet::getOpenPrice(int index)
{
	return openPrices[index];
}

double DataSet::getClosePrice(int index)
{
	return closePrices[index];
}

double DataSet::getHighPrice(int index)
{
	return highPrices[index];
}

double DataSet::getLowPrice(int index)
{
	return lowPrices[index];
}

map<shared_ptr<Indicator>, double>* DataSet::getIndicatorValues(int index)
{
	return &indicators[index];
}

DateTime DataSet::getStart()
{
	return start;
}

DateTime DataSet::getEnd()
{
	return end;
}

string DataSet::getName()
{
	return to_string(start.getDay()) + "." + to_string(start.getMonth()) + "." + to_string(start.getYear()) + "_" +
		to_string(end.getDay()) + "." + to_string(end.getMonth()) + "." + to_string(end.getYear());
}

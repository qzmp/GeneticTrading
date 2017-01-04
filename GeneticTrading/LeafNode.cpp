#include "LeafNode.h"



LeafNode::LeafNode(vector<shared_ptr<Indicator>> & indicators)
{
	srand(time(0));
	int randomIndicatorIndex = rand() % indicators.size();
	indicator = indicators[randomIndicatorIndex];
	greater = rand() % 2 == 0;
	value = rand() % numeric_limits<uint8_t>::max();
}

LeafNode::~LeafNode()
{
}

bool LeafNode::isActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return indicator->isActive(greater, value, currentPrice, indicatorValues[indicator]);
}

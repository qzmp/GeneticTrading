#include "Tree.h"


list<bool> Tree::getRandomPath() const
{
	list<bool> path;
	rootNode->getRandomPath(path);
	return path;
}

unique_ptr<Node> Tree::getNodeFromPath(list<bool>& path, int index) const
{
	return rootNode->getNodeFromPath(path.begin(), index);
}

void Tree::swapSubtree(list<bool>& path, int index, unique_ptr<Node>& subtree)
{
	rootNode->swapSubtree(path.begin(), index, subtree);
}

Tree::Tree()
{
}

Tree::Tree(IndicatorHolder * indicators, MutationChances * mutationChances, int maxTreeHeight) 
	: indicators(indicators), mutationChances(mutationChances), maxTreeHeight(maxTreeHeight)
{
}

Tree::Tree(const Tree & other)
	: rootNode(make_unique<InternalNode>(*other.rootNode)), indicators(other.indicators), 
	mutationChances(other.mutationChances), maxTreeHeight(other.maxTreeHeight)
{
}

Tree::~Tree()
{
	//cout << "tree destroyed" << endl;
}

void Tree::generateRandom()
{
	rootNode = unique_ptr<InternalNode>(new InternalNode(1, this));
}

bool Tree::isActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues) const
{
	return rootNode->isActive(currentPrice, indicatorValues);
}

void Tree::mutate()
{
	if (rand() / double(RAND_MAX) < mutationChances->getCutChance())
	{
		bool cutLeft = rand() % 2 == 0;
		if (cutLeft)
		{
			if (!rootNode->isRightLeaf())
			{
				rootNode.reset((InternalNode*)rootNode->releaseRight());
			}
			else if (!rootNode->isLeftLeaf())
			{
				rootNode.reset((InternalNode*)rootNode->releaseLeft());
			}
		}
		else
		{
			if (!rootNode->isLeftLeaf())
			{
				rootNode.reset((InternalNode*)rootNode->releaseLeft());
			}
			else if (!rootNode->isRightLeaf())
			{
				rootNode.reset((InternalNode*)rootNode->releaseRight());
			}
		}
	}
	rootNode->mutate(*rootNode, false, 0, this);
}

MutationChances * Tree::getMutationChances()
{
	return mutationChances;
}

IndicatorHolder* Tree::getIndicators()
{
	return indicators;
}

int Tree::getMaxHeight()
{
	return maxTreeHeight;
}

int Tree::getSize()
{
	return rootNode->getSize();
}

unique_ptr<Tree> Tree::crossLeft(const Tree& other)
{
	unique_ptr<Tree> child = make_unique<Tree>(Tree(*this));
	child->rootNode->setLeft(other.rootNode->getLeftCopy());
	return child;
}

unique_ptr<Tree> Tree::crossRight(const Tree& other)
{
	unique_ptr<Tree> child = make_unique<Tree>(Tree(*this));
	child->rootNode->setRight(other.rootNode->getRightCopy());
	return child;
}

pair<unique_ptr<Tree>, unique_ptr<Tree>> Tree::cross(const Tree & other)
{
	unique_ptr<Tree> child1 = make_unique<Tree>(Tree(*this));
	unique_ptr<Tree> child2 = make_unique<Tree>(Tree(other));

	list<bool> firstPath = this->getRandomPath();
	list<bool> secondPath = other.getRandomPath();
	int firstIndex = rand() % firstPath.size();
	int secondIndex = rand() % secondPath.size();
	unique_ptr<Node> firstSubtree = this->getNodeFromPath(firstPath, firstIndex);
	unique_ptr<Node> secondSubtree = other.getNodeFromPath(secondPath, secondIndex);
	child1->rootNode->swapSubtree(firstPath.begin(), firstIndex, secondSubtree);
	child2->rootNode->swapSubtree(secondPath.begin(), secondIndex, firstSubtree);

	return pair<unique_ptr<Tree>, unique_ptr<Tree>>(move(child1), move(child2));
}

string Tree::drawLatex()
{
	stringstream ss;
	ss << "\\begin{tikzpicture}[every leaf node/.style =" << endl;
	ss << "{draw,rectangle,minimum width = {3em}}," << endl;
	ss << "every internal node/.style = {draw, circle, child anchor=center}]" << endl;
	ss << "\\tikzset{edge from parent/.style=" << endl;
	ss << "{draw, edge from parent path = { (\\tikzparentnode.south)" << endl;
	ss << "-- + (0,-4pt)- | (\\tikzchildnode) }}}" << endl;
	ss << "\\Tree" << endl;
	rootNode->writeLatex(ss);
	ss << "\\end{tikzpicture}" << endl;

	return ss.str();
}

shared_ptr<Node> Tree::getRandomNode()
{
	int index = 0;
	return rootNode->getNodeFromPath(getRandomPath().begin(), index);
}

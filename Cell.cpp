#include "Cell.h"

Cell::Cell(char type,int x_,int y_)
{
	switch (type)
	{
	case 's':
		this->state = START;
		break;
	case 'f':
		this->state = FINISH;
		this->isPath = true;
		break;
	case '0':
		this->state = NOT_VISITED;
		this->isPath = false;
		break;
	default:
		this->state = BLOCKED;
		this->isPath = false;
		break;
	}
	this->cost = this->state == START ? 0 : -1;
	this->location.first = x_;
	this->location.second = y_;
	this->previous = nullptr;
}

void Cell::addNeighbors(Cell& other)
{
	if (this->neighbors.size() == 8)/*add Neighbors point*/
		return;
	if (abs(this->getX() - other.getX()) <= 1 && abs(this->getY() - other.getY()) <= 1)
		if (this->getX() != other.getX() || this->getY() != other.getY())
			neighbors.push_back(std::ref(other));
}

void Cell::changeNeighborsCost()
{
	/*"visit" neighbors point and change its costs*/
	for (auto& el : neighbors)
	{
		if (el.get().cost != -1 || el.get().state == BLOCKED || el.get().state == VISITED)
			continue;
		el.get().changeCost(this->cost);
		el.get().setPrevious(*this);
	}
	if (this->state!= START)
		this->state = VISITED;
}

std::vector<std::reference_wrapper<Cell>>& Cell::getNeighbors()
{
	return this->neighbors;
}

Cell::Statement Cell::getState()
{
	return this->state;
}

Cell* Cell::getPrevious()
{
	return previous;
}

void Cell::buildPath()
{
	/*build path from FINISH to START*/
	if (this->previous == nullptr)
		return;
	this->isPath = true;
	this->previous->buildPath();
}

bool Cell::inPath()
{
	return this->isPath;
}

void Cell::setPath()
{
	isPath = true;
}

std::pair<int, int> Cell::getLocation()
{
	return this->location;
}

int Cell::getX()
{
	return location.first;
}

int Cell::getY()
{
	return location.second;
}

void Cell::changeCost(int previousCost)
{
	this->cost = previousCost + 1;
}

void Cell::setPrevious(Cell& cell)
{
	this->previous = &cell;
}

#include "Field.h"

void Field::fillCellList()
{
	std::fstream in;
	in.open(pathLoad);
	try
	{
		int count = 0;
		int x = 0;
		int y = 0;
		while (!in.eof() && count < (size + 1) * (size + 1))
		{
			char ch;
			in >> ch;
			this->cellList.push_back(Cell(ch, x, y));
			y = x == size ? y + 1 : y;
			x = x == size ? 0 : x + 1;
			count++;
		}
		in.close();
	}
	catch (const std::ifstream::failure& ex)
	{
		std::cout << "Exception opening/readin file";
		in.close();
	}
}

void Field::setPatch(Cell & cell)
{
	cell.setPath();
}

Field::Field(int size_, std::string pathLoad_)
{
	this->size = size_ - 1;
	this->pathLoad = pathLoad_;
	this->fillCellList();
	for (auto& el : cellList)
		for (auto& elOther : cellList)
			el.addNeighbors(elOther);
	std::cout << "Filed Map";
}

Cell& Field::getStartCell()
{
	for (auto& el : cellList)
		if (el.getState() == Cell::START)
			return std::ref(el);
}

int Field::getSize()
{
	return this->size;
}

void Field::insertPatch(Cell finish)
{
	/*some trouble with reference
	that's why it builds here*/
	if (finish.getPrevious() == nullptr)
		return;
	auto it = std::find_if(cellList.begin(), cellList.end(), [&finish](Cell& el) {return el.getLocation() == finish.getLocation(); });
	(*it).setPath();
	insertPatch(*finish.getPrevious());
}

std::vector<Cell >& Field::getFullCellList()
{
	return cellList;
}

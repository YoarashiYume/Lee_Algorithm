#include "WaveAlgorithm.h"

WaveAlgorithm::WaveAlgorithm(Field f, std::string savePach_)
{
	this->savePach = savePach_;
	/*add start point in buffer*/
	this->cellList.push_back(f.getStartCell());
	this->size = f.getSize();
	while (!cellList.empty()&&std::find_if(cellList.begin(), cellList.end(), [](auto& cCell) {return cCell.get().getState() == Cell::FINISH; }) == cellList.end())
	{
		cellList.front().get().changeNeighborsCost();
		auto temp = cellList.front().get().getNeighbors();
		/*add only NOT_VISITED and FINISH point*/
		for (auto& el : temp)
			if (el.get().getState() == Cell::NOT_VISITED || el.get().getState() == Cell::FINISH)
				cellList.push_back(std::ref(el));
		cellList.erase(cellList.begin());
		/*if something switched to VISITED - remove it*/
		cellList.erase(std::remove_if(cellList.begin(), cellList.end(), [](auto& cCell) {return cCell.get().getState() == Cell::VISITED; }),cellList.end());
	}
	if (cellList.empty())
	{
		std::cout << "No way\n";
	}
	else
	{
		f.insertPatch((*std::find_if(cellList.begin(), cellList.end(), [](auto& cCell) {return cCell.get().getState() == Cell::FINISH; })));
		saveResult(f);
	}
}

void WaveAlgorithm::saveResult(Field f)
{
	/*simple outprint*/
	std::ofstream out;
	out.open(savePach);
	auto field = f.getFullCellList();
	try
	{
		for (size_t i = 0; i < (size+1) * (size+1); ++i)
		{
			if (i % (size+1) == 0 && i != 0)
				out << std::endl;
			if (field[i].getState() == Cell::FINISH)
				out << 'F' << " ";
			else if (field[i].inPath())
				out << '*' << " ";
			else if (field[i].getState()==Cell::BLOCKED)
				out << '1' << " ";
			else if (field[i].getState() == Cell::START)
				out << 'S' << " ";
			else
				out << '0' << " ";
		}
		out.close();
	}
	catch (const std::ifstream::failure& ex)
	{
		std::cout << "Exception opening/readin file";
		out.close();
	}
}

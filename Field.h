#ifndef _FIELD_H_
#define _FIELD_H_
#include "Cell.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
class Field
{
private:
	int size;
	std::string pathLoad;
	std::vector<Cell> cellList;
	void fillCellList();
	void setPatch(Cell& cell);
public:
	Field(int size_,std::string pathLoad_);
	Cell& getStartCell();
	int getSize();
	void insertPatch(Cell finish);
	std::vector<Cell>& getFullCellList();
};
#endif // !_FIELD_H_
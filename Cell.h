#ifndef _CELL_H_
#define _CELL_H_
#include <vector>
#include <algorithm>
#include <utility>
class Cell
{
public:
	enum Statement {
		START,
		FINISH,
		NOT_VISITED,
		VISITED,
		BLOCKED
	};
private:
	int cost;
	std::vector<std::reference_wrapper<Cell>> neighbors;
	Statement state;
	std::pair<int, int> location;
	Cell* previous;
	bool isPath;
	int getX();
	int getY();
	void changeCost(int previousCost);
	void setPrevious(Cell& cell);
	
public:
	Cell(char type, int x_, int y_);
	void addNeighbors(Cell& other);
	void changeNeighborsCost();
	std::vector<std::reference_wrapper<Cell>>& getNeighbors();
	Statement getState();
	Cell* getPrevious();
	void buildPath();
	bool inPath();
	void setPath();
	std::pair<int, int> getLocation();
};
#endif // !_CELL_H_
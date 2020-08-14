#ifndef _WAVEALGORITHM_H_
#define _WAVEALGORITHM_H_
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Cell.h"
#include "Field.h"
class WaveAlgorithm
{
private:
	int size;
	std::vector<std::reference_wrapper<Cell>> cellList;
	std::string savePach;
	void saveResult(Field f);
public:
	WaveAlgorithm(Field f,std::string savePach_);
	
};
#endif // !_WAVEALGORITHM_H_

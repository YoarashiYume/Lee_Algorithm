#include <iostream>
#include "Field.h"
#include "WaveAlgorithm.h"

int main(int argc, char* argv[])
{
	if (argc < 4) {
		std::cout << "usage: <prog-name> <sizeOfSqareMatrix> <input.txt>  <output.txt>\n";
		std::system("pause");
		return 1;
	}
	int size = std::atoi(argv[1]);
	Field f(size,argv[2]);
	WaveAlgorithm(f, argv[3]);
	return 0;
}
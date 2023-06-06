#pragma once

#include <iostream>
#include <string>
#include <list>
#include <array>

class cfop
{
public:
	std::list<std::string> solveQueue;

	const std::string solvedCube[6][3][3] =
	{ {   { "W1", "W2", "W3" }, { "W4" "W5", "W6" }, { "W7", "W8", "W9" }  },
	  {   { "G1", "G2", "G3" }, { "G4" "G5", "G6" }, { "G7", "G8", "G9" }  },
	  {   { "R1", "R2", "R3" }, { "R4" "R5", "R6" }, { "R7", "R8", "R9" }  },
	  {   { "B1", "B2", "B3" }, { "B4" "B5", "B6" }, { "B7", "B8", "B9" }  },
	  {   { "O1", "O2", "O3" }, { "O4" "O5", "O6" }, { "O7", "O8", "O9" }  },
	  {   { "Y1", "Y2", "Y3" }, { "Y4" "Y5", "Y6" }, { "Y7", "Y8", "Y9" }  },
	};

	std::string cube[6][3][3];

public:
	cfop();
	cfop(std::string _cube[6][3][3]);
	~cfop();

	void setCube(std::string _cube[6][3][3]);
	void setCubie(std::string cubie, int position[3]);

	void addToQueue(std::string turn);
	void addToQueue(std::string turn[]);
	void printQueue();

	std::array<int, 3> findCubie(std::string cubie);

	void solveCube();
	void cross();
	void f2l();
	void oll();
	void pll();
};


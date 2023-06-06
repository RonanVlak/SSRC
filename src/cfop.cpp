#include "cfop.h"

cfop::cfop()
{
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				cube[i][j][k] = solvedCube[i][j][k]; // assume a solved cube is entered
			}
		}
	}
}

cfop::cfop(std::string _cube[6][3][3])
{
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				cube[i][j][k] = _cube[i][j][k];
			}
		}
	}
}

cfop::~cfop()
{
}

void cfop::setCube(std::string _cube[6][3][3]) {
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				cube[i][j][k] = _cube[i][j][k];
			}
		}
	}
}

void cfop::setCubie(std::string cubie, int position[3]) {
	cube[position[0]][position[1]][position[2]] = cubie;
}

void cfop::addToQueue(std::string turn) {
	solveQueue.push_back(turn);
	// ****** turn cube according to input ******
}

void cfop::addToQueue(std::string turn[]) {
    for (int i = 0; i < turn->size(); i++) {
        solveQueue.push_back(turn[i]);
    }
    // ****** turn cube according to input ******
}

void cfop::printQueue() {
    if (solveQueue.empty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }
    for (const std::string& str : solveQueue) {
        std::cout << str << ", ";
    }
}

std::array<int, 3> cfop::findCubie(std::string cubie) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (cube[i][j][k] == cubie) {
                    return { i, j, k };
                }
            }
        }
    }
    return { 6, 6, 6 };
}

void cfop::solveCube()
{
	cross();
	// f2l();
	// oll();
	// pll();
}

void cfop::cross()
{
    // reposition W2, W4, W6 and W8 to the correct place
    std::string crossCubies[4] = { "W2", "W4", "W6", "W8" };
    for (int i = 0; i < 4; i++) {
        bool correctPlace = false;
        while (!correctPlace) {
            // find position of cubie
            std::array<int, 3> foundPosition = findCubie(crossCubies[i]);
            // check if the found position is the correct one by comparing it to the solved state of the cube
            //try{
            if (cube[foundPosition[0]][foundPosition[1]][foundPosition[2]] ==
                solvedCube[foundPosition[0]][foundPosition[1]][foundPosition[2]]) {
                correctPlace = true;
                break;
            }
            //}
            //catch(){}

            switch (foundPosition[0]) {
            case 0:
                // on the correct face but not correct place
                if (i == 0) { // first cubie can be turned to correct face
                    solveQueue.push_back("D"); // keep turning 'down' clockwise until correct place found
                    break;
                }
                if (foundPosition[2] == 0) {
                    //turn left side twice, makes sure that the cubie is on the top side
                    solveQueue.push_back("L");
                    solveQueue.push_back("L");
                }
                else if (foundPosition[2] == 1) {
                    //turn back side twice, makes sure that the cubie is on the top side
                    solveQueue.push_back("B");
                    solveQueue.push_back("B");
                }
                else if (foundPosition[2] == 2) {
                    //turn right side twice, makes sure that the cubie is on the top side
                    solveQueue.push_back("R");
                    solveQueue.push_back("R");
                }
                break;
            case 1:// left face, turn to upper side
                if (foundPosition[2] == 1 && foundPosition[1] == 0) {
                    solveQueue.push_back("L");
                    solveQueue.push_back("F");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'F");
                    solveQueue.push_back("'L");
                }
                else if (foundPosition[2] == 1 && foundPosition[1] == 2) {
                    solveQueue.push_back("'L");
                    solveQueue.push_back("F");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'F");
                    solveQueue.push_back("L");
                }
                else if (foundPosition[2] == 0 && foundPosition[1] == 1) {
                    solveQueue.push_back("'B");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("B");
                }
                else if (foundPosition[2] == 2 && foundPosition[1] == 1) {
                    solveQueue.push_back("F");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'F");
                }
                break;
            case 2:// front face, turn to upper side
                if (foundPosition[2] == 1 && foundPosition[1] == 0) {
                    solveQueue.push_back("F");
                    solveQueue.push_back("R");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'R");
                    solveQueue.push_back("'F");
                }
                else if (foundPosition[2] == 1 && foundPosition[1] == 2) {
                    solveQueue.push_back("'F");
                    solveQueue.push_back("R");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'R");
                    solveQueue.push_back("F");
                }
                else if (foundPosition[2] == 0 && foundPosition[1] == 1) {
                    solveQueue.push_back("'L");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("L");
                }
                else if (foundPosition[2] == 2 && foundPosition[1] == 1) {
                    solveQueue.push_back("R");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'R");
                }
                break;
            case 3:// right face, turn to upper side
                if (foundPosition[2] == 1 && foundPosition[1] == 0) {
                    solveQueue.push_back("R");
                    solveQueue.push_back("B");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'B");
                    solveQueue.push_back("'R");
                }
                else if (foundPosition[2] == 1 && foundPosition[1] == 2) {
                    solveQueue.push_back("'R");
                    solveQueue.push_back("B");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'B");
                    solveQueue.push_back("R");
                }
                else if (foundPosition[2] == 0 && foundPosition[1] == 1) {
                    solveQueue.push_back("'F");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("F");
                }
                else if (foundPosition[2] == 2 && foundPosition[1] == 1) {
                    solveQueue.push_back("B");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'B");
                }
                break;
            case 4:// back face, turn to upper side
                if (foundPosition[2] == 1 && foundPosition[1] == 0) {
                    solveQueue.push_back("B");
                    solveQueue.push_back("L");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'L");
                    solveQueue.push_back("'B");
                }
                else if (foundPosition[2] == 1 && foundPosition[1] == 2) {
                    solveQueue.push_back("'B");
                    solveQueue.push_back("L");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'L");
                    solveQueue.push_back("B");
                }
                else if (foundPosition[2] == 0 && foundPosition[1] == 1) {
                    solveQueue.push_back("'R");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("R");
                }
                else if (foundPosition[2] == 2 && foundPosition[1] == 1) {
                    solveQueue.push_back("L");
                    solveQueue.push_back("'U");
                    solveQueue.push_back("'L");
                }
                break;
            case 5:
                // it's on the opposite face, turn to correct position, then push it in correct position.
                // first check which cubie is currently being put in position
                switch (i) {
                case 0: // cubie W2
                    if (foundPosition[1] != 2) {
                        solveQueue.push_back("U");
                    }
                    else { // correct position on top side found, turn to white side
                        solveQueue.push_back("F");
                        solveQueue.push_back("F");
                    }
                    break;
                case 1: // cubie W4
                    if (foundPosition[2] != 0) {
                        solveQueue.push_back("U");
                    }
                    else { // correct position on top side found, turn to white side
                        solveQueue.push_back("L");
                        solveQueue.push_back("L");
                    }
                    break;
                case 2: // cubie W6
                    if (foundPosition[2] != 2) {
                        solveQueue.push_back("U");
                    }
                    else { // correct position on top side found, turn to white side
                        solveQueue.push_back("R");
                        solveQueue.push_back("R");
                    }
                    break;
                case 3: // cubie W8
                    if (foundPosition[1] != 2) {
                        solveQueue.push_back("U");
                    }
                    else { // correct position on top side found, turn to white side
                        solveQueue.push_back("B");
                        solveQueue.push_back("B");
                    }
                    break;
                default:
                    std::cout << "Error in phase 1 cross:" << std::endl;
                    std::cout << "Unknown cubie" << std::endl;
                    return;
                    break;
                }
                break;
            default:
                std::cout << "Error in phase 1 cross:" << std::endl;
                std::cout << "Unknown side was found" << std::endl;
                return;
                break;
            }
        }
    }
}

void cfop::f2l()
{
}

void cfop::oll()
{
}

void cfop::pll()
{
}

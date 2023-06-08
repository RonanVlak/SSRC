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
    std::string testCube[6][3][3] =
    {
{{ "B3", "B6", "Y3" }, { "G6", "W5", "R2" }, { "B9", "W6", "G7" }},
{{ "G9", "B8", "B7" }, { "B2", "O5", "G4" }, { "W3", "O4", "Y9" }},
{{ "O9", "O2", "Y1" }, { "R6", "B5", "B4" }, { "R1", "R4", "G1" }},
{{ "G3", "G8", "O3" }, { "O6", "R5", "Y2" }, { "R3", "Y6", "W9" }},
{{ "B1", "W4", "O7" }, { "G2", "G5", "Y8" }, { "R9", "R8", "R7" }},
{{ "W7", "O8", "Y7" }, { "W2", "Y5", "W8" }, { "W1", "Y4", "O1" }},
    };;

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				cube[i][j][k] = testCube[i][j][k];
			}
		}
	}
}

void cfop::setCubie(std::string cubie, int position[3]) {
	cube[position[0]][position[1]][position[2]] = cubie;
}

/*
* fill solveQueue with the next symbols:
* "U" = up
* "D" = down
* "L" = left
* "R" = right
* "F" = front
* "B" = back
* ' indicates counter clockwise
*/
void cfop::addToQueue(const std::string& turn) {
	solveQueue.push_back(turn);
    if (turn == "F") { rotateFaceClockwise(FRONT); }
    else if (turn == "'F") { rotateFaceCounterClockwise(FRONT); }
    else if (turn == "L") { rotateFaceClockwise(LEFT); }
    else if (turn == "'L") { rotateFaceCounterClockwise(LEFT); }
    else if (turn == "R") { rotateFaceClockwise(RIGHT); }
    else if (turn == "'R") { rotateFaceCounterClockwise(RIGHT); }
    else if (turn == "B") { rotateFaceClockwise(BACK); }
    else if (turn == "'B") { rotateFaceCounterClockwise(BACK); }
    else if (turn == "U") { rotateFaceClockwise(UP); }
    else if (turn == "'U") { rotateFaceCounterClockwise(UP); }
    else if (turn == "D") { rotateFaceClockwise(DOWN); }
    else if (turn == "'D") { rotateFaceCounterClockwise(DOWN); }
}
int nrMoves = 0;
void cfop::addToQueue(const std::string turn[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        nrMoves++;
        std::cout << "Move " << nrMoves << ":" << turn[i] << std::endl;
        solveQueue.push_back(turn[i]);

        if (turn[i] == "F") { rotateFaceClockwise(FRONT); }
        else if (turn[i] == "'F") { rotateFaceCounterClockwise(FRONT); }
        else if (turn[i] == "L") { rotateFaceClockwise(LEFT); }
        else if (turn[i] == "'L") { rotateFaceCounterClockwise(LEFT); }
        else if (turn[i] == "R") { rotateFaceClockwise(RIGHT); }
        else if (turn[i] == "'R") { rotateFaceCounterClockwise(RIGHT); }
        else if (turn[i] == "B") { rotateFaceClockwise(BACK); }
        else if (turn[i] == "'B") { rotateFaceCounterClockwise(BACK); }
        else if (turn[i] == "U") { rotateFaceClockwise(UP); }
        else if (turn[i] == "'U") { rotateFaceCounterClockwise(UP); }
        else if (turn[i] == "D") { rotateFaceClockwise(DOWN); }
        else if (turn[i] == "'D") { rotateFaceCounterClockwise(DOWN); }
        printCube();
    }
   // delete[] turn;
}

void cfop::printQueue() {
    if (solveQueue.empty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }
    for (const std::string& value : solveQueue) {
        std::cout << value << ",";
    }
    std::cout << std::endl;
}

void cfop::printCube() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                std::cout << cube[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
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
    printCube();
    std::cout << "CROSS PHASE COMPLETED. START FIRST LAYER." << std::endl;
	firstLayer();
    printCube();
    //std::cout << "FIRST LAYER PHASE COMPLETED. START SECOND LAYER." << std::endl;
	//secondLayer();
    //printCube();
    //std::cout << "F2L PHASE COMPLETED. START OLL." << std::endl;
	//oll();
    //printCube();
    //std::cout << "OLL PHASE COMPLETED. START MATCHING YELLOW CROSS COLORS." << std::endl;
    //yellowCrossColors();
    //printCube();
    //std::cout << "YELLOW CROSS COLORS COMPLETED. START PLLPART1." << std::endl;
    //pllPart1();
    //printCube();
    //std::cout << "PLLPART1 COMPLETED. START PLLPART2." << std::endl;
    //pllPart2();
    //printCube();
    //std::cout << "PLLPART2 COMPLETED. CUBE SOLVED." << std::endl;
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
            case 0: // white face
                // on the correct face but not correct place
                if (i == 0) { // first cubie can be turned to correct face
                    addToQueue("D"); // keep turning 'down' clockwise until correct place found
                    break;
                }
                if (foundPosition[2] == 0) {
                    //turn left side twice, makes sure that the cubie is on the top side
                    std::string turns[] = { "L", "L" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 1 && foundPosition[1] == 2) {
                    //turn back side twice, makes sure that the cubie is on the top side
                    std::string turns[] = { "B", "B" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 2) {
                    //turn right side twice, makes sure that the cubie is on the top side
                    std::string turns[] = { "R", "R" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 1:// left face, turn to upper side
                if (foundPosition[2] == 1 && foundPosition[1] == 0) {
                    std::string turns[] = { "L", "F", "'U", "'F", "'L"};
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 1 && foundPosition[1] == 2) {
                    std::string turns[] = { "'L", "F", "'U", "'F", "'L" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 0 && foundPosition[1] == 1) {
                    std::string turns[] = { "'B", "'U", "B" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 2 && foundPosition[1] == 1) {
                    std::string turns[] = { "F", "'U", "'F"};
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 2:// front face, turn to upper side
                if (foundPosition[2] == 1 && foundPosition[1] == 0) {
                    std::string turns[] = { "F", "R", "'U", "'R", "'F" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 1 && foundPosition[1] == 2) {
                    std::string turns[] = { "'F", "R", "'U", "'R", "F" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 0 && foundPosition[1] == 1) {
                    std::string turns[] = { "'L", "'U", "L"};
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 2 && foundPosition[1] == 1) {
                    std::string turns[] = { "R", "'U", "R" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 3:// right face, turn to upper side
                if (foundPosition[2] == 1 && foundPosition[1] == 0) {
                    std::string turns[] = { "R", "B", "'U", "'B", "'R"};
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 1 && foundPosition[1] == 2) {
                    std::string turns[] = { "R", "B", "'U", "'B", "'R" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 0 && foundPosition[1] == 1) {
                    std::string turns[] = { "'F", "'U", "F"};
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 2 && foundPosition[1] == 1) {
                    std::string turns[] = { "B", "'U", "'B" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 4:// back face, turn to upper side
                if (foundPosition[2] == 1 && foundPosition[1] == 0) {
                    std::string turns[] = { "B", "L", "'U", "'L", "'B"};
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 1 && foundPosition[1] == 2) {
                    std::string turns[] = { "'B", "L", "'U", "'L", "B" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 0 && foundPosition[1] == 1) {
                    std::string turns[] = { "'R", "'U", "R" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[2] == 2 && foundPosition[1] == 1) {
                    std::string turns[] = { "L", "'U", "'L" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 5:
                // it's on the top face, turn to correct position, then push it in correct position.
                // first check which cubie is currently being put in position
                switch (i) {
                case 0: // cubie W2
                    if (foundPosition[1] != 2) {
                        addToQueue("U");
                    }
                    else { // correct position on top side found, turn to white side
                        std::string turns[] = { "F", "F" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    break;
                case 1: // cubie W4
                    if (foundPosition[2] != 0) {
                        addToQueue("U");
                    }
                    else { // correct position on top side found, turn to white side
                        std::string turns[] = { "L", "L" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    break;
                case 2: // cubie W6
                    if (foundPosition[2] != 2) {
                        addToQueue("U");
                    }
                    else { // correct position on top side found, turn to white side
                        std::string turns[] = { "R", "R" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    break;
                case 3: // cubie W8
                    if (foundPosition[1] != 0) {
                        addToQueue("U");
                    }
                    else { // correct position on top side found, turn to white side
                        std::string turns[] = { "B", "B" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
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

void cfop::firstLayer() {
    std::string firstLayerCubies[4] = { "W1", "W3", "W7", "W9" };
    for (int i = 0; i < 4; i++) {
        bool correctPlace = false;
        while (!correctPlace) {
            // find position of cubie
            std::array<int, 3> foundPosition = findCubie(firstLayerCubies[i]);
            // check if the found position is the correct one by comparing it to the solved state of the cube
            if (cube[foundPosition[0]][foundPosition[1]][foundPosition[2]] ==
                solvedCube[foundPosition[0]][foundPosition[1]][foundPosition[2]]) {
                correctPlace = true;
                break;
            }

            switch (foundPosition[0]) {
            case 0: // white face
                // on white face but incorrect corner, get it out, turn to correct place
                if (foundPosition[1] == 0 && foundPosition[2] == 0) { // top left
                    std::string turns[] = { "F", "U", "'F", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[1] == 0 && foundPosition[2] == 2) { // top right
                    std::string turns[] = { "R", "U", "'R", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 0) { // bottom left
                    std::string turns[] = { "L", "U", "'L", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 2) { // bottom right
                    std::string turns[] = { "B", "U", "'B", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 1:
                if (foundPosition[1] == 0 && foundPosition[2] == 0) { // top left
                    if (i == 2) {
                        std::string turns[] = { "L", "U", "'L", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }// turn to another face
                }
                else if (foundPosition[1] == 0 && foundPosition[2] == 2) { // top right
                    if (i == 0) {
                        std::string turns[] = { "F", "U", "'F", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 0) { // bottom left
                    std::string turns[] = { "L", "U", "'L", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 2) { // bottom right
                    std::string turns[] = { "F", "U", "'F", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 2:
                if (foundPosition[1] == 0 && foundPosition[2] == 0) { // top left
                    if (i == 0) {
                        std::string turns[] = { "F", "U", "'F", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }// turn to another face
                }
                else if (foundPosition[1] == 0 && foundPosition[2] == 2) { // top right
                    if (i == 1) {
                        std::string turns[] = { "R", "U", "'R", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 0) { // bottom left
                    std::string turns[] = { "F", "U", "'F", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 2) { // bottom right
                    std::string turns[] = { "R", "U", "'R", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 3: // right face
                if (foundPosition[1] == 0 && foundPosition[2] == 0) { // top left
                    if (i == 1) {
                        std::string turns[] = { "R", "U", "'R", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }// turn to another face
                }
                else if (foundPosition[1] == 0 && foundPosition[2] == 2) { // top right
                    if (i == 3) {
                        std::string turns[] = { "B", "U", "'B", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 0) { // bottom left
                    std::string turns[] = { "R", "U", "'R", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 2) { // bottom right
                    std::string turns[] = { "B", "U", "'B", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 4:
                if (foundPosition[1] == 0 && foundPosition[2] == 0) { // top left
                    if (i == 3) {
                        std::string turns[] = { "B", "U", "'B", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }// turn to another face
                }
                else if (foundPosition[1] == 0 && foundPosition[2] == 2) { // top right
                    if (i == 2) {
                        std::string turns[] = { "L", "U", "'L", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 0) { // bottom left
                    std::string turns[] = { "B", "U", "'B", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 2) { // bottom right
                    std::string turns[] = { "L", "U", "'L", "'U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 5:
                if (foundPosition[1] == 0 && foundPosition[2] == 0) { // top left
                    if (i == 2) {
                        std::string turns[] = { "L", "U", "'L", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }// turn to another face
                }
                else if (foundPosition[1] == 0 && foundPosition[2] == 2) { // top right
                    if (i == 3) {
                        std::string turns[] = { "B", "U", "'B", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 0) { // bottom left
                    if (i == 0) {
                        std::string turns[] = { "F", "U", "'F", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }
                }
                else if (foundPosition[1] == 2 && foundPosition[2] == 2) { // bottom right
                    if (i == 1) {
                        std::string turns[] = { "R", "U", "'R", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else { addToQueue("U"); }
                }
                break;
            default:
                // fault in searching
                break;
            }
        }
    }
}


void cfop::oll()
{
}

void cfop::yellowCrossColors()
{
}

void cfop::pllPart1()
{
}

void cfop::pllPart2()
{
}

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
{{ "R1", "G8", "W7" }, { "G2", "W5", "W2" }, { "Y3", "R2", "G3" }},
{{ "B9", "O8", "G7" }, { "O4", "O5", "B4" }, { "R3", "Y2", "B3" }},
{{ "R9", "B6", "B7" }, { "O6", "B5", "R8" }, { "Y9", "W8", "G9" }},
{{ "O9", "Y4", "O3" }, { "W6", "R5", "G4" }, { "O7", "B8", "Y1" }},
{{ "B1", "B2", "R7" }, { "R6", "G5", "G6" }, { "O1", "Y6", "G1" }},
{{ "W3", "Y8", "Y7" }, { "W4", "Y5", "O2" }, { "W9", "R4", "W1" }},
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
    printCube();
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
    std::cout << "FIRST LAYER PHASE COMPLETED. START SECOND LAYER." << std::endl;
	secondLayer();
    printCube();
    std::cout << "F2L PHASE COMPLETED. START OLL." << std::endl;
	oll();
    printCube();
    std::cout << "OLL PHASE COMPLETED. START MATCHING YELLOW CROSS COLORS." << std::endl;
    yellowCrossColors();
    printCube();
    std::cout << "YELLOW CROSS COLORS COMPLETED. START PLLPART1." << std::endl;
    pllPart1();
    printCube();
    std::cout << "PLLPART1 COMPLETED. START PLLPART2." << std::endl;
    pllPart2();
    printCube();
    std::cout << "PLLPART2 COMPLETED. CUBE SOLVED." << std::endl;
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

void cfop::secondLayer() {
    std::string secondLayerCubies[4] = { "O6", "B6", "R6", "G6" };
    for (int i = 0; i < 4; i++) {
        bool correctPlace = false;
        while (!correctPlace) {
            // find position of cubie
            std::array<int, 3> foundPosition = findCubie(secondLayerCubies[i]);
            // check if the found position is the correct one by comparing it to the solved state of the cube
            if (cube[foundPosition[0]][foundPosition[1]][foundPosition[2]] ==
                solvedCube[foundPosition[0]][foundPosition[1]][foundPosition[2]]) {
                correctPlace = true;
                break;
            }

            switch (foundPosition[0]) {
            case 0: // white face
                // error, should not be possible
                return;
                break;
            case 1:
                if (foundPosition[1] == 0) {
                    switch (i) {
                    case 0: {
                        std::string turns[] = { "U", "F", "U", "'F", "'U", "'L", "'U", "L", "U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                        break;
                    }
                    case 1:
                        addToQueue("'U");
                        break;
                    case 2:
                        addToQueue("U");
                        addToQueue("U");
                        break;
                    case 3:
                        addToQueue("U");
                        break;
                    default: // unknown cubie found
                        break;
                    }
                }
                else if (foundPosition[1] == 1 && foundPosition[2] == 0) { // move to top face
                    std::string turns[] = { "'U", "'B", "'U", "B", "U", "L", "U", "'L", "'U", };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[1] == 1 && foundPosition[2] == 2) { // move to top face
                    std::string turns[] = { "U", "F", "U", "'F", "'U", "'L", "'U", "L", "U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 2:
                if (foundPosition[1] == 0) {
                    switch (i) {
                    case 0: 
                        addToQueue("U");
                        break;
                    case 1:
                        {
                            std::string turns[] = { "U", "R", "U", "'R", "'U", "'F", "'U", "F", "U" };
                            addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                            break;
                        }
                    case 2:
                        addToQueue("'U");
                        break;
                    case 3:
                        addToQueue("U");
                        addToQueue("U");
                        break;
                    default: // unknown cubie found
                        break;
                    }
                }
                else if (foundPosition[1] == 1 && foundPosition[2] == 0) { // move to top face
                    std::string turns[] = { "'U", "'F", "'U", "F", "U", "R", "U", "'R", "'U", };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[1] == 1 && foundPosition[2] == 2) { // move to top face
                    std::string turns[] = { "'U", "'R", "'U", "R", "U", "B", "U", "'B", "'U", };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 3:
                if (foundPosition[1] == 0) {
                    switch (i) {
                    case 0:
                        addToQueue("U");
                        addToQueue("U");
                        break;
                    case 1:
                        addToQueue("U");
                        break;
                    case 2:
                        {
                            std::string turns[] = { "U", "B", "U", "'B", "'U", "'R", "'U", "R", "U" };
                            addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                            break;
                        }
                    case 3:
                        addToQueue("'U");
                        break;
                    default: // unknown cubie found
                        break;
                    }
                }
                else if (foundPosition[1] == 1 && foundPosition[2] == 0) { // move to top face
                    std::string turns[] = { "'U", "'F", "'U", "F", "U", "R", "U", "'R", "'U", };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[1] == 1 && foundPosition[2] == 2) { // move to top face
                    std::string turns[] = { "'U", "'R", "'U", "R", "U", "B", "U", "'B", "'U", };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 4:
                if (foundPosition[1] == 0) {
                    switch (i) {
                    case 0:
                        addToQueue("'U");
                        break;
                    case 1:
                        addToQueue("U");
                        addToQueue("U");
                        break;
                    case 2:
                        addToQueue("U");
                    break;
                    case 3: {
                        std::string turns[] = { "U", "R", "U", "'R", "'U", "'B", "'U", "B", "U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                        break;
                    }
                    default: // unknown cubie found
                        break;
                    }
                }
                else if (foundPosition[1] == 1 && foundPosition[2] == 0) { // move to top face
                    std::string turns[] = { "'U", "'R", "'U", "R", "U", "B", "U", "'B", "'U", };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                else if (foundPosition[1] == 1 && foundPosition[2] == 2) { // move to top face
                    std::string turns[] = { "U", "R", "U", "'R", "'U", "'B", "'U", "B", "U" };
                    addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                }
                break;
            case 5:
                if (i == 0) {               // O6
                    if (foundPosition[1] == 2 && foundPosition[2] == 1) {
                        std::string turns[] = { "'U", "'L", "'U", "L", "U", "F", "U", "'F", "'U" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else {
                        addToQueue("U");
                    }
                } else if (i == 1) {        // B6
                    if (foundPosition[1] == 1 && foundPosition[2] == 2) {
                        std::string turns[] = { "'U", "'F", "'U", "F", "U", "R", "U", "'R", "'U", };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else {
                        addToQueue("U");
                    }
                } else if (i == 2) {        // R6
                    if (foundPosition[1] == 0 && foundPosition[2] == 1) {
                        std::string turns[] = { "'U", "'R", "'U", "R", "U", "B", "U", "'B", "'U", };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else {
                        addToQueue("U");
                    }
                } else if (i == 3) {        // G6
                    if (foundPosition[1] == 1 && foundPosition[2] == 0) {
                        std::string turns[] = { "'U", "'B", "'U", "B", "U", "L", "U", "'L", "'U", };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                    else {
                        addToQueue("U");
                    }
                }
                break;
            default:
                // fault in searching
                break;
            }
        }
    }
}

void cfop::oll() // create yellow cross
{
    std::string ollCubies[4] = { "Y2", "Y4", "Y6", "Y8" };
    bool yellowCross = false;
    while (!yellowCross) {
        int correctYellow = 0;
        for (int i = 0; i < 4; i++) {
            std::array<int, 3> foundPosition = findCubie(ollCubies[i]);
            if (foundPosition[0] == 5) { // check if yellow cubie is on yellow face
                correctYellow++;
            }
        }
        if (correctYellow == 4) { // check how many cubies are in correct position
            yellowCross = true;
            break;
        }
        // get correct pattern on top of cube
        std::string blueCubie = cube[2][0][1].substr(0, 1);
        std::string redCubie = cube[3][0][1].substr(0, 1);

        if ((correctYellow == 2 && blueCubie == "Y" && "Y") || 
            (correctYellow == 2 && blueCubie == "Y" && redCubie != "Y") ||
            (correctYellow == 0)) {
            std::string turns[] = { "F", "R", "U", "'R", "'U", "'F" };
            addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
        }
        else {
            addToQueue("U");
        }

        if (correctYellow == 1 || correctYellow == 3) {
            // panic
            std::cout << "Unsolvable Cube." << std::endl;
            return;
        }
    }
}

void cfop::yellowCrossColors() {
    std::string yellowCrossCubies[4] = { "O2", "B2", "R2", "G2" };
    bool matchingColors = false;
    while (!matchingColors) {
        int correctColor = 0;
        for (int i = 0; i < 4; i++) {
            std::array<int, 3> foundPosition = findCubie(yellowCrossCubies[i]);
            // check if color is on correct place
            if (cube[foundPosition[0]][foundPosition[1]][foundPosition[2]] ==
                solvedCube[foundPosition[0]][foundPosition[1]][foundPosition[2]]) {
                correctColor++;
            }
        }
        if (correctColor == 4) { // check how many cubies are in correct position
            matchingColors = true;
            break;
        } 
        else if (correctColor == 0) {
            addToQueue("U");
        }
        else if (correctColor == 2 && cube[4][0][1] == "G2" &&
            ( cube[2][0][1] == "B2" || cube[3][0][1] == "R2") ) {
            std::string turns[] = { "R", "U", "'R", "U", "R", "U", "U", "'R"};
            addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
        } 
        else if (correctColor == 2 && cube[3][0][1] == "R2" &&
            (cube[2][0][1] == "B2" || cube[1][0][1] == "O2")) {
            std::string turns[] = { "F", "U", "'F", "U", "F", "U", "U", "'F" };
            addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
        }
        else if (correctColor == 2 && cube[2][0][1] == "B2" && cube[1][0][1] == "O2") {
            std::string turns[] = { "L", "U", "'L", "U", "L", "U", "U", "'L" };
            addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
        }
        else if (correctColor == 2 && cube[1][0][1] == "O2" && cube[4][0][1] == "G2") {
            std::string turns[] = { "B", "U", "'B", "U", "B", "U", "U", "'B" };
            addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
        }
        else if (correctColor == 3) { // check how many cubies are in correct position
            std::cout << "panic, unsolvable cube" << std::endl;
            break;
        }
    }
}

void cfop::pllPart1()
{
    std::string pllP1Cubies[4] = { "O1", "B1", "R1", "G1" };
    bool cornersInPlace = false;
    while (!cornersInPlace) {
        int correctCorners = 0;
        bool frontCorner = false;
        if (cube[1][0][0] == "O1" ||
            cube[1][0][0] == "G3" ||
            cube[1][0][0] == "Y1") {
            correctCorners++;
        }
        if (cube[2][0][0] == "B1" ||
            cube[2][0][0] == "O3" ||
            cube[2][0][0] == "Y7") {
            correctCorners++;
            frontCorner = true;

        }
        if (cube[3][0][0] == "R1" ||
            cube[3][0][0] == "B3" ||
            cube[3][0][0] == "Y9") {
            correctCorners++;
        }
        if (cube[4][0][0] == "G1" ||
            cube[4][0][0] == "R3" ||
            cube[4][0][0] == "Y3") {
            correctCorners++;
        }
        if (frontCorner && correctCorners != 2 && correctCorners != 4) {
            std::string turns[] = { "U", "R", "'U", "'L", "U", "'R", "'U", "L" };
            addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
        }
        else if (correctCorners == 4) {
            cornersInPlace = true;
            break;
        }
        else if (correctCorners == 0 || correctCorners == 1 || correctCorners == 3) {
            addToQueue("U");
        }
        else if (correctCorners == 2) {
            std::cout << "panic, unsolvable cube" << std::endl;
            return;
        }
    }
}

void cfop::pllPart2() {
    std::string pllP2Cubies[4] = { "B3", "R3", "G3", "O3" };
    std::string pllP2YellowCubies[4] = { "Y9", "Y3", "Y1", "Y7" };
    for (int i = 0; i < 4; i++) {
        bool cornerCorrect = false;
        while (!cornerCorrect) {
            if (cube[2][0][2] == pllP2Cubies[i] ||
                cube[3][0][0] == pllP2Cubies[i] ||
                cube[5][2][2] == pllP2Cubies[i]) {
                bool cornerOriented = false;
                while (!cornerOriented) {
                    if (cube[5][2][2] == pllP2YellowCubies[i]) {
                        cornerOriented = true;
                    }
                    else {
                        std::string turns[] = { "F", "D", "'F", "'D" };
                        addToQueue(turns, sizeof(turns) / sizeof(turns[0]));
                    }
                }
                cornerCorrect = true;
            }   
            else {
                addToQueue("U");
            }
        }
    }
    std::array<int, 3> posY1 = findCubie("Y1");
    int turnCounter = 0;
    while (posY1[0] != 5 || posY1[1] != 0 || posY1[2] != 0) {
        addToQueue("U");
        turnCounter++;
        if (turnCounter >= 5) {
            return; // cannot be solved
        }
        posY1 = findCubie("Y1");
    }
}

void cfop::rotateFaceClockwise(CubeFace face)
{
    const int ROWS = 3;
    const int COLUMNS = 3;
    const int FACES = 6;
    // Rotate the given face clockwise
    std::string tmp[ROWS][COLUMNS];
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmp[row][col] = cube[face][COLUMNS - col - 1][row];
        }
    }
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLUMNS; ++col)
        {
            cube[face][row][col] = tmp[row][col];
        }
    }

    // Update the surrounding faces
    std::string tmpRow[COLUMNS];
    switch (face)
    {
    case FRONT:
        // Rotate adjacent rows on FRONT face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[UP][2][col]; // store value from upper cube face
            cube[UP][2][col] = cube[LEFT][COLUMNS - col - 1][2]; // put value from left face into top face
            cube[LEFT][COLUMNS - col - 1][2] = cube[DOWN][0][COLUMNS - col - 1];
            cube[DOWN][0][COLUMNS - col - 1] = cube[RIGHT][col][0];
            cube[RIGHT][col][0] = tmpRow[col];
        }
        break;
    case BACK:
        // Rotate adjacent rows on BACK face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[UP][0][COLUMNS - col - 1];
            cube[UP][0][COLUMNS - col - 1] = cube[RIGHT][COLUMNS - col - 1][2]; 
            cube[RIGHT][COLUMNS - col - 1][2] = cube[DOWN][2][col];
            cube[DOWN][2][col] = cube[LEFT][col][0];
            cube[LEFT][col][0] = tmpRow[col];
        }
        break;
    case LEFT:
        // Rotate adjacent rows on LEFT face
        for (int row = 0; row < ROWS; ++row)
        {
            tmpRow[row] = cube[UP][ROWS - row - 1][0];
            cube[UP][ROWS - row - 1][0] = cube[BACK][row][COLUMNS - 1];
            cube[BACK][row][COLUMNS - 1] = cube[DOWN][ROWS - row - 1][0];
            cube[DOWN][ROWS - row - 1][0] = cube[FRONT][ROWS - row - 1][0];
            cube[FRONT][ROWS - row - 1][0] = tmpRow[row];
        }
        break;
    case RIGHT:
        // Rotate adjacent rows on RIGHT face
        for (int row = 0; row < ROWS; ++row)
        {
            tmpRow[row] = cube[UP][row][COLUMNS - 1];
            cube[UP][row][COLUMNS - 1] = cube[FRONT][row][COLUMNS - 1];
            cube[FRONT][row][COLUMNS - 1] = cube[DOWN][row][COLUMNS - 1];
            cube[DOWN][row][COLUMNS - 1] = cube[BACK][ROWS - row - 1][0];
            cube[BACK][ROWS - row - 1][0] = tmpRow[row];
        }
        break;
    case UP:
        // Rotate adjacent rows on UP face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[LEFT][0][col];
            cube[LEFT][0][col] = cube[FRONT][0][col];
            cube[FRONT][0][col] = cube[RIGHT][0][col];
            cube[RIGHT][0][col] = cube[BACK][0][col];
            cube[BACK][0][col] = tmpRow[col];
        }
        break;
    case DOWN:
        // Rotate adjacent rows on DOWN face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[LEFT][ROWS - 1][col];
            cube[LEFT][ROWS - 1][col] = cube[BACK][ROWS - 1][col];
            cube[BACK][ROWS - 1][col] = cube[RIGHT][ROWS - 1][col];
            cube[RIGHT][ROWS - 1][col] = cube[FRONT][ROWS - 1][col];
            cube[FRONT][ROWS - 1][col] = tmpRow[col];
        }
        break;
    }
}

void cfop::rotateFaceCounterClockwise(CubeFace face)
{
    // Rotate the face three times clockwise to achieve a counterclockwise rotation
    for (int i = 0; i < 3; ++i) {
        rotateFaceClockwise(face);
    }
}
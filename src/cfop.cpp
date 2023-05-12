#pragma once
#include <iostream>
#include <string>
#include "cubie.cpp"
#include "../include/cfop.h"
#include <vector>

cfop::cfop(){
    solvePattern.clear();
}

void cfop::addToSolvePattern(std::string newTurn){
    solvePattern.push_back(newTurn);
}

bool cfop::solveCube(std::string cube[6][3][3]){
    cross(cube);
}

void cfop::cross(std::string cube[6][3][3]) {
    std::string centerColor = cube[2][1][1]; // Center color of the cross
    std::string edgeColor, adjacentColor;
    
    // Check if the edge pieces on the first layer have the center color
    for (int i = 0; i < 4; i++) {
        if (cube[0][1][0] == centerColor) {
            edgeColor = cube[1][0][1];
            adjacentColor = cube[2][1][0];
        } else if (cube[0][1][2] == centerColor) {
            edgeColor = cube[1][2][1];
            adjacentColor = cube[2][1][2];
        } else if (cube[1][0][2] == centerColor) {
            edgeColor = cube[0][1][2];
            adjacentColor = cube[2][0][1];
        } else if (cube[1][2][2] == centerColor) {
            edgeColor = cube[0][1][0];
            adjacentColor = cube[2][2][1];
        }
        
        // Rotate the edge piece to the correct position and orientation
        if (edgeColor == adjacentColor) {
            // The edge piece is already in the correct position and orientation
            continue;
        } else if (edgeColor == centerColor) {
            // The edge piece is on the wrong side but in the correct orientation
            // Rotate the first layer to bring the edge piece to the top layer
            if (i == 0) {
                addToSolvePattern("U'");
            } else if (i == 1) {
                addToSolvePattern("U2");
            } else if (i == 2) {
                addToSolvePattern("U");
            }
            // Rotate the edge piece to the correct position and orientation
            addToSolvePattern("F");
            addToSolvePattern("R");
            addToSolvePattern("U'");
            addToSolvePattern("R'");
            addToSolvePattern("U'");
            addToSolvePattern("F'");
        } else if (adjacentColor == centerColor) {
            // The edge piece is on the wrong side and in the wrong orientation
            // Rotate the first layer to bring the edge piece to the top layer
            if (i == 0) {
                addToSolvePattern("U'");
            } else if (i == 1) {
                addToSolvePattern("U2");
            } else if (i == 2) {
                addToSolvePattern("U");
            }
            // Rotate the edge piece to the correct position and orientation
            addToSolvePattern("R'");
            addToSolvePattern("U'");
            addToSolvePattern("R");
        }
    }
}
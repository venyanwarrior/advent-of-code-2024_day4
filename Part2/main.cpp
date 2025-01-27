#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <exception>

bool searchAllDirections(std::vector<std::string> wordSearch, uint xPos, uint yPos);
int getDirection(char axis, uint num);

int main() {
    std::ifstream infile;
    infile.open("../input.txt");
    if (!infile.is_open()) {
        std::cout << "File opening failed." << std::endl;
    }

    std::vector<std::string> wordSearch;
    std::string currentLine;
    while (!infile.eof()) {
        getline(infile, currentLine);
        wordSearch.push_back(currentLine);
    }
    infile.close();

    int numXmas = 0;
    for (uint i = 0; i < wordSearch.size(); i++) {
        for (uint j = 0; j < wordSearch.at(i).size(); j++) {
            if (searchAllDirections(wordSearch, j, i)) {
                numXmas++;
            }
        }
    }
    std::cout << "Number of XMAS: " << numXmas << std::endl;

}

bool searchAllDirections(std::vector<std::string> wordSearch, uint xPos, uint yPos) {
    int numASFound = 0, numAMFound = 0;
    int yDirection, xDirection;
    std::string currentString, firstString, secondString, thirdString, fourthString;

    for (uint i = 0; i < 4; i++) {
        currentString = "";
        yDirection = getDirection('y', i);
        xDirection = getDirection('x', i);
        for (uint j = 0; j < 2; j++) {
            try {
                currentString += wordSearch.at(yPos + (j * yDirection)).at(xPos + (j * xDirection));
            } catch (std::out_of_range& e) { //Bad practice but it works anyway, integer underflow is fine here
                //std::cout << "Out of range" << std::endl;
            }
        }
        if (currentString == "AM") {
            numAMFound++;
            if (i == 0) { firstString = currentString; }
            if (i == 1) { secondString = currentString; }
            if (i == 2) { thirdString = currentString; }
            if (i == 3) { fourthString = currentString; }
        }
        if (currentString == "AS") {
            numASFound++;
            if (i == 0) { firstString = currentString; }
            if (i == 1) { secondString = currentString; }
            if (i == 2) { thirdString = currentString; }
            if (i == 3) { fourthString = currentString; }
        }
    }

    if (((numAMFound == 2) && (numASFound == 2)) && ((firstString != thirdString) && (secondString != fourthString))) {
        return true;
    } else {
        return false;
    }
}

int getDirection(char axis, uint num) {
    uint offset;
    if (axis == 'x') {
        offset = 0;
    } else if (axis == 'y') {
        offset = 3;
    }

    switch ((num + offset) % 4) {
        case 0:
        case 3:
            return 1;
        case 1:
        case 2:
            return -1;
        default:
            return 0;
    }
}
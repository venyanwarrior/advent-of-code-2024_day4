#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <exception>

int searchAllDirections(std::vector<std::string> wordSearch, uint xPos, uint yPos);
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
            numXmas += searchAllDirections(wordSearch, j, i);
        }
    }
    std::cout << "Number of XMAS: " << numXmas << std::endl;

}

int searchAllDirections(std::vector<std::string> wordSearch, uint xPos, uint yPos) {
    int numXmasFound = 0;
    int yDirection, xDirection;
    std::string currentString;

    for (uint i = 0; i < 8; i++) {
        currentString = "";
        yDirection = getDirection('y', i);
        xDirection = getDirection('x', i);
        for (uint j = 0; j < 4; j++) {
            try {
                currentString += wordSearch.at(yPos + (j * yDirection)).at(xPos + (j * xDirection));
            } catch (std::out_of_range& e) { //Bad practice but it works anyway, integer underflow is fine here
                //std::cout << "Out of range" << std::endl;
            }
        }
        if (currentString == "XMAS") {
            numXmasFound++;
        }
    }
    return numXmasFound;
}

int getDirection(char axis, uint num) {
    uint offset;
    if (axis == 'x') {
        offset = 0;
    } else if (axis == 'y') {
        offset = 6;
    }

    switch ((num + offset) % 8) {
        case 0:
        case 1:
        case 7:
            return 1;
        case 2:
        case 6:
            return 0;
        case 3:
        case 4:
        case 5:
            return -1;
        default:
            return 0;
    }
}
  
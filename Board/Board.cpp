#include "Board.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>


using namespace std;

Board::Board(RenderWindow &wind, Font &scoreBoardFont, bool isVsAi) : boardWindow(wind), saveGame(wind),
                                                                      isAgainstAi(isVsAi) {
    fillBoard();
    setScoreBoard(scoreBoardFont);
    drawBoard();
    drawScoreBoard();
}

Board::Board(RenderWindow &wind, Font &scoreBoardFont, const String &fileName, bool isVsAi) : boardWindow(wind),
                                                                                              saveGame(wind),
                                                                                              isAgainstAi(isVsAi) {
    saveGame.fillBoardLoadGame(vectorBoard, fileName, currentPlayer);
    setScoreBoard(scoreBoardFont);
    drawBoard();
    drawScoreBoard();
}

void Board::fillBoard() {
    int ow = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < i + 5; j++) {
            if ((i == 0 && j == 0) || (i == 4 && j == 8)) {
                ow = 1;
            } else if ((i == 0 && j == 4) || (i == 4 && j == 0)) {
                ow = 2;
            } else if ((i == 3 && j == 4) || (i == 4 && j == 3)) {
                ow = 3;
            }
            vectorBoard.at(i).emplace_back(i, j, ow);
            ow = 0;
        }
    }
    ow = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8 - i; j++) {
            if (i == 3 && j == 0) {
                ow = 1;
            } else if (i == 3 && j == 4) {
                ow = 2;
            } else if (i == 0 && j == 4) {
                ow = 3;
            }
            vectorBoard.at(i + 5).emplace_back(i + 5, j, ow);
            ow = 0;
        }
    }
}

void Board::mouseClick(Vector2i position) {
    if (saveGame.isButtonPressed(position)) {
        RenderWindow saveWindow(VideoMode(400, 250), "Save Your Game", Style::Default);
        saveGame.showSaveWindow(saveWindow, vectorBoard, currentPlayer);
    }
    for (int i = 0; i < vectorBoard.size(); i++) {
        for (int j = 0; j < vectorBoard.at(i).size(); j++) {
            if (vectorBoard.at(i).at(j).isInsideHexagon(position)) {
                if (vectorBoard.at(i).at(j).getOwner() == currentPlayer) {
                    chooseHex(vectorBoard.at(i).at(j));
                } else if (vectorBoard.at(i).at(j).getState() == "Close") {
                    moveHex(*chosenHex2, vectorBoard.at(i).at(j), true, vectorBoard);
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    if (isAgainstAi) {
                        aiMove();
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    }
                } else if (vectorBoard.at(i).at(j).getState() == "Far") {
                    moveHex(*chosenHex2, vectorBoard.at(i).at(j), false, vectorBoard);
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    if (isAgainstAi) {
                        aiMove();
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    }
                }
            }
        }
    }
}

void Board::chooseHex(Hex &hex) {
    if (chosenHex2 != nullptr) {
        chosenHex2->setState("Empty");
    }

    chosenHex2 = &hex;

    hex.setState("Chosen");
    availableMoves(hex, vectorBoard);
}

void Board::moveHex(Hex &chosenHex, Hex &hexToMove, bool isClose, vector<vector<Hex>> &vectorB) {
    double maxCloseDistance = 94;
    int currP = (currentPlayer == 1) ? 2 : 1;

    if (isClose) {
        hexToMove.setOwner(chosenHex.getOwner());
    } else {
        hexToMove.setOwner(chosenHex.getOwner());
        chosenHex.setOwner(0);
    }

    for (int i = 0; i < vectorB.size(); i++) {
        for (int j = 0; j < vectorB.at(i).size(); j++) {
            double distance = sqrt(
                    pow(abs(hexToMove.getWindowPositionX() - vectorB.at(i).at(j).getWindowPositionX()), 2) +
                    pow(abs(hexToMove.getWindowPositionY() - vectorB.at(i).at(j).getWindowPositionY()), 2));
            if (distance <= maxCloseDistance && vectorB.at(i).at(j).getOwner() == currP) {
                vectorB.at(i).at(j).setOwner(currentPlayer);
            }
            vectorB.at(i).at(j).setState("Empty");
        }
    }
}

vector<Hex *> Board::availableMoves(Hex &h, vector<vector<Hex>> &vectorB) {
    //2r
    // Radius = 50
    vector<Hex *> availableMoves;
    availableMoves.clear();

    double maxCloseDistance = 94;
    double maxFarDistance = 187;

    for (int i = 0; i < vectorB.size(); i++) {
        for (int j = 0; j < vectorB.at(i).size(); j++) {
            int currP = (currentPlayer == 1) ? 2 : 1;

            if (vectorB.at(i).at(j).getOwner() == 3 || vectorB.at(i).at(j).getOwner() == currP ||
                vectorB.at(i).at(j).getOwner() == currentPlayer) {
                continue;
            }
            double distance = sqrt(pow(abs(h.getWindowPositionX() - vectorB.at(i).at(j).getWindowPositionX()), 2) +
                                   pow(abs(h.getWindowPositionY() - vectorB.at(i).at(j).getWindowPositionY()), 2));
            if (distance <= maxCloseDistance) {
                vectorB.at(i).at(j).setState("Close");
                availableMoves.push_back(&vectorB.at(i).at(j));
            } else if (distance <= maxFarDistance) {
                vectorB.at(i).at(j).setState("Far");
                availableMoves.push_back(&vectorB.at(i).at(j));
            } else {
                vectorB.at(i).at(j).setState("Empty");
            }
        }
    }
    return availableMoves;
}

void Board::setScoreBoard(Font &font) {
    scoreboardP1.setFont(font);
    scoreboardP1.setString("Player 1: " + to_string(3));
    scoreboardP1.setCharacterSize(30);
    scoreboardP1.setPosition(200, 400);
    scoreboardP1.setFillColor(Color(150, 3, 3));

    scoreboardP2.setFont(font);
    scoreboardP2.setString("Player 2: " + to_string(3));
    scoreboardP2.setCharacterSize(30);
    scoreboardP2.setPosition(200, 450);
    scoreboardP2.setFillColor(Color(94, 91, 3));

    saveGame.setSaveGame();
}

int Board::countHexes(int hexOwner, vector<vector<Hex>> &vectorB) {
    int counter = 0;
    for (int i = 0; i < vectorB.size(); i++) {
        for (int j = 0; j < vectorB.at(i).size(); j++) {
            if (vectorB.at(i).at(j).getOwner() == hexOwner) {
                counter++;
            }
        }
    }
    if (hexOwner == 1) {
        p1Counter = counter;
    } else {
        p2Counter = counter;
    }
    setFinalScore(p1Counter + p2Counter);
    return counter;
}

void Board::aiMove() {
    double maxCloseDistance = 94;

    int maxVal = 0;
    int boardPositionX1 = 0;
    int boardPositionY1 = 0;
    int boardPositionX2 = 0;
    int boardPositionY2 = 0;

    for (int i = 0; i < vectorBoard.size(); i++) {
        for (int j = 0; j < vectorBoard.at(i).size(); j++) {
            if (vectorBoard.at(i).at(j).getOwner() == 2) {
                vector<int> numbers = checkAiMove(vectorBoard, vectorBoard.at(i).at(j));
                int value = numbers.at(0);

                int bpx2 = numbers.at(1);
                int bpy2 = numbers.at(2);
                if (value >= maxVal) {
                    maxVal = value;
                    boardPositionX2 = bpx2;
                    boardPositionY2 = bpy2;
                    boardPositionX1 = vectorBoard.at(i).at(j).getBoardPositionX();
                    boardPositionY1 = vectorBoard.at(i).at(j).getBoardPositionY();
                }
            }
        }
    }
    double distance = sqrt(pow(abs(vectorBoard.at(boardPositionX1).at(boardPositionY1).getWindowPositionX() -
                                   vectorBoard.at(boardPositionX2).at(boardPositionY2).getWindowPositionX()), 2) +
                           pow(abs(vectorBoard.at(boardPositionX1).at(boardPositionY1).getWindowPositionY() -
                                   vectorBoard.at(boardPositionX2).at(boardPositionY2).getWindowPositionY()), 2));
    if (distance <= maxCloseDistance) {
        moveHex(vectorBoard.at(boardPositionX1).at(boardPositionY1),
                vectorBoard.at(boardPositionX2).at(boardPositionY2),
                true, vectorBoard);
    } else {
        moveHex(vectorBoard.at(boardPositionX1).at(boardPositionY1),
                vectorBoard.at(boardPositionX2).at(boardPositionY2),
                false, vectorBoard);
    }
}

vector<int> Board::checkAiMove(vector<vector<Hex>> vectorB, Hex &hex) {

    Hex copyOfHex = hex;
    vector<Hex> possibleMoves;
    vector<int> numbers = {0, 0, 0};
    double maxFarDistance = 187;
    double maxCloseDistance = 94;
    int maxVal = 0;

    for (int i = 0; i < vectorB.size(); i++) {
        for (int j = 0; j < vectorB.at(i).size(); j++) {
            if (vectorB.at(i).at(j).getOwner() == 3 || vectorB.at(i).at(j).getOwner() == 1 ||
                vectorB.at(i).at(j).getOwner() == 2) {
                continue;
            }
            double distance = sqrt(pow(abs(copyOfHex.getWindowPositionX() -
                                           vectorB.at(i).at(j).getWindowPositionX()), 2) +
                                   pow(abs(copyOfHex.getWindowPositionY()
                                           - vectorB.at(i).at(j).getWindowPositionY()), 2));
            if (distance <= maxFarDistance) {
                possibleMoves.push_back(vectorB.at(i).at(j));
            }
        }
    }
    for (int i = 0; i < possibleMoves.size(); i++) {
        int counter = 0;
        vector<vector<Hex>> vec;
        vec = vectorB;
        double distance = sqrt(pow(abs(copyOfHex.getWindowPositionX() -
                                       possibleMoves.at(i).getWindowPositionX()), 2) +
                               pow(abs(copyOfHex.getWindowPositionY()
                                       - possibleMoves.at(i).getWindowPositionY()), 2));
        if (distance <= maxCloseDistance) {
            moveHex(copyOfHex, possibleMoves.at(i), true, vec);
            for (int j = 0; j < vec.size(); j++) {
                for (int k = 0; k < vec.at(j).size(); k++) {
                    if (vec.at(j).at(k).getOwner() == 2) {
                        counter++;
                    }
                }
            }
        } else {
            moveHex(copyOfHex, possibleMoves.at(i), false, vec);
            for (int j = 0; j < vec.size(); j++) {
                for (int k = 0; k < vec.at(j).size(); k++) {
                    if (vec.at(j).at(k).getOwner() == 2) {
                        counter++;
                    }
                }
            }
        }
        if (counter >= maxVal) {
            maxVal = counter;
            numbers.at(0) = counter;
            numbers.at(1) = possibleMoves.at(i).getBoardPositionX();
            numbers.at(2) = possibleMoves.at(i).getBoardPositionY();
        }
        vec.clear();
    }
    return numbers;
}

void Board::drawScoreBoard() {
    scoreboardP1.setString("Player 1: " + to_string(countHexes(1, vectorBoard)));
    scoreboardP2.setString("Player 2: " + to_string(countHexes(2, vectorBoard)));

    boardWindow.draw(scoreboardP1);
    boardWindow.draw(scoreboardP2);
    saveGame.drawSaveButton();
}

void Board::drawBoard() {
    for (int i = 0; i < vectorBoard.size(); i++) {
        for (int j = 0; j < vectorBoard[i].size(); j++) {
            drawHex(vectorBoard.at(i).at(j));
        }
        //rysowanie vectora
    }
}

void Board::drawHex(Hex &hex) {
    hex.draw(boardWindow);
}

void Board::update() {
    drawBoard();
    drawScoreBoard();
}

void Board::setFinalScore(int finalS) {
    Board::finalScore = finalS;
}

int Board::getFinalScore() {
    return finalScore;
}


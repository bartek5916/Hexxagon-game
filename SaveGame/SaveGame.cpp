#include <fstream>
#include "SaveGame.h"
#include <vector>
#include <iostream>

SaveGame::SaveGame(RenderWindow &bWindow) : window(bWindow) {
    font.loadFromFile("Font\\Baloo-Regular.ttf");
}

void SaveGame::setSaveGame() {
    saveGameButton.setSize(Vector2f(200, 60));
    saveGameButton.setPosition(1275, 410);
    saveGameButton.setFillColor(Color::Black);

    String buttonText = "Save Game";
    saveButtonText.setString(buttonText);
    saveButtonText.setFont(font);
    saveButtonText.setPosition(1300, 420);

    setFileNameText();
}

void SaveGame::saveGame(const String &fileName, vector<vector<Hex>> &vectorBoard, int currentP) {
    const String path = "Saved_Games\\" + fileName;
    std::ofstream file(path);
    if (file.is_open()) {
        file << currentP << endl;
        for (int i = 0; i < vectorBoard.size(); i++) {
            for (int j = 0; j < vectorBoard.at(i).size(); j++) {
                file << i << " " << j << " " << vectorBoard.at(i).at(j).getOwner() << " " << endl;
            }
        }
        file.close();
    } else {
        std::cout << "blad xd" << std::endl;
    }
}

void SaveGame::setLoadGame(vector<string> &vector, ::vector<Text> &menuVector, ::vector<RectangleShape> &buttonsVec) {
    for (int i = 0; i < vector.size(); i++) {
        RectangleShape loadButton;
        loadButton.setSize(Vector2f(vector.at(i).length() * 15, 30));
        loadButton.setPosition(menuVector.at(i).getPosition());
        loadButton.setFillColor(Color(50, 1, 1));

        buttonsVec.push_back(loadButton);
    }
}

void SaveGame::fillBoardLoadGame(vector<vector<Hex>> &vectorBoard, const String &fileName, int &currentPlayer) {
    int counter = 0;
    ifstream file;
    file.open("Saved_Games\\" + fileName);

    if (!file.good()) {
        cout << "blad pliku" << endl;
        return;
    }

    while (true) {
        if (counter == 0) {
            file >> counter;
            currentPlayer = counter;
        } else {
            int variableI;
            int variableJ;
            int owner;

            file >> variableI >> variableJ >> owner;

            if (!file.fail()) {
                vectorBoard.at(variableI).emplace_back(variableI, variableJ, owner);
            } else {
                break;
            }
        }
    }
}

void SaveGame::showSaveWindow(RenderWindow &saveWindow, vector<vector<Hex>> &vectorBoard, int currentPlayer) {
    while (saveWindow.isOpen()) {
        Event saveEvent;

        while (saveWindow.pollEvent(saveEvent)) {
            if (saveEvent.type == Event::Closed) {
                saveWindow.close();
            } else if (saveEvent.type == Event::TextEntered && saveEvent.text.unicode <= 122 &&
                       saveEvent.text.unicode >= 65) {
                fillText(saveEvent.text.unicode);
                fileNameText.setString(saveText);
            } else if (saveEvent.type == Event::KeyReleased && saveEvent.key.code == Keyboard::BackSpace) {
                saveText = deleteChar();
                fileNameText.setString(saveText);
            } else if (saveEvent.type == Event::KeyReleased && saveEvent.key.code == Keyboard::Return) {
                saveGame(saveText, vectorBoard, currentPlayer);
                saveWindow.close();
            }
        }
        saveWindow.clear();
        saveWindow.draw(fileNameText);
        saveWindow.display();
    }
    saveText.clear();
    fileNameText.setString(saveText);
}

bool SaveGame::isButtonPressed(Vector2i pos) {
    float upY = saveGameButton.getTransform().transformPoint(saveGameButton.getPoint(1)).y;
    float leftX = saveGameButton.getTransform().transformPoint(saveGameButton.getPoint(0)).x;
    float downY = saveGameButton.getTransform().transformPoint(saveGameButton.getPoint(3)).y;
    float rightX = saveGameButton.getTransform().transformPoint(saveGameButton.getPoint(2)).x;

    if (pos.x >= leftX && pos.x <= rightX && pos.y >= upY && pos.y <= downY) {
        return true;
    } else {
        return false;
    }
}

int SaveGame::mouseClick(::vector<RectangleShape> &buttonsVec, Vector2i position) {
    for (int i = 0; i < buttonsVec.size(); i++) {
        if (buttonsVec.at(i).getGlobalBounds().contains(
                {static_cast<float>(position.x), static_cast<float>(position.y)})) {
            return i;
        }
    }
    return -1;
}




void SaveGame::drawSaveButton() {
    window.draw(saveGameButton);
    window.draw(saveButtonText);
}

void SaveGame::fillText(char c) {
    saveText += c;
}

string SaveGame::deleteChar() {
    string newString;
    if (saveText.length() > 0) {
        for (int i = 0; i < saveText.length() - 1; i++) {
            newString = newString + saveText.at(i);
        }
    }
    return newString;
}



void SaveGame::setFileNameText() {
    fileNameText.setFillColor(Color::White);
    fileNameText.setCharacterSize(25);
    fileNameText.setFont(font);
    fileNameText.setPosition(20, 100);
}

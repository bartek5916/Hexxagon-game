#include "Menu.h"
#include "../Board/Board.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Menu::Menu() {
    setAll();
}

Menu::~Menu() {
}

void Menu::setAll() {
    window.create(VideoMode(640, 640), "Hexxagon", Style::Default);

    background.loadFromFile(
            "Images\\polygonal-abstract-background-black-and-light-red-free-vector.jpg");

    spriteBackg.setTexture(background);
    spriteBackg.setOrigin(640, 480);

    font.loadFromFile("Font\\arial.ttf");
    scoreBoardFont.loadFromFile("Font\\Baloo-Regular.ttf");

    menu[0].setFont(font);
    menu[0].setString("NOWA GRA");
    menu[0].setFillColor(Color::Red);
    menu[0].setCharacterSize(25);
    menu[0].setPosition(258, 200);

    menu[1].setFont(font);
    menu[1].setString("WCZYTAJ GRE");
    menu[1].setCharacterSize(25);
    menu[1].setPosition(235, 250);
    menu[1].setFillColor(Color::White);

    menu[2].setFont(font);
    menu[2].setString("NAJLEPSZE WYNIKI");
    menu[2].setCharacterSize(25);
    menu[2].setPosition(205, 300);
    menu[2].setFillColor(Color::White);

    menu[3].setFont(font);
    menu[3].setString("TRYB GRY");
    menu[3].setCharacterSize(25);
    menu[3].setPosition(260, 350);
    menu[3].setFillColor(Color::White);

    selectedMenu = 0;
}

void Menu::select() {
    Event e;
    while (window.pollEvent(e)) {
        if (e.type == Event::Closed) {
            window.close();
        }
        if (e.type == Event::KeyReleased) {
            if (e.key.code == Keyboard::Up) {
                moveUp();
                break;
            }
            if (e.key.code == Keyboard::Down) {
                moveDown();
                break;
            }
            if (e.key.code == Keyboard::Return) {
                //podlaczanie okienek

                int x = getSelectedMenu();
                if (x == 0) {
                    startGame(isAgainstAi);
                }
                if (x == 1) {
                    RenderWindow loadg(VideoMode(640, 640), "Load Your Game");
                    SaveGame loadGame = SaveGame(loadg);
                    Texture background2;
                    background2.loadFromFile(
                            "Images\\polygonal-abstract-background-black-and-light-red-free-vector.jpg");
                    Sprite backgroundL;
                    backgroundL.setTexture(background2);
                    backgroundL.setOrigin(0, 0);

                    vector<string> vector;
                    ::vector<Text> menuVector;
                    ::vector<RectangleShape> buttonsVec;

                    Text text1;
                    text1.setString("Wczytaj gre: ");
                    text1.setFillColor(Color::Black);
                    text1.setCharacterSize(25);
                    text1.setFont(font);
                    text1.setPosition(10, 10);

                    fs::path myPath("Saved_Games/");
                    for (auto& entry: fs::directory_iterator(myPath)) {
                        vector.push_back(entry.path().filename().string());
                    }
                    for(int i = 0; i < vector.size(); i++){
                        menuVector.emplace_back(to_string(i + 1) + ". "  + vector.at(i), font, 25);
                        menuVector.at(i).setPosition(10, 50 + i*40);
                        menuVector.at(i).setFillColor(Color::Black);
                    }

                    loadGame.setLoadGame(vector, menuVector, buttonsVec);
                    while (loadg.isOpen()) {
                        Event ge;
                        while (loadg.pollEvent(ge)) {
                            if (ge.type == Event::Closed) {
                                loadg.close();
                            }
                            if (ge.type == Event::MouseButtonPressed) {
                                Vector2i mousePos = Mouse::getPosition(loadg);
                                int buttonPressed = loadGame.mouseClick(buttonsVec, mousePos);
                                if(buttonPressed != -1){
                                    loadg.close();
                                    startGame(vector.at(buttonPressed), isAgainstAi);
                                }
                            }
                        }
                        loadg.clear();
                        loadg.draw(backgroundL);
                        for (int i = 0; i < buttonsVec.size(); i++) {
                            loadg.draw(buttonsVec.at(i));
                            loadg.draw(menuVector.at(i));
                        }
                        loadg.draw(text1);
                        loadg.display();
                    }
                }
                if (x == 2) {
                    RenderWindow bestS(VideoMode(640, 640), "bestScore");

                    while (bestS.isOpen()) {
                        Event ge;
                        while (bestS.pollEvent(ge)) {
                            if (ge.type == Event::Closed) {
                                bestS.close();
                            }
                        }
                        bestS.clear();
                        bestS.draw(spriteBackg);
                        bestS.display();
                    }
                }
                if (x == 3) {
                    RenderWindow gameMd(VideoMode(640, 640), "gameMd");


                    Text text1("Wybierz tryb gry: ", font, 25);
                    text1.setFillColor(Color::Black);
                    text1.setPosition(230 , 200);

                    Text textButton("Gracz vs Gracz", font, 25);
                    textButton.setFillColor(Color::Black);
                    textButton.setPosition(230 , 240);

                    RectangleShape button(Vector2f(175 ,25));
                    button.setFillColor(Color::Red);
                    button.setPosition(230 , 245);

                    while (gameMd.isOpen()) {
                        Event ge;
                        while (gameMd.pollEvent(ge)) {
                            if (ge.type == Event::Closed) {
                                gameMd.close();
                            }
                            if (ge.type == Event::MouseButtonPressed) {
                                Vector2i mousePos = Mouse::getPosition(gameMd);
                                if(button.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                                    if(button.getFillColor() == Color::Red){
                                        button.setFillColor(Color::Green);
                                        button.setSize(Vector2f(225 ,25));
                                        textButton.setString("Gracz vs Komputer");
                                        isAgainstAi = true;
                                    }else{
                                        button.setFillColor(Color::Red);
                                        button.setSize(Vector2f(175 ,25));
                                        textButton.setString("Gracz vs Gracz");
                                        isAgainstAi = false;
                                    }
                                }
                            }
                        }
                        gameMd.clear();
                        gameMd.draw(spriteBackg);
                        gameMd.draw(button);
                        gameMd.draw(text1);
                        gameMd.draw(textButton);
                        gameMd.display();
                    }
                }
            }
        }
    }
    window.clear();
    window.draw(spriteBackg);
    for (const auto &i: menu) {
        window.draw(i);
    }
    window.display();
}

void Menu::moveUp() {
    if (selectedMenu - 1 >= 0) {
        menu[selectedMenu].setFillColor(Color::White);
        selectedMenu--;
        menu[selectedMenu].setFillColor(Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedMenu + 1 <= menuOptions) {
        menu[selectedMenu].setFillColor(Color::White);

        selectedMenu++;

        if (selectedMenu == 4) {
            selectedMenu = 0;
        }
        menu[selectedMenu].setFillColor(Color::Red);
    }
}

void Menu::run() {
    while (window.isOpen()) {
        select();
    }
}

void Menu::startGame(bool isVai) {
    RenderWindow boardWindow(VideoMode(1600, 900), "Hexxagon", Style::Default);
    Board board = Board(boardWindow, scoreBoardFont, isVai);
    Texture background2;
    background2.loadFromFile(
            "Images\\polygonal-abstract-background-black-and-light-red-free-vector.jpg");

    Sprite backgroundTest;
    backgroundTest.setTexture(background2);
    backgroundTest.setOrigin(0, 0);
    while (boardWindow.isOpen()) {
        Event ge;
        while (boardWindow.pollEvent(ge)) {
            if (ge.type == Event::Closed) {
                boardWindow.close();
            }
            if (ge.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(boardWindow);
                board.mouseClick(mousePos);
            }
            if (board.getFinalScore() > 57) {
                boardWindow.close();
            }
        }

        boardWindow.clear();
        boardWindow.draw(backgroundTest);
        board.update();
        boardWindow.display();
    }
}

void Menu::startGame(const String &filename, bool isVai) {
    RenderWindow boardWindow(VideoMode(1600, 900), "Hexxagon", Style::Default);
    Board board = Board(boardWindow, scoreBoardFont, filename, isVai);
    Texture background2;
    background2.loadFromFile(
            "Images\\polygonal-abstract-background-black-and-light-red-free-vector.jpg");

    Sprite backgroundTest;
    backgroundTest.setTexture(background2);
    backgroundTest.setOrigin(0, 0);
    while (boardWindow.isOpen()) {
        Event ge;
        while (boardWindow.pollEvent(ge)) {
            if (ge.type == Event::Closed) {
                boardWindow.close();
            }
            if (ge.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(boardWindow);
                board.mouseClick(mousePos);
            }
            if (board.getFinalScore() > 57) {
                boardWindow.close();
            }
        }

        boardWindow.clear();
        boardWindow.draw(backgroundTest);
        board.update();
        boardWindow.display();
    }
}
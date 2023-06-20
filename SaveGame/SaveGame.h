#include <SFML/Graphics.hpp>
#include <vector>
#include "../Board/Hex.h"

using namespace sf;
using namespace std;

/**
 * @brief Zapis gry
 *
 * Klasa odpowiadająca za zapis, ale też wczytywanie gry.
 */

class SaveGame {
private:
    /**
     * @brief Przycisk SaveGame
     *
     * Wszystkie poniższe, prywatne pola odpowiadają za utworzenie przycisku "Save Game"
     * i jego graficzne wyświetlenie na planszy.
     */
    Text saveButtonText;
    Text fileNameText;
    RectangleShape saveGameButton;
    Font font;
    RenderWindow &window;
    string saveText = "";
public:
    /**
     * Konstruktor tworzący obiekt klasy SaveGame
     *
     * @param boardWindow Okno, na który ma zostać wyświetlony przycisk "Save Game".
     */
    SaveGame(RenderWindow &boardWindow);


    /**
     * @brief Ustawianie przycisku Save Game
     *
     * Metoda ustawia(kolor, pozycję na planszy itd.) graficznie przycisk "Save Game".
     */
    void setSaveGame();


    /**
     * @brief Rysowanie przycisku
     *
     * Rysuje przycisk Save Game na planszy.
     */
    void drawSaveButton();


    /**
     * @brief Zapis gry do pliku
     *
     * Zapisuje stan gry do pliku o nazwie wybranej przez użytkownika. Jest wywoływana
     * w metodzie showSaveWindow.
     *
     * @param fileName Nazwa pliku wpisana przez użytkownika.
     * @param vectorBoard Wektor przechowujący wszystkie pionki oraz informacje o nich.
     * @param currentP Przechowuje informację, kto w momencie zapisu gry powinien wykonywać swój ruch.
     */
    void saveGame(const String& fileName, vector<vector<Hex>> &vectorBoard, int currentP);


    /**
     * @brief Okno zapisu gry
     *
     * Tworzy i wyświetla okno, w którym gracz wpisuje nazwę pliku,
     * w którym chciałby zapisać stan rozgrywki.
     *
     * @param saveWindow Wyświetlane okno zapisu gry.
     * @param vectorBoard Wektor z zapisanym stanem pionków potrzebny do wywołania metody saveGame.
     * @param currentPlayer Przechowuje informację, kto w momencie zapisu gry powinien wykonywać swój ruch. Również
     * potrzebne przy wywoływaniu metody saveGame.
     */
    void showSaveWindow(RenderWindow &saveWindow, vector<vector<Hex>> &vectorBoard, int currentPlayer);


    /**
     * @brief Kliknięcie myszką
     *
     * Sprawdza, czy użytkownik kliknął przycisk Save Game.
     *
     * @param vec Pozycja myszki na ekranie, w momencie kliknięcia przycisku.
     * @return
     */
    bool isButtonPressed(Vector2i vec);


    /**
     * @brief Wpisywanie nazwy pliku do zapisu
     *
     * Metoda dodająca do tymczasowej nazwy pliku wpisanej przez użytkownika kolejną wpisaną przez niego literę.
     * Razem z metodami setFileNameText oraz deleteChar tworzą efekt dynamicznej zmiany nazwy pliku wpisywanej przez użytkownika
     * oraz wyświetlają to na ekranie.
     *
     * @param c Mała, lub duża litera wpisywana przez użytkownika z klawiatury.
     */
    void fillText(char c);
    void setFileNameText();
    string deleteChar();


    /**
     * @brief Wypełnianie wektora po wczytaniu gry
     *
     * Wypełnia wektor pionkami, aby wszystkie miały taki sam stan,
     * który miały w momencie zapisu
     *
     * @param vectorBoard Adres wektora, który zostaje uzupełniony pionkami.
     * @param fileName Nazwa pliku, z którego metoda ma pobrać stan zapisanych pionków.
     * @param currentPlayer
     */
    void fillBoardLoadGame(vector<vector<Hex>> &vectorBoard, const String &fileName, int &currentPlayer);


    /**
     * @brief Ustawianie parametrów przycisków do wczytania gry
     *
     * Ustawia parametry graficzne przycisków z nazwami plików do wczytania gry.
     *
     * @param vector Wektor przechowujący wszystkie nazwy plików typu String.
     * @param menuVector Wektor przechowujący pliki typu Text.
     * @param buttonsVec Wektor przechowujący finalne przyciski typu RectangleShape.
     */
    void setLoadGame(vector<string>& vector, ::vector<Text>& menuVector, ::vector<RectangleShape>& buttonsVec);


    /**
     * @brief Kliknięcie myszką
     *
     * Sprawdzc czy, a jeśli tak to który przycisk z wczytywaniem gry został kliknięty przez użytkownika.
     *
     * @param buttonsVec Wektor z przyciskami.
     * @param position Pozycja myszki na ekranie w momencie kliknięcia.
     * @return
     */
    int mouseClick(::vector<RectangleShape>& buttonsVec, Vector2i position);
};

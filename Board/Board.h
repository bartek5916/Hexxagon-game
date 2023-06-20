#include <vector>
#include <SFML/Graphics.hpp>
#include "../SaveGame/SaveGame.h"

using namespace sf;
using namespace std;

/**
 * @brief Plansza gry
 *
 * Główna klasa projektu. Jest odpowiedzielna za poprawne działanie i wyświeltanie
 * pionków na planszy, tabeli wyników ale również za całą logikę gry włącznie z logiką AI.
 */

class Board {
private:
    /**
     * @brief Tło planszy
     *
     * Obiekty reprezentujące tło planszy gry.
     */
    Sprite spriteBackg;
    Texture background;


    /**
     * @brief Licznik punktów
     *
     * Liczniki punktów dla gracza 1 oraz 2. Po uruchomieniu gry domyślnie ustawione na 3,bo
     * z tyloma pionkami każdy gracz zaczyna grę. Są dynamicznie aktualizowane po pojedynczym ruchu
     * każdego z graczy.
     */
    int p1Counter = 3;
    int p2Counter = 3;


    /**
     * @brief Wynik całej planszy
     *
     * Suma punktów gracza 1 i 2. Wykorzystywana przy warunku kończenia gry.
     */
    int finalScore = p1Counter + p2Counter;


    /**
     * @brief Czy przeciwko AI
     *
     * Przechowuje informacje o tym, czy uruchomiona gra jest przeciwko AI, czy przeciwko
     * drugiemu graczowi.
     *
     * True - vs Ai
     * False - vs Player
     */
    bool isAgainstAi;


    /**
     * @brief Tablica wyników
     *
     * Tablica wyników dla obydwu graczy, ale w formie możliwej do wyświetlenia na planszy.
     */
    Text scoreboardP1;
    Text scoreboardP2;


    /**
     * @brief Wektor przechowujący heksagony
     *
     * Dwuwymiarowy wektor przechowujący wszystkie pojedyczne heksagony na planszy.
     * Każdy następny wektor przechwouje taką ilość heksagonów, ile jest w każej kolejnej
     * kolumnie, którą widzimy po narysowaniu planszy.
     */
    vector<vector<Hex>> vectorBoard = {{}, {}, {}, {}, {}, {}, {}, {}, {}};


    /**
     * @brief Okno gry
     *
     * Przechowuje adres okna, na którym rysowana jest cała gra.
     *
     */
    RenderWindow &boardWindow;


    /**
     * @brief Wybrany pionek
     *
     * Wskaźnik na "podniesiony" w danym momencie przez gracza pionek.
     * Wykorzystywany przy wyrysowywaniu dostępnych dla tego pionka ruchów.
     */
    Hex *chosenHex2 = nullptr;


    /**
     * @brief Aktualny gracz
     *
     * Przechowuje informacje o tym, który gracz wykonuje teraz swój ruch.
     */
    int currentPlayer = 1;


    /**
     * @brief Zapis gry
     *
     * Obiekt klasy, której metody pozwalają na zapis i odczyt gry.
     */
    SaveGame saveGame;
public:
    /**
     * @brief Tworzenie planszy
     *
     * Tworzy nową planszę do gry.
     *
     * @param window Adres okna, na którym ma zostać wyrysowana plansza.
     * @param font Adres czcionki wykorzystywanej przy rysowaniu tablicy wyników, lub przycisku "Save Game".
     * @param isVsAi Przechowuje informacje o tym, czy gra będzie się toczyć przeciwko drugiem graczowi czy komputerowi.
     */
    Board(RenderWindow &window, Font &font, bool isVsAi);


    /**
     * @brief Tworzenie planszy
     *
     * Tworzy nową planszę do gry na podstawie wczytanego zapisu gry.
     *
     * @param window Adres okna, na którym ma zostać wyrysowana plansza.
     * @param font Adres czcionki wykorzystywanej przy rysowaniu tablicy wyników, lub przycisku "Save Game".
     * @param fileName Nazwa pliku, z którego ma zostać wczytany zapis(stan gry).
     * @param isVsAi Przechowuje informacje o tym, czy gra będzie się toczyć przeciwko drugiem graczowi czy komputerowi.
     */
    Board(RenderWindow &window, Font &font, const String& fileName, bool isVsAi);


    /**
     * @brief Kliknięcie myszką
     *
     * Bada kliknięcie myszką przez gracza a następnie wywołuje kolejne działania w zależności od rezultatu.
     * Jeśli kliknął w przycisk "Save Game" - wywołuje działania związane z zapisem gry,
     * jeśli kliknął w należący do niego heksagon - oznacza go jako wybrany itd.
     *
     * @param position Pozycja(x,y) myszy na planszy w momencie kliknięcia przez gracza.
     */
    void mouseClick(Vector2i position);


    /**
     * @brief Rysowanie planszy
     *
     * Metoda odpowiedzialna za narysowanie całej planszy złożonej z
     * heksagonów.
     */
    void drawBoard();


    /**
     * @brief Wypełnianie wektora planszy
     *
     * Odpowiada za wypełnienie wektora "vectorBoard" konkretnymi "Hexami".
     */
    void fillBoard();


    /**
     * @brief Wybrany pionek
     *
     * Sprawia, że kliknięty przez gracza pionek jest oznaczany jako wybrany, a następnie
     * na skutek działania innych metod zawartych w tej są pokazywane możliwe dla tego pionka ruchy.
     *
     * @param hex Reprezentuje kliknięty przez gracza pionek
     */
    void chooseHex(Hex &hex);


    /**
     * @brief Rysowanie pionka
     *
     * Rysuje pojedynczego pionka na planszy.
     *
     * @param hex Pionek do narysowania.
     */
    void drawHex(Hex& hex);


    /**
     * @brief Przemieszczenie pionka na planszy
     *
     * Przesuwa pionki na planszy. Jeśli pionek zostaje przesunięty na bliską odległość, to jest duplikowany,
     * jeśli na dalszą to "przeskakuje" na odpowiednie miejsce.
     *
     * @param chosenHex Wybrany do przesunięcia/ruchu pionek.
     * @param hexToMove Pionek, na który zostaje przesunięty wybrany wcześniej pionek.
     * @param isClose Przechowuje informacje, czy pionek jest przesuwany na bliską odległość (o jedno pole), czy na daleką(o dwa pola).
     * @param vectorB Adres wektora, który przechowuje heksagony na których wykonywane są wszystkie operacje.
     */
    void moveHex(Hex& chosenHex, Hex& hexToMove, bool isClose, vector<vector<Hex>> &vectorB);


    /**
     * @brief Aktualizowanie planszy
     *
     * Służy do aktualizowania, czyli ponownego rysowania całej planszy po każdym zdarzeniu(kliknięcie myszą, przesunięcie pionka itd.).
     */
    void update();


    /**
     * @brief Ustawianie tablicy wyników
     *
     * Graficzne ustawienie tablicy wyników, tak aby można ją było narysować.
     *
     * @param font Czcionka wykorzystywana do wypisania tablicy wyników.
     */
    void setScoreBoard(Font &font);


    /**
     *@brief Rysowanie tablicy wyników
     *
     * Rysuje tablicę wyników na planszy.
     */
    void drawScoreBoard();


    /**
     * @brief Zliacznie punktów
     *
     * Sprawdza planszę i liczy pionki, które należą do danego gracza.
     *
     * @param hexOwner Wartosc 1 lub 2 w zależności od tego którego gracza pionki chcemy przeliczyć.
     * 1 - Gracz nr 1
     * 2 - Gracz nr 2
     * @param vectorB Adres wektora przechowującego pionki.
     * @return
     */
    int countHexes(int hexOwner, vector<vector<Hex>> &vectorB);


    /**
     * Ustawianie finalnego wyniku
     *
     * Ustawia finalny wynik, czyli sumę pionków gracza nr 1 i 2. Wykorzystywane przy sprawdzaniu zapełnienia planszy.
     *
     * @param finalScore Zmienna przechowująca pełny wynik planszy.
     */
    void setFinalScore(int finalScore);


    /**
     * @brief Ruch AI
     *
     * Przechodzi po wszystkich pionkach należących do gracza nr 2 - czyli do AI.
     * Następnie przekazuje je po kolei do metody "checkAiMove", po czym wykonuje najlepszy obliczony ruch.
     */
    void aiMove();


    /**
     * @brief Kalkulacja ruchu AI
     *
     * Metoda wykorzystywana w ciele metody aiMove().Oblicza najlepszy ruch dla przekazanego do niej pionka.
     * Kalkulacja odbywa się w następujący sposób: w ciele metody zostaje skopiowany przekazany do niej wektor z heksagonami,
     * po to aby nie ingerować od razu w faktyczną planszę do gry. Następnie na skopiowanym wektorze są wykonywane wszystkie
     * możliwe dla niego ruchy i zostaje wtedy obliczony stan pionków AI na skopiowanej planszy oraz zapisany w zmiennej.
     * W ten sposób jest wyłaniany ruch, po którym AI ma najwięcej punktów na planszy.
     *
     * @param vectorB Wektor planszy przechowujący wszystkie heksagony.
     * @param hex Pionek należący do AI, dla którego testowane są wszystkie możliwe ruchy.
     * @return Wektor intów zwracający: liczbę punktów po wykonaniu najlepszego ruchu dla danego pionka, oraz jego x i y w wektorze.
     */
    vector<int> checkAiMove(vector<vector<Hex>> vectorB, Hex &hex);


    int getFinalScore();


    /**
     * @brief Dostępne ruchy
     *
     * Po wybraniu pionka do ruszenia się, pokazuje dostępne dla niego ruchy.
     *
     * @param h Pionek, dla którego zostają wyświetlone dostępne ruchy.
     * @param vectorB Wektor, w którym są przechowwywane pozostałe pionki.
     * @return
     */
    vector<Hex*> availableMoves(Hex &h, vector<vector<Hex>> &vectorB);
};




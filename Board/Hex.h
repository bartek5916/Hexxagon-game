#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * @brief Klasa Hex
 *
 * Klasa reprezentująca każdy pojedynczy heksagon.
 */

class Hex {
private:
    /**
     * @brief Tablica przechowująca wszystkie możliwe stany heksagonu.
     */
    inline static String hexState[4] = {"Empty", "Chosen", "Close", "Far"};
    CircleShape hexagon;


    /**
     * @brief Pozycja pionka na planszy
     *
     * Zmienne przechowujące pozycję x oraz y na planszy dla danego pionka.
     */
    double windowPositionX;
    double windowPositionY;


    /**
     * @brief Pozycja pionka w wektorze
     *
     * Pozycja pionka w wektorze vectorBoard.
     */
    int boardPositionX;
    int boardPositionY;


    /**
     * @brief Właściciel pionka.
     * 0 - Pionek nie ma właściciela
     * 1 - Gracz numer 1
     * 2 - Gracz numer 2
     * 3 - Pionek jest jednym z 3 niegrywalnych pionków na planszy.
     */
    int owner;


    /**
     * @brief Status pionka
     *
     * Domyślny stan dla każdego pionka po utworzeniu go.
     */
    String state = "Empty";


    /**
     * @brief Kolor pionka
     *
     * Reprezentuje w sposób graficzny właściciela danego pionka.
     */
    Color color;

protected:
    /**
     * @brief Ustawienie pionka
     *
     * Ustawia parametry pionka takie jak jego pozycję na planszy, kolor, czy promień.
     *
     * @param boardPositionX Pozycja X pionka na planszy.
     * @param boardPositionY Pozycja Y pionka na planszy.
     */
    void setHex(int boardPositionX, int boardPositionY);

    float getRadius2(){
        return hexagon.getRadius();
    }
public:
    /**
     * @brief Tworzenie pionka
     *
     * Konstruktor tworzący pionek. Przypisuje indeksy i oraz y w wektorze z pionkami
     * a także właściciela pionka.
     *
     * @param boardPositionX Pozycja X(indeks i) pionka w wektorze.
     * @param boardPositionY Pozycja Y(indeks j) pionka w wektorze.
     * @param owner Właściciel pionka.
     */
    Hex(int boardPositionX, int boardPositionY, int owner);
    ~Hex();


    /**
     * @brief Ustalanie stanu pionka
     *
     * Ustawia stan pionka na jeden z tablicy hexState.
     *
     * @param s Stan pionka przekazany w postaci zmiennej typu String.
     */
    void setState(const String &s);

    const String &getState() const;


    /**
     * @brief Zmiana koloru pionka
     *
     * Metoda zmieniająca kolor pionka w zależności od właściciela.
     * Zmienia również kolor obwodu pionka, w zależności od jego stanu.
     */
    void colorHex();

    void setOwner(int owner);
    int getOwner() const;

    /**
     * @brief Sprawdzanie pozycji kliknięcia myszki
     *
     * Sprawdza, czy kliknięcie myszą przez gracza nastąpiło w obrębie pionka
     * należącego do tego gracza.
     *
     * @param pos Pozycja myszy na planszy w momencie kliknięcia przycisku.
     * @return
     */
    bool isInsideHexagon(Vector2i pos);


    /**
     * @brief Rysowanie pionka na planszy
     *
     * Rysuje pionek na planszy.
     *
     * @param boardWindow Adres okna, na którym ma zostać narysowany pionek.
     */
    void draw(RenderWindow& boardWindow);


    /**
     * @brief Ustalanie pozycji pionka na planszy.
     *
     * Ustala i ustawia pozycję pionka w oknie(na planszy).
     * Jest domyślnie wywoływana w metodzie setHex.
     */
    void setPosition();

    float getWindowPositionX() const;
    float getWindowPositionY() const;


    int getBoardPositionX() const;
    int getBoardPositionY() const;
};

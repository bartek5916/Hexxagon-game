#include <SFML/Graphics.hpp>
#include <iostream>

#define menuOptions 4

using namespace sf;

/**
 * @brief Klasa menu
 *
 * Klasa Menu jest odpowiedzialna za tworzenie całego menu, wyświeltanie go oraz startowanie gry.
 * Ponadto są tutaj załadowywane wszystkie potrzebne w grze tekstury oraz czcionki.
 */

class Menu {
 /**
  * @brief Tło w menu
  *
  * Reprezentuje obrazek, który jest tłem dla menu, jego opcji oraz samej gry.
  */
    Texture background;


    /** / @brief Sprite utworzony z tła
     *
     * Sprite reprezentujący tło dla wielu elementów całego projektu.
     */
    Sprite spriteBackg;


    /**
     * @brief Okno menu
     *
     * Reprezentuje okno menu wyświetlane każdorazowo po włączeniu programu.
     * Jego parametery zostają raz ustawione w metodzie, a później nie są już zmieniane.
     * Okno głównego Menu zostaje zamknięte tylko wtedy, kiedy zamknięty zostaje cały program.
     */
    RenderWindow window;


    /**
     * @brief Czcionka menu
     *
     * Reprezentuje czcionkę używaną w główny menu programu.
     * Zostaje raz załadowana i nie jest już później zmieniana.
     */
    Font font;


    /**
     * @brief Czcionka tablicy wyników
     *
     * Reprezentuje czionkę tablicy wyników. Jest ona również używana jako czcionka przy wpisywaniu
     * nazwy pliku w jakim chcemy zapisać stan gry oraz przy wyświetlaniu możliwych do wczytania zapisów gry.
     */
    Font scoreBoardFont;


    /**
     * @brief Tablica przechowująca opcje w Menu
     *
     * Tablica przechowująca dostępne w Menu opcje typu Text do wybrania przez użytkownika.
     * Zostaje ona raz zdefiniowana w metodzie i nie jest później zmieniania.
     */
    Text menu[menuOptions];


    /**
     * @brief Wybrana opcja menu
     *
     * Reprezentuje opcję menu, którą użyutkownik w danym momencie wybiera strzałkami.
     * Domyślnie do uruchomieniu programu jest ustawiona na 0, co oznacza pierwszą opcję w menu.
     */
    int selectedMenu;

protected:
    /**
     * @brief Ustawienie parametrów dla klasy Menu
     *
     * Metoda ustawiająca wszystkie parametry dla zmiennych potrzebne do wyświetlenia Menu.
     * Są tutaj ustawiane: samo okno menu(rozmiar i tytuł), czcionki, tło oraz definiowana jest tablica menu.
     */
    void setAll();


    /**
     * @brief Ruch strzałką do góry
     *
     * Metoda odpowiedzialna za umożliwnie użytkownikowi poruszanie się
     * po menu za pomocą strzałki w górę na klawiaturze.
     */
    void moveUp();


    /**
     * @brief Ruch strzałką w dół
     *
     * Metoda odpowiedzialna za umożliwnie użytkownikowi poruszanie się
     * po menu za pomocą strzałki w dół na klawiaturze.
     */
    void moveDown();


    /**
     * @brief Wybór opcji w menu
     *
     * Wybór opcji w menu po naciśnięciu klawisza enter.
     * Po wybraniu odpowiedniej opcji otwierane jest(oraz ustawianie są jego parametry)
     * nowe okno z grą, możliwością wczytania zapisu gry, najlepszymi wynikami lub wyborem trybu gry.
     */
    void select();


    /**
     * @brief Start gry
     *
     * Służy do utworzenia nowego okna oraz wystartowania właściwej gry.
     *
     * @param isVai Przechowuje informację, czy wybranym przez użytkownika trybem gry jest PvP, czy PvE.
     */
    void startGame(bool isVai);


    /**
     * @brief Start gry z załadowanego zapisu gry.
     *
     * Służy do utworzenia nowego okna oraz wystartowania właściwej gry wybranej przez użytkownika
     * z wcześniej utworzynych zapisów.
     *
     * @param filename Nazwa pliku, w którym jest zapisany stan rozgrywki.
     * @param isVai Przechowuje informację, czy wybranym przez użytkownika trybem gry jest PvP, czy PvE.
     */
    void startGame(const String& filename, bool isVai);
    bool isAgainstAi = false;
public:
    Menu();
    ~Menu();


    /**
     * @brief Start programu
     *
     * Ma za zadanie uruchomić program.
     */
    void run();


    int getSelectedMenu(){
        return selectedMenu;
    }
};


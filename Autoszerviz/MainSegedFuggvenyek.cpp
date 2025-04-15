/**
*	\file MainSegedFuggvenyek.cpp
*	A f�program (main) men�rendszer�nek vizu�lis megjelen�t�s�hez �s m�k�d�s�hez
*	sz�ks�ges seg�df�ggv�nyek implement�ci�j�t tartalmazza.
*/

#include "MainSegedFuggvenyek.h"
#include "SzervizNyilvantartoRendszer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>  // system()
#include <limits>   // numeric_limits
#include <cstdio>   // getchar()

/// "Autoszerviz" felirat ASCII art ki�r�sa a konzolra, tabul�torral beh�zva
void kiirASCII1() {
    std::cout <<
        "\n\n\t    /\\         | |                                (_)\n"
        "\t   /  \\  _    _| |_ ___    ___ _______ _ ______   ___ ____\n"
        "\t  / /\\ \\| |  | | __/ _ \\ / __ |_  /  _ \\'  __\\ \\ / / |_  /\n"
        "\t / ____ \\ | _| | || (_) \\__   \\/ /   __/  |   \\ V /| |/ /\n"
        "\t/_/    \\_\\__,_ |\\__\\___/ |___ /___\\___ |__|    \\_/ |_/___/\n\n";
}

/// "Arrivederci" felirat ASCII art ki�r�sa a konzolra, tabul�torral beh�zva
void kiirASCII2() {
    std::cout <<
        "\n\n\t    /\\             (_)             | |             (_)\n"
        "\t   /  \\   _ __ _ __ ___   _____  __| | ___ _ __ ___ _ \n"
        "\t  / /\\ \\ | '__| '__| \\ \\ / / _ \\/ _` |/ _ \\ '__/ __| |\n"
        "\t / ____ \\| |  | |  | |\\ V /  __/ (_| |  __/ | | (__| |\n"
        "\t/_/    \\_\\_|  |_|  |_| \\_/ \\___|\\__,_|\\___|_|  \\___|_|\n\n";
}

/// A program �ltal biztos�tott funkci�k haszn�lat�hoz sz�ks�ges men� opci�k ki�r�sa
void menuOpciok() {
    kiirASCII1();
    std::cout << "\n\t1. Uj ugyfel es auto felvetele\n";
    std::cout << "\t2. Ugyfel keresese nev alapjan\n";
    std::cout << "\t3. Auto keresese rendszam alapjan\n";
    std::cout << "\t4. Javitas rogzitese\n";
    std::cout << "\t5. Autok vagy Ugyfelek adatainak fajlba irasa\n";
    std::cout << "\t6. Autok vagy Ugyfelek adatainak fajbol beolvasasa\n";
    std::cout << "\t0. Kilepes\n\n";
    std::cout << "\tValassz egy lehetoseget: ";
}

/// Megv�rja, am�g a felhaszn�l� lenyomja az Enter billenty�t.
/// �ltal�ban hiba�zenetek vagy inform�ci�k megjelen�t�se ut�n haszn�latos, 
/// hogy a felhaszn�l�nak legyen ideje elolvasni azokat.
void varakozasEnterre() {
    std::cout << "\n\tNyomj Entert a folytatashoz...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();  // v�rakoz�s
}

/// T�rli a konzol k�perny�t
void torolKonzol() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/// Ellen�rzi, hogy a megadott f�jl l�tezik-e.
/// @param f - A vizsg�lt f�jl neve (el�r�si �tvonal is lehet).
/// @return - true, ha a f�jl l�tezik, k�l�nben false.
bool letezikAFajl(const std::string& f) {
    std::ifstream fajl(f);
    return fajl.good();
}

/// F�jln�v bek�r�se, form�tum�nak �s l�tez�s�nek ellen�rz�se.
/// Elfogadja az "exit" sz�t is, ami visszal�p�st jelent a f�men�be.
/// @param mentesE - A f�ggv�ny c�lj�t jelz� kapcsol� (ment�s vagy bet�lt�s)
/// @param aDB - A szerviz adatb�zis objektum referenci�ja
/// @return true, ha sikeres volt a m�velet, false ha "exit"-tel kil�pt�nk
bool fajlNevHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB) {
    std::string fajlNev;
    while (true) {
        torolKonzol();
        kiirASCII1();
        std::cout << "\tAdd meg a fajl nevet (vagy 'exit' a kilepeshez): ";
        std::cin >> fajlNev;

        if (fajlNev == "exit") {
            return false;  // Jelzi, hogy visszal�pett
        }

        bool ugyfelFajl = fajlNev.find("_ufl.txt") != std::string::npos;
        bool autoFajl = fajlNev.find("_auo.txt") != std::string::npos;

        if (!ugyfelFajl && !autoFajl) {
            std::cout << "\n\tIsmeretlen fajlformatum! (Helyes: xxx_auo.txt vagy xxx_ufl.txt)";
        }
        else if (!mentesE && !letezikAFajl(fajlNev)) {
            std::cout << "\n\tA megadott fajl nem letezik!";
        }
        else {
            // f�jln�v helyes, m�velet v�gezhet�
            if (mentesE)
                aDB.mentesFajlba(fajlNev);
            else
                aDB.betoltesFajlbol(fajlNev);
            return true;
        }

        varakozasEnterre();
    }
}
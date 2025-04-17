/**
*	\file MainSegedFuggvenyek.cpp
*	A fõprogram (main) menürendszerének vizuális megjelenítéséhez és mûködéséhez
*	szükséges segédfüggvények implementációját tartalmazza.
*/

#include "MainSegedFuggvenyek.h"
#include "SzervizNyilvantartoRendszer.h"
#include "VegzettMuvelet.h"
#include "Vizsga.h"
#include "Karbantartas.h"
#include "Javitas.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>  // system()
#include <limits>   // numeric_limits
#include <cstdio>   // getchar()

/*-------------------------------------------
             Menü rendszerhez
-------------------------------------------*/
/// "Autoszerviz" felirat ASCII art kiírása a konzolra, tabulátorral behúzva
void kiirASCII1() {
    std::cout <<
        "\n\n\t    /\\         | |                                (_)\n"
        "\t   /  \\  _    _| |_ ___    ___ _______ _ ______   ___ ____\n"
        "\t  / /\\ \\| |  | | __/ _ \\ / __ |_  /  _ \\'  __\\ \\ / / |_  /\n"
        "\t / ____ \\ | _| | || (_) \\__   \\/ /   __/  |   \\ V /| |/ /\n"
        "\t/_/    \\_\\__,_ |\\__\\___/ |___ /___\\___ |__|    \\_/ |_/___/\n\n";
}

/// "Arrivederci" felirat ASCII art kiírása a konzolra, tabulátorral behúzva
void kiirASCII2() {
    std::cout <<
        "\n\n\t    /\\             (_)             | |             (_)\n"
        "\t   /  \\   _ __ _ __ ___   _____  __| | ___ _ __ ___ _ \n"
        "\t  / /\\ \\ | '__| '__| \\ \\ / / _ \\/ _` |/ _ \\ '__/ __| |\n"
        "\t / ____ \\| |  | |  | |\\ V /  __/ (_| |  __/ | | (__| |\n"
        "\t/_/    \\_\\_|  |_|  |_| \\_/ \\___|\\__,_|\\___|_|  \\___|_|\n\n";
}

/// A program által biztosított funkciók használatához szükséges menü opciók kiírása
void menuOpciok() {
    kiirASCII1();
    std::cout << "\n\t1. Az ugyfel/auto tarolok listazasa\n";
    std::cout << "\t2. Uj ugyfel/auto felvetele\n";
    std::cout << "\t3. Ugyfel keresese nev alapjan\n";
    std::cout << "\t4. Auto keresese rendszam alapjan\n";
    std::cout << "\t5. Uj szerviz muvelet rogzitese\n";
    std::cout << "\t6. Autok vagy Ugyfelek adatainak fajlba irasa\n";
    std::cout << "\t7. Autok vagy Ugyfelek adatainak fajbol beolvasasa\n";
    std::cout << "\t0. Kilepes\n\n";
    std::cout << "\tValassz egy lehetoseget: ";
}



/*-------------------------------------------
               UI élményhez
-------------------------------------------*/
/// Megvárja, amíg a felhasználó lenyomja az Enter billentyût.
/// Általában hibaüzenetek vagy információk megjelenítése után használatos, 
/// hogy a felhasználónak legyen ideje elolvasni azokat.
void varakozasEnterre() {
    std::cout << "\n\tNyomj Entert a folytatashoz...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // bemeneti puffer kiürítése
    std::cin.get();  // várakozás
}

/// Törli a konzol képernyõt
void torolKonzol() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/// Meghívja a torolKonzol-t majd kiírja a "Szerviz Nyilvántartó Rendszer" feliratot ASCII art formátumban
void toroloMajdCim() {
    torolKonzol();
    kiirASCII1();
}

/// Varakozik az Enter billentyû lenyomására, majd törli a konzolt
void varakozasTorol() {
    varakozasEnterre();
    torolKonzol();
}


/*-------------------------------------------
            1. menüponthoz
-------------------------------------------*/
/// Listázza az ügyfeleket vagy az autókat a megadott adatbázisból.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return - true, ha a kiirás sikeres volt, false, ha a felhasználó kilépett.
bool kiListazo(SzervizNyilvantartoRendszer& aDB) {
	std::string mitKerj;
    do {
        toroloMajdCim();
        std::cout << "\tAdd meg 'ugyfel' vagy 'auto' szeretned listazni ('exit' a kilepeshez): ";
        std::cin >> mitKerj;

        if (mitKerj == "exit") {
            torolKonzol();
            return false;
            break;
        }

		if (mitKerj != "ugyfel" && mitKerj != "auto" &&
            mitKerj != "Ugyfel" && mitKerj != "Auto") {
			std::cout << "\n\tIsmeretlen parancs! (ugyfel/auto/exit)";
			varakozasEnterre();
			continue;
		}

        if (mitKerj == "auto") {
            std::cout << "\n";
            for (size_t i = 0; i < aDB.getAutok().size(); i++) {
                std::cout << aDB.getAutok().at(i);
            }
            varakozasTorol();
            continue;
        }
        else if (mitKerj == "ugyfel") {
            std::cout << "\n";
            for (size_t i = 0; i < aDB.getUgyfelek().size(); i++) {
                std::cout << aDB.getUgyfelek().at(i);
            }
            varakozasTorol();
            continue;
        }
        return true;
	} while (mitKerj != "ugyfel" && mitKerj != "auto" && mitKerj != "exit");

    return true; // Ha valami miatt mégsem lépett vissza korábba
}



/*-------------------------------------------
            2. menüponthoz
-------------------------------------------*/
/// Új ügyfél vagy autó rögzítése.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/*
void ujUgyfelAuto(SzervizNyilvantartoRendszer& aDB) {
    std::string nev, tel, cim;
    std::cout << "Ugyfel neve: ";
    std::cin.ignore();
    std::getline(std::cin, nev);
    std::cout << "Telefonszama: ";
    std::getline(std::cin, tel);
    std::cout << "Cime: ";
    std::getline(std::cin, cim);

    Ugyfel ujUgyfel(nev, tel, cim);
    aDB.ujUgyfel(ujUgyfel);

    std::string rendszam, marka, tipus;
    int km;
    std::cout << "Auto rendszama: ";
    std::getline(std::cin, rendszam);
    std::cout << "Marka: ";
    std::getline(std::cin, marka);
    std::cout << "Tipus: ";
    std::getline(std::cin, tipus);
    std::cout << "Kilometerora allasa: ";
    std::cin >> km;

    Auto ujAuto(rendszam, marka, tipus, km);
    aDB.ujAuto(ujAuto);

    std::cout << "\t>>> Uj ugyfel es auto sikeresen rogzitve! <<<" << std::endl;
}
*/


/*-------------------------------------------
            3. menüponthoz
-------------------------------------------*/
/// Keres egy ügyfelet a megadott név alapján.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/*
void ugyfelKereses(SzervizNyilvantartoRendszer& rendszer) {
    std::string nev;
    std::cin.ignore();
    std::cout << "Add meg az ugyfel nevet: ";
    std::getline(std::cin, nev);

    try {
        const Ugyfel& u = rendszer.keresUgyfel(nev);
        std::cout << "Ugyfel adatai:\n" << u << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "\t>>> " << e.what() << " <<<" << std::endl;
    }
}
*/


/*-------------------------------------------
            4. menüponthoz
-------------------------------------------*/
/// Keres egy autót a megadott rendszám alapján.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/*
void autoKereses(SzervizNyilvantartoRendszer& rendszer) {
    std::string rendszam;
    std::cin.ignore();
    std::cout << "Add meg az auto rendszamat: ";
    std::getline(std::cin, rendszam);

    try {
        const Auto& a = rendszer.keresAuto(rendszam);
        std::cout << "Auto adatai:\n" << a << std::endl;
        rendszer.lekeroVegzettMuvelet(std::cout, rendszam);
    }
    catch (const std::exception& e) {
        std::cout << "\t>>> " << e.what() << " <<<" << std::endl;
    }
}
*/



/*-------------------------------------------
            5. menüponthoz
-------------------------------------------*/
/// Új szerviz mûvelet rögzítése egy autóhoz.
/// @param rendszer - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return - true, ha a mûvelet sikeresen rögzítve lett, false, ha a felhasználó kilépett.
bool ujSzervizMuvelet(SzervizNyilvantartoRendszer& aDB) {
    std::string milyenSzerviz;
    do {
        toroloMajdCim();
        std::cout << "\tAdd meg a szerviz muvelet tipusat 'vizsga', 'karbantartas' vagy 'javitas' ('exit' a kilepeshez): ";
        std::cin >> milyenSzerviz;

        if (milyenSzerviz == "exit") {
            return false;
            break;
        }

        if (milyenSzerviz != "vizsga" && milyenSzerviz != "karbantartas" && milyenSzerviz != "javitas" &&
            milyenSzerviz != "Vizsga" && milyenSzerviz != "Karbantartas" && milyenSzerviz != "Javitas") {
            std::cout << "\n\tIsmeretlen parancs! (vizsga/karbantartas/javitas/exit)";
            varakozasEnterre();
            continue;
        }

        std::string rendszam;
		Auto talaltAuto;
        std::cin.ignore();
        do {
            toroloMajdCim();
            std::cout << "\tAdd meg az auto rendszamat, formatum: 3 nagybetu majd 3 szam (pl: ABC123): ";
            std::getline(std::cin, rendszam);

            if (rendszam.length() != 6 || !isupper(rendszam[0]) || !isupper(rendszam[1]) || !isupper(rendszam[2]) ||
                !isdigit(rendszam[3]) || !isdigit(rendszam[4]) || !isdigit(rendszam[5])) {
                std::cout << "\n\tIsmeretlen rendszam formatum! (pelda: ABC123)";
                varakozasEnterre();
                continue;
            }

            if (!aDB.vanAuto(rendszam)) {
                std::cout << "\n\tA keresett auto nincs rendszerben, igy nem rogzitheto uj szervizmuvelet!";
                varakozasEnterre();
                continue;
            }
            talaltAuto = aDB.keresAuto(rendszam);
            break; // autó létezik és formátum is jó, kilépünk a ciklusból
        } while (true);

        toroloMajdCim();
        std::string muveletLeirasa;
        int ev, ho, nap, ar, km;
        std::cout << "\tAdd meg a javitas reszletes leirasat: ";
        std::cin >> muveletLeirasa;

		do {
            toroloMajdCim();
            std::cout << "\tAdd meg a datumot, formatum: ev ho nap (pl 2004 10 23): ";
            std::cin >> std::setw(4) >> ev >> std::setw(2) >> ho >> std::setw(2) >> nap;

			if (ho < 1 || ho > 12 || nap < 1 || nap > 31) {
				std::cout << "\n\tIsmeretlen datum formatum! (pelda: ev, 1 <= ho <= 12, 1 <= nap <= 31)";
				varakozasEnterre();
				continue;
			}
			break; // datum helyes formátumú, kilépünk a ciklusból
		} while (true);

        toroloMajdCim();
        std::cout << "\tAdd meg a szerviz muvelet arat: ";
        std::cin >> ar;

        do {
            toroloMajdCim();
            std::cout << "\tAdd meg az aktualis km allast: ";
            std::cin >> km;

            if (talaltAuto.getSzervizMuveletek().back()->getAktKmOra() > km) {
                std::cout << "\n\tNem lehet kisebb a km ora allasa mint a legutobbi szerviz eseten volt!";
				std::cout << "\n\tLegutolso szerviz km ora allasa: " << talaltAuto.getSzervizMuveletek().back()->getAktKmOra() << std::endl;
                varakozasEnterre();
                continue;
            }
            break;
        } while (true); // km óra helyes értéket tartalmaz, kilépünk a ciklusból
        

        VegzettMuvelet* ujSzervizMuvelet;
        if (milyenSzerviz == "vizsga") {
			bool siker;
			std::cout << "\tSikeres vizsga? (1 - Igen, 0 - Nem): ";
			std::cin >> siker;

            ujSzervizMuvelet = new Vizsga(muveletLeirasa, Datum(ev, ho, nap), km, ar, siker);
        }
        else if (milyenSzerviz == "karbantartas") {
            ujSzervizMuvelet = new Karbantartas(muveletLeirasa, Datum(ev, ho, nap), km, ar);
        } else {
            ujSzervizMuvelet = new Javitas(muveletLeirasa, Datum(ev, ho, nap), km, ar);
        }

        aDB.rogzitesVegzettMuvelet(rendszam, *ujSzervizMuvelet);
        delete ujSzervizMuvelet;
        return true;
    } while (milyenSzerviz != "vizsga" && milyenSzerviz != "karbantartas" && milyenSzerviz != "javitas" && milyenSzerviz != "exit" &&
             milyenSzerviz != "Vizsga" && milyenSzerviz != "Karbantartas" && milyenSzerviz != "Javitas" && milyenSzerviz != "Exit");

    return true; // Ha valami miatt mégsem lépett vissza korábba
}
// Lehetne szebben is egy tömbben vagy Vectorban beírva std::string-kent a lehetséges helyes megoldásokat



/*-------------------------------------------
            6-7. menüponthoz
-------------------------------------------*/
/// Ellenõrzi, hogy a megadott fájl létezik-e.
/// @param f - A vizsgált fájl neve (elérési útvonal is lehet).
/// @return - true, ha a fájl létezik, különben false.
bool letezikAFajl(const std::string& f) {
    std::ifstream fajl(f);
    return fajl.good();
}

/// Fájlnév bekérése, formátumának és létezésének ellenõrzése.
/// Elfogadja az "exit" szót is, ami visszalépést jelent a fõmenübe.
/// @param mentesE - A függvény célját jelzõ kapcsoló (mentés vagy betöltés)
/// @param aDB - A szerviz adatbázis objektum referenciája
/// @return true, ha sikeres volt a mûvelet, false, ha a felhasználó kilépett.
bool fajlNevHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB) {
    std::string fajlNev;
    while (true) {
        toroloMajdCim();
        std::cout << "\tAdd meg a fajl nevet (vagy 'exit' a kilepeshez): ";
        std::cin >> fajlNev;

        if (fajlNev == "exit") {
            return false;
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
            if (mentesE)
                aDB.mentesFajlba(fajlNev);
            else
                aDB.betoltesFajlbol(fajlNev);
            return true;
        }

        varakozasEnterre();
    }

    return false; // Ha valami miatt mégsem lépett vissza korábba
}
/**
*	\file MainSegedFuggvenyek.cpp
*	A f�program (main) men�rendszer�nek vizu�lis megjelen�t�s�hez �s m�k�d�s�hez
*	sz�ks�ges seg�df�ggv�nyek implement�ci�j�t tartalmazza.
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
             Men� rendszerhez
-------------------------------------------*/
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
               UI �lm�nyhez
-------------------------------------------*/
/// Megv�rja, am�g a felhaszn�l� lenyomja az Enter billenty�t.
/// �ltal�ban hiba�zenetek vagy inform�ci�k megjelen�t�se ut�n haszn�latos, 
/// hogy a felhaszn�l�nak legyen ideje elolvasni azokat.
void varakozasEnterre() {
    std::cout << "\n\tNyomj Entert a folytatashoz...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // bemeneti puffer ki�r�t�se
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

/// Megh�vja a torolKonzol-t majd ki�rja a "Szerviz Nyilv�ntart� Rendszer" feliratot ASCII art form�tumban
void toroloMajdCim() {
    torolKonzol();
    kiirASCII1();
}

/// Varakozik az Enter billenty� lenyom�s�ra, majd t�rli a konzolt
void varakozasTorol() {
    varakozasEnterre();
    torolKonzol();
}


/*-------------------------------------------
            1. men�ponthoz
-------------------------------------------*/
/// List�zza az �gyfeleket vagy az aut�kat a megadott adatb�zisb�l.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a kiir�s sikeres volt, false, ha a felhaszn�l� kil�pett.
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

    return true; // Ha valami miatt m�gsem l�pett vissza kor�bba
}



/*-------------------------------------------
            2. men�ponthoz
-------------------------------------------*/
/// �j �gyf�l vagy aut� r�gz�t�se.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
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
            3. men�ponthoz
-------------------------------------------*/
/// Keres egy �gyfelet a megadott n�v alapj�n.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
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
            4. men�ponthoz
-------------------------------------------*/
/// Keres egy aut�t a megadott rendsz�m alapj�n.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
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
            5. men�ponthoz
-------------------------------------------*/
/// �j szerviz m�velet r�gz�t�se egy aut�hoz.
/// @param rendszer - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
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
            break; // aut� l�tezik �s form�tum is j�, kil�p�nk a ciklusb�l
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
			break; // datum helyes form�tum�, kil�p�nk a ciklusb�l
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
        } while (true); // km �ra helyes �rt�ket tartalmaz, kil�p�nk a ciklusb�l
        

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

    return true; // Ha valami miatt m�gsem l�pett vissza kor�bba
}
// Lehetne szebben is egy t�mbben vagy Vectorban be�rva std::string-kent a lehets�ges helyes megold�sokat



/*-------------------------------------------
            6-7. men�ponthoz
-------------------------------------------*/
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
/// @return true, ha sikeres volt a m�velet, false, ha a felhaszn�l� kil�pett.
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

    return false; // Ha valami miatt m�gsem l�pett vissza kor�bba
}
/**
*	\file MainSegedFuggvenyek.cpp
*	A f�program (main) men�rendszer�nek vizu�lis megjelen�t�s�hez �s m�k�d�s�hez
*	sz�ks�ges seg�df�ggv�nyek implement�ci�j�t tartalmazza.
*/

#include "Memtrace.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>  // system()
#include <limits>   // numeric_limits
#include <cstdio>   // getchar()

#include "MainSegedFuggvenyek.h"
#include "SzervizNyilvantartoRendszer.h"
#include "VegzettMuvelet.h"
#include "Vizsga.h"
#include "Karbantartas.h"
#include "Javitas.h"
#include "Teszt.h"

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
    std::cout << '\t' << std::setw(2) << std::setfill('0') << 0 << ". Tesztek futatasa\n";
    std::cout << '\t' << std::setw(2) << std::setfill('0') << 1 << ". A tarolok listazasa\n";
    std::cout << '\t' << std::setw(2) << std::setfill('0') << 2 << ". Uj ugyfel/auto felvetele\n";
    std::cout << '\t' << std::setw(2) << std::setfill('0') << 3 << ". Ugyfelek/autok frissitese\n";
    std::cout << '\t' << std::setw(2) << std::setfill('0') << 4 << ". Ugyfelek/autok torlese\n";
    std::cout << '\t' << std::setw(2) << std::setfill('0') << 5 << ". Ugyfel keresese nev alapjan\n";
    std::cout << '\t' << std::setw(2) << std::setfill('0') << 6 << ". Auto keresese rendszam alapjan\n";
    std::cout << '\t' << std::setw(2) << std::setfill('0') << 7 << ". Uj szerviz muvelet rogzitese\n";
    std::cout << '\t' << std::setw(2) << std::setfill('0') << 8 << ". Autok vagy Ugyfelek adatainak fajlba irasa\n";
    std::cout << '\t' << std::setw(2) << std::setfill('0') << 9 << ". Autok vagy Ugyfelek adatainak fajbol beolvasasa\n";
	std::cout << '\t' << std::setw(2) << std::setfill('0') << 10 << ". Kilepes\n\n";
    std::cout << "\tValassz egy lehetoseget: ";
}



/*-------------------------------------------
               UI �lm�nyhez
-------------------------------------------*/
/// Megv�rja, am�g a felhaszn�l� lenyomja az Enter billenty�t.
/// �ltal�ban hiba�zenetek vagy inform�ci�k megjelen�t�se ut�n haszn�latos, hogy a felhaszn�l�nak legyen ideje elolvasni azokat.
/// @param o - A ki�rand� �zenet.
void varakozasEnterre(const std::string& o) {
    std::cout << o;
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
    varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
    torolKonzol();
}



/*-------------------------------------------
                Seg�d
-------------------------------------------*/
/// Ellen�rzi, hogy a megadott rendsz�m form�tuma helyes-e.
/// @param rendszam - A vizsg�lt rendsz�m.
/// @return - true, ha a form�tum helyes, false, ha helytelen.
bool helyesRendszamFormatum(const std::string& rendszam) {
    if (rendszam.length() != 6)
        return false;

    return isupper(rendszam[0]) && isupper(rendszam[1]) && isupper(rendszam[2]) &&
        isdigit(rendszam[3]) && isdigit(rendszam[4]) && isdigit(rendszam[5]);
}

/// Ellen�rzi, hogy a megadott f�jl l�tezik-e.
/// @param f - A vizsg�lt f�jl neve (el�r�si �tvonal is lehet).
/// @return - true, ha a f�jl l�tezik, k�l�nben false.
bool letezikAFajl(const std::string& f) {
    std::ifstream fajl(f);
    return fajl.good();
}

/// Bek�ri a felhaszn�l�t�l egy d�tum (�v, h�nap, nap) �rt�keit.
/// Addig ism�tli a bek�r�st, am�g helyes form�tum� (�rv�nyes tartom�nyban l�v�) d�tumot nem kap.
/// @return - A bek�rt d�tum `Datum` t�pusban.
Datum bekerDatum() {
    int ev, ho, nap;

    while (true) {
        toroloMajdCim();
        std::cout << "\tAdd meg a datumot (ev honap nap): ";
        std::cin >> ev >> ho >> nap;

        if (ho >= 1 && ho <= 12 && nap >= 1 && nap <= 31 && ev >= 1000 && ev <= 9999) {
            break;
        }
        else {
            std::cout << "\n\tIsmeretlen datum formatum!";
            varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return Datum(ev, ho, nap);
}


/// Bek�r egy sort a felhaszn�l�t�l, miut�n ki�r egy megadott �zenetet.
/// @param t - A felhaszn�l�nak megjelen�tend� �zenet.
/// @return - A felhaszn�l� �ltal be�rt sor.
std::string sorBeker(const std::string& t) {
    toroloMajdCim();
    std::string sor;
    std::cout << t;
    std::getline(std::cin, sor);
    return sor;
}

/// Lefuttat egy adott m�veletet, majd a visszat�r�si �rt�kt�l f�gg�en ki�rja a megfelel� �zenetet.
/// @param muvelet - A v�grehajtand� f�ggv�ny.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @param sikerUzenet - Az �zenet, ha a m�velet sikeres.
void muveletFuttato(bool (*muvelet)(SzervizNyilvantartoRendszer&), SzervizNyilvantartoRendszer& aDB, const std::string& sikerUzenet) {
    if (!muvelet(aDB)) {
        torolKonzol();
        std::cout << "\t=== " << "Sikeres vissza lepes a menube!" << " ===";
    } else {
        torolKonzol();
        std::cout << "\t=== " << sikerUzenet << " ===";
    }
}

/// Lefuttatja f�jl kezel�shez sz�ks�ges m�veletet, majd a visszat�r�si �rt�kt�l f�gg�en ki�rja a megfelel� �zenetet.
/// @param muvelet - A v�grehajtand� f�ggv�ny.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @param sikerUzenet - Az �zenet, ha a m�velet sikeres.
void fajlMuveletFuttato(bool (*muvelet)(bool, SzervizNyilvantartoRendszer&), SzervizNyilvantartoRendszer& aDB, bool tipus, const std::string& sikerUzenet) {
    if (!muvelet(tipus, aDB)) {
        torolKonzol();
        std::cout << "\t=== " << "Sikeres vissza lepes a menube!" << " ===";
    }
    else {
        torolKonzol();
        std::cout << "\t=== " << sikerUzenet << " ===";
    }
}



/*-------------------------------------------
            1. men�ponthoz
-------------------------------------------*/
/// List�zza az �gyfeleket vagy az aut�kat a megadott adatb�zisb�l.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a kiir�s sikeres volt, false, ha a felhaszn�l� kil�pett.
bool kiListazo(SzervizNyilvantartoRendszer& aDB) {
	std::string mitKerj;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(true) {
        toroloMajdCim();
        std::cout << "\tAdd meg a ki listazando adatbazist ('ugyfel', 'auto' vagy 'exit' a kilepeshez): ";
        std::getline(std::cin, mitKerj);

        if (mitKerj == "exit")
            return false;

		if (mitKerj != "ugyfel" && mitKerj != "auto") {
			std::cout << "\n\tIsmeretlen parancs!";
			varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
			continue;
		}

        if (mitKerj == "ugyfel") {
            std::cout << "\n\t--- Ugyfelek adatai ---\n";
			if (aDB.getUgyfelek().empty()) {
				std::cout << "\tNincsenek ugyfelek a rendszerben!\n";
				varakozasTorol();
				return true;
			}
            for (const auto& ugyfel : aDB.getUgyfelek())
                std::cout << ugyfel;
            varakozasTorol();
        } else if (mitKerj == "auto") {
            std::cout << "\n\t--- Autok adatai ---\n";
			if (aDB.getAutok().empty()) {
				std::cout << "\tNincsenek autok a rendszerben!\n";
				varakozasTorol();
				return true;
			}
            for (const auto& autok : aDB.getAutok())
                std::cout << autok;
            varakozasTorol();
        }
        return true;
	}

    return true;
}



/*-------------------------------------------
           2. men�ponthoz
-------------------------------------------*/
/// �j �gyf�l vagy aut� r�gz�t�se.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool ugyfelAutoAdd(SzervizNyilvantartoRendszer& aDB) {
    std::string mitFelvesz;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        toroloMajdCim();
        std::cout << "\tMit szeretnel felvenni ('ugyfel', 'auto' vagy 'exit' a kilepeshez): ";
        std::getline(std::cin, mitFelvesz);

        if (mitFelvesz == "exit")
            return false;

        if (mitFelvesz != "ugyfel" && mitFelvesz != "auto") {
            std::cout << "\n\tIsmeretlen parancs!";
            varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
            continue;
        }

        toroloMajdCim();

        // �j �gyf�l felvitele
        if (mitFelvesz == "ugyfel") {
            std::string nev;
            while (true) {
                nev = sorBeker("\tAdd meg az ugyfel nevet (pelda: 'Hajdu Patrik Zsolt'): ");

                if (aDB.vanUgyfel(nev)) {
                    std::cout << "\n\tA keresett ugyfel mar a rendszerben van!";
                    varakozasTorol();
                    return false;
                }
                break;
            }

            std::string tel = sorBeker("\tAdd meg az ugyfel telefonszamat: ");
            std::string cim = sorBeker("\tAdd meg az ugyfel cimet: ");

            aDB.ujUgyfel(Ugyfel(nev, tel, cim));
            return true;
        }

        // �j aut� felvitele
        if (mitFelvesz == "auto") {
            std::string rendszam;
            while (true) {
                rendszam = sorBeker("\tAdd meg az auto rendszamat (pelda: 'ABC123'): ");

                if (!helyesRendszamFormatum(rendszam)) {
                    std::cout << "\n\tIsmeretlen rendszam formatum!";
                    varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
                    continue;
                }

                if (aDB.vanAuto(rendszam)) {
                    std::cout << "\n\tA keresett auto mar a rendszerben van!";
                    varakozasTorol();
                    return false;
                }

                break;
            }

            std::string marka = sorBeker("\tAdd meg az auto markajat: ");
            std::string tipus = sorBeker("\tAdd meg az auto tipusat: ");

            toroloMajdCim();
            int km;
            std::cout << "\tAdd meg az auto kilometerora allasat: ";
            std::cin >> km;

            Datum datum = bekerDatum();
            std::string tulajNev = sorBeker("\tAdd meg az auto tulajdonosat (pelda: 'Hajdu Patrik Zsolt'): ");

            Ugyfel* tulajPtr = nullptr;
            if (aDB.vanUgyfel(tulajNev)) {
                tulajPtr = &aDB.keresUgyfel(tulajNev);
            } else {
                std::string tel = sorBeker("\tUj tulajdonos, kerlek add meg a telefonszamat: ");
                std::string cim = sorBeker("\tAdd meg a lakcimet: ");
                aDB.ujUgyfel(Ugyfel(tulajNev, tel, cim));
                tulajPtr = &aDB.getUgyfelek().back();
            }

            aDB.ujAuto(Auto(rendszam, marka, tipus, km, datum, Vector<VegzettMuvelet*>(), tulajPtr));
            return true;
        }
    }

    return true;
}



/*-------------------------------------------
           3. men�ponthoz
-------------------------------------------*/
/// Megl�v� �gyf�l vagy aut� friss�t�se.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool ugyfelAutoFrissit(SzervizNyilvantartoRendszer& aDB) {
    std::string MitFrissit;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        toroloMajdCim();
        std::cout << "\tMit szeretnel frissiteni ('ugyfel', 'auto' vagy 'exit' a kilepeshez): ";
        std::getline(std::cin, MitFrissit);

        if (MitFrissit == "exit")
            return false;

        if (MitFrissit != "ugyfel" && MitFrissit != "auto") {
            std::cout << "\n\tIsmeretlen parancs!";
            varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
            continue;
        }

        // �gyf�l friss�t�se
        if (MitFrissit == "ugyfel") {
            std::string nev = sorBeker("\tAdd meg az ugyfel nevet (pelda: 'Hajdu Patrik Zsolt'): ");

            if (!aDB.vanUgyfel(nev)) {
                std::cout << "\n\tNincs ilyen nevu ugyfel a rendszerben!";
                varakozasTorol();
                return false;
            }

            Ugyfel u = aDB.keresUgyfel(nev);

            std::string ujTel = sorBeker("\tAdd meg az uj telefonszamot: ");
            std::string ujEmail = sorBeker("\tAdd meg az uj email cimet: ");

            u.setTel(ujTel);
            u.setEmail(ujEmail);
            aDB.frissitUgyfel(u);

            return true;
        }

        // Aut� friss�t�se
        if (MitFrissit == "auto") {
            std::string rendszam;
            while (true) {
                rendszam = sorBeker("\tAdd meg az auto rendszamat (pelda: 'ABC123'): ");

                if (!helyesRendszamFormatum(rendszam)) {
                    std::cout << "\n\tIsmeretlen rendszam formatum!";
                    varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
                    continue;
                }

                if (!aDB.vanAuto(rendszam)) {
                    std::cout << "\n\tNincs ilyen rendszamu auto a rendszerben!";
                    varakozasTorol();
                    return false;
                }

                break;
            }

            Auto a = aDB.keresAuto(rendszam);

            int km;
            while (true) {
                toroloMajdCim();
                std::cout << "\tAdd meg az uj kilometerora allast: ";
                std::cin >> km;

                if (a.getSzervizMuveletek().back()->getAktKmOra() > km) {
                    std::cout << "\n\tNem lehet kisebb a km ora allasa mint az ami a legutolso szerviznel lett rogzitve!";
                    std::cout << "\n\tLegutolso szerviz km ora allasa: " << a.getSzervizMuveletek().back()->getAktKmOra() << std::endl;
                    varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
                    continue;
                }
                break;
            }
            a.setKmOra(km);
            aDB.frissitAuto(a);

            return true;
        }
    }

    return true;
}




/*-------------------------------------------
            4. men�ponthoz
-------------------------------------------*/
/// A rendszerben l�v� �gyf�l vagy aut� t�rl�s�re szolg�l.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool ugyfelAutoTorlo(SzervizNyilvantartoRendszer& aDB) {
   std::string mitTorol;
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

   while (true) {
       mitTorol = sorBeker("\tMit szeretnel torolni ('ugyfel', 'auto' vagy 'exit' a kilepeshez): ");

       if (mitTorol == "exit")
           return false;

       if (mitTorol != "ugyfel" && mitTorol != "auto") {
           std::cout << "\n\tIsmeretlen parancs!";
           varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
           continue;
       }

       if (mitTorol == "ugyfel") {
           std::string nev = sorBeker("\tAdd meg az ugyfel nevet, akit torolni szeretnel (pelda: 'Hajdu Patrik Zsolt'): ");

           if (!aDB.vanUgyfel(nev)) {
               std::cout << "\n\tA keresett ugyfel nincs rendszerben!";
               varakozasTorol();
               return false;
           }

           aDB.torolUgyfel(nev);
       } else if (mitTorol == "auto") {
           std::string rendszam;

           while(true) {
               rendszam = sorBeker("\tAdd meg az auto rendszamat, amit torolni szeretnel (pelda: 'ABC123'): ");

               if (!helyesRendszamFormatum(rendszam)) {
                   std::cout << "\n\tIsmeretlen rendszam formatum!";
                   varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
                   continue;
               }

               if (!aDB.vanAuto(rendszam)) {
                   std::cout << "\n\tA keresett auto nincs rendszerben!";
                   varakozasTorol();
                   return false;
               }
               break;
		   }

		   aDB.torolAuto(rendszam);
       }
	   torolKonzol();
       return true;
   }
   return true;
}



/*-------------------------------------------
            5. men�ponthoz
-------------------------------------------*/
/// Keres egy �gyfelet a megadott n�v alapj�n.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool ugyfelKereses(SzervizNyilvantartoRendszer& aDB) {
    std::string nev;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        nev = sorBeker("\tAdd meg az ugyfel nevet ('Hajdu Patrik Zsolt' vagy 'exit'): ");

        if (nev == "exit")
            return false;

        if (!aDB.vanUgyfel(nev)) {
            std::cout << "\n\tA keresett ugyfel nincs rendszerben!";
            varakozasTorol();
            return true;
        }

        toroloMajdCim();
        const Ugyfel& ugyfelRef = aDB.keresUgyfel(nev);
        std::cout << "\t--- Ugyfel adatai ---\n";
        std::cout << ugyfelRef;

        varakozasTorol();
        return true;
    }

    return true;
}



/*-------------------------------------------
            6. men�ponthoz
-------------------------------------------*/
/// Keres egy aut�t a megadott rendsz�m alapj�n.
/// @param rendszer - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool autoKereses(SzervizNyilvantartoRendszer& aDB) {
    std::string rendszam;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        rendszam = sorBeker("\tAdd meg az auto rendszamat ('ABC123' vagy 'exit' a kilepeshez): ");

        if (rendszam == "exit")
            return false;
        
        if (!helyesRendszamFormatum(rendszam)) {
            std::cout << "\n\tIsmeretlen rendszam formatum!";
            varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
            continue;
        }

        if (!aDB.vanAuto(rendszam)) {
            std::cout << "\n\tA keresett auto nincs rendszerben!";
            varakozasTorol();
            return true;
        }

        toroloMajdCim();
        const Auto& autoRef = aDB.keresAuto(rendszam);
        std::cout << "\t--- Auto adatai ---\n";
        std::cout << autoRef;

        std::cout << "\t--- Figyelmeztetesek ---\n";
		aDB.figyelmeztetesek(std::cout, autoRef);

		/* Ha k�l�n ki szeretn�d csak a szerviz m�veleteket list�zni van r� opci�
        std::cout << "\n\t--- Szerviz muveletek ---\n";
        aDB.lekeroVegzettMuvelet(std::cout, rendszam);
        */

        varakozasTorol();
        return true;
    }
    return true;
}




/*-------------------------------------------
            7. men�ponthoz
-------------------------------------------*/
/// �j szerviz m�velet r�gz�t�se egy aut�hoz.
/// @param rendszer - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool ujSzervizMuvelet(SzervizNyilvantartoRendszer& aDB) {
    std::string milyenSzerviz;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        milyenSzerviz = sorBeker("\tAdd meg a szerviz muvelet tipusat ('vizsga', 'karbantartas', 'javitas' vagy 'exit' a kilepeshez): ");

        if (milyenSzerviz == "exit")
            return false;

        if (milyenSzerviz != "vizsga" && milyenSzerviz != "karbantartas" && milyenSzerviz != "javitas") {
            std::cout << "\n\tIsmeretlen parancs!";
            varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
            continue;
        }

        std::string rendszam;
        Auto talaltAuto;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (true) {
            rendszam = sorBeker("\tAdd meg az auto rendszamat (pelda: 'ABC123'): ");

            if (!helyesRendszamFormatum(rendszam)) {
                std::cout << "\n\tIsmeretlen rendszam formatum!";
                varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
                continue;
            }

            if (!aDB.vanAuto(rendszam)) {
                std::cout << "\n\tA keresett auto nincs rendszerben, igy nem rogzitheto uj szervizmuvelet!";
                varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
                return false;
            }
            talaltAuto = aDB.keresAuto(rendszam);
            break; // aut� l�tezik �s form�tum is j�, kil�p�nk a ciklusb�l
        }

        std::string muveletLeirasa = sorBeker("\tAdd meg a javitas reszletes leirasat: ");
        Datum datum = bekerDatum();
        
        int ar, km;
        toroloMajdCim();
        std::cout << "\tAdd meg a szerviz muvelet arat: ";
        std::cin >> ar;

        while(true) {
            toroloMajdCim();
            std::cout << "\tAdd meg az aktualis km ora allast: ";
            std::cin >> km;

            if (talaltAuto.getSzervizMuveletek().back()->getAktKmOra() > km) {
                std::cout << "\n\tNem lehet kisebb a km ora allasa mint az ami a legutolso szerviznel lett rogzitve!";
                std::cout << "\n\tLegutolso szerviz km ora allasa: " << talaltAuto.getSzervizMuveletek().back()->getAktKmOra() << std::endl;
                varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
                continue;
            }
            break;
        } // km �ra helyes �rt�ket tartalmaz, kil�p�nk a ciklusb�l


        VegzettMuvelet* ujSzervizMuvelet;
        if (milyenSzerviz == "vizsga") {
            bool siker;
            toroloMajdCim();
            std::cout << "\tSikeres vizsga? (1 - Igen, 0 - Nem): ";
            std::cin >> siker;

            ujSzervizMuvelet = new Vizsga(muveletLeirasa, datum, km, ar, siker);
        }
        else if (milyenSzerviz == "karbantartas") {
            ujSzervizMuvelet = new Karbantartas(muveletLeirasa, datum, km, ar);
        }
        else {
            ujSzervizMuvelet = new Javitas(muveletLeirasa, datum, km, ar);
        }

        aDB.rogzitesVegzettMuvelet(rendszam, *ujSzervizMuvelet);
        delete ujSzervizMuvelet;
        return true;
    };
    return true;
}



/*-------------------------------------------
            8.-9. men�ponthoz
-------------------------------------------*/
/// F�jln�v bek�r�se, form�tum�nak �s l�tez�s�nek ellen�rz�se.
/// Elfogadja az "exit" sz�t is, ami visszal�p�st jelent a f�men�be.
/// @param mentesE - A f�ggv�ny c�lj�t jelz� kapcsol� (ment�s vagy bet�lt�s)
/// @param aDB - A szerviz adatb�zis objektum referenci�ja
/// @return true, ha sikeres volt a m�velet, false, ha a felhaszn�l� kil�pett.
bool fajlHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB) {
    std::string fajlNev;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        fajlNev = sorBeker("\tAdd meg a fajl nevet ('xxx_auo.txt', 'xxx_ufl.txt' vagy 'exit' a kilepeshez): ");

        if (fajlNev == "exit")
            return false;

        bool ugyfelFajl = fajlNev.find("_ufl.txt") != std::string::npos;
        bool autoFajl = fajlNev.find("_auo.txt") != std::string::npos;

        if (!ugyfelFajl && !autoFajl) {
            std::cout << "\n\tIsmeretlen fajlformatum!";
            varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
			continue;
        }
        else if (!mentesE && !letezikAFajl(fajlNev)) {
            std::cout << "\n\tA megadott fajl nem letezik!";
            varakozasEnterre("\n\tNyomj Entert a folytatashoz...");
			continue;
        }
        else {
            if (mentesE)
                aDB.mentesFajlba(fajlNev);
            else
                aDB.betoltesFajlbol(fajlNev);
            return true;
        }
    }
    return true;
}
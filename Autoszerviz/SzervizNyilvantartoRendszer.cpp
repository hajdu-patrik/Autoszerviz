/**
*   \file SzervizNyilvantartoRendszer.cpp
*   A SzervizNyilvantartoRendszer osztály tagfüggvényeinek megvalósítása.
*/

#include "Memtrace.h"
#include <fstream>
#include <sstream>
#include <regex>
#include "Vector.hpp"
#include "Auto.h"
#include "Ugyfel.h"
#include "SzervizNyilvantartoRendszer.h"
#include "VegzettMuvelet.h"
#include "Datum.h"
#include "Vizsga.h"
#include "Karbantartas.h"
#include "Javitas.h"

/*-------------------------------------------
		Konstruktorok és destruktor
-------------------------------------------*/
/// Alapértelmezett konstruktor.
/// Üres vektort hoz létre, előre lefoglalt kapacitással.
SzervizNyilvantartoRendszer::SzervizNyilvantartoRendszer() : autok(), ugyfelek() {}

/// Paraméteres konstruktor
/// @param a - Az autó példány
/// @param u - Az ügyfél példány
SzervizNyilvantartoRendszer::SzervizNyilvantartoRendszer(const Auto& a, const Ugyfel& u) {
	autok.push_back(a);
	ugyfelek.push_back(u);
}

/// Másoló konstruktor.
/// @param v - Másolandó SzervizNyilvantartoRendszer példány
SzervizNyilvantartoRendszer::SzervizNyilvantartoRendszer(const SzervizNyilvantartoRendszer& v) {
	for (size_t i = 0; i < v.autok.size(); i++)
		autok.push_back(v.autok.at(i));
	for (size_t i = 0; i < v.ugyfelek.size(); i++)
		ugyfelek.push_back(v.ugyfelek.at(i));
}

/// Destruktor.
/// Ez jelzi, hogy nem kell semmi egyedi a destruktorba, mert a tagok destruktora magától elintézi.
SzervizNyilvantartoRendszer::~SzervizNyilvantartoRendszer() = default;



/*-------------------------------------------
				Getter
-------------------------------------------*/
/// Visszaadja az összes autó objektumot.
/// @return - Egy Vector<Auto> példány, amely az összes jelenleg nyilvántartott autót tartalmazza.
Vector<Auto> SzervizNyilvantartoRendszer::getAutok() {
	return autok;
}


/// Visszaadja az összes ügyfél objektumot.
/// @return - Egy Vector<Ugyfel> példány, amely az összes jelenleg nyilvántartott ügyfelet tartalmazza.
Vector<Ugyfel> SzervizNyilvantartoRendszer::getUgyfelek() {
	return ugyfelek;
}



/*-------------------------------------------
				Bővítő tagfüggvények
-------------------------------------------*/
/// Új autó hozzáadása az adatbázishoz.
/// @param a - Az új autó példány.
void SzervizNyilvantartoRendszer::ujAuto(const Auto& a) {
	autok.push_back(a);
}

/// Új ügyfél hozzáadása az adatbázishoz.
/// @param u - Az új ügyfél példány.
void SzervizNyilvantartoRendszer::ujUgyfel(const Ugyfel& u) {
	ugyfelek.push_back(u);
}



/*-------------------------------------------
			Frissítő tagfüggvények
-------------------------------------------*/
/// Egy autó adatainak frissítése a rendszeren belül.
/// Ha a rendszeren belül már létezik az autó (rendszám alapján), akkor az adatai frissülnek.
/// @param a - Az autó új adatai.
/// @throws std::out_of_range - Ha az autó nem található.
void SzervizNyilvantartoRendszer::frissitAuto(const Auto& a) {
	// Az auto használata az iterátorok esetében a kódot egyszerűsíti, rugalmasabbá teszi és csökkenti a hibák lehetőségét,
	// miközben biztosítja, hogy a típusok mindig pontosak legyenek a kód bármely részében.
	for (auto it = autok.begin(); it != autok.end(); it++) {
		if (it->getRendszam() == a.getRendszam()) {
			*it = a;
			return;
		}
	}
	throw std::out_of_range("A megadott auto nincs rendszerben, igy nem frissitheto! (frissitAuto)");
}


/// Egy ügyfél adatainak frissítése a rendszeren belül.
/// Ha a rendszeren belül már létezik az ügyfél (név alapján), akkor az adatai frissülnek.
/// @param u - Az ügyfél új adatai.
/// @throws std::out_of_range - Ha az ügyfél nem található.
void SzervizNyilvantartoRendszer::frissitUgyfel(const Ugyfel& u) {
	for (auto it = ugyfelek.begin(); it != ugyfelek.end(); it++) {
		if (it->getNev() == u.getNev()) {
			*it = u;
			return;
		}
	}
	throw std::out_of_range("A megadott ugyfel nincs rendszerben, igy nem firssitheto! (frissitUgyfel)");
}



/*-------------------------------------------
			Törlő tagfüggvények
-------------------------------------------*/
/// Egy autó törlése rendszám alapján.
/// @param r - A törlendő autó rendszáma.
/// @throws std::out_of_range - Ha az autó nem található.
void SzervizNyilvantartoRendszer::torolAuto(const std::string& r) {
	for (auto it = autok.begin(); it != autok.end(); ++it) {
		if (it->getRendszam() == r) {
			autok.erase(it);  // Az iterátor használata
			return;
		}
	}
	throw std::out_of_range("A megadott auto nincs rendszerben, igy nem torolheto! (torolAuto)");
}

/// Egy ügyfél törlése név alapján.
/// @param n - A törlendő ügyfél neve.
/// @throws std::out_of_range - Ha az ügyfél nem található.
void SzervizNyilvantartoRendszer::torolUgyfel(const std::string& n) {
	for (auto it = ugyfelek.begin(); it != ugyfelek.end(); ++it) {
		if (it->getNev() == n) {
			ugyfelek.erase(it);
			return;
		}
	}
	throw std::out_of_range("A megadott ugyfel nincs rendszerben, igy nem torolheto! (torolUgyfel)");
}




/*-------------------------------------------
		  Kereső tagfüggvények
-------------------------------------------*/
/// Autó keresése rendszám alapján.
/// @param r - A keresett autó rendszáma (teljes egyezés).
/// @return - Az autó referenciája, ha megtalálta.
/// @throws std::out_of_range - Ha az autó nem található.
Auto& SzervizNyilvantartoRendszer::keresAuto(const std::string& r) {
	for (auto it = autok.begin(); it != autok.end(); ++it) {
		if (it->getRendszam() == r) {
			return *it;  // Az iterált elem referenciája
		}
	}
	throw std::out_of_range("A keresett auto nincs rendszerben! (keresAuto)");
}

/// Ügyfél létezésének ellenőrzése név alapján.
/// @param r - A keresett autó rendszáma (teljes egyezés).
/// @return - True, ha az auto megtalálható a rendszerben, false egyébként.
bool SzervizNyilvantartoRendszer::vanAuto(const std::string& r) const {
	for (const auto& au : autok) {
		if (au.getRendszam() == r) {
			return true;
		}
	}
	return false;
}

/// Ügyfél keresése név alapján.
/// @param n - A keresett ügyfél neve (teljes egyezés).
/// @return - Az ügyfél referenciája, ha megtalálta.
/// @throws std::out_of_range - Ha a keresett ügyfél nem található.
Ugyfel& SzervizNyilvantartoRendszer::keresUgyfel(const std::string& n) {
	for (auto it = ugyfelek.begin(); it != ugyfelek.end(); ++it) {
		if (it->getNev() == n) {
			return *it;  // Az iterált elem referenciája
		}
	}
	throw std::out_of_range("A keresett ugyfel nincs rendszerben! (keresUgyfel)");
}

/// Ügyfél létezésének ellenőrzése név alapján.
/// @param n - A keresett ügyfél neve (teljes egyezés).
/// @return - True, ha az ügyfél megtalálható a rendszerben, false egyébként.
bool SzervizNyilvantartoRendszer::vanUgyfel(const std::string& n) const {
	for (const auto& ugyfel : ugyfelek) {
		if (ugyfel.getNev() == n) {
			return true;
		}
	}
	return false;
}


/*-------------------------------------------
			Fontos tagműveletek
-------------------------------------------*/
/// Egy végzett szervizművelet rögzítése adott autóhoz.
/// @param r - Az autó rendszáma.
/// @param m - A végzett szervizművelet.
/// @throws std::out_of_range - Ha az autó nem található.
void SzervizNyilvantartoRendszer::rogzitesVegzettMuvelet(const std::string& r, const VegzettMuvelet& m) {
	for (auto& autoObj : autok) {
		if (autoObj.getRendszam() == r) {
			VegzettMuvelet* ujMuvelet = m.clone();
			autoObj.addVegzettSzerviz(ujMuvelet);
			return;
		}
	}
	throw std::out_of_range("A keresett auto nincs rendszerben, igy nem rogzitheto uj szervizmuvelet! (rogzitesVegzettMuvelet)");
}

/// Lekérdezi az adott autóhoz tartozó szervizműveleteket.
/// @param r - Az autó rendszáma.
void SzervizNyilvantartoRendszer::lekeroVegzettMuvelet(std::ostream& os, const std::string& r) const {
	for (const auto& autoObj : autok) {
		if (autoObj.getRendszam() == r) {
			const auto& muveletek = autoObj.getSzervizMuveletek();
			for (const auto& muvelet : muveletek) {
				muvelet->kiir(os);
			}
			return;
		}
	}
	throw std::out_of_range("A keresett auto nincs rendszerben, igy nem kerdezheto le a hozza tartozo szervizmuveleteket! (lekeroVegzettMuvelet)");
}

/// Figyelmeztetéseket generál az autó állapota alapján.
/// @param a - Az autó példány.
void SzervizNyilvantartoRendszer::figyelmeztetesek(std::ostream& os, const Auto& a) const {
	for (const auto& autoObj : autok) {
		if (autoObj == a) {
			const auto& muveletek = autoObj.getSzervizMuveletek();
			if (muveletek.empty()) {
				os << "Figyelmeztetes: A " << a.getRendszam()
					<< " rendszamu autohoz nincsenek rogzitett szervizmuveletek!" << std::endl;
				return;
			}

			// Az utolsó szervizművelet:
			VegzettMuvelet* utolso = muveletek.back();

			// Dátum alapú figyelmeztetés
			if (utolso->getDatum().elteltNap(Datum(2025, 4, 14)) > (365 * 2)) { // Több mint 2 éve
				os << "Figyelmeztetes: A " << a.getRendszam()
					<< " rendszamu auto muszaki vizsgaja lejart! (Utolso vizsga: "
					<< utolso->getDatum() << ")" << std::endl;
			}

			// Km alapú figyelmeztetés
			int elteltKm = autoObj.getKmOra() - utolso->getAktKmOra();
			if (elteltKm > 10000) {
				os << "Figyelmeztetes: A " << a.getRendszam()
					<< " rendszamu auto szervizelese esedekes! (Utolso szerviz ota "
					<< elteltKm << " km telt el)" << std::endl;
			}

			return;
		}
	}

	throw std::out_of_range("A keresett auto nincs rendszerben, igy nem kaphat figyelmeztetest sem! (figyelmeztetesek)");
}



/*-------------------------------------------
		 Fájlkezelő tagfüggvények
-------------------------------------------*/
/// Lecseréli a szövegben található aláhúzásjeleket (_) szóközökre.
/// @param str - A bemeneti string, amelyet formázni szeretnénk.
/// @return - std::string
static std::string trim(const std::string& str) {
	std::string result;
	for (char c : str) {
		if (c == '_') result += ' ';
		else result += c;
	}
	return result;
}

/// Lecseréli a szövegben található szóközjeleket ("_") aláhúzásra.
/// @param str - A bemeneti string, amelyet formázni szeretnénk.
/// @return - std::string
static std::string reverse_trim(const std::string& str) {
	std::string result;
	for (char c : str) {
		if (c == ' ') result += '_';
		else result += c;
	}
	return result;
}

/// Rendszeradatok betöltése fájlból.
/// @param f - A forrásfájl neve.
void SzervizNyilvantartoRendszer::betoltesFajlbol(const std::string& f) {
	std::ifstream fp(f);
	if (!fp.is_open()) throw std::runtime_error("Nem sikerult megnyitni a fajlt! (betoltesFajlbol)");

	/* --- std::string.find() ---
	   - Megkeresi egy adott részszöveg (karakter vagy string) első előfordulásának helyét egy másik stringben.
	   - Ha nem találja meg:A find() visszaadja a speciális értéket: std::string::npos
	*/
	bool ugyfelFajl = f.find("_ufl.txt") != std::string::npos; // A std::string::npos egy speciális konstans érték, amit a C++ std::string típus használ arra, hogy jelezze: valamit nem talált meg.
	bool autoFajl = f.find("_auo.txt") != std::string::npos;
	if (!ugyfelFajl && !autoFajl) throw std::invalid_argument("Ismeretlen fajlformatum! (betoltesFajlbol)");

	std::string sor;
	/* --- std::getline() ---
	   - Sor beolvasása szövegből (akár fájlból, akár más streamből).
	   - Megadott elválasztó karakterig olvas('\n' az alapértelmezett), de lehet mást is adni
	*/
	while (std::getline(fp, sor)) {
		if (sor.empty()) continue;

		if (ugyfelFajl) {
			std::istringstream iss(sor);
			std::string nev, tel, email;

			std::getline(iss, nev, '-');
			std::getline(iss, tel, '-');
			std::getline(iss, email);

			// Azokat a mezőket, ahol alulvonás("_") karaktert használtunk szóköz helyett, visszaalakítjuk szóközökké(" ") a megjelenés egységesítése érdekében.
			nev = trim(nev);
			tel = trim(tel);

			ugyfelek.push_back(Ugyfel(nev, tel, email));
		}
		else if (autoFajl) {
			std::string rendszamStr, markaStr, tipusStr, kmOraStr, datumStr, muveletekStr, tulajNevStr;
			std::istringstream iss(sor);
			std::getline(iss, rendszamStr, '-');
			std::getline(iss, markaStr, '-');
			std::getline(iss, tipusStr, '-');
			std::getline(iss, kmOraStr, '-');
			std::getline(iss, datumStr, '-');

			std::string muveletekTulajStr;
			std::getline(iss, muveletekTulajStr);

			// Az utolsó '-' jel alapján vágjuk ketté: muveletekStr - tulajNev
			size_t utolsoKotojelHelye = muveletekTulajStr.rfind('-');
			if (utolsoKotojelHelye == std::string::npos)
				throw std::runtime_error("Hibas sorformatum, nem talalhato tulajdonos neve!");

			muveletekStr = muveletekTulajStr.substr(0, utolsoKotojelHelye);
			tulajNevStr = muveletekTulajStr.substr(utolsoKotojelHelye + 1);

			// Azokat a mezőket, ahol alulvonás("_") karaktert használtunk szóköz helyett, visszaalakítjuk szóközökké(" ") a megjelenés egységesítése érdekében.
			markaStr = trim(markaStr);
			tipusStr = trim(tipusStr);
			muveletekStr = trim(muveletekStr);
			tulajNevStr = trim(tulajNevStr);
			int kmOra = std::stoi(kmOraStr);
			Datum uzembeHelyezes = Datum::parseFromString(datumStr);

			Vector<VegzettMuvelet*> szervizLista;
			if (muveletekStr != "nincs") {
				std::stringstream muveletTempStream(muveletekStr);
				std::string muveletElem;

				while (std::getline(muveletTempStream, muveletElem, ';')) {
					muveletElem = trim(muveletElem);
					if (muveletElem.empty()) continue;

					char tipus = muveletElem[0];
					std::string extraStr; // deklaráljuk itt, de értéket csak akkor adunk, ha kell
					std::string leirasStr, datumStr, arStr, kmStr;

					std::string tartalomStr = muveletElem.substr(2);
					std::stringstream adatSS(tartalomStr);
					std::getline(adatSS, leirasStr, ',');
					std::getline(adatSS, datumStr, ',');
					std::getline(adatSS, arStr, ',');
					std::getline(adatSS, kmStr, ',');

					if (tipus == 'V') {
						std::getline(adatSS, extraStr); // csak akkor olvassuk be, ha van ilyen mező
					}

					leirasStr = trim(leirasStr);
					extraStr = trim(extraStr);
					Datum datum = Datum::parseFromString(datumStr);
					int ar = std::stoi(arStr);
					int km = std::stoi(kmStr);

					if (tipus == 'J') {
						szervizLista.push_back(new Javitas(leirasStr, datum, ar, km));
					} else if (tipus == 'K') {
						szervizLista.push_back(new Karbantartas(leirasStr, datum, ar, km));
					} else if (tipus == 'V') {
						bool sikeresE = extraStr == "sikeres";
						szervizLista.push_back(new Vizsga(leirasStr, datum, ar, km, sikeresE));
					}
				}
			}
			if (vanAuto(tulajNevStr)) {
				Ugyfel& tulajStr = keresUgyfel(tulajNevStr);
				autok.push_back(Auto(rendszamStr, markaStr, tipusStr, kmOra, uzembeHelyezes, szervizLista, &tulajStr));
			} else {
				Ugyfel backUgyfel(tulajNevStr, "", "");
				autok.push_back(Auto(rendszamStr, markaStr, tipusStr, kmOra, uzembeHelyezes, szervizLista, &backUgyfel));
			}	
		}
	}
	fp.close();
}

/// Az aktuális rendszeradatok mentése fájlba.
/// @param f - A célfájl neve.
void SzervizNyilvantartoRendszer::mentesFajlba(const std::string& f) const {
	std::ofstream fp(f);
	if (!fp.is_open()) throw std::runtime_error("Nem sikerult megnyitni a fajlt! (mentesFajlba)");

	bool ugyfelFajl = f.find("_ufl.txt") != std::string::npos;
	bool autoFajl = f.find("_auo.txt") != std::string::npos;
	if (!ugyfelFajl && !autoFajl) throw std::invalid_argument("Ismeretlen fajlformatum! (mentesFajlba)");

	if (ugyfelFajl) {
		for (const auto& ugyfelObj : ugyfelek) {
			fp << reverse_trim(ugyfelObj.getNev()) << "-"
				<< reverse_trim(ugyfelObj.getTelefonszam()) << "-"
				<< ugyfelObj.getEmail() << '\n';
		}
	} else if (autoFajl) {
		for (const auto& autoObj : autok) {
			fp << autoObj.getRendszam() << "-"
				<< reverse_trim(autoObj.getMarka()) << "-"
				<< reverse_trim(autoObj.getTipus()) << "-"
				<< autoObj.getKmOra() << "-"
				<< autoObj.getUzembeHelyezes().toString() << "-";

			const Vector<VegzettMuvelet*> muveletek = autoObj.getSzervizMuveletek();
			if (muveletek.empty()) {
				fp << "nincs";
			} else {
				for (size_t i = 0; i < muveletek.size(); i++) {
					const VegzettMuvelet* m = muveletek[i];
					std::string tipusBetu;

					if (dynamic_cast<const Javitas*>(m)) tipusBetu = "J";
					else if (dynamic_cast<const Karbantartas*>(m)) tipusBetu = "K";
					else if (dynamic_cast<const Vizsga*>(m)) tipusBetu = "V";
					else throw std::runtime_error("Ismeretlen muvelet tipus a mentesFajlba fuggvenyben! (mentesFajlba)");

					fp << tipusBetu << " "
						<< reverse_trim(m->getMuvelet()) << ","
						<< m->getDatum().toString() << ","
						<< m->getAr() << ","
						<< m->getAktKmOra();

					if (const auto* vizsga = dynamic_cast<const Vizsga*>(m)) {
						fp << "," << (vizsga->getSikeres() ? "sikeres" : "sikertelen");
					}

					if (i < muveletek.size() - 1) fp << ";";
				}
			}

			// Tulajdonos ellenőrzés
			if (autoObj.getTulajdonos() == nullptr) {
				throw std::runtime_error("Auto tulajdonosa nullptr! Hibas adatstruktura. (mentesFajlba)");
			}

			fp << "-" << reverse_trim(autoObj.getTulajdonos()->getNev()) << '\n';
		}
	}

	fp.close();
}
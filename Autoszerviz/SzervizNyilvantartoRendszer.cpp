/**
*   \file SzervizNyilvantartoRendszer.cpp
*   A SzervizNyilvantartoRendszer osztály tagfüggvényeinek megvalósítása.
*/

#include "Memtrace.h"

#include <fstream>
#include <sstream>
#include <cctype>

#include "SzervizNyilvantartoRendszer.h"
#include "Auto.h"
#include "Ugyfel.h"
#include "VegzettMuvelet.h"
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

/// Visszaadja az összes auto objektumot (const változat).
/// @return - Egy const Vector<Auto> példány, amely az összes jelenleg nyilvántartott autott tartalmazza.
const Vector<Auto>& SzervizNyilvantartoRendszer::getAutok() const {
	return autok;
}

/// Visszaadja az összes ügyfél objektumot.
/// @return - Egy Vector<Ugyfel> példány, amely az összes jelenleg nyilvántartott ügyfelet tartalmazza.
Vector<Ugyfel> SzervizNyilvantartoRendszer::getUgyfelek() {
	return ugyfelek;
}

/// Visszaadja az összes ügyfél objektumot (const változat).
/// @return - Egy const Vector<Ugyfel> példány, amely az összes jelenleg nyilvántartott ügyfelet tartalmazza.
const Vector<Ugyfel>& SzervizNyilvantartoRendszer::getUgyfelek() const {
	return ugyfelek;
}



/*-------------------------------------------
				Bővítő tagfüggvények
-------------------------------------------*/
/// Új autó hozzáadása az adatbázishoz.
/// @param a - Az új autó példány.
/// @return - True, ha az autó sikeresen hozzáadva, false, ha már létezik.
bool SzervizNyilvantartoRendszer::ujAuto(const Auto& a) {
	if (!vanAuto(a.getRendszam())) {
		autok.push_back(a);
		return true;
	}
	return false;
}


/// Új ügyfél hozzáadása az adatbázishoz.
/// @param u - Az új ügyfél példány.
/// @return - True, ha az ügyfél sikeresen hozzáadva, false, ha már létezik.
bool SzervizNyilvantartoRendszer::ujUgyfel(const Ugyfel& u) {
	if (!vanUgyfel(u.getNev())) {
		ugyfelek.push_back(u);
		return true;
	}
	return false;
}



/*-------------------------------------------
			Frissítő tagfüggvények
-------------------------------------------*/
/// Egy autó adatainak frissítése a rendszeren belül.
/// Ha a rendszeren belül már létezik az autó (rendszám alapján), akkor az adatai frissülnek.
/// @param a - Az autó új adatai.
/// @return - True, ha az autó sikeresen frissítve lett, false, ha nem található.
bool SzervizNyilvantartoRendszer::frissitAuto(const Auto& a) {
	for (auto& autoRef : autok) {
		if (autoRef.getRendszam() == a.getRendszam()) {
			autoRef = a;
			return true;
		}
	}
	return false;
}

/// Egy ügyfél adatainak frissítése a rendszeren belül.
/// Ha a rendszeren belül már létezik az ügyfél (név alapján), akkor az adatai frissülnek.
/// @param u - Az ügyfél új adatai.
/// @return - True, ha az ügyfél sikeresen frissítve lett, false, ha nem található.
bool SzervizNyilvantartoRendszer::frissitUgyfel(const Ugyfel& u) {
	for (auto& ugyfelRef : ugyfelek) {
		if (ugyfelRef.getNev() == u.getNev()) {
			ugyfelRef = u;
			return true;
		}
	}
	return false;
}



/*-------------------------------------------
			Törlő tagfüggvények
-------------------------------------------*/
/// Egy autó törlése rendszám alapján.
/// @param r - A törlendő autó rendszáma.
/// @return - True, ha az autó törölve lett, false, ha nem található.
bool SzervizNyilvantartoRendszer::torolAuto(const std::string& r) {
	for (auto it = autok.begin(); it != autok.end(); it++) {
		if (it->getRendszam() == r) {
			autok.erase(it);
			return true;
		}
	}
	return false;
}

/// Egy ügyfél törlése név alapján.
/// @param n - A törlendő ügyfél neve.
/// @return - True, ha az ügyfél törölve lett, false, ha nem található.
bool SzervizNyilvantartoRendszer::torolUgyfel(const std::string& n) {
	bool torolve = false;

	// Töröljük az ügyfélhez tartozó autókat
	for (auto jt = autok.begin(); jt != autok.end(); ) {
		if (jt->getTulajdonos()->getNev() == n) {
			jt = autok.erase(jt);
			torolve = true;
		}
		else {
			++jt;
		}
	}

	// Töröljük az ügyfelet
	for (auto it = ugyfelek.begin(); it != ugyfelek.end(); ) {
		if (it->getNev() == n) {
			it = ugyfelek.erase(it);
			torolve = true;
		}
		else {
			it++;
		}
	}

	return torolve;
}

/// Egy adott rendszámú autóhoz tartozó szervizművelet törlése a megadott dátum alapján.
/// @param r - Az autó rendszáma.
/// @param d - A törlendő művelet dátuma.
/// @return - True, ha a művelet sikeresen törölve lett, false, ha az autó vagy a megadott dátumú művelet nem található.
bool SzervizNyilvantartoRendszer::torolMuvelet(const std::string& r, const Datum& d) {
	for (auto& autoObj : autok) {
		if (autoObj.getRendszam() == r) {
			auto& muveletek = autoObj.getSzervizMuveletek();
			for (size_t i = 0; i < muveletek.size(); ++i) {
				if (muveletek[i]->getDatum() == d) {
					autoObj.torolVegzettSzerviz(i);
					return true;
				}
			}
			return false; // Az autó létezik, de nincs ilyen dátumú művelet
		}
	}
	return false; // Nincs ilyen rendszámú autó
}



/*-------------------------------------------
		  Kereső tagfüggvények
-------------------------------------------*/
/// Autó keresése rendszám alapján.
/// @param r - A keresett autó rendszáma (teljes egyezés).
/// @return - Az autó referenciája, ha megtalálta.
/// @throw - Hibát dob ha nem talált meg a kerest rendszámu autot
Auto& SzervizNyilvantartoRendszer::keresAuto(const std::string& r) {
	for (auto it = autok.begin(); it != autok.end(); it++) {
		if (it->getRendszam() == r) {
			return *it;
		}
	}
	throw std::runtime_error("Nincs ilyen rendszamu auto!");
}

/// Ügyfél keresése név alapján.
/// @param n - A keresett ügyfél neve (teljes egyezés).
/// @return - Az ügyfél referenciája, ha megtalálta.
/// @throw - Hibát dob ha nem talált meg a kerest nevű embert
Ugyfel& SzervizNyilvantartoRendszer::keresUgyfel(const std::string& n) {
	for (auto it = ugyfelek.begin(); it != ugyfelek.end(); it++) {
		if (it->getNev() == n) {
			return *it;
		}
	}
	throw std::runtime_error("Nincs ilyen nevu ugyfel!");
}

/// Auto létezésének ellenőrzése név alapján.
/// @param r - A keresett autó rendszáma (teljes egyezés).
/// @return - True, ha az auto megtalálható a rendszerben, false egyébként.
bool SzervizNyilvantartoRendszer::vanAuto(const std::string& r) const {
	for (const auto& a : autok)
		if (a.getRendszam() == r)
			return true;
	return false;
}

/// Ügyfél létezésének ellenőrzése név alapján.
/// @param n - A keresett ügyfél neve (teljes egyezés).
/// @return - True, ha az ügyfél megtalálható a rendszerben, false egyébként.
bool SzervizNyilvantartoRendszer::vanUgyfel(const std::string& n) const {
	for (const auto& u : ugyfelek)
		if (u.getNev() == n)
			return true;
	return false;
}



/*-------------------------------------------
			Fontos tagműveletek
-------------------------------------------*/
/// Egy végzett szervizművelet rögzítése adott autóhoz.
/// @param r - Az autó rendszáma.
/// @param m - A végzett szervizművelet.
/// @return - True, ha a művelet sikeresen rögzítve lett, false, ha az autó nem található.
bool SzervizNyilvantartoRendszer::rogzitesVegzettMuvelet(const std::string& r, const VegzettMuvelet& m) {
	for (auto& autoObj : autok) {
		if (autoObj.getRendszam() == r) {
			VegzettMuvelet* ujMuvelet = m.clone();
			autoObj.addVegzettSzerviz(ujMuvelet);
			return true;
		}
	}
	return false;
}

/// Lekérdezi az adott autóhoz tartozó szervizműveleteket.ű
/// @param os - A kimeneti adatfolyam.
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
}

/// Figyelmeztetéseket generál az autó állapota alapján.
/// @param os - A kimeneti adatfolyam.
/// @param a - Az autó példány.
void SzervizNyilvantartoRendszer::figyelmeztetesek(std::ostream& os, const Auto& a) const {
	int hanyDBHiba = 0; // Hiba számláló
	for (const auto& autoObj : autok) {
		if (autoObj == a) {
			const auto& muveletek = autoObj.getSzervizMuveletek();
			if (muveletek.empty()) {
				os << "\tA " << a.getRendszam() << " rendszamu autohoz nincsenek rogzitett szervizmuveletek!" << std::endl;
				return;
			}

			// Az utolsó szervizművelet:
			VegzettMuvelet* utolso = muveletek.back();

			// Dátum alapú figyelmeztetés
			if (utolso->getDatum().elteltNap(Datum(2025, 4, 14)) > (365 * 2)) { // Több mint 2 éve
				os << "\tA " << a.getRendszam() << " rendszamu auto muszaki vizsgaja lejart! (Utolso vizsga: " << utolso->getDatum() << ")" << std::endl;
				hanyDBHiba++;
			}

			// Km alapú figyelmeztetés
			int elteltKm = autoObj.getKmOra() - utolso->getAktKmOra();
			if (elteltKm > 10000) {
				os << "\tA " << a.getRendszam() << " rendszamu auto szervizelesre esedekes! (Utolso szerviz ota "	<< elteltKm << " km telt el)" << std::endl;
				hanyDBHiba++;
			}

			if (hanyDBHiba == 0) {
				os << "\tNincsenek figyelmeztetesek!" << std::endl;
			}
		}
	}
}



/*-------------------------------------------
		 Fájlkezelő tagfüggvények
-------------------------------------------*/
/// Lecseréli a szövegben található aláhúzásjeleket (_) szóközökre.
/// A függvény static kulcsszóval van ellátva, mert csak a jelenlegi fordítási egységen (fájlban) belül használjuk, így nem szükséges kívülről elérhetővé tenni.
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
/// A függvény static kulcsszóval van ellátva, mert csak a jelenlegi fordítási egységen (fájlban) belül használjuk, így nem szükséges kívülről elérhetővé tenni.
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
			std::string nevStr, telStr, emailStr;

			std::getline(iss, nevStr, '-');
			std::getline(iss, telStr, '-');
			std::getline(iss, emailStr);

			nevStr = trim(nevStr);
			telStr = trim(telStr);

			if (vanUgyfel(nevStr)) {
				// Frissítjük az ügyfél adatait
				Ugyfel& letezoUgyfel = keresUgyfel(nevStr);
				letezoUgyfel.setTel(telStr);
				letezoUgyfel.setEmail(emailStr);
			}
			else {
				// Új ügyfél hozzáadása
				ugyfelek.push_back(Ugyfel(nevStr, telStr, emailStr));
			}
		} else if (autoFajl) {
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
				throw std::runtime_error("Hibas sorformatum, nem talalhato tulajdonos neve! (betoltesFajlbol)");

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

			if (vanUgyfel(tulajNevStr)) {
				Ugyfel& tulajStr = keresUgyfel(tulajNevStr);
				autok.push_back(Auto(rendszamStr, markaStr, tipusStr, kmOra, uzembeHelyezes, szervizLista, &tulajStr));
			}
			else {
				// tulajdonos még nincs, létrehozás + beszúrás
				ugyfelek.push_back(Ugyfel(tulajNevStr, "", ""));
				Ugyfel& ujTulaj = ugyfelek.back();
				autok.push_back(Auto(rendszamStr, markaStr, tipusStr, kmOra, uzembeHelyezes, szervizLista, &ujTulaj));
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

					fp << tipusBetu << ":"
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

/**
 * Fontos tudnivalók a fájlkezelő függvények működéséről:
 *
 * A fájlokban tárolt adatoknak pontosan meg kell felelniük az előre definiált szabályoknak, melyek a következők:
 *
 * Fájlnevek:
 *   - Ügyfél típusú fájl esetén a fájlnévnek tartalmaznia kell az "_ufl.txt" végződést.
 *   - Autó típusú fájl esetén a fájlnévnek "_auo.txt" végződést kell tartalmaznia.
 *
 * Fájlstruktúra:
 *   - Ügyfelek esetén a sorok formátuma: "ugyfel_neve-telefonszam-email"
 *   - Autók esetén a formátum: "rendszam-marka-tipus-kmora-uzembe_helyezes_datuma-szervizmuveletek-tulajdonos_neve"
 *
 * Megjegyzések az autós adatokhoz:
 *   - A "szervizmuveletek" mezőben szerepelhet:
 *     - a "nincs" szó, ha nem történt szervizelés,
 *     - vagy egy felsorolás az elvégzett műveletekről, az alábbi formátumban:
 *       "tipus,leiras,datum,ar,kmora,extra;"
 *       ahol:
 *         - tipus: 'J' (javítás), 'K' (karbantartás), vagy 'V' (vizsga),
 *         - az "extra" mező kizárólag vizsga esetén tartalmazza a „sikeres” vagy „sikertelen” értéket.
 *		   - a mezők közötti elválasztó karakter a vessző (,) és a végén pontosvessző (;) ha van további szervizmuvelet.
 *		   - azt is elvárjuk, hogy a kmora értékek mindig pozitív egész számok legyenek amik minden esettben <= mint az azt megelőző "szervizmuvelet kmora" értéke
 *
 * További szabály:
 *   - Amennyiben az autóhoz tartozó tulajdonos még nem szerepel a rendszerben, az új ügyfelet automatikusan felvesszük, viszont a telefonszám és e-mail mezői üresen maradnak.
 */
/**
*   \file Auto.cpp
*   Az autó osztály tagfüggvényeinek megvalósítása.
*/

#include <string>

#include "Memtrace.h"

#include "Auto.h"
#include "Datum.h"
#include "Ugyfel.h"
#include "Vector.hpp"
#include "VegzettMuvelet.h"

/*-------------------------------------------
        Konstruktorok és destruktor
-------------------------------------------*/
/// Alapértelmezett konstruktor.
Auto::Auto() : rendszam(""), marka(""), tipus(""), kmOra(0), uzembeHelyezes(Datum()), tulajdonos(nullptr) {}

/// Paraméteres konstruktor.  
/// @param r - Az autó rendszáma  
/// @param m - Az autó márkája  
/// @param t - Az autó típusa  
/// @param k - A kilométeróra állása  
Auto::Auto(const std::string& r, const std::string& m, const std::string& t, int k)
    : rendszam(r), marka(m), tipus(t), kmOra(k), uzembeHelyezes(), tulajdonos(nullptr) {
}

/// Paraméteres konstruktor.
/// @param r - Az autó rendszáma
/// @param m - Az autó márkája
/// @param t - Az autó típusa
/// @param k - A kilométeróra állása
/// @param d - Az üzembe helyezés dátuma
Auto::Auto(const std::string& r, const std::string& m, const std::string& t, int k, const Datum& d, const Vector<VegzettMuvelet*>& v, Ugyfel* u)
    : rendszam(r), marka(m), tipus(t), kmOra(k), uzembeHelyezes(d), tulajdonos(u) {
    for (size_t i = 0; i < v.size(); i++) {
        vegzettSzervizMuveletek.push_back(v.at(i)->clone());
    }
}


/// Másoló konstruktor.
/// @param a - másolandó Auto objektum
Auto::Auto(const Auto& a) : rendszam(a.rendszam), marka(a.marka), tipus(a.tipus), kmOra(a.kmOra), uzembeHelyezes(a.uzembeHelyezes), tulajdonos(a.tulajdonos) {
    for (size_t i = 0; i < a.vegzettSzervizMuveletek.size(); i++) {
        vegzettSzervizMuveletek.push_back(a.vegzettSzervizMuveletek[i]->clone());
    }
}

/// Destruktor
Auto::~Auto() {
    for (size_t i = 0; i < vegzettSzervizMuveletek.size(); i++)
        delete vegzettSzervizMuveletek[i]; // felszabadítjuk a dinamikusan foglalt szervizmûveletet
    vegzettSzervizMuveletek.clear(); // nem kötelezõ, de szép
}



/*-------------------------------------------
                Operátorok
-------------------------------------------*/
/// Értékadó operátor.
/// @param a - másolandó Auto objektum
/// @return - Az aktuális objektum referenciája
Auto& Auto::operator=(const Auto& a) {
    if (this != &a) {
        rendszam = a.rendszam;
        marka = a.marka;
        tipus = a.tipus;
        kmOra = a.kmOra;
        uzembeHelyezes = a.uzembeHelyezes;
        tulajdonos = a.tulajdonos;

        for (size_t i = 0; i < vegzettSzervizMuveletek.size(); i++) {
            delete vegzettSzervizMuveletek.at(i);
        }
        vegzettSzervizMuveletek.clear();

        for (size_t i = 0; i < a.vegzettSzervizMuveletek.size(); i++) {
            vegzettSzervizMuveletek.push_back(a.vegzettSzervizMuveletek[i]->clone());
        }
    }
    return *this;
}

/// Egyenlõség operátor túlterhelése az Auto osztályhoz.
/// @param a - Az összehasonlítandó Auto objektum.
/// @return - true, ha az objektumok megegyeznek, különben false.
bool Auto::operator==(const Auto& a) const {
    return rendszam == a.rendszam &&
        marka == a.marka &&
        tipus == a.tipus &&
        kmOra == a.kmOra &&
        uzembeHelyezes == a.uzembeHelyezes &&
        tulajdonos->getNev() == a.tulajdonos->getNev() &&
        tulajdonos->getTelefonszam() == a.tulajdonos->getTelefonszam() &&
        tulajdonos->getEmail() == a.tulajdonos->getEmail();
}



/*-------------------------------------------
                 Getterek
-------------------------------------------*/
/// Visszaadja az autó rendszámát.
/// @return - Rendszám
const std::string& Auto::getRendszam() const {
   return rendszam;
}

/// Visszaadja az autó márkáját.
/// @return - Márka.
const std::string& Auto::getMarka() const {
	return marka;
}

/// Visszaadja az autó típusát.
/// @return - Típus.
const std::string& Auto::getTipus() const {
	return tipus;
}

/// Visszaadja a kilométeróra aktuális értékét.
/// @return - Km óra értéke.
const int Auto::getKmOra() const {
	return kmOra;
}

/// Visszaadja az üzembe helyezés dátumát.
/// @return - Dátum.
const Datum& Auto::getUzembeHelyezes() const {
	return uzembeHelyezes;
}

/// Visszaadja az autóhoz tartozó szervizmûveletek listáját.
/// @return - Szervizmûveletek vektora.
Vector<VegzettMuvelet*>& Auto::getSzervizMuveletek() {
	return vegzettSzervizMuveletek;
}

/// Visszaadja az autóhoz tartozó szervizmûveletek listáját (const változat).
/// @return - Szervizmûveletek vektora.
const Vector<VegzettMuvelet*>& Auto::getSzervizMuveletek() const {
    return vegzettSzervizMuveletek;
}

// Visszaadja az autó tulajdonosát.
/// @return - Az autó tulajdonosa.
Ugyfel* Auto::getTulajdonos() {
    return tulajdonos;
}

// Visszaadja az autó tulajdonosát (const változat).
/// @return - Az autó tulajdonosa.
const Ugyfel* Auto::getTulajdonos() const {
    return tulajdonos;
}



/*-------------------------------------------
                Setterek
-------------------------------------------*/
/// Beállítja az autó rendszámát.
/// @param r - Az új rendszám
void Auto::setRendszam(const std::string& r) {
    rendszam = r;
}

/// Beállítja a kilométeróra értékét.
/// @param k - Az új km óra érték
void Auto::setKmOra(int k) {
    if (k >= kmOra) kmOra = k;
}

/// Beállítja a tulajdonost.
/// @param u - Az új tulajdonos.
void Auto::setTulajdonos(Ugyfel* u) {
    tulajdonos = u;
}



/*-------------------------------------------
            Fontos tagmûveletek
-------------------------------------------*/
/// Másoló függvény (virtuális, tisztán absztrakt)
/// @return - új példány
Auto* Auto::clone() const {
    return new Auto(*this);
}

/// Hozzáad egy szervizmûveletet az autó szervizlistájához.
/// @param m - A hozzáadandó szervizmûvelet pointere
void Auto::addVegzettSzerviz(VegzettMuvelet* m) {
	vegzettSzervizMuveletek.push_back(m);
}

/// Törli a megadott indexû szervizmûveletet a listából.
/// @param idx - A törlendõ mûvelet pozíciója
void Auto::torolVegzettSzerviz(size_t idx) {
    if (idx < vegzettSzervizMuveletek.size()) {
        delete vegzettSzervizMuveletek.at(idx);
        vegzettSzervizMuveletek.erase(vegzettSzervizMuveletek.begin() + idx);
    }
}

/// Kiírja az autó adatait és szervizmûveleteit az adott ostream-re.
/// @param os - A kimeneti adatfolyam
/// @return - Az ostream referenciája (láncoláshoz)
void Auto::kiir(std::ostream& os) const {
    os << "\tRendszam: " << rendszam << "\n"
        << "\tMarka: " << marka << "\n"
        << "\tTipus: " << tipus << "\n"
        << "\tKm ora: " << kmOra << "\n"
        << "\tUzembe helyezes: " << uzembeHelyezes << "\n"
        << "\tTulajdonos: " << tulajdonos->getNev() << "\n"
        << "\tSzervizmuveletek:" << (vegzettSzervizMuveletek.size() == 0 ? "nincs" : "") << "\n";

    for (size_t i = 0; i < vegzettSzervizMuveletek.size(); i++) {
        vegzettSzervizMuveletek.at(i)->kiir(os);
    }

    os << std::endl;
}



/*-------------------------------------------
            Globális operátorok
-------------------------------------------*/
/// Kimeneti operátor Datum objektumhoz
/// @param os - kimeneti stream
/// @param a - kiírandó Auto objektum
/// @return - módosított kimeneti stream
std::ostream& operator<<(std::ostream& os, const Auto& a) {
	a.kiir(os);
    return os;
}
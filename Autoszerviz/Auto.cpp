/**
*   \file Auto.cpp
*   Az aut� oszt�ly tagf�ggv�nyeinek megval�s�t�sa.
*/

#include <string>

#include "Memtrace.h"

#include "Auto.h"
#include "Datum.h"
#include "Ugyfel.h"
#include "Vector.hpp"
#include "VegzettMuvelet.h"

/*-------------------------------------------
        Konstruktorok �s destruktor
-------------------------------------------*/
/// Alap�rtelmezett konstruktor.
Auto::Auto() : rendszam(""), marka(""), tipus(""), kmOra(0), uzembeHelyezes(Datum()), tulajdonos(nullptr) {}

/// Param�teres konstruktor.  
/// @param r - Az aut� rendsz�ma  
/// @param m - Az aut� m�rk�ja  
/// @param t - Az aut� t�pusa  
/// @param k - A kilom�ter�ra �ll�sa  
Auto::Auto(const std::string& r, const std::string& m, const std::string& t, int k)
    : rendszam(r), marka(m), tipus(t), kmOra(k), uzembeHelyezes(), tulajdonos(nullptr) {
}

/// Param�teres konstruktor.
/// @param r - Az aut� rendsz�ma
/// @param m - Az aut� m�rk�ja
/// @param t - Az aut� t�pusa
/// @param k - A kilom�ter�ra �ll�sa
/// @param d - Az �zembe helyez�s d�tuma
Auto::Auto(const std::string& r, const std::string& m, const std::string& t, int k, const Datum& d, const Vector<VegzettMuvelet*>& v, Ugyfel* u)
    : rendszam(r), marka(m), tipus(t), kmOra(k), uzembeHelyezes(d), tulajdonos(u) {
    for (size_t i = 0; i < v.size(); i++) {
        vegzettSzervizMuveletek.push_back(v.at(i)->clone());
    }
}


/// M�sol� konstruktor.
/// @param a - m�soland� Auto objektum
Auto::Auto(const Auto& a) : rendszam(a.rendszam), marka(a.marka), tipus(a.tipus), kmOra(a.kmOra), uzembeHelyezes(a.uzembeHelyezes), tulajdonos(a.tulajdonos) {
    for (size_t i = 0; i < a.vegzettSzervizMuveletek.size(); i++) {
        vegzettSzervizMuveletek.push_back(a.vegzettSzervizMuveletek[i]->clone());
    }
}

/// Destruktor
Auto::~Auto() {
    for (size_t i = 0; i < vegzettSzervizMuveletek.size(); i++)
        delete vegzettSzervizMuveletek[i]; // felszabad�tjuk a dinamikusan foglalt szervizm�veletet
    vegzettSzervizMuveletek.clear(); // nem k�telez�, de sz�p
}



/*-------------------------------------------
                Oper�torok
-------------------------------------------*/
/// �rt�kad� oper�tor.
/// @param a - m�soland� Auto objektum
/// @return - Az aktu�lis objektum referenci�ja
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

/// Egyenl�s�g oper�tor t�lterhel�se az Auto oszt�lyhoz.
/// @param a - Az �sszehasonl�tand� Auto objektum.
/// @return - true, ha az objektumok megegyeznek, k�l�nben false.
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
/// Visszaadja az aut� rendsz�m�t.
/// @return - Rendsz�m
const std::string& Auto::getRendszam() const {
   return rendszam;
}

/// Visszaadja az aut� m�rk�j�t.
/// @return - M�rka.
const std::string& Auto::getMarka() const {
	return marka;
}

/// Visszaadja az aut� t�pus�t.
/// @return - T�pus.
const std::string& Auto::getTipus() const {
	return tipus;
}

/// Visszaadja a kilom�ter�ra aktu�lis �rt�k�t.
/// @return - Km �ra �rt�ke.
const int Auto::getKmOra() const {
	return kmOra;
}

/// Visszaadja az �zembe helyez�s d�tum�t.
/// @return - D�tum.
const Datum& Auto::getUzembeHelyezes() const {
	return uzembeHelyezes;
}

/// Visszaadja az aut�hoz tartoz� szervizm�veletek list�j�t.
/// @return - Szervizm�veletek vektora.
Vector<VegzettMuvelet*>& Auto::getSzervizMuveletek() {
	return vegzettSzervizMuveletek;
}

/// Visszaadja az aut�hoz tartoz� szervizm�veletek list�j�t (const v�ltozat).
/// @return - Szervizm�veletek vektora.
const Vector<VegzettMuvelet*>& Auto::getSzervizMuveletek() const {
    return vegzettSzervizMuveletek;
}

// Visszaadja az aut� tulajdonos�t.
/// @return - Az aut� tulajdonosa.
Ugyfel* Auto::getTulajdonos() {
    return tulajdonos;
}

// Visszaadja az aut� tulajdonos�t (const v�ltozat).
/// @return - Az aut� tulajdonosa.
const Ugyfel* Auto::getTulajdonos() const {
    return tulajdonos;
}



/*-------------------------------------------
                Setterek
-------------------------------------------*/
/// Be�ll�tja az aut� rendsz�m�t.
/// @param r - Az �j rendsz�m
void Auto::setRendszam(const std::string& r) {
    rendszam = r;
}

/// Be�ll�tja a kilom�ter�ra �rt�k�t.
/// @param k - Az �j km �ra �rt�k
void Auto::setKmOra(int k) {
    if (k >= kmOra) kmOra = k;
}

/// Be�ll�tja a tulajdonost.
/// @param u - Az �j tulajdonos.
void Auto::setTulajdonos(Ugyfel* u) {
    tulajdonos = u;
}



/*-------------------------------------------
            Fontos tagm�veletek
-------------------------------------------*/
/// M�sol� f�ggv�ny (virtu�lis, tiszt�n absztrakt)
/// @return - �j p�ld�ny
Auto* Auto::clone() const {
    return new Auto(*this);
}

/// Hozz�ad egy szervizm�veletet az aut� szervizlist�j�hoz.
/// @param m - A hozz�adand� szervizm�velet pointere
void Auto::addVegzettSzerviz(VegzettMuvelet* m) {
	vegzettSzervizMuveletek.push_back(m);
}

/// T�rli a megadott index� szervizm�veletet a list�b�l.
/// @param idx - A t�rlend� m�velet poz�ci�ja
void Auto::torolVegzettSzerviz(size_t idx) {
    if (idx < vegzettSzervizMuveletek.size()) {
        delete vegzettSzervizMuveletek.at(idx);
        vegzettSzervizMuveletek.erase(vegzettSzervizMuveletek.begin() + idx);
    }
}

/// Ki�rja az aut� adatait �s szervizm�veleteit az adott ostream-re.
/// @param os - A kimeneti adatfolyam
/// @return - Az ostream referenci�ja (l�ncol�shoz)
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
            Glob�lis oper�torok
-------------------------------------------*/
/// Kimeneti oper�tor Datum objektumhoz
/// @param os - kimeneti stream
/// @param a - ki�rand� Auto objektum
/// @return - m�dos�tott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Auto& a) {
	a.kiir(os);
    return os;
}
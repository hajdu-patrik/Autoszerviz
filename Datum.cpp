/**
*   \file Datum.cpp
*   A datum osztály tagfüggvényeinek megvalósítása.
*/

#define MEMTRACE
#include "Memtrace.h"

#include "Datum.h"

/*-------------------------------------------
        Konstruktorok és destruktor
-------------------------------------------*/
/// Alapértelmezett konstruktor
/// 0-ra inicializálja az évet, hónapot és napot.
Datum::Datum() : ev(0), ho(0), nap(0) {}

/// Paraméteres konstruktor
/// @param e - év
/// @param h - hónap
/// @param n - nap
Datum::Datum(int e, int h, int n) : ev(e), ho(h), nap(n) {}

/// Másoló konstruktor
/// @param d - másolandó Datum objektum
Datum::Datum(const Datum& d) : ev(d.ev), ho(d.ho), nap(d.nap) {}

/// Destruktor
Datum::~Datum() {}



/*-------------------------------------------
                Operátorok
-------------------------------------------*/
/// Értékadó operátor
/// @param d - másolandó Datum objektum
/// @return - az aktuális objektum referenciája
Datum& Datum::operator=(const Datum& d) {
    if (this != &d) {
        ev = d.ev;
        ho = d.ho;
        nap = d.nap;
    }
    return *this;
}

/// Összehasonlító operátor
/// @param d - összehasonlítandó Datum objektum
/// @return - true, ha az objektumok megegyeznek, különben false.
bool Datum::operator==(const Datum& d) const {
    return ev == d.ev && ho == d.ho && nap == d.nap;
}



/*-------------------------------------------
                 Getterek
-------------------------------------------*/
/// Év lekérdezése
/// @return - év
int Datum::getEv() const { return ev; }

/// Hónap lekérdezése
/// @return - hónap
int Datum::getHo() const { return ho; }

/// Nap lekérdezése
/// @return - nap
int Datum::getNap() const { return nap; }

/// Dátum eltelt napok számának lekérdezése
/// @param d - másik Datum objektum
int Datum::elteltNap(const Datum& d) const {
    int e = d.getEv() - ev;
    int h = d.getHo() - ho;
    int n = d.getNap() - nap;
    return e * 365 + h * 30 + n;
}



/*-------------------------------------------
                Setterek
-------------------------------------------*/
/// Dátum beállítása
/// @param e - év
/// @param h - hónap
/// @param n - nap
void Datum::setDatum(int e, int h, int n) {
    ev = e;
    ho = h;
    nap = n;
}



/*-------------------------------------------
               Segédfüggvények
-------------------------------------------*/
/// Létrehoz egy Datum objektumot egy stringbõl.
/// A string formátuma: "ÉÉÉÉ.HH.NN".
/// @param str - A dátumot tartalmazó string.
/// @return - A létrehozott Datum objektum.
Datum Datum::parseFromString(const std::string& str) {
    int e, h, n;
    char dot1, dot2;
    std::istringstream iss(str);

    if (!(iss >> e >> dot1 >> h >> dot2 >> n) || dot1 != '.' || dot2 != '.')
        throw std::runtime_error("Hibas datum formatum! (parseFromString)");

    return Datum(e, h, n);
}

/// Egy Datum objektumot stringgé alakít "ÉÉÉÉ.HH.NN" formátumban.
/// @return std::string A formázott dátum szövegként.
const std::string Datum::toString() const {
    std::ostringstream oss;

    oss << std::setw(4) << std::setfill('0') << ev << "."
        << std::setw(2) << std::setfill('0') << ho << "."
        << std::setw(2) << std::setfill('0') << nap;

    return oss.str();
}




/*-------------------------------------------
            Globális operátorok
-------------------------------------------*/
/// Kimeneti operátor Datum objektumhoz
/// @param os - kimeneti stream
/// @param d - kiírandó Datum objektum
/// @return - módosított kimeneti stream
std::ostream& operator<<(std::ostream& os, const Datum& d) {
    return os << std::setw(4) << std::setfill('0') << d.getEv() << "."
        << std::setw(2) << std::setfill('0') << d.getHo() << "."
        << std::setw(2) << std::setfill('0') << d.getNap();
}
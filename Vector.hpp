#ifndef VECTOR_HPP  
#define VECTOR_HPP 

#include "Memtrace.h"

#include <stdexcept>

/// Típusjellemzõ sablon struktúra, amely meghatározza, hogy egy típus pointer-e.
/// @tparam T A vizsgált típus.
/// @note Alapértelmezetten false, azaz a típus nem pointer.
template <typename T>
struct IsPointer {
    enum { value = false };
};

/// Típusjellemzõ specializáció pointer típusokra.
/// @tparam T A típus, amelynek pointer változata a specializáció célja.
/// @note Ez a specializáció akkor aktiválódik, ha T pointer típus (pl. int*), és true-t ad vissza.
template <typename T>
struct IsPointer<T*> {
    enum { value = true };
};

/// Sablon alapú dinamikus tömbosztály, amely külön kezeli pointer és nem-pointer típusokat.
/// @tparam T A tárolt típus.
/// @tparam VECTOR_MERET A vektor kezdeti kapacitása, alapértelmezés szerint 100.
template <typename T, size_t VECTOR_MERET = 100>
class Vector {
    size_t kapacitas; ///< Az aktuálisan lefoglalt tárhely mérete.
    size_t meret;     ///< Az aktuálisan tárolt elemek száma.
    T* tomb;          ///< A dinamikusan foglalt tömb mutatója.

    /// Másoló függvény, amely delegál a típusnak megfelelõ implementációs változatra.
    /// @param src - A másolandó Vector példány.
    void copy_elements(const Vector& src) {
        copy_elements_impl(src, std::integral_constant<bool, IsPointer<T>::value>());
        /*  Itt az std::integral_constant<bool, IsPointer<T>::value>() egy típus szintû dispatcher: ha pointer típus, akkor true_type, különben false_type.
            Ez azt jelenti, hogy típus alapján kiválasztjuk, melyik copy_elements_impl() vagy delete_elements_impl() függvény hívódjon meg — tehát:
            Dispatcheles = döntéshozatal a függvényhívásról(futási vagy fordítási idõben)
        */
    }

    /// Pointer típusokra specializált másoló logika. Mély másolatot készít clone() segítségével.
    /// @param src - A forrás vektor.
    /// @param is_ptr - std::true_type jelzi, hogy pointer típusról van szó.
    void copy_elements_impl(const Vector& src, std::true_type) {
        for (size_t i = 0; i < meret; ++i)
            tomb[i] = src.tomb[i] ? src.tomb[i]->clone() : nullptr;
    }

    /// Nem-pointer típusokra specializált másoló logika. Egyszerû értékadás történik.
    /// @param src - A forrás vektor.
    /// @param is_ptr - std::false_type jelzi, hogy nem pointer típusról van szó.
    void copy_elements_impl(const Vector& src, std::false_type) {
        for (size_t i = 0; i < meret; ++i)
            tomb[i] = src.tomb[i];
    }

    /// Elemfelszabadító függvény, amely delegál a típusfüggõ implementációra.
    void delete_elements() {
        delete_elements_impl(std::integral_constant<bool, IsPointer<T>::value>());
    }

    /// Pointer típus esetén felszabadítja a mutatott objektumokat.
    /// @param is_ptr - std::true_type jelzi, hogy pointer típusról van szó.
    void delete_elements_impl(std::true_type) {
        for (size_t i = 0; i < meret; ++i)
            delete tomb[i];
    }

    /// Nem-pointer típus esetén nem végez semmilyen mûveletet.
    /// @param is_ptr - std::false_type jelzi, hogy nem pointer típusról van szó.
    void delete_elements_impl(std::false_type) {
        // Nem csinálunk semmit
    }

public:
    /// Alapértelmezett konstruktor. Inicializálja az üres vektort.
    Vector() : meret(0), kapacitas(VECTOR_MERET), tomb(new T[kapacitas]) {}

    /// Másoló konstruktor. Mély vagy sekély másolatot készít a típus alapján.
    /// @param v - A másolandó vektor példány.
    Vector(const Vector& v) : meret(v.meret), kapacitas(v.kapacitas), tomb(new T[kapacitas]) {
        copy_elements(v);
    }

    /// Destruktor.
    ~Vector() {
        delete_elements();
        delete[] tomb;
    }


    /*-------------------------------------------
                Iterátor támogatás
    -------------------------------------------*/
    /// Mutató az elsõ elemre (iterátor kezdete)
    /// @return - Pointer az elsõ elemre
    T* begin() { return tomb; }

    /// Konstans mutató az elsõ elemre (konstans iterátor kezdete)
    /// @return - Konstans pointer az elsõ elemre
    const T* begin() const { return tomb; }

    /// Mutató az utolsó elem utáni területre (iterátor vége)
    /// @return Pointer az utolsó elem utáni területre
    T* end() { return tomb + meret; }

    /// Konstans mutató az utolsó elem utáni területre (konstans iterátor vége)
    /// @return Konstans pointer az utolsó elem utáni területre
    const T* end() const { return tomb + meret; }



    /*-------------------------------------------
                    Operátorok
    -------------------------------------------*/
    /// Értékadó operátor.
    /// @param v - Másolandó vector példány
    /// @return - Az aktuális objektum referenciája
    Vector& operator=(const Vector& v) {
        if (this != &v) {
            delete_elements();
            delete[] tomb;

            meret = v.meret;
            kapacitas = v.kapacitas;
            tomb = new T[kapacitas];
            copy_elements(v);
        }
        return *this;
    }

    /// Egyenlõségvizsgáló operátor
    /// @param v - Összehasonlítandó vector
    /// @return true - ha a vektorok tartalma megegyezik
    bool operator==(const Vector& v) const {
        if (meret != v.meret) return false;
        for (size_t i = 0; i < meret; i++) {
            if (tomb[i] != v.tomb[i]) return false;
        }
        return true;
    }

    /// Indexelõ operátor
    /// @param idx - Index
    /// @return - Az adott indexû elem referenciája
    /// @note - Nincs határellenõrzés!
    T& operator[](size_t idx) { return tomb[idx]; }

    /// Konstans indexelõ operátor
    /// @param idx - Index
    /// @return - Az adott indexû elem konstans referenciája
    /// @note - Nincs határellenõrzés!
    const T& operator[](size_t idx) const { return tomb[idx]; }



    /*-------------------------------------------
        Kapacitással kapcsolatos mûveletek
    -------------------------------------------*/
    /// Visszaadja a vektorban tárolt elemek számát.
    /// @return - Az aktuális elemszám (meret)
    size_t size() const { return meret; }

    /// Visszaadja a vektor kapacitását.
    /// @return - A kapacitás (kapacitas)
    size_t capacity() const { return kapacitas; }

    /// Megvizsgálja, hogy a vektor üres-e.
    /// @return true - ha nincs benne elem, különben false
    bool empty() const { return meret == 0; }

    /// Megváltoztatja a vektor méretét
    /// @param ns - Az új méret
    /// @param v - Az új elemek értéke (opcionális)
    void resize(size_t ns, const T& v = T()) {
        if (ns > kapacitas) {
            reserve(ns);
        }
        if (ns > meret) {
            for (size_t i = meret; i < ns; i++) {
                tomb[i] = v;
            }
        }
        meret = ns;
    }

    /// Foglal memóriát a megadott kapacitásra
    /// @param m - új kapacitás
    void reserve(size_t m) {
        if (m <= kapacitas) return;

        T* new_tomb = new T[m];
        for (size_t i = 0; i < meret; i++) {
            new_tomb[i] = tomb[i];
        }
        delete[] tomb;
        tomb = new_tomb;
        kapacitas = m;
    }

    /// Csökkenti a kapacitást a jelenlegi elemszámra.
    void shrink_to_fit() {
        if (kapacitas == meret) return;

        T* new_tomb = new T[meret];
        for (size_t i = 0; i < meret; i++) {
            new_tomb[i] = tomb[i];
        }
        delete[] tomb;
        tomb = new_tomb;
        kapacitas = meret;
    }



    /*-------------------------------------------
            Elem-hozzáférési mûveletek
    -------------------------------------------*/
    /// Biztonságos elemhozzáférés
    /// @param idx - Index
    /// @return - Az adott indexû elem referenciája
    /// @throws - std::out_of_range Ha az index érvénytelen
    T& at(size_t idx) {
        if (idx >= meret) throw std::out_of_range("Index tulcsordulas! (at)");
        return tomb[idx];
    }

    /// Biztonságos konstans elemhozzáférés
    /// @param idx - Index
    /// @return - Az adott indexû elem konstans referenciája
    /// @throws - std::out_of_range Ha az index érvénytelen
    const T& at(size_t idx) const {
        if (idx >= meret) throw std::out_of_range("Index tulcsordulas! (const at)");
        return tomb[idx];
    }

    /// Az elsõ elem referenciája
    /// @return - Az elsõ elem referenciája
    /// @throws - std::out_of_range Ha a vektor üres
    T& front() {
        if (empty()) throw std::out_of_range("Ures vector! (front)");
        return tomb[0];
    }

    /// Az utolsó elem referenciája
    /// @return - Az utolsó elem referenciája
    /// @throws - std::out_of_range Ha a vektor üres
    T& back() {
        if (empty()) throw std::out_of_range("Ures vector! (back)");
        return tomb[(meret - 1)];
    }

    /// Az elsõ elem konstans referenciája
    /// @return - Az elsõ elem konstans referenciája
    /// @throws - std::out_of_range Ha a vektor üres
    const T& front() const {
        if (empty()) throw std::out_of_range("Ures vector! (const front)");
        return tomb[0];
    }

    /// Az utolsó elem konstans referenciája
    /// @return - Az utolsó elem konstans referenciája
    /// @throws - std::out_of_range Ha a vektor üres
    const T& back() const {
        if (empty()) throw std::out_of_range("Ures vector! (const back)");
        return tomb[(meret - 1)];
    }



    /*-------------------------------------------
                Módosító mûveletek
    -------------------------------------------*/
    /// Új elem hozzáadása a végére
    /// @param v - A hozzáadandó érték
    void push_back(const T& v) {
        if (meret >= kapacitas) {
            reserve(kapacitas * 2);
        }
        tomb[meret++] = v;
    }

    /// Utolsó elem törlése
    /// @throws - std::out_of_range Ha a vektor üres
    void pop_back() {
        if (empty()) throw std::out_of_range("Ures vector! (pop_back)");
        --meret;
    }

    /// Elem beszúrása a megadott pozícióra
    /// @param p - Beszúrási pozíció (iterátor)
    /// @param v - A beszúrandó érték
    /// @return - Iterator az új elemre
    /// @throws - std::out_of_range Ha a pozíció érvénytelen
    T* insert(T* p, const T& v) {
        size_t idx = p - tomb;
        if (idx > meret) throw std::out_of_range("Ervenytelen pozicio! (insert)");

        if (meret >= kapacitas) {
            reserve(kapacitas == 0 ? 1 : kapacitas * 2);
            p = tomb + idx;  // Frissítjük a pozíciót, mert a tomb újra lett foglalva
        }

        for (size_t i = meret; i > idx; --i) {
            tomb[i] = tomb[i - 1];
        }
        tomb[idx] = v;
        meret++;
        return tomb + idx;
    }

    /// Elem törlése a megadott pozícióról
    /// @param p - Törlendõ elem pozíciója (iterátor)
    /// @return - Iterator a törölt elem utáni elemre
    /// @throws - std::out_of_range Ha a pozíció érvénytelen
    T* erase(T* p) {
        size_t idx = p - tomb;
        if (idx >= meret) throw std::out_of_range("Ervenytelen pozicio! (erase)");

        for (size_t i = idx; i < (meret - 1); i++) {
            tomb[i] = tomb[i + 1];
        }
        --meret;
        return tomb + idx;
    }

    /// Minden elem törlése
    void clear() {
        meret = 0;
    }
};

#endif // !VECTOR_HPP

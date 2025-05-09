#ifndef VECTOR_HPP  
#define VECTOR_HPP 

#include "Memtrace.h"

#include <stdexcept>

/// T�pusjellemz� sablon strukt�ra, amely meghat�rozza, hogy egy t�pus pointer-e.
/// @tparam T A vizsg�lt t�pus.
/// @note Alap�rtelmezetten false, azaz a t�pus nem pointer.
template <typename T>
struct IsPointer {
    enum { value = false };
};

/// T�pusjellemz� specializ�ci� pointer t�pusokra.
/// @tparam T A t�pus, amelynek pointer v�ltozata a specializ�ci� c�lja.
/// @note Ez a specializ�ci� akkor aktiv�l�dik, ha T pointer t�pus (pl. int*), �s true-t ad vissza.
template <typename T>
struct IsPointer<T*> {
    enum { value = true };
};

/// Sablon alap� dinamikus t�mboszt�ly, amely k�l�n kezeli pointer �s nem-pointer t�pusokat.
/// @tparam T A t�rolt t�pus.
/// @tparam VECTOR_MERET A vektor kezdeti kapacit�sa, alap�rtelmez�s szerint 100.
template <typename T, size_t VECTOR_MERET = 100>
class Vector {
    size_t kapacitas; ///< Az aktu�lisan lefoglalt t�rhely m�rete.
    size_t meret;     ///< Az aktu�lisan t�rolt elemek sz�ma.
    T* tomb;          ///< A dinamikusan foglalt t�mb mutat�ja.

    /// M�sol� f�ggv�ny, amely deleg�l a t�pusnak megfelel� implement�ci�s v�ltozatra.
    /// @param src - A m�soland� Vector p�ld�ny.
    void copy_elements(const Vector& src) {
        copy_elements_impl(src, std::integral_constant<bool, IsPointer<T>::value>());
        /*  Itt az std::integral_constant<bool, IsPointer<T>::value>() egy t�pus szint� dispatcher: ha pointer t�pus, akkor true_type, k�l�nben false_type.
            Ez azt jelenti, hogy t�pus alapj�n kiv�lasztjuk, melyik copy_elements_impl() vagy delete_elements_impl() f�ggv�ny h�v�djon meg � teh�t:
            Dispatcheles = d�nt�shozatal a f�ggv�nyh�v�sr�l(fut�si vagy ford�t�si id�ben)
        */
    }

    /// Pointer t�pusokra specializ�lt m�sol� logika. M�ly m�solatot k�sz�t clone() seg�ts�g�vel.
    /// @param src - A forr�s vektor.
    /// @param is_ptr - std::true_type jelzi, hogy pointer t�pusr�l van sz�.
    void copy_elements_impl(const Vector& src, std::true_type) {
        for (size_t i = 0; i < meret; ++i)
            tomb[i] = src.tomb[i] ? src.tomb[i]->clone() : nullptr;
    }

    /// Nem-pointer t�pusokra specializ�lt m�sol� logika. Egyszer� �rt�kad�s t�rt�nik.
    /// @param src - A forr�s vektor.
    /// @param is_ptr - std::false_type jelzi, hogy nem pointer t�pusr�l van sz�.
    void copy_elements_impl(const Vector& src, std::false_type) {
        for (size_t i = 0; i < meret; ++i)
            tomb[i] = src.tomb[i];
    }

    /// Elemfelszabad�t� f�ggv�ny, amely deleg�l a t�pusf�gg� implement�ci�ra.
    void delete_elements() {
        delete_elements_impl(std::integral_constant<bool, IsPointer<T>::value>());
    }

    /// Pointer t�pus eset�n felszabad�tja a mutatott objektumokat.
    /// @param is_ptr - std::true_type jelzi, hogy pointer t�pusr�l van sz�.
    void delete_elements_impl(std::true_type) {
        for (size_t i = 0; i < meret; ++i)
            delete tomb[i];
    }

    /// Nem-pointer t�pus eset�n nem v�gez semmilyen m�veletet.
    /// @param is_ptr - std::false_type jelzi, hogy nem pointer t�pusr�l van sz�.
    void delete_elements_impl(std::false_type) {
        // Nem csin�lunk semmit
    }

public:
    /// Alap�rtelmezett konstruktor. Inicializ�lja az �res vektort.
    Vector() : meret(0), kapacitas(VECTOR_MERET), tomb(new T[kapacitas]) {}

    /// M�sol� konstruktor. M�ly vagy sek�ly m�solatot k�sz�t a t�pus alapj�n.
    /// @param v - A m�soland� vektor p�ld�ny.
    Vector(const Vector& v) : meret(v.meret), kapacitas(v.kapacitas), tomb(new T[kapacitas]) {
        copy_elements(v);
    }

    /// Destruktor.
    ~Vector() {
        delete_elements();
        delete[] tomb;
    }


    /*-------------------------------------------
                Iter�tor t�mogat�s
    -------------------------------------------*/
    /// Mutat� az els� elemre (iter�tor kezdete)
    /// @return - Pointer az els� elemre
    T* begin() { return tomb; }

    /// Konstans mutat� az els� elemre (konstans iter�tor kezdete)
    /// @return - Konstans pointer az els� elemre
    const T* begin() const { return tomb; }

    /// Mutat� az utols� elem ut�ni ter�letre (iter�tor v�ge)
    /// @return Pointer az utols� elem ut�ni ter�letre
    T* end() { return tomb + meret; }

    /// Konstans mutat� az utols� elem ut�ni ter�letre (konstans iter�tor v�ge)
    /// @return Konstans pointer az utols� elem ut�ni ter�letre
    const T* end() const { return tomb + meret; }



    /*-------------------------------------------
                    Oper�torok
    -------------------------------------------*/
    /// �rt�kad� oper�tor.
    /// @param v - M�soland� vector p�ld�ny
    /// @return - Az aktu�lis objektum referenci�ja
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

    /// Egyenl�s�gvizsg�l� oper�tor
    /// @param v - �sszehasonl�tand� vector
    /// @return true - ha a vektorok tartalma megegyezik
    bool operator==(const Vector& v) const {
        if (meret != v.meret) return false;
        for (size_t i = 0; i < meret; i++) {
            if (tomb[i] != v.tomb[i]) return false;
        }
        return true;
    }

    /// Indexel� oper�tor
    /// @param idx - Index
    /// @return - Az adott index� elem referenci�ja
    /// @note - Nincs hat�rellen�rz�s!
    T& operator[](size_t idx) { return tomb[idx]; }

    /// Konstans indexel� oper�tor
    /// @param idx - Index
    /// @return - Az adott index� elem konstans referenci�ja
    /// @note - Nincs hat�rellen�rz�s!
    const T& operator[](size_t idx) const { return tomb[idx]; }



    /*-------------------------------------------
        Kapacit�ssal kapcsolatos m�veletek
    -------------------------------------------*/
    /// Visszaadja a vektorban t�rolt elemek sz�m�t.
    /// @return - Az aktu�lis elemsz�m (meret)
    size_t size() const { return meret; }

    /// Visszaadja a vektor kapacit�s�t.
    /// @return - A kapacit�s (kapacitas)
    size_t capacity() const { return kapacitas; }

    /// Megvizsg�lja, hogy a vektor �res-e.
    /// @return true - ha nincs benne elem, k�l�nben false
    bool empty() const { return meret == 0; }

    /// Megv�ltoztatja a vektor m�ret�t
    /// @param ns - Az �j m�ret
    /// @param v - Az �j elemek �rt�ke (opcion�lis)
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

    /// Foglal mem�ri�t a megadott kapacit�sra
    /// @param m - �j kapacit�s
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

    /// Cs�kkenti a kapacit�st a jelenlegi elemsz�mra.
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
            Elem-hozz�f�r�si m�veletek
    -------------------------------------------*/
    /// Biztons�gos elemhozz�f�r�s
    /// @param idx - Index
    /// @return - Az adott index� elem referenci�ja
    /// @throws - std::out_of_range Ha az index �rv�nytelen
    T& at(size_t idx) {
        if (idx >= meret) throw std::out_of_range("Index tulcsordulas! (at)");
        return tomb[idx];
    }

    /// Biztons�gos konstans elemhozz�f�r�s
    /// @param idx - Index
    /// @return - Az adott index� elem konstans referenci�ja
    /// @throws - std::out_of_range Ha az index �rv�nytelen
    const T& at(size_t idx) const {
        if (idx >= meret) throw std::out_of_range("Index tulcsordulas! (const at)");
        return tomb[idx];
    }

    /// Az els� elem referenci�ja
    /// @return - Az els� elem referenci�ja
    /// @throws - std::out_of_range Ha a vektor �res
    T& front() {
        if (empty()) throw std::out_of_range("Ures vector! (front)");
        return tomb[0];
    }

    /// Az utols� elem referenci�ja
    /// @return - Az utols� elem referenci�ja
    /// @throws - std::out_of_range Ha a vektor �res
    T& back() {
        if (empty()) throw std::out_of_range("Ures vector! (back)");
        return tomb[(meret - 1)];
    }

    /// Az els� elem konstans referenci�ja
    /// @return - Az els� elem konstans referenci�ja
    /// @throws - std::out_of_range Ha a vektor �res
    const T& front() const {
        if (empty()) throw std::out_of_range("Ures vector! (const front)");
        return tomb[0];
    }

    /// Az utols� elem konstans referenci�ja
    /// @return - Az utols� elem konstans referenci�ja
    /// @throws - std::out_of_range Ha a vektor �res
    const T& back() const {
        if (empty()) throw std::out_of_range("Ures vector! (const back)");
        return tomb[(meret - 1)];
    }



    /*-------------------------------------------
                M�dos�t� m�veletek
    -------------------------------------------*/
    /// �j elem hozz�ad�sa a v�g�re
    /// @param v - A hozz�adand� �rt�k
    void push_back(const T& v) {
        if (meret >= kapacitas) {
            reserve(kapacitas * 2);
        }
        tomb[meret++] = v;
    }

    /// Utols� elem t�rl�se
    /// @throws - std::out_of_range Ha a vektor �res
    void pop_back() {
        if (empty()) throw std::out_of_range("Ures vector! (pop_back)");
        --meret;
    }

    /// Elem besz�r�sa a megadott poz�ci�ra
    /// @param p - Besz�r�si poz�ci� (iter�tor)
    /// @param v - A besz�rand� �rt�k
    /// @return - Iterator az �j elemre
    /// @throws - std::out_of_range Ha a poz�ci� �rv�nytelen
    T* insert(T* p, const T& v) {
        size_t idx = p - tomb;
        if (idx > meret) throw std::out_of_range("Ervenytelen pozicio! (insert)");

        if (meret >= kapacitas) {
            reserve(kapacitas == 0 ? 1 : kapacitas * 2);
            p = tomb + idx;  // Friss�tj�k a poz�ci�t, mert a tomb �jra lett foglalva
        }

        for (size_t i = meret; i > idx; --i) {
            tomb[i] = tomb[i - 1];
        }
        tomb[idx] = v;
        meret++;
        return tomb + idx;
    }

    /// Elem t�rl�se a megadott poz�ci�r�l
    /// @param p - T�rlend� elem poz�ci�ja (iter�tor)
    /// @return - Iterator a t�r�lt elem ut�ni elemre
    /// @throws - std::out_of_range Ha a poz�ci� �rv�nytelen
    T* erase(T* p) {
        size_t idx = p - tomb;
        if (idx >= meret) throw std::out_of_range("Ervenytelen pozicio! (erase)");

        for (size_t i = idx; i < (meret - 1); i++) {
            tomb[i] = tomb[i + 1];
        }
        --meret;
        return tomb + idx;
    }

    /// Minden elem t�rl�se
    void clear() {
        meret = 0;
    }
};

#endif // !VECTOR_HPP

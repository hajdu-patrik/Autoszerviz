/**
*	\file MuveletAllapot.h
*   Ez a fájl a menürendszer állapotait definiálja.
*/

#ifndef MUVELETALLAPOT_H
#define MUVELETALLAPOT_H

/// A mûvelet végrehajtásának állapotát jelzõ enum.
enum class MuveletAllapot {
    Siker,
    Kilepes,
    Hiba
};

#endif // !MUVELETALLAPOT_H
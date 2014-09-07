// libeffects-android.cpp : Definiert die exportierten Funktionen für die DLL-Anwendung.
//

#include "stdafx.h"
#include "libeffects-android.h"


// Dies ist das Beispiel einer exportierten Variable.
LIBEFFECTSANDROID_API int nlibeffectsandroid=0;

// Dies ist das Beispiel einer exportierten Funktion.
LIBEFFECTSANDROID_API int fnlibeffectsandroid(void)
{
	return 42;
}

// Dies ist der Konstruktor einer Klasse, die exportiert wurde.
// Siehe libeffects-android.h für die Klassendefinition.
Clibeffectsandroid::Clibeffectsandroid()
{
	return;
}

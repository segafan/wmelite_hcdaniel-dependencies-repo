// Folgender ifdef-Block ist die Standardmethode zum Erstellen von Makros, die das Exportieren 
// aus einer DLL vereinfachen. Alle Dateien in dieser DLL werden mit dem LIBEFFECTSANDROID_EXPORTS-Symbol
// (in der Befehlszeile definiert) kompiliert. Dieses Symbol darf für kein Projekt definiert werden,
// das diese DLL verwendet. Alle anderen Projekte, deren Quelldateien diese Datei beinhalten, erkennen 
// LIBEFFECTSANDROID_API-Funktionen als aus einer DLL importiert, während die DLL
// mit diesem Makro definierte Symbole als exportiert ansieht.
#ifdef LIBEFFECTSANDROID_EXPORTS
#define LIBEFFECTSANDROID_API __declspec(dllexport)
#else
#define LIBEFFECTSANDROID_API __declspec(dllimport)
#endif

// Diese Klasse wird aus libeffects-android.dll exportiert.
class LIBEFFECTSANDROID_API Clibeffectsandroid {
public:
	Clibeffectsandroid(void);
	// TODO: Hier die Methoden hinzufügen.
};

extern LIBEFFECTSANDROID_API int nlibeffectsandroid;

LIBEFFECTSANDROID_API int fnlibeffectsandroid(void);

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBEFFECTS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBEFFECTS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBEFFECTS_EXPORTS
#define LIBEFFECTS_API __declspec(dllexport)
#else
#define LIBEFFECTS_API __declspec(dllimport)
#endif

// This class is exported from the libeffects.dll
class LIBEFFECTS_API Clibeffects {
public:
	Clibeffects(void);
	// TODO: add your methods here.
};

extern LIBEFFECTS_API int nlibeffects;

LIBEFFECTS_API int fnlibeffects(void);

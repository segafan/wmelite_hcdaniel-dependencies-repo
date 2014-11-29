#pragma once

// Durch Einbeziehen von"SDKDDKVer.h" wird die h�chste verf�gbare Windows-Plattform definiert.

// Wenn Sie die Anwendung f�r eine fr�here Windows-Plattform erstellen m�chten, schlie�en Sie "WinSDKVer.h" ein, und
// legen Sie das _WIN32_WINNT-Makro auf die zu unterst�tzende Plattform fest, bevor Sie "SDKDDKVer.h" einschlie�en.
#include <winsdkver.h>

#ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x0501
#endif

#include <SDKDDKVer.h>
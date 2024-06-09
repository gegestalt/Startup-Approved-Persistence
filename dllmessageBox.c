#include <windows.h>
BOOL APIENTRY DllMain(HMODULE hModule,DWORD nReason, LPVOID lpReserved){
	switch(nReason){
	case DLL_PROCESS_ATTACH:
		MessageBox(NULL,"Gügü-Learns-Malware!","(|_|)",MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

//for compilation : x86_64-w64-mingw32-g++ -shared -o dllmessageBox.dll dllmessageBox.c -fpermissive

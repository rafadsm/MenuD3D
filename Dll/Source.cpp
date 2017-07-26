///////////////////////////////
//	Desenvolvido por Finn	 //
//	  Source base menu		//
//	Não remova os créditos //
////////////////////////////

#include "Header.h"


extern unsigned WINAPI thread(LPVOID Param);

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		VM_START;
		DisableThreadLibraryCalls(hModule);
		g_Draw = std::make_unique<DXManager>();
		_beginthreadex(0, 0, thread, 0, 0, 0);
		VM_END;
	}
	return true;
}
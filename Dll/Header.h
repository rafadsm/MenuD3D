#pragma once
///////////////////////////////
//	Desenvolvido por Finn	 //
//	  Source base menu		//
//	Não remova os créditos //
////////////////////////////

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <process.h>
#include <memory>
#include <iterator>
#include <vector>
#include <map>
#include <unordered_map>

#pragma comment(lib, "Winmm.lib")

#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")

#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")

#include "VirtualizerSDK.h"
#include "XorStr.h"

#include "detours.h"
#pragma comment(lib, "detours.lib")

#include "Menu.h"
#include "DXManager.h"


#define VM_START VIRTUALIZER_START VIRTUALIZER_MUTATE1_START	VIRTUALIZER_MUTATE2_START VIRTUALIZER_MUTATE3_START
#define VM_END VIRTUALIZER_END

#define Fundo		   D3DCOLOR_ARGB(140, 40, 40, 40)
#define Cinza		   D3DCOLOR_ARGB(255,  60,  60,  60)
#define Preto		   0xFF000000
#define Branco         0xFFFFFFFF
#define Verde		   0xFF00FF00
#define Vermelho	   0xFFcc0000
#define Borda		   0xFF00739f


static struct key_s
{
	bool bPressed;
	DWORD dwStartTime;
}
key_state[256];
inline BOOL IsKeyPressed(int Key, DWORD dwTimeOut)
{
		if (HIWORD(GetKeyState(Key)))
		{
			if (!key_state[Key].bPressed || (key_state[Key].dwStartTime && (key_state[Key].dwStartTime + dwTimeOut) <= timeGetTime()))
			{
				key_state[Key].bPressed = TRUE;
				if (dwTimeOut > NULL)
					key_state[Key].dwStartTime = timeGetTime();
				return TRUE;
			}
		}
		else
			key_state[Key].bPressed = FALSE;
	return FALSE;
}




// Configurações

//#define _ANIMATION
//#define _USEIMAGEM
///////////////////////////////
//	Desenvolvido por Finn	 //
//	  Source base menu		//
//	Não remova os créditos //
////////////////////////////

#include "Header.h"
#include "Menu.h"


std::unique_ptr<MenuManager> g_Menu;

MenuManager::MenuManager(int x, int y, int w, int h)
{
	bVisible = true;
	bDir = true;
	bRun = false;

	backupX = x;
	startX = x;
	startY = y;
	startW = w;
	startH = h;

	currentSel = 0;

}

MenuManager::~MenuManager() = default;

bool MenuManager::GetActived(ItemType type)
{
	auto search = m_Items.find(type);
	if (search != m_Items.end()) {
		if (search->second->bUse)
			return true;
	}
	return false;
}

int MenuManager::GetArrayPos(ItemType type)
{
	auto search = m_Items.find(type);
	if (search != m_Items.end())
		return search->second->Pos;

	return 0;
}

void MenuManager::SetAnimation(bool b)
{
#ifdef _ANIMATION
	bDir = b;
	bRun = true;
#else
	bVisible = b;
#endif // _ANIMATION
}


void MenuManager::OnUpdate(LPDIRECT3DDEVICE9 pDevice)
{
#ifdef _ANIMATION
	if(bRun)
	{
		static DWORD dwTime = timeGetTime();
		bool process = (dwTime - timeGetTime() > 200) ? true : false;

		if (bDir)
		{
			bVisible = true;

			if (startX < backupX)
			{
				if (process)
				{
					startX++;
					dwTime = timeGetTime();
				}
			}
			else
				bRun = false;
		}
		else
		{
			if (startX + startW > 0)
			{
				if (process)
				{
					startX--;
					dwTime = timeGetTime();
				}
			}
			else
			{
				bRun = false;
				bVisible = false;
			}
		}

	}
#endif // _ANIMATION

	
	if (IsKeyPressed(VK_INSERT, 0) & 1)
	{
		SetAnimation(!bVisible);
	}

	HackActions();

	if (!bVisible)
		return;

	if (IsKeyPressed(VK_UP, 0) & 1)
		currentSel--;

	if (IsKeyPressed(VK_DOWN, 0) & 1)
		currentSel++;


	if (currentSel < 0)
		currentSel = m_Items.size() - 1;
	 else if (currentSel > (m_Items.size() - 1))
		currentSel = 0;
}


void MenuManager::Render(LPDIRECT3DDEVICE9 pDevice, IDirect3DTexture9* TextFundoMenu)
{

	OnUpdate(pDevice);

	if (!bVisible)
		return;

#ifdef _USEIMAGEM
	g_Draw->TexturedQuad(startX, startY, startW, startH, TextFundoMenu);
	g_Draw->DrawTextA("Game Hack", startX + startW / 2, startY + 8, Branco, 1);

	int listX = startX + 14;
	int listY = startY + 44;
#else
	g_Draw->DrawBox(startX, startY, startW, startH, Fundo);

	g_Draw->DrawBorder(startX, startY, startW, startH, Preto);
	g_Draw->DrawBorder(startX - 1, startY - 1, startW + 2, startH + 2, Cinza);

	g_Draw->DrawBorder(startX, startY, startW, 20, Preto);
	g_Draw->DrawTextA("Game Hack - Finn", startX + startW / 2, 52, Branco, 1);

	int listX = startX + 7;
	int listY = startY + 20 + 5;
#endif
	
	int itemShow = startX + startW - 36;
	int loopPos = 0;
	
	if (m_Items.size() == 0)
	{
#if !defined(_USEIMAGEM)
		startH = listY - (17 * 3) + 4;
#endif // _USEIMAGE
		return;
	}

	for(auto& itor : m_Items)
	{
		auto item = (itor).second;

		if (currentSel == loopPos)
		{
#ifdef _USEIMAGEM
			g_Draw->DrawBorder(listX - 5, listY - 2, startW - 15, 18, Borda);
#else
			g_Draw->DrawBorder(listX - 5, listY - 2, startW - 4, 18, Borda);
#endif // _USEIMAGEM

			if (IsKeyPressed(VK_RIGHT, 0) & 1)
			{
				if (item->bMulti)
				{
					if (item->Pos < item->Array.size() - 1)
						item->Pos++;
				}
				else
					item->bUse = true;
			}
			else if (IsKeyPressed(VK_LEFT, 0) & 1)
			{
				if (item->bMulti)
				{
					if (item->Pos > 0)
						item->Pos--;
				}
				else
					item->bUse = false;
			}
		}

		
		g_Draw->DrawTextA(item->szAction, listX + 18, listY, Branco, 2);
		
		if (item->bMulti)			
			g_Draw->DrawTextA(item->Array[item->Pos], itemShow, listY, Borda, 2);
		else
			g_Draw->DrawTextA((item->bUse ? "[On]" : "[Off]"), itemShow, listY, (item->bUse ? Borda : Vermelho), 2);

		g_Draw->DrawBox(listX, listY + 2, 10, 10, item->bMulti ? Borda : (item->bUse ? Borda : Vermelho));

		loopPos++;
		listY += 17;
	}

#ifdef _USEIMAGEM
	g_Draw->DrawTextA("Desenvolvido por Finn", startX + startW / 2, startY + startH - 32, Branco, 1);
#else
	startH = listY - (17 * 3) + 4;
#endif // _USEIMAGEM
	
}

void MenuManager::CreateItems()
{
	m_Items.emplace(HK_TESTE1, new MenuItem("Item 1", false));
	m_Items.emplace(HK_TESTE2, new MenuItem("Item 2", true));
	m_Items.emplace(HK_TESTE3, new MenuItem("Item 3", {"[str1]", "[str2]", "[str3]"}));
	
}

void MenuManager::HackActions()
{
	//Adicionar hacks aqui

	//ON/OFF
	if (GetActived(HK_TESTE1)) 
	{
		g_Draw->DrawTextA("Item 1 Ativado", 500, 300, Verde, 2);
	}

	if (GetActived(HK_TESTE2))
	{
		g_Draw->DrawTextA("Item 2 Ativado", 500, 320, Verde, 2);
	}

	//ARRAY VALUE - Exemplos
	{
		auto arrPos = GetArrayPos(HK_TESTE3); // Posição na array

		DWORD color;
		//OBS: valores em array sempre começam a contagem apartir do 0.
		//Valores e Ações
		if (arrPos == 0) //Se a array estiver em 0 [str1], a cor será vermelha
			color = 0xFFFF0000;
		else if (arrPos == 1) //Se o valor estiver em 1 [str2] será verde
			color = 0xFF00FF00;
		else if (arrPos == 2) //se o valor estiver em 2 [str3] será azul
			color = 0xFF0000FF;


		char buff[128];
		sprintf_s(buff, "ArrayPos Item 3: %d", arrPos);
		g_Draw->DrawTextA(buff, 500, 340, color, 2);
	}

}
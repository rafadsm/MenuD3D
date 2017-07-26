#pragma once
///////////////////////////////
//	Desenvolvido por Finn	 //
//	  Source base menu		//
//	Não remova os créditos //
////////////////////////////

//Aqui você vai adicionar o identificador do item
enum ItemType
{
	HK_TESTE1 = 0,
	HK_TESTE2,
	HK_TESTE3,

	HK_END
};


class MenuItem
{
public:
	MenuItem(char* name, bool b)
	{
		strcpy(szAction, name);
		bUse = b;

		bMulti = false;
	}

	MenuItem(char* name, std::vector<char*> arr)
	{
		strcpy(szAction, name);
		bUse = false;
		
		bMulti = true;
		Pos = 0;

		Array = arr;
	}

	~MenuItem() {}

	char szAction[128];
	bool bUse;

	bool bMulti;
	int Pos;
	
	std::vector<char*> Array;
};


class MenuManager
{
public:
	MenuManager(int x, int y, int w, int h);
	~MenuManager();

	void CreateItems();
	void HackActions();

	//bool IsVisible() { return bVisible; }
	void SetAnimation(bool b);

	void Render(LPDIRECT3DDEVICE9 pDevice, IDirect3DTexture9* TextFundoMenu);

private:
	bool bVisible{};

	bool bDir{}, bRun{};
	
	void OnUpdate(LPDIRECT3DDEVICE9 pDevice);
	bool GetActived(ItemType type);
	int GetArrayPos(ItemType type);

	int startX{}, startY{}, startW{}, startH{}, currentSel{}, backupX{};

	std::unordered_map<ItemType, MenuItem*> m_Items;
	
};

extern std::unique_ptr<MenuManager> g_Menu;
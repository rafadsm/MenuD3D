#pragma once
///////////////////////////////
//	Desenvolvido por Finn	 //
//	  Source base menu		//
//	Não remova os créditos //
////////////////////////////

struct vertex
{
	FLOAT x, y, z, rhw;
	DWORD color;
};

class DXManager
{
public:
	DXManager();
	~DXManager();

	void TexturedQuad(int x, int y, int w, int h, IDirect3DTexture9 * Texture);
	void DrawBox(float x, float y, float w, float h, DWORD color);
	void DrawBorder(int x, int y, int w, int h, D3DCOLOR BorderColor, int px = 1);
	void DrawTextA(const char* str, int x, int y, DWORD color, int f);
	
	
};

extern std::unique_ptr<DXManager> g_Draw;
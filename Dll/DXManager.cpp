///////////////////////////////
//	Desenvolvido por Finn	 //
//	  Source base menu		//
//	Não remova os créditos //
////////////////////////////

#include "Header.h"
#include "DXManager.h"

std::unique_ptr<DXManager> g_Draw;

LPDIRECT3DDEVICE9 m_Device = nullptr;
ID3DXFont * pFont = nullptr;
IDirect3DTexture9* pText = nullptr;

DXManager::DXManager() = default;
DXManager::~DXManager() = default;


void DXManager::TexturedQuad(int x, int y, int w, int h, IDirect3DTexture9 * Texture)
{
	struct ScreenSpaceTexVertex
	{
		float x, y, z, rhw;
		float tu, tv;
	};
	static ScreenSpaceTexVertex Triangles[6];

	int i = 0;

	auto Set = [&](bool a, bool b)
	{
		Triangles[i].x = a ? float(x) : float(x+w);
		Triangles[i].y = b ? float(y) : float(y+h);
		Triangles[i].z = 0;
		Triangles[i].rhw = 0;
		Triangles[i].tu = a ? 0 : 1;
		Triangles[i].tv = b ? 0 : 1;

		i++;
	};

	Set(true, true);
	Set(false, true);
	Set(false, false);
	Set(true, false);

	m_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_Device->SetTexture(0, Texture);
	m_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Triangles, sizeof(ScreenSpaceTexVertex));
}
void DXManager::DrawBox(float x, float y, float w, float h, DWORD color)
{
	m_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	m_Device->SetPixelShader(NULL);


	static vertex p[4];
	p[0].x = float(x);
	p[0].y = float(y);
	p[0].z = 0;
	p[0].rhw = 1;
	p[0].color = color;

	p[1].x = float(x + w);
	p[1].y = float(y);
	p[1].z = 0;
	p[1].rhw = 1;
	p[1].color = color;

	p[2].x = float(x + w);
	p[2].y = float(y + h);
	p[2].z = 0;
	p[2].rhw = 1;
	p[2].color = color;

	p[3].x = float(x);
	p[3].y = float(y + h);
	p[3].z = 0;
	p[3].rhw = 1;
	p[3].color = color;

	m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_Device->SetRenderState(D3DRS_FOGENABLE, FALSE);
	m_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	m_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);

	m_Device->SetTexture(0, NULL);

	HRESULT hr = m_Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, p, sizeof(vertex));
	_ASSERT(hr == D3D_OK);
}
void DXManager::DrawBorder(int x, int y, int w, int h, D3DCOLOR BorderColor, int px)
{
	DrawBox(x, (y + h - px), w, px, BorderColor);
	DrawBox(x, y, px, h, BorderColor);
	DrawBox(x, y, w, px, BorderColor);
	DrawBox((x + w - px), y, px, h, BorderColor);
}
void DXManager::DrawTextA(const char* str, int x, int y, DWORD color, int f)
{
	RECT pText;
	SetRect(&pText, x, y, x, y);

	switch (f)
	{
	case 0:
		pFont->DrawText(nullptr, str, -1, &pText, DT_NOCLIP | DT_RIGHT, color);
		break;

	case 1:
		pFont->DrawText(nullptr, str, -1, &pText, DT_NOCLIP | DT_CENTER, color);
		break;

	case 2:
		pFont->DrawText(nullptr, str, -1, &pText, DT_NOCLIP | DT_LEFT, color);
		break;
	}
}

typedef HRESULT(WINAPI* EndSceneDef)(LPDIRECT3DDEVICE9 pDevice);
EndSceneDef OnEndScene = NULL;

typedef HRESULT(WINAPI* ResetDef)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
ResetDef OnReset = NULL;

/*typedef HRESULT(WINAPI *PresentDef)(LPDIRECT3DDEVICE9 pDevice, CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion);
PresentDef OnPresent;*/

HRESULT WINAPI OnResetFunc(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
#ifdef _USEIMAGEM
	if (pText)
		pText->Release();
#endif // _USEIMAGEM

	if (pFont)
		pFont->OnLostDevice();

	auto reset = OnReset(pDevice, pPresentationParameters);
	if(SUCCEEDED(reset))
	{
		if (pFont) pFont->OnResetDevice();

		pText = nullptr;
	}
	return reset;
}

const HMODULE GetCurrentModule()
{
	DWORD flags = GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS;
	HMODULE hm = 0;
	::GetModuleHandleEx(flags, reinterpret_cast<LPCTSTR>(GetCurrentModule), &hm);
	return hm;
}

HRESULT WINAPI OnEndSceneFunc(LPDIRECT3DDEVICE9 pDevice)
{
	while (!m_Device) {
		m_Device = pDevice;
	}
	
	if (!pFont)
		D3DXCreateFontA(pDevice, 14, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "pFont", &pFont);

#ifdef _USEIMAGEM
	if (!pText) 
	{
		VM_START;
		auto Path = [&]()->std::string
		{
			HMODULE hmod = GetCurrentModule();
			TCHAR szPath[MAX_PATH];
			DWORD dwLen = GetModuleFileNameA(hmod, szPath, MAX_PATH);
			std::string f = szPath;

			return f.substr(0, f.find_last_of("/\\"));
		};

		char txPath[MAX_PATH];
		sprintf(txPath, "%s\\FinnMenu.png", Path().c_str());
		D3DXCreateTextureFromFileA(pDevice, txPath, &pText);
		VM_END;
		
		
		}
#endif // _USEIMAGEM

	g_Menu->Render(pDevice, pText);

	return OnEndScene(pDevice);
}

/*
HRESULT WINAPI OnPresentFunc(LPDIRECT3DDEVICE9 pDevice, CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion)
{
	while (!m_Device) {
		m_Device = pDevice;
	}
	
	return OnPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}*/


unsigned WINAPI thread(LPVOID Param)
{
		VM_START;

		auto lambda = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		};

		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, lambda, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "windowdxhook", NULL };
		RegisterClassEx(&wc);
		HWND hWnd = CreateWindow("windowdxhook", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, GetDesktopWindow(), NULL, wc.hInstance, NULL);
		LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		LPDIRECT3DDEVICE9 pDevice;
		pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice);
		DWORD* Table = (DWORD*)pDevice;
		Table = (DWORD*)Table[0];
		DestroyWindow(hWnd);


		g_Menu = std::make_unique<MenuManager>(50, 50, 255, 350);
		g_Menu->CreateItems();

		OnReset = (ResetDef)DetourFunction((PBYTE)(Table[16]), (PBYTE)&OnResetFunc);
		OnEndScene = (EndSceneDef)DetourFunction((PBYTE)(Table[42]), (PBYTE)&OnEndSceneFunc);
		//OnPresent = (PresentDef)DetourFunction((PBYTE)zHAK[17], (PBYTE)&OnPresentFunc);

		VM_END;

	return 0;
}
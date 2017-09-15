#include "stdafx.h"

#pragma intrinsic(_ReturnAddress) 
#define WFPlayer 0xA1F51A
#define WarfaceSmoke 0xA1B3E9
#define World 0xA1F4C8
#define Fullbright 0x8BBA03
//#define Mines ((NumVertices == 637 && primCount == 524 && Stride == 16)|| (NumVertices == 1541 && primCount == 1220 && Stride == 16))
//#define Grenades ((NumVertices == 128 && primCount == 120 && Stride == 16 ))

bool Esp;
bool Aimbot;
bool AutoShoot;
//autoshoot 
bool IsPressed = false;
int AimKey = 2;
int AimFOV = 15;
double AimSens = 0;
double vOutY = 2.5;
DWORD frametime = timeGetTime();

int Espr;
int Espg;
int Espb;

int Menu;
int Menux = 25;
int Menuy = 100;
int Menuw = 190;
int Menuh = 180;

int bMenux = 250;
int bMenuy = 300;
int bMenuw = 200;
int bMenuh = 125;

int cMenux = 250;
int cMenuy = 300;
int cMenuw = 200;
int cMenuh = 80;
bool dCounter;
bool AimEsp;
bool BoneDot;
bool BoneCircle;
bool BoneCrosshair;
bool Boxes;
bool Lines;
int aMenuSelection;
int bMenuSelection;
int cMenuSelection;

bool EspSettings;
bool AimSettings;
double AimHeight = 1;
bool Chams;
bool Glow;
bool LTrippin;
bool Explosives;
bool Frontcolor;
bool Backcolor;
bool Trippin;
bool NoSmoke;
bool Wireframe;
int Crosshair;
bool WallHack;
#define ItemOffset 25 
#define ValueOffset Menuw - 10 
#define ItemOffsetB 20 
#define ValueOffsetB Menuw - 10 


LPD3DXFONT    XFont = NULL;
LPD3DXFONT    ZFont = NULL;
LPD3DXLINE    pLine = NULL;
LPD3DXLINE  XLine = NULL;

D3DCOLOR d3dColorGreen = D3DCOLOR_ARGB(255, 0, 255, 0);
D3DCOLOR d3dColorWhite = D3DCOLOR_ARGB(255, 255, 255, 255);
D3DCOLOR d3dColorBlack = D3DCOLOR_ARGB(255, 0, 0, 0);
D3DCOLOR d3dColorBlue = D3DCOLOR_ARGB(255, 0, 0, 255);
D3DCOLOR d3dColorYellow = D3DCOLOR_ARGB(255, 255, 255, 0);
D3DCOLOR d3dColorRed = D3DCOLOR_ARGB(255, 255, 0, 0);
D3DCOLOR d3dColorLightBlue = D3DCOLOR_ARGB(255, 0, 255, 255);

LPDIRECT3DDEVICE9 pDevice;

typedef HRESULT(WINAPI *Prototype_Present)(LPDIRECT3DDEVICE9, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
typedef HRESULT(WINAPI *Prototype_End)(LPDIRECT3DDEVICE9);
typedef HRESULT(WINAPI *Prototype_Reset)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
typedef HRESULT(WINAPI* Prototype_DrawIndexedPrimitive)(LPDIRECT3DDEVICE9, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);

Prototype_Present xPresent;
Prototype_End xEnd;
Prototype_Reset xReset;
Prototype_DrawIndexedPrimitive xDrawIndexedPrimitive;

HRESULT WINAPI zPresent(LPDIRECT3DDEVICE9 Device, CONST RECT *pSrcRect, CONST RECT *pDestRect, HWND hDestWindow, CONST RGNDATA *pDirtyRegion);
HRESULT WINAPI zEnd(LPDIRECT3DDEVICE9 Device);
HRESULT WINAPI zReset(LPDIRECT3DDEVICE9 Device, D3DPRESENT_PARAMETERS *pp);
HRESULT WINAPI zDrawIndexedPrimitive(LPDIRECT3DDEVICE9 Device, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);

bool                                XInit = false;
int                                    g_Index = -1;
HMODULE                                g_HModule = 0;
std::vector<void*>                    g_Vector;
char                                g_Text[128] = { '\0' };
void*                                g_SelectedAddress = NULL;

LPDIRECT3DTEXTURE9 Pink, Black, Blue, Green, Red, Orange, White, Tur, Yellow, cFront, cBack;
DWORD cColorBack[3], CurrentColorBack;
DWORD cColorFront[3], CurrentColorFront;
#define d3dColorESP D3DCOLOR_ARGB( 0, Espr, Espg, Espb ) 
POINT Pos;
RECT rMyRect;
#define PI 3.14159265
LPDIRECT3DDEVICE9 Device;
IDirect3DPixelShader9* pShader;

//////////////////////// 
void CaseFunction();
void bCaseFunction();
void cCaseFunction();

void AddInt(int Pos, const char *text, int controller);
void AddBool(int Pos, const char *text, bool controller);
void bAddInt(int bPos, const char *text, int bcontroller);
void bAddBool(int bPos, const char *text, bool bcontroller);
void bSetIntLimits(int bcontroller, int bmax, int bmin);
void bAddIntItem(int Pos, const char *test, int controller, int max, int min);
void SetIntLimits(int bcontroller, int bmax, int bmin);
void SetIntLoop(int controller, int max, int min);
void AddIntItem(int Pos, const char *test, int controller, int max, int min);
void cAddIntItem(int cPos, const char *test, int ccontroller, int cmax, int cmin);
/////////////////////////// 

void DrawShadowText(int x, int y, D3DCOLOR color, char* String, const char * cFmt, ...)
{
	RECT Font;
	Font.bottom = 0;
	Font.left = x;
	Font.top = y;
	Font.right = 0;

	RECT Fonts;
	Fonts.bottom = 0;
	Fonts.left = x + 1;
	Fonts.top = y + 1;
	Fonts.right = 0;

	XFont->DrawTextA(0, String, strlen(String), &Fonts, DT_NOCLIP, 0xFF010101);
	XFont->DrawTextA(0, String, strlen(String), &Font, DT_NOCLIP, color);
}

void eDrawShadowText(int x, int y, D3DCOLOR color, char* String, float)
{
	RECT Font;
	Font.bottom = 0;
	Font.left = x;
	Font.top = y;
	Font.right = 0;

	RECT Fonts;
	Fonts.bottom = 0;
	Fonts.left = x + 1;
	Fonts.top = y + 1;
	Fonts.right = 0;

	XFont->DrawTextA(0, String, strlen(String), &Fonts, DT_NOCLIP, 0xFF010101);
	XFont->DrawTextA(0, String, strlen(String), &Font, DT_NOCLIP, color);
}

void FillRGB(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* Device)
{
	D3DRECT rec = { x, y, x + w, y + h };
	Device->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void zTitle(int x, int y, D3DCOLOR color, char* String, const char * cFmt, ...)
{
	RECT Font;
	Font.bottom = 0;
	Font.left = x;
	Font.top = y;
	Font.right = 0;

	RECT Fonts;
	Fonts.bottom = 0;
	Fonts.left = x + 1;
	Fonts.top = y + 1;
	Fonts.right = 0;

	ZFont->DrawTextA(0, String, strlen(String), &Fonts, DT_NOCLIP, 0xFF010101);
	ZFont->DrawTextA(0, String, strlen(String), &Font, DT_NOCLIP, color);
}

void zTitleCenterBottom(D3DVIEWPORT9* viewport, D3DCOLOR color, char* string, const char* cFmt, ...)
{
	RECT txtRect{};
	ZFont->DrawTextA(0, string, strlen(string), &txtRect, DT_CALCRECT, color);

	RECT fontRect;
	fontRect.bottom = viewport->Height;
	fontRect.left = (viewport->Width / 2) - ((txtRect.right - txtRect.left) / 2);
	fontRect.top = viewport->Height - (txtRect.bottom - txtRect.top);
	fontRect.right = viewport->Width;

	RECT fontShadowRect;
	fontShadowRect.bottom = fontRect.bottom;
	fontShadowRect.left = fontRect.left + 1;
	fontShadowRect.top = fontRect.top + 1;
	fontShadowRect.right = fontRect.right;

	ZFont->DrawTextA(0, string, strlen(string), &fontShadowRect, DT_NOCLIP, 0xFF010101);
	ZFont->DrawTextA(0, string, strlen(string), &fontRect, DT_NOCLIP, color);
}

void DrawPoint(LPDIRECT3DDEVICE9 Device, int baseX, int baseY, int baseW, int baseH, D3DCOLOR Cor)
{
	D3DRECT BarRect = { baseX, baseY, baseX + baseW, baseY + baseH };
	Device->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Cor, 0, 0);
}

void DrawFilledBox(int x, int y, int w, int h, D3DCOLOR color)
{
	D3DXVECTOR2 vLine[2];

	XLine->SetWidth(w);
	XLine->SetAntialias(false);
	XLine->SetGLLines(true);

	vLine[0].x = x + w / 2;
	vLine[0].y = y;
	vLine[1].x = x + w / 2;
	vLine[1].y = y + h;

	XLine->Begin();
	XLine->Draw(vLine, 2, color);
	XLine->End();
}

/*void DrawLine(float x, float y, float x2, float y2, float width, DWORD color)
{
	D3DXVECTOR2 vLine[2];
	pLine->SetWidth(width);
	pLine->SetAntialias(true);
	pLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();
}*/

void SetINTCVar(const char* szString, int iVal)
{
	_asm
	{
		mov ecx, dword ptr ds : [0x175F3E8]
		mov ecx, dword ptr ds : [ecx + 0x50]
		mov edx, dword ptr ds : [ecx]
		mov eax, dword ptr ds : [edx + 0xD0]
		push szString
		call eax
		mov edx, dword ptr ds : [eax + 0x18]
		mov eax, iVal
		mov dword ptr ds : [edx], eax
	}
}

void PrintText(LPD3DXFONT Font, long x, long y, D3DCOLOR fontColor, char *text, ...)
{
	RECT rct;
	rct.left = x - 1;
	rct.right = x + 1;
	rct.top = y - 1;
	rct.bottom = y + 1;

	if (!text) { return; }
	va_list va_alist;
	char logbuf[256] = { 0 };
	va_start(va_alist, text);
	_vsnprintf(logbuf + strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
	va_end(va_alist);
	RECT FontRect = { x, y, x, y };
	XFont->DrawText(NULL, logbuf, -1, &rct, DT_NOCLIP, fontColor);
}

void DrawRect(IDirect3DDevice9* dev, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT BarRect = { x, y, x + w, y + h };
	dev->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 0, 0);
}

void LBox(IDirect3DDevice9* Device, int x, int y, int w, int h, D3DCOLOR Outline)
{
	DrawRect(Device, x, y, w, 1, Outline);
	DrawRect(Device, x, y, 1, h, Outline);
	DrawRect(Device, x + w, y, 1, h, Outline);
	DrawRect(Device, x, y + h, w, 1, Outline);
}

void zLine(LPDIRECT3DDEVICE9 Device, int x, int y, int w, int h, D3DCOLOR Color)
{
	struct D3DVERTEX
	{
		float x, y, z, rhw;
		D3DCOLOR color;
	};
	D3DVERTEX vertices[] =
	{
		{ x, y, 0.5f, 1.0f, Color },
		{ w, h, 0.5f, 1.0f, Color }
	};

	Device->SetTexture(0, NULL);
	Device->SetPixelShader(NULL);
	Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Device->SetRenderState(D3DRS_ZENABLE, FALSE);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertices, sizeof(D3DVERTEX));
}

void Blur(float x, float y, float w, float h, D3DCOLOR ColorTwo, D3DCOLOR ColorOne, LPDIRECT3DDEVICE9 Device)
{
	struct D3DVERTEX
	{
		float x, y, z, rhw;
		D3DCOLOR color;
	};
	D3DVERTEX   vertices[] =
	{
		{ x - 7, y, 0, 5.0f, ColorTwo },
		{ x + w + 10, y, 0, 5.0f, ColorTwo },
		{ x, y + h, 1 , 1.0f, ColorOne },
		{ x + w, y + h, 1 , 1.0f, ColorOne }
	};

	Device->SetTexture(0, NULL);
	Device->SetPixelShader(NULL);
	Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Device->SetRenderState(D3DRS_ZENABLE, FALSE);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(D3DVERTEX));
}

void DrawRectangle(int x, int y, int w, int h, int r, int g, int b, int a) {
	if (!IsBadReadPtr(pLine, sizeof(ID3DXLine))) {
		D3DXVECTOR2 vLine1[2];
		D3DXVECTOR2 vLine2[2];
		D3DXVECTOR2 vLine3[2];
		D3DXVECTOR2 vLine4[2];

		pLine->SetAntialias(false);
		pLine->SetGLLines(true);

		vLine1[0].x = x;
		vLine1[0].y = y;
		vLine1[1].x = x;
		vLine1[1].y = y + h;

		vLine2[0].x = x + w;
		vLine2[0].y = y;
		vLine2[1].x = x + w;
		vLine2[1].y = y + h;

		vLine3[0].x = x;
		vLine3[0].y = y;
		vLine3[1].x = x + w;
		vLine3[1].y = y;

		vLine4[0].x = x;
		vLine4[0].y = y + h;
		vLine4[1].x = x + w;
		vLine4[1].y = y + h;

		pLine->Begin();
		pLine->Draw(vLine1, 2, D3DCOLOR_RGBA(r, g, b, a));
		pLine->Draw(vLine2, 2, D3DCOLOR_RGBA(r, g, b, a));
		pLine->Draw(vLine3, 2, D3DCOLOR_RGBA(r, g, b, a));
		pLine->Draw(vLine4, 2, D3DCOLOR_RGBA(r, g, b, a));
		pLine->End();
	}
}

void DrawString(ID3DXFont * XFont, int nPosX, int nPosY, D3DCOLOR dColor, const char * cFmt, ...)
{
	va_list mvalist;
	char cBuffer[256] = { 0 };
	RECT rFontRect = { nPosX, nPosY, nPosX + 16, nPosY + 120 };

	va_start(mvalist, cFmt);
	vsnprintf_s(cBuffer, sizeof(cBuffer), cFmt, mvalist);
	va_end(mvalist);

	XFont->DrawTextA(NULL, cBuffer, -1, &rFontRect, DT_LEFT | DT_NOCLIP, dColor);
}

struct ModelInfo_t
{
	float vOutX, vOutY;
	INT       iTeam;
	float CrosshairDistance;
};
std::vector<ModelInfo_t>ModelInfo;

float GetDistance(float Xx, float Yy, float xX, float yY)
{
	return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
}


void AddModel(LPDIRECT3DDEVICE9 Device, int iTeam)
{
	float xx, yy;
	D3DXMATRIX matrix, worldmatrix, m1;
	D3DXVECTOR4 position, input;
	D3DVIEWPORT9 dip_viewport;
	Device->GetViewport(&dip_viewport);
	Device->GetVertexShaderConstantF(36, m1, 4);
	Device->GetVertexShaderConstantF(0, worldmatrix, 3);

	input.x = worldmatrix._14;
	input.y = worldmatrix._24;
	input.z = worldmatrix._34 + (float)AimHeight;

	D3DXMatrixTranspose(&matrix, &m1);
	D3DXVec4Transform(&position, &input, &matrix);

	position.x = input.x * matrix._11 + input.y * matrix._21 + input.z * matrix._31 + matrix._41;
	position.y = input.x * matrix._12 + input.y * matrix._22 + input.z * matrix._32 + matrix._42;
	position.z = input.x * matrix._13 + input.y * matrix._23 + input.z * matrix._33 + matrix._43;
	position.w = input.x * matrix._14 + input.y * matrix._24 + input.z * matrix._34 + matrix._44;

	xx = ((position.x / position.w) * (dip_viewport.Width / 2.0f)) + dip_viewport.X + (dip_viewport.Width / 2.0f);
	yy = dip_viewport.Y + (dip_viewport.Height / 2.0f) - ((position.y / position.w) * (dip_viewport.Height / 2.0f));

	ModelInfo_t pModelInfo = { static_cast<float>(xx), static_cast<float>(yy), iTeam };

	ModelInfo.push_back(pModelInfo);
}

void DrawMyText(int x, int y, D3DCOLOR color, const char * cFmt, ...)
{
	CHAR buf[512] = { NULL };
	va_list ArgumentList;
	va_start(ArgumentList, cFmt);
	_vsnprintf_s(buf, sizeof(buf), sizeof(buf) - strlen(buf), cFmt, ArgumentList);
	va_end(ArgumentList);

	RECT Font;
	Font.bottom = 0;
	Font.left = x;
	Font.top = y;
	Font.right = 0;

	XFont->DrawTextA(0, buf, strlen(buf), &Font, DT_NOCLIP, color);
}

void Circle(int X, int Y, int radius, int numSides, DWORD Color)
{
	D3DXVECTOR2 Line[128];
	float Step = PI * 2.0 / numSides;
	int Count = 0;
	for (float a = 0; a < PI*2.0; a += Step)
	{
		float X1 = radius * cos(a) + X;
		float Y1 = radius * sin(a) + Y;
		float X2 = radius * cos(a + Step) + X;
		float Y2 = radius * sin(a + Step) + Y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}
	XLine->Begin();
	XLine->Draw(Line, Count, Color);
	XLine->End();
}

DWORD FindDevice(DWORD Len)
{
	DWORD dwObjBase = 0;

	dwObjBase = (DWORD)LoadLibrary(XorStr("d3d9.dll"));
	while (dwObjBase++ < dwObjBase + Len)
	{
		if ((*(WORD*)(dwObjBase + 0x00)) == 0x06C7
			&& (*(WORD*)(dwObjBase + 0x06)) == 0x8689
			&& (*(WORD*)(dwObjBase + 0x0C)) == 0x8689
			) {
			dwObjBase += 2; break;
		}
	}
	return(dwObjBase);
}

DWORD GetDeviceAddress(int VTableIndex)
{
	PDWORD VTable;
	*(DWORD*)&VTable = *(DWORD*)FindDevice(0x128000);
	return VTable[VTableIndex];
}

void zThread()
{
	while (true) {
		xPresent = (Prototype_Present)DetourFunction((PBYTE)GetDeviceAddress(17), (PBYTE)zPresent);
		xEnd = (Prototype_End)DetourFunction((PBYTE)GetDeviceAddress(42), (PBYTE)zEnd);
		xReset = (Prototype_Reset)DetourFunction((PBYTE)GetDeviceAddress(16), (PBYTE)zReset);
		xDrawIndexedPrimitive = (Prototype_DrawIndexedPrimitive)DetourFunction((PBYTE)GetDeviceAddress(82), (PBYTE)zDrawIndexedPrimitive);

		Sleep(60000);
		DetourRemove((PBYTE)zPresent, (PBYTE)zPresent);
		DetourRemove((PBYTE)zEnd, (PBYTE)zEnd);
		DetourRemove((PBYTE)zReset, (PBYTE)zReset);
		DetourRemove((PBYTE)zDrawIndexedPrimitive, (PBYTE)zDrawIndexedPrimitive);
	}
}

HRESULT cGenTex(LPDIRECT3DDEVICE9 Device, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
	if (FAILED(Device->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
		return E_FAIL;

	WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
		| (WORD)(((colour32 >> 20) & 0xF) << 8)
		| (WORD)(((colour32 >> 12) & 0xF) << 4)
		| (WORD)(((colour32 >> 4) & 0xF) << 0);

	D3DLOCKED_RECT d3dlr;
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*)d3dlr.pBits;

	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;

	(*ppD3Dtex)->UnlockRect(0);

	return S_OK;
}

void InitObjects(IDirect3DDevice9 * Device)
{

}
void DrawLine(float StartX, float StartY, float EndX, float EndY, D3DCOLOR dColor)
{
	XLine->SetWidth(1);
	XLine->SetGLLines(0);
	XLine->SetAntialias(1);

	D3DXVECTOR2 v2Line[2];
	v2Line[0].x = StartX;
	v2Line[0].y = StartY;
	v2Line[1].x = EndX;
	v2Line[1].y = EndY;

	XLine->Begin();
	XLine->Draw(v2Line, 2, dColor);
	XLine->End();
}


void Button(IDirect3DDevice9* dev, int x, int y, int w, int h, D3DCOLOR Outline)
{
	DrawRect(dev, x, y, w, 1, Outline);
	DrawRect(dev, x, y, 1, h, Outline);
	DrawRect(dev, x + w, y, 1, h, Outline);
	DrawRect(dev, x, y + h, w, 1, Outline);
}

void AddInt(int Pos, const char *text, int controller)
{
	DWORD OnColor = d3dColorGreen;
	DWORD OffColor = d3dColorWhite;
	if (controller)
	{
		DrawString(XFont, Menux + ItemOffset, (Menuy)+((Pos - 1) * 15), OnColor, text);
		DrawString(XFont, Menux + ValueOffset, (Menuy)+((Pos - 1) * 15), OnColor, XorStr("%i.00"), controller);
	}
	else if (!controller)
	{
		DrawString(XFont, Menux + ItemOffset, (Menuy)+((Pos - 1) * 15), OffColor, text);
		DrawString(XFont, Menux + ValueOffset, (Menuy)+((Pos - 1) * 15), OffColor, XorStr("0.00"));
	}
}

void AddBool(int Pos, const char *text, bool controller)
{
	DWORD OnColor = d3dColorGreen;
	DWORD OffColor = d3dColorWhite;
	if (controller)
	{
		DrawString(XFont, Menux + ItemOffset, (Menuy)+((Pos - 1) * 15), OnColor, text);
		DrawString(XFont, Menux + ValueOffset, (Menuy)+((Pos - 1) * 15), OnColor, XorStr("On"));
	}
	else if (!controller)
	{
		DrawString(XFont, Menux + ItemOffset, (Menuy)+((Pos - 1) * 15), OffColor, text);
		DrawString(XFont, Menux + ValueOffset, (Menuy)+((Pos - 1) * 15), OffColor, XorStr("Off"));
	}
}
void bAddInt(int Pos, const char *text, int controller)
{
	DWORD OnColor = d3dColorGreen;
	DWORD OffColor = d3dColorWhite;
	if (controller)
	{
		DrawString(XFont, bMenux + ItemOffsetB, (bMenuy)+((Pos - 1) * 15), OnColor, text);
		DrawString(XFont, bMenux + ValueOffsetB, (bMenuy)+((Pos - 1) * 15), OnColor, XorStr("%i.00"), controller);
	}
	else if (!controller)
	{
		DrawString(XFont, bMenux + ItemOffsetB, (bMenuy)+((Pos - 1) * 15), OffColor, text);
		DrawString(XFont, bMenux + ValueOffsetB, (bMenuy)+((Pos - 1) * 15), OffColor, XorStr("0.00"));
	}
}

void bAddBool(int Pos, const char *text, bool controller)
{
	DWORD OnColor = d3dColorGreen;
	DWORD OffColor = d3dColorWhite;
	if (controller)
	{
		DrawString(XFont, bMenux + ItemOffsetB, (bMenuy)+((Pos - 1) * 15), OnColor, text);
		DrawString(XFont, bMenux + ValueOffsetB, (bMenuy)+((Pos - 1) * 15), OnColor, XorStr("On"));
	}
	else if (!controller)
	{
		DrawString(XFont, bMenux + ItemOffsetB, (bMenuy)+((Pos - 1) * 15), OffColor, text);
		DrawString(XFont, bMenux + ValueOffsetB, (bMenuy)+((Pos - 1) * 15), OffColor, XorStr("Off"));
	}
}

void cAddInt(int Pos, const char *text, int controller)
{
	DWORD OnColor = d3dColorGreen;
	DWORD OffColor = d3dColorWhite;
	if (controller)
	{
		DrawString(XFont, bMenux + ItemOffsetB, (bMenuy)+((Pos - 1) * 15), OnColor, text);
		DrawString(XFont, bMenux + ValueOffsetB, (bMenuy)+((Pos - 1) * 15), OnColor, XorStr("%i.00"), controller);
	}
	else if (!controller)
	{
		DrawString(XFont, bMenux + ItemOffsetB, (bMenuy)+((Pos - 1) * 15), OffColor, text);
		DrawString(XFont, bMenux + ValueOffsetB, (bMenuy)+((Pos - 1) * 15), OffColor, XorStr("0.00"));
	}
}

void cAddBool(int Pos, const char *text, bool controller)
{
	DWORD OnColor = d3dColorGreen;
	DWORD OffColor = d3dColorWhite;
	if (controller)
	{
		DrawString(XFont, bMenux + ItemOffsetB, (bMenuy)+((Pos - 1) * 15), OnColor, text);
		DrawString(XFont, bMenux + ValueOffsetB, (bMenuy)+((Pos - 1) * 15), OnColor, XorStr("On"));
	}
	else if (!controller)
	{
		DrawString(XFont, bMenux + ItemOffsetB, (bMenuy)+((Pos - 1) * 15), OffColor, text);
		DrawString(XFont, bMenux + ValueOffsetB, (bMenuy)+((Pos - 1) * 15), OffColor, XorStr("Off"));
	}
}


int Menu_Max = 9;
void SetIntLimits(int controller, int max, int min)
{
	if (controller == max + 1)
	{
		controller = max;
	}
	if (controller == min - 1)
	{
		controller = min;
	}
}

void SetIntLoop(int controller, int max, int min)
{
	if (controller == max + 1)
	{
		controller = min;
	}
	if (controller == min - 1)
	{
		controller = max;
	}
}

void AddIntItem(int Pos, const char *test, int controller, int max, int min) {
	AddInt(Pos, test, controller);
	SetIntLimits(controller, max, min);
}

void CaseFunction()
{
	if (!EspSettings)
		if (!AimSettings)
			if (Menu && ((GetAsyncKeyState(VK_UP) & 1)))
			{
				if (aMenuSelection > 0)
					aMenuSelection--;
			}

	if (!EspSettings)
		if (!AimSettings)
			if (Menu && ((GetAsyncKeyState(VK_DOWN) & 1)))
			{
				if (aMenuSelection < Menu_Max)
					aMenuSelection++;
			}

	if (!EspSettings)
		if (!AimSettings)
			if (Menu && ((GetAsyncKeyState(VK_RIGHT) & 1)))
			{
				{
					switch (aMenuSelection)
					{
					case 0:
						Chams = !Chams;
						break;
					/*case 1:
						Glow = !Glow;
						break;*/
					case 1:
						Frontcolor = !Frontcolor && !Backcolor;
						break;
					case 2:
						Backcolor = !Backcolor && !Frontcolor;
						break;
					case 3:
						WallHack = !WallHack;
						break;
					/*case 3:
						Explosives = !Explosives;
						break;
					case 5:
						Wireframe = !Wireframe;
						break;*/
					case 4:
						NoSmoke = !NoSmoke;
						break;
					case 5:
						Crosshair++;
						if (Crosshair > 7)
							Crosshair--;
						break;
					case 6:
						Aimbot = !Aimbot;
						break;
					case 7:
						AimSettings = !AimSettings;
						break;
					case 8:
						Esp = !Esp;
						break;
					case 9:
						EspSettings = !EspSettings;
						break;
					/*case 12:
						AutoShoot = !AutoShoot;
						break;*/
					}
				}
			}

	if (!EspSettings)
		if (!AimSettings)
			if (Menu && ((GetAsyncKeyState(VK_LEFT) & 1)))
			{
				if (Menu)
				{
					switch (aMenuSelection)
					{
					case 0:
						Chams = !Chams;
						break;
					/*case 1:
						Glow = !Glow;
						break;
					case 3:
						Explosives = !Explosives;
						break;*/
					case 1:
						Frontcolor = !Frontcolor && !Backcolor;
						break;
					case 2:
						Backcolor = !Backcolor && !Frontcolor;
						break;
					case 3:
						WallHack = !WallHack;
						break;
					/*case 5:
						Wireframe = !Wireframe;
						break;*/
					case 4:
						NoSmoke = !NoSmoke;
						break;
					case 5:
						Crosshair--;
						if (Crosshair < 0)
							Crosshair++;
						break;
					case 6:
						Aimbot = !Aimbot;
						break;
					case 7:
						AimSettings = !AimSettings;
						break;
					case 8:
						Esp = !Esp;
						break;
					case 9:
						EspSettings = !EspSettings;
						break;
					/*case 12:
						AutoShoot = !AutoShoot;
						break;*/
					}
				}
			}
}

void bSetIntLimits(int bcontroller, int bmax, int bmin)
{
	if (bcontroller == bmax + 1)
	{
		bcontroller = bmax;
	}
	if (bcontroller == bmin - 1)
	{
		bcontroller = bmin;
	}
}

void bSetIntLoop(int bcontroller, int bmax, int bmin)
{
	if (bcontroller == bmax + 1)
	{
		bcontroller = bmin;
	}
	if (bcontroller == bmin - 1)
	{
		bcontroller = bmax;
	}
}

int bMenu_Max = 7;

void bAddIntItem(int bPos, const char *test, int bcontroller, int bmax, int bmin) {
	bAddInt(bPos, test, bcontroller);
	bSetIntLimits(bcontroller, bmax, bmin);
}

void bCaseFunction()
{
	if (!AimSettings)
		if (EspSettings && ((GetAsyncKeyState(VK_UP) & 1)))
		{
			if (bMenuSelection > 0)
				bMenuSelection--;
		}

	if (!AimSettings)
		if (EspSettings && ((GetAsyncKeyState(VK_DOWN) & 1)))
		{
			if (bMenuSelection < bMenu_Max)
				bMenuSelection++;
		}

	if (!AimSettings)
		if (EspSettings && ((GetAsyncKeyState(VK_RIGHT) & 1)))
		{
			if (EspSettings)
			{
				switch (bMenuSelection)
				{
				case 0:
					Boxes = !Boxes;
					break;
				case 1:
					Espr += 10;
					if (Espr > 255)
						Espr -= 10;
					break;
				case 2:
					Espg += 10;
					if (Espg > 255)
						Espg -= 10;
					break;
				case 3:
					Espb += 10;
					if (Espb > 255)
						Espb -= 10;
					break;
				case 4:
					dCounter = !dCounter;
					break;
				case 5:
					Lines = !Lines;
					break;
				case 6:
					AimHeight += 0.1;
					if (AimHeight > 2)
						AimHeight -= .1;
					break;
				case 7:
					EspSettings = !EspSettings;
					break;
				}
			}
		}

	if (!AimSettings)
		if (EspSettings && ((GetAsyncKeyState(VK_LEFT) & 1)))
		{
			if (EspSettings)
			{
				switch (bMenuSelection)
				{
				case 0:
					Boxes = !Boxes;
					break;
				case 1:
					Espr--;
					if (Espr < 0)
						Espr += 1;
					break;
				case 2:
					Espg--;
					if (Espg < 0)
						Espg += 1;
					break;
				case 3:
					Espb--;
					if (Espb < 0)
						Espb += 1;
					break;
				case 4:
					dCounter = !dCounter;
					break;
				case 5:
					Lines = !Lines;
					break;
				case 6:
					AimHeight -= 0.1;
					if (AimHeight < 0)
						AimHeight += .1;
					break;
				case 7:
					EspSettings = !EspSettings;
					break;
				}
			}
		}
}

void cSetIntLimits(int ccontroller, int cmax, int cmin)
{
	if (ccontroller == cmax + 1)
	{
		ccontroller = cmax;
	}
	if (ccontroller == cmin - 1)
	{
		ccontroller = cmin;
	}
}

void cSetIntLoop(int ccontroller, int cmax, int cmin)
{
	if (ccontroller == cmax + 1)
	{
		ccontroller = cmin;
	}
	if (ccontroller == cmin - 1)
	{
		ccontroller = cmax;
	}
}

int cMenu_Max = 4;

void cAddIntItem(int cPos, const char *test, int ccontroller, int cmax, int cmin) {
	cAddInt(cPos, test, ccontroller);
	cSetIntLimits(ccontroller, cmax, cmin);
}

void cCaseFunction()
{
	if (!EspSettings)
		if (AimSettings && ((GetAsyncKeyState(VK_UP) & 1)))
		{
			if (cMenuSelection > 0)
				cMenuSelection--;
		}
	if (!EspSettings)
		if (AimSettings && ((GetAsyncKeyState(VK_DOWN) & 1)))
		{
			if (cMenuSelection < cMenu_Max)
				cMenuSelection++;
		}
	if (!EspSettings)
		if (AimSettings && ((GetAsyncKeyState(VK_RIGHT) & 1)))
		{
			if (AimSettings)
			{
				switch (cMenuSelection)
				{
				case 0:
					AimSens += 0.5;
					if (AimSens > 5)
						AimSens -= .5;
					break;
				case 1:
					AimHeight += 0.1;
					if (AimHeight > 2)
						AimHeight -= .1;
					break;
				case 2:
					AimKey += 1;
					if (AimKey > 8)
						AimKey -= 1;
					break;
				case 3:
					AutoShoot = !AutoShoot;
					break;
				case 4:
					AimSettings = !AimSettings;
					break;
				}
			}
		}

	if (!EspSettings)
		if (AimSettings && ((GetAsyncKeyState(VK_LEFT) & 1)))
		{
			if (AimSettings)
			{
				switch (cMenuSelection)
				{
				case 0:
					AimSens--;
					if (AimSens < 0)
						AimSens++;
					break;
				case 1:
					AimHeight -= 0.1;
					if (AimHeight < 0)
						AimHeight += .1;
					break;
				case 2:
					AimKey -= 1;
					if (AimKey < 0)
						AimKey += 1;
					break;
				case 3:
					AutoShoot = !AutoShoot;
					break;
				case 5:
					AimSettings = !AimSettings;
					break;
				}
			}
		}
}
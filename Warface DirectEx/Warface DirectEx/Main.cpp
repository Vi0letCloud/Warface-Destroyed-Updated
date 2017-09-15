#include "Main.h"

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		g_HModule = hInstance;

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)zThread, 0, 0, 0);

		MessageBox(0, XorStr("Hack by Dark1027\nEnjoy :)"), XorStr("Warface Hack by Dark1027"), 0); //remove if you want ;)
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		if (XFont != NULL)
		{
			XFont->OnLostDevice();
			XFont->OnResetDevice();
			XFont->Release();
			XFont = NULL;
		}

		DetourRemove((PBYTE)zPresent, (PBYTE)zPresent);
		DetourRemove((PBYTE)zEnd, (PBYTE)zEnd);
		DetourRemove((PBYTE)zReset, (PBYTE)zReset);
		DetourRemove((PBYTE)zDrawIndexedPrimitive, (PBYTE)zDrawIndexedPrimitive);
	}
	return TRUE;
}

HRESULT WINAPI zPresent(LPDIRECT3DDEVICE9 Device, CONST RECT *pSrcRect, CONST RECT *pDestRect, HWND hDestWindow, CONST RGNDATA *pDirtyRegion)
{
	return xPresent(Device, pSrcRect, pDestRect, hDestWindow, pDirtyRegion);
}

HRESULT WINAPI zReset(LPDIRECT3DDEVICE9 Device, D3DPRESENT_PARAMETERS *pp)
{

	if (XFont != NULL) {
		XFont->OnResetDevice();
		XFont->OnResetDevice();
	}
	
	if (pLine != NULL) {
		pLine->OnResetDevice();
		pLine->OnResetDevice();
	}

	return xReset(Device, pp);

}
HRESULT WINAPI zDrawIndexedPrimitive(LPDIRECT3DDEVICE9 Device, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	IDirect3DVertexBuffer9* pStreamData = NULL;
	UINT xOffset, Stride;
	UINT pSizeOfData = 0;
	if (Device->GetStreamSource(0, &pStreamData, &xOffset, &Stride) == D3D_OK)
		pStreamData->Release();

	if (SUCCEEDED(Device->GetPixelShader(&pShader)))
		if (pShader != NULL)
			if (SUCCEEDED(pShader->GetFunction(NULL, &pSizeOfData)))
				if (pShader != NULL) { pShader->Release(); pShader = NULL; }
	void* ReturnAddress = _ReturnAddress();

	if (Chams)
		if (ReturnAddress != NULL && ReturnAddress == (void *)WFPlayer)
		{
			Device->SetRenderState(D3DRS_ZENABLE, FALSE);
			Device->SetTexture(0, cBack);
			xDrawIndexedPrimitive(Device, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			Device->SetRenderState(D3DRS_ZENABLE, TRUE);
			Device->SetTexture(0, cFront);

			Device->SetTexture(0, cBack);
			Device->SetRenderState(D3DRS_ZENABLE, false);
			Device->DrawIndexedPrimitive(PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			Device->SetRenderState(D3DRS_ZENABLE, true);
			Device->SetTexture(0, cFront);
		}

	if (Glow)
		if (ReturnAddress != NULL && ReturnAddress == (void *)WFPlayer)
		{
			Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			Device->SetTexture(0, cBack);
			Device->SetRenderState(D3DRS_ZENABLE, false);
			Device->DrawIndexedPrimitive(PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			Device->SetTexture(0, cFront);
			Device->SetRenderState(D3DRS_ZENABLE, true);
			Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			Device->DrawIndexedPrimitive(PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			Device->SetTexture(0, cFront);
			Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		}

	if (WallHack)
		if (ReturnAddress == (void *)WFPlayer)
		{
			Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			Device->SetRenderState(D3DRS_ZENABLE, FALSE);
			Device->DrawIndexedPrimitive(PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			Device->SetRenderState(D3DRS_ZENABLE, TRUE);
			Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

			Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			Device->SetRenderState(D3DRS_ZENABLE, false);
			Device->DrawIndexedPrimitive(PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			Device->SetRenderState(D3DRS_ZENABLE, true);
			Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}

	//Explosives Chams unfinished, causes crashes
	/*if (Explosives)
		if (Mines || Grenades)
		{
			Device->SetRenderState(D3DRS_ZENABLE, false);
			Device->SetTexture(0, cBack);
			Device->DrawIndexedPrimitive(PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			Device->SetRenderState(D3DRS_ZENABLE, true);
			Device->SetTexture(0, cFront);
		}*/

	//Weapons Chams unfinished, lost interest
	/*if (Weapons)
		if (pSizeOfData == 1984)
		{
			Device->SetRenderState(D3DRS_ZENABLE, FALSE);
			Device->SetTexture(0, cBack);
			xDrawIndexedPrimitive(Device, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			Device->SetRenderState(D3DRS_ZENABLE, TRUE);
			Device->SetTexture(0, cFront);
		}*/

	if (Wireframe)
		if (ReturnAddress == (void *)WFPlayer)
		{
			Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else {
			Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}

	if (NoSmoke && ReturnAddress != NULL && ReturnAddress == (void *)WarfaceSmoke)
	{
		return D3D_OK;
	}

	if (Esp)
	{
		if (ReturnAddress == (void *)WFPlayer && (Stride == 16 && (pSizeOfData == 640 || pSizeOfData <= 2436 ||pSizeOfData == 3152)))
			/*if (Stride == 16 && pSizeOfData == 640) 
			if(decl->Type == 16 && numElements == 7 && vSize == 2012)*/
		{
			AddModel(Device, 1);
		}
		else
		{
		}
	}

	return xDrawIndexedPrimitive(Device, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT WINAPI zEnd(LPDIRECT3DDEVICE9 Device)
{
	D3DVIEWPORT9 VP;
	memset(&VP, 0, sizeof(D3DVIEWPORT9));
	Device->GetViewport(&VP);
	float ScreenCenterX = (float)VP.Width / 2;
	float ScreenCenterY = (float)VP.Height / 2;

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = Device;

	if (Crosshair > 0)
		if (Crosshair == 1)
		{
			D3DRECT rec1 = { ScreenCenterX - 5, ScreenCenterY, ScreenCenterX + 5, ScreenCenterY + 1 };
			D3DRECT rec2 = { ScreenCenterX, ScreenCenterY - 5, ScreenCenterX + 1,ScreenCenterY + 5 };
			Device->Clear(1, &rec1, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 0), 0, 0);
			Device->Clear(1, &rec2, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 0), 0, 0);
		}

	if (Crosshair > 0)
		if (Crosshair == 2)
		{
			D3DRECT rec1 = { ScreenCenterX - 5, ScreenCenterY, ScreenCenterX + 5, ScreenCenterY + 1 };
			D3DRECT rec2 = { ScreenCenterX, ScreenCenterY - 5, ScreenCenterX + 1,ScreenCenterY + 5 };
			Device->Clear(1, &rec1, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 0, 0);
			Device->Clear(1, &rec2, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 0, 0);
		}

	if (Crosshair > 0 && Crosshair == 3)
	{
		D3DRECT rec1 = { ScreenCenterX - 5, ScreenCenterY, ScreenCenterX + 5, ScreenCenterY + 1 };
		D3DRECT rec2 = { ScreenCenterX, ScreenCenterY - 5, ScreenCenterX + 1,ScreenCenterY + 5 };
		Device->Clear(1, &rec1, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 0, 0);
		Device->Clear(1, &rec2, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 0, 0);
	}

	if (Crosshair > 0 && Crosshair == 4)
	{
		D3DRECT rec1 = { ScreenCenterX - 5, ScreenCenterY, ScreenCenterX + 5, ScreenCenterY + 1 };
		D3DRECT rec2 = { ScreenCenterX, ScreenCenterY - 5, ScreenCenterX + 1,ScreenCenterY + 5 };
		LBox(Device, ScreenCenterX - 5, ScreenCenterY - 5, 10, 10, d3dColorWhite);
	}

	if (Crosshair > 0 && Crosshair == 5)
	{
		FillRGB(ScreenCenterX - 20, ScreenCenterY, 40, 1, d3dColorBlack, Device);
		FillRGB(ScreenCenterX, ScreenCenterY - 20, 1, 40, d3dColorBlack, Device);
		FillRGB(ScreenCenterX - 17, ScreenCenterY, 34, 1, d3dColorBlue, Device);
		FillRGB(ScreenCenterX, ScreenCenterY - 17, 1, 34, d3dColorBlue, Device);
		FillRGB(ScreenCenterX - 14, ScreenCenterY, 28, 1, d3dColorWhite, Device);
		FillRGB(ScreenCenterX, ScreenCenterY - 14, 1, 28, d3dColorWhite, Device);
		FillRGB(ScreenCenterX - 11, ScreenCenterY, 22, 1, d3dColorGreen, Device);
		FillRGB(ScreenCenterX, ScreenCenterY - 11, 1, 22, d3dColorGreen, Device);
		FillRGB(ScreenCenterX - 9, ScreenCenterY, 18, 1, d3dColorYellow, Device);
		FillRGB(ScreenCenterX, ScreenCenterY - 9, 1, 18, d3dColorYellow, Device);
		FillRGB(ScreenCenterX - 6, ScreenCenterY, 12, 1, d3dColorLightBlue, Device);
		FillRGB(ScreenCenterX, ScreenCenterY - 6, 1, 12, d3dColorLightBlue, Device);
		FillRGB(ScreenCenterX - 3, ScreenCenterY, 6, 1, d3dColorRed, Device);
		FillRGB(ScreenCenterX, ScreenCenterY - 3, 1, 6, d3dColorRed, Device);
	}

	if (Crosshair > 0 && Crosshair == 6)
	{
		FillRGB(ScreenCenterX - 13, ScreenCenterY, 10, 1, d3dColorRed, Device);
		FillRGB(ScreenCenterX + 4, ScreenCenterY, 10, 1, d3dColorRed, Device);
		FillRGB(ScreenCenterX, ScreenCenterY - 13, 1, 10, d3dColorRed, Device);
		FillRGB(ScreenCenterX, ScreenCenterY + 4, 1, 10, d3dColorRed, Device);
	}

	if (Crosshair > 0 && Crosshair == 7)
	{
		FillRGB(ScreenCenterX - 13, ScreenCenterY, 10, 1, d3dColorBlue, Device);
		FillRGB(ScreenCenterX + 4, ScreenCenterY, 10, 1, d3dColorBlue, Device);
		FillRGB(ScreenCenterX, ScreenCenterY - 13, 1, 10, d3dColorBlue, Device);
		FillRGB(ScreenCenterX, ScreenCenterY + 4, 1, 10, d3dColorBlue, Device);
	}

	InitObjects(Device);

	if (!XInit)
	{
		if (XFont == NULL)
			D3DXCreateFont(Device, 14, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, XorStr("red"), &XFont);
		if (ZFont == NULL)
			D3DXCreateFont(Device, 14, 0, FW_EXTRABOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, XorStr("red"), &ZFont);
		if (XLine == NULL) D3DXCreateLine(Device, &XLine);
		cColorFront[CurrentColorFront] = 255;
		cColorBack[CurrentColorBack] = 255;
		XInit = true;
	}

	if (Frontcolor && !Backcolor)
		if (ModelInfo.size() != NULL)
		{
			for (unsigned int i = 0; i < ModelInfo.size(); i++)
			{
				ModelInfo[i].CrosshairDistance = GetDistance(ModelInfo[i].vOutX, ModelInfo[i].vOutY, ScreenCenterX, ScreenCenterY);
				cGenTex(Device, &cFront, D3DCOLOR_ARGB(255, cColorFront[0], cColorFront[1], cColorFront[2]));

				if (GetAsyncKeyState(VK_ADD) && cColorFront[CurrentColorFront] < 250)
					cColorFront[CurrentColorFront] += 10; 
				if (GetAsyncKeyState(VK_SUBTRACT) && cColorFront[CurrentColorFront] > 5)
					cColorFront[CurrentColorFront] -= 10;

				if (GetAsyncKeyState(0x31) & 1)
					CurrentColorFront = 0;
				else if (GetAsyncKeyState(0x32) & 1)
					CurrentColorFront = 1;
				else if (GetAsyncKeyState(0x33) & 1)
					CurrentColorFront = 2;

				DrawShadowText(Menux + 5, Menuy + 245, d3dColorRed, XorStr("Choose Color : 1/2/3 : +/-"), 0);

				FillRGB((int)ModelInfo[i].vOutX + 24, (int)ModelInfo[i].vOutY - 126.5, 7, 126.5, D3DCOLOR_ARGB(255, 255, 0, 0), Device);
				FillRGB((int)ModelInfo[i].vOutX + 25, (int)ModelInfo[i].vOutY - cColorFront[0] / 2, 10, 1, D3DCOLOR_ARGB(255, 255, 255, 255), Device);
				
				FillRGB((int)ModelInfo[i].vOutX + 40, (int)ModelInfo[i].vOutY - 126.5, 7, 126.5, D3DCOLOR_ARGB(255, 0, 255, 0), Device);
				FillRGB((int)ModelInfo[i].vOutX + 40, (int)ModelInfo[i].vOutY - cColorFront[1] / 2, 10, 1, D3DCOLOR_ARGB(255, 255, 255, 255), Device);
				
				FillRGB((int)ModelInfo[i].vOutX + 55, (int)ModelInfo[i].vOutY - 126.5, 7, 126.5, D3DCOLOR_ARGB(255, 0, 0, 255), Device);
				FillRGB((int)ModelInfo[i].vOutX + 55, (int)ModelInfo[i].vOutY - cColorFront[2] / 2, 10, 1, D3DCOLOR_ARGB(255, 255, 255, 255), Device);
			}
		}
	if (Backcolor && !Frontcolor)
		if (ModelInfo.size() != NULL)
		{
			for (unsigned int i = 0; i < ModelInfo.size(); i++)
			{
				ModelInfo[i].CrosshairDistance = GetDistance(ModelInfo[i].vOutX, ModelInfo[i].vOutY, ScreenCenterX, ScreenCenterY);
				cGenTex(Device, &cBack, D3DCOLOR_ARGB(255, cColorBack[0], cColorBack[1], cColorBack[2]));

				if (GetAsyncKeyState(VK_ADD) && cColorBack[CurrentColorBack] < 250)
					cColorBack[CurrentColorBack] += 10;
				if (GetAsyncKeyState(VK_SUBTRACT) && cColorBack[CurrentColorBack] > 5)
					cColorBack[CurrentColorBack] -= 10;

				if (GetAsyncKeyState(0x31) & 1)
					CurrentColorBack = 0;
				else if (GetAsyncKeyState(0x32) & 1)
					CurrentColorBack = 1;
				else if (GetAsyncKeyState(0x33) & 1)
					CurrentColorBack = 2;

				DrawShadowText(Menux + 5, Menuy + 245, d3dColorRed, XorStr("Choose Color : 1/2/3 : +/-"), 0);

				FillRGB((int)ModelInfo[i].vOutX + 24, (int)ModelInfo[i].vOutY - 126.5, 7, 126.5, D3DCOLOR_ARGB(255, 255, 0, 0), Device);
				FillRGB((int)ModelInfo[i].vOutX + 25, (int)ModelInfo[i].vOutY - cColorBack[0] / 2, 10, 1, D3DCOLOR_ARGB(255, 255, 255, 255), Device);
				
				FillRGB((int)ModelInfo[i].vOutX + 40, (int)ModelInfo[i].vOutY - 126.5, 7, 126.5, D3DCOLOR_ARGB(255, 0, 255, 0), Device);
				FillRGB((int)ModelInfo[i].vOutX + 40, (int)ModelInfo[i].vOutY - cColorBack[1] / 2, 10, 1, D3DCOLOR_ARGB(255, 255, 255, 255), Device);
				
				FillRGB((int)ModelInfo[i].vOutX + 55, (int)ModelInfo[i].vOutY - 126.5, 7, 126.5, D3DCOLOR_ARGB(255, 0, 0, 255), Device);
				FillRGB((int)ModelInfo[i].vOutX + 55, (int)ModelInfo[i].vOutY - cColorBack[2] / 2, 10, 1, D3DCOLOR_ARGB(255, 255, 255, 255), Device);
			}
		}


	if (ModelInfo.size() != NULL)
	{
		for (unsigned int i = 0; i < ModelInfo.size(); i++)
		{
			if (Esp)
			{
				ModelInfo[i].CrosshairDistance = GetDistance(ModelInfo[i].vOutX, ModelInfo[i].vOutY, ScreenCenterX, ScreenCenterY);

				if (ModelInfo[i].vOutX > 1 && ModelInfo[i].vOutY > 1)

					Blur((int)ModelInfo[i].vOutX - 20, (int)ModelInfo[i].vOutY - 40, 35, 25, D3DCOLOR D3DCOLOR_ARGB(0, Espr, Espg, Espb), d3dColorWhite, Device);

				if (Boxes)
				{
					LBox(Device, (int)ModelInfo[i].vOutX - 11, (int)ModelInfo[i].vOutY - 11, 20, 30, D3DCOLOR_ARGB(0, Espr, Espg, Espb));
				}

				if (Lines)
				{
					zLine(Device, (int)ModelInfo[i].vOutX, (int)ModelInfo[i].vOutY, ScreenCenterX, ScreenCenterY, d3dColorWhite);
				}

				if (dCounter)
				{
					if (ModelInfo[i].vOutX > 1 && ModelInfo[i].vOutY > 1)
						DrawMyText((int)ModelInfo[i].vOutX - 10, (int)ModelInfo[i].vOutY - 35, d3dColorWhite, XorStr("%.f"), ModelInfo[i].CrosshairDistance / 2);
				}
			}
		}
	}

	if (ModelInfo.size() != NULL)
	{
		UINT BestTarget = -1;
		DOUBLE fClosestPos = 99999;

		for (unsigned int i = 0; i < ModelInfo.size(); i++)
			if (Aimbot)
			{
				float radiusx = AimFOV * (ScreenCenterX / 100);
				float radiusy = AimFOV * (ScreenCenterY / 100);

				ModelInfo[i].CrosshairDistance = GetDistance(ModelInfo[i].vOutX, ModelInfo[i].vOutY, ScreenCenterX, ScreenCenterY);

				if (ModelInfo[i].vOutX >= ScreenCenterX - radiusx && ModelInfo[i].vOutX <= ScreenCenterX + radiusx && ModelInfo[i].vOutY >= ScreenCenterY - radiusy && ModelInfo[i].vOutY <= ScreenCenterY + radiusy)
				{
					if (ModelInfo[i].CrosshairDistance < fClosestPos)
					{
						fClosestPos = ModelInfo[i].CrosshairDistance;
						BestTarget = i;
					}
				}
			}

		if (AimKey == 1 && BestTarget != -1)
		{
			double DistX = ModelInfo[BestTarget].vOutX - ScreenCenterX;
			double DistY = ModelInfo[BestTarget].vOutY - ScreenCenterY;

			DistX /= 1;
			DistY /= 1;

			if (Aimbot && (GetAsyncKeyState(VK_SHIFT) & 0x8000))
				mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);


			
			if ((!GetAsyncKeyState(VK_LBUTTON) && (AutoShoot) && (GetAsyncKeyState(AimKey) & 0x8000)))
			{
				if (!IsPressed)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					IsPressed = true;
				}
			}
		}

		if (AimKey == 2 && BestTarget != -1)
		{
			double DistX = ModelInfo[BestTarget].vOutX - ScreenCenterX;
			double DistY = ModelInfo[BestTarget].vOutY - ScreenCenterY;

			DistX /= 1;
			DistY /= 1;

			if (Aimbot && (GetAsyncKeyState(VK_RBUTTON) & 0x8000))
				mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);

			
			if ((!GetAsyncKeyState(VK_LBUTTON) && (AutoShoot) && (GetAsyncKeyState(AimKey) & 0x8000)))
			{
				if (!IsPressed)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					IsPressed = true;
				}
			}
		}

		if (AimKey == 3 && BestTarget != -1)
		{
			double DistX = ModelInfo[BestTarget].vOutX - ScreenCenterX;
			double DistY = ModelInfo[BestTarget].vOutY - ScreenCenterY;

			DistX /= 1;
			DistY /= 1;

			if (Aimbot && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
				mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);

			
			if ((!GetAsyncKeyState(VK_LBUTTON) && (AutoShoot) && (GetAsyncKeyState(AimKey) & 0x8000)))
			{
				if (!IsPressed)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					IsPressed = true;
				}
			}
		}

		if (AimKey == 4 && BestTarget != -1)
		{
			double DistX = ModelInfo[BestTarget].vOutX - ScreenCenterX;
			double DistY = ModelInfo[BestTarget].vOutY - ScreenCenterY;

			DistX /= 1;
			DistY /= 1;

			if (Aimbot && (GetAsyncKeyState(VK_CONTROL) & 0x8000))
				mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);

			
			if ((!GetAsyncKeyState(VK_LBUTTON) && (AutoShoot) && (GetAsyncKeyState(AimKey) & 0x8000)))
			{
				if (!IsPressed)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					IsPressed = true;
				}
			}
		}

		if (AimKey == 5 && BestTarget != -1)
		{
			double DistX = ModelInfo[BestTarget].vOutX - ScreenCenterX;
			double DistY = ModelInfo[BestTarget].vOutY - ScreenCenterY;

			DistX /= 1;
			DistY /= 1;

			if (Aimbot && (GetAsyncKeyState(VK_MENU) & 0x8000))
				mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);

			
			if ((!GetAsyncKeyState(VK_LBUTTON) && (AutoShoot) && (GetAsyncKeyState(AimKey) & 0x8000)))
			{
				if (!IsPressed)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					IsPressed = true;
				}
			}
		}

		if (AimKey == 6 && BestTarget != -1)
		{
			double DistX = ModelInfo[BestTarget].vOutX - ScreenCenterX;
			double DistY = ModelInfo[BestTarget].vOutY - ScreenCenterY;

			DistX /= 1;
			DistY /= 1;

			if (Aimbot && (GetAsyncKeyState(VK_SPACE) & 0x8000))
				mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);

			
			if ((!GetAsyncKeyState(VK_LBUTTON) && (AutoShoot) && (GetAsyncKeyState(AimKey) & 0x8000)))
			{
				if (!IsPressed)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					IsPressed = true;
				}
			}
		}

		if (AimKey == 7 && BestTarget != -1)
		{
			double DistX = ModelInfo[BestTarget].vOutX - ScreenCenterX;
			double DistY = ModelInfo[BestTarget].vOutY - ScreenCenterY;

			DistX /= 1;
			DistY /= 1;

			if (Aimbot && (GetAsyncKeyState(0x58) & 0x8000))
				mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);

			
			if ((!GetAsyncKeyState(VK_LBUTTON) && (AutoShoot) && (GetAsyncKeyState(AimKey) & 0x8000)))
			{
				if (!IsPressed)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					IsPressed = true;
				}
			}
		}

		if (AimKey == 8 && BestTarget != -1)
		{
			double DistX = ModelInfo[BestTarget].vOutX - ScreenCenterX;
			double DistY = ModelInfo[BestTarget].vOutY - ScreenCenterY;

			DistX /= 1;
			DistY /= 1;

			if (Aimbot && (GetAsyncKeyState(0x43) & 0x8000))
				mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);

			
			if ((!GetAsyncKeyState(VK_LBUTTON) && (AutoShoot) && (GetAsyncKeyState(AimKey) & 0x8000)))
			{
				if (!IsPressed)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					IsPressed = true;
				}
			}
		}
	}


	ModelInfo.clear();

	if (AutoShoot && IsPressed)
	{
		if ((timeGetTime() - frametime >= 99) || (timeGetTime() >= (frametime + CLOCKS_PER_SEC / 2)))
		{
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			IsPressed = false;
			frametime = timeGetTime();
		}
	}

	if (GetAsyncKeyState(VK_INSERT) & 1) { Menu = !Menu; }

	CaseFunction();
	int x = 1;
	for (int x = 0; x < 20; x++) {
		if (Menu && aMenuSelection == x) {

			LBox(Device, Menux, Menuy - 20, Menuw + 25, Menuh + 20, D3DCOLOR_ARGB(255, 64, 64, 64));
			DrawFilledBox(Menux, Menuy, Menuw + 25, Menuh + 20, D3DCOLOR_ARGB(0, 150, 255, 155));
			DrawFilledBox(Menux, Menuy - 20, Menuw + 25, Menuh + 20, D3DCOLOR_ARGB(155, 0, 204, 0)); //(155, 25, 56, 100)
			LBox(Device, Menux, Menuy + (15 * x), Menuw + 25, 15, D3DCOLOR_ARGB(255, 64, 64, 64));
			Blur(Menux + 7, Menuy + (15 * x), Menuw + 8, 15, D3DCOLOR D3DCOLOR_ARGB(255, 64, 64, 64), d3dColorWhite, Device); //(255, 100, 0, 155)

			zTitle(Menux + 25, Menuy - 16, d3dColorWhite, XorStr("Warface Hack by Dark1027"), 0);
			AddBool(1, XorStr("Chams"), Chams);
			//AddBool(2, XorStr("Translucent Chams"), Glow);
			AddBool(2, XorStr("Front Chams Color"), Frontcolor);
			AddBool(3, XorStr("Back Chams Color"), Backcolor);
			AddBool(4, XorStr("Wallhack"), WallHack);
			/*AddBool(4, XorStr("Explosive Chams"), Explosives);
			AddBool(6, XorStr("Wireframe"), Wireframe);*/
			AddBool(5, XorStr("No Smoke"), NoSmoke);
			AddIntItem(6, XorStr("Crosshair"), Crosshair, 1, 0);
			AddBool(7, XorStr("Aimbot"), Aimbot);
			AddBool(8, XorStr("Aim-Settings"), AimSettings);
			AddBool(9, XorStr("ESP"), Esp);
			AddBool(10, XorStr("ESP-Settings"), EspSettings);
			//AddBool(13, XorStr("Auto Shoot"), AutoShoot);
			LBox(Device, Menux, Menuy - 20, Menuw + 25, Menuh + 20, D3DCOLOR_ARGB(255, 64, 64, 64));
			DrawLine(Menux, Menuy, Menuw + 50, Menuy, D3DCOLOR_ARGB(255, 64, 64, 64));
			DrawLine(Menux, (Menuh * 2) - 100, Menuw + 50, (Menuh * 2) - 100, D3DCOLOR_ARGB(255, 64, 64, 64));
			zTitle(Menux + 25, Menuh + 85, d3dColorWhite, XorStr("Made by Dark1027"), 0);

			if (Frontcolor)
				if (!Backcolor && !Esp)
				{
					cGenTex(Device, &cFront, D3DCOLOR_ARGB(255, cColorFront[0], cColorFront[1], cColorFront[2]));

					DrawShadowText(Menux + 5, Menuy + 245, d3dColorRed, XorStr("Choose Color : 1/2/3 : +/-"), 0);

					if (GetAsyncKeyState(VK_ADD) && cColorFront[CurrentColorFront] < 250)
						cColorFront[CurrentColorFront] += 10;
					if (GetAsyncKeyState(VK_SUBTRACT) && cColorFront[CurrentColorFront] > 5)
						cColorFront[CurrentColorFront] -= 10;

					if (GetAsyncKeyState(0x31) & 1)
						CurrentColorFront = 0;
					else if (GetAsyncKeyState(0x32) & 1)
						CurrentColorFront = 1;
					else if (GetAsyncKeyState(0x33) & 1)
						CurrentColorFront = 2;


					FillRGB(325, 135 + 3, 255, 8, D3DCOLOR_ARGB(255, 255, 0, 0), Device);
					FillRGB(325 + cColorFront[0], 136, 2, 11, D3DCOLOR_ARGB(255, 255, 255, 255), Device);
					FillRGB(325, 150 + 3, 255, 8, D3DCOLOR_ARGB(255, 0, 255, 0), Device);
					FillRGB(325 + cColorFront[1], 150 + 1, 2, 11, D3DCOLOR_ARGB(255, 255, 255, 255), Device);
					FillRGB(325, 165 + 3, 255, 8, D3DCOLOR_ARGB(255, 0, 0, 255), Device);
					FillRGB(325 + cColorFront[2], 165 + 1, 2, 11, D3DCOLOR_ARGB(255, 255, 255, 255), Device);
				}

			if (Backcolor)
				if (!Frontcolor && !Esp)
				{
					cGenTex(Device, &cBack, D3DCOLOR_ARGB(255, cColorBack[0], cColorBack[1], cColorBack[2]));

					FillRGB(325, 135 + 3, 255, 8, D3DCOLOR_ARGB(255, 255, 0, 0), Device);
					FillRGB(325 + cColorBack[0], 135 + 1, 2, 11, D3DCOLOR_ARGB(255, 255, 255, 255), Device);
					FillRGB(325, 150 + 3, 255, 8, D3DCOLOR_ARGB(255, 0, 255, 0), Device);
					FillRGB(325 + cColorBack[1], 150 + 1, 2, 11, D3DCOLOR_ARGB(255, 255, 255, 255), Device);
					FillRGB(325, 165 + 3, 255, 8, D3DCOLOR_ARGB(255, 0, 0, 255), Device);
					FillRGB(325 + cColorBack[2], 165 + 1, 2, 11, D3DCOLOR_ARGB(255, 255, 255, 255), Device);

					DrawShadowText(Menux + 5, Menuy + 245, d3dColorRed, XorStr("Choose Color : 1/2/3 : +/-"), 0);

					if (GetAsyncKeyState(VK_ADD) && cColorBack[CurrentColorBack] < 250)
						cColorBack[CurrentColorBack] += 10;
					if (GetAsyncKeyState(VK_SUBTRACT) && cColorBack[CurrentColorBack] > 5)
						cColorBack[CurrentColorBack] -= 10;

					if (GetAsyncKeyState(0x31) & 1)
						CurrentColorBack = 0;
					else if (GetAsyncKeyState(0x32) & 1)
						CurrentColorBack = 1;
					else if (GetAsyncKeyState(0x33) & 1)
						CurrentColorBack = 2;
				}
		}
	}

	if (EspSettings)
	{
		bCaseFunction();
		int x = 1;
		for (int x = 0; x < 20; x++) {
			if (EspSettings && bMenuSelection == x) {
				LBox(Device, bMenux, bMenuy - 20, bMenuw + 25, bMenuh + 20, d3dColorWhite);
				DrawFilledBox(bMenux, bMenuy, bMenuw + 25, bMenuh + 20, D3DCOLOR_ARGB(0, 25, 255, 155));
				DrawFilledBox(bMenux, bMenuy - 20, bMenuw + 25, bMenuh + 20, D3DCOLOR_ARGB(155, 25, 56, 100));
				LBox(Device, bMenux, bMenuy + (15 * x), bMenuw + 25, 15, d3dColorWhite);
				Blur(bMenux, bMenuy + (15 * x), bMenuw + 25, 15, D3DCOLOR D3DCOLOR_ARGB(255, 100, 0, 155), d3dColorWhite, Device);
				zTitle(bMenux + 18, bMenuy - 20, d3dColorWhite, XorStr("Esp Settings"), 0);
				bAddBool(1, XorStr("Boxes"), Boxes);
				bAddIntItem(2, XorStr("Esp Red"), Espr, 1, 0);
				bAddIntItem(3, XorStr("Esp Green"), Espg, 1, 0);
				bAddIntItem(4, XorStr("Esp Blue"), Espb, 1, 0);
				bAddBool(5, "Distance Counter", dCounter);
				bAddBool(6, XorStr("Lines"), Lines);
				cAddIntItem(7, XorStr("Bone Height ( + 0.1 )"), AimHeight, 1, 0);
				bAddIntItem(8, XorStr("Go Back"), EspSettings, 1, 0);
			}
		}
	}

	if (AimSettings)
	{
		cCaseFunction();
		int x = 1;
		for (int x = 0; x < 20; x++) {
			if (AimSettings && cMenuSelection == x) {

				LBox(Device, cMenux, cMenuy - 20, cMenuw + 25, cMenuh + 20, d3dColorWhite);
				DrawFilledBox(cMenux, cMenuy, cMenuw + 25, cMenuh + 20, D3DCOLOR_ARGB(0, 25, 255, 155));
				DrawFilledBox(cMenux, cMenuy - 20, cMenuw + 25, cMenuh + 20, D3DCOLOR_ARGB(155, 25, 56, 100));
				LBox(Device, cMenux, cMenuy + (15 * x), cMenuw + 25, 15, d3dColorWhite);
				Blur(cMenux, cMenuy + (15 * x), cMenuw + 25, 15, D3DCOLOR D3DCOLOR_ARGB(255, 100, 0, 155), d3dColorWhite, Device);

				zTitle(cMenux + 18, cMenuy - 20, d3dColorWhite, XorStr("Aim Settings"), 0);
				cAddIntItem(1, XorStr("Aim Sensitivity ( + 0.5 )"), AimSens, 1, 0);
				cAddIntItem(2, XorStr("Bone Height ( + 0.1 )"), AimHeight, 1, 0);
				cAddIntItem(3, XorStr("Aim Key"), AimKey, 1, 0);
				if (AimKey == 1) DrawShadowText(cMenux + 235, cMenuy, d3dColorGreen, XorStr("AimKey - Shift"), 0);
				else if (AimKey == 2) DrawShadowText(cMenux + 235, cMenuy, d3dColorGreen, XorStr("AimKey - RMouse"), 0);
				else if (AimKey == 3) DrawShadowText(cMenux + 235, cMenuy, d3dColorGreen, XorStr("AimKey - LMouse"), 0);
				else if (AimKey == 4) DrawShadowText(cMenux + 235, cMenuy, d3dColorGreen, XorStr("AimKey - Ctrl"), 0);
				else if (AimKey == 5) DrawShadowText(cMenux + 235, cMenuy, d3dColorGreen, XorStr("AimKey - Alt"), 0);
				else if (AimKey == 6) DrawShadowText(cMenux + 235, cMenuy, d3dColorGreen, XorStr("AimKey - Space"), 0);
				else if (AimKey == 7) DrawShadowText(cMenux + 235, cMenuy, d3dColorGreen, XorStr("AimKey - X"), 0);
				else if (AimKey == 8) DrawShadowText(cMenux + 235, cMenuy, d3dColorGreen, XorStr("AimKey - C"), 0);
				cAddIntItem(4, XorStr("Autoshoot"), AutoShoot, 1, 0);
				cAddIntItem(5, XorStr("Go Back"), AimSettings, 1, 0);
			}
		}
	}

	if (!Menu)
	{
		//Possible Watermarks here
	}

	return xEnd(Device);
}
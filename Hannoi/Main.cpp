#include "Pch.h"
#include "Application.h"

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int nCmdShow)
{
	CoInitialize(nullptr);
	return Application(1280,720,hInstance).Run(nCmdShow);
}

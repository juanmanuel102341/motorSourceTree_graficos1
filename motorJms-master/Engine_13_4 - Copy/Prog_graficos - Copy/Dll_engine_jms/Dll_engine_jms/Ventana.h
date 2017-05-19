#ifndef _VENTANA_H
#define _VENTANA_H
#include"EngineApi.h"
#include <windows.h>
#include <string>

using namespace std;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
 class ENGINE_API Ventana
{
public:
	Ventana();
	HWND hWnd;
	int ancho = 800;
	int alto = 640;
	wstring		className = L"NombreClase";
	void registerClass(HINSTANCE hInstance);
	bool createWindow(HINSTANCE hInstance, wstring title,
		int width, int height);
	//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//	~Ventana();

private:

};

#endif // !_VENTANA_H

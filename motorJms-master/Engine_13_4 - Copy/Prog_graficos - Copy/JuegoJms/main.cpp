// ---------------------------------------------------------------------
// Archivo: main.cpp
// Desc: Ejemplo de creación de ventanas
//
// Autor: Juan Pablo (McKrackeN) Bettini
// ---------------------------------------------------------------------

#include <windows.h>
#include <string>
#include"..//Dll_engine_jms/Dll_engine_jms/EngineApi.h"
#include "..//Dll_engine_jms/Dll_engine_jms/Ventana.h"
#include"..//Dll_engine_jms/Dll_engine_jms/Game.h"
//#pragma comment(lib,"d3d9.lib")
//#pragma comment(lib,"d3dx9.lib")
//#pragma comment(lib,"dxguid.lib")
using namespace std;



// ---------------------------------------------------------------------
// WinMain
// Es el equivalente a la clásica función int main ();
// ---------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	

	Game * nuevoJuego=new Game;
	if (nuevoJuego->StartUp(hInstance))
	{
		nuevoJuego->Update();
		nuevoJuego->ShutDown();

	}
	else {
	//mensaje error
	
	}
	
	
}

// ---------------------------------------------------------------------
// Window Procedure
// Cuando registramos la clase, deberemos especificar una función que
// atienda los mensajes que llegan a nuestra ventana.
// ---------------------------------------------------------------------

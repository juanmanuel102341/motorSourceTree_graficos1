#include"Game.h"


bool Game::StartUp(HINSTANCE hInstance)
{

	nuevaVentana = new Ventana;
	nuevaVentana->registerClass(hInstance);

	if (!nuevaVentana->createWindow(hInstance, L"PROYECTO", nuevaVentana->ancho,nuevaVentana->alto)) {
		return false;
	}
	else {
		
		nuevoGraphics = new Graphics;
	
		if (!nuevoGraphics->Initialize(nuevaVentana)) {
		return false;
		}
		return OnInitialize();
	//mensaje error
	}
}
void Game::Update() {
	static MSG	msg;			// Estructura de mensajes
	static bool	done = false;	// Si debo interrumpir el loop
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				done = true;			// ALT-F4
		}
		nuevoGraphics->Render();
		done = !OnLoop();
	}
	

}

bool Game::ShutDown() {
	OnShutDown();
	return true;
}

bool Game::OnInitialize() {
	return true;
}
bool Game::OnLoop() {
	return true;
}
void Game::OnDraw() {

}
bool Game::OnShutDown() {
	return true;
}
Game::Game() {


}
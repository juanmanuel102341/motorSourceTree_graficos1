#include"Ventana.h"

Ventana::Ventana() {


}

void Ventana::registerClass(HINSTANCE hInstance)
{
	WNDCLASS wc;

	memset(static_cast<void *> (&wc), 0, sizeof(WNDCLASS));  // Vacío la estrcutura WNDCLASS

	wc.style = CS_HREDRAW | CS_VREDRAW;					// Fuerza a enviar un Redraw si la ventana es reescalada 
														// movida horizontal o verticalmente
	wc.lpfnWndProc = (WNDPROC)WndProc;					// Asigna el Windows Procedure apropiado
	wc.hInstance = hInstance;							// Handler de la instancia de la aplicación
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;		// Cómo debe pintarse el fondo de la ventana
	wc.lpszClassName = (LPCWSTR)(className.c_str());	// Nombre de la clase

	RegisterClass(&wc);									// Registrando la clase
}

bool Ventana::createWindow(HINSTANCE hInstance, wstring title,int width, int height){
	hWnd = CreateWindow((LPCWSTR)(className.c_str()),	// Nombre de la clase
		(LPCWSTR)(title.c_str()),		// Título de la ventana
		WS_OVERLAPPEDWINDOW,			// Tipo de ventana
		0,								// Posición X inicial
		0,								// Posición Y inicial
		width,							// Ancho
		height,							// Alto
		NULL,							// Ventana padre (en nuestro caso es NULL)
		NULL,							// Menu (en nuestro caso NULL)
		hInstance,						// Handler de la instancia de la ventana (en XP es ignorado)
		NULL							// Siempre va NULL en estos casos
	);


	if (!hWnd) {	// Si hubo error retorno false
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);	//Fuerzo a mostrar la ventana
	UpdateWindow(hWnd);			// Actualizo la ventana

	return true;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:	// Selección del menú
		break;
	case WM_PAINT:		// Repintar la ventana
		break;
	case WM_DESTROY:	// Destruir la ventana
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); // Devuelvo los mensajes al Windows Procedure por defecto
	}
	return(0);
}



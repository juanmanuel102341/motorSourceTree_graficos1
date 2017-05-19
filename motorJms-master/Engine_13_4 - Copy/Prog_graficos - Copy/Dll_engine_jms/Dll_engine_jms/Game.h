#ifndef GAME_H
#define GAME_H
#include"EngineApi.h"
#include"Graphics.h"
#include"Ventana.h"

#include<iostream>
using namespace std;


class ENGINE_API Game
{
public:
	Ventana* nuevaVentana;
	Graphics* nuevoGraphics;
	bool StartUp(HINSTANCE hInstance);
	
	

	void Update();
	bool ShutDown();
	Game();
	
protected:

	 virtual bool OnInitialize();
	virtual bool OnLoop();
	virtual bool OnShutDown();
	virtual void OnDraw();
	//~Game();



};

#endif // !GAME_H


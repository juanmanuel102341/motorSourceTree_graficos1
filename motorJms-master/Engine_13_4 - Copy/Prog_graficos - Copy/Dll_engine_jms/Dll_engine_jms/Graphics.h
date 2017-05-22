#ifndef GRAPHICS_H
#define GRAPHICS_H

#include"EngineApi.h"

#include"Ventana.h"
#include<d3d9.h>
#include<d3dx9.h>
#include"Entity2d.h"
#include"Shape.h"
#include"Sprite.h"
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

#include<string>



 class ENGINE_API Graphics
{
public:
	

	Graphics();
		bool Initialize(Ventana* _objVentana);
		bool Shutdown();
		void Clear();
		void Draw();
		void Begin();
		void End();
		void Present();//manda a la pantalla lo q dibujas
		void Render(void);
					   //	~Graphics();

private:
	LPDIRECT3D9 pD3D;//objeto
	LPDIRECT3DDEVICE9 dispositivo;//device
	IDirect3DSurface9*backbufer;
	Ventana* nuevaVentana;
	
	IDirect3DVertexBuffer9*buffer_vertex_triangle;
	IDirect3DVertexBuffer9*buffer_vertex_square;

	Shape* entity2d;
	Sprite* sprite;

	bool InitDirect3D(void);


	void CleanUp(void);
	bool SetupEscene();
	
	CustomVertex coleccionVertices[3];
	HRESULT SetupVertexBuffer();
	//void DrawVertexBuffer();

	
	
	D3DXMATRIX MatrizTraslacion(float x, float y);
	D3DXMATRIX MatrizRotacion(float angle);
	D3DXMATRIX MatrizScala(float x, float y);
 };



#endif // !GRAPHICS_H

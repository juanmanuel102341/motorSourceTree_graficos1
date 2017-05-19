#include"Graphics.h"

bool Graphics::Initialize(Ventana* _ventana) {
	nuevaVentana = _ventana;
	if (!InitDirect3D()) {
		return false;
	}
	SetupVertexBuffer();
	//Render();
	return true;
	
		
}

void Graphics::CreacionColeccionVertices() {
	coleccionVertices[0].x = 100.0f;
	coleccionVertices[0].y = 100.0f;
	coleccionVertices[0].z = 0.0f;
//	coleccionVertices[0].rw = 1.0f;
	coleccionVertices[0].color = D3DCOLOR_XRGB(255, 0, 255);

	coleccionVertices[1].x = 500.0f;
	coleccionVertices[1].y = 100.0f;
	coleccionVertices[1].z = 0.0f;
	//coleccionVertices[1].rw = 1.0f;
	coleccionVertices[0].color = D3DCOLOR_XRGB(255, 0, 255);

	coleccionVertices[2].x = 500.0f;
	coleccionVertices[2].y = 500.0f;
	coleccionVertices[2].z = 0.0f;
	//coleccionVertices[2].rw = 1.0f;
	coleccionVertices[0].color = D3DCOLOR_XRGB(255, 0, 255);
}
HRESULT Graphics::SetupVertexBuffer() {
	buffer_vertex = NULL;
	HRESULT hr;

	CreacionColeccionVertices();
	hr = dispositivo->CreateVertexBuffer(3 * sizeof(CustomVertex), 0, D3DFVF_XYZ| D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &buffer_vertex, NULL);
		
	//chequeo
	if (FAILED(hr)) {
		return NULL;
	}

	VOID* punterosVacios;

	hr = buffer_vertex->Lock(0, 0, (VOID**)&punterosVacios, 0);

	if (FAILED(hr)) {
		return NULL;
	}
	memcpy(punterosVacios, coleccionVertices, sizeof(coleccionVertices));
	buffer_vertex->Unlock();
	return S_OK;


}
bool Graphics::MatrizTransformacion() {
	//generamos la matriz de transformacion
	HRESULT hr;
	D3DXMATRIX m_transformacion;
	D3DXMATRIX matTraslacion;
	D3DXMatrixIdentity(&m_transformacion);
	
	D3DXMatrixTranslation(&matTraslacion, 0, 300, 0.0f);
	D3DXMatrixMultiply(&m_transformacion, &matTraslacion,&m_transformacion);
	hr = dispositivo->SetTransform(D3DTS_WORLD, &m_transformacion);//se la asignamos a direct x
	if (FAILED(hr)) {
		return false;
	}
	return true;
}
D3DXMATRIX Graphics::MatrizTraslacion(float _x, float _y) {
	D3DXMATRIX matTraslacion;
	D3DXMatrixTranslation(&matTraslacion, _x, _y, 0.0f);
	return matTraslacion;
}
D3DXMATRIX Graphics::MatrizRotacion(float _angle) {
	D3DXMATRIX matRotacion;
	D3DXMatrixRotationZ(&matRotacion, _angle);
	return matRotacion;
}
D3DXMATRIX Graphics::MatrizScala(float _x, float _y) {
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, _x, _y, 0.0f);
	return matScale;
}
bool Graphics::MatrizVista() {
	HRESULT hr=NULL;

	//	D3DVIEWPORT9 viewport;
	//hr = dispositivo->GetViewport(&viewport);
	//if (FAILED(hr)) {
		//return false;
	//}

	D3DXMATRIX m_vista;
	D3DXVECTOR3 pos(0.0f, -15.0f, 0.0f);//pos
	D3DXVECTOR3 orientacion(0.0f, 0.0f, 0.0f);//donde mira
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//arriba
	D3DXMatrixLookAtLH(&m_vista, &pos, &orientacion, &up);//generamos la matriz
	hr = dispositivo->SetTransform(D3DTS_VIEW, &m_vista);//aaplicamos a direct x
	if (FAILED(hr)) {
		return false;
	}
	return true;
}
bool Graphics::MatrizProyeccion() {
	HRESULT hr;
	D3DXMATRIX m_proyeccion;
	D3DXMatrixOrthoLH(&m_proyeccion, nuevaVentana->ancho, nuevaVentana->alto, 1.0f, 500.0f);
	hr = dispositivo->SetTransform(D3DTS_PROJECTION, &m_proyeccion);//aplicamos dtx
	if (FAILED(hr)) {
		return false;
	}
	return true;

}

bool Graphics::SetupEscene() {
	
	
	D3DVIEWPORT9 vp{ 0, 0, nuevaVentana->ancho, nuevaVentana->alto, 0, 1 };
	
	dispositivo->SetViewport(&vp);
	//dispositivo->GetViewport(_viewport);
	
	D3DXMATRIX d3dmat;
	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&d3dmat);
	

	D3DXMatrixTranslation(&matTrans, 100.0f, 100.0f, 0.0f);
	D3DXMatrixMultiply(&d3dmat, &matTrans, &d3dmat);
	dispositivo->SetTransform(D3DTS_WORLD,&d3dmat);
	


	D3DXVECTOR3 eyePos(vp.Width/2, vp.Height/2.0f, -5.0f);
	D3DXVECTOR3 lookPos(vp.Width/2.0f, vp.Height/2.0f, 0.0f);
	D3DXVECTOR3 upVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&d3dmat, &eyePos, &lookPos, &upVec);
	dispositivo->SetTransform(D3DTS_VIEW,&d3dmat);

	D3DXMATRIX mProjectionMatrix;
	float fAspectRatio = (float) vp.Width/ vp.Height;
	D3DXMatrixOrthoLH(&mProjectionMatrix, (float) vp.Width, (float) vp.Height, -25.0f, 25.0f);
	 dispositivo->SetTransform(D3DTS_PROJECTION, &mProjectionMatrix);

	//if(FAILED(hres)) {
	//Error::setError(6);
	//return false;
	//}

	//dispositivo->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // D3DCULL_CCW
	
	//dispositivo->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);//?
	//dispositivo->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);//?
	//dispositivo->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);//?

	// Fijo valores por defecto para operaciones con el canal alpha
	//dispositivo->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//dispositivo->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//dispositivo->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	//dispositivo->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Deshabilito los speculars
	dispositivo->SetRenderState(D3DRS_SPECULARENABLE, FALSE);

	// Deshabilito el stencil
	dispositivo->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	
	return true;
}
void Graphics::Draw() {
//dibujo escena
}
void Graphics::Begin(){
	dispositivo->BeginScene();
}
void Graphics::End() {
	dispositivo->EndScene();
}
void Graphics::Clear() {
	dispositivo->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 0), 1.0f, 0);
}

void Graphics::Present(){
	if (NULL == dispositivo)
		return;

	dispositivo->Present(NULL, NULL, NULL, NULL);
}
bool Graphics::Shutdown() {
	return true;
}

bool Graphics::InitDirect3D(void) {
	
	pD3D = NULL;
	dispositivo = NULL;
	//objeto dtx;
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}
	//parametros objeto direct x
	
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = 800;
	d3dpp.BackBufferHeight = 600;
	d3dpp.hDeviceWindow = nuevaVentana->hWnd;

	//creamos device

	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF,nuevaVentana->hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &dispositivo))) {
		return false;
	}
	return true;
	
	}
void Graphics::Render(void) {
	
	Clear();
	SetupEscene();
	//MatrizTransformacion();
	//MatrizVista();
	//MatrizProyeccion();
	dispositivo->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // D3DCULL_CCW
	  // Deshabilito los speculars
	dispositivo->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	// Deshabilito el stencil
	dispositivo->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	
	Begin();
	dispositivo->SetStreamSource(0, buffer_vertex,0,sizeof(CustomVertex));
	dispositivo->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	dispositivo->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);

	End();
	
	Present();
}
void Graphics::CleanUp(void) {
      if (dispositivo != NULL){
		dispositivo->Release();
		}
	

	if (pD3D != NULL) {
		pD3D->Release();
	}
}
Graphics::Graphics() {
	
	
	

}
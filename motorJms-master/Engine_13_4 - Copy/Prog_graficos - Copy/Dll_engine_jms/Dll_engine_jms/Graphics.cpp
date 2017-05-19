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
	coleccionVertices[0].rw = 1.0f;
	coleccionVertices[0].color = D3DCOLOR_ARGB(0, 0, 0, 0);

	coleccionVertices[1].x = 500.0f;
	coleccionVertices[1].y = 100.0f;
	coleccionVertices[1].z = 0.0f;
	coleccionVertices[1].rw = 1.0f;
	coleccionVertices[1].color = D3DCOLOR_ARGB(0, 0, 0, 0);

	coleccionVertices[2].x = 500.0f;
	coleccionVertices[2].y = 500.0f;
	coleccionVertices[2].z = 0.0f;
	coleccionVertices[2].rw = 1.0f;
	coleccionVertices[2].color = D3DCOLOR_ARGB(0, 0, 0, 0);
}
HRESULT Graphics::SetupVertexBuffer() {
	buffer_vertex = NULL;
	HRESULT hr;

	CreacionColeccionVertices();
	hr = dispositivo->CreateVertexBuffer(3 * sizeof(CustomVertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &buffer_vertex, NULL);
		
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


bool Graphics::SetupEscene() {
	HRESULT hres;
	_viewport = nullptr;
	hres = dispositivo->GetViewport(_viewport);
	if (FAILED(hres)) {
		return false;
	}
	D3DXMATRIX d3dmat;

	D3DXMatrixIdentity(&d3dmat);
	
	 
	dispositivo->SetTransform(D3DTS_WORLD,&d3dmat);
	D3DXVECTOR3 eyePos(_viewport->Width/2, _viewport->Height/2.0f, -5.0f);
	D3DXVECTOR3 lookPos(_viewport->Width/2.0f, _viewport->Height/2.0f, 0.0f);
	D3DXVECTOR3 upVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&d3dmat, &eyePos, &lookPos, &upVec);
	dispositivo->SetTransform(D3DTS_VIEW,&d3dmat);

	D3DXMATRIX mProjectionMatrix;
	float fAspectRatio = (float) _viewport->Width/ _viewport->Height;
	D3DXMatrixOrthoLH(&mProjectionMatrix, (float) _viewport->Width, (float) _viewport->Height, -25.0f, 25.0f);
	hres = dispositivo->SetTransform(D3DTS_PROJECTION, &mProjectionMatrix);

	if(FAILED(hres)) {
	//Error::setError(6);
	return false;
	}

	dispositivo->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // D3DCULL_CCW

	dispositivo->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);//?
	dispositivo->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);//?
	dispositivo->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);//?

	// Fijo valores por defecto para operaciones con el canal alpha
	dispositivo->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	dispositivo->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	dispositivo->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	dispositivo->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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

	Begin();
	dispositivo->SetStreamSource(0, buffer_vertex,0,sizeof(CustomVertex));
	dispositivo->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
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
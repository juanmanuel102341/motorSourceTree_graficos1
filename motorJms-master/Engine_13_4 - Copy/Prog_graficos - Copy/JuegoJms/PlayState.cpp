#include"PlayState.h"



bool PlayState::OnInitialize() {
	OutputDebugString(TEXT("initialize playstate"));
	main_entity2d = new Shape;

	Point p;
	p.ptox = 0.0f;
	p.ptoy = 0.0f;
	Point p2;
	p2.ptox = -100.0f;
	p2.ptoy = 0.0f;
	Point p3;
	p3.ptox = -50.0f;
	p3.ptoy = 100.0f;
	main_entity2d->CreateTriangle(p, p2, p3);
	return true;
}
bool PlayState::OnLoop() {
	return true;
}
bool PlayState::OnShutDown() {
	return true;
}
PlayState::PlayState() {
}

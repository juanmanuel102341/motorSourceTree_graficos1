#include"PlayState.h"



bool PlayState::OnInitialize() {
	OutputDebugString(TEXT("initialize playstate"));

	main_entity2d = new Shape;
	
	main_entity2d->CreateTriangle();

	
	
	return true;
//	Game::OnInitialize

}


bool PlayState::OnLoop() {
	
	return true;
}
bool PlayState::OnShutDown() {
	return true;
}
PlayState::PlayState() {
//	Game::StartUp();
}

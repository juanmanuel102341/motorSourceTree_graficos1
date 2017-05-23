#ifndef PLAY_STATE

#define PLAY_STATE
#include"../Dll_engine_jms/Dll_engine_jms/Game.h"
#include"../Dll_engine_jms/Dll_engine_jms/Shape.h"
class PlayState:public Game
{
	Shape* main_entity2d;
public:
  PlayState();
protected:
  virtual bool OnInitialize();
 bool OnLoop();
bool OnShutDown();
//~PlayState();
  


};



#endif // !PLAY_STATE

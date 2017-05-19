#ifndef PLAY_STATE

#define PLAY_STATE
#include"../Dll_engine_jms/Dll_engine_jms/Game.h"
class PlayState:Game
{
protected:

  PlayState();
 bool OnInitialize();
 bool OnLoop();
bool OnShutDown();
//~PlayState();
  


};



#endif // !PLAY_STATE

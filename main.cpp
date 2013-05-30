#include"Game.h"

using namespace std;

int main()
{
	Game App;

	if(App.Initialize())
	{
		App.GameLoop();
		App.Deinitialize();
		return 0;
	}
	else
		return -1;
}
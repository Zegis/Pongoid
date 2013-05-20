#include"Game.h"

using namespace std;

int main()
{
	Game gra;

	if(gra.Initialize())
	{
		gra.GameLoop();
		gra.Deinitialize();
		return 0;
	}
	else
		return -1;
}
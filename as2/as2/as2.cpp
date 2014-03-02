// as2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Scene.h"
#include <time.h>


using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	time_t start = time(NULL);
	Scene coolScene = Scene();
	coolScene.render();
	//coolScene.film.writeFile("test.jpg");
	time_t end = time(NULL);
	cout <<  difftime(end, start) << " seconds elapsed" << endl;
	coolScene.film.display();
	return 0;
}



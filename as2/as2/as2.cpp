// as2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Scene.h"
#include "Parser.h"
#include <time.h>


using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	time_t start = time(NULL);
	Scene scene = Scene();
	loadScene("scene3.test",scene);
	
	/*cout << scene.allDirLights.front().color << endl;
	cout << scene.allDirLights.front().dir << endl;*/
	cout << scene.allPtLights.size() << endl;
	cout << scene.allDirLights.size() << endl;
	//cout << scene.allShapes.size() << endl;
	//cout << scene.allShapes.front()->material.ambient << endl;
	//cout << scene.depth << endl;
	//cout << scene.camera.lookFrom << endl;
	scene.render();
	scene.film.writeFile("test.jpg");
	time_t end = time(NULL);
	cout <<  difftime(end, start) << " seconds elapsed" << endl;
	scene.film.display();
	return 0;
}
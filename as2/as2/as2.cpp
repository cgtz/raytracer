// as2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Color.h"
#include "Sampler.h"


using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{




 //   //COLOR TEST - PASS
 //   Color c1(0.38f,0.67f,0.32f);
 //   cout << c1.toString() << endl;

	//SAMPLER & SAMPLE TEST - PASS	
	//Sample cool = Sample(0,0);
	//Sampler sampler = Sampler(5,6,.5);
	//while (sampler.generateSample(cool)) {
	//	cout << cool.toString() << endl;
	//}
	Sample cool = Sample(0,0);
	Sampler sampler = Sampler(5,6,.5);
	while (sampler.generateSample(cool)) {
		cout << cool.toString() << endl;
	}
	return 0;
	


	
}



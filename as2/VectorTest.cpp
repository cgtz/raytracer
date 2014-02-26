#include "stdafx.h""

using namespace std;
void VectorTest(){
	cout << "BEGIN VECTOR TEST" << endl;
	Vector v1(3.14f, 4.44f, 5.0f);
	Vector v2(3.14f, 4.44f, 5.0f);
	Vector v3(3.14f, 4.0f, 5.0f);

	cout << "Vector + Vector" << endl;
	Vector addTest = v1 + v2;
	cout << + Vector(6.28, 8.88, 10).toString() + " | "+ addTest.toString() << endl;

	cout << "Vector - Vector" << endl;
	Vector subTest = v1 - v2;
	cout << Vector(0,0,0).toString() + " | " + subTest.toString() << endl;

	Vector multTest = v1 * 6;
	cout << multTest.toString() << endl;

	float dotTest = v1.dot(v3);
	cout << dotTest << endl;

	bool eqTest = v1 == v2;
	cout << eqTest << endl;

	bool ceqTest = v1 == v1;
	cout << ceqTest << endl;

	bool neqTest = v1 != v3;
	cout << neqTest << endl;

	cout << v1.normalize().toString() << endl;
	cout << subTest.normalize().toString() << endl;

}
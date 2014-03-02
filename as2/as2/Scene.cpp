#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	this->transformation = Transformation();
	
	//this->allShapes.push_back(new Sphere(vec3(0, 0, 0), 100, Material(vec3(1, 0, 0.5), vec3(0.5, 0.5, 0.5), vec3(0.3, 0.9, 0.8), vec3(1, 0, 0),32), transformation));
	//this->allShapes.push_back(new Sphere(vec3(600, 600, 900), 100, Material(vec3(1, 1, 0), vec3(0.5, 0.5, 0.5), vec3(0.3, 0.9, 0.8), vec3(1,1,1),32), transformation));
	transformation.push();
		transformation.scale(vec3(4,2,1));
		this->allShapes.push_back(new Sphere(vec3(0, 0, 0), 100, Material(vec3(0.8, 0.1, 0), vec3(1, 0, 0), vec3(1, 1, 1), vec3(1, 1, 1),32), transformation));
	transformation.pop();

	transformation.push();
		transformation.scale(vec3(1,1,1));
		transformation.rotate(vec3(0,0,1),-30);
		transformation.translate(vec3(400,400,0));
		this->allShapes.push_back(new Sphere(vec3(0, 0, 0), 200, Material(vec3(1, 0, 1), vec3(0, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1),32), transformation));
	transformation.pop();

	transformation.push();
		transformation.scale(vec3(1,1,1));
		transformation.rotate(vec3(0,0,1),30);
		transformation.translate(vec3(-400,400, 0));
		this->allShapes.push_back(new Sphere(vec3(0, 0, 0), 200, Material(vec3(1, 1, 0), vec3(0, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1),32), transformation));
	transformation.pop();

	transformation.push();
		transformation.scale(vec3(1,1,1));
		transformation.rotate(vec3(0,0,1), -30);
		transformation.translate(vec3(-400,-400, 0));
		this->allShapes.push_back(new Sphere(vec3(0, 0, 0), 200, Material(vec3(0, 1, 1), vec3(0, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1),32), transformation));
	transformation.pop();

	transformation.push();
		transformation.scale(vec3(1,1,1));
		transformation.rotate(vec3(0,0,1),30);
		transformation.translate(vec3(400,-400, 0));
		this->allShapes.push_back(new Sphere(vec3(0, 0, 0), 200, Material(vec3(0, 0, 1), vec3(0, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1),32), transformation));
	transformation.pop();


	this->allShapes.push_back(new Triangle(vec3(0, 1000, -500), vec3(0, -1000, -500), vec3(-1000,0, -200), Material(vec3(1, 1, 0), vec3(0.0, 0.0, 0.0), vec3(1, 1, 1), vec3(1,1,1),200), transformation));
	this->allShapes.push_back(new Triangle(vec3(0, 1000, -500), vec3(0, -1000, -500), vec3(1000,0, -200), Material(vec3(1, 1, 0), vec3(0.0, 0.0, 0.0), vec3(1, 1, 1), vec3(1,1,1),200), transformation));

	//this->allDirLights.push_back(DirLight(vec3(1, 1, 1), vec3(1, 1, 1)));
	//this->allDirLights.push_back(DirLight(vec3(1, 1, 1), vec3(-1, 1, 1)));
	this->allPtLights.push_back(PtLight(vec3(1, 1, 1), vec3(0, 0, 1000)));
	this->camera = Camera(vec3(0, 0, 4000), vec3(0, 0, 0), vec3(0, 1, 0), 0.47, 680, 680);
	this->film = Film(680, 680);
}


bool Scene::closestIntersect(Ray& ray, float& minT, Intersection& closest){
	bool hit = false;
	minT = POS_INF;
	for (auto shape = this->allShapes.begin(); shape != this->allShapes.end(); shape++){
		float tempT = POS_INF;
		Intersection tempI;

		Ray tempR = ray;
		tempR.pos = ((*shape)->transform.inverse())*tempR.pos;
		tempR.dir = vec3(((*shape)->transform.inverse())*vec4(tempR.dir,0),VW).normalize();

		if ((*shape)->intersect(tempR, tempT, &tempI)) {
			if (tempT < minT){
				minT = tempT;
				closest = tempI; //CAUTION
				hit = true;
			}
		}
	}
	return hit;
}

vec3 Scene::phongShading(Material mat, Intersection intersect) {
	vec3 totalColor(0, 0, 0);
	for (auto dirLight = this->allDirLights.begin(); dirLight != this->allDirLights.end(); dirLight++){
		Ray lray;			
		vec3 lcolor;		//Don't matter variable
		float tempT = POS_INF;
		Intersection tempI; //Don't matter variable
		dirLight->generateLightRay(intersect, &lray, &lcolor); //create ray: intersect->point + t*(dirLight->dir) 
		//color only if path to object not occluded
		if (!this->closestIntersect(lray, tempT, tempI)){
			vec3 I = (dirLight->dir * -1).normalize();
			vec3 ambient = prod(mat.ambient, dirLight->color);
			//std::cout << ambient << std::endl;
			vec3 diffuse = prod(mat.diffuse, dirLight->color)*max(0.0, I*intersect.normal);
			vec3 specular = prod(mat.specular, dirLight->color)*
				pow(max(0.0,
				(-I + (2 * I*intersect.normal)*intersect.normal).normalize()
				*(this->camera.lookFrom - intersect.point).normalize()),
				mat.coeff);
			totalColor += ambient + diffuse + specular;
		}
	}
	for (auto ptLight = this->allPtLights.begin(); ptLight != this->allPtLights.end(); ptLight++){
		Ray lray;
		vec3 lcolor;		//Don't matter variable
		float tempT = POS_INF;
		Intersection tempI; //Don't matter variable
		ptLight->generateLightRay(intersect, &lray, &lcolor); //create lray: intersect->point + t*(light - intersect->point) 
		//Color only if path to object not occluded
		if (!this->closestIntersect(lray, tempT, tempI)){
			vec3 I = (ptLight->pos - intersect.point).normalize();
			vec3 ambient = prod(mat.ambient, ptLight->color);
			vec3 diffuse = prod(mat.diffuse, ptLight->color)*max(0.0, I*intersect.normal);
			vec3 specular = prod(mat.specular, ptLight->color)*
				pow(max(0.0,
				(-I + (2 * I*intersect.normal)*intersect.normal).normalize()
					*(this->camera.lookFrom - intersect.point).normalize()),
				mat.coeff);
			totalColor += ambient + diffuse + specular;
		}
		else{
			//cout << intersect.point << endl;
		}
	}
	//cout << totalColor << endl;
	return totalColor;
}

void Scene::raytrace(Ray& ray, int depth, vec3* color){
	if (depth <= 0) return;

	float minT = POS_INF;
	//std::cout << "depth: " << depth << std::endl;
	Intersection intersect; 
	bool hit = this->closestIntersect(ray, minT, intersect);
	if(hit){
		Material mat = intersect.shape->material;
		*color = *color + phongShading(mat, intersect); 
		if (mat.reflect[RED] > 0 || mat.reflect[GREEN] > 0 || mat.reflect[BLUE] > 0){
			//std::cout << "Reflected" << std::endl;
			Ray reflectRay(intersect.point, ray.dir.normalize()-intersect.normal*(intersect.normal*ray.dir.normalize()*2), 1, POS_INF);//define bounce angle/direction
			vec3 reflectedColor(0,0,0);
			raytrace(reflectRay, depth - 1, &reflectedColor);//CAUTION, reflected same recursion as eye?
			/*if (reflectedColor[RED] != 0 || reflectedColor[GREEN] != 0 || reflectedColor[BLUE] != 0) {
				cout << reflectedColor << endl;
				
			}*/
			*color = *color + reflectedColor; //prod(reflectedColor, mat.reflect);
		}
	}
	else{
		//Hit nothing, paint it black
		*color = vec3(0, 0, 0);
		return; //actually don't need this
	}
}

void Scene::render(){
	
	int step = camera.width/20;
	int c = 0;
	cout << "Render start: "<< endl;
	for (int i=0; i<camera.width; i++){
		if (i%step == 0){
			cout << c << "%";
			c += 5;
		}
		for (int j=0; j<camera.height; j++){
			vec3 pixel = camera.getPixel(i,j);
			Ray eyeRay= camera.generateRay(pixel);
			vec3 pixColor(0,0,0);
			this->raytrace(eyeRay, 5, &pixColor);
			film.writePixel(i, j, pixColor);
		}
	}
	std::cout << "DONE." << std::endl;
	film.display();
}


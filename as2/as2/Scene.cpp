#include "stdafx.h"
#include "Scene.h"
#include <omp.h>

Scene::Scene() {
	this->transformation = Transformation();
	this->depth = 5;

}

Scene::Scene(int depth)
{
	this->transformation = Transformation();
	this->depth = depth;
	transformation.push();
		transformation.scale(vec3(1,1,1));
		this->allShapes.push_back(new Sphere(vec3(0, 0, 0), 300, Material(vec3(1, 0, 0), vec3(0, 0.6, 0.6), vec3(0, 0, 1), vec3(1, 1, 1),320), transformation));
	transformation.pop();

	transformation.push();
		transformation.scale(vec3(2,1,1));
		transformation.rotate(vec3(0,0,1),-90);
		transformation.translate(vec3(400,0,0));
		this->allShapes.push_back(new Sphere(vec3(0, 0, 0), 100, Material(vec3(1, 0, 1), vec3(0, 1, 1), vec3(1, 1, 1), vec3(0.5, 0.5, 0.5),320), transformation));
	transformation.pop();

	transformation.push();
		transformation.scale(vec3(2,1,1));
		transformation.rotate(vec3(0,0,1),90);
		transformation.translate(vec3(-400,0, 0));
		this->allShapes.push_back(new Sphere(vec3(0, 0, 0), 100, Material(vec3(1, 1, 0), vec3(0, 1, 1), vec3(1, 1, 1), vec3(0.5, 0.5, 0.5),320), transformation));
	transformation.pop();

	transformation.push();
		transformation.scale(vec3(2,1,1));
		//transformation.rotate(vec3(0,0,1), -30);
		transformation.translate(vec3(0,-400, 0));
		this->allShapes.push_back(new Sphere(vec3(0, 0, 0), 100, Material(vec3(0, 1, 1), vec3(0, 1, 1), vec3(1, 1, 1), vec3(0.5, 0.5, 0.5),320), transformation));
	transformation.pop();

	transformation.push();
		transformation.scale(vec3(2,1,1));
		//transformation.rotate(vec3(0,0,1),30);
		transformation.translate(vec3(0,400, 0));
		this->allShapes.push_back(new Sphere(vec3(0, 0, 0), 100, Material(vec3(0, 0, 1), vec3(0, 1, 1), vec3(1, 1, 1), vec3(0.5, 0.5, 0.5),320), transformation));
	transformation.pop();

	this->allShapes.push_back(new Triangle(vec3(-200, 400, -1000), vec3(-1000, 0, 0), vec3(-200,-400, -1000), Material(vec3(0, 0, 0), vec3(0, 1.0, 0.6), vec3(1, 1, 1), vec3(1,1,1),500), transformation));
	this->allShapes.push_back(new Triangle(vec3(200, 400, -1000),  vec3(200,-400, -1000), vec3(1000, 0, 0), Material(vec3(0, 0, 0), vec3(0, 1.0, 0.6), vec3(1, 1, 1), vec3(1,1,1),500), transformation));
	this->allShapes.push_back(new Triangle(vec3(-200, 400, -1000), vec3(200, 400, -1000), vec3(0, 1000, 0),  Material(vec3(0, 0, 0), vec3(0, 1.0, 0.6), vec3(1, 1, 1), vec3(1,1,1),500), transformation));
	this->allShapes.push_back(new Triangle(vec3(-200, -400, -1000), vec3(0, -1000, 0), vec3(200,-400, -1000), Material(vec3(0, 0, 0), vec3(0, 1.0, 0.6), vec3(1, 1, 1), vec3(1,1,1),500), transformation));

	this->allShapes.push_back(new Triangle(vec3(-10000, -10000, -4000), vec3(10000, 10000, -4000), vec3(-10000, 10000, -4000), Material(vec3(0, 0, 0), vec3(0.8, 0.5, 0.8), vec3(1, 1, 1), vec3(1,1,1),200), transformation));
	this->allShapes.push_back(new Triangle(vec3(-10000, -10000, -4000), vec3(10000,-10000, -4000), vec3(10000, 10000, -4000), Material(vec3(0, 0, 0), vec3(0.8, 0.5, 0.8), vec3(1, 1, 1), vec3(1,1,1),200), transformation));

	this->allDirLights.push_back(DirLight(vec3(1, 1, 1), vec3(1, 1, 1)));
	this->allDirLights.push_back(DirLight(vec3(1, 1, 1), vec3(-1, 1, 1)));
	this->allPtLights.push_back(PtLight(vec3(1, 1, 1), vec3(0, 0, 1000)));
	this->allPtLights.push_back(PtLight(vec3(1, 1, 1), vec3(0, 0, -3000)));
	this->camera = Camera(vec3(0, 0, 4000), vec3(0, 0, 0), vec3(0, 1, 0), 40, 680, 680);
	this->film = Film(680, 680);
}


bool Scene::closestIntersect(Ray& ray, float& minT, Intersection& closest){
	bool hit = false;
	minT = POS_INF;
	for (auto shape = this->allShapes.begin(); shape != this->allShapes.end(); shape++){
		float tempT = POS_INF;
		Intersection tempI;

		Ray tempR = ray;

		tempR.pos = vec3(((*shape)->transformI)*vec4(tempR.pos,1),VW);
		tempR.dir = vec3(((*shape)->transformI)*vec4(tempR.dir,0),VW);

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
	vec3 totalColor = mat.emissive;
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
	}
	return totalColor;
}

void Scene::raytrace(Ray& ray, int depth, vec3* color){
	if (depth <= 0) return;

	float minT = POS_INF;
	Intersection intersect; 
	bool hit = this->closestIntersect(ray, minT, intersect);
	if(hit){
		Material mat = intersect.shape->material;
		*color = *color + phongShading(mat, intersect); 
		if (mat.reflect[RED] > 0 || mat.reflect[GREEN] > 0 || mat.reflect[BLUE] > 0){
			Ray reflectRay(intersect.point, ray.dir.normalize()-intersect.normal*(intersect.normal*ray.dir.normalize()*2), 1, POS_INF);//define bounce angle/direction
			vec3 reflectedColor(0,0,0);
			raytrace(reflectRay, depth - 1, &reflectedColor);//CAUTION, reflected same recursion as eye?
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
	int width = camera.width;
	int height = camera.height;

	//omp_set_num_threads(8);
	
	#pragma omp parallel
	{
		#pragma omp for
		for (int i=0; i<width; i++){
			if (i%step == 0){
				cout << c << "%";
				c += 5;
			}
			for (int j=0; j<height; j++){
				vec3 pixel = camera.getPixel(i,j);
				Ray eyeRay= camera.generateRay(pixel);
				vec3 pixColor(0,0,0);
				this->raytrace(eyeRay, this->depth, &pixColor);
				film.writePixel(i, j, pixColor);
			}
		}
	}
	std::cout << " DONE." << std::endl;
}


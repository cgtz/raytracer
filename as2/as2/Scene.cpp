#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	this->allShapes.push_back(new Sphere(Point(32, 45, 0), 50, Material(Color(1, 0, 0), Color(0.5, 0.5, 0.5), Color(0.3, 0.9, 0.8), 16)));
	this->allDirLights.push_back(DirLight(Color(1, 1, 1), Vector(1, 1, 1)));
	//this->allPtLights;
	this->camera = Camera(Point(0, 0, -200), Point(32, 45, -100), Vector(0, 1, 0), PI / 1.5, 680, 680);
	this->film = Film(680, 680);
	this->sampler = Sampler(680, 680);
	this->sample = Sample(0, 0);
}


bool Scene::closestIntersect(Ray& ray, float& minT, Intersection& closest){
	bool hit = false;
	minT = POS_INF;
	for (auto shape = this->allShapes.begin(); shape != this->allShapes.end(); shape++){
		float tempT = POS_INF;
		Intersection tempI;
		if ((*shape)->intersect(ray, tempT, &tempI)) {
			if (tempT < minT){
				minT = tempT;
				closest = tempI; //CAUTION
				hit = true;
			}
		}
	}
	return hit;
}

Color Scene::phongShading(Material mat, Intersection intersect) {
	Color totalColor(0, 0, 0);
	for (auto dirLight = this->allDirLights.begin(); dirLight != this->allDirLights.end(); dirLight++){
		Ray lray;			
		Color lcolor;		//Don't matter variable
		float tempT = POS_INF;
		Intersection tempI; //Don't matter variable
		dirLight->generateLightRay(intersect, &lray, &lcolor); //create ray: intersectPoint + t*(dirLight->dir) 
		//Color only if path to object not occluded
		if (!this->closestIntersect(lray, tempT, tempI)){
			Vector I = dirLight->dir * -1;
			Color ambient = mat.ambient*dirLight->color;
			Color diffuse = mat.diffuse*dirLight->color*max(0.0f, I.dot(intersect.normal));
			Color specular = mat.specular*dirLight->color*
							pow(max(0.0f,
								((I * -1) + intersect.normal * 2 * I.dot(intersect.normal))
								.dot(this->camera.lookFrom - intersect.point)),
							mat.coeff);
			totalColor = totalColor + ambient + diffuse + specular;
		}
	}
	for (auto ptLight = this->allPtLights.begin(); ptLight != this->allPtLights.end(); ptLight++){
		Ray lray;
		Color lcolor;		//Don't matter variable
		float tempT = POS_INF;
		Intersection tempI; //Don't matter variable
		ptLight->generateLightRay(intersect, &lray, &lcolor); //create ray: intersectPoint + t*(light - intersectPoint) 
		//Color only if path to object not occluded
		if (!this->closestIntersect(lray, tempT, tempI)){
			Vector I = ptLight->pos - intersect.point;
			Color ambient = mat.ambient*ptLight->color;
			Color diffuse = mat.diffuse*ptLight->color*max(0.0f, I.dot(intersect.normal));
			Color specular = mat.specular*ptLight->color*
				pow(max(0.0f,
				((I * -1) + intersect.normal * 2 * I.dot(intersect.normal))
				.dot(this->camera.lookFrom - intersect.point)),
				mat.coeff);
			totalColor = totalColor + ambient + diffuse + specular;
		}
	}

	return totalColor;
}

	void Scene::raytrace(Ray& ray, int depth, Color* color){
		if (depth <= 0) return;

		float minT = POS_INF;
		Intersection intersect; 
		bool hit = this->closestIntersect(ray, minT, intersect);
		if(hit){
			Material mat = intersect.shape->material;
			*color = *color + phongShading(mat, intersect); //NO OPERATOR COLOR* and COLOR
			if (mat.coeff > 0){
				Ray reflectRay;
				Color reflectedColor;
				raytrace(reflectRay, depth - 1, &reflectedColor);//CAUTION, reflected same recursion as eye?
				*color = *color + reflectedColor;
			}
		}
		else{
			//Hit nothing, paint it black
			*color = Color(0, 0, 0);
			return;
		}
	}

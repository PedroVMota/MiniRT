#include "center.h" 


double toCanvas(double x, bool isHeight){
	if(isHeight)
		return scene->height / 2 - x;
	return x + scene->width / 2;
}

Ray GetRayDir(Vec3 o, double x, double y){

	Camera *cam = scene->camera;
	Ray ray;
	ray.o = o;
	ray.d.x = x / scene->width * cam->width;
	ray.d.y = y / scene->height * cam->height * scene->camera->aspectRatio;
	ray.d.z = 1;
    ray.o = cam->o;
    ray.val = (tValues){INFINITY, INFINITY};
	ray.ObjectClosest = NULL;
	return ray;
}



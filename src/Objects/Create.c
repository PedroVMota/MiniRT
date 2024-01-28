#include <center.h>

Object *newObject(size_t ModelType, Vec3 o, Vec3 d, Vec4 color, Vec3 theta)
{
	Object *obj = calloc(ModelType, 1);
	obj->o = o;
	obj->d = d;
	obj->color = color;
	obj->theta = theta;
	obj->next = NULL;
	obj->colision = NULL;
	return obj;
}

Sphere *newSphere(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, double diameter, tValues (*colision)()){
	Sphere *s = (Sphere *)newObject(sizeof(Sphere), o, d, color, theta);
	s->diameter = diameter;
	s->type = SPHERE;
	s->colision = colision;
	return s;
}

Plane *newPlane(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, float size, tValues (*colision)()){
	Plane *p = (Plane *)newObject(sizeof(Plane), o, d, color, theta);
	p->size = size;
	p->type = PLANE;
	p->colision = colision;
	return p;
}

Camera *newCamera(Vec3 o, Vec3 d, double fov, Vec3 theta){
	Camera *c = (Camera *)calloc(1, sizeof(Camera));
	c->o = o;
	c->d = d;
	c->fov = fov;
	c->theta = theta;
	c->type = CAMERA;
    c->aspectRatio = scene->width / scene->height;
    c->height = (tan(c->fov / 2 * M_PI / 180) * 2);
    c->width = c->height * c->aspectRatio;
	return c;
}

Light *newLight(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, double intensity, int type){

	Light *l = (Light *)newObject(sizeof(Light), o, d, color, theta);
	l->intensity = intensity;
	l->type = type;
	return l;
}
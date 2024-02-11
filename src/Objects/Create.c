#include <center.h>

Object *newObject(size_t ModelType, Vec3 o, Vec3 d, Vec4 color, Vec3 theta){
	Object *obj = calloc(ModelType, 1);
	obj->o = o;
	obj->d = d;
	obj->color = newrgb(color.r, color.g, color.b);
	obj->theta = theta;
	obj->next = NULL;
	obj->colision = NULL;
	return obj;
}

Sphere *newSphere(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, double diameter, tValues (*colision)(), double reflec, double specular){	Sphere *s = (Sphere *)newObject(sizeof(Sphere), o, d, color, theta);
	s->diameter = diameter;
	s->type = SPHERE;
	s->colision = colision;
    s->reflection = reflec;
    s->specular = specular;
    s->color =(int)(color.r) << 16 | (int)(color.g) << 8 | (int)(color.b);
	return s;
}

Plane *newPlane(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, float size, tValues (*colision)(), double reflec, double specular, int checkerboard){	Plane *p = (Plane *)newObject(sizeof(Plane), o, d, color, theta);
	p->size = size;
	p->type = PLANE;
	p->colision = colision;
    p->reflection = reflec;
    p->specular = specular;
    p->checkerboard = checkerboard;
	return p;
}

Camera *newCamera(Vec3 o, Vec3 d, double fov, Vec3 theta){	Camera *c = (Camera *)calloc(1, sizeof(Camera));
	c->o = o;
	c->d = d;
	c->fov = fov;
	c->theta = theta;
	c->type = CAMERA;
    c->aspectRatio = g_scene->width / g_scene->height;
    c->height = c->height * c->aspectRatio;
    c->width = (tan(c->fov / 2 * M_PI / 180) * 2);
	return c;
}

Light *newLight(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, double intensity, int type)
{

	Light *l = (Light *)newObject(sizeof(Light), o, d, color, theta);

	l->i = intensity;
	l->type = type;
	return l;
}

Cylinder *newCylinder(Vec3 o, Vec3 d, double diameter, double height, Vec4 color, Vec3 theta, tValues (*colision)(), double reflec, double specular){
    Cylinder *c = (Cylinder *)newObject(sizeof(Cylinder), o, d, color, theta);
    c->diameter = diameter;
    c->height = height;
    c->type = CYLINDER;
    c->colision = colision;
    c->reflection = reflec;
    c->specular = specular;
    return c;
}

Paraboloid *newParaboloid(Vec3 o, Vec4 color, double p, double height, double diameter, tValues (*collision)(), double reflection, double specular)
{
    Paraboloid *paraboloid = (Paraboloid *)newObject(sizeof(Paraboloid), o, (Vec3){1, 1, 0}, color, (Vec3){0, 0, 0});
    if (!paraboloid)
        return (NULL);
    printf("Paraboloid\n");
    paraboloid->o = o;
    paraboloid->color =(int)(color.r) << 16 | (int)(color.g) << 8 | (int)(color.b);
    paraboloid->p = p;
    paraboloid->height = height;
    paraboloid->diameter = diameter;
    paraboloid->colision = collision;
    paraboloid->reflection = reflection;
    paraboloid->specular = specular;
    paraboloid->type = PARABOLOID;
    return paraboloid;
}
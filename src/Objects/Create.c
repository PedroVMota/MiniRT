#include <StandarLibrarys.h>

void *object_error_handler(Object *obj, void **ptr, char *msg);

Object *newObject(size_t targetsize)
{
	Object	*obj;

	(obj) = ft_calloc(targetsize, 1);
	(obj)->o = (Vec3){0, 0, 0};
	(obj)->d = (Vec3){0, 0, 0};
	(obj)->color = 0x00ffffff;
	(obj)->theta = (Vec3){0, 0, 0};
	(obj)->next = NULL;
	return (obj);
}

Sphere *newSphere(int type, char **props)
{
	Sphere	*s;
	Vec3	color;

	s = (Sphere *)newObject(sizeof(Sphere));
	s->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	s->diameter = getFloat(props[2], true, (float []){INT16_MAX / 3, 0}, 1);
	color = getVec4(props[3], true, 255, 0);
	s->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	s->type = type;
	if(props[4])
	{
		s->specular = (int)getFloat(props[4], true, (float []){1000, 0}, 1);
		if(!g_scene->error)
			s->reflection = getFloat(props[5], true, (float []){1, 0}, 0);
	}
	s->colision = (tValues (*)(struct Object *, struct Ray)) spherecolision;
	s->next = NULL;
	return 	((Sphere *)object_error_handler((Object *)s, (void **)props, "-> Invalid sphere"));
}

Plane *newPlane(int type, char **props)
{
	Vec3	color;
	Plane	*p;

	p = (Plane *)newObject(sizeof(Plane));
	p->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	p->d = getVec4(props[1], true, 1, -1);
	color = getVec4(props[1], true, 255, 0);
	p->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	if(props[4])
	{
		p->specular = getFloat(props[4], true, (float []){1000, 0}, 0);
		p->reflection = getFloat(props[5], true, (float []){1, 0}, 0);
		p->checkerboard = getFloat(props[6], true, (float []){1, 0}, 0);
	}
	p->colision = planecolision;
	p->next = NULL;
	return (Plane *)object_error_handler((Object *)p, (void **)props, "-> Invalid plane");
}

Camera *newCamera(int type, char **props)
{
	Camera *c;

	printprops(props, "Data", __func__);
	c = (Camera *)newObject(sizeof(Camera));
	c->type = CAMERA;
	c->aspectRatio = (float)g_scene->width / (float)g_scene->height;
	c->height = (tan(c->fov / 2 * M_PI / 180) * 2);
	c->width = c->height * c->aspectRatio;
	c->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	c->theta = getVec4(props[2], true, 1, -1);
	c->fov = getFloat(props[3], true, (float []){180, 0}, 1);
	c->next = NULL;
	return (Camera *)object_error_handler((Object *)c, (void **)props, "-> Invalid Camera");
}



 Cylinder *newCylinder(int type, char **props)
{
	Cylinder *c = (Cylinder *)newObject(sizeof(Cylinder));
 	c->type = CYLINDER;
	c->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	c->d = getVec4(props[2], true, 1, -1);
	c->diameter = getFloat(props[3], true, (float []){INT16_MAX / 3, 0}, 1);
 	c->height = getFloat(props[4], true, (float []){INT16_MAX / 3, 0}, 1);
	if(props[5])
	{
 		c->reflection = getFloat(props[5], true, (float []){1, 0}, 0);
 		c->specular = getFloat(props[6], true, (float []){1000, 0}, 0);
	}
 	c->colision = cylindercolision;
 	return (Cylinder *)object_error_handler((Object *)c, (void **)props, "-> Invalid Cylinder");
 }
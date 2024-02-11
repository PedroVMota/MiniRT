#include <StandarLibrarys.h>

void *object_error_handler(Object *obj, void **ptr, char *msg);

Object *newObject(size_t targetsize, tValues (*colision)(struct Object *, Ray))
{
	Object	*obj;

	(obj) = ft_calloc(targetsize, 1);
	(obj)->colision = colision;
	(obj)->d = (Vec3){0, 0, 0};
	(obj)->next = NULL;
	return (obj);
}

Sphere *newSphere(int type, char **props)
{
	Sphere	*s;
	Vec3	color;

	s = (Sphere *)newObject(sizeof(Sphere), spherecolision);
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
	s->next = NULL;
	return 	((Sphere *)object_error_handler((Object *)s, (void **)props, "-> Invalid sphere"));
}

Plane *newPlane(int type, char **props)
{
	Vec3	color;
	Plane	*p;

	p = (Plane *)newObject(sizeof(Plane) , (tValues (*)(struct Object *, struct Ray))planecolision);
	p->type = type;
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
	p->next = NULL;
	return (Plane *)object_error_handler((Object *)p, (void **)props, "-> Invalid plane");
}

/*
	To calculate the:

	aspect = width / height -> just divide the width by the height
	height = tan(fov / 2 * M_PI / 180) -> fov is the field of view, it's the angle of the camera
	width = aspect * height -> the width is the aspect times the height to keep the aspect ratio
*/
Camera *newCamera(int type, char **props)
{
	Camera *c;

	c = (Camera *)newObject(sizeof(Camera), NULL);
	c->type = CAMERA;
	c->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	c->d = getVec4(props[2], true, 1, -1);
	c->theta = getVec4("0,0,0", true, 1, -1);
	c->fov = getFloat(props[3], true, (float []){180, 0}, 1);
	c->aspect = (double)g_scene->width / (double)g_scene->height;
	c->height = tan(c->fov / 2 * M_PI / 180);
	c->width = c->aspect * c->height;
	c->next = NULL;
	printf("============================= %d =============================\n", g_scene->error);
	return (Camera *)object_error_handler((Object *)c, (void **)props, "-> Invalid Camera");
}



Cylinder *newCylinder(int type, char **props)
{
	Cylinder *c = (Cylinder *)newObject(sizeof(Cylinder) , (tValues (*)(struct Object *, struct Ray))cylindercolision);
 	c->type = CYLINDER;
	c->type = type;
	c->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	c->d = getVec4(props[2], true, 1, -1);
	c->diameter = getFloat(props[3], true, (float []){INT16_MAX / 3, 0}, 1);
 	c->height = getFloat(props[4], true, (float []){INT16_MAX / 3, 0}, 1);
 	c->colision = (tValues (*)(struct Object *, struct Ray))cylindercolision;
	if(props[5])
	{
 		c->reflection = getFloat(props[5], true, (float []){1, 0}, 0);
 		c->specular = getFloat(props[6], true, (float []){1000, 0}, 0);
	}
 	return (Cylinder *)object_error_handler((Object *)c, (void **)props, "-> Invalid Cylinder");
 }
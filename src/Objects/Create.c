#include <center.h>

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



// Cylinder *newCylinder(Vec3 o, Vec3 d, double diameter, double height, Vec4 color, Vec3 theta, tValues (*colision)(), double reflec, double specular){
// 	Cylinder *c = (Cylinder *)newObject(sizeof(Cylinder), o, d, color, theta);
// 	c->diameter = diameter;
// 	c->height = height;
// 	c->type = CYLINDER;
// 	c->colision = colision;
// 	c->reflection = reflec;
// 	c->specular = specular;
// 	return c;
// }

// Vec3 calculateNormal(Vec3 v0, Vec3 v1, Vec3 v2) {
// 	Vec3 edge1 = sub(v1, v0);
// 	Vec3 edge2 = sub(v2, v0);
// 	Vec3 normal = cross(edge1, edge2);
// 	return norm(normal);
// }

// Pyramid *newPyramid(Vec3 o, Vec3 d, double width, double height, Vec4 color, double angle, tValues (*colision)(), double reflec, double specular)
// {
// 	Vec3 rotation = {0, angle, 0}; // Rotate around the y-axis
// 	Pyramid *p = (Pyramid *)newObject(sizeof(Pyramid), o, d, color, rotation);
// 	p->width = width;
// 	p->height = height;
// 	p->type = PYRAMID;
// 	p->colision = colision;
// 	p->reflection = reflec;
// 	p->specular = specular;

// 	// Define os vértices da pirâmide.
// 	double halfWidth = width / 2;
// 	p->vertices[0] = (Vec3){0, height, 0}; // Top vertex
// 	p->vertices[1] = (Vec3){-halfWidth, 0, -halfWidth}; // Base vertices
// 	p->vertices[2] = (Vec3){halfWidth, 0, -halfWidth};
// 	p->vertices[3] = (Vec3){halfWidth, 0, halfWidth};
// 	p->vertices[4] = (Vec3){-halfWidth, 0, halfWidth};

// 	// Rotate the vertices according to the direction
// 	for (int i = 0; i < 5; i++) {
// 		p->vertices[i] = rotate(p->vertices[i], d, angle);
// 		p->vertices[i] = add(p->vertices[i], o); // Add the base center position back
// 	}

// 	// Define as normais das faces da pirâmide.
// 	for (int i = 1; i <= 4; i++) {
// 		Vec3 v0 = p->vertices[0];
// 		Vec3 v1 = p->vertices[i];
// 		Vec3 v2 = p->vertices[i % 4 + 1];
// 		p->normals[i-1] = calculateNormal(v0, v1, v2);
// 	}

// 	// Define os vértices e normais dos triângulos da base.
// 	p->vertices[5] = p->vertices[1];
// 	p->vertices[6] = p->vertices[2];
// 	p->vertices[7] = p->vertices[3];
// 	p->normals[4] = calculateNormal(p->vertices[5], p->vertices[6], p->vertices[7]);

// 	p->vertices[8] = p->vertices[1];
// 	p->vertices[9] = p->vertices[3];
// 	p->vertices[10] = p->vertices[4];
// 	p->normals[5] = calculateNormal(p->vertices[8], p->vertices[9], p->vertices[10]);
// 	p->reflection = reflec;
// 	return p;
// }
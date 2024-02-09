#include <center.h>

bool	float_requirements(char *s, int start, int end);
bool	vector_requirements(char *s);
void	printprops(char **line, char *name, const char *funcname);

static Vec3 newvec4(char *s, float max, float min)
{
	Vec3 v;
	char **split;

	if(!vector_requirements(s))
	{
		printf("%sError: %sInvalid Vec3 value: %s%s: syntax error", RED, RESET, s, RED);
		g_scene->error = 1;
		return (Vec3){0,0,0};
	}
	split = ft_split(s, ',');
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	if (v.x > max || v.x < min || v.y > max || v.y < min || v.z > max ||
		v.z < min)
	{
		printf("%sError: %sInvalid Vec value: %s%s: how fo range", RED, RESET, s, RED);
		g_scene->error = 1;
		return (v);
	}
	delprops(split);
	return (v);
}
static double newfloat(char *s, float max, float min)
{
	double f;

	if(float_requirements(s, 0, ft_strlen(s) - 1))
	{
		printf("%sError: %sInvalid float value: %s%s: Syntax Error", RED, RESET, s, RED);
		g_scene->error = 1;
		return (0);
	}
	f = ft_atof(s);
	if (f > max || f < min)
	{
		printf("%sError: %sInvalid float value: %s%s: out of range", RED, RESET, s, RED);
		g_scene->error = 1;
		return (0);
	}
	return (f);
}

void *object_error_handler(Object *obj, void **ptr, char *msg)
{

	delprops((char **)ptr);
	if(g_scene->error)
	{
		if(msg)
			printf("%s%s%s\n", RED, msg, RESET);
		free(obj);
		return NULL;
	}
	return obj;
}


Object *newObject(void){

	Object	*obj;

	obj = ft_calloc(sizeof(Object), 1);
	obj->o = (Vec3){0, 0, 0};
	obj->d = (Vec3){0, 0, 0};
	obj->color = 0x00ffffff;
	obj->theta = (Vec3){0, 0, 0};
	obj->next = NULL;
	obj->colision = NULL;
	return (obj);
}

Sphere *newSphere(int type, char **props)
{
	Sphere	*s;
	Vec3	color;

	printprops(props, "Data", __func__);
	s = (Sphere *)newObject();
	s->o = newvec4(props[1], INT16_MAX, -INT16_MAX);
	s->diameter = (double)newfloat(props[2], INT16_MAX, 0);
	color = newvec4(props[3], 255, 0);
	s->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	s->type = type;
	s->specular = newfloat(props[4], 1000, 0);
	s->reflection = newfloat(props[5], 1, 0);
	s->colision = (tValues (*)(struct Object *, struct Ray)) spherecolision;
	s->next = NULL;
	return 	((Sphere *)object_error_handler((Object *)s, (void **)props, "-> Invalid sphere"));
}

Plane *newPlane(int type, char **props)
{
	Plane	*p;
	Vec3	color;

	printprops(props, "Data", __func__);
	p = ft_calloc(1, sizeof(Plane));
	p->o = newvec4(props[1], INT16_MAX, -INT16_MAX);
	p->d = newvec4(props[2], 1, -1);
	color = newvec4(props[3], 255, 0);
	p->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	p->colision = (tValues (*)(struct Object *, struct Ray)) planecolision;
	p->specular = newfloat(props[4], 1000, 0);
	p->reflection = newfloat(props[5], 1, 0);
	p->checkerboard = (int)newfloat(props[6], 3, -1);
	return (Plane *)object_error_handler((Object *)p, (void **)props, "-> Invalid plane");
}

Camera *newCamera(int type, char **props)
{
	Camera *c;

	printprops(props, "Data", __func__);
	c = (Camera *)ft_calloc(1, sizeof(Camera));
	c->type = CAMERA;
	c->aspectRatio = g_scene->width / g_scene->height;
	c->height = (tan(c->fov / 2 * M_PI / 180) * 2);
	c->width = c->height * c->aspectRatio;
	c->o = newvec4(props[1], INT16_MAX, -INT16_MAX);
	c->theta = newvec4(props[2], 1, 0);
	c->fov = newfloat(props[3], 100, 12);
	return (Camera *)object_error_handler((Object *)c, (void **)props, "-> Invalid Camera");

}

// Light *newLight(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, double intensity, int type)
// {

// 	Light *l = (Light *)newObject(sizeof(Light), o, d, color, theta);

// 	l->i = intensity;
// 	l->type = type;
// 	return l;
// }

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
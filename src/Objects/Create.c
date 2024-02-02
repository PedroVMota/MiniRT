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

Sphere *newSphere(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, double diameter, tValues (*colision)(), double reflec){
	Sphere *s = (Sphere *)newObject(sizeof(Sphere), o, d, color, theta);
	s->diameter = diameter;
	s->type = SPHERE;
	s->colision = colision;
    s->reflection = reflec;
	return s;
}

Plane *newPlane(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, float size, tValues (*colision)(), double reflec){
	Plane *p = (Plane *)newObject(sizeof(Plane), o, d, color, theta);
	p->size = size;
	p->type = PLANE;
	p->colision = colision;
    p->reflection = reflec;
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

Cylinder *newCylinder(Vec3 o, Vec3 d, double diameter, double height, Vec4 color, Vec3 theta, tValues (*colision)(), double reflec)
{
    Cylinder *c = (Cylinder *)newObject(sizeof(Cylinder), o, d, color, theta);
    c->diameter = diameter;
    c->height = height;
    c->type = CYLINDER;
    c->colision = colision;
    c->reflection = reflec;
    return c;
}

Vec3 calculateNormal(Vec3 v0, Vec3 v1, Vec3 v2) {
    Vec3 edge1 = Sub(v1, v0);
    Vec3 edge2 = Sub(v2, v0);
    Vec3 normal = Cross(edge1, edge2);
    return Normalize(normal);
}

Pyramid *newPyramid(Vec3 o, Vec3 d, double width, double height, Vec4 color, double angle, tValues (*colision)(), double reflec)
{
    Vec3 rotation = {0, angle, 0}; // Rotate around the y-axis
    Pyramid *p = (Pyramid *)newObject(sizeof(Pyramid), o, d, color, rotation);
    p->width = width;
    p->height = height;
    p->type = PYRAMID;
    p->colision = colision;

    // Define os vértices da pirâmide.
    double halfWidth = width / 2;
    p->vertices[0] = (Vec3){0, height, 0}; // Top vertex
    p->vertices[1] = (Vec3){-halfWidth, 0, -halfWidth}; // Base vertices
    p->vertices[2] = (Vec3){halfWidth, 0, -halfWidth};
    p->vertices[3] = (Vec3){halfWidth, 0, halfWidth};
    p->vertices[4] = (Vec3){-halfWidth, 0, halfWidth};

    // Rotate the vertices according to the direction
    for (int i = 0; i < 5; i++) {
        p->vertices[i] = rotate(p->vertices[i], d, angle);
        p->vertices[i] = Add(p->vertices[i], o); // Add the base center position back
    }

    // Define as normais das faces da pirâmide.
    for (int i = 1; i <= 4; i++) {
        Vec3 v0 = p->vertices[0];
        Vec3 v1 = p->vertices[i];
        Vec3 v2 = p->vertices[i % 4 + 1];
        p->normals[i-1] = calculateNormal(v0, v1, v2);
    }

    // Define os vértices e normais dos triângulos da base.
    p->vertices[5] = p->vertices[1];
    p->vertices[6] = p->vertices[2];
    p->vertices[7] = p->vertices[3];
    p->normals[4] = calculateNormal(p->vertices[5], p->vertices[6], p->vertices[7]);

    p->vertices[8] = p->vertices[1];
    p->vertices[9] = p->vertices[3];
    p->vertices[10] = p->vertices[4];
    p->normals[5] = calculateNormal(p->vertices[8], p->vertices[9], p->vertices[10]);
    p->reflection = reflec;
    return p;
}
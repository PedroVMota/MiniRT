#include "center.h"

Vec4 getBackgroundColor(Ray raytrace)
{
    Vec4 color = (Vec4){0, 0, 0, 0};
    Vec3 unit_direction = unitVector(raytrace.d);
    double t = 0.5 * (unit_direction.y + 1.0);
    unsigned int white = 0xFFFFFF; // RGB white
    unsigned int blue = 0x7FB2FF;  // RGB blue
    color.r = (unsigned int)((1.0 - t) * ((white >> 16) & 0xFF) + t * ((blue >> 16) & 0xFF));
    color.g = (unsigned int)((1.0 - t) * ((white >> 8) & 0xFF) + t * ((blue >> 8) & 0xFF));
    color.b = (unsigned int)((1.0 - t) * (white & 0xFF) + t * (blue & 0xFF));
    return color;
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

void objectAdd(Object *nObj, Object **lst)
{
    if (!*lst)
    {
        *lst = nObj;
        return;
    }
    Object *tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = nObj;
}

Vec3 normalCalc(Object *obj, Vec3 p)
{
    Vec3 normal;
    normal = (Vec3){0, 0, 0};
    if (!obj)
        return normal;
    if (obj->type == SPHERE)
    {
        normal = Sub(p, (obj)->o);
        normal = Normalize(normal);
    }
    else if (obj->type == PLANE)
        normal = ((Plane *)obj)->d;
    else if (obj->type == CYLINDER)
    {
        Cylinder *c = (Cylinder *)obj;
        Vec3 oc = Sub(p, c->o);
        double t = Dot(oc, c->d);
        normal = Sub(oc, Mul(c->d, t));
        normal = Normalize(normal);
        
    }
    return normal;
}

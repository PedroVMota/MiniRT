#include "center.h"



Ray GetRayDir(Vec3 o, double x, double y){

	Camera *cam = scene->camera;
	Ray ray;
	ray.o = o;
	ray.d.x = x / scene->width * cam->width;
	ray.d.y = y / scene->height;
	ray.d.z = 1;
    ray.o = cam->o;
    ray.val = (tValues){INFINITY, INFINITY};
	ray.ObjectClosest = NULL;
	return ray;
}

void objectAdd(Object *nObj, Object **lst)
{
    if(!nObj)
        return;
    if(nObj->type == AMBIENT)
    {
        if(!scene->am)
            scene->am = (Light *)nObj;
        else
            free(nObj);   
        return;
    }
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
        if (t < 0.001 || t > c->height - 0.001)
            normal = c->d; // Cap normal
        else
        {
            normal = Sub(oc, Mul(c->d, t));
            normal = Normalize(normal);
        }
        
    }
    else if (obj->type == PYRAMID)
    {
        Pyramid *pyr = (Pyramid *)obj;
        normal = Sub(p, pyr->d);
        normal = Normalize(normal);
    }

    return normal;
}

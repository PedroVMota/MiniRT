#include <StandarLibrarys.h>

void ShowCamera(Camera *cam) {
    printf("Camera:\n");
    printf("Position: (%lf, %lf, %lf)\n", cam->o.x, cam->o.y, cam->o.z);
    printf("Direction: (%lf, %lf, %lf)\n", cam->d.x, cam->d.y, cam->d.z);
    printf("Color: %d\n", cam->color);
    printf("Theta: (%lf, %lf, %lf)\n", cam->theta.x, cam->theta.y, cam->theta.z);
    printf("Type: %d\n", cam->type);
    printf("Specular: %lf\n", cam->specular);
    printf("Reflection: %lf\n", cam->reflection);
    printf("Diameter: %lf\n", cam->diameter);
    printf("Height: %lf\n", cam->height);
    printf("Width: %lf\n", cam->width);
    printf("Fov: %lf\n", cam->fov);
    printf("Aspect: %lf\n", cam->aspect);
}

void ShowSphere(Sphere *sphere) {
    printf("Sphere:\n");
    printf("Position: (%lf, %lf, %lf)\n", sphere->o.x, sphere->o.y, sphere->o.z);
    printf("Direction: (%lf, %lf, %lf)\n", sphere->d.x, sphere->d.y, sphere->d.z);
    printf("Color: %d\n", sphere->color);
    printf("Theta: (%lf, %lf, %lf)\n", sphere->theta.x, sphere->theta.y, sphere->theta.z);
    printf("Type: %d\n", sphere->type);
    printf("Specular: %lf\n", sphere->specular);
    printf("Reflection: %lf\n", sphere->reflection);
    printf("Diameter: %lf\n", sphere->diameter);
}

void ShowPlane(Plane *plane) {
    printf("Plane:\n");
    printf("Position: (%lf, %lf, %lf)\n", plane->o.x, plane->o.y, plane->o.z);
    printf("Direction: (%lf, %lf, %lf)\n", plane->d.x, plane->d.y, plane->d.z);
    printf("Color: %d\n", plane->color);
    printf("Theta: (%lf, %lf, %lf)\n", plane->theta.x, plane->theta.y, plane->theta.z);
    printf("Type: %d\n", plane->type);
    printf("Specular: %lf\n", plane->specular);
    printf("Reflection: %lf\n", plane->reflection);
    printf("Diameter: %lf\n", plane->diameter);
}

void ShowLight(Light *light) {
    printf("Light:\n");
    printf("Position: (%lf, %lf, %lf)\n", light->o.x, light->o.y, light->o.z);
    printf("Direction: (%lf, %lf, %lf)\n", light->d.x, light->d.y, light->d.z);
    printf("Color: %d\n", light->color);
    printf("Theta: (%lf, %lf, %lf)\n", light->theta.x, light->theta.y, light->theta.z);
    printf("Type: %d\n", light->type);
    printf("Specular: %lf\n", light->specular);
    printf("Reflection: %lf\n", light->reflection);
    printf("Diameter: %lf\n", light->diameter);
    printf("Intensity: %lf\n", light->i);
}

void ShowCylinder(Cylinder *cylinder) {
    printf("Cylinder:\n");
    printf("Position: (%lf, %lf, %lf)\n", cylinder->o.x, cylinder->o.y, cylinder->o.z);
    printf("Direction: (%lf, %lf, %lf)\n", cylinder->d.x, cylinder->d.y, cylinder->d.z);
    printf("Color: %d\n", cylinder->color);
    printf("Theta: (%lf, %lf, %lf)\n", cylinder->theta.x, cylinder->theta.y, cylinder->theta.z);
    printf("Type: %d\n", cylinder->type);
    printf("Specular: %lf\n", cylinder->specular);
    printf("Reflection: %lf\n", cylinder->reflection);
    printf("Diameter: %lf\n", cylinder->diameter);
    printf("Height: %lf\n", cylinder->height);
}

void ShowGeneralInfo(void)
{
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int in = dup(1);
    dup2(fd, 1);
    printf("General Info:\n");
    for(Object *obj = g_scene->objects; obj; obj = obj->next)
    {
        if(obj->type == SPHERE)
            ShowSphere((Sphere *)obj);
        else if(obj->type == PLANE)
            ShowPlane((Plane *)obj);
        else if(obj->type == CYLINDER)
            ShowCylinder((Cylinder *)obj);
    }
    printf("\n");

    for(Light *light = g_scene->lights; light; light = light->next)
        ShowLight(light);

    

    printf("\n");
    ShowCamera(g_scene->camera);
    dup2(in, 1);
    close(fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/01/29 18:51:19 by pedro            ###   ########.fr       */
/*                                                \                            */
/* ************************************************************************** */

#include "center.h"

gscene *scene = NULL;
Vec4 getBackgroundColor(Ray raytrace);
Vec3 normalCalc(Object *obj, Vec3 p);

Object *getClosestObject(Ray *rayTrace, double maxDistance, double minDistance, bool updateData)
{
	double ct = INFINITY;
	Object *closest = NULL;
	for (Object *lst = scene->objects; lst; lst = lst->next)
	{
		rayTrace->val = lst->colision(lst, *rayTrace);
		if ((rayTrace->val.t0 > minDistance && rayTrace->val.t0 < maxDistance) && rayTrace->val.t0 < ct)
		{
			closest = lst;
			ct = rayTrace->val.t0;
		}
		else if ((rayTrace->val.t1 > minDistance && rayTrace->val.t1 < maxDistance) && rayTrace->val.t1 < ct)
		{
			closest = lst;
			ct = rayTrace->val.t1;
		}
	}
    if(updateData){
        rayTrace->normal = normalCalc(closest, Add(rayTrace->o, Mul(rayTrace->d, ct)));
        rayTrace->ct = ct;
        rayTrace->HitPoint = Add(rayTrace->o, Mul(rayTrace->d, ct));
    }
	return closest;
}

Vec3 Multiply(double scalar, Vec3 vector) {
    Vec3 result;
    result.x = scalar * vector.x;
    result.y = scalar * vector.y;
    result.z = scalar * vector.z;
    return result;
}

double calculateLighting(Vec3 point, Vec3 normal, Vec3 Hitpoint, double specular)
{
    Light *l = scene->lights;
    if (!l)
        return 0;
    double intensity = 0;
    double length_n = Length(normal); // Corrected typo
    Vec3 vec_l;

    while (l)
    {
        if (l->type == AMBIENT)
            intensity += l->intensity;
        else
        {
            vec_l = Sub(l->o, Hitpoint);
            vec_l = Normalize(vec_l);
            Ray lightVector;

            lightVector.o = Hitpoint;
            lightVector.d = Sub(l->o, Hitpoint);
            if(getClosestObject(&lightVector, 1, 0.001, false)){
                l = (Light *)l->next;
                continue;
            }
            double n_dot_l = Dot(normal, vec_l);
            if (n_dot_l > 0)
                intensity += l->intensity * n_dot_l / (Length(vec_l) * length_n);

            if (specular != -1) {
                Vec3 viewDirection = Mul(point, -1); // Assuming this is your view direction
                Vec3 reflection = Reflect(viewDirection, normal);
                double r_dot_v = Dot(reflection, vec_l);

                if (r_dot_v > 0) {
                    double specularFactor = pow(r_dot_v / (Length(reflection) * Length(vec_l)), specular);
                    intensity += l->intensity * specularFactor;
                }
            }
        }
        l = (Light *)l->next;
    }
    return intensity;
}

//double calculateLighting(Vec3 point, Vec3 normal, Vec3 view, double specular)
//{
//    Light *l = scene->lights;
//	view = Multiply(-1, view);
//    if (!l)
//        return 0;
//    double intensity = 0;
//    double length_n = Length(normal);
//    double length_v = Length(view);
//    Vec3 vec_l, vec_r;
//    double r_dot_v;
//
//    while (l)
//    {
//        if (l->type == AMBIENT)
//            intensity += l->intensity;
//        else
//        {
//            if (l->type == POINT) {
//                vec_l = Sub(l->o, point);
//            } else if (l->type == DIRECTIONAL) {
//                vec_l = l->o;
//            }
//            vec_l = Normalize(vec_l);
//            Ray lightVector;
//
//            lightVector.o = view;
//          lightVector.d = Sub(l->o, view);
//          if(getClosestObject(&lightVector, 1, 0.001, false)){
//                l = (Light *)l->next;
//                continue;
//            }
//
//            double n_dot_l = Dot(normal, vec_l);
//            if (n_dot_l > 0.001)
//                intensity += l->intensity * n_dot_l / (Length(vec_l) * length_n);
//
//            if (specular != -1) {
//                vec_r = Sub(Multiply(2.0 * Dot(normal, vec_l), normal), vec_l);
//                vec_r = Normalize(vec_r);  // Normalize the reflection vector
//                r_dot_v = Dot(vec_r, view);
//                if (r_dot_v > 0)
//                    intensity += l->intensity * pow(r_dot_v / (Length(vec_r) * length_v), specular);
//            }
//        }
//        l = (Light *)l->next;
//    }
//    return intensity;
//}

Vec4 RayColor(Ray rayTrace, int depth)
{
    if (depth <= 0)
        return (Vec4){0, 0, 0, 0}; // cor preta para profundidade máxima

    Vec4 CurrentColor = getBackgroundColor(rayTrace);
    Object *obj = getClosestObject(&rayTrace, INFINITY, 0, true);
    if (!obj)
        return Mul4(CurrentColor, 0);
    Vec4 objectColor = obj->color;
    if (Dot(rayTrace.d, rayTrace.normal) > 0)
        rayTrace.normal = Mul(rayTrace.normal, -1);
    double i = calculateLighting(rayTrace.o, rayTrace.normal, rayTrace.HitPoint, 200);
    objectColor.r *= i;
    objectColor.g *= i;
    objectColor.b *= i;

    // Adicionando reflexão
    // Adicionando reflexão
double reflection = 0;
if (obj->type == SPHERE)
    reflection = ((Sphere *)obj)->reflection;
else if (obj->type == PLANE)
    reflection = ((Plane *)obj)->reflection;
else if (obj->type == CYLINDER)
    reflection = ((Cylinder *)obj)->reflection;
else if (obj->type == PYRAMID)
    reflection = ((Pyramid *)obj)->reflection;
// Adicione mais condições aqui para outros tipos de objetos que têm um campo de reflexão

if (reflection > 0) {
    Vec3 reflectionDirection = Reflect(Normalize(rayTrace.d), rayTrace.normal);
    Ray reflectionRay;
    reflectionRay.o = Add(rayTrace.HitPoint, Mul(rayTrace.normal, 0.0001)); // Move a origem do raio de reflexão um pouco na direção da normal
    reflectionRay.d = reflectionDirection;
    Vec4 reflectionColor = RayColor(reflectionRay, depth - 1); // Chamada recursiva para calcular a cor de reflexão
    objectColor = Add4(Mul4(objectColor, 1 - reflection), Mul4(reflectionColor, reflection)); 
}

    return objectColor;
}

void renderFrame()
{
	// Calculate teh vector across the horizontal and down the vertical viewport edges.
	// Calculate the horizontal and vertical delta vector form the pixel to pixel.
	// calculate the location of the upper left pixel.
	for (double y = scene->height / 2; y > -scene->height / 2; y--)
	{
		for (double x = -scene->width / 2; x < scene->width / 2; x++)
		{
			Ray ray = GetRayDir((scene->camera)->o, x, y);
			Vec4 color = RayColor(ray, 4);
			my_mlx_pixel_put(toCanvas(x, false), toCanvas(y, true), color);
		}
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img, 0, 0);
	printf("\rDone.\n");
}

#ifdef __APPLE__
#define UP 126
#define DOWN 125
#define LEFT 123
#define RIGHT 124
#define ESC 53
#define W 13
#define A 0
#define S 1
#define D 2
#define SPACE 49
#else
#define SPACE 32 // 49
#define UP 65362	// 126
#define DOWN 65364	// 125
#define LEFT 65361	// 123
#define RIGHT 65363 // 124
#define ESC 65307	// 53
#define W 119		// 13
#define A 97		// 0
#define S 115		// 1 D // 2
#define D 100
#endif


Object *selected = NULL;

void changeSelector(int keycode) {
    static int selector = 0;

    if (keycode == SPACE) {
        selector++;
        if (selector == 3)
            selector = 0;
        printf("Changing Selector %d\n", selector);
    }
    if (selector == 0)
        selected = (Object *) scene->lights;
    if (selector == 1)
        selected = scene->objects;
    if(selector == 2)
        selected = (Object *)scene->camera;
}
int keyhook(int keycode)
{
	printf("keycode: %d\n", keycode);
    if(keycode == SPACE || selected == NULL)
        changeSelector(keycode);
    printf("selected %f\n", selected->o.y);
	if (keycode == UP)
		selected->o.z += 0.1;
	if (keycode == DOWN)
        selected->o.z -= 0.1;
	if (keycode == LEFT)
        selected->o.x -= 0.1;
	if (keycode == RIGHT)
        selected->o.x += 0.1;
	if (keycode == W)
        selected->o.y += 0.1;
	if (keycode == S)
        selected->o.y -= 0.1;
	if (keycode == ESC)
	{
		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
#ifndef __APPLE__
		mlx_destroy_display(scene->mlx->mlx);
#endif
		free(scene->mlx->mlx);
		free(scene->mlx);
		exit(0);
	}
    if(keycode == SPACE || keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT || keycode == W || keycode == S)
        renderFrame();
	return 0;
}
//
//int main(void)
//{
//	scene = init_MainStruct(250, 250);
//    if(!scene)
//        return 1;
//
//    objectAdd(
//            (Object *)newCamera(
//                    (Vec3){0, 0, -10},
//                    (Vec3){0, -1, 0},
//                    90,
//                    (Vec3){0, 0, 0}),
//            (Object **)&scene->camera);
//    objectAdd(
//            (Object *)newPlane(
//                    (Vec3){0, -1, 0},
//                    (Vec3){0, 1, 0},
//                    (Vec4){0, 255, 255, 255},
//                    (Vec3){0, 0, 0},
//                    1,
//                    planeColision, 0.99),
//            (Object **)&scene->objects);
//    objectAdd(
//			(Object *)newSphere(
//					(Vec3){0, 0, -6},
//					(Vec3){0, 0, 0},
//					(Vec4){0, 255, 255, 0},
//					(Vec3){0, 0, 0},
//					1,
//					sphereColision, 0.7),
//			(Object **)&scene->objects);
//    objectAdd(
//    (Object *)newPyramid(
//        (Vec3){0, 0, -5}, // posição da pirâmide
//        (Vec3){1, 1, 0}, // direção da pirâmide (não usada neste caso)
//        2, // largura da base da pirâmide
//        5, // altura da pirâmide
//        (Vec4){255, 0, 0, 255}, // cor da pirâmide
//        23 * M_PI / 180, // rotação da pirâmide (não usada neste caso)
//        pyramidCollision, 0.6),
//    (Object **)&scene->objects);
//    /*objectAdd(
//            (Object *)newCylinder(
//                    (Vec3){2, 0, -5},
//                    Normalize((Vec3){0, 1, 0}),
//                    1.5,
//                    7,
//                    (Vec4){0, 255, 255, 0},
//                    (Vec3){0, 0, 0},
//                    cylinderColision, 0.8),
//            (Object **)&scene->objects);*/
//    objectAdd(
//			(Object *)newSphere(
//					(Vec3){0, 0, 1},
//					(Vec3){0, 0, 0},
//					(Vec4){0, 255, 0, 0},
//					(Vec3){0, 0, 0},
//					1,
//					sphereColision, 0.5),
//			(Object **)&scene->objects);
//
//    objectAdd(
//            (Object *)newLight(
//                    (Vec3){-2, 0, -5},
//                    (Vec3){0, 0, 0},
//                    (Vec4){0, 255, 255, 255},
//                    (Vec3){0, 0, 0},
//                    0.3,
//                    POINT),
//            (Object **)&scene->lights);
//    objectAdd(
//            (Object *)newLight(
//                    (Vec3){2, 1, -7},
//                    (Vec3){0, 0, 0},
//                    (Vec4){0, 255, 255, 255},
//                    (Vec3){0, 0, 0},
//                    0.3,
//                    POINT),
//            (Object **)&scene->lights);
//
//    objectAdd(
//            (Object *)newLight(
//                    (Vec3){2, 3, -1},
//                    (Vec3){0, 0, 0},
//                    (Vec4){0, 255, 255, 255},
//                    (Vec3){0, 0, 0},
//                    0.3,
//                    AMBIENT),
//            (Object **)&scene->lights);
//	/*objectAdd(
//    (Object *)newLight(
//        (Vec3){1.0, 0.0, 0.0},  // Direction of the directional light
//        (Vec3){0, 0, 0},
//        (Vec4){0, 255, 255, 255},
//        (Vec3){0, 0, 0},
//        0.2,  // Intensity of the directional light
//        DIRECTIONAL),  // Type of the light
//    (Object **)&scene->lights);*/
//
//    renderFrame();
//	mlx_key_hook(scene->mlx->win, keyhook, scene->mlx);
//	// mlx_loop_hook(scene->mlx->mlx, keyhook, NULL);
//	mlx_loop(scene->mlx->mlx);
//	return 0;
//}

int main(int ac, char **av)
{
    if(ac != 2)
        exitProgram("No arguments\n");
    scene = init_MainStruct(500, 250);
    if(!scene)
        return 1;
    if(parseFile(av[1]))
        exitProgram(NULL);

    return 0;
}
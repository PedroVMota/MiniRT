/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycolor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:52:57 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/13 20:54:51 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

Ray	getraydir(Vec3 o, double x, double y)
{
	Camera	*cam;
	Ray		ray;

	cam = g_scene->camera;
	ray.o = o;
	ray.d.x = ((x) / g_scene->width) * cam->width;
	ray.d.y = ((y) / g_scene->height) * cam->height;
	ray.d.z = 1;
	ray.o = cam->o;
	ray.val = (tValues){.t0 = INFINITY, .t1 = INFINITY};
	ray.objc = NULL;
	return (ray);
}

int	compcolor(int obj_color, Vec4 objectColor)
{
	int	r;
	int	g;
	int	b;

	r = ((obj_color >> 16 & 255)) * objectColor.r;
	g = ((obj_color >> 8 & 255)) * objectColor.g;
	b = ((obj_color & 255)) * objectColor.b;
	return (newrgb(r, g, b));
}

static	int	calculreflectcolor(Ray refray, int depth, double reflect, int lc)
{
	int	reflectedcolor;

	reflectedcolor = raycolor(refray, depth - 1);
	lc = newrgb((int)(mulcomp(lc, 16, 1 - reflect) + \
	mulcomp(reflectedcolor, 16, reflect)), (int)(mulcomp(lc, 8, 1 - reflect) + \
	mulcomp(reflectedcolor, 8, reflect)), (int)(mulcomp(lc, 0, 1 - reflect) + \
	mulcomp(reflectedcolor, 0, reflect)));
	return (lc);
}

static	int	calcullocalcolo(Ray rayTrace, Object *obj)
{
	Vec4	objectcolor;

	if (dot(rayTrace.d, rayTrace.normal) > 0)
		rayTrace.normal = mul(rayTrace.normal, -1);
	objectcolor = calcligh(rayTrace._hit, rayTrace.normal, \
	rayTrace.d, obj->specular);
	return (compcolor(obj->color, objectcolor));
}

int	raycolor(Ray rayTrace, int depth)
{
	int		lc;
	Object	*obj;
	double	reflection;
	Vec3	reflected;
	Ray		reflectedray;

	obj = intersections(&rayTrace, INFINITY, 0, true);
	if (!obj)
		return (0);
	lc = calcullocalcolo(rayTrace, obj);
	if (obj->reflection <= 0 || obj->specular <= 0 || depth <= 0)
		return (lc);
	reflection = obj->reflection;
	reflected = reflect(rayTrace.d, rayTrace.normal);
	reflectedray = (Ray){add(rayTrace._hit, mul(reflected, 0.001)), reflected};
	return (calculreflectcolor(reflectedray, depth, reflection, lc));
}

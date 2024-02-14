/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:35:54 by pedro             #+#    #+#             */
/*   Updated: 2024/02/13 19:41:29 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

Sphere	*newsphere(int type, char **props)
{
	Sphere	*s;
	Vec3	color;

	s = (Sphere *)newobject(sizeof(Sphere), spherecolision);
	s->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	s->diameter = getfloat(props[2], true, (float []){INT16_MAX / 3, 0}, 1);
	color = getvec4(props[3], true, 255, 0);
	s->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	s->type = type;
	if (props[4])
	{
		s->specular = (int)getfloat(props[4], true, (float []){1000, 0}, 1);
		if (!g_scene->error && props[5])
			s->reflection = getfloat(props[5], true, (float []){1, 0}, 0);
	}
	s->next = NULL;
	return ((Sphere *)object_error_handler((Object *)s, \
	(void **)props, "-> Invalid sphere\n"));
}

Plane	*newplane(int type, char **props)
{
	Vec3	color;
	Plane	*p;

	p = (Plane *)newobject(sizeof(Plane), \
		(tValues (*)(struct Object *, struct Ray))planecolision);
	p->type = type;
	p->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	p->d = getvec4(props[2], true, 1, -1);
	color = getvec4(props[3], true, 255, 0);
	p->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	if (props[4])
	{
		p->specular = getfloat(props[4], true, (float []){1000, 0}, 0);
		p->reflection = getfloat(props[5], true, (float []){1, 0}, 0);
		p->checkerboard = getfloat(props[6], true, (float []){1, 0}, 0);
	}
	p->next = NULL;
	return ((Plane *)object_error_handler((Object *)p, \
		(void **)props, "-> Invalid plane\n"));
}

Cylinder	*newcylinder(int type, char **props)
{
	Vec3		color;
	Cylinder	*c;

	c = (Cylinder *)newobject(sizeof(Cylinder), \
		(tValues (*)(struct Object *, struct Ray))cylindercolision);
	c->type = CYLINDER;
	c->type = type;
	if(g_scene->error != 2)
		c->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	if(g_scene->error != 2)
		c->d = norm(getvec4(props[2], true, 1, -1));
	if(g_scene->error != 2)
		c->diameter = getfloat(props[3], true, (float []){INT16_MAX / 3, 0}, 1);
	if(g_scene->error != 2)
		c->height = getfloat(props[4], true, (float []){INT16_MAX / 3, 0}, 1);
	if(g_scene->error != 2)
		color = getvec4(props[5], true, 255, 0);
	c->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	c->colision = (tValues (*)(struct Object *, struct Ray))cylindercolision;
	if (props[6])
	{
		c->specular = getfloat(props[6], true, (float []){1000, 0}, 0);
		c->reflection = getfloat(props[7], true, (float []){1, 0}, 0);
	}
	return ((Cylinder *)object_error_handler((Object *)c, \
		(void **)props, "-> Invalid Cylinder\n"));
}

Camera	*newcamera(int type, char **props)
{
	Camera	*c;

	c = (Camera *)newobject(sizeof(Camera), NULL);
	c->type = CAMERA;
	c->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	c->d = getvec4(props[2], true, 1, -1);
	c->theta = getvec4("0,0,0", true, 1, -1);
	c->fov = getfloat(props[3], true, (float []){180, 0}, 1);
	c->aspect = (double)g_scene->width / (double)g_scene->height;
	c->height = tan(c->fov / 2 * M_PI / 180);
	c->width = c->aspect * c->height;
	c->next = NULL;
	return ((Camera *)object_error_handler((Object *)c, (void **)props, \
		"-> Invalid Camera\n"));
}

Paraboloid	*newparaboloid(int type, char **props)
{
	Paraboloid	*paraboloid;
	Vec3		color;

	paraboloid = (Paraboloid *)newobject(sizeof(Paraboloid), \
		(tValues (*)(struct Object *, struct Ray))paraboloidcollision);
	if (!paraboloid)
		return (NULL);
	paraboloid->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	paraboloid->height = getfloat(props[2], true, (float []){INT16_MAX / 3, \
		0}, 1);
	paraboloid->diameter = getfloat(props[3], true, (float []){INT16_MAX / 3, \
		0}, 1);
	paraboloid->p = 1;
	color = getvec4(props[4], true, 255, 0);
	paraboloid->type = type;
	paraboloid->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	if (props[5])
	{
		paraboloid->specular = getfloat(props[5], true, (float []){1000, 0}, 1);
		if (!g_scene->error)
			paraboloid->reflection = getfloat(props[6], true, \
			(float []){1, 0}, 0);
	}
	return ((Paraboloid *)object_error_handler((Object *)paraboloid, \
	(void **)props, "-> Invalid Paraboloid\n"));
}

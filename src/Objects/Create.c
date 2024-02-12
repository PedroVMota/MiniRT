/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:35:54 by pedro             #+#    #+#             */
/*   Updated: 2024/02/12 17:58:01 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

double	getfloat(char *prop, bool required, float *range, int standard_value);
Vec3	getVec4(char *prop, bool required, float max, float min);
void	updateError(char *msg);

void	*object_error_handler(Object *obj, void **ptr, char *msg)
{
	delprops((char **) ptr);
	if (g_scene->error)
	{
		if (msg)
			updateError(msg);
		return (free(obj), NULL);
	}
	return ((void *)obj);
}

Object	*newObject(size_t targetsize, tValues (*colision)(struct Object *, Ray))
{
	Object	*obj;

	(obj) = ft_calloc(targetsize, 1);
	(obj)->colision = colision;
	(obj)->d = (Vec3){0, 0, 0};
	(obj)->next = NULL;
	return (obj);
}

Sphere	*newSphere(int type, char **props){
	Sphere	*s;
	Vec3	color;

	s = (Sphere *)newObject(sizeof(Sphere), spherecolision);
	s->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	s->diameter = getfloat(props[2], true, (float []){INT16_MAX / 3, 0}, 1);
	color = getVec4(props[3], true, 255, 0);
	s->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	s->type = type;
	if (props[4])
	{
		s->specular = (int)getfloat(props[4], true, (float []){1000, 0}, 1);
		if(!g_scene->error)
			s->reflection = getfloat(props[5], true, (float []){1, 0}, 0);
	}
	s->next = NULL;
	return 	((Sphere *)object_error_handler((Object *)s, (void **)props, "-> Invalid sphere"));
}

Plane	*newPlane(int type, char **props){
	Vec3	color;
	Plane	*p;

	p = (Plane *)newObject(sizeof(Plane), \
		(tValues (*)(struct Object *, struct Ray))planecolision);
	p->type = type;
	p->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	p->d = getVec4(props[2], true, 1, -1);
	color = getVec4(props[3], true, 255, 0);
	p->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	if (props[4])
	{
		p->specular = getfloat(props[4], true, (float []){1000, 0}, 0);
		p->reflection = getfloat(props[5], true, (float []){1, 0}, 0);
		p->checkerboard = getfloat(props[6], true, (float []){1, 0}, 0);
	}
	p->next = NULL;
	return ((Plane *)object_error_handler((Object *)p, \
		(void **)props, "-> Invalid plane"));
}

static void	setup_am(char **p, Light *l)
{
	Vec3	color;

	l->i = getfloat(p[1], true, (float []){1, 0}, 0);
	color = getVec4(p[2], true, 255, 0);
	l->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	l->next = NULL;
}

// SECTION - POINT LIGHT
static void	setup_p(char **p, Light *l)
{
	Vec3	color;

	l->o = getVec4(p[1], true, INT16_MAX, -INT16_MAX);
	l->i = getfloat(p[2], true, (float []){1, 0}, 0);
	color = getVec4(p[3], true, 255, 0);
	l->color = newrgb((int)color.x, (int)color.y, (int)color.z);
}

Light	*newlight(int type, char **props){
	Light	*l;

	l = (Light *)newObject(sizeof(Light), NULL);
	l->type = type;
	if (type == POINT)
		setup_p(props, l);
	else if (type == AMBIENT)
		setup_am(props, l);
	l->next = NULL;
	return 	((Light *)object_error_handler((Object *)l, (void **)props, "-> Invalid sphere"));
}

Cylinder	*newCylinder(int type, char **props){
	Vec3		color;
	Cylinder	*c;

	c = (Cylinder *)newObject(sizeof(Cylinder), \
		(tValues (*)(struct Object *, struct Ray))cylindercolision);
	c->type = CYLINDER;
	c->type = type;
	c->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	c->d = norm(getVec4(props[2], true, 1, -1));
	c->diameter = getfloat(props[3], true, (float []){INT16_MAX / 3, 0}, 1);
	c->height = getfloat(props[4], true, (float []){INT16_MAX / 3, 0}, 1);
	color = getVec4(props[5], true, 255, 0);
	c->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	c->colision = (tValues (*)(struct Object *, struct Ray))cylindercolision;
	if (props[6])
	{
		c->specular = getfloat(props[6], true, (float []){1000, 0}, 0);
		c->reflection = getfloat(props[7], true, (float []){1, 0}, 0);
	}
	return ((Cylinder *)object_error_handler((Object *)c, \
		(void **)props, "-> Invalid Cylinder"));
}

Camera	*newCamera(int type, char **props)
{
	Camera	*c;

	c = (Camera *)newObject(sizeof(Camera), NULL);
	c->type = CAMERA;
	c->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	c->d = getVec4(props[2], true, 1, -1);
	c->theta = getVec4("0,0,0", true, 1, -1);
	c->fov = getfloat(props[3], true, (float []){180, 0}, 1);
	c->aspect = (double)g_scene->width / (double)g_scene->height;
	c->height = tan(c->fov / 2 * M_PI / 180);
	c->width = c->aspect * c->height;
	c->next = NULL;
	return ((Camera *)object_error_handler((Object *)c, (void **)props, \
		"-> Invalid Camera"));
}

Paraboloid	*newParaboloid(int type, char **props)
{
	Paraboloid	*paraboloid;
	Vec3		color;

	paraboloid = (Paraboloid *)newObject(sizeof(Paraboloid), \
		(tValues (*)(struct Object *, struct Ray))paraboloidCollision);
	if (!paraboloid)
		return (NULL);
	printf("NEW CREATE PARABOLIOD\n");
	paraboloid->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	printf("O: %f %f %f\n", paraboloid->o.x, paraboloid->o.y, paraboloid->o.z);
	paraboloid->height = getfloat(props[2], true, (float []){INT16_MAX / 3, \
		0}, 1);
	printf("HEIGHT: %f\n", paraboloid->height);
	paraboloid->diameter = getfloat(props[3], true, (float []){INT16_MAX / 3, \
		0}, 1);
	printf("DIAMETER: %f\n", paraboloid->diameter);
	paraboloid->p = 1;
	color = getVec4(props[4], true, 255, 0);
	paraboloid->type = type;
	paraboloid->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	if (props[5])
	{
		paraboloid->specular = getfloat(props[5], true, (float []){1000, 0}, 1);
		if (!g_scene->error)
			paraboloid->reflection = getfloat(props[6], true, (float []){1,\ 
			0}, 0);
	}
	return ((Paraboloid *)object_error_handler((Object *)paraboloid, \
	(void **)props, "-> Invalid Paraboloid"));
}
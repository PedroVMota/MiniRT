/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:17:08 by pedro             #+#    #+#             */
/*   Updated: 2023/12/28 05:03:42 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.h>
#include <center.h>

t_object	*errhandler(t_object **obj);
t_object	*create_camera(char **objectdata, t_type data);

/// @brief Generate a ambient with the given data
/// @param objectdata
/// @return return the final ambient
/// @note Any error g_error will be setted
t_object	*create_light(char **objectdata, t_type data)
{
	t_light	*light;

	info("Creating light");
	light = (t_light *)generate_object(sizeof(t_light));
	light->type = data;
	if (!light)
		return (NULL);
	if (data == POINT)
	{
		light->vector = vector_generator(objectdata[1]);
		split_remove_element(objectdata, 1);
	}
	if (isallnum(objectdata[1], 12))
	{
		light->intensity = atof(objectdata[1]);
		split_remove_element(objectdata, 1);
	}
	if (scene()->error == 0)
	{
		light->color = color_generator(objectdata[1]);
		split_remove_element(objectdata, 1);
	}
	return (errhandler((t_object **)&light));
}

/// @brief Generate a plane with the given data
/// @param objectdata
/// @return return the final plane
t_object	*generate_pl(char **objectdata)
{
	t_plane	*plane;

	info("Creating plane");
	plane = (t_plane *)generate_object(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->type = PLANE;
	plane->vector = vector_generator(objectdata[1]);
	plane->direction = vector_generator(objectdata[2]);
	if (!objectdata[3])
		scene()->error = 5;
	plane->color = color_generator(objectdata[3]);
	plane->phi = 0.0f;
	plane->theta = 0.0f;
	plane->qsi = 0.0f;
	return (errhandler((t_object **)&plane));
}

/// @brief Generate a sphere with the given data
/// @param objectdata
/// @return  return the final sphere

t_values sphere_intersect(t_sphere *sphere, t_vector *ray);

t_object	*create_sp(char **objectdata)
{
	t_sphere	*sphere;

	info("Creating sphere");
	sphere = (t_sphere *)generate_object(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->vector = vector_generator(objectdata[1]);
	split_remove_element(objectdata, 1);
	sphere->type = SPHERE;
	if (isallnum(objectdata[1], 10))
	{
		sphere->diameter = atof(objectdata[1]);
		split_remove_element(objectdata, 1);
	}
	if (!objectdata[1])
		scene()->error = 8;
	else
		sphere->color = color_generator(objectdata[1]);
	sphere->phi = 0.0f;
	sphere->theta = 0.0f;
	sphere->qsi = 0.0f;
	sphere->intersect = sphere_intersect;
	// sphere->next = NULL;
	return (errhandler((t_object **)&sphere));
}

t_object	*create_cy(char **objectdata, t_type data)
{
	t_cylinder	*cylinder;

	info("Creating cylinder");
	cylinder = (t_cylinder *)generate_object(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->type = data;
	cylinder->vector = vector_generator(objectdata[1]);
	split_remove_element(objectdata, 1);
	cylinder->axis = vector_generator(objectdata[1]);
	split_remove_element(objectdata, 1);
	if (isallnum(objectdata[1], 10))
	{
		cylinder->diameter = atof(objectdata[1]);
		split_remove_element(objectdata, 1);
	}
	if (isallnum(objectdata[1], 12))
	{
		cylinder->height = atof(objectdata[1]);
		split_remove_element(objectdata, 1);
	}
	cylinder->color = color_generator(objectdata[1]);
	cylinder->phi = 0.0f;
	cylinder->theta = 0.0f;
	cylinder->qsi = 0.0f;
	return (errhandler((t_object **)&cylinder));
}

t_object	*create_cn(char **objectdata)
{
	t_cone	*cone;

	info("Creating cone");
	cone = (t_cone *)generate_object(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->type = CONE;
	cone->vector = vector_generator(objectdata[1]);
	cone->direction = vector_generator(objectdata[2]);
	if (isallnum(objectdata[3], 10))
		cone->radius = atof(objectdata[3]);
	if (isallnum(objectdata[4], 12))
		cone->height = atof(objectdata[4]);
	if (!objectdata[5])
		scene()->error = 8;
	else
		cone->color = color_generator(objectdata[5]);
	cone->phi = 0.0f;
	cone->theta = 0.0f;
	cone->qsi = 0.0f;
	return (errhandler((t_object **)&cone));
}

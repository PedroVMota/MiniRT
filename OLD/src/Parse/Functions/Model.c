/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:17:08 by pedro             #+#    #+#             */
/*   Updated: 2024/01/27 15:52:41 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.h>
#include <center.h>

// ======= ANGLE CALCULATION =======

double len(t_vector v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double rotate_x(t_vector original, t_vector new_vector){
    double x;

    // Project the vectors onto the yz-plane
    t_vector original_proj = {0, original.y, original.z};
    t_vector new_vector_proj = {0, new_vector.y, new_vector.z};

    // Calculate the dot product of the projected vectors
    x = dot(original_proj, new_vector_proj);

    // Calculate the lengths of the projected vectors
    double len_original = len(original_proj);
    double len_new_vector = len(new_vector_proj);

    // If either of the vectors is a zero vector, return 0
    if (len_original == 0 || len_new_vector == 0)
        return 0;

    // Calculate the angle between the vectors
    x = acos(x / (len_original * len_new_vector));

    // If the y-component of the new vector is negative, negate the angle
    if (new_vector.y < 0)
        x *= -1;

    return x;
}

double rotate_y(t_vector original, t_vector new_vector){
    double y;

    // Project the vectors onto the xz-plane
    t_vector original_proj = {original.x, 0, original.z};
    t_vector new_vector_proj = {new_vector.x, 0, new_vector.z};

    // Calculate the dot product of the projected vectors
    y = dot(original_proj, new_vector_proj);

    // Calculate the lengths of the projected vectors
    double len_original = len(original_proj);
    double len_new_vector = len(new_vector_proj);

    // If either of the vectors is a zero vector, return 0
    if (len_original == 0 || len_new_vector == 0)
        return 0;

    // Calculate the angle between the vectors
    y = acos(y / (len_original * len_new_vector));

    // If the x-component of the new vector is negative, negate the angle
    if (new_vector.x < 0)
        y *= -1;

    return y;
}

double rotate_z(t_vector original, t_vector new_vector){
    double z;

    // Project the vectors onto the xy-plane
    t_vector original_proj = {original.x, original.y, 0};
    t_vector new_vector_proj = {new_vector.x, new_vector.y, 0};

    // Calculate the dot product of the projected vectors
    z = dot(original_proj, new_vector_proj);

    // Calculate the lengths of the projected vectors
    double len_original = len(original_proj);
    double len_new_vector = len(new_vector_proj);

    // If either of the vectors is a zero vector, return 0
    if (len_original == 0 || len_new_vector == 0)
        return 0;

    // Calculate the angle between the vectors
    z = acos(z / (len_original * len_new_vector));

    // If the y-component of the new vector is negative, negate the angle
    if (new_vector.y < 0)
        z *= -1;

    return z;
}

t_vector calcTheta(t_vector origin, t_vector new_vector)
{
    t_vector theta;

    theta.x = rotate_x(origin, new_vector);
    theta.y = rotate_y(origin, new_vector);
    theta.z = rotate_z(origin, new_vector);

    return (theta);
}

// ======= ANGLE CALCULATION =======

t_object *errhandler(t_object **obj);
t_object *create_camera(char **objectdata, t_type data);

/// @brief Generate a ambient with the given data
/// @param objectdata
/// @return return the final ambient
/// @note Any error g_error will be setted
t_object *create_light(char **objectdata, t_type data)
{
	t_light *light;

	light = (t_light *)generate_object(sizeof(t_light));
	light->type = data;
	if (!light)
		return (NULL);
	if (data == POINT)
	{
		light->o = vector_generator(objectdata[1]);
		split_remove_element(objectdata, 1);
	}
	if (isallnum(objectdata[1], 12))
	{
		light->intensity = atof(objectdata[1]);
		split_remove_element(objectdata, 1);
	}
	if (scene()->error == 0)
	{
		light->rgb = color_generator(objectdata[1]);
		split_remove_element(objectdata, 1);
	}
	return (errhandler((t_object **)&light));
}

/// @brief Generate a plane with the given data
/// @param objectdata
/// @return return the final plane
t_object *generate_pl(char **objectdata)
{
	t_plane *plane;

	plane = (t_plane *)generate_object(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->o = vector_generator(objectdata[1]);
	plane->direction = vector_generator(objectdata[2]);
	if (!objectdata[3])
		scene()->error = 5;
	plane->rgb = color_generator(objectdata[3]);
	plane->type = PLANE;
	return (errhandler((t_object **)&plane));
}

/// @brief Generate a sphere with the given data
/// @param objectdata
/// @return  return the final sphere
t_object *create_sp(char **objectdata)
{
	t_sphere *sphere;

	sphere = (t_sphere *)generate_object(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->o = vector_generator(objectdata[1]);
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
		sphere->rgb = color_generator(objectdata[1]);
	return (errhandler((t_object **)&sphere));
}

t_object *create_cy(char **objectdata, t_type data)
{
	t_cylinder *cylinder;

	cylinder = (t_cylinder *)generate_object(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->type = data;
	cylinder->o = vector_generator(objectdata[1]);
	split_remove_element(objectdata, 1);
	cylinder->direction = vector_generator(objectdata[1]);
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
	cylinder->rgb = color_generator(objectdata[1]);
	return (errhandler((t_object **)&cylinder));
}

t_object *create_cn(char **objectdata)
{
	t_cone *cone;

	cone = (t_cone *)generate_object(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->type = CONE;
	cone->o = vector_generator(objectdata[1]);
	cone->direction = vector_generator(objectdata[2]);
	if (isallnum(objectdata[3], 10))
		cone->radius = atof(objectdata[3]);
	if (isallnum(objectdata[4], 12))
		cone->height = atof(objectdata[4]);
	if (!objectdata[5])
		scene()->error = 8;
	else
		cone->rgb = color_generator(objectdata[5]);
	return (errhandler((t_object **)&cone));
}

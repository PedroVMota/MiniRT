/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:18:51 by pedro             #+#    #+#             */
/*   Updated: 2023/12/24 02:18:52 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_object	*errhandler(t_object **obj);
bool		isallnum(char *str, int error);
void		split_remove_element(char **arr, int index);

/// @brief Generate a camera with the given data
/// @param objectdata
/// @return return the final camear
/// @note Any error g_error will be setted
t_object	*create_camera(char **objectdata, t_type data)
{
	t_camera	*camera;

	camera = (t_camera *)generate_object(sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->type = data;
	camera->next = NULL;
	return (camera_initilize(&camera, objectdata));
}

t_object	*camera_initilize(t_camera **obj, char **objd)
{
	if (!scene()->error && !objd[1])
		scene()->error = 6;
	else if (!scene()->error)
		(*obj)->vector = vector_generator(objd[1]);
	split_remove_element(objd, 1);
	if (!scene()->error && !objd[1])
		scene()->error = 6;
	else if (!scene()->error)
		(*obj)->direction = vector_generator(objd[1]);
	split_remove_element(objd, 1);
	if (!scene()->error && !objd[1])
		scene()->error = 5;
	if (!isallnum(objd[1], 5))
		scene()->error = 3;
	else if (!scene()->error)
		(*obj)->fov = atof(objd[1]);
	(*obj)->phi = 0.0f;
	(*obj)->theta = 0.0f;
	(*obj)->qsi = 0.0f;
	return (errhandler((t_object **)obj));
}

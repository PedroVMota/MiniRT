#include <Vector.h>
#include <center.h>

void		*generate_object(int size);
bool		isallnum(char *str, int error);


// =============== initilize function 
t_object    *camera_initilize(t_camera **obj, char **objd);

t_object *errhandler(t_object **obj)
{
	if(scene()->error != 0)
	{
		free(*obj);
		return NULL;
	}
	return *obj;
}

void split_remove_element(char **arr, int index)
{
	int	len;
	int	i;

	i = index - 1;
	len = 0;
	if (!arr || index < 0)
		return ;
	while (arr[len])
		len++;
	if (index >= len)
		return ;
	free(arr[index]);
	while (++i < len - 1)
		arr[i] = arr[i + 1];
	arr[len - 1] = NULL;
}

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
	return (camera_initilize(&camera, objectdata));
}

/// @brief Generate a ambient with the given data
/// @param objectdata
/// @return return the final ambient
/// @note Any error g_error will be setted
t_object	*create_light(char **objectdata, t_type data)
{
	t_light	*light;

	light = (t_light *)generate_object(sizeof(t_light));
	if (!light)
		return (NULL);
	if(data == POINT)
	{
		light->vector = vector_generator(objectdata[1]);
		split_remove_element(objectdata, 1);
	}
	if(isallnum(objectdata[1], 12))
		light->intensity = atof(objectdata[1]);
	light->color = color_generator(objectdata[1]);
	split_remove_element(objectdata, 1);
	errhandler((t_object **)&light);
	return ((t_object *)light);
}

/// @brief Generate a plane with the given data
/// @param objectdata
/// @return return the final plane
t_object	*generate_pl(char **objectdata)
{
	t_plane	*plane;

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
	errhandler((t_object **)&plane);
	return ((t_object *)plane);
}

/// @brief Generate a sphere with the given data
/// @param objectdata
/// @return  return the final sphere
t_object	*create_sp(char **objectdata)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)generate_object(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->type = SPHERE;
	sphere->vector = vector_generator(objectdata[1]);
	if (!objectdata[2])
		scene()->error = 10;
	else
		sphere->diameter = atof(objectdata[2]);
	if (!objectdata[3])
		scene()->error = 8;
	else
		sphere->color = color_generator(objectdata[3]);
	sphere->phi = 0.0f;
	sphere->theta = 0.0f;
	sphere->qsi = 0.0f;
	errhandler((t_object **)&sphere);
	return ((t_object *)sphere);
}

t_object	*create_cy(char **objectdata)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)generate_object(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->type = CYLINDER;
	cylinder->vector = vector_generator(objectdata[1]);
	cylinder->axis = vector_generator(objectdata[2]);
	if (isallnum(objectdata[3], 10))
		cylinder->diameter = atof(objectdata[3]);
	if (isallnum(objectdata[4], 12))
		cylinder->height = atof(objectdata[4]);
	if (!objectdata[5])
		scene()->error = 8;
	else
		cylinder->color = color_generator(objectdata[5]);
	cylinder->phi = 0.0f;
	cylinder->theta = 0.0f;
	cylinder->qsi = 0.0f;
	errhandler((t_object **)&cylinder);
	return ((t_object *)cylinder);
}


t_object	*create_cn(char **objectdata)
{

	t_cone	*cone;

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
	errhandler((t_object **)&cone);
	return ((t_object *)cone);
}

#include <center.h>

char	**ft_splitstr(char *str, char *charset);


t_scene g_scene  = (t_scene){NULL};

void interator(void **c, void (*f)(void *x))
{
	int i = 0;
	while(c[i])
		f(c[i++]);
	f(c);
}

t_vector vectorGenerator(char **vector)
{
	t_vector new_vector;
	new_vector.x = atof(vector[0]);
	new_vector.y = atof(vector[1]);
	new_vector.z = atof(vector[2]);
	interator((void **)vector, free);
	return ((t_vector){new_vector.x, new_vector.y, new_vector.z});
}

void objectaddlastcamera(t_object *object)
{
	t_object *tmp;

	if(!g_scene.objects)
	{
		g_scene.objects = object;
		return;
	}
	tmp = g_scene.objects;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = object;
}

// int  analize_light(char **objectdata)
// {
// 	t_type lighttype;

// 	if(ft_strcmp(objectdata[0], "A") != 0 && ft_strcmp(objectdata[0], "L") != 0)
// 		return 1;
// 	if(!ft_strcmp(objectdata[0], "A"))
// 		lighttype = AMBIENT;
// 	if(!ft_strcmp(objectdata[0], "L"))
// 		lighttype = POINT;	
// 	interator((void **)objectdata, free);
// 	return 0;
// }

// int  analize_object(char **objectdata)
// {
// 	t_type lighttype;

// 	if(ft_strcmp(objectdata[0], "pl") != 0 && ft_strcmp(objectdata[0], "cy") != 0 && ft_strcmp(objectdata[0], "sp"))
// 		return 1;
// 	if(!ft_strcmp(objectdata[0], "pl"))
// 		lighttype = PLANE;
// 	if(!ft_strcmp(objectdata[0], "cy"))
// 		lighttype = CYLINDER;	
// 	if(!ft_strcmp(objectdata[0], "sp"))
// 		lighttype = SPHERE;	
// 	interator((void **)objectdata, free);
// 	return 0;
// }

int  analize_camera(char **objectdata)
{
	t_type lighttype;


	if((objectdata && ft_strcmp(objectdata[0], "C") != 0) || !objectdata)
		return 1;
	char **origin = ft_splitstr(objectdata[1], ",");
	char **normal = ft_splitstr(objectdata[2], ",");
	
	t_camera *camera = (t_camera *)malloc(sizeof(t_camera));
	if(!camera)
		return 1;
	interator((void **)objectdata, free);
	camera->vector = vectorGenerator(origin);
	camera->vectorn = vectorGenerator(normal);
	camera->fov = 245;
	camera->type = CAMERA;
	camera->next = NULL;
	objectaddlastcamera((t_object *)camera);
	return 0;
}



bool splitdata(int fd)
{
	char *line;
	char **objectdata;
	line = NULL;
	objectdata = NULL;
	while(1)
	{
		line = get_next_line(fd);
		if(!line)
			break;
		objectdata = ft_splitstr(line, " \n\t");
		if(!objectdata)
			exit(1);
		else if (!ft_strcmp(objectdata[0], "->"))
			interator((void **)objectdata, free);
		// else if (analize_light(objectdata) == -1)
			// return true;
		else if (analize_camera(objectdata) == -1)
			return true;
		// else if (analize_object(objectdata) == -1)
			// return true;
		free(line);
	}
	close(fd);
}

void delete(t_scene *scene)
{
	t_object *tmp;
	t_object *tmp2;

	tmp = scene->objects;
	while(tmp)
	{
		if(tmp->type == CAMERA)
		{
			tmp2 = tmp->next;
			free((t_camera *)tmp);
			tmp = tmp2;
		}
		else
		{
			tmp2 = tmp->next;
			free(tmp);
			tmp = tmp2;
		}
	}
}


bool parse_data(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if(fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return true;
	}
	if(splitdata(fd))
		return true;
	delete(&g_scene);
}

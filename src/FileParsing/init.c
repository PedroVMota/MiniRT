#include <center.h>

char	**ft_splitstr(char *str, char *charset);

void interator(void **c, void (*f)(void *x))
{
	int i = 0;
	while(c[i])
	{
		f(c[i]);
		i++;
	}
	f(c);
}

int  analize_light(char **objectdata)
{
	t_type lighttype;

	if(strcmp(objectdata[0], "A") != 0 && strcmp(objectdata[0], "L") != 0)
		return 1;
	if(!strcmp(objectdata[0], "A"))
		lighttype = AMBIENT;
	if(!strcmp(objectdata[0], "L"))
		lighttype = POINT;	
	interator(objectdata, free);
	return 0;
}

int  analize_object(char **objectdata)
{
	t_type lighttype;

	if(strcmp(objectdata[0], "pl") != 0 && strcmp(objectdata[0], "cy") != 0 && strcmp(objectdata[0], "sp"))
		return 1;
	if(!strcmp(objectdata[0], "pl"))
		lighttype = PLANE;
	if(!strcmp(objectdata[0], "cy"))
		lighttype = CYLINDER;	
	if(!strcmp(objectdata[0], "sp"))
		lighttype = SPHERE;	
	interator(objectdata, free);
	return 0;
}

int  analize_camera(char **objectdata)
{
	t_type lighttype;

	if(strcmp(objectdata[0], "C") != 0)
		return 1;
	if(!strcmp(objectdata[0], "C"))
		lighttype = CAMERA;
	interator(objectdata, free);
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
		else if (!strcmp(objectdata[0], "->"))
			interator(objectdata, free);
		else if (analize_light(objectdata) == -1)
			return true;
		else if (analize_camera(objectdata) == -1)
			return true;
		else if (analize_object(objectdata) == -1)
			return true;
		else
		{
			interator(objectdata, free);
			return true;
		}
		free(line);
	}
	close(fd);
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
}

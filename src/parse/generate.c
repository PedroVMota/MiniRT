#include <center.h>

bool	err(char *msg, int exit_code);
void	printprops(char **line, char *name, const char *funcname);
void	delprops(char **line);

int setdata(bool *ptr, bool data, int res)
{
	if(*ptr == data)
		return 2;
	*ptr = data;
	return res;
}

bool	float_requirements(char *s, int start, int end){
	bool	asdot;
	bool	assignal;

	asdot = false;
	assignal = false;
	if (start > end)
		return (false);
	if(start == -1 && end == -1)
	{
		start = 0;
		end = ft_strlen(s);
	}
	while (start < end && s[start])
	{
		if (s[start] == ',')
			if (start == 0 || s[start - 1] == ',' || s[start + 1] == ',')
					return (true);
		if (s[start] == '-' || s[start] == '+')
		{
			if (s[start - 1] != ',' || assignal)
				return (true);
			assignal = true;
		}
		if (s[start] == '.' && setdata(&asdot, true, 0) == 2)
			return (true);
		if (!ft_isdigit(s[start]) && s[start] != '.' && s[start] != '-'	&& s[start] != '+')
			return (true);
		start++;
	}
	return (false);
}

bool	vector_requirements(char *s){
	int	commas;
	int	i;
	int	start;

	i = -1;
	start = 0;
	commas = 0;
	while (true)
	{
		if(!s[++i])
			break ;
		if (s[i] == ',')
		{
			commas++;
			if ((i == 0) || float_requirements(s, start, i) || commas > 2 || \
				s[i + 1] == '\0' || s[i + 1] == ',')
				return (false);
			start = i + 1;
		}
		else if (s[i] == ' ')
			return (false);
	}
	if(float_requirements(s, start, i))
		return (false);
	if (commas < 2)
		return (false);
	return (true);
}

bool	distributeobject(int type, char **props)
{
	if(type == UNKNOWN)
	{
		delprops(props);
		return (err("Unknown object type", 1));
	}
	if(type == SPHERE)
		objectadd((Object *)newSphere(type, props), (Object **)&g_scene->objects);
	if(type == PLANE)
		objectadd((Object *)newPlane(type, props), (Object **)&g_scene->objects);
	if(type == CAMERA)
		objectadd((Object *)newCamera(type, props), (Object **)&g_scene->camera);

	return (true);
}
#include <center.h>

void	delprops(char **line)
{
	int	i;

	i = 0;
	while (line[++i])
		free(line[i]);
	free(line);
}

bool	generateobject(char **props)
{
	int	type;

	type = UNKNOWN;
	if (ft_strncmp(props[0], "sp", 6) == 0)
		type = SPHERE;
	else if (ft_strncmp(props[0], "pl", 5) == 0)
		type = PLANE;
	else if (ft_strncmp(props[0], "C", 6) == 0)
		type = CAMERA;
	else if (ft_strncmp(props[0], "L", 5) == 0)
		type = POINT;
	else if (ft_strncmp(props[0], "A", 7) == 0)
		type = AMBIENT;
	else if (ft_strncmp(props[0], "D", 12) == 0)
		type = DIRECTIONAL;
	else if (ft_strncmp(props[0], "cy", 8) == 0)
		type = CYLINDER;
	else if (ft_strncmp(props[0], "pa", 7) == 0)
		type = PARABOLOID;
	if (!distributeobject(type, props))
		return (false);
	return (true);
}
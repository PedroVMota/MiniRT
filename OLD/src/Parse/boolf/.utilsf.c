#include <center.h>

bool	check_object_identifier(char *s)
{
	int res;

	if(!s)
	{
		scene()->error = 2;
		return 1;

	}
	res = ((ft_strcmp(s, "C") && ft_strcmp(s, "L") && ft_strcmp(s, "A")
			&& ft_strcmp(s, "pl") && ft_strcmp(s, "cy") && ft_strcmp(s, "sp")
			&& ft_strcmp(s, "co")));
	if(res != 0)
	{
		scene()->error = 2;
		return 1;
	}
	return (0);
}

bool	type_model_struct(t_object *tmp)
{
	return (tmp->type == CAMERA || tmp->type == POINT || tmp->type == AMBIENT
		|| tmp->type == DIRECTIONAL || tmp->type == SPHERE
		|| tmp->type == CYLINDER || tmp->type == PLANE || tmp->type == CONE);
}

bool	check_alloc(void *ptr){
	if (ptr == NULL)
	{
		scene()->error = 1;
		return (true);
	}
	return (false);
}

bool	check_double_alloc(void **ptr){
	if (ptr == NULL)
	{
		scene()->error = 1;
		return (true);
	}
	return (false);
}
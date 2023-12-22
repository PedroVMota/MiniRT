#include <center.h>

/// @brief This function will add a element to the link list
/// @param object list
void	objectaddlast(t_object *object)
{
	t_object	*tmp;

	if (!scene()->objects)
	{
		scene()->objects = object;
		return ;
	}
	tmp = scene()->objects;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = object;
}

t_scene	*scene(void)
{
	static t_scene	scene;

	return (&scene);
}
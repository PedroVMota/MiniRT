#include <center.h>

void	interator(void **c, void (*f)(void *x))
{
	int	i;

	i = 0;
	while (c[i])
		f(c[i++]);
	f(c);
	c = NULL;
}

void remove_object_list(void)
{
	t_object	*tmp;
	t_object	*tmp2;

	long int i = 0;
	for(t_object *tmp = scene()->objects; tmp; tmp = tmp->next)
		i++;
	printf("objects: %ld\n", i);
	report();
	tmp = scene()->objects;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:45:14 by pvital-m          #+#    #+#             */
/*   Updated: 2023/12/24 02:19:33 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void	*interator(char ***c, void (*f)(void *x))
{
	int	i;

	i = 0;
	if (!c || !*c)
		return (NULL);
	while ((*c)[i])
	{
		f((*c)[i]);
		i++;
	}
	free(*c);
	*c = NULL;
	return (NULL);
}

void	rm_list(t_object **lst)
{
	t_object	*tmp;
	int			index;
	t_type		type;

	index = 0;
	if (!*lst)
		return ;
	while (*lst)
	{
		type = (*lst)->type;
		index++;
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	if (type == CAMERA)
		printf("Cameras: %d Deleted\n", index);
	if (type == AMBIENT || type == POINT)
		printf("Lights: %d Deleted\n", index);
	if (type == SPHERE || type == PLANE || type == CYLINDER || type == CONE)
		printf("Objects: %d Deleted\n", index);
	*lst = NULL;
}

void	remove_object_list(void)
{
	rm_list(&scene()->objects);
	rm_list(&scene()->lights);
	rm_list(&scene()->camera);
}

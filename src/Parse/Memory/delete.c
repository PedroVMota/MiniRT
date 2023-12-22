/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:45:14 by pvital-m          #+#    #+#             */
/*   Updated: 2023/12/22 18:47:20 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	remove_object_list(void)
{
	t_object	*tmp;
	t_object	*tmp2;
	long long i;
	
	i = 0;
	for(t_object *tmp = scene()->objects; tmp; tmp = tmp->next)
		i++;
	printf("objects: %lld\n", i);
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

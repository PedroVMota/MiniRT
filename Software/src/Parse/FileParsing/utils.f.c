/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 01:29:36 by pedro             #+#    #+#             */
/*   Updated: 2023/12/24 02:20:00 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void	split_remove_element(char **arr, int index)
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

t_object	*errhandler(t_object **obj)
{
	if (scene()->error != 0)
	{
		free(*obj);
		return (NULL);
	}
	return (*obj);
}

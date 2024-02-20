/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:21:19 by pvital-m          #+#    #+#             */
/*   Updated: 2024/02/20 15:44:45 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"

static t_obj	*objreturn(t_ray *s)
{
	t_obj	*o;

	o = intersections(s, INFINITY, 0, false);
	if (!o)
		return (NULL);
	return (o);
}

int	rt_select(int key)
{
	double	xv;
	double	yv;
	int		x;
	int		y;
	t_ray	s;

	if (key == 1)
	{
		xv = (gscene()->width / 2);
		yv = -(gscene()->height / 2);
		mlx_mouse_get_pos(gscene()->mlx->win, &x, &y);
		// mlx_mouse_get_pos(gscene()->mlx->mlx, gscene()->mlx->win, &x, &y);
		x = x - (gscene()->width / 2);
		y = (y - (gscene()->height / 2)) * -1;
		s = getraydir(gscene()->camera->o, x, y);
		gscene()->selected = objreturn(&s);
		renderframe();
	}
	else if (key == 3)
	{
		gscene()->selected = (t_obj *)gscene()->camera;
		renderframe();
	}
	return (0);
}

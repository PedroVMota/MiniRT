/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:32:45 by pedro             #+#    #+#             */
/*   Updated: 2024/02/19 22:58:48 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

int	sysclean(int res);
int	rt_select(void);

bool	initialize_mlx(t_scene *s)
{
	s->mlx = malloc(sizeof(t_mlxdata) * 1);
	s->mlx->mlx = mlx_init();
	if (!s->mlx->mlx)
		return (false);
	s->mlx->win = mlx_new_window(s->mlx->mlx, s->width, s->height, "miniRT");
	if (!s->mlx->win)
		return (false);
	s->mlx->img = mlx_new_image(s->mlx->mlx, s->width, s->height);
	if (!s->mlx->img)
		return (false);
	s->mlx->addr = mlx_get_data_addr(s->mlx->img, &s->mlx->bits_per_pixel, \
		&s->mlx->line_length, &s->mlx->endian);
	if (!s->mlx->addr)
		return (false);
	mlx_mouse_hook((gscene())->mlx->win, rt_select, NULL);
	mlx_key_hook((gscene())->mlx->win, key_hook, NULL);
	mlx_hook((gscene())->mlx->win, 17, 0, sysclean, (void *)(1));
	return (true);
}

t_scene	*init_main(int depth)
{
	gscene()->depth = depth;
	gscene()->camera = NULL;
	gscene()->objects = NULL;
	gscene()->lights = NULL;
	gscene()->selected = NULL;
	gscene()->am = NULL;
	gscene()->props = NULL;
	gscene()->mlx = NULL;
	gscene()->error = 0;
	gscene()->width = WIDTH;
	gscene()->height = HEIGHT;
	return (gscene());
}

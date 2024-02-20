/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:41:50 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/20 12:18:25 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

int		sysclean(int res);
void	rotation_x(double theta, t_vector *vec);
void	rotation_y(double theta, t_vector *vec);
void	rotation_z(double theta, t_vector *vec);

int	keytest(int keycode)
{
	t_pl	*pl;

	pl = (t_pl *)gscene()->selected;
	if (keycode == R)
		rotation_x(0.5, &pl->d);
	if (keycode == F)
		rotation_x(-0.5, &pl->d);
	if (keycode == T)
		rotation_y(0.5, &pl->d);
	if (keycode == G)
		rotation_y(-0.5, &pl->d);
	if (keycode == Y)
		rotation_z(-0.05, &pl->d);
	if (keycode == H)
		rotation_z(0.05, &pl->d);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	(void)param;
	if (keycode == ESCAPE)
		sysclean(0);
	if (!(gscene())->selected)
		return (0);
	if (keycode == A)
		(gscene())->selected->o.x -= 0.5;
	if (keycode == D)
		(gscene())->selected->o.x += 0.5;
	if (keycode == W)
		(gscene())->selected->o.y += 0.5;
	if (keycode == S)
		(gscene())->selected->o.y -= 0.5;
	if (keycode == Q)
		(gscene())->selected->o.z += 0.5;
	if (keycode == E)
		(gscene())->selected->o.z -= 0.5;
	if (gscene()->selected->type != CAMERA)
		keytest(keycode);
	renderframe();
	return (0);
}

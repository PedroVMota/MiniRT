/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:41:50 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/18 17:19:03 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

int	sysclean(int res);
void	rotation_x(double theta, t_vector *vec);
void	rotation_y(double theta, t_vector *vec);
void	rotation_z(double theta, t_vector *vec);


int	keytest(int keycode)
{
	t_pl	*pl;
	pl = (t_pl *)gscene()->objects;
	if (keycode == B)
		rotation_x(0.5, &pl->d);
	if (keycode == N)
		rotation_x(-0.5, &pl->d);
	if (keycode == G)
		rotation_y(0.5, &pl->d);
	if (keycode == H)
		rotation_y(-0.5, &pl->d);
	if (keycode == K)
		rotation_z(-0.05, &pl->d);
	if (keycode == L)
		rotation_z(0.05, &pl->d);
	return (0);
}
int	key_hook(int keycode, void *param)
{
	printf("Keycode: %d\n", keycode);
	(void)param;
	keytest(keycode);
	if (keycode == ESCAPE)
		sysclean(0);
	if (keycode == LEFT)
		(gscene())->lights->o.x -= 0.5;
	if (keycode == RIGHT)
		(gscene())->lights->o.x += 0.5;
	if (keycode == UP)
		(gscene())->lights->o.y += 0.5;
	if (keycode == DOWN)
		(gscene())->lights->o.y -= 0.5;
	if (keycode == Q)
		(gscene())->lights->o.z += 0.5;
	if (keycode == E)
		(gscene())->lights->o.z -= 0.5;
	renderframe();
	return (0);
}



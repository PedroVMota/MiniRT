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

int	key_hook(int keycode, void *param)
{
	printf("Keycode: %d\n", keycode);
	(void)param;
	if (keycode == 65307)
		sysclean(0);
	if (keycode == 65361)
		(gscene())->lights->o.x -= 0.5;
	if (keycode == 65363)
		(gscene())->lights->o.x += 0.5;
	if (keycode == 65362)
		(gscene())->lights->o.y += 0.5;
	if (keycode == 65364)
		(gscene())->lights->o.y -= 0.5;
	if (keycode == 113)
		(gscene())->lights->o.z += 0.5;
	if (keycode == 101)
		(gscene())->lights->o.z -= 0.5;
	renderframe();
	return (0);
}

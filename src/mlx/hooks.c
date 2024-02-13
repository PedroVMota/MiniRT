/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:41:50 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/13 21:44:58 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

int	key_hook(int keycode, void *param)
{
	printf("Keycode: %d\n", keycode);
	if (keycode == 65307)
		sysclean(0);
	if (keycode == 65361)
		g_scene->lights->o.x -= 0.5;
	if (keycode == 65363)
		g_scene->lights->o.x += 0.5;
	if (keycode == 65362)
		g_scene->lights->o.y += 0.5;
	if (keycode == 65364)
		g_scene->lights->o.y -= 0.5;
	if (keycode == 65360)
		g_scene->lights->o.z += 0.5;
	if (keycode == 65367)
		g_scene->lights->o.z -= 0.5;
	renderframe();
	return (0);
}

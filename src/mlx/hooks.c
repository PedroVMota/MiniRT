/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:41:50 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/14 14:53:08 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

int	sysclean(int res);

int	key_hook(int keycode, void *param)
{
	printf("Keycode: %d\n", keycode);
	if (keycode == 65307)
		sysclean(0);
	if (keycode == 123)
		g_scene->camera->o.x -= 0.5;
	if (keycode == 124)
		g_scene->camera->o.x += 0.5;
	if (keycode == 126)
		g_scene->camera->o.y += 0.5;
	if (keycode == 125)
		g_scene->camera->o.y -= 0.5;
	if (keycode == 12)
		g_scene->camera->o.z += 0.5;
	if (keycode == 14)
		g_scene->camera->o.z -= 0.5;
	renderframe();
	return (0);
}

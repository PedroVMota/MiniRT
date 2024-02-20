/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/02/20 12:14:02 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"

t_scene	*gscene(void)
{
	static t_scene	scene;

	return (&scene);
}

int	sysclean(int res)
{
	del((t_obj **)&(gscene())->lights);
	del((t_obj **)&(gscene())->objects);
	del((t_obj **)&(gscene())->camera);
	del((t_obj **)&(gscene())->am);
	if ((gscene())->mlx)
	{
		mlx_clear_window((gscene())->mlx->mlx, (gscene())->mlx->win);
		mlx_destroy_window((gscene())->mlx->mlx, (gscene())->mlx->win);
		mlx_destroy_image((gscene())->mlx->mlx, (gscene())->mlx->img);
		mlx_destroy_display((gscene())->mlx->mlx);
		free((gscene())->mlx->mlx);
		free((gscene())->mlx);
	}
	if (res != -1)
		exit(res);
	return (res);
}

int	checkcamera(void)
{
	int	count;
	t_cam *c;
	count = 0;
	
	c = (t_cam *)gscene()->camera;
	while (c)
	{
		count++;
		c = c->next;
	}
	if (count > 1)
		return 1;
	return 0;
}
bool	secutity(int argc, char **argv)
{
	if (argc != 2)
		return (uptadeerror("Invalud number of arguments\n"), true);
	init_main(3);
	if ((!parse(argv[1])))
		return (1);
	if (!(gscene())->am || !(gscene())->camera || checkcamera()|| (gscene())->error)
		return (uptadeerror("The scene does not a camera or a ambient\n"), sysclean(1));
	if (!initialize_mlx((gscene())))
		return (uptadeerror("Initialize mlx failed\n"), 1);
	return (0);
}
int	main(int argc, char **argv)
{
	if (secutity(argc, argv))
		return (sysclean(1));
	renderframe();
	mlx_loop((gscene())->mlx->mlx);
	return (0);
}

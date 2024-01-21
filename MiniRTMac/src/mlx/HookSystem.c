#include <center.h>

#ifndef __APPLE__
	#define  UP 65364
	#define  DOWN 65362
	#define  LEFT 65361
	#define  RIGHT 65363
	#define  ESC 65307
#else
	#define  ESC 53
	#define  UP 126
	#define  DOWN 125
	#define  LEFT 123
	#define  RIGHT 124
	#define PLUS 24
	#define MINUS 27
#endif

double shift = 1;
int key_hook(int keycode)
{

	printf("keycode: %d\n", keycode);
	if(keycode == ESC)
	{
		mlx_clear_window(scene()->mlx_data->mlx, scene()->mlx_data->win);
		mlx_destroy_window(scene()->mlx_data->mlx, scene()->mlx_data->win);
		mlx_destroy_image(scene()->mlx_data->mlx, scene()->mlx_data->img);
		#ifndef __APPLE__
			mlx_destroy_display(scene()->mlx_data->mlx);
		#endif
		remove_object_list();
		free(scene()->mlx_data->mlx);
		free(scene()->mlx_data);
		ft_exit();
	}

	if(keycode == UP)
		scene()->objects->o.y += shift;
	if(keycode == DOWN)
		scene()->objects->o.y -= shift;
	if(keycode == LEFT)
		scene()->objects->o.x -= shift;
	if(keycode == RIGHT)
		scene()->objects->o.x += shift;
	if(keycode == PLUS)
		shift += 0.2;
	if(keycode == MINUS)
		shift -= 0.2;
	render();
	return (0);
}


#include <center.h>


int key_hook(int keycode)
{
	printf("keycode: %d\n", keycode);
	/*
		65364: down
		65362: Up
		65361: left
		65363: right
		65307: ESC
	*/
	if(keycode == 65307)
	{
		mlx_clear_window(scene()->mlx_data->mlx, scene()->mlx_data->win);
		mlx_destroy_window(scene()->mlx_data->mlx, scene()->mlx_data->win);
		mlx_destroy_image(scene()->mlx_data->mlx, scene()->mlx_data->img);
		mlx_destroy_display(scene()->mlx_data->mlx);
		remove_object_list();
		free(scene()->mlx_data->mlx);
		free(scene()->mlx_data);
		ft_exit();
	}
	return (0);
}


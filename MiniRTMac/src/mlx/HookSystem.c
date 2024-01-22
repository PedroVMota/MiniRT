#include <center.h>

#ifndef __APPLE__
	#define  UP 65362
	#define  DOWN 65364
	#define  LEFT 65361
	#define  RIGHT 65363
	#define  ESC 65307
	#define PLUS 61
	#define MINUS 45
	#define Z 122
	#define X 120
	#define SPACE 32
#else
	#define  ESC 53
	#define  UP 126
	#define  DOWN 125
	#define  LEFT 123
	#define  RIGHT 124
	#define PLUS 24
	#define MINUS 27
	#define Z 6
	#define X 7
	#define SPACE 49
	#define A 0
	#define S 1
	#define D 2
	#define W 13
	#define Q 12
	#define E 14
	#define M 46
#endif

double shift = 0.5;

void ft_swap_camera()
{
	if(scene()->camera->next == NULL)
		return ;
	t_object *tmp;
	tmp = scene()->camera;
	scene()->camera = scene()->camera->next;
	tmp->next = NULL;
	scene()->camera->next = tmp;
}

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
	if(keycode == M)
	{
		printf("M\n");
		if(scene()->show_menu == false)
			scene()->show_menu = true;
		else
			scene()->show_menu = false;
	}
	if(keycode == UP)
		scene()->objects->o.y += shift;
	if(keycode == DOWN)
		scene()->objects->o.y -= shift;
	if(keycode == LEFT)
		scene()->objects->o.x -= shift;
	if(keycode == RIGHT)
		scene()->objects->o.x += shift;
	if(keycode == Z)
		scene()->objects->o.z += shift;
	if(keycode == X)
		scene()->objects->o.z -= shift;
	if(keycode == PLUS)
		shift += 0.2;
	if(keycode == MINUS)
		shift -= 0.2;
	if(keycode == SPACE)
		ft_swap_camera();
	if(keycode == A && scene()->objects->type == PLANE || scene()->objects->type == CYLINDER)
		((t_plane *)scene()->objects)->direction.x -= shift;
	if(keycode == D && scene()->objects->type == PLANE || scene()->objects->type == CYLINDER)
		((t_plane *)scene()->objects)->direction.x += shift;
	if(keycode == W && scene()->objects->type == PLANE || scene()->objects->type == CYLINDER)
		((t_plane *)scene()->objects)->direction.y += shift;
	if(keycode == S && scene()->objects->type == PLANE || scene()->objects->type == CYLINDER)
		((t_plane *)scene()->objects)->direction.y -= shift;
	if(keycode == Q && scene()->objects->type == PLANE || scene()->objects->type == CYLINDER)
		((t_plane *)scene()->objects)->direction.z -= shift;
	if(keycode == E && scene()->objects->type == PLANE || scene()->objects->type == CYLINDER)
		((t_plane *)scene()->objects)->direction.z += shift;
	

	
	// printf("Shift: %f\n", shift);
	// printf("Object Orientation: (%f, %f, %f)\n", scene()->objects->o.x, scene()->objects->o.y, scene()->objects->o.z);
	// ((t_plane *)scene()->objects)->direction;
	// printf("Plane Direction: (%f, %f, %f)\n", ((t_plane *)scene()->objects)->direction.x, ((t_plane *)scene()->objects)->direction.y, ((t_plane *)scene()->objects)->direction.z);
	render();
	return (0);
}


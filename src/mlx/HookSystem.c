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
		free(scene()->mutex);
		ft_exit();
	}
    // printf("Direction: %f,%f,%f\n", ((t_plane *) scene()->objects)->direction.x, ((t_plane *) scene()->objects)->direction.y, ((t_plane *) scene()->objects)->direction.z);
    switch (keycode)
    {
    case 65364:
        ((t_plane *) scene()->objects)->direction.y -= 0.1; 
        // printf("Direction: %f,%f,%f\n", ((t_plane *) scene()->objects)->direction.x, ((t_plane *) scene()->objects)->direction.y, ((t_plane *) scene()->objects)->direction.z);
        render();
        break;
    case 65362:
        ((t_plane *) scene()->objects)->direction.y += 0.1; 
    // printf("Direction: %f,%f,%f\n", ((t_plane *) scene()->objects)->direction.x, ((t_plane *) scene()->objects)->direction.y, ((t_plane *) scene()->objects)->direction.z);
        render();
        break;
    case 65361:
        ((t_plane *) scene()->objects)->direction.x += 0.1; 
    // printf("Direction: %f,%f,%f\n", ((t_plane *) scene()->objects)->direction.x, ((t_plane *) scene()->objects)->direction.y, ((t_plane *) scene()->objects)->direction.z);
        render();
        break;
    case 65363:
        ((t_plane *) scene()->objects)->direction.x -= 0.1; 
    // printf("Direction: %f,%f,%f\n", ((t_plane *) scene()->objects)->direction.x, ((t_plane *) scene()->objects)->direction.y, ((t_plane *) scene()->objects)->direction.z);
        render();
        break;
    case 122:
        ((t_plane *) scene()->objects)->direction.z += 0.1; 
    // printf("Direction: %f,%f,%f\n", ((t_plane *) scene()->objects)->direction.x, ((t_plane *) scene()->objects)->direction.y, ((t_plane *) scene()->objects)->direction.z);
        render();
        break;
    case 120:
        ((t_plane *) scene()->objects)->direction.z -= 0.1; 
    // printf("Direction: %f,%f,%f\n", ((t_plane *) scene()->objects)->direction.x, ((t_plane *) scene()->objects)->direction.y, ((t_plane *) scene()->objects)->direction.z);
        render();
        break;
    default:
        break;
    }

	return (0);
}

//pl  5.0,1.0,-1.0       1,0,0                           0,0,225
//pl  -5.0,1.0,-1.0       1,0,0                           0,0,225

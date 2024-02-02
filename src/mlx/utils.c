#include <center.h>

int	create_trgb(Vec4 color){
    return (color.t << 24 | color.r << 16 | color.g << 8 | color.b);
}

Vec4 create_color(unsigned int t, unsigned int r, unsigned int g, unsigned int b){
    return (Vec4){t, r, g, b};
}

void	my_mlx_pixel_put(double x, double y, Vec4 rgb){
	char	*dst;

	dst = scene->mlx->addr + (((int)y) * scene->mlx->line_length + ((int)x) * (scene->mlx->bits_per_pixel/ 8));
	//rgb.t = Clamp(rgb.t, 0, 255);
	rgb.t = 0;
   	rgb.r = Min(255, Max(rgb.r, 0));
	rgb.g = Min(255, Max(rgb.g, 0));
	rgb.b = Min(255, Max(rgb.b, 0));
	// printf("%u, %u, %u, %u\n", rgb.t, rgb.r, rgb.g, rgb.b);
	*(unsigned int *)dst = create_trgb(rgb);
}

void cleanMlx()
{
    mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
    mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
    mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
#ifndef __APPLE__
    mlx_destroy_display(scene->mlx->mlx);
#endif
    free(scene->mlx->mlx);
    free(scene->mlx);
    exit(0);
}
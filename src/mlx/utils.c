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
	rgb.t = Clamp(rgb.t, 0, 255);
    rgb.r = Clamp(rgb.r, 0, 255);
    rgb.g = Clamp(rgb.g, 0, 255);
    rgb.b = Clamp(rgb.b, 0, 255);
	*(unsigned int *)dst = create_trgb(rgb);
}

bool	initialize_mlx(void){
	scene->mlx->mlx = mlx_init();
	if(!scene->mlx->mlx)
		return (false);
	scene->mlx->win = mlx_new_window(scene->mlx->mlx, scene->width,scene->height, "miniRT");
	if(!scene->mlx->win)
		return (false);
	scene->mlx->img = mlx_new_image(scene->mlx->mlx, scene->width,scene->height);
	if(!scene->mlx->img)
		return (false);
	scene->mlx->addr = mlx_get_data_addr(scene->mlx->img, &scene->mlx->bits_per_pixel,
			&scene->mlx->line_length, &scene->mlx->endian);
	if(!scene->mlx->addr)
		return (false);
	return (true);
}
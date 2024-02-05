#include <center.h>

//Accept 3 integers and return a single integer with the RGB value
int rgbGetter(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}


//Accepts a color, a shifting value, and an intensity value, and returns the new value of the color
double plusComponent(int color, int shifting, double intensity)
{
	return ((color >> shifting & 255) * intensity);
}

//Accepts a color and an intensity value, and returns the new value of the color
int colorMultiply(int color, double intensity){
	int r = plusComponent(color, 16, intensity);
	int g = plusComponent(color, 8, intensity);
	int b = plusComponent(color, 0, intensity);
	return rgbGetter(r, g, b);
}

//Accepts a color and an intensity value, and returns the new value of the color
void	my_mlx_pixel_put(double x, double y, int rgb)
{
	char	*dst;

	dst = scene->mlx->addr + (((int)y) * scene->mlx->line_length + ((int)x) * (scene->mlx->bits_per_pixel/ 8));
	*(unsigned int *)dst = rgb;
}


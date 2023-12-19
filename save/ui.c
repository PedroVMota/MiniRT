#include <center.h>

void	ShowUi(void)
{
	char *lightPosX = ft_ftoa(light.origin.x);
	char *lightPosY = ft_ftoa(light.origin.y);
	char *lightPosZ = ft_ftoa(light.origin.z);
	int padding_x = 10;
	int padding_y = 10;

	mlx_string_put(var()->mlx, var()->mlx_win, 10 + padding_x, 10 + padding_y,
		0x00FFFFFF, "light.origin.x = ");
	mlx_string_put(var()->mlx, var()->mlx_win, 10 + padding_x + 100, 10
		+ padding_y, 0x00FFFFFF, lightPosX);
	mlx_string_put(var()->mlx, var()->mlx_win, 10 + padding_x, 10 + padding_y
		+ 20, 0x00FFFFFF, "light.origin.y = ");
	mlx_string_put(var()->mlx, var()->mlx_win, 10 + padding_x + 100, 10
		+ padding_y + 20, 0x00FFFFFF, lightPosY);
	mlx_string_put(var()->mlx, var()->mlx_win, 10 + padding_x, 10 + padding_y
		+ 40, 0x00FFFFFF, "light.origin.z = ");
	mlx_string_put(var()->mlx, var()->mlx_win, 10 + padding_x + 100, 10
		+ padding_y + 40, 0x00FFFFFF, lightPosZ);
	free(lightPosX);
	free(lightPosY);
	free(lightPosZ);
}
#include <center.h>

/// @brief  Returns a pointer to a static variable of type t_vars.
/// @return  A pointer to a static variable of type t_vars.
t_vars	*var(void)
{
	static t_vars	var;

	return (&var);
}

/// @brief  Puts a pixel on the screen
/// @param x  The x coordinate of the pixel
/// @param y  The y coordinate of the pixel
/// @param color  The color of the pixel
void	my_mlx_pixel_put(int x, int y, int color)
{
	char	*dst;

	dst = var()->addr + (y * var()->line_length + x * (var()->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

/// @brief  Initializes the mlx library
/// @return  true if the initialization was successful, false otherwise
bool	initialize_mlx(void)
{
	var()->mlx = mlx_init();
	if (!var()->mlx)
		return (false);
	var()->mlx_win = mlx_new_window(var()->mlx, WIDTH, HEIGHT,
			"RayTracing Engine");
	if (!var()->mlx_win)
		return (false);
	var()->img = mlx_new_image(var()->mlx, WIDTH, HEIGHT);
	if (!var()->img)
		return (false);
	var()->addr = mlx_get_data_addr(var()->img, &var()->bits_per_pixel,
			&var()->line_length, &var()->endian);
	if (!var()->addr)
		return (false);
	return (true);
}

int	create_trgb(int t, int r, int g, int b)
{
	t > 255 ? t = 255 : t < 0 ? t = 0 : t;
	r > 255 ? r = 255 : r < 0 ? r = 0 : r;
	g > 255 ? g = 255 : g < 0 ? g = 0 : g;
	b > 255 ? b = 255 : b < 0 ? b = 0 : b;
	return (t << 24 | r << 16 | g << 8 | b);
}

size_t	get_digits(int n)
{
	size_t	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str_num;
	size_t		digits;
	long int	num;

	num = n;
	digits = get_digits(n);
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	if (!(str_num = (char *)malloc(sizeof(char) * (digits + 1))))
		return (NULL);
	*(str_num + digits) = 0;
	while (digits--)
	{
		*(str_num + digits) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(str_num + 0) = '-';
	return (str_num);
}
size_t	get_float_digits(float n)
{
	size_t	digits;
	int		integer_part;

	digits = 0;
	integer_part = (int)n;
	while (integer_part)
	{
		integer_part /= 10;
		digits++;
	}
	return (digits + 3); // 2 decimal digits + dot
}

char	*ft_ftoa(float n)
{
	size_t digits = get_float_digits(n);
	char *str_num = (char *)malloc(sizeof(char) * (digits + 1));
	if (!str_num)
		return (NULL);

	int integer_part = (int)n;
	int decimal_part = (n - integer_part) * 100; // Keep 2 decimal places
	if (decimal_part < 0)
		decimal_part *= -1; // Make sure decimal part is positive

	*(str_num + digits) = '\0';
	for (int i = 0; i < 2; i++) // Fill decimal part
	{
		*(str_num + --digits) = decimal_part % 10 + '0';
		decimal_part /= 10;
	}
	*(str_num + --digits) = '.'; // Place the decimal point

	while (integer_part) // Fill integer part
	{
		*(str_num + --digits) = integer_part % 10 + '0';
		integer_part /= 10;
	}

	return (str_num);
}
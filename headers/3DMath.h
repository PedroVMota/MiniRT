#pragma once
#include <math.h>
#include <stdbool.h>

typedef struct s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct s_color
{
	float		r;
	float		g;
	float		b;
	float		t;
}				t_color;	

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_hitinfo
{
	bool		hit;
	float		distance;
	t_vector	hitpoint;
	t_vector	normal;
}				t_hitinfo;
/// @brief This will be represented for the camera so we can render the image without any problem.
/// TODO - For now we have just 2 elements will be added more data.
typedef struct s_camera
{
	float		x_offset;
	float		y_offset;
	t_vector	origin;
	t_vector	normal;
	int			fov;
}				t_camera;

/// @brief A struct that will be for mlx manipulation.
typedef struct s_vars
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_vars;

typedef struct s_sphere
{
	t_vector	origin;
	double		diameter;
	t_color			color;
}				t_sphere;

typedef struct s_light
{
	t_vector	origin;
	float		brightness;
	int			color;
}				t_light;
float			dot(t_vector a, t_vector b);
void			normalized(t_vector *a);
float			Max(float a, float b);

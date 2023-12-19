#pragma once
#include <math.h>
#include <stdbool.h>

typedef struct s_object		t_object;
typedef struct s_vector		t_vector;
typedef enum e_type			t_type;
typedef struct s_color		t_color;
typedef struct s_values		t_values;

enum e_type{
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	AMBIENT,
	POINT,
	DIRECTIONAL,
	CAMERA,
	ERROR,
	EMPTY_LINE,
	COMMENT,
};

struct s_vector
{
	float x;
	float y;
	float z;
};

struct s_color
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
};

struct s_values{
	float t1;
	float t2;
};


struct	s_object {
	t_object	*next;
	t_vector	vector;
	t_type		type;
	t_color		color;
	int			specular;
	float		refletive;
	t_values	(*intersect)();
	void		(*rotate)();
	void		(*resize)(int ratio);
	float		height;
	float		intensity;
	float		theta;
	float		phi;
	float		qsi;
	int			checkerboard;
};


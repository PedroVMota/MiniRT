#pragma once

#include <libft.h>
#include <math.h>
#include <stdbool.h>
#include <error.h>
#include <string.h>
#include <errno.h>

typedef struct 	s_object		t_object;
typedef struct 	s_vector		t_vector;
typedef enum	e_type			t_type;
typedef struct  s_color		    t_color;
typedef struct  s_values	    t_values;
typedef struct  s_light		    t_light;
typedef struct	s_plane 	    t_plane;

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

struct	s_camera {
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
	t_vector	direction;
	float		fov;
};

struct	s_light {
	t_light		*next;
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

struct	s_plane {
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
	t_vector	direction;
};

struct	s_sphere {
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
	float		diameter;
};

struct	s_cylinder{
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
	t_vector	axis;
	float		diameter;
	t_plane		*up_cap;
	t_plane		*down_cap;
	int			flag;
};

struct s_cone
{
	t_object	*next;
	t_vector	vector;
	t_type		type;
	t_color		color;
	int			specular;
	float		refletive;
	t_values	(*intersect)();
	void		(*rotate)();
	void		(*move)(int x, int y);
	void		(*resize)(int ratio);
	float		height;
	float		intensity;
	float		theta;
	float		phi;
	float		qsi;
	int			checkerboard;
	t_vector	base;
	t_vector	direction;
	t_vector	tmp;
	float		m;
	float		radius;
}; 


#ifdef DEBUG_LOG
#define DEBUG_LOG

	#define INFO(msg) printf("%s[%s]%s", YEL, msg, RESET)
#endif
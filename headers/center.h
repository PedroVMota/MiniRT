#pragma once

#include <mlx.h>
#include <fcntl.h>
#include <mlx_int.h>

#include <Vector.h>
#include <errno.h>
#include <error.h>
#include <libft.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <mlx_function.h>
#include <pthread.h>


#define NUM_THREADS 12
#define WIDTH 1000
#define HEIGHT 1000

typedef struct s_object	t_object;
typedef t_object		*(*t_create_object)();

void					err(char *msg);
void					sucess(char *msg);
void					info(char *msg);

typedef enum e_type
{
	END_OF_FILE = -1,
	CAMERA,
	AMBIENT,
	POINT,
	DIRECTIONAL,
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	ERROR,
	EMPTY_LINE,
	COMMENT,
}						t_type;

typedef struct s_mlxdata
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_mlxdata;

typedef struct s_object
{
	struct s_object		*next;
	t_vector			vector;
	t_type				type;
	t_color				color;
	int					specular;
	float				refletive;
	t_values			(*intersect)();
	void				(*rotate)();
	void				(*resize)(int ratio);
	float				height;
	float				intensity;
	float				theta;
	float				phi;
	float				qsi;
	int					checkerboard;
}						t_object;

typedef struct s_camera
{
	struct s_object		*next;
	t_vector			vector;
	t_type				type;
	t_color				color;
	int					specular;
	float				refletive;
	t_values			(*intersect)();
	void				(*rotate)();
	void				(*resize)(int ratio);
	float				height;
	float				intensity;
	float				theta;
	float				phi;
	float				qsi;
	int					checkerboard;
	t_vector			direction;
	float				fov;
}						t_camera;

typedef struct s_light
{
	struct s_object		*next;
	t_vector			vector;
	t_type				type;
	t_color				color;
	int					specular;
	float				refletive;
	t_values			(*intersect)();
	void				(*rotate)();
	void				(*resize)(int ratio);
	float				height;
	float				intensity;
	float				theta;
	float				phi;
	float				qsi;
	int					checkerboard;
}						t_light;

typedef struct s_plane
{
	struct s_plane		*next;
	t_vector			vector;
	t_type				type;
	t_color				color;
	int					specular;
	float				refletive;
	t_values			(*intersect)();
	void				(*rotate)();
	void				(*resize)(int ratio);
	float				height;
	float				intensity;
	float				theta;
	float				phi;
	float				qsi;
	int					checkerboard;
	t_vector			direction;
}						t_plane;

typedef struct s_sphere
{
	struct s_sphere		*next;
	t_vector			vector;
	t_type				type;
	t_color				color;
	int					specular;
	float				refletive;
	t_values			(*intersect)();
	void				(*rotate)();
	void				(*resize)(int ratio);
	float				height;
	float				intensity;
	float				theta;
	float				phi;
	float				qsi;
	int					checkerboard;
	float				diameter;
}						t_sphere;

typedef struct s_cylinder
{
	struct s_cylinder	*next;
	t_vector			vector;
	t_type				type;
	t_color				color;
	int					specular;
	float				refletive;
	t_values			(*intersect)();
	void				(*rotate)();
	void				(*resize)(int ratio);
	float				height;
	float				intensity;
	float				theta;
	float				phi;
	float				qsi;
	int					checkerboard;
	t_vector			axis;
	float				diameter;
	t_plane				*up_cap;
	t_plane				*down_cap;
	int					flag;
}						t_cylinder;

typedef struct s_cone
{
	struct s_cone		*next;
	t_vector			vector;
	t_type				type;
	t_color				color;
	int					specular;
	float				refletive;
	t_values			(*intersect)();
	void				(*rotate)();
	void				(*move)(int x, int y);
	void				(*resize)(int ratio);
	float				height;
	float				intensity;
	float				theta;
	float				phi;
	float				qsi;
	int					checkerboard;
	t_vector			base;
	t_vector			direction;
	t_vector			tmp;
	float				m;
	float				radius;
}						t_cone;

typedef struct s_thread_data
{
	int id;
	int start_x;
	int end_x;
	t_vector direction;
}	t_thread_data;


typedef struct s_scene
{
	t_create_object		add_objs[8];

	char				*line;
	char				**objd;
	int					error;

	t_object			*camera;
	t_object			*lights;
	t_object			*objects;


	t_mlxdata			*mlx_data;


	//thread data;
	pthread_t			threads[NUM_THREADS];
	t_thread_data		thread_data[NUM_THREADS];
	pthread_mutex_t		*mutex;

	float aspect_ratio;
	float scale;
}						t_scene;
t_scene					*scene(void);

// bool functions
bool					check_object_identifier(char *s);
bool					type_model_struct(t_object *tmp);
bool					check_alloc(void *ptr);
bool					check_double_alloc(void **ptr);

// model generation
void					*generate_object(int size);
bool					isallnum(char *str, int error);
void					split_remove_element(char **arr, int index);
t_object				*camera_initilize(t_camera **obj, char **objd);

// add memory functions
void					objectaddlast(t_object *object);
int						create_c(char **objectdata);
int						create_a(char **objectdata);

// delete memory functions
void					*interator(char ***c, void (*f)(void *x));
void					report(void);
void					remove_object_list(void);

char					**ft_splitstr(char *str, char *charset);
void					*generate_object(int size);
void					init_add_functions(void);
void					objectaddlast(t_object *object);

//intersection functions;
t_values sphere_intersect(t_sphere *sphere, t_vector *ray);

#define RAD(x) (x * PI / 180)
#define DEG(x) (x * 180 / PI)
#define M_PI 3.14159265358979323846

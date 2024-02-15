/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:45:52 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 10:14:13 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CENTER_H
# define CENTER_H
# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

# define NUM_THREADS sysconf(_SC_NPROCESSORS_ONLN)
# define SPHERE 1
# define PLANE 2
# define CAMERA 3
# define POINT 4
# define AMBIENT 5
# define DIRECTIONAL 6
# define CYLINDER 7
# define PARABOLOID 8
# define UNKNOWN 9

typedef struct s_vector		t_vector;
typedef struct s_values		t_values;
typedef struct s_vec4		t_vec4;
typedef struct s_ray		t_ray;
typedef struct s_obj		t_obj;
typedef struct s_cam		t_cam;
typedef struct s_sp			t_sp;
typedef struct s_pl			t_pl;
typedef struct s_li			t_li;
typedef struct s_cy			t_cy;
typedef struct s_pa			t_pa;
typedef struct s_mlxdata	t_mlxdata;
typedef struct s_scene		t_scene;
typedef struct s_threadata	t_threadata;

struct						s_vector
{
	double					x;
	double					y;
	double					z;
};

struct						s_values
{
	double					t0;
	double					t1;
	t_vector				normal0;
	t_vector				normal1;
};

struct						s_vec4
{
	float					r;
	float					g;
	float					b;
};

struct						s_ray
{
	t_vector				o;
	t_vector				d;
	t_values				val;
	t_vector				normal;
	t_obj					*objc;
	double					ct;
	t_vector				_hit;
};

struct						s_obj
{
	t_obj					*next;
	t_vector				o;
	t_vector				d;
	int						color;
	t_vector				theta;
	int						type;
	double					specular;
	double					reflection;
	t_values				(*colision)(t_obj	*obj, t_ray	rayData);
};

struct						s_cam
{
	t_cam					*next;
	t_vector				o;
	t_vector				d;
	int						color;
	t_vector				theta;
	int						type;
	double					specular;
	double					reflection;
	double					diameter;
	t_values				(*colision)(t_cam	*obj, t_ray	rayData);
	double					fov;
	double					aspect;
	double					depth;
	double					width;
	double					height;
};

struct						s_sp
{
	t_sp					*next;
	t_vector				o;
	t_vector				d;
	int						color;
	t_vector				theta;
	int						type;
	double					specular;
	double					reflection;
	t_values				(*colision)(t_sp	*obj, t_ray	rayData);
	double					diameter;
};

struct						s_pl
{
	t_pl					*next;
	t_vector				o;
	t_vector				d;
	int						color;
	t_vector				theta;
	int						type;
	double					specular;
	double					reflection;
	t_values				(*colision)(t_pl	*obj, t_ray	rayData);
	float					size;
	int						checkerboard;
};

struct						s_li
{
	t_li					*next;
	t_vector				o;
	t_vector				d;
	int						color;
	t_vector				theta;
	int						type;
	double					specular;
	double					r;
	t_values				(*colision)(t_li	*obj, t_ray	rayData);
	double					i;
};

struct						s_cy
{
	t_cy					*next;
	t_vector				o;
	t_vector				d;
	int						color;
	t_vector				theta;
	int						type;
	double					specular;
	double					reflection;
	t_values				(*colision)(t_cy	*obj, t_ray	rayData);
	double					height;
	double					diameter;
};

struct						s_pa
{
	t_pa					*next;
	t_vector				o;
	t_vector				d;
	int						color;
	t_vector				theta;
	int						type;
	double					specular;
	double					reflection;
	t_values				(*colision)(t_pa	*obj, t_ray	rayData);
	double					diameter;

	double					p;
	double					height;
};

typedef struct s_mlxdata
{
	void					*mlx;
	void					*win;
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
}							t_mlxdata;

struct s_scene
{
	char					**props;
	t_cam					*camera;
	t_obj					*objects;
	t_li					*lights;
	t_li					*am;
	t_mlxdata				*mlx;
	int						width;
	int						height;
	int						depth;
	int						error;
};

struct s_threadata
{
	double					start_y;
	double					end_y;
};

extern t_scene				*g_scene;

// Mathmatical Functions
t_vector					norm(t_vector v);
t_vector					add(t_vector a, t_vector b);
t_vector					sub(t_vector a, t_vector b);
t_vector					mul(t_vector a, double b);
t_vector					divv(t_vector a, double b);
t_vector					unitvector(t_vector v);
t_vector					cross(t_vector a, t_vector b);
t_vec4						add4(t_vec4 a, t_vec4 b);
t_vec4						mul4(t_vec4 a, double b);
double						dot(t_vector a, t_vector b);
double						len(t_vector v);
double						maxval(double a, double b);
double						minval(double a, double b);
double						randomlimited(double min, double max);
t_vector					randomDirection(void);
t_vector					normalcalc(t_obj *obj, t_vector p);
t_vector					rotate(t_vector point, t_vector axis, double angle);

// Initialize Functions
t_scene						*init_main(int width, int height, int depth);
bool						initialize_mlx(t_scene *s);

// Mlx Functions
void						my_mlx_pixel_put(double x, double y, int rgb);
double						tocanvas(double x, bool isHeight);

// Color Functions
int							newrgb(int r, int g, int b);
double						mulcomp(int color, int shifting, double intensity);
int							colmul(int color, double intensity);

// Object Functions
t_obj						*newobject(size_t targetsize, t_values \
		(*colision)(t_obj *, t_ray));
t_sp						*newsphere(int type, char **props);
t_pl						*newplane(int type, char **props);
t_li						*newlight(int type, char **props);
t_cy						*newcylinder(int type, char **props);
t_cam						*newcamera(int type, char **props);
t_pa						*newparaboloid(int type, char **props);

t_values					quadraticsolver(double a, double b, double c);
t_values					spherecolision(t_obj *s, t_ray raydata);
t_values					planecolision(t_pl *plane, t_ray ray);
t_values					planecolisioncylinder(t_vector planep,
								t_vector planen, t_ray ray, double radius);
t_values					calculatetvalues(t_vector oc, t_ray ray,
								t_cy *cylinder);
t_values					calculatetopplanecolision(t_ray ray,
								t_cy *cylinder);
t_values					calculatebotplanecolision(t_ray ray,
								t_cy *cylinder);
t_values					calculateplanecolisions(t_ray ray, t_cy *cylinder);
t_vector					calculatenormalone(t_values t, t_vector p1,
								t_cy *cylinder);
t_vector					calculatenormaltwo(t_values t, t_vector p2,
								t_cy *cylinder);
t_values					calculatenormals(t_values t, t_vector p1,
								t_vector p2, t_cy *cylinder);
bool						iswithintopdisk(t_pa *paraboloid,
								t_vector intersection);
bool						iswithinbounds(t_pa *paraboloid,
								t_vector intersection);
t_values					calculatevaluespbld(t_pa *paraboloid, t_ray ray);
t_values					paraboloidcollision(t_pa *paraboloid, t_ray ray);
void						checkheight(t_values *t, t_vector p1, t_vector p2,
								t_cy *cylinder);
t_values					cylindercolision(t_cy *cylinder, t_ray ray);
void						objectadd(t_obj *nObj, void **list);

// Ray Functions && utils
t_ray						getraydir(t_vector o, double x, double y);
int							raycolor(t_ray rayTrace, int depth);
int							compcolor(int obj_color, t_vec4 objectColor);

// Reflection Functions
t_vector					reflect(t_vector incident, t_vector normal);
double						refl(t_vector data, t_vector reflected,
								t_vector vect);
double						to_reflect(t_vector light, t_vector n,
								t_vector vect, t_vector *reflected);
void						calc_combined(t_vec4 *combined, int light_color,
								double brightness);

// lighting Functions
void						diffusion(t_vec4 *combined, t_vector normal,
								t_vector light, t_li *src);
int							shadow(t_vector origin, t_vector dir, double t_min,
								double t_max);

t_vec4						limit(t_vec4 v);
int							skip(t_li **l);
t_obj						*intersections(t_ray *rt, double md, double d,
								bool set);
t_vec4						calcligh(t_vector p, t_vector n, t_vector v,
								double spec);

bool						parse(char *f);
bool						float_requirements(char *s, int start, int end);
bool						vector_requirements(char *s);
double						getfloat(char *prop, bool required, float *range,
								int standard_value);
t_vector					getvec4(char *prop, bool required, float max,
								float min);
void						uptadeerror(char *msg);
void						printprops(char **line, char *name,
								const char *funcname);
void						delprops(char ***line);
void						del(t_obj **lsg);
bool						distributeobject(int type, char **props);
bool						generateobject(char **props);
void						*object_error_handler(t_obj *obj, void **ptr,
								char *msg);

// Rotate Function for Camera
void						rotation(t_vector *v, t_vector *theta);

// Thread Functions
void						*renderframethread(void *arg);
void						renderframe(void);

// hooks
int							key_hook(int keycode, void *param);

#endif
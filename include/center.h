#include <fcntl.h>
#include <libft.h>
#include <math.h>
#include <mlx.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 12

#define SPHERE 1
#define PLANE 2
#define CAMERA 3
#define POINT 4
#define AMBIENT 5
#define DIRECTIONAL 6
#define CYLINDER 7
#define PARABOLOID 8
#define UNKNOWN 9

typedef struct Vec3
{
	double			x;
	double			y;
	double			z;
}					Vec3;

typedef struct tValues
{
	double			t0;
	double			t1;
	Vec3			normal0;
	Vec3			normal1;
}					tValues;

typedef struct Vec4
{
	float			r;
	float			g;
	float			b;
}					Vec4;

typedef struct Ray
{
	Vec3			o;
	Vec3			d;
	tValues			val;
	Vec3			normal;
	struct Object	*objc;
	double			ct;
	Vec3			_hit;
}					Ray;

typedef struct Object
{
	struct Object	*next;
	Vec3			o;
	Vec3			d;
	int				color;
	Vec3			theta;
	int				type;
	double			specular;
	double			reflection;
	tValues			(*colision)(struct Object	*obj, struct Ray rayData);
}					Object;

typedef struct Camera
{
	struct Camera	*next;
	Vec3			o;
	Vec3			d;
	int				color;
	Vec3			theta;
	int				type;
	double			specular;
	double			reflection;
	double			diameter;
	tValues			(*colision)(struct Object	*obj, struct Ray rayData);
	double			fov;
	double			aspect;
	double			depth;
	double			width;
	double			height;
}					Camera;

typedef struct Sphere
{
	struct Object	*next;
	Vec3			o;
	Vec3			d;
	int				color;
	Vec3			theta;
	int				type;
	double			specular;
	double			reflection;
	tValues			(*colision)(struct Object	*obj, struct Ray	rayData);
	double			diameter;
}					Sphere;

typedef struct Plane
{
	struct Object	*next;
	Vec3			o;
	Vec3			d;
	int				color;
	Vec3			theta;
	int				type;
	double			specular;
	double			reflection;
	tValues			(*colision)(struct Object	*obj, struct Ray	rayData);
	float			size;
	int				checkerboard;
}					Plane;

typedef struct Light
{
	struct Object	*next;
	Vec3			o;
	Vec3			d;
	int				color;
	Vec3			theta;
	int				type;
	double			specular;
	double			r;
	tValues			(*colision)(struct Object	*obj, struct Ray	rayData);
	double			i;
}					Light;

typedef struct Cylinder
{
	struct Object	*next;
	Vec3			o;
	Vec3			d;
	int				color;
	Vec3			theta;
	int				type;
	double			specular;
	double			reflection;
	tValues			(*colision)(struct Object	*obj, struct Ray	rayData);
	double			diameter;
	double			height;
}					Cylinder;

typedef struct Paraboloid
{
	struct Object	*next;
	Vec3			o;
	Vec3			d;
	int				color;
	Vec3			theta;
	int				type;
	double			specular;
	double			reflection;
	tValues			(*colision)(struct Object	*obj, struct	Ray rayData);
	double			diameter;

	double			p;
	double			height;
}					Paraboloid;

typedef struct s_mlxdata
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_mlxdata;

typedef struct scene
{

	char			**props;
	Camera			*camera;
	Object			*objects;
	Light			*lights;
	Light			*am;
	t_mlxdata		*mlx;
	int				width;
	int				height;
	int				depth;
	int				error;
}					gscene;

typedef struct ThreadData
{
    double	start_y;
    double	end_y;
}				ThreadData;


extern gscene		*g_scene;

// Mathmatical Functions
Vec3				norm(Vec3 v);
Vec3				add(Vec3 a, Vec3 b);
Vec3				sub(Vec3 a, Vec3 b);
Vec3				mul(Vec3 a, double b);
Vec3				divv(Vec3 a, double b);
Vec3				unitvector(Vec3 v);
Vec3				cross(Vec3 a, Vec3 b);
Vec4				add4(Vec4 a, Vec4 b);
Vec4				mul4(Vec4 a, double b);
double				dot(Vec3 a, Vec3 b);
double				len(Vec3 v);
double				maxval(double a, double b);
double				minval(double a, double b);
double				randomlimited(double min, double max);
Vec3				randomDirection(void);
Vec3				normalcalc(Object *obj, Vec3 p);
Vec3				rotate(Vec3 point, Vec3 axis, double angle);

// Initialize Functions
gscene				*init_main(int width, int height, int depth);
bool				initialize_mlx(gscene *s);

// Mlx Functions
void				my_mlx_pixel_put(double x, double y, int rgb);
double				tocanvas(double x, bool isHeight);

// Color Functions
int					newrgb(int r, int g, int b);
double				mulcomp(int color, int shifting, double intensity);
int					colmul(int color, double intensity);

// Object Functions
Object				*newobject(size_t targetsize, tValues (*colision)(struct Object *, Ray));
Sphere				*newsphere(int type, char **props);
Plane				*newplane(int type, char **props);
Light				*newlight(int type, char **props);
Cylinder			*newcylinder(int type, char **props);
Camera				*newcamera(int type, char **props);
Paraboloid			*newparaboloid(int type, char **props);

tValues				quadraticsolver(double a, double b, double c);
tValues				spherecolision(struct Object *s, Ray raydata);
tValues				planecolision(Plane *plane, Ray ray);
tValues				planecolisioncylinder(Vec3 planep, Vec3 planen, Ray ray,
						double radius);
tValues				calculatetvalues(Vec3 oc, Ray ray, Cylinder *cylinder);
tValues				calculatetopplanecolision(Ray ray, Cylinder *cylinder);
tValues				calculatebotplanecolision(Ray ray, Cylinder *cylinder);
tValues				calculateplanecolisions(Ray ray, Cylinder *cylinder);
Vec3				calculatenormalone(tValues t, Vec3 p1, Cylinder *cylinder);
Vec3				calculatenormaltwo(tValues t, Vec3 p2, Cylinder *cylinder);
tValues				calculatenormals(tValues t, Vec3 p1, Vec3 p2,
					Cylinder *cylinder);
bool				iswithintopdisk(Paraboloid *paraboloid, Vec3 intersection);
bool 				iswithinbounds(Paraboloid *paraboloid, Vec3 intersection);
tValues 			calculatevaluespbld(Paraboloid *paraboloid, Ray ray);
tValues				paraboloidcollision(Paraboloid *paraboloid, Ray ray);
void				checkheight(tValues *t, Vec3 p1, Vec3 p2,
						Cylinder *cylinder);
tValues				cylindercolision(Cylinder *cylinder, Ray ray);
void				objectadd(Object *nObj, void **list);

// Ray Functions && utils
Ray					getraydir(Vec3 o, double x, double y);
int					raycolor(Ray rayTrace, int depth);
int					compcolor(int obj_color, Vec4 objectColor);


// Reflection Functions
Vec3				reflect(Vec3 incident, Vec3 normal);
double				refl(Vec3 data, Vec3 reflected, Vec3 vect);
double				to_reflect(Vec3 light, Vec3 n, Vec3 vect, Vec3 *reflected);
void				calc_combined(Vec4 *combined, int light_color,
						double brightness);

// lighting Functions
void				diffusion(Vec4 *combined, Vec3 normal, Vec3 light,
						Light *src);
int					shadow(Vec3 origin, Vec3 dir, double t_min, double t_max);

Vec4				limit(Vec4 v);
int					skip(Light **l);
Object				*intersections(Ray *rt, double md, double d, bool set);
Vec4				calcligh(Vec3 p, Vec3 n, Vec3 v, double spec);

bool				parse(char *f);
bool				float_requirements(char *s, int start, int end);
bool				vector_requirements(char *s);
double				getfloat(char *prop, bool required, float *range,
						int standard_value);
Vec3				getvec4(char *prop, bool required, float max, float min);
void				uptadeerror(char *msg);
void				printprops(char **line, char *name, const char *funcname);
void				delprops(char ***line);
void				del(Object **lsg);
bool				distributeobject(int type, char **props);
bool				generateobject(char **props);
void				*object_error_handler(Object *obj, void **ptr, char *msg);

// Rotate Function for Camera
void				rotation(Vec3 *v, Vec3 *theta);

// Thread Functions
void*				renderframethread(void* arg);
void				renderframe(void);

//hooks
int					key_hook(int keycode, void *param);
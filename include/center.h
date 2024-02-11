#include <fcntl.h>
#include <mlx.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <libft.h>


#define SPHERE 1
#define PLANE 2
#define CAMERA 3
#define POINT 4
#define AMBIENT 5
#define DIRECTIONAL 6
#define CYLINDER 7
#define PARABOLOID 8



struct Vec3
{
	double x; //coordenadas
	double y;
	double z;
} typedef Vec3;

struct tValues
{
	double t0; //distance a partir do centro.
	double t1;
	Vec3 normal0; //normal do ponto de intersecao
	Vec3 normal1;
} typedef tValues;

struct Vec4
{
	float r;
	float g;
	float b;
} typedef Vec4;

struct Ray
{
	Vec3 o; //origem
	Vec3 d;	//direcao
	tValues val; //hit distance
	Vec3 normal; //calculo para calcular as sombras
	struct Object *ObjectClosest;
	double ct;
	Vec3 HitPoint;
} typedef Ray;

struct Object
{
	struct Object *next;
	Vec3 o; //origem
	Vec3 d; //direcao
	int color;
	Vec3 theta;
	int type; //tipo
	double specular;
	double reflection;
	tValues (*colision)(struct Object *obj, struct Ray rayData); //funcao da colisao
} typedef Object;

struct Camera
{
	struct Camera *next;
	Vec3 o;
	Vec3 d;
	Vec3 theta;
	int type;
	double fov;
	double aspectRatio;
	double width;
	double height;
} typedef Camera;


struct Sphere
{
	struct Object *next;
	Vec3 o; //origem
	Vec3 d; //direcao
	int color;
	Vec3 theta;
	int type; //tipo
	double specular;
	double reflection;
	tValues (*colision)(struct Object *obj, struct Ray rayData);
	double diameter;
} typedef Sphere;

struct Plane
{
	struct Object *next;
	Vec3 o; //origem
	Vec3 d; //direcao
	int color;
	Vec3 theta;
	int type; //tipo
	double specular;
	double reflection;
	tValues (*colision)(struct Object *obj, struct Ray rayData);
	float size;
	int checkerboard;
} typedef Plane;

struct Light
{
	struct Object *next;
	Vec3 o; //origem
	Vec3 d; //direcao
	int color;
	Vec3 theta;
	int type; //tipo
	double specular;
	double r;
	tValues (*colision)(struct Object *obj, struct Ray rayData);
	double i;
} typedef Light;


struct Cylinder
{
    struct Object *next;
	Vec3 o; //origem
	Vec3 d; //direcao
	int color;
	Vec3 theta;
	int type; //tipo
	double specular;
	double reflection;
	tValues (*colision)(struct Object *obj, struct Ray rayData);
    double diameter;
    double height;
} typedef Cylinder;

typedef struct Paraboloid {
    struct Object *next;
	Vec3 o; //origem
	Vec3 d; //direcao
	int color;
	Vec3 theta;
	int type; //tipo
	double specular;
	double reflection;
	tValues (*colision)(struct Object *obj, struct Ray rayData);
	double diameter;

	double p; // Parâmetro
	double height; // Altura
} Paraboloid;

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






struct scene
{
	Camera *camera;
	Object *objects;
	Light *lights;
	Light *am;

	// Mlx information.
	t_mlxdata *mlx;

	// Image information.
	int width;
	int height;
	int depth;

} typedef gscene;

extern gscene *g_scene;


//Mathmatical Functions
Vec3 norm(Vec3 v);
Vec3 add(Vec3 a, Vec3 b);
Vec3 sub(Vec3 a, Vec3 b);
Vec3 mul(Vec3 a, double b);
Vec3 divv(Vec3 a, double b);
Vec3 unitvector(Vec3 v);
Vec3 cross(Vec3 a, Vec3 b);
Vec4 add4(Vec4 a, Vec4 b);
Vec4 mul4(Vec4 a, double b);
double dot(Vec3 a, Vec3 b);
double len(Vec3 v);
double maxval(double a, double b);
double minval(double a, double b);
double randomlimited(double min, double max);
Vec3 randomDirection();
Vec3 normalcalc(Object *obj, Vec3 p);
Vec3 rotate(Vec3 point, Vec3 axis, double angle);

//Initialize Functions
gscene *init_main(int width, int height, int depth);
bool	initialize_mlx(gscene *s);

//Mlx Functions
void	my_mlx_pixel_put(double x, double y, int rgb);
double tocanvas(double x, bool isHeight);


//Color Functions
int newrgb(int r, int g, int b);
double mulcomp(int color, int shifting, double intensity);
int colmul(int color, double intensity);


//Object Functions
Object *newObject(size_t ModelType, Vec3 o, Vec3 d, Vec4 color, Vec3 theta);
Sphere *newSphere(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, double diameter, tValues (*colision)(), double reflec, double specular);
Plane *newPlane(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, float size, tValues (*colision)(), double reflec, double specular, int checkerboard);
Camera *newCamera(Vec3 o, Vec3 d, double fov, Vec3 theta);
Cylinder *newCylinder(Vec3 o, Vec3 d, double diameter, double height, Vec4 color, Vec3 theta, tValues (*colision)(), double reflec, double specular);
Light *newLight(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, double intensity, int type);
Paraboloid *newParaboloid(Vec3 o, Vec4 color, double p, double height, double diameter, tValues (*collision)(), double reflec, double specular);
tValues	quadraticsolver(double a, double b, double c);
tValues spherecolision(Sphere *s, Ray rayData);
tValues planecolision(Plane *plane, Ray ray);
tValues planecolisioncylinder(Vec3 planep, Vec3 planen, Ray ray, double radius);
tValues	calculatetvalues(Vec3 oc, Ray ray, Cylinder *cylinder);
tValues calculatetopplanecolision(Ray ray, Cylinder *cylinder);
tValues calculatebotplanecolision(Ray ray, Cylinder *cylinder);
tValues calculateplanecolisions(Ray ray, Cylinder *cylinder);
Vec3 calculatenormalone(tValues t, Vec3 p1, Cylinder *cylinder);
Vec3 calculatenormaltwo(tValues t, Vec3 p2, Cylinder *cylinder);
tValues calculatenormals(tValues t, Vec3 p1, Vec3 p2, Cylinder *cylinder);
tValues paraboloidCollision(Paraboloid *paraboloid, Ray ray) ;
void	checkheight(tValues *t, Vec3 p1, Vec3 p2, Cylinder *cylinder);
tValues cylindercolision(Cylinder *cylinder, Ray ray);
void objectadd(Object *nObj, Object **lst);

//Ray Functions
Ray getraydir(Vec3 o, double x, double y);

//Reflection Functions
Vec3 reflect(Vec3 incident, Vec3 normal);
double refl(Vec3 data, Vec3 reflected, Vec3 vect);
double to_reflect(Vec3 light, Vec3 n, Vec3 vect, Vec3 *reflected);
void calc_combined(Vec4 *combined, int light_color, double brightness);


//lighting Functions
void diffusion(Vec4 *combined, Vec3 normal, Vec3 light, Light *src);
int shadow(Vec3 origin, Vec3 dir, double t_min, double t_max);



Vec4	limit(Vec4 v);
int	skip(Light **l);
Object	*intersections(Ray *rt, double md, double d, bool set);
Vec4 calcligh(Vec3 p, Vec3 n, Vec3 v, double spec);
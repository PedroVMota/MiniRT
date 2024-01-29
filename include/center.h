#include <fcntl.h>
#include <mlx.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SPHERE 1
#define PLANE 2
#define CAMERA 3
#define POINT 4
#define AMBIENT 5
#define DIRECTIONAL 6

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
} typedef tValues;

struct Vec4
{
	unsigned int t; //alfa da cor
	unsigned int r;
	unsigned int g;
	unsigned int b;
} typedef Vec4;

struct Ray
{
	Vec3 o; //origem
	Vec3 d;	//direcao
	tValues val; //hit distance
	Vec3 normal; //calculo para calcular as sombras
	struct Object *ObjectClosest;
} typedef Ray;

struct Object
{
	struct Object *next;
	Vec3 o; //origem
	Vec3 d; //direcao
	Vec4 color;
	Vec3 theta;
	int type; //tipo
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
	Object *next;
	Vec3 o;
	Vec3 d;
	Vec4 color;
	Vec3 theta;
	int type;
	tValues (*colision)(struct Sphere *s, struct Ray rayData);
	double diameter;
} typedef Sphere;

struct Plane
{
	Object *next;
	Vec3 o;
	Vec3 d;
	Vec4 color;
	Vec3 theta;
	int type;
	tValues (*colision)(struct Plane *p, struct Ray rayData);
	float size;
} typedef Plane;

struct Light
{
	struct Object *next;
	Vec3 o;
	Vec3 d;
	Vec4 color;
	Vec3 theta;
	int type;
	tValues (*colision)(struct Object *obj, struct Ray rayData);
	double intensity;
} typedef Light;

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

	// Mlx information.
	t_mlxdata *mlx;

	// Image information.
	int width;
	int height;

} typedef gscene;


extern gscene *scene;

double Dot(Vec3 a, Vec3 b);
double Length(Vec3 v);
Vec3 Normalize(Vec3 v);
Vec3 Add(Vec3 a, Vec3 b);
Vec3 Sub(Vec3 a, Vec3 b);
Vec3 Mul(Vec3 a, double b);
Vec3 Div(Vec3 a, double b);
Vec3 unitVector(Vec3 v);
Vec3 Cross(Vec3 a, Vec3 b);
Vec4 Add4(Vec4 a, Vec4 b);
Vec4 Mul4(Vec4 a, double b);

double Clamp(double n, double min, double max);
int	create_trgb(Vec4 color);
Vec4 create_color(unsigned int t, unsigned int r, unsigned int g, unsigned int b);
void	my_mlx_pixel_put(double x, double y, Vec4 rgb);
bool	initialize_mlx(void);



Object *newObject(size_t ModelType, Vec3 o, Vec3 d, Vec4 color, Vec3 theta);
Sphere *newSphere(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, double diameter, tValues (*colision)());
Plane *newPlane(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, float size, tValues (*colision)());
Camera *newCamera(Vec3 o, Vec3 d, double fov, Vec3 theta);
Light *newLight(Vec3 o, Vec3 d, Vec4 color, Vec3 theta, double intensity, int type);

double toCanvas(double x, bool isHeight);
Ray GetRayDir(Vec3 o, double x, double y);
tValues sphereColision(Sphere *s, Ray rayData);
tValues planeColision(Plane *plane, Ray ray);
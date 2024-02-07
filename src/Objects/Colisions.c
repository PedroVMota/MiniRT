#include <center.h>

tValues	sphereColision(Sphere *s, Ray rayData)
{
	tValues		t;
	Vec3		oc;

	oc = Sub(rayData.o, s->o);
	t = quadraticsolver(Dot(rayData.d, rayData.d), 2 * Dot(oc, rayData.d), Dot(oc, oc) - (s->diameter));
	return (t);
}

tValues	planeColision(Plane *plane, Ray ray)
{
	double	numerator;
	tValues	t;

	numerator = 0;
	numerator = plane->d.x * (ray.o.x - plane->o.x);
	numerator += plane->d.y * (ray.o.y - plane->o.y);
	numerator += plane->d.z * (ray.o.z - plane->o.z);

	numerator *= -1;
	t.t0 = numerator / (plane->d.x * \
		ray.d.x + plane->d.y * \
		ray.d.y + plane->d.z * \
		ray.d.z);
	t.t1 = 0;
	return t;
}

double vcos(Vec3 a, Vec3 b) {
	return Dot(a, b) / (Length(a) * Length(b));
}

int p_is_outside(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 ip) {
	Vec3 v1 = Sub(p2, p1);
	Vec3 v2 = Sub(p3, p1);
	Vec3 vp = Sub(ip, p1);
	if (vcos(Cross(v1, v2), Cross(v1, vp)) < 0)
		return 1;
	return 0;
}

// Função para calcular a interseção de um raio com um triângulo
double rayTriangleIntersect(Vec3 rayOrigin, Vec3 rayDirection, Vec3 v0, Vec3 v1, Vec3 v2) {
	Vec3 edge1 = Sub(v1, v0);
	Vec3 edge2 = Sub(v2, v0);
	Vec3 h = Cross(rayDirection, edge2);
	double a = Dot(edge1, h);
	if (a > -0.00001 && a < 0.00001)
		return(INFINITY);
	double f = 1.0/a;
	Vec3 s = Sub(rayOrigin, v0);
	double u = f * Dot(s, h);
	if (u < 0.0 || u > 1.0)
		return(INFINITY);
	Vec3 q = Cross(s, edge1);
	double v = f * Dot(rayDirection, q);
	if (v < 0.0 || u + v > 1.0)
		return(INFINITY);
	// At this stage we can compute t to find out where the intersection point is on the line.
	double t = f * Dot(edge2, q);
	if (t > 0.001) // ray intersection
		return t;
	else // This means that there is a line intersection but not a ray intersection.
		return INFINITY;
}

// Função para calcular a interseção de um raio com uma pirâmide
// Função para calcular a interseção de um raio com uma pirâmide
tValues pyramidCollision(Pyramid *pyramid, Ray ray)
{
	tValues result;
	result.t0 = INFINITY;
	result.t1 = INFINITY;

	// Agora temos 5 faces na pirâmide, incluindo a base.
	// Agora temos 4 faces na pirâmide, excluindo a base.
for (int i = 1; i <= 4; i++) {
	// Cada face da pirâmide é um triângulo formado por três vértices.
	Vec3 v0 = pyramid->vertices[0]; // Top vertex is common for all faces
	Vec3 v1 = pyramid->vertices[i];
	Vec3 v2 = pyramid->vertices[i % 4 + 1]; // Changed from (i + 2) % 5 to i % 4 + 1

	// Calcula a interseção do raio com o triângulo.
	double t = rayTriangleIntersect(ray.o, ray.d, v0, v1, v2);

	// Se o raio intersecta o triângulo e a interseção está mais próxima do que a interseção atual,
	// atualiza a interseção e a normal.
	if (t < result.t0) {
		result.t0 = t;
		result.normal0 = pyramid->normals[i-1];
		}
	}

	// Check intersection with the base of the pyramid
	Vec3 v0 = pyramid->vertices[1];
	Vec3 v1 = pyramid->vertices[2];
	Vec3 v2 = pyramid->vertices[3];
	Vec3 v3 = pyramid->vertices[4];
	double t1 = rayTriangleIntersect(ray.o, ray.d, v0, v1, v3); // Changed v2 to v3
	double t2 = rayTriangleIntersect(ray.o, ray.d, v1, v2, v3); // Changed v0 to v1
	double t = (t1 < t2) ? t1 : t2;
	if (t < result.t0) {
		result.t0 = t;
		result.normal0 = pyramid->normals[4];
	}

	return result;
}
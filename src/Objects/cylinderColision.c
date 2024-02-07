#include <center.h>

tValues	quadraticsolver(double a, double b, double c)
{
	tValues		t;
	double		discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
		return ((tValues){(\
			-b - sqrt(discriminant)) / \
			(2 * a), (-b + sqrt(discriminant)) / \
			(2 * a)});
	return ((tValues){INFINITY, INFINITY});
}

tValues	planecolisioncylinder(Vec3 planep, Vec3 planen, Ray ray, double radius)
{
	tValues	t;
	double	denominador;
	double	numerator;
	Vec3	intersectionpoint;
	double	distance;

	denominador = Dot(ray.d, planen);
	if (fabs(denominador) < 0.001)
	{
		t.t0 = INFINITY;
		t.t1 = INFINITY;
		return (t);
	}
	numerator = Dot(Sub(planep, ray.o), planen);
	t.t0 = numerator / denominador;
	t.t1 = INFINITY;
	intersectionpoint = Add(ray.o, Mul(ray.d, t.t0));
	distance = Length(Sub(intersectionpoint, planep));
	if (distance > radius)
		t.t0 = INFINITY;
	return (t);
}

tValues	calculatetvalues(Vec3 oc, Ray ray, Cylinder *cylinder)
{
	tValues	t;
	double	radius;

	radius = cylinder->diameter / 2;
	return (quadraticsolver(Dot(ray.d, ray.d) - Dot(ray.d, cylinder->d) \
		* Dot(ray.d, cylinder->d) \
		, 2 * (Dot(ray.d, oc) - Dot(ray.d, cylinder->d) * \
		Dot(oc, cylinder->d)) \
		, Dot(oc, oc) - Dot(oc, cylinder->d) * Dot(oc, cylinder->d) \
		- radius * radius));
}

void	checkheight(tValues *t, Vec3 p1, Vec3 p2, Cylinder *cylinder)
{
	double	h1;
	double	h2;

	h1 = Dot(Sub(p1, cylinder->o), cylinder->d);
	h2 = Dot(Sub(p2, cylinder->o), cylinder->d);
	if (h1 < 0 || h1 > cylinder->height)
		t->t0 = INFINITY;
	if (h2 < 0 || h2 > cylinder->height)
		t->t1 = INFINITY;
}

tValues	calculatetopplanecolision(Ray ray, Cylinder *cylinder)
{
	Vec3	topcenter;

	topcenter = Add(cylinder->o, Mul(cylinder->d, cylinder->height));
	return (planecolisioncylinder(topcenter, cylinder->d, ray, \
	cylinder->diameter / 2));
}

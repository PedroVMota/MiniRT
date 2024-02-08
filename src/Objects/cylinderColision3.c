#include <center.h>

tValues	cylindercolision(Cylinder *cylinder, Ray ray)
{
	Vec3	oc;
	tValues	t;
	Vec3	p1;
	Vec3	p2;
	tValues	planecolisions;

	oc = sub(ray.o, cylinder->o);
	t = calculatetvalues(oc, ray, cylinder);
	p1 = add(ray.o, mul(ray.d, t.t0));
	p2 = add(ray.o, mul(ray.d, t.t1));
	checkheight(&t, p1, p2, cylinder);
	planecolisions = calculateplanecolisions(ray, cylinder);
	t.t0 = minval(t.t0, planecolisions.t0);
	return (calculatenormals(t, p1, p2, cylinder));
}
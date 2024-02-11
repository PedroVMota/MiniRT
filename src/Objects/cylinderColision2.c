#include <StandarLibrarys.h>

tValues	calculatebotplanecolision(Ray ray, Cylinder *cylinder)
{
	Vec3	botcenter;

	botcenter = cylinder->o;
	return (planecolisioncylinder(botcenter, cylinder->d, ray, \
	cylinder->diameter / 2));
}

tValues	calculateplanecolisions(Ray ray, Cylinder *cylinder)
{
	tValues	top;
	tValues	bot;
	tValues	result;

	top = calculatetopplanecolision(ray, cylinder);
	bot = calculatebotplanecolision(ray, cylinder);
	result.t0 = minval(top.t0, bot.t0);
	result.t1 = INFINITY;
	return (result);
}

Vec3	calculatenormalone(tValues t, Vec3 p1, Cylinder *cylinder)
{
	Vec3	normal;
	double	dotc;

	normal = sub(p1, cylinder->o);
	dotc = dot(normal, cylinder->d);
	return (norm(sub(normal, mul(cylinder->d, dotc))));
}

Vec3	calculatenormaltwo(tValues t, Vec3 p2, Cylinder *cylinder)
{
	Vec3	normal;
	double	dotc;

	normal = sub(p2, cylinder->o);
	dotc = dot(normal, cylinder->d);
	return (norm(sub(normal, mul(cylinder->d, dotc))));
}

tValues	calculatenormals(tValues t, Vec3 p1, Vec3 p2, Cylinder *cylinder)
{
	tValues	result;

	result.t0 = t.t0;
	result.t1 = t.t1;
	result.normal0 = calculatenormalone(t, p1, cylinder);
	result.normal1 = calculatenormaltwo(t, p2, cylinder);
	return (result);
}

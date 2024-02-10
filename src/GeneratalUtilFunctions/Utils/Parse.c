#include <center.h>

void updateError(char *msg);

static Vec3 newvec4(char *s, float max, float min)
{
	Vec3 v;
	char **split;

	if(vector_requirements(s))
	{
		updateError("Error: Invalid Vec3 value");
		return (Vec3){0,0,0};
	}
	split = ft_split(s, ',');
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	if (v.x > max || v.x < min || v.y > max || v.y < min || v.z > max ||
		v.z < min)
		updateError("Error: Invalid Vec out of range");
	delprops(split);
	return (v);
}

static double newfloat(char *s, float max, float min)
{
	double f;

	if(float_requirements(s, 0, (int)ft_strlen(s) - 1))
	{
		updateError("Error: Invalid float value");
		g_scene->error = 1;
		return (0);
	}
	f = ft_atof(s);
	if (f > max || f < min)
	{
		updateError("Error: Invalid float range");
		return (0);
	}
	return (f);
}

double	getFloat(char *prop, bool required, float *range, int standard_value)
{
	if(required)
	{
		if(!prop){
			updateError("Field required\n");
			return standard_value;
		}
		return (newfloat(prop, range[0], range[1]));
	}
	return standard_value;
}

Vec3 getVec4(char *prop, bool required, float max, float min)
{
	if(required && !prop)
	{
		if(!g_scene)
			updateError("Expected Vec3\n");
		return ((Vec3){0,0,0});
	}
	if(g_scene->error)
		return ((Vec3){0,0,0});
	return (newvec4(prop, max, min));
}
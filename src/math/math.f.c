#include <center.h>

float Lenght(t_vector a)
{
	return(sqrt(pow(a.x,2)+pow(a.y,2)+pow(a.z,2)));
}

t_vector Multiply(float k,  t_vector vec){
  return (t_vector){k * vec.x, k * vec.y, k * vec.z};
}

t_vector add(t_vector v1, t_vector v2){
  return (t_vector){v1.x + v2.x , v1.y + v2.y , v1.z + v2.z };
}


float Max(float a, float b)
{
	if (a > b)
		return a;
	return b;
}

float Min(float a, float b)
{
	if(a < b)
		return a;
	return b;
}

float	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void normilized(t_vector *vector)
{
	float length;

	length = Lenght(*vector);
	vector->x /= length;
	vector->y /= length;
	vector->z /= length;
}

t_vector operation(int type, t_vector a, t_vector b)
{
	t_vector result;

	if(type == ADD)
	{
		result.x = a.x + b.x;
		result.y = a.y + b.y;
		result.z = a.z + b.z;
	}
	if(type == SUBTRACT)
	{
		result.x = a.x - b.x;
		result.y = a.y - b.y;
		result.z = a.z - b.z;
	}
	if(type == MULTIPLY)
	{
		result.x = a.x * b.x;
		result.y = a.y * b.y;
		result.z = a.z * b.z;
	}
	if(type == DIVISION)
	{
		result.x = a.x / b.x;
		result.y = a.y / b.y;
		result.z = a.z / b.z;
	}
	return result;
}
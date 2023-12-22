#ifndef VECTOR_H
#define VECTOR_H
#pragma once

typedef struct 	s_vector		t_vector;
typedef struct  s_color		    t_color;
typedef struct  s_values	    t_values;

struct s_vector
{
	float x;
	float y;
	float z;
};

struct s_color
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
};

struct s_values{
	float t1;
	float t2;
};

t_vector vector_generator(char *vector);
t_color color_generator(char *color);

#endif
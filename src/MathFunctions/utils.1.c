#include <center.h>

double degrees_to_radians(double degrees)
{
    return degrees * M_PI / 180.0;
}

double random_double()
{
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

double randomLimited(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

double Clamp(double n, double min, double max){
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}

double Max(double a, double b)
{
    if (a > b)
        return a;
    return b;
}

double Min(double a, double b)
{
    if (a < b)
        return a;
    return b;
}

double toCanvas(double x, bool isHeight){
    if(isHeight)
        return scene->height / 2 - x;
    return x + scene->width / 2;
}
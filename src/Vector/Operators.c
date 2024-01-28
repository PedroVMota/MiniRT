#include "center.h"

double Dot(Vec3 a, Vec3 b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double Length(Vec3 v){
    return sqrt(Dot(v, v));
}

Vec3 Normalize(Vec3 v){
    double len = Length(v);
    return (Vec3){v.x / len, v.y / len, v.z / len};
}

Vec3 Add(Vec3 a, Vec3 b){
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}
Vec3 Sub(Vec3 a, Vec3 b){
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}
Vec3 Mul(Vec3 a, double b){
    return (Vec3){a.x * b, a.y * b, a.z * b};
}
Vec3 Div(Vec3 a, double b){
    return (Vec3){a.x / b, a.y / b, a.z / b};
}

Vec3 unitVector(Vec3 v){
	double len = Length(v);
	return (Vec3){v.x / len, v.y / len, v.z / len};
}

Vec3 Cross(Vec3 a, Vec3 b){    return (Vec3){a.y * b.z - a.z * b.y,
                  a.z * b.x - a.x * b.z,
                  a.x * b.y - a.y * b.x};
}

double Clamp(double n, double min, double max){
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}
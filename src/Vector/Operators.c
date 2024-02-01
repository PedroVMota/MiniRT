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



Vec4 Add4(Vec4 a, Vec4 b) {
    Vec4 result;
    result.t = a.t + b.t;
    result.r = a.r + b.r;
    result.g = a.g + b.g;
    result.b = a.b + b.b;
    return result;
}

Vec4 Mul4(Vec4 a, double b) {
    Vec4 result;
    result.r = a.r * b;
    result.g = a.g * b;
    result.b = a.b * b;
    return result;
}

Vec3 randomDirection()
{
    while (true) {
        Vec3 D;
        D.x = randomLimited(-1, 1);
        D.y = randomLimited(-1, 1);
        D.z = randomLimited(-1, 1);
        if(Length(D) < 0)
            return D;
    }
}

Vec3 Reflect(Vec3 incident, Vec3 normal) {
    return Sub(incident, Mul(normal, 2 * Dot(incident, normal)));
}
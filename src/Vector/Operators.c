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
    result.r = minval(a.r + b.r, 255);
    result.g = minval(a.g + b.g, 255);
    result.b = minval(a.b + b.b, 255);
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
        D.x = randomlimited(-1, 1);
        D.y = randomlimited(-1, 1);
        D.z = randomlimited(-1, 1);
        if(Length(D) < 0)
            return D;
    }
}

Vec3 Reflect(Vec3 incident, Vec3 normal) {
    return Sub(incident, Mul(normal, 2 * Dot(incident, normal)));
}

Vec3 rotate(Vec3 point, Vec3 axis, double angle) {
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);
    Vec3 u = Normalize(axis);

    Vec3 rotatedPoint;
    rotatedPoint.x = (cosTheta + u.x * u.x * (1 - cosTheta)) * point.x
                   + (u.x * u.y * (1 - cosTheta) - u.z * sinTheta) * point.y
                   + (u.x * u.z * (1 - cosTheta) + u.y * sinTheta) * point.z;
    rotatedPoint.y = (u.y * u.x * (1 - cosTheta) + u.z * sinTheta) * point.x
                   + (cosTheta + u.y * u.y * (1 - cosTheta)) * point.y
                   + (u.y * u.z * (1 - cosTheta) - u.x * sinTheta) * point.z;
    rotatedPoint.z = (u.z * u.x * (1 - cosTheta) - u.y * sinTheta) * point.x
                   + (u.z * u.y * (1 - cosTheta) + u.x * sinTheta) * point.y
                   + (cosTheta + u.z * u.z * (1 - cosTheta)) * point.z;

    return rotatedPoint;
}
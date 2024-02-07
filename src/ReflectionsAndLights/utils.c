#include <center.h>

Vec3 reflect_ray(Vec3 light, Vec3 normal)
{
    Vec3 result;

    double dot_product = normal.x * light.x + normal.y * light.y + normal.z * light.z;

    result.x = light.x - 2 * normal.x * dot_product;
    result.y = light.y - 2 * normal.y * dot_product;
    result.z = light.z - 2 * normal.z * dot_product;

    return result;
}

double to_reflect(Vec3 light, Vec3 n, Vec3 vect, Vec3 *reflected)
{
    double r_dot_v;

    *reflected = reflect_ray(light, n);
    r_dot_v = reflected->x * vect.x + reflected->y * vect.y + reflected->z * vect.z;

    return r_dot_v;
}

double compute_refl(Vec3 data, Vec3 reflected, Vec3 vect)
{
    double bright;
    double length_reflected = sqrt(reflected.x * reflected.x + reflected.y * reflected.y + reflected.z * reflected.z);
    double length_vect = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);

    bright = data.x * pow(data.y / (length_reflected * length_vect), data.z);

    return bright;
}

void diffusion(Vec4 *combined, Vec3 normal, Vec3 light, Light *src)
{
    double n_dot_l;
    double bright;

    n_dot_l = Dot(normal, light);
    if (n_dot_l > 0)
    {
        bright = src->intensity * n_dot_l /
                 (Length(normal) * Length(light));
        calc_combined(combined, src->color, bright);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colisions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 01:06:59 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/12 19:55:07 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

tValues	spherecolision(struct Object *s, Ray raydata)
{
	tValues	t;
	Vec3	oc;
	Sphere	*sphere;

	sphere = (Sphere *)s;
	oc = sub(raydata.o, sphere->o);
	t = quadraticsolver(dot(raydata.d, raydata.d), 2 * dot(oc, raydata.d), \
	dot(oc, oc) - (sphere->diameter));
	return (t);
}

tValues	planecolision(Plane *plane, Ray ray)
{
	double	numerator;
	tValues	t;

	numerator = 0;
	numerator = plane->d.x * (ray.o.x - plane->o.x);
	numerator += plane->d.y * (ray.o.y - plane->o.y);
	numerator += plane->d.z * (ray.o.z - plane->o.z);
	numerator *= -1;
	t.t0 = numerator / (plane->d.x * \
		ray.d.x + plane->d.y * \
		ray.d.y + plane->d.z * \
		ray.d.z);
	t.t1 = 0;
	return (t);
}

double vcos(Vec3 a, Vec3 b) {
	return dot(a, b) / (len(a) * len(b));
}

int p_is_outside(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 ip) {
	Vec3 v1 = sub(p2, p1);
	Vec3 v2 = sub(p3, p1);
	Vec3 vp = sub(ip, p1);
	if (vcos(cross(v1, v2), cross(v1, vp)) < 0)
		return 1;
	return 0;
}

bool isWithinTopDisk(Paraboloid *paraboloid, Vec3 intersection) {
    double rMax = paraboloid->diameter / 2; // Define your maximum radius

    // Calculate the distance from the intersection to the center of the disk in the xy plane
    double dx = intersection.x - paraboloid->o.x;
    double dy = intersection.y - paraboloid->o.y;
    double distance = sqrt(dx*dx + dy*dy);

    // Check if the intersection is within the top disk
    return intersection.z >= paraboloid->height && distance <= rMax;
}

bool isWithinBounds(Paraboloid *paraboloid, Vec3 intersection) {
    double zMin = 10; // Define your zMin
    double zMax = 10000; // Define your zMax
    return intersection.z >= zMin && intersection.z <= zMax;
}

tValues paraboloidCollision(Paraboloid *paraboloid, Ray ray) 
{
	printf("Paraboloid\n");
    tValues t;
    Vec3 oc = sub(ray.o, paraboloid->o);
    double a =  pow(ray.d.x, 2) / pow(paraboloid->diameter, 2) + pow(ray.d.y, 2) / pow(paraboloid->height, 2);
    double b = 2 * (ray.d.x * oc.x / pow(paraboloid->diameter, 2) + ray.d.y * oc.y / pow(paraboloid->height, 2) - ray.d.z);
    double c = pow(oc.x, 2) / pow(paraboloid->diameter, 2) + pow(oc.y, 2) / pow(paraboloid->height, 2) - oc.z;
    t = quadraticsolver(a, b, c);

    Vec3 intersection1 = add(ray.o, mul(ray.d, t.t0));
    Vec3 intersection2 = add(ray.o, mul(ray.d, t.t1));

    if (!isWithinBounds(paraboloid, intersection1) || isWithinTopDisk(paraboloid, intersection1)) {
        t.t0 = -1;
    }

    if (!isWithinBounds(paraboloid, intersection2) || isWithinTopDisk(paraboloid, intersection2)) {
        t.t1 = -1;
    }

    return t;
}
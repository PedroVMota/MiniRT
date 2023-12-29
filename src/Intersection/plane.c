#include <center.h>

t_vector vector_sub(t_vector *a, t_vector *b);
float dot(t_vector a, t_vector b);
t_values QuadraticFormula(float a, float b, float c);


/*
	Plane equation: Ax + By + Cz + D = 0
	Ax is the dot product of the normal vector of the plane and the point of the plane
	By is the dot product of the normal vector of the plane and the point of the plane
	Cz is the dot product of the normal vector of the plane and the point of the plane
	D is the dot product of the normal vector of the plane and the point of the plane

	to calculate the normal vector we need 3 points of the plane:
		- p1
		- p2
		- p3
	
	Ray equation: P = P0 + t * V
	P0 is the origin of the ray
	t is the distance from the origin of the ray to the point of the plane
	V is the direction of the ray

	Intersection calculation:
	
	a(P0x + t * Vx) + b(P0y + t * Vy) + c(P0z + t * Vz) + d = 0

*/
t_values plane_intersect(t_plane *plane, t_vector *ray) {
    t_values result;

    // Assuming the plane equation is ax + by + cz + d = 0
    float denominator = plane->vector.x * ray->x + plane->vector.y * ray->y + plane->vector.z * ray->z;

    // Check if the ray is parallel to the plane
    if (fabs(denominator) < 1e-6) {
        // No intersection, set both t1 and t2 to infinity
        result.t1 = result.t2 = INFINITY;
    } else {
        // Calculate t values for intersection
        result.t1 = - (plane->vector.x * ray->x + plane->vector.y * ray->y + plane->vector.z * ray->z + plane->height) / denominator;
        result.t2 = result.t1;

        // Check the direction of the ray relative to the plane normal
        float dotProduct = plane->vector.x * ray->x + plane->vector.y * ray->y + plane->vector.z * ray->z;
        if (dotProduct < 0) {
            // Ray is approaching the plane, keep the result
        } else {
            // Ray is leaving the plane, set both t1 and t2 to infinity
            result.t1 = result.t2 = INFINITY;
        }
    }

    return result;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theta.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:27:24 by pedro             #+#    #+#             */
/*   Updated: 2024/02/18 19:05:27 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

// This function calculates the dot product of two 2D vectors.
double	individual_dot(double a1, double a2, double b1, double b2)
{
	return (a1 * b1 + a2 * b2);
}

// This function calculates the length of a 2D vector.
double	len_2d(int a, int b)
{
	return (sqrt(a * a + b * b));
}

/*!SECTION

	This function calculates the angle between the `original` vector and the
		`d` in the x direction.
	It does so by calculating the dot product of the two vectors and dividing it
		by the product of their lengths.
	It then uses the acos function to calculate the angle in radians.
	If the d is pointing downwards, the angle is multiplied by -1.

	@param original The original vector.
	@param d The new vector.
	@return The angle between the two vectors in the x direction.

*/
double	get_theta_x(t_vector original, t_vector d)
{
	double	x;

	x = individual_dot(original.y, original.z, d.y, d.z);
	if (!len_2d(d.y, d.z)
		|| !len_2d(original.y, original.z))
		x = 0;
	else if (x > 0)
		x = acos(x / len_2d(d.y, d.z));
	else
		x = M_PI - acos(x / len_2d(d.y, d.z));
	if (d.y < 0)
		x *= -1;
	return (x);
}

/*!SECTION
	This function is similar to find_theta_x, but it calculates the angle in
	the y direction. It uses the x and z components of the vectors instead of
	the y and z components.
*/
double	get_theta_y(t_vector original, t_vector d)
{
	double	y;

	y = individual_dot(original.x, original.z, d.x, d.z);
	if (!len_2d(d.x, d.z)
		|| !len_2d(original.x, original.z))
		y = 0;
	else
		y = acos(y / len_2d(d.x, d.z));
	if (d.x < 0)
		y *= -1;
	return (y);
}

/*!SECTION
	The find_theta_z function would calculate the angle between the original
		vector and the d in the z direction.
	It would use the x and y components of the vectors instead of the y and z
		components (for find_theta_x) or x and z components (for find_theta_y).
		Here's how you can define it:
*/

t_vector	applyrot(t_vector original, t_vector nt)
{
	t_vector	theta;

	theta.x = get_theta_x(original, nt);
	theta.y = get_theta_y(original, nt);
	theta.z = individual_dot(original.x, original.y, nt.x, nt.y);
	if (!len_2d(nt.x, nt.y) || \
		!len_2d(original.x, original.y))
		theta.z = 0;
	else if (theta.z > 0)
		theta.z = acos(theta.z / len_2d(nt.x, nt.y));
	else
		theta.z = -M_PI + \
				acos(theta.z / len_2d(nt.x, nt.y));
	return (theta);
}

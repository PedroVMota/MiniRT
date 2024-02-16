/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sinwave.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:58:09 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/16 17:58:14 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_vector x_axis_rotation(t_vector vec, double angle)
{
    t_vector row1;
    t_vector row2;
    t_vector row3;
    t_vector rotated;
    double rad_angle;

    rad_angle = angle * M_PI / 180;
    row1 = (t_vector){1, 0, 0};
    row2 = (t_vector){0, cos(rad_angle), -sin(rad_angle)};
    row3 = (t_vector){0, sin(rad_angle), cos(rad_angle)};
    rotated.x = vec.x * row1.x + vec.y * row1.y + vec.z * row1.z;
    rotated.y = vec.x * row2.x + vec.y * row2.y + vec.z * row2.z;
    rotated.z = vec.x * row3.x + vec.y * row3.y + vec.z * row3.z;
    return (rotated);
}

t_vector cartesian_to_spherical(t_vector cartesian)
{
    t_vector spherical;

    double r = sqrt(cartesian.x * cartesian.x + cartesian.y * cartesian.y + cartesian.z * cartesian.z);
    double theta = atan2(sqrt(cartesian.x * cartesian.x + cartesian.y * cartesian.y), cartesian.z); // inclination angle
    double phi = atan2(cartesian.y, cartesian.x); // azimuthal angle

    spherical.x = r;
    spherical.y = theta;
    spherical.z = phi;

    return spherical;
}

t_vec4 sinwave(t_ray rayTrace, t_obj *obj)
{
    double sinn;
    double scal;
    double angle = 45; // 45 degree rotation

    scal = 0.01; // Use a fixed value for the wavelength

    // Convert the hit point to spherical coordinates
    t_vector sphere_coords = cartesian_to_spherical(rayTrace._hit);

    // Rotate the coordinates
    t_vector rotated = x_axis_rotation(sphere_coords, angle);

    sinn = sin(rotated.z * scal) + sin(rotated.x * scal);

    // Convert the sin value to a color
    t_vec4 color = int_to_vec4(obj->color);
    color.r *= sinn; // Convert the sin value from [-1, 1] to [0, 1]
    color.g *= sinn;
    color.b *= sinn;

    return color;
}
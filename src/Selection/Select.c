/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:21:19 by pvital-m          #+#    #+#             */
/*   Updated: 2024/02/19 23:05:58 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <center.h>

static t_obj *objreturn(t_ray *s)
{
    t_obj *o = intersections(s, INFINITY, 0, false);
    if (!o)
        return NULL;
    
    printf("Type: %d", o->type);
    return o;
}

int rt_select(void)
{
    double xv;
    double yv;
    int x, y;
    

    xv = (gscene()->width / 2);
    yv = -(gscene()->height / 2);
    t_ray s;
    
    mlx_mouse_get_pos(gscene()->mlx->mlx, gscene()->mlx->win, &x, &y);

    x = x - (gscene()->width / 2);
    y = (y - (gscene()->height / 2)) * -1;
    printf("%d %d\n", x, y);
    s = getraydir(gscene()->camera->o, x, y);
    printf("selected: %p\n", gscene()->selected);
    
    printf("%f %f %f\n", s.d.x, s.d.y, s.d.z);
    gscene()->selected = objreturn(&s);
    
    mlx_pixel_put(gscene()->mlx->mlx, gscene()->mlx->win, tocanvas(x, false), tocanvas(y, true), 0x00ff0000);
    menu();
    
    return 0;
}
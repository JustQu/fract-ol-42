/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:38:27 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/20 13:14:28 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

void	map_julia(t_frctl_ptr f)
{
	f->z = complex_sq(f->z);
	f->z = complex_sum(f->z, f->c);
}

void	julia_current_value(t_frctl_ptr f, int x, int y)
{
	f->z.r = f->startx + f->xdx * x;
	f->z.i = f->starty - f->ydy * y;
}

t_frctl	init_julia(void)
{
	return ((t_frctl){julia, (t_complex){0., 0.}, (t_complex){0.265, 0.1},\
							1.5, 1.5, 50, 1.,\
							(t_vec2){400., 400.},\
							-1.5, 1.5, 0, 0, map_julia, julia_current_value,
							get_color});
}

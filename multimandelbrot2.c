/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multimandelbrot2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 16:59:33 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/13 17:36:04 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

void	map_multimandelbrot2(t_frctl_ptr f)
{
	f->z = complex_multi(f->z, f->z);
	f->z = complex_multi(f->z, f->z);
	f->z = complex_sum(f->z, f->c);
}

void	multimandelbrot2_current_value(t_frctl_ptr f, int x, int y)
{
	f->c.r = f->startx + f->xdx * x;
	f->c.i = f->starty - f->ydy * y;
	f->z = (t_complex) {0., 0.};
}

t_frctl	init_multimandelbrot2(void)
{
	return ((t_frctl){multimandelbrot2, (t_complex){0., 0.},\
								(t_complex){0.265, 0.1}, 2, 2, 50, 1.,\
								(t_vec2){400., 400.},\
								-2, 2, 0, 0, map_multimandelbrot2,\
								multimandelbrot2_current_value, get_color});
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:39:20 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/13 17:35:23 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

void	map_mandelbrot(t_frctl_ptr f)
{
	f->z = complex_sq(f->z);
	f->z = complex_sum(f->z, f->c);
}

void	mandelbrot_current_value(t_frctl_ptr f, int x, int y)
{
	f->c.r = f->startx + f->xdx * x;
	f->c.i = f->starty - f->ydy * y;
	f->z = (t_complex) {0., 0.};
}

t_frctl	init_mandelbrot(void)
{
	return ((t_frctl){mandelbrot, (t_complex){0., 0.},\
								(t_complex){0.265, 0.1}, 2, 2, 50, 1.,\
								(t_vec2){400., 400.},\
								-2.5, 2, 0, 0, map_mandelbrot,\
								mandelbrot_current_value, get_color});
}

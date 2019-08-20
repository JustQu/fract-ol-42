/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 20:24:52 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/20 13:30:23 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

void	map_ship(t_frctl_ptr f)
{
	t_complex c;

	c.r = ABS(f->z.r);
	c.i = ABS(f->z.i);
	c = complex_sq(c);
	f->z = c;
	f->z = complex_sum(f->z, f->c);
}

void	ship_current_value(t_frctl_ptr f, int x, int y)
{
	f->c.r = f->startx + f->xdx * x;
	f->c.i = -f->starty + f->ydy * y;
	f->z = (t_complex) {0., 0.};
}

t_frctl	init_ship(void)
{
	return ((t_frctl){ship,
						(t_complex){0., 0.},
						(t_complex){0.265, 0.1},
						1.5,
						1.5,
						50,
						1.,
						(t_vec2){400., 400.},
						-2.,
						1.5,
						0,
						0,
						map_ship,
						ship_current_value,
						get_color});
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorne.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 16:49:21 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/13 17:49:15 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

void	map_tricorne(t_frctl_ptr f)
{
	t_complex c;

	c.r = f->z.r;
	c.i = -f->z.i;
	c = complex_sq(c);
	f->z = c;
	f->z = complex_sum(f->z, f->c);
}

void	tricorne_current_value(t_frctl_ptr f, int x, int y)
{
	f->c.r = f->startx + f->xdx * x;
	f->c.i = -f->starty + f->ydy * y;
	f->z = (t_complex) {0., 0.};
}

t_frctl	init_tricorne(void)
{
	return ((t_frctl){julia, (t_complex){0., 0.},
								(t_complex){0.265, 0.1}, 2, 2, 64, 1.,
								(t_vec2){400., 400.},
								-2., 2, 0, 0, map_tricorne,
								tricorne_current_value,
								get_color});
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:28:19 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/13 17:36:01 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

int		get_color(t_frctl_ptr f, int i)//TODO:rename
{
	float	t;
	float	r;
	float	g;
	float	b;

	if (i == f->maxi)
		return (0);
	t = i + 1+ log(log(10) / log((f->z.r * f->z.r + f->z.i * f->z.i)))/log(2);
	r = sin(0.13 * t + 1.) * 100 + 100;
	g = (sin(0.19 * t + 2) * 100 + 100);
	b = sin(0.1 * t + 8) * 100 + 100;
	return ((((int)(r) << 16) & 0x00ff0000) |
			(((int)(g) << 8) & 0x0000ff00) |
			((int)(b) & 0x000000ff));
}

void	set_palette(t_param_ptr p)
{
	p->frctl.get_color = get_color;
}
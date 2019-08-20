/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:28:19 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/20 16:41:28 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

int	get_color5(t_frctl_ptr f, int i)
{
	float	t;
	float	r;
	float	g;
	float	b;

	if (i == f->maxi)
		return (0);
	t = i + 1 - log(log(sqrt(f->z.r * f->z.r + f->z.i * f->z.i)) / log(5))
		/ log(2);
	r = sin(0.13 * t + 1.) * 90 + 80;
	g = (sin(0.19 * t + 2) * 90 + 100);
	b = sin(0.3 * t + 8) * 55 + 169;
	return ((((int)r << 16) & 0x00ff0000) |
			(((int)g << 8) & 0x0000ff00) |
			((int)b & 0x000000ff));
}

/*
**gray smooth
*/

int	get_color(t_frctl_ptr f, int i)
{
	float	t;
	float	r;
	float	g;
	float	b;

	if (i == f->maxi)
		return (0);
	t = (i + 1 - log2(log2((f->z.r * f->z.r + f->z.i * f->z.i))));
	r = sin(.29 * t + 1) * 100 + 127;
	g = r;
	b = r;
	return ((((int)r << 16) & 0x00ff0000) |
			(((int)g << 8) & 0x0000ff00) |
			((int)b & 0x000000ff));
}

/*
**smooth grey green purple
*/

int	get_color4(t_frctl_ptr f, int i)
{
	float	t;
	float	r;
	float	g;
	float	b;

	if (i == f->maxi)
		return (0);
	t = i + 1 + log(log(10) / log((f->z.r * f->z.r + f->z.i * f->z.i)))
		/ log(2);
	r = sin(.29 * t + 1) * 100 + 100;
	g = (sin(0.16 * t + 2) * 100 + 100);
	b = r;
	return ((((int)r << 16) & 0x00ff0000) |
			(((int)g << 8) & 0x0000ff00) |
			((int)b & 0x000000ff));
}

/*
** smooth white blue gold
*/

int	get_color2(t_frctl_ptr f, int i)
{
	float	t;
	float	r;
	float	g;
	float	b;

	if (i == f->maxi)
		return (0);
	t = i + 1 - log(log(sqrt(f->z.r * f->z.r + f->z.i * f->z.i)) / log(5))
		/ log(2);
	r = sin(.29 * t + 1) * 100 + 100;
	b = (sin(0.16 * t + 2) * 100 + 100);
	g = r;
	return ((((int)r << 16) & 0x00ff0000) |
			(((int)g << 8) & 0x0000ff00) |
			((int)b & 0x000000ff));
}

/*
** smooth white grin pink
*/

int	get_color3(t_frctl_ptr f, int i)
{
	float	t;
	float	r;
	float	g;
	float	b;

	if (i == f->maxi)
		return (0);
	t = i + 1 - log(log(sqrt(f->z.r * f->z.r + f->z.i * f->z.i)) / log(5))
		/ log(2);
	r = sin(.1 * t + 1) * 90 + 100;
	b = r * 0.5;
	g = (sin(0.16 * t + 8) * 100 + 100);
	return ((((int)r << 16) & 0x00ff0000) |
			(((int)g << 8) & 0x0000ff00) |
			((int)b & 0x000000ff));
}

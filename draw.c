/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:42:42 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/07 19:28:05 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"
#include "fcntl.h"

/*
** TODO: more color options including smooth coloring
*/

static inline int		get_color(t_frctl_ptr f, int i)
{
	float	t;
	float	r;
	float	g;
	float	b;

	if (i == f->maxi)
		return (0);
	//t = i + 1 - log2(log2((f->z.r * f->z.r + f->z.i * f->z.i)));
	t = i;
	r = sin(0.13 * t + 1.);
	r *= 100.;
	r += 100.;
	g = (sin(0.16 * t + 2) * 100 + 100);
	//g += 100;
	b = sin(0.1 * t + 8) * 100 + 100;
	return ((((int)(r) << 16) & 0x00ff0000) |
			(((int)(g) << 8) & 0x0000ff00) |
			((int)(b) & 0x000000ff));
}

void			*thread_draw(void *args)
{
	t_thread_ptr	t;
	int				x;
	int				y;
	int				i;

	t = args;
	t->frctl.xdx = 2. * t->frctl.r1 / WIDTH;
	t->frctl.ydy = 2. * t->frctl.r1 / HEIGHT;
	y = HEIGHT / NTHREADS * t->id;
	while (y < HEIGHT / NTHREADS * (t->id + 1))
	{
		x = -1;
		while (++x < WIDTH)
		{
			t->frctl.get_value(&t->frctl, x, y);
			i = -1;
			while (++i < t->frctl.maxi && t->frctl.z.r * t->frctl.z.r + t->frctl.z.i * t->frctl.z.i <
					4)
				t->frctl.map(&t->frctl);
			put_pixel(&t->pic, x, y - HEIGHT / NTHREADS * t->id +
				(t->id == NTHREADS - 1 ? 0 : 1), get_color(&t->frctl, i));
		}
		y++;
	}
	return (0);
}

void			draw_fractal(t_param_ptr p)
{
	int i;

	i = -1;
	while (++i < NTHREADS)
	{
		p->thread_args[i].id = i;
		pthread_create(p->thread_id + i, NULL, thread_draw, p->thread_args + i);
	}
	i = -1;
	while (++i < NTHREADS)
		pthread_join(p->thread_id[i], 0);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->pic.img_ptr, 0, 0);
}

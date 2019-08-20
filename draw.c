/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:42:42 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/20 13:50:36 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"
#include "fcntl.h"

/*
** TODO: more color options including smooth coloring
*/

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
			while (++i < t->frctl.maxi && t->frctl.z.r * t->frctl.z.r
										+ t->frctl.z.i * t->frctl.z.i < 10)
				t->frctl.map(&t->frctl);
			put_pixel(&t->pic, x, y - HEIGHT / NTHREADS * t->id + (t->id
				== NTHREADS - 1 ? 0 : 1), t->frctl.get_color(&t->frctl, i));
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
		(p->thread_args + i)->frctl = p->frctl;
		p->thread_args[i].id = i;
		pthread_create(p->thread_id + i, NULL, thread_draw, p->thread_args + i);
	}
	i = -1;
	while (++i < NTHREADS)
		pthread_join(p->thread_id[i], 0);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->pic.img_ptr, 0, 0);
}

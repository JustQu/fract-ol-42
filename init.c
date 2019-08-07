/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:39:55 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/07 19:30:04 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

void	init_frctl_tb(t_frctl f[])
{
	f[julia] = init_julia();
	f[mandelbrot] = init_mandelbrot();
	f[ship] = init_ship();
	f[tricorne] = init_tricorne();
	f[multimandelbrot2] = init_multimandelbrot2();
}

void	init_thread(t_thread_ptr t, t_frctl_ptr f)
{
	t->frctl = *f;
}

void	init_param(t_param_ptr p, t_fractal_type f)
{
	int	i;

	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIDTH, HEIGHT, "Fract'ol");
	p->cntrl.follow_zoom = 1;
	p->cntrl.follow_mouse = 0;
	init_frctl_tb(p->frctl_tb);
	p->frctl = p->frctl_tb[f];
	p->thread_id = malloc(sizeof(pthread_t) * NTHREADS);
	p->thread_args = malloc(sizeof(t_thread) * NTHREADS);
	p->pic.img_ptr = mlx_new_image(p->mlx_ptr, 1000, 1000);
	p->pic.addr = mlx_get_data_addr(p->pic.img_ptr, &p->pic.bpp,
									&p->pic.size_line, &p->pic.endian);
	i = -1;
	while (++i < NTHREADS)
	{
		init_thread(p->thread_args + i, &p->frctl);
		(p->thread_args + i)->pic = p->pic;
		(p->thread_args + i)->pic.addr +=
			HEIGHT / NTHREADS * i * p->pic.size_line;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:41:01 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/13 17:05:06 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

void	zoom_in(t_param_ptr p, int x, int y)
{
	int	i;

	i = -1;
	p->frctl.zoom *= 1.05;
	if (p->cntrl.follow_zoom)
	{
		p->frctl.startx = p->frctl.startx + 2 * p->frctl.r1 * x
			/ WIDTH - p->frctl.r / p->frctl.zoom;
		p->frctl.starty = p->frctl.starty - 2 * p->frctl.r1 * y
			/ HEIGHT + p->frctl.r / p->frctl.zoom;
	}
	else
	{
		p->frctl.startx = p->frctl.startx + p->frctl.r1 - p->frctl.r
			/ p->frctl.zoom;
		p->frctl.starty = p->frctl.starty - p->frctl.r1 + p->frctl.r
		/ p->frctl.zoom;
	}
	p->frctl.r1 = p->frctl.r / p->frctl.zoom;
	while (++i < NTHREADS)
		(p->thread_args + i)->frctl = p->frctl;
	draw_fractal(p);
}

void	zoom_out(t_param_ptr p, int x, int y)
{
	int	i;

	i = -1;
	p->frctl.zoom *= 0.95;
	p->frctl.startx = p->frctl.startx + p->frctl.r1 - p->frctl.r
			/ p->frctl.zoom;
	p->frctl.starty = p->frctl.starty - p->frctl.r1 + p->frctl.r
		/ p->frctl.zoom;
	p->frctl.r1 = p->frctl.r / p->frctl.zoom;
	if (p->frctl.zoom < 1.)
	{
		p->frctl.startx = p->frctl_tb[p->frctl.type].startx;
		p->frctl.starty = p->frctl_tb[p->frctl.type].starty;
		p->frctl.r = p->frctl_tb[p->frctl.type].r;
		p->frctl.r1 = p->frctl_tb[p->frctl.type].r1;
		p->frctl.zoom = p->frctl_tb[p->frctl.type].zoom;
		p->frctl.zoom_coord = p->frctl_tb[p->frctl.type].zoom_coord;
	}
	while (++i < NTHREADS)
		(p->thread_args + i)->frctl = p->frctl;
	draw_fractal(p);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_param_ptr p;

	p = param;
	if (button == 4)
		zoom_in(p, x, y);
	if (button == 5)
		zoom_out(p, 400, 400);
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_param_ptr	p;
	int			i;

	p = param;
	if (p->cntrl.follow_mouse == 0)
		return (0);
	i = -1;
	p->frctl.c.r = 2. / WIDTH * x - 1;
	p->frctl.c.i = 2. / HEIGHT * y - 1;
	while (++i < NTHREADS)
		(p->thread_args + i)->frctl = p->frctl;
	draw_fractal(p);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:41:59 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/07 18:57:08 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

int	key_press(int keycode, void *param)
{
	t_param_ptr	p;
	int			i;

	p = param;
	i = -1;
	if (keycode == 5)
		p->cntrl.follow_zoom ^= 1;
	if (keycode == 3)
		p->cntrl.follow_mouse ^= 1;
	if (keycode == 27)
	{
		p->frctl.maxi += 10;
		while (++i < NTHREADS)
			(p->thread_args + i)->frctl = p->frctl;
		draw_fractal(p);
	}
	if (keycode == 24)
	{
		p->frctl.maxi -= 10;
		while (++i < NTHREADS)
			(p->thread_args + i)->frctl = p->frctl;
		draw_fractal(p);
	}
	return (1);
}

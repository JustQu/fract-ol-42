/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:41:59 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/20 14:54:11 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

void	key_press1(int keycode, t_param_ptr p)
{
	int	i;

	i = -1;
	if (keycode == KEY_ESC)
	{
		free(p->thread_id);
		free(p->thread_args);
		mlx_destroy_image(p->mlx_ptr, p->pic.img_ptr);
		mlx_destroy_window(p->mlx_ptr, p->win_ptr);
		exit(0);
	}
	if (keycode == KEY_TAB)
		set_palette(p);
	if (keycode == KEY_ONE)
		p->frctl = p->frctl_tb[0];
	if (keycode == KEY_TWO)
		p->frctl = p->frctl_tb[1];
	if (keycode == KEY_THREE)
		p->frctl = p->frctl_tb[2];
	if (keycode == KEY_FOUR)
		p->frctl = p->frctl_tb[3];
	if (keycode == KEY_FIVE)
		p->frctl = p->frctl_tb[4];
	draw_fractal(p);
}

int		key_press(int keycode, void *param)
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
		printf("%d\n", p->frctl.maxi);
		while (++i < NTHREADS)
			;
		draw_fractal(p);
	}
	if (keycode == 24)
	{
		p->frctl.maxi -= 10;
		while (++i < NTHREADS)
			(p->thread_args + i)->frctl = p->frctl;
		draw_fractal(p);
	}
	key_press1(keycode, p);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_palette.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:13:46 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/20 13:36:28 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

void	set_palette(t_param_ptr p)
{
	static int i;

	i++;
	if (i > 4)
		i = 0;
	if (i == 0)
		p->frctl.get_color = get_color;
	else if (i == 1)
		p->frctl.get_color = get_color2;
	else if (i == 2)
		p->frctl.get_color = get_color3;
	else if (i == 3)
		p->frctl.get_color = get_color4;
	else if (i == 4)
		p->frctl.get_color = get_color5;
	draw_fractal(p);
}

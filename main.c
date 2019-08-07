/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 20:00:15 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/07 19:20:57 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

int	main(int ac, char **av)
{
	t_param param;

	init_param(&param, julia);
	draw_fractal(&param);
	mlx_hook(param.win_ptr, 6, 0, mouse_move, &param);
	mlx_hook(param.win_ptr, 4, 0, mouse_press, &param);
	mlx_hook(param.win_ptr, 2, 0, key_press, &param);
	mlx_loop(param.mlx_ptr);
	return (1);
}

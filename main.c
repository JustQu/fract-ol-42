/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 20:00:15 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/20 16:47:05 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

size_t			ft_strlen(const char *s)
{
	const char *p;

	p = s;
	while (*p)
		p++;
	return (p - s);
}

int				ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char *p1;
	const unsigned char *p2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	while (*p1 && (*p1 == *p2))
	{
		++p1;
		++p2;
	}
	return (*p1 - *p2);
}

void			usage(char **av)
{
	write(2, "Usage: ", 8);
	write(2, av[0], ft_strlen(av[0]));
	write(2, " fractal_type\n", 15);
	write(2, "\t\tfractal_type:\tjulia\n\t\t\t\tmandelbrot\n\t\t\t\t"
	"ship\n\t\t\t\ttricorne\n\t\t\t\tmultimandelbrot\n", 80);
	exit(0);
}

t_fractal_type	get_type(char *s)
{
	if (ft_strcmp(s, "julia") == 0)
		return (julia);
	if (ft_strcmp(s, "mandelbrot") == 0)
		return (mandelbrot);
	if (ft_strcmp(s, "multimandelbrot") == 0)
		return (multimandelbrot2);
	if (ft_strcmp(s, "ship") == 0)
		return (ship);
	if (ft_strcmp(s, "tricorne") == 0)
		return (tricorne);
	return (None);
}

int				main(int ac, char **av)
{
	t_param			param;
	t_fractal_type	type;

	if (ac < 2 || ac > 2)
		usage(av);
	if ((type = get_type(av[1])) == None)
		usage(av);
	init_param(&param, type);
	draw_fractal(&param);
	mlx_hook(param.win_ptr, 6, 0, mouse_move, &param);
	mlx_hook(param.win_ptr, 4, 0, mouse_press, &param);
	mlx_hook(param.win_ptr, 2, 0, key_press, &param);
	mlx_loop(param.mlx_ptr);
	return (1);
}

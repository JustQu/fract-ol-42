/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:31:55 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/07 19:04:26 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frctl.h"

t_complex	complex_multi(t_complex x, t_complex y)
{
	return ((t_complex){x.r * y.r - x.i * y.i,
						x.i * y.r + x.r * y.i});
}

t_complex	complex_sum(t_complex x, t_complex y)
{
	return ((t_complex){x.r + y.r, x.i + y.i});
}

double		complex_mod(t_complex x)
{
	return (((x.r == 0 || x.i == 0) ? ABS(x.r) + ABS(x.i)
									: sqrt(x.r * x.r + x.i * x.i)));
}

t_complex	complex_sq(t_complex x)
{
	return ((t_complex){x.r * x.r - x.i * x.i,
						x.i * x.r + x.r * x.i});
}

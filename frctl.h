/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frctl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 19:58:59 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/07 19:16:32 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRCTL_H
# define FRCTL_H

# include "math.h"
# include "mlx.h"
# include "pthread.h"
# include "stdlib.h"
# include "stdio.h"

# define WIDTH 1000
# define HEIGHT 1000
# define NTHREADS 32

# define ABS(x) (((x) < 0.) ? (-(x)) : (x))

typedef enum e_fractal_type	t_fractal_type;
typedef struct s_complex	t_complex;
typedef struct s_vec2		t_vec2;
typedef struct s_frctl		t_frctl;
typedef struct s_thread		t_thread;
typedef struct s_cntrl		t_cntrl;
typedef struct s_param		t_param;
typedef	struct s_image		t_image;

typedef struct s_thread	*t_thread_ptr;
typedef struct s_frctl	*t_frctl_ptr;
typedef struct s_param	*t_param_ptr;
typedef void	(*t_map)(t_frctl_ptr);
typedef void	(*t_getval)(t_frctl_ptr, int, int);

# define NFRCTLS 6

enum		e_fractal_type
{
	julia,
	mandelbrot,
	ship,
	tricorne,
	multimandelbrot2,
	None
};

struct		s_complex
{
	double			r;
	double			i;
};

struct		s_vec2
{
	double				x;
	double				y;
};

struct		s_frctl
{
	t_fractal_type		type;
	t_complex			z;
	t_complex			c;
	double				r;
	double				r1;
	int					maxi;
	double				zoom;
	t_vec2				zoom_coord;
	double				startx;
	double				starty;
	double				xdx;
	double				ydy;
	t_map				map;
	t_getval			get_value;
};

struct		s_image
{
	void				*img_ptr;
	char				*addr;
	int					bpp;
	int					size_line;
	int					endian;
};

/*
** will be allocated on heap
** each thread will have its own copy
** to avoid shared resources
** each pic have size 800 x 50 pix
*/

struct		s_thread
{
	t_image				pic;
	t_frctl				frctl;
	int					id;
};

struct		s_cntrl
{
	int					follow_zoom;
	int					follow_mouse;
};

struct		s_param
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_frctl				frctl_tb[NFRCTLS];
	t_frctl				frctl;
	t_thread_ptr		thread_args;
	t_image				pic;
	pthread_t			*thread_id;
	t_cntrl				cntrl;
};

void		put_pixel(t_image *img, int x, int y, int color);
void		draw_fractal(t_param_ptr p);

void		init_param(t_param_ptr p, t_fractal_type f);
t_frctl		init_julia();
t_frctl		init_mandelbrot();
t_frctl		init_multimandelbrot2();
t_frctl		init_ship();
t_frctl		init_tricorne();

int			key_press(int keycode, void *param);
int			mouse_move(int x, int y, void *param);
int			mouse_press(int button, int x, int y, void *param);

t_complex	complex_multi(t_complex x, t_complex y);
t_complex	complex_sum(t_complex x, t_complex y);
double		complex_mod(t_complex x);
t_complex	complex_sq(t_complex x);

#endif

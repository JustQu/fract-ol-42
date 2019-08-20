/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frctl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 19:58:59 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/20 13:23:38 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRCTL_H
# define FRCTL_H

# include "math.h"
# include "mlx.h"
# include "pthread.h"
# include "stdlib.h"
# include "stdio.h"
# include "fcntl.h"
# include "unistd.h"

# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6
# define KEY_ZERO 29
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_SIX 22
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_NINE 25
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_MULTI 67
# define KEY_SPACE 49
# define KEY_ENTER 36
# define KEY_ESC 53
# define KEY_TAB 48

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
typedef int		(*t_getclr)(t_frctl_ptr , int);

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

enum		e_pallete
{
	smooth_grey = 1,
	smooth_pink_grey
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
	t_getclr			get_color;
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

void		set_palette(t_param_ptr p);
int			get_color(t_frctl_ptr f, int i);
int			get_color1(t_frctl_ptr f, int i);
int			get_color2(t_frctl_ptr f, int i);
int			get_color3(t_frctl_ptr f, int i);
int			get_color4(t_frctl_ptr f, int i);
int			get_color5(t_frctl_ptr f, int i);

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

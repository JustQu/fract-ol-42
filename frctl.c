#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stddef.h>
#include <mlx.h>

#define WIDTH 1000
#define HEIGHT 1000

/*
** r is for real part of complex number
** i is for imaginary part of complex number
*/

typedef struct 		s_complex
{
	double			r;
	double			i;
}					t_complex;

#define ABS(x) (((x) < 0.) ? (-(x)) : (x))

#define complex_multi(x, y) (t_complex){x.r * y.r - x.i * y.i,\
										x.i * y.r + x.r * y.i}									
#define complex_sum(x, y) (t_complex){(x).r + (y).r, (x).i + (y).i}
#define complex_mod(x) ((x.r == 0 || x.i == 0) ? ABS(x.r) + ABS(x.i)\
												: sqrt(x.r * x.r + x.i * x.i))
#define complex_sq(x) (t_complex){(x).r * (x).r - (x).i * (x).i,\
										(x).i * (x).r + (x).r * (x).i}	

#define NTHREADS 32

/*
** all fractales that programm support
*/

#define NFRCTLS 4
typedef enum			e_fractal_type
{
	julia,
	mandelbrot,
	ship,
	thricorne
}						t_fractal_type;

/*
** 
*/
typedef struct			s_vec2
{
	double				x;
	double				y;
}						t_vec2;


typedef struct s_thread	*t_thread_ptr;
typedef struct s_frctl	*t_frctl_ptr;

typedef void			(*t_map)(t_frctl_ptr);
typedef void			(*t_getval)(t_frctl_ptr, int, int);

typedef struct 			s_frctl
{
	t_fractal_type		type;
	t_complex			z;
	t_complex			c;
	double				r; // radius of fractal 1.5 for mandelbrot
	double				r1; //radius while zooming
	int					maxi;
	double				zoom;
	t_vec2				zoom_coord; // window coordinates of cursor
	double				startx;
	double				starty;
	double				xdx;
	double				ydy;
	t_map				map;
	t_getval			get_value;
}						t_frctl;

typedef struct			s_image
{
	void				*img_ptr;
	char				*addr;
	int					bpp;
	int					size_line;
	int					endian;
}						t_image;

/*
** will be allocated on heap
** each thread will have its own copy
** to avoid shared resources
** each pic have size 800 x 50 pix
*/

typedef struct			s_thread
{
	t_image				pic;
	t_frctl				frctl;
	int					id;
}						t_thread;

typedef struct			s_cntrl
{
	int					follow_zoom;
	int					follow_mouse;
}						t_cntrl;

typedef struct 			s_param
{
	void 				*mlx_ptr;
	void				*win_ptr;
	t_frctl				frctl_tb[NFRCTLS];
	t_frctl				frctl;
	t_thread_ptr		thread_args;
	t_image				pic;
	pthread_t			*thread_id;
	t_cntrl				cntrl;
}						t_param;
typedef struct s_param	*t_param_ptr;

void	map_julia(t_frctl_ptr f)
{
	f->z = complex_sq(f->z);
	f->z = complex_sum(f->z, f->c);
}

void	julia_current_value(t_frctl_ptr f, int x, int y)
{
	f->z.r = f->startx + f->xdx * x;
	f->z.i = f->starty - f->ydy * y;
}

void	map_mandelbrot(t_frctl_ptr f)
{
	f->z = complex_sq(f->z);
	f->z = complex_sum(f->z, f->c);
}

void	mandelbrot_current_value(t_frctl_ptr f, int x, int y)
{
	f->c.r = f->startx + f->xdx * x;
	f->c.i = f->starty - f->ydy * y;
	f->z = (t_complex) {0., 0.};
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char *p;


	if (x <= 0 || y <= 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	p = img->addr;
	p = (p + img->size_line * y) + ((x * img->bpp) >> 3);
	*(int *)p = color;
}

/*
** TODO: more color options including smooth coloring
*/

int		get_color(t_frctl_ptr f, int i)
{
	if (i == f->maxi)
		return 0;
	//double t = (i + 2 - log2(log2(sqrt(f->z.r * f->z.r + f->z.i * f->z.i)))) / f->maxi;
	double t = i + 1 - log(log(sqrt(f->z.r * f->z.r + f->z.i * f->z.i) / 2 / log(2))) / log2(2);
	//int r = (74 * t);
	int	r = (sin(0.13 * t + 1) * 100 + 100);
	//int g = (205 * t);
	int g = (sin(0.16 * t + 2) * 100 + 100);
	//int b = 250 * t;
	int b = sin(0.1 * t + 8) * 100 + 100;
	int color = ((((int)(r) << 16) & 0x00ff0000) | (((int)(g) << 8) & 0x0000ff00) | ((b) & 0x000000ff));
	return (color);
}

void	*thread_draw(void *args)
{
	t_thread_ptr t = args;
	int x;
	int y;
	int i;

	t->frctl.xdx = 2. * t->frctl.r1 / WIDTH;
	t->frctl.ydy = 2. * t->frctl.r1 / HEIGHT;
	y = HEIGHT / NTHREADS * t->id;
	//printf("\tthread #%d y: %d\n\tthread #%d xdx: %f\n\tthread #%d ydy: %f\n", 
	//				t->id + 1, y, t->id + 1, t->frctl.xdx, t->id + 1, t->frctl.ydy);
	while (y < HEIGHT / NTHREADS * (t->id + 1))
	{
		x = -1;
		while (++x < WIDTH)
		{			
			t->frctl.get_value(&t->frctl, x, y);
			i = -1;
			//printf("\tthread #%d z at\t(%d, %d):\t%f\t%f\n\tthread #%d c at\t(%d, %d):\t%f\t%f\n",
			//	t->id + 1, x, y, t->frctl.z.r, t->frctl.z.i,  t->id + 1, x, y, t->frctl.c.r, t->frctl.c.i);
			while (t->frctl.z.r * t->frctl.z.r + t->frctl.z.i * t->frctl.z.i < 4
														&& ++i < t->frctl.maxi)
				t->frctl.map(&t->frctl);
			int cl = get_color(&t->frctl, i);
			//if (y % 50 == 0)
			//	printf("\tpixel\t\t(%d, %d) colored in 0x%08X\n", x, y, cl);
			put_pixel(&t->pic, x, y - HEIGHT / NTHREADS * t->id + (t->id == NTHREADS - 1 ? 0 : 1), cl);
		}
		y++;
	}
	return (0);
}

void	draw_fractal(t_param_ptr p)
{
	int i;

	i = -1;
	while (++i < NTHREADS)
	{
		//printf("STARTING THREAD #%d...\n", i + 1);
		p->thread_args[i].id = i;
		pthread_create(p->thread_id + i, NULL, thread_draw, p->thread_args + i);
		//thread_draw(p->thread_args + i);
		//printf("OK\n");
	}
	i = -1;
	while (++i < NTHREADS)
	{
		//printf("ENDING THREAD #%d... ", i);
		pthread_join(p->thread_id[i], 0);
		//printf("OK\nPUTTTING IMAGE TO WINDOW AT (0, %d)... ", HEIGHT / NTHREADS * i);
		//mlx_put_image_to_window(p->mlx_ptr, p->win_ptr,
			//(p->thread_args + i)->pic.img_ptr, 0, HEIGHT / NTHREADS * i - (i == 0 ? 0 : 5));
		//printf("OK\n");
	}
	//printf("draw\n");
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->pic.img_ptr, 0, 0);
}

#define INIT_JULIA (t_frctl){julia, (t_complex){0., 0.}, (t_complex){0.265, 0.1},\
							1.5, 1.5, 100, 1.,\
							(t_vec2){400., 400.},\
							-1.5, 1.5, 0, 0, map_julia, julia_current_value}
#define INIT_MANDELBROT (t_frctl){julia, (t_complex){0., 0.},\
								(t_complex){0.265, 0.1}, 1.5, 1.5, 200, 1.,\
								(t_vec2){400., 400.},\
								-2., 1.5, 0, 0, map_mandelbrot,\
								mandelbrot_current_value}
void	init_frctl_tb(t_frctl f[])
{
	f[julia] = INIT_JULIA;
	f[mandelbrot] = INIT_MANDELBROT;
}

void	init_thread(t_thread_ptr t, t_frctl_ptr f)
{	
	t->frctl = *f;
	/*printf("FRACTAL PARAMS:\n\
	type: %d\n\
	z.r: %f\n\
	z.i: %f\n\
	c.r: %f\n\
	c.i %f\n\
	r: %f\n\
	r1: %f\n\
	maxi: %d\n\
	zoom: %f\n\
	zoom_coord.x: %f\n\
	zoom_coord.y: %f\n\
	startx: %f\n\
	starty: %f\n\
	xdx: %f\n\
	ydy: %f\n",
		t->frctl.type, t->frctl.z.r, t->frctl.z.i, t->frctl.c.r, t->frctl.c.i, t->frctl.r,
		t->frctl.r1, t->frctl.maxi, t->frctl.zoom, t->frctl.zoom_coord.x, t->frctl.zoom_coord.y,
		t->frctl.startx, t->frctl.starty, t->frctl.xdx, t->frctl.ydy);*/
	//printf("\tCREATING NEW IMAGE 100x100...\t");
	//t->pic.img_ptr = mlx_new_image(mlx_ptr, 800, HEIGHT / NTHREADS);
	//printf("OK\n");
	//t->pic.addr = mlx_get_data_addr(t->pic.img_ptr, &t->pic.bpp, &t->pic.size_line, &t->pic.endian);
	//printf("\tbpp: %d\n\tsize line: %d\n", t->pic.bpp, t->pic.size_line);
}

void	init_param(t_param_ptr p, t_fractal_type f)
{
	int	i;
	//printf("INIT PARAM:\n");
	//printf("INIT MLX...\t");
 	p->mlx_ptr = mlx_init();
	//printf("OK\nINIT WINDOW...\t");
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIDTH, HEIGHT, "Fract'ol");
	p->cntrl.follow_zoom = 1;
	p->cntrl.follow_mouse = 1;
	//printf("OK\nINIT FRCTL TB...\t");
	init_frctl_tb(p->frctl_tb);
	//printf("OK\nINIT FRCTL...\t");
	p->frctl = p->frctl_tb[f];
	//printf("OK\n");
	p->thread_id = malloc(sizeof(pthread_t) * NTHREADS);
	p->thread_args = malloc(sizeof(t_thread) * NTHREADS);
	p->pic.img_ptr = mlx_new_image(p->mlx_ptr, 1000, 1000);
	p->pic.addr = mlx_get_data_addr(p->pic.img_ptr, &p->pic.bpp, &p->pic.size_line, &p->pic.endian);
	i = -1;
	while (++i < NTHREADS)
	{
		//printf("INIT THREAD #%d...\n", i + 1);
		init_thread(p->thread_args + i, &p->frctl);
		(p->thread_args + i)->pic = p->pic;
		(p->thread_args + i)->pic.addr += HEIGHT / NTHREADS * i * p->pic.size_line;
		//printf("OK\n");
	}
}


int	mouse_press(int button, int x, int y, void *param)
{
	t_param_ptr p;
	int i;
	
	i = -1;
	p = param;
	if (button == 4) // zoom in
	{
		//printf("Mouse zoom at %d\t%d\n", x, y);
		//printf("\tzooom: %f\n\tleft x: %f\n\ttop y: %f\n\tradius: %f\n", p->frctl.zoom, p->frctl.startx, p->frctl.starty, p->frctl.r1);
		p->frctl.zoom *= 1.05;
		if (p->cntrl.follow_zoom)
		{
			p->frctl.startx = p->frctl.startx + 2 * p->frctl.r1 * x / WIDTH - p->frctl.r / p->frctl.zoom; // left poin starts with -r value
			p->frctl.starty = p->frctl.starty - 2 * p->frctl.r1 * y / HEIGHT + p->frctl.r / p->frctl.zoom; // top point starts with +r value
		}
		else
		{
			p->frctl.startx = p->frctl.startx + p->frctl.r1 - p->frctl.r / p->frctl.zoom;
			p->frctl.starty = p->frctl.starty - p->frctl.r1 + p->frctl.r / p->frctl.zoom;
		}
		p->frctl.r1 = p->frctl.r / p->frctl.zoom;
		//printf("\tzooom: %f\n\tleft x: %f\n\ttop y: %f\n\tradius: %f\n", p->frctl.zoom, p->frctl.startx, p->frctl.starty, p->frctl.r1);
		while (++i < NTHREADS)
			(p->thread_args + i)->frctl = p->frctl;
		draw_fractal(p);
	}
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_param_ptr p = param;
	int i;
	if(p->cntrl.follow_mouse == 0)
		return (0);
	//printf("%d\t%d\n", x, y);
	i = -1;
	p->frctl.c.r = 2. / WIDTH * x - 1;
	p->frctl.c.i = 2. / HEIGHT * y - 1;
	while (++i < NTHREADS)
		(p->thread_args + i)->frctl = p->frctl;
	draw_fractal(p);
	return 0;
}

int	key_press(int keycode, void *param)
{
	t_param_ptr p = param;
	int i;
	i = -1;
	if (keycode == 5)
	{
		p->cntrl.follow_zoom ^= 1;
		printf("OK\n");
	}
	if (keycode == 3)
	{
		p->cntrl.follow_mouse ^= 1;
	}
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

int main(int ac, char **av)
{
	t_param param;
	init_param(&param, julia);
	//init_param(&param, julia);
	//sleep(30);
	draw_fractal(&param);
	mlx_hook(param.win_ptr, 6, 0, mouse_move, &param);
	mlx_hook(param.win_ptr, 4, 0, mouse_press, &param);
	mlx_hook(param.win_ptr, 2, 0, key_press, &param);
	mlx_loop(param.mlx_ptr);
}
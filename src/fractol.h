#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/src/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <stdio.h>

# define DEFAULT_LENGTH 600
# define DEFAULT_WIDTH 600

# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5
# define MOUSE_LEFT_BUTTON	1
# define MOUSE_RIGHT_BUTTON	2

# define ARROW_UP			126
# define ARROW_DOWN			125
# define ARROW_LEFT			123
# define ARROW_RIGHT		124

# define NUM_PAD_PLUS		69
# define NUM_PAD_MINUS		78

# define MAIN_PAD_ESC		53
# define MAIN_PAD_SPACE		49
# define MAIN_PAD_C			8
# define MAIN_PAD_H			4
# define MAIN_PAD_R			15
# define MAIN_PAD_PLUS		24
# define MAIN_PAD_MINUS		27
# define MAIN_PAD_1			18
# define MAIN_PAD_2			19
# define MAIN_PAD_3			20
# define MAIN_PAD_4			21
# define MAIN_PAD_5			23
# define MAIN_PAD_6			22
# define MAIN_PAD_7			26
# define MAIN_PAD_8			28
# define MAIN_PAD_9			25

typedef union u_color
{
	unsigned int	color;
	struct s_rgb
	{
		unsigned int	b : 8;
		unsigned int	g : 8;
		unsigned int	r : 8;
	}	t_rgb;
}	t_color;

typedef struct s_complex
{
	double			re;
	double			im;
}					t_complex;

typedef struct s_data
{
	void	*mlx;
	void	*img;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_canva
{
	int		length;
	int		width;
}	t_canva;

typedef struct s_vars
{
	char		**argv;
	t_data		mlx_data;
	t_canva		canva;
	int			max_iteration;
	t_complex	min;
	t_complex	max;
	t_complex	julia_k;
	int			change_julia_k;
	int			press_mouse_button;
	int			(*formula)(int x, int y, struct s_vars *vars);
	int			color_shift;
}	t_vars;

typedef struct s_formula
{
	char	*name;
	int		(*formula)(int x, int y, t_vars *vars);
}	t_formula;

/*
** color_functions.c
*/

t_color	new_color(int r, int g, int b);

t_color	fract_get_color(int iteration, t_vars *vars);

/*
** mouse_control.c
*/

int		press_mouse_button(int keycode, int x, int y, t_vars *vars);

int		release_mouse_button(int keycode, int x, int y, t_vars *vars);

int		motion_mouse(int x, int y, t_vars *vars);

void	move_screen(int x, int y, t_vars *vars);

/*
** keyboard_control.c
*/

int		press_key(int keycode, t_vars *vars);

/*
** init.c
*/

void	reset_vars(t_vars *vars);

int		init_vars(t_vars *vars, char **argv);

/*
** exit.c
*/

int		end_program(t_vars *vars);

/*
** draw_fractal.c
*/

void	draw_fractal(t_vars *vars);

//int get_pixel_color(int x, int y, t_vars *vars);

/*
** Fractals
*/

int		iterate_mandelbrot(int x, int y, t_vars *vars);

int		iterate_julia(int x, int y, t_vars *vars);

int		iterate_buterfly(int x, int y, t_vars *vars);

int		iterate_burning_ship(int x, int y, t_vars *vars);

int		iterate_mandelbar(int x, int y, t_vars *vars);

#endif

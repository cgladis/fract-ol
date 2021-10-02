#include "fractol.h"

static void	arrow_keys(int keycode, t_vars *vars)
{
	t_complex	delta;

	delta = (t_complex){(vars->max.re - vars->min.re) / 100,
		(vars->max.im - vars->min.im) / 100};
	if (keycode == ARROW_DOWN)
	{
		vars->min.im += delta.im;
		vars->max.im += delta.im;
	}
	else if (keycode == ARROW_UP)
	{
		vars->min.im -= delta.im;
		vars->max.im -= delta.im;
	}
	else if (keycode == ARROW_RIGHT)
	{
		vars->min.re -= delta.re;
		vars->max.re -= delta.re;
	}
	else if (keycode == ARROW_LEFT)
	{
		vars->min.re += delta.re;
		vars->max.re += delta.re;
	}
}

static void	change_fractal(int keycode, t_vars *vars)
{
	if (keycode == MAIN_PAD_1)
		vars->formula = &iterate_mandelbrot;
	else if (keycode == MAIN_PAD_2)
		vars->formula = &iterate_julia;
	else if (keycode == MAIN_PAD_3)
		vars->formula = &iterate_buterfly;
	else if (keycode == MAIN_PAD_4)
		vars->formula = &iterate_burning_ship;
	else if (keycode == MAIN_PAD_5)
		vars->formula = &iterate_mandelbar;
}

int	press_key(int keycode, t_vars *vars)
{
	if (keycode == MAIN_PAD_PLUS || keycode == NUM_PAD_PLUS)
		vars->max_iteration++;
	else if (keycode == MAIN_PAD_MINUS || keycode == NUM_PAD_MINUS)
		vars->max_iteration--;
	else if (keycode == ARROW_DOWN || keycode == ARROW_UP
		|| keycode == ARROW_RIGHT || keycode == ARROW_LEFT)
		arrow_keys(keycode, vars);
	else if (keycode == MAIN_PAD_R)
		reset_vars(vars);
	else if (keycode == MAIN_PAD_C)
		vars->color_shift++;
	else if (keycode == MAIN_PAD_SPACE)
		vars->change_julia_k = !vars->change_julia_k;
	else if (keycode == MAIN_PAD_ESC)
		end_program(vars);
	else if (keycode == MAIN_PAD_1 || keycode == MAIN_PAD_2
		|| keycode == MAIN_PAD_3 || keycode == MAIN_PAD_4
		|| keycode == MAIN_PAD_5 || keycode == MAIN_PAD_6
		|| keycode == MAIN_PAD_7 || keycode == MAIN_PAD_8
		|| keycode == MAIN_PAD_9)
		change_fractal(keycode, vars);
	draw_fractal(vars);
	return (1);
}

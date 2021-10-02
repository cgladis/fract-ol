#include "fractol.h"

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

static void	zoom_screen(int keycode, int x, int y, t_vars *vars)
{
	t_complex	delta;
	double		interpolation;

	delta = (t_complex){(double)x / (vars->canva.width
			/ (vars->max.re - vars->min.re)) + vars->min.re,
		(double)y / (vars->canva.length
			/ (vars->max.im - vars->min.im)) * -1 + vars->max.im};
	interpolation = 1;
	if (keycode == MOUSE_SCROLL_DOWN)
		interpolation = 1.05;
	else if (keycode == MOUSE_SCROLL_UP)
		interpolation = 0.95;
	vars->min.re = interpolate(delta.re, vars->min.re, interpolation);
	vars->min.im = interpolate(delta.im, vars->min.im, interpolation);
	vars->max.re = interpolate(delta.re, vars->max.re, interpolation);
	vars->max.im = interpolate(delta.im, vars->max.im, interpolation);
}

void	move_screen(int x, int y, t_vars *vars)
{
	t_complex	delta;
	static int	x1;
	static int	y1;
	static int	first_time = 1;

	if (!vars->press_mouse_button)
	{
		first_time = 1;
		return ;
	}
	if (first_time)
	{
		x1 = x;
		y1 = y;
		first_time = 0;
		return ;
	}
	delta.re = (vars->max.re - vars->min.re) / vars->canva.width * (x1 - x);
	delta.im = (vars->max.im - vars->min.im) / vars->canva.length * (y - y1);
	vars->min.im += delta.im;
	vars->max.im += delta.im;
	vars->min.re += delta.re;
	vars->max.re += delta.re;
	x1 = x;
	y1 = y;
}

int	press_mouse_button(int keycode, int x, int y, t_vars *vars)
{
	if (x < 0 || y < 0)
		return (0);
	if (keycode == MOUSE_SCROLL_DOWN || keycode == MOUSE_SCROLL_UP)
		zoom_screen(keycode, x, y, vars);
	if (keycode == MOUSE_LEFT_BUTTON)
	{
		vars->press_mouse_button = 1;
		move_screen(x, y, vars);
	}
	draw_fractal(vars);
	return (0);
}

int	release_mouse_button(int keycode, int x, int y, t_vars *vars)
{
	if (keycode == MOUSE_LEFT_BUTTON)
	{
		vars->press_mouse_button = 0;
		move_screen(x, y, vars);
	}
	draw_fractal(vars);
	return (0);
}

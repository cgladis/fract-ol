#include "fractol.h"

int	motion_mouse(int x, int y, t_vars *vars)
{
	if (vars->press_mouse_button && x > 0 && y > 0 && x < vars->canva.width
		&& y < vars->canva.length)
	{
		move_screen(x, y, vars);
	}
	else if (vars->change_julia_k && (x > 0 && y > 0 && x < vars->canva.width
			&& y < vars->canva.length))
	{
		vars->julia_k.re = ((double)x - (double)vars->canva.width / 2)
			/ ((double)vars->canva.width / 2);
		vars->julia_k.im = ((double)y - (double)vars->canva.length / 2)
			/ ((double)vars->canva.length / 2);
		draw_fractal(vars);
	}
	draw_fractal(vars);
	return (0);
}

#include "fractol.h"

int	iterate_mandelbrot(int x, int y, t_vars *vars)
{
	t_complex	base_point;
	t_complex	z;
	int			i;
	double		tmp;

	(void)vars;
	base_point = (t_complex){
		.re = vars->min.re + x * ((vars->max.re - vars->min.re)
			/ (vars->canva.width)),
		.im = vars->max.im - y * ((vars->max.im - vars->min.im)
			/ (vars->canva.length))};
	z = base_point;
	i = 0;
	while (z.re * z.re + z.im * z.im < 4 && i < vars->max_iteration)
	{
		tmp = z.re;
		z.re = z.re * z.re - z.im * z.im + base_point.re;
		z.im = 2 * z.im * tmp + base_point.im;
		i++;
	}
	return (i);
}

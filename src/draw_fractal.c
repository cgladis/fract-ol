#include "fractol.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_fractal(t_vars *vars)
{
	int				i;
	int				j;
	int				iteration;
	t_color			color;

	i = 0;
	while (i < vars->canva.width)
	{
		j = 0;
		while (j < vars->canva.length)
		{
			iteration = vars->formula(i, j, vars);
			color = fract_get_color(iteration, vars);
			my_mlx_pixel_put(&vars->mlx_data, i, j, color.color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx_data.mlx, vars->mlx_data.win,
		vars->mlx_data.img, 0, 0);
}

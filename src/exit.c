#include "fractol.h"

int	end_program(t_vars *vars)
{
	if (vars->mlx_data.img)
		mlx_destroy_image(vars->mlx_data.mlx, vars->mlx_data.img);
	if (vars->mlx_data.win)
		mlx_destroy_window(vars->mlx_data.mlx, vars->mlx_data.win);
	exit (0);
}

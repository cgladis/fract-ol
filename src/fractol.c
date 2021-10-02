#include "fractol.h"

void	print_anable_parameters_n_exit(void)
{
	ft_print("Usage: ./fractol <name> [(float)k1 (float)k2]\n", NULL);
	ft_print("k1, k2 - the parameters (from -1 to 1) for Julia "
		"(default [-0.4, 0.6])\n\n", NULL);
	ft_print("List of available fractals:\n * Mandelbrot\n * Julia\n", NULL);
	ft_print(" * Buterfly\n * Burning Ship\n * Mandelbar\n", NULL);
}

int	check_double(char *str)
{
	int	i;

	i = 0;
	if (*str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		str++;
		i++;
	}
	if (*str == '.' && i <= 5)
	{
		str++;
		while (ft_isdigit(*str))
		{
			str++;
			i++;
		}
		if (*str == '\0' && i > 0 && i <= 10)
			return (1);
	}
	else if (*str == '\0' && i > 0)
		return (1);
	return (0);
}

int	check_parameters(int argc, char **argv)
{
	if (argc != 2 && argc != 4)
		return (0);
	if (argc == 4)
	{
		if (!check_double(argv[2]) || !check_double(argv[3]))
			return (0);
	}
	return (1);
}

void	view_scene(t_vars *vars)
{
	vars->mlx_data.img = mlx_new_image(vars->mlx_data.mlx, vars->canva.length,
			vars->canva.width);
	vars->mlx_data.addr = mlx_get_data_addr(vars->mlx_data.img,
			&vars->mlx_data.bits_per_pixel, &vars->mlx_data.line_length,
			&vars->mlx_data.endian);
	vars->mlx_data.win = mlx_new_window(vars->mlx_data.mlx, vars->canva.length,
			vars->canva.width, vars->argv[1]);
	mlx_put_image_to_window(vars->mlx_data.mlx, vars->mlx_data.win,
		vars->mlx_data.img, 0, 0);
	mlx_hook(vars->mlx_data.win, 04, 1L << 2, press_mouse_button, vars);
	mlx_hook(vars->mlx_data.win, 05, 1L << 3, release_mouse_button, vars);
	mlx_hook(vars->mlx_data.win, 06, 1L << 8, motion_mouse, vars);
	mlx_hook(vars->mlx_data.win, 02, 1L << 0, press_key, vars);
	mlx_hook(vars->mlx_data.win, 17, 1L << 17, end_program, vars);
	draw_fractal(vars);
	mlx_loop(vars->mlx_data.mlx);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (!check_parameters(argc, argv))
	{
		print_anable_parameters_n_exit();
		return (0);
	}
	if (!init_vars(&vars, argv))
	{
		print_anable_parameters_n_exit();
		end_program(&vars);
	}
	view_scene(&vars);
}

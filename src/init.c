#include "fractol.h"

static int	(*get_formula(char *name)) (int x, int y, t_vars *vars)
{
	size_t				i;
	int					(*formula)(int x, int y, t_vars *vars);
	static t_formula	formulas[] = {
			{"Mandelbrot", &iterate_mandelbrot},
			{"Julia", &iterate_julia},
			{"Buterfly", &iterate_buterfly},
			{"Burning Ship", &iterate_burning_ship},
			{"Mandelbar", &iterate_mandelbar}
	};

	i = 0;
	formula = NULL;
	while (i < (sizeof(formulas) / sizeof(t_formula)))
	{
		if (!ft_strcmp(name, formulas[i].name))
			formula = formulas[i].formula;
		i++;
	}
	return (formula);
}

void	reset_vars(t_vars *vars)
{
	vars->canva.length = DEFAULT_LENGTH;
	vars->canva.width = DEFAULT_WIDTH;
	vars->max_iteration = 50;
	vars->change_julia_k = 0;
	if (ft_len((void **)vars->argv) == 4)
		vars->julia_k = (t_complex){ft_double(vars->argv[2]),
			ft_double(vars->argv[3])};
	else
		vars->julia_k = (t_complex){-.4, .6};
	vars->min = (t_complex){-2, -2};
	vars->max = (t_complex){2, 2};
	vars->color_shift = 0;
}

int	init_vars(t_vars *vars, char **argv)
{
	vars->argv = argv;
	vars->mlx_data.win = NULL;
	vars->mlx_data.img = NULL;
	vars->mlx_data.addr = NULL;
	vars->press_mouse_button = 0;
	vars->formula = get_formula(argv[1]);
	if (vars->formula == NULL)
		return (0);
	if (ft_len((void **)vars->argv) == 4)
	{
		vars->julia_k = (t_complex){ft_double(vars->argv[2]),
			ft_double(vars->argv[3])};
		if (vars->julia_k.im > 1.0 || vars->julia_k.im < -1.0
			|| vars->julia_k.re > 1.0 || vars->julia_k.re < -1.0)
			return (0);
	}
	reset_vars(vars);
	vars->mlx_data.mlx = mlx_init();
	return (1);
}

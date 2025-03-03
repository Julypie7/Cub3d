/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:16:45 by ineimatu          #+#    #+#             */
/*   Updated: 2025/03/03 17:21:56 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->map->no)
		printf("NO = %s\n", data->map->no);
	if (data->map->so)
		printf("SO = %s\n", data->map->so);
	if (data->map->we)
		printf("WE = %s\n", data->map->we);
	if (data->map->ea)
		printf("EA = %s\n", data->map->ea);
	printf("Floor.red = %d\n", data->map->floor.red);
	printf("Floor.green = %d\n", data->map->floor.green);
	printf("Floor.blue = %d\n", data->map->floor.blue);
	printf("Ceiling.red = %d\n", data->map->ceiling.red);
	printf("Ceiling.green = %d\n", data->map->ceiling.green);
	printf("Ceiling.blue = %d\n", data->map->ceiling.blue);
	printf("Flag = %d\n", data->map->flag);
	if (data->player.news)
		printf("Player_news = %c\n", data->player.news);
	if (data->player.position_x)
		printf("Player_X = %f\n", data->player.position_x);
	if (data->player.position_y)
		printf("Player_Y = %f\n", data->player.position_y);
	if (data->player.angle)
		printf("Player_angle = %d\n", data->player.angle);
	if (data->map->matrix)
	{
		while (data->map->matrix[i])
		{
			printf("%s\n", data->map->matrix[i]);
			i++;
		}
	}
}

int	close_escape(t_data *data)
{
	free_data(data);
	exit (EXIT_SUCCESS);
}

int	is_cub(char *argv)
{
	int	i;
	int	fd;

	fd = -1;
	i = ft_strlen(argv) - 1;
	if (!(argv[i - 3] == '.' && argv[i - 2] == 'c' && argv[i - 1] == 'u'
			&& argv[i] == 'b'))
		exit (error_msg("map file is incorrect", NULL));
	else
	{
		if (access(argv, F_OK) == 0 && access(argv, R_OK) == 0)
			fd = open(argv, O_RDONLY);
		if (fd == -1 || access(argv, F_OK) != 0 || access(argv, R_OK) != 0)
			exit (error_msg("map file is not open", NULL));
	}
	return (0);
}

void	implementation_mlx(t_data *data, char *name)
{
	data->image = malloc(sizeof(t_image));
	if (!data->image)
		exit (error_msg("malloc didn't work correctly", data));
	data->mlx = mlx_init();
	if (!data->mlx)
		exit (error_msg("mlx_init didn't works properly", data));
	data->mlx_window = mlx_new_window(data->mlx, LENGTH, HEIGHT, name);
	if (!data->mlx_window)
		exit (error_msg("mlx_new_window didn't works properly", data));
	data->image->img_add = mlx_new_image(data->mlx, LENGTH, HEIGHT);
	if (!data->image->img_add)
		exit (error_msg("mlx_new_image didn't works properly", data));
	data->image->pix_add = mlx_get_data_addr(data->image->img_add,
			&data->image->bit_pix, &data->image->length_line,
			&data->image->endian);
	get_wall_texture(data);
	initialize_door(data);
	if (&data->doors->sprite[3])
		data->texture_door = data->doors->sprite[3];
}


int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc != 2)
		exit (error_msg("wrong number of arguments", NULL));
	is_cub(argv[1]);
	data = initialize(data);
	check_cub_file(data, argv[1]);
	map_check(data, data->map->matrix);
	map_size(data);
	implementation_mlx(data, "cub3D_map");
	find_wall(data);
	mlx_loop_hook(data->mlx, do_hook, data);
	mlx_hook(data->mlx_window, 2, (1L << 0), do_key, data);
	mlx_hook(data->mlx_window, 17, (1L << 5), close_escape, data);
	//mlx_mouse_hook(data->mlx_window, do_mouse, data);
	mlx_loop(data->mlx);
	//print_data(data);
	free_data(data);
	return (0);
}

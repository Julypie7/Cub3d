/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:33:29 by esellier          #+#    #+#             */
/*   Updated: 2025/02/04 19:05:00 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*news_args_check(char *str, t_data *data, char **news)
{
	int		i;
	char	*tmp;

	i = 0;
	if (*news)
		exit (error_msg("duplicate texture element ", data));
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '	'))
			i++;
		if (!str[i])
			exit (error_msg("texture path is missing", data));
		str = &str[i];
		i = 0;
		while (str[i] && str[i] != ' ' && str[i] != '	')
			i++;
		if (str[i]) //checker si plusieurs arg ou finit par autre chose qu'un caractere(pas ok espace apres)
			exit (error_msg("texture argument is not appropriate", data));
		tmp = malloc((i + 1) * sizeof(char));
		if (!tmp)
			exit (error_msg("malloc didn't work correctly", data));
		ft_strlcpy(tmp, str, i + 1);
	}
	*news = tmp;
	return (0);
}
//checker si le chemin d'acces des textures est ok plus tard, par Julia

void	*news_check(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (str[i] == 'N' && str[i + 1] && str[i + 1] == 'O' && str[i + 2]
		&& (str[i + 2] == ' ' || str[i + 2] == '	'))
		return (news_args_check(&str[i + 2], data, &data->map->no));
	else if (str[i] == 'S' && str[i + 1] && str[i + 1] == 'O' && str[i + 2]
		&& (str[i + 2] == ' ' || str[i + 2] == '	'))
		return (news_args_check(&str[i + 2], data, &data->map->so));
	else if (str[i] == 'W' && str[i + 1] && str[i + 1] == 'E' && str[i + 2]
		&& (str[i + 2] == ' ' || str[i + 2] == '	'))
		return (news_args_check(&str[i + 2], data, &data->map->we));
	else if (str[i] == 'E' && str[i + 1] && str[i + 1] == 'A' && str[i + 2]
		&& (str[i + 2] == ' ' || str[i + 2] == '	'))
		return (news_args_check(&str[i + 2], data, &data->map->ea));
	exit (error_msg("identifier argument is not appropriate", data));
}

t_files	create_struct_files(t_data *data, char *path)
{
	t_files	files;

	files.img = mlx_xpm_file_to_image(data->mlx, path,
			&files.width, &files.height);
	if (!files.img)
		exit (error_msg("image not loaded", data));
	return (files);
}

void	create_struct_texture(t_data *data)
{
	data->texture[0] = create_struct_files(data, data->map->no);
	data->texture[1] = create_struct_files(data, data->map->so);
	data->texture[2] = create_struct_files(data, data->map->we);
	data->texture[3] = create_struct_files(data, data->map->ea);
}

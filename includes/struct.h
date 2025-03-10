/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:26:57 by ineimatu          #+#    #+#             */
/*   Updated: 2025/03/06 14:00:46 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_files
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}				t_files;

typedef struct s_door
{
	int				x;
	int				y;
	int				flag;
	int				count;
	struct timeval	timer;
	t_files			sprite[PICS];
}				t_door;

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
}				t_color;

typedef struct s_map
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	t_color			floor;
	t_color			ceiling;
	char			**matrix;
	int				flag;
}				t_map;

typedef struct s_image
{
	void			*img_add;
	char			*pix_add;
	int				bit_pix;
	int				length_line;
	int				endian;
}				t_image;

typedef struct s_player
{
	double			position_x;
	double			position_y;
	int				angle;
	char			news;
}				t_player;

typedef struct s_ray
{
	double			player_x;
	double			player_y;
	double			angle_start;
	int				fov;
	double			dist_h;
	double			dist_v;
	double			dist_t_wall;
	int				first_wall_pxl;
	int				last_wall_pxl;
	double			wall_height;
	int				c_f;
}				t_ray;

typedef struct s_utils
{
	double			radians;
	char			wall_hit;
	int				v_x;
	int				v_y;
	int				h_x;
	int				h_y;
	int				hit_x;
	int				hit_y;
}				t_utils;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_window;
	t_map			*map;
	t_player		player;
	t_ray			ray;
	t_utils			utils;
	t_image			*image;
	struct timeval	timer;
	t_files			texture_door;
	t_files			texture_north;
	t_files			texture_south;
	t_files			texture_west;
	t_files			texture_east;
	t_door			*doors;
	int				mouse;
	int				mouse_flag;
}				t_data;

#endif

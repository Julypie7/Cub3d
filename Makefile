# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 11:01:31 by ineimatu          #+#    #+#              #
#    Updated: 2025/01/20 14:18:49 by ineimatu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = cub3D
MLX = mlx_linux/
GNL = gnl/
LIBFT = libft/
MLX_A = $(addprefix $(MLX), libmlx.a)
GNL_A = $(addprefix $(GNL), libgnl.a)
LIBFT_A = $(addprefix $(LIBFT), libft.a)

SRC = main.c \
	  ray_cast.c \
	  test.c \
	  ray_cast_calcul.c \

OBJ = $(SRC:.c=.o)

CC = cc

INCLUDES = -I includes -I $(LIBFT)libft.h -I $(GNL)get_next_line.h

CCFLAGS = -Wextra -Werror -Wall $(INCLUDES) -fsanitize=address -fsanitize=leak

all:
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) -C $(GNL)
	@$(MAKE) -C $(MLX)
	@$(MAKE) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIBFT) -lft -L$(GNL) -lgnl -L$(MLX) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o:		%.c Makefile includes/cub3D.h includes/struct.h $(LIBFT_A) $(GNL_A) $(MLX_A)
			$(CC) $(CCFLAGS) -Imlx_linux -O3 -c $< -o $(<:.c=.o)
clean:
			rm -f $(OBJ)
			$(MAKE) clean -s -C $(GNL)
			$(MAKE) clean -s -C $(LIBFT)

fclean:		clean
			$(MAKE) clean -s -C $(MLX)
			$(MAKE) fclean -s -C $(GNL)
			$(MAKE) fclean -s -C $(LIBFT)
			rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
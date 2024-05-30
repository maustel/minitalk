# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 11:32:58 by maustel           #+#    #+#              #
#    Updated: 2024/05/15 12:19:59 by maustel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENTNAME := client
SERVERNAME := server

CFLAGS := -Wall -Werror -Wextra -I./libft
# LIBFT_HEADERS = -I./libft

LIBFT = ./libft/libft.a

SRC_CLIENT 			:= client.c
SRC_CLIENT_BONUS	:= client_bonus.c
SRC_SERVER			:= server.c
SRC_SERVER_BONUS	:= server_bonus.c

OBJ_CLIENT			:= $(SRC_CLIENT:.c=.o)
OBJ_CLIENT_BONUS	:= $(SRC_CLIENT_BONUS:.c=.o)
OBJ_SERVER			:= $(SRC_SERVER:.c=.o)
OBJ_SERVER_BONUS	:= $(SRC_SERVER_BONUS:.c=.o)

all:	$(SERVERNAME) $(CLIENTNAME)

$(SERVERNAME):	$(LIBFT) $(OBJ_SERVER)
		cc $(CFLAGS) $(OBJ_SERVER) -o $(SERVERNAME) $(LIBFT)

$(CLIENTNAME):	$(LIBFT) $(OBJ_CLIENT)
		cc $(CFLAGS) $(OBJ_CLIENT) -o $(CLIENTNAME) $(LIBFT)

%.o: %.c
		cc $(CFLAGS) -c $< -o $@

#-C option is used to change the directory before doing anything else.
$(LIBFT):
	make -C libft

bonus:	bonus_client bonus_server

bonus_client:	$(LIBFT) $(OBJ_CLIENT_BONUS)
		@cc $(CFLAGS) $(LIBFT) $(OBJ_CLIENT_BONUS) -o $(CLIENTNAME)

bonus_server:	$(LIBFT) $(OBJ_SERVER_BONUS)
		@cc $(CFLAGS) $(LIBFT) $(OBJ_SERVER_BONUS) -o $(SERVERNAME)

clean:
	make -C libft clean
	rm -f $(OBJ_CLIENT) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER) $(OBJ_SERVER_BONUS)

fclean:	clean
	make -C libft fclean
	rm -f $(CLIENTNAME) $(SERVERNAME)

re:	fclean all

.PHONY:	all clean fclean re bonus
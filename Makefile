# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 18:01:32 by fnichola          #+#    #+#              #
#    Updated: 2021/11/28 08:44:04 by fnichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER_NAME = server
CLIENT_NAME = client

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SERVER_SRCS = srcs/server.c
CLIENT_SRCS = srcs/client.c

ifdef WITH_BONUS
SERVER_SRCS = bonus_srcs/server_bonus.c
CLIENT_SRCS = bonus_srcs/client_bonus.c \
	bonus_srcs/gnl/get_next_line_bonus.c \
	bonus_srcs/gnl/get_next_line_utils_bonus.c
endif

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

all: server client

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
$(SERVER_NAME): $(SERVER_OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBFT_LIB) -o server

$(CLIENT_NAME): $(CLIENT_OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT_LIB) -o client

bonus:
	$(MAKE) WITH_BONUS=1

$(LIBFT_LIB):
	$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	$(RM) $(SERVER_OBJS)
	$(RM) $(CLIENT_OBJS)
	$(MAKE) clean WITH_BONUS=1 -C $(LIBFT_DIR)

fclean: clean
	$(RM) server client
	$(RM) $(LIBFT_LIB)

re: fclean all

.PHONY: all clean fclean re bonus

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 18:01:32 by fnichola          #+#    #+#              #
#    Updated: 2021/11/25 19:55:39 by fnichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SERVER_SRCS = srcs/server.c
CLIENT_SRCS = srcs/client.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

all: server client

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<
	
server: $(SERVER_OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBFT_LIB) -o server

client: $(CLIENT_OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT_LIB) -o client

$(LIBFT_LIB):
	$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	$(RM) $(SERVER_OBJS)
	$(RM) $(CLIENT_OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) server client
	$(RM) $(LIBFT_LIB)

re: fclean all

.PHONY: all clean fclean re bonus

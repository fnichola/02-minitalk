# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 18:01:32 by fnichola          #+#    #+#              #
#    Updated: 2021/12/01 20:05:30 by fnichola         ###   ########.fr        #
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
	bonus_srcs/client_signal_bonus.c \
	bonus_srcs/gnl/get_next_line.c \
	bonus_srcs/gnl/get_next_line_utils.c
endif

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
SERVER_DEPS = $(SERVER_SRCS:.c=.d)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
CLIENT_DEPS = $(CLIENT_SRCS:.c=.d)

all: server client

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $<
	
$(SERVER_NAME): $(SERVER_OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBFT_LIB) -o server

$(CLIENT_NAME): $(CLIENT_OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT_LIB) -o client

bonus:
	$(MAKE) WITH_BONUS=1

$(LIBFT_LIB):
	$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	$(RM) $(SERVER_OBJS) $(SERVER_DEPS)
	$(RM) $(CLIENT_OBJS) $(CLIENT_DEPS)
	$(MAKE) clean WITH_BONUS=1 -C $(LIBFT_DIR)

fclean: clean
	$(RM) server client
	$(RM) $(LIBFT_LIB)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(SERVER_DEPS) $(CLIENT_DEPS)

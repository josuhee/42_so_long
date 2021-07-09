# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/30 16:33:42 by sujo              #+#    #+#              #
#    Updated: 2021/07/06 20:07:59 by sujo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
SRCS=src/main.c\
	src/so_long.c\
	src/parsing_map.c\
	src/get_next_line.c\
	src/get_next_line_utils.c\
	src/paint_map.c\
	src/valid_map.c\
	src/key_event.c\
	src/ft_itoa.c\
	src/search_player.c

OBJS		=$(SRCS:.c=.o)
OBJB		=$(SRCB:.c=.o)
NAME		=so_long
HEADER		=-I include/
CFLAG		= -fsanitize=address
MINI_DIR	=mlx_opengl/
MINI_NAME	=libmlx.a
LIBS		=-Lmlx_opengl -lmlx -framework OpenGL -framework Appkit
RM			=rm -f

FG_YELLOW	=\e[33m
FG_RED		=\e[31m
FG_BLUE		=\e[34m
FG_MAGENTA	=\e[35m
FG_CYAN		=\e[36m
NO_COLOR	=\e[0m

ifdef WITH_BONUS
	OBJ_FILES = $(OBJB)
	NAME=checker
else
	OBJ_FILES = $(OBJS)
endif

ifdef WITH_BONUS
%.o: %.c
	$(CC) $(CFLAG) -c -o $@ $< $(HEADERB)
else
%.o: %.c
	@$(CC) $(CFLAG) -c -o $@ $< $(HEADER)
endif

all: $(NAME)

$(NAME): $(MINI_NAME) $(OBJ_FILES)
	$(CC) $(CFLAG) -o $@ $(OBJ_FILES) $(LIBS)
	@printf "💬 $(FG_MAGENTA)create exec file 'so_long'\n$(NO_COLOR)"

$(MINI_NAME):
	@make -C $(MINI_DIR)
	@mv $(MINI_DIR)/$(MINI_NAME) .
	@printf "💬 $(FG_MAGENTA)minilibx opengl make complete !\n$(NO_COLOR)"

bonus:
	make WITH_BONUS=1 all

clean:
	@$(RM) $(OBJS) $(OBJB) $(MINI_NAME)
	@make clean -C $(MINI_DIR)
	@printf "$(FG_YELLOW)👻 .o 파일들을 삭제하였습니다 👻\n$(NO_COLOR)"

fclean: clean
	@rm -f $(NAME) $(NAMEB)
	@printf "$(FG_RED)🍀 실행파일을 삭제하였습니다 🍀\n$(NO_COLOR)"

re: fclean all

.PHONY: all bonus clean fclean re
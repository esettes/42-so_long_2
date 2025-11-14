BWHITE	= \033[1;37m
LGREEN	= \033[2;32m
LWHITE	= \033[2;37m
RESET	= \033[0m
GREEN	= \033[0;32m
WHITE	= \033[0;37m

NAME = so_long

DISTRO_ID := $(shell sh -c '. /etc/os-release 2>/dev/null; echo $$ID')

ifeq ($(DISTRO_ID),ubuntu)
    CFLAGS += -DASSET_DIR=\"/home/rstancu/cursus/so_long_2/tiles\"
else ifeq ($(DISTRO_ID),debian)
    CFLAGS += -DASSET_DIR=\"/home/settes/cursus/2025/so_long_2/tiles\"
endif


SRCDIR		= ./src/
SRCNAMES	= main.c \
			read_file.c \
			parse.c \
			free.c \
			fps_controller.c \
			print_map.c\
			init_anim_player.c \
			init_enemies.c \
			init_anim_enemy.c \
			init_so_long.c \
			init_player.c \
			init_collectibles.c \
			movements_helpers.c \
			epsilon.c \
			collectibles_spawn.c \
			player_utils.c \
			exit_utils.c \
			map_mandatory.c \
			dfs.c \
			print_movements.c

SRC			= $(addprefix $(SRCDIR), $(SRCNAMES))

OBJDIR	= ./src/obj/
OBJS	= $(addprefix $(OBJDIR), $(SRCNAMES:.c=.o))

LIBFT = ./inc/libft/libft.a
MLX42 = ./inc/MLX42/build/libmlx42.a
GNL = ./inc/gnl/libgnl.a
 
LDFLAGS += -L ./inc/libft -L ./inc/gnl
LDLIBS += -lft -lgnl -lm -pthread
HEADERS	= -I include -I ./inc/libft/inc/ -I ./inc/gnl/inc/ -I ./inc/  -I ./inc/MLX42/include/MLX42/
LIBX42_FLAGS	=	-I include -ldl -lglfw

CFLAGS +=   -g3  -Wall -Wextra -Werror -fno-omit-frame-pointer -fsanitize=leak

PRINT ?= 0
CFLAGS += -DPRINT=$(PRINT)

CC = cc

MAKEFLAGS += --no-print-directory

all: obj $(LIBFT) $(GNL) $(NAME)

$(NAME):  $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(HEADERS) -o $(NAME) $(OBJS) $(MLX42) $(LIBX42_FLAGS) $(LDLIBS)
	@echo "${LWHITE}$(NAME) ${GREEN}✓$(RESET)"
	@echo "${BWHITE}Compilation ${GREEN}[OK]$(RESET)"

$(OBJDIR)%.o:$(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(dir $(LIBFT))

$(GNL):
	@$(MAKE) -C $(dir $(GNL))

obj:
	@mkdir -p $(OBJDIR)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(dir $(LIBFT)) clean
	@$(MAKE) -C $(dir $(GNL)) clean

fclean:	clean
	@rm -f $(NAME)
	@$(MAKE) -C $(dir $(LIBFT)) fclean
	@$(MAKE) -C $(dir $(GNL)) fclean

re: fclean all

.PHONY: all clean fclean re

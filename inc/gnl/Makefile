LGREEN	= \033[2;32m
LWHITE	= \033[2;37m
RESET	= \033[0m
GREEN	=\033[0;32m

NAME = libgnl.a

SRCDIR	= ./src/
SRCNAMES =	get_next_line.c \
			get_next_line_utils.c

SRCS	= $(addprefix $(SRCDIR), $(SRCNAMES))

OBJDIR	= ./obj/
OBJS = $(addprefix $(OBJDIR), $(SRCNAMES:.c=.o))

LIBS	=  ./inc

CFLAGS =  -Wall -Wextra -Werror -I include -I

CC = cc

AR = ar rcs

all: $(NAME)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

$(NAME): $(OBJS) $(LIBS)
	@$(AR) $(NAME) $(OBJS)
	@echo "${LWHITE}$(NAME) ${GREEN}✓$(RESET)"

clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

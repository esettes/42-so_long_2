LGREEN	= \033[2;32m
LWHITE	= \033[2;37m
RESET	= \033[0m
GREEN	=\033[0;32m

NAME = libft.a

SRCDIR	= ./src/
SRCNAMES =	ft_strlen.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isspace.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strchr.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_atoi.c \
		ft_atoint32.c \
		ft_floor.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_strrchr.c \
		ft_itoa.c \
		ft_abs.c \
		ft_min.c \
		ft_max.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_striteri.c \
		ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \
		ft_get_time_ms.c \
		ft_clampd.c \
		ft_clampi.c \
		ft_lerp.c

SRCS	= $(addprefix $(SRCDIR), $(SRCNAMES))

OBJDIR	= ./obj/
OBJS = $(addprefix $(OBJDIR), $(SRCNAMES:.c=.o))

LIBS	=  ./inc

CFLAGS =  -Wall -Wextra -Werror -I include -I

CC = cc

AR = ar rcs

all: $(NAME)


#$(OBJS):$(SRCS)
#	@mkdir -p $(OBJDIR)
#	@$(CC) $(CFLAGS) $(LIBS) -c $< -o $@ 

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

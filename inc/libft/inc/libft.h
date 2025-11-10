/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:37:10 by rstancu           #+#    #+#             */
/*   Updated: 2025/10/20 13:08:31 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}       t_list;

typedef struct s_vec2
{
	double	x;
	double	y;
}               t_vec2;

typedef struct s_int2
{
	int32_t	x;
	int32_t	y;
}               t_int2;

int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isprint(int c);
int				ft_isdigit(int c);
int				ft_isascii(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isspace(int c);
size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
void			*ft_memset(void *p, int val, size_t bytes);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t bytes);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t bytes);
char			*ft_strchr(const char *str, int c);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
char			*ft_strchr(const char *str, int c);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_atoi(const char *str);
/**
 * @param text 
 * @param out_value the integer conversion result
 * @return true or false if can or not parse to int32
 */
bool			ft_atoint32(const char *str, int32_t *out_value);
double			ft_floor(double value);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strrchr(const char *s, int c);
char			**ft_split(char const *s1, char c);
char			*ft_itoa(int n);
int32_t			ft_abs(int32_t a);
int32_t			ft_max(int32_t a, int32_t b);
int32_t			ft_min(int32_t a, int32_t b);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd( char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
long			get_time_ms(void);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
double			ft_clampd(double x, double lo, double hi);
int32_t			ft_clampi(int32_t x, int32_t lo, int32_t hi);
double			ft_lerp(double a, double b, double t);

#endif

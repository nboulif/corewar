/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:53:33 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/22 18:54:27 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef S_LIST
#  define S_LIST

typedef struct		s_list
{
	void			*content;
	uint32_t			content_size;
	struct s_list	*next;
}					t_list;
# endif

int					ft_abs(int n);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, uint32_t n);
int					ft_count_words(char const *s, char c);
uint32_t				ft_intlen(int n);
int					ft_intpow(int nb, int power);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, uint32_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, uint32_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
uint32_t				ft_lstlen(t_list *lst);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, uint32_t content_size);
void				*ft_memalloc(uint32_t size);
void				*ft_memccpy(void *dst, const void *src, int c, uint32_t n);
void				*ft_memchr(const void *s, int c, uint32_t n);
int					ft_memcmp(const void *s1, const void *s2, uint32_t n);
void				*ft_memcpy(void *dst, const void *src, uint32_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, uint32_t len);
void				*ft_memset(void *b, int c, uint32_t len);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnstr(char const *str, int n);
void				ft_putnstr_fd(char const *str, int len, int fd);
void				ft_putstr(char const *str);
void				ft_putstr_fd(char const *str, int fd);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(uint32_t, char *));
char				*ft_strjoin(char const *s1, char const *s2);
uint32_t				ft_strlcat(char *dst, const char *src, uint32_t size);
uint32_t				ft_strlen(const char *s);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(uint32_t, char));
char				*ft_strncat(char *s1, const char *s2, uint32_t n);
int					ft_strncmp(const char *s1, const char *s2, uint32_t n);
char				*ft_strncpy(char *dst, const char *src, uint32_t len);
int					ft_strnequ(char const *s1, char const *s2, uint32_t n);
char				*ft_strnew(uint32_t size);
char				*ft_strnstr(const char *haystack, const char *needle,
					uint32_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strrev(char *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strsub(char const *s, uint32_t start, uint32_t len);
char				*ft_strtrim(char const *s);
int					ft_tabadd_sec(char ***tab, uint32_t i, uint32_t len);
void				ft_tabdel(char ***tab);
int					ft_tolower(int c);
int					ft_toupper(int c);

#endif

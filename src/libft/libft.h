/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				*content;
	struct s_list	*next;

}					t_list;

typedef struct s_str_builder
{
	char			*buff;
	size_t			cap;
	size_t			len;
}					t_str_builder;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 69
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

int					ft_atoi(const char *nptr, int *valid);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
size_t				ft_strlen(const char *s);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_strdup(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char *start, char *end, char join);
char				*ft_strsearch(char *haystack[], char *needle);
char				**ft_split_free(char **arr);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *item);
void				ft_lstadd_sorted(t_list **head, void *content,
						int (*f)(void *, void *));
int					ft_lstsize(t_list *lst);
char				*ft_strndup(const char *src, size_t n);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *item);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					ft_vprintf_fd(va_list args, int fd, const char *format,
						...);
int					ft_printf(const char *format, ...);
int					ft_vprintf(va_list args, const char *format, ...);
int					ft_printf_fd(int fd, const char *format, ...);
int					ft_sprintf(char **buff, const char *format, ...);
int					ft_vsprintf(va_list args, char **buff, const char *s, ...);
char				*ft_strchr(const char *s, int c);
int					ft_putstr_fd(char *str, int fd);
int					ft_putchr(char c);
int					ft_putchr_fd(char c, int fd);
int					ft_putstr(char *s);
int					ft_putnbr(int n, int fd);
int					ft_putunbr(unsigned int n, int fd);
int					ft_putnbr_hex(unsigned long num, int uppercase, int fd);
int					ft_putptr(void *num, int fd);

ssize_t				get_next_line(int fd, char **receiver);
ssize_t				ft_istrchr(const char *s, char c);

t_str_builder		*sb_create(size_t cap);
void				sb_free(t_str_builder *sb);
bool				sb_ensure_size(t_str_builder *sb, size_t len);
void				sb_truncate(t_str_builder *sb, size_t len);
void				sb_clear(t_str_builder *sb);
void				sb_drop(t_str_builder *sb, size_t len);
bool				sb_append_str(t_str_builder *sb, const char *str,
						size_t len);
bool				sb_append_char(t_str_builder *sb, char c);
bool				sb_append_nbr(t_str_builder *sb, int n);
bool				sb_append_unbr(t_str_builder *sb, unsigned int n);
bool				sb_append_ptr(t_str_builder *sb, void *ptr);
bool				sb_append_hex(t_str_builder *sb, unsigned long num,
						int uppercase);
size_t				sb_len(t_str_builder *sb);
const char			*sb_str(t_str_builder *sb);
char				*sb_build(t_str_builder *sb);

#endif

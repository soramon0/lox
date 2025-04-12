#include "libft.h"

t_str_builder	*str_builder_create(size_t cap)
{
	t_str_builder	*sb;

	sb = ft_calloc(1, sizeof(*sb));
	if (sb == NULL)
		return (NULL);
	sb->cap = 32;
	if (sb->cap < cap)
		sb->cap = cap;
	sb->buff = malloc(sb->cap);
	if (sb->buff == NULL)
		return (free(sb), NULL);
	sb->buff[0] = '\0';
	sb->len = 0;
	return (sb);
}

void	str_builder_free(t_str_builder *sb)
{
	if (sb == NULL)
		return ;
	free(sb->buff);
	sb->buff = NULL;
	sb->cap = 0;
	sb->len = 0;
	free(sb);
}

static void	str_builder_ensure_size(t_str_builder *sb, size_t len)
{
	char	*new_buff;

	if (sb == NULL || len == 0)
		return ;
	if (sb->cap >= sb->len + len + 1)
		return ;
	while (sb->cap < sb->len + len + 1)
	{
		sb->cap <<= 1;
		if (sb->cap == 0)
			sb->cap--;
	}
	new_buff = malloc(sb->cap);
	if (new_buff == NULL)
	{
		sb->buff = NULL;
		return (free(sb->buff));
	}
	ft_memcpy(new_buff, sb->buff, sb->len);
}

void	str_builder_append(t_str_builder *sb, const char *str, size_t len)
{
	if (sb == NULL || str == NULL || *str == '\0')
		return ;
	if (len == 0)
		len = ft_strlen(str);
	str_builder_ensure_size(sb, len);
	if (sb->buff == NULL)
		return ;
	ft_memmove(sb->buff + sb->len, str, len);
	sb->len += len;
	sb->buff[sb->len] = '\0';
}

char	*str_builder_str(t_str_builder *sb)
{
	char	*str;

	if (sb == NULL)
		return (NULL);
	if (sb->buff == NULL)
		return (str_builder_free(sb), NULL);
	str = ft_strdup(sb->buff);
	return (str_builder_free(sb), str);
}

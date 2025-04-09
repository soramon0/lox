#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dup;

	dup = (char *)malloc(n + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

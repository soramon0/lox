#include "libft.h"

char	*ft_strsearch(char *haystack[], char *needle)
{
	int	i;
	int	n;

	if (haystack == NULL || needle == NULL)
		return (NULL);
	n = ft_strlen(needle);
	i = 0;
	while (haystack[i] != NULL)
	{
		if (ft_strncmp(haystack[i], needle, n) == 0)
			return (haystack[i]);
		i++;
	}
	return (NULL);
}

#include "lox.h"

char *read_entire_file(char *file)
{
  ssize_t bytes = 0;
  ssize_t pos = 0;
  ssize_t size = 128;
  int fd = open(file, O_RDONLY);
  if (fd == -1)
    return (NULL);
  char *buf = malloc(size + 1);
  if (buf == NULL)
    return (NULL);
  while (1)
  {
    if (pos >= size)
    {
      size += size;
      char *tmp = malloc(size + 1);
      if (tmp == NULL)
        return (free(buf), NULL);
      int i = 0;
      while (buf[i])
      {
        tmp[i] = buf[i];
        i++;
      }
      free(buf);
      buf = tmp;
    }
    bytes = read(fd, buf + pos, 128);
    pos += bytes;
    if (bytes == -1)
      return (free(buf), NULL);
    if (bytes > 0)
      buf[pos] = '\0';
    if (bytes == 0)
      break;
  }
  return (buf);
}

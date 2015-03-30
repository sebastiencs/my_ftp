/*
** convert_telnet_dir.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 08:39:59 2015 chapui_s
** Last update Sun Mar 29 04:12:59 2015 chapui_s
*/

#include "server.h"

size_t		get_size_file(char *file)
{
  struct stat	st;

  stat(file, &st);
  return (st.st_size);
}

static void	remove_home_directory(char *home, char *s)
{
  int		i;
  int		j;
  char		*ptr;
  int		size;

  if ((ptr = strstr(s, home)))
  {
    i = 0;
    size = strlen(home) - 1;
    while (i < size)
    {
      j = 0;
      while (ptr[j])
      {
	ptr[j] = ptr[j + 1];
	j += 1;
      }
      i += 1;
    }
  }
}

char		*convert_telnet(char *home)
{
  int		fd;
  char		*str;
  char		*tmp;
  int		i;

  if ((fd = open(TMP_LIST_DIR, O_RDONLY)) == -1)
    return ((char*)0);
  if ((str = (char*)malloc(get_size_file(TMP_LIST_DIR) * 2 + 1)) == (char*)0)
    return ((char*)0);
  memset(str, 0, get_size_file(TMP_LIST_DIR) * 2 + 1);
  i = 0;
  while ((tmp = get_next_line(fd)))
  {
    if ((i != 0 || strncmp(tmp, "total", 5)) && strlen(tmp) > 0)
    {
      remove_home_directory(home, tmp);
      strcat(str, tmp);
      strcat(str, "\r\n");
    }
    i += 1;
  }
  close(fd);
  return (str);
}

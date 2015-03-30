/*
** get_command.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 22:22:39 2015 chapui_s
** Last update Sat Mar 21 23:52:18 2015 chapui_s
*/

#include "server.h"

int			get_command(t_user *user)
{
  ssize_t		size;

  memset(user->buffer, 0, SIZE_MAX_BUFFER);
  signal(SIGPIPE, SIG_IGN);
  size = read(user->fd, user->buffer, SIZE_MAX_BUFFER);
#ifdef DEBUG
  printf("BUFFER: '%s'\n", user->buffer);
#endif
  if (size == -1)
    return (derror("error: read"));
  else if (size == 0)
    return (derrorn("Client disconnect"));
  return (0);
}

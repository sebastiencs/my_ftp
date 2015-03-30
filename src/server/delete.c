/*
** delete.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 10:22:06 2015 chapui_s
** Last update Sun Mar 22 15:23:52 2015 chapui_s
*/

#include "server.h"

int		delete(t_user *user, char *param)
{
  char		buffer[PATH_MAX];
  char		tmp[PATH_MAX];

  memset(buffer, 0, 1024);
  if (param[0] == '/')
    param = manage_from_root(user, buffer, param);
  realpath(param, tmp);
  if (!strncmp(tmp, user->user.directory, strlen(user->user.directory)))
  {
    if (!remove(tmp))
      send_reply(user->fd, 250, (char*)0);
    else
      send_reply(user->fd, 550, (char*)0);
  }
  else
    send_reply(user->fd, 550, (char*)0);
  return (0);
}

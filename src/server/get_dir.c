/*
** get_dir.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 09:31:52 2015 chapui_s
** Last update Tue Mar 17 11:48:55 2015 chapui_s
*/

#include "server.h"

int		get_dir(t_user *user, char *param)
{
  char		buffer[1024];

  (void)param;
  memset(buffer, 0, 1024);
  strncpy(buffer, user->dir_current, 1023);
  if (buffer[strlen(buffer) - 1] != '/')
    strcat(buffer, "/");
  free(user->dir_current);
  user->dir_current = strdup(buffer);
  send_reply(user->fd, 257, buffer + strlen(user->user.directory) - 1);
  return (0);
}

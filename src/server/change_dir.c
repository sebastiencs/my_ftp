/*
** change_dir.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 08:50:46 2015 chapui_s
** Last update Sun Mar 22 15:23:20 2015 chapui_s
*/

#include "server.h"

char		*manage_from_root(t_user *user, char *buffer, char *param)
{
  strcpy(buffer, user->user.directory);
  buffer[strlen(buffer) - 1] = 0;
  strcat(buffer, param);
  return (buffer);
}

int		change_dir(t_user *user, char *param)
{
  char		buffer[PATH_MAX];
  char		tmp[PATH_MAX];

  memset(buffer, 0, PATH_MAX);
  memset(tmp, 0, PATH_MAX);
  if (param[0] == '/')
    param = manage_from_root(user, buffer, param);
  realpath(param, tmp);
  if (strncmp(tmp, user->user.directory, strlen(user->user.directory)))
  {
    param = user->user.directory;
    strcpy(tmp, param);
  }
  if (!chdir(tmp))
  {
    send_reply(user->fd, 250, (char*)0);
    free(user->dir_current);
    user->dir_current = strdup(tmp);
  }
  else
    send_reply(user->fd, 550, (char*)0);
  return (0);
}

int		change_dir_up(t_user *user, char *param)
{
  (void)param;
  return (change_dir(user, ".."));
}

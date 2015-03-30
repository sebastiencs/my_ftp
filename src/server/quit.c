/*
** quit.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 09:18:02 2015 chapui_s
** Last update Sun Mar 22 15:16:08 2015 chapui_s
*/

#include "server.h"

int		quit(t_user *user, char *param)
{
  (void)param;
  send_reply(user->fd, 221, (char*)0);
  free(user->user.name);
  free(user->user.password);
  free(user->user.directory);
  free(user->dir_current);
  close(user->fd);
  sem_destroy(&g_lock);
  sem_destroy(&g_lock_finish);
  user->run = 0;
  return (0);
}

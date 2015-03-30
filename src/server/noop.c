/*
** noop.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 12:15:38 2015 chapui_s
** Last update Tue Mar 17 12:17:24 2015 chapui_s
*/

#include "server.h"

int		noop(t_user *user, char *param)
{
  (void)param;
  send_reply(user->fd, 200, (char*)0);
  return (0);
}

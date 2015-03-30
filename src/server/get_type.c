/*
** get_type.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 18:11:06 2015 chapui_s
** Last update Tue Mar 17 18:13:53 2015 chapui_s
*/

#include "server.h"

int		get_type(t_user *user, char *param)
{
  (void)param;
  send_reply(user->fd, 200, (char*)0);
  return (0);
}

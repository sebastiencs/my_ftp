/*
** send_syst.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 19:58:27 2015 chapui_s
** Last update Mon Mar 16 20:01:37 2015 chapui_s
*/

#include "server.h"

int		send_syst(t_user *user, char *param)
{
  (void)param;
  send_reply(user->fd, 215, (char*)0);
  return (0);
}

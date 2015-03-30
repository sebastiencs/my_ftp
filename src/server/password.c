/*
** password.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 20:08:15 2015 chapui_s
** Last update Sat Mar 21 23:06:06 2015 chapui_s
*/

#include "server.h"

int		password(t_user *user, char *param)
{
  if (user->status == NOT_LOGGED_IN)
  {
    if (user->user.password && !strcmp(user->user.password, param))
    {
      user->status = LOGGED_IN;
      send_reply(user->fd, 230, (char*)0);
    }
    else
    {
      user->status = NOT_LOGGED_IN;
      send_reply(user->fd, 530, "Login incorrect");
    }
  }
  else
    send_reply(user->fd, 550, (char*)0);
  return (0);
}

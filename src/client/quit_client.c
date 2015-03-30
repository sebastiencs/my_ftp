/*
** quit_client.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 19:52:42 2015 chapui_s
** Last update Thu Mar 19 20:17:52 2015 chapui_s
*/

#include "client.h"

int		quit_client(t_client *client, char *true_cmd, char *param)
{
  (void)true_cmd;
  (void)param;
  client->run = 0;
  if (send_request(client->fd, "QUIT") == -1)
    return (-1);
  if (get_reply(client) == -1 || client->code_reply != 250)
    return (-1);
  close(client->fd);
  return (0);
}

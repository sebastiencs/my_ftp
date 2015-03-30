/*
** noop.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 20:16:10 2015 chapui_s
** Last update Fri Mar 20 03:13:35 2015 chapui_s
*/

#include "client.h"

int		noop(t_client *client, char *true_cmd, char *param)
{
  (void)true_cmd;
  (void)param;
  if (send_request(client->fd, "NOOP") == -1)
    return (-1);
  if (get_reply(client) == -1 || client->code_reply != 227)
    return (-1);
  return (0);
}

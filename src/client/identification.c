/*
** identification.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 22 00:31:00 2015 chapui_s
** Last update Sun Mar 22 00:36:04 2015 chapui_s
*/

#include "client.h"

static int	get_username(t_client *client, char *tmp)
{
  char		*s;

  memset(tmp, 0, 1024);
  my_putstr("Username: ");
  if ((s = get_next_line(0)) == (char*)0)
    return (-1);
  sprintf(tmp, "%s %s", "USER", s);
  free(s);
  if (send_request(client->fd, tmp) == -1)
    return (-1);
  if (get_reply(client) == -1)
    return (-1);
  return (0);
}

static int	get_password(t_client *client, char *tmp)
{
  char		*s;

  memset(tmp, 0, 1024);
  my_putstr("Password: ");
  if ((s = get_next_line(0)) == (char*)0)
    return (-1);
  sprintf(tmp, "%s %s", "PASS", s);
  free(s);
  if (send_request(client->fd, tmp) == -1)
    return (-1);
  if (get_reply(client) == -1)
    return (-1);
  if (client->code_reply != 230)
    return (-1);
  return (0);
}

int		identification(t_client *client)
{
  char		tmp[1024];

  if (get_username(client, tmp) == -1)
    return (-1);
  if (client->code_reply == 230)
    return (0);
  if (get_password(client, tmp) == -1)
    return (-1);
  return (0);
}

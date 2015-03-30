/*
** list_dir.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 17:16:16 2015 chapui_s
** Last update Fri Mar 20 03:13:34 2015 chapui_s
*/

#include "client.h"

int		write_from_telnet(char *s, ssize_t size)
{
  int		i;

  i = 0;
  while (s[i])
  {
    if (s[i] == '\r' && s[i + 1] == '\n')
    {
      s[i] = '\n';
      s[i + 1] = 0;
    }
    i += 1;
  }
  if (write(1, s, size) == -1)
    return (-1);
  memset(s, 0, 1024);
  return (0);
}

int		list_dir(t_client *client, char *true_cmd, char *param)
{
  char		buffer[1024];
  char		buffer_req[1024];
  ssize_t	size;

  if (client->mode == PASSIVE)
    if (passive_mode(client) == -1)
      return (-1);
  memset(buffer, 0, 1024);
  memset(buffer_req, 0, 1024);
  if (client->tab_cmd[1])
    sprintf(buffer_req, "%s %s", true_cmd, param);
  else
    sprintf(buffer_req, "%s", true_cmd);
  if (send_request(client->fd, buffer_req) == -1)
    return (-1);
  if (get_reply(client) == -1 || client->code_reply != 150)
    return (-1);
  while ((size = read(client->passive_fd, buffer, 1023)) > 0)
    if (write_from_telnet(buffer, size) == -1)
      return (-1);
  if (size == -1)
    return (-1);
  if (get_reply(client) == -1 || client->code_reply != 226)
    return (-1);
  return (0);
}

/*
** passive_mode.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 18:34:17 2015 chapui_s
** Last update Thu Mar 19 18:40:22 2015 chapui_s
*/

#include "client.h"

char		*str_replace(char *s, char old, char new)
{
  int		i;

  i = 0;
  while (s[i])
  {
    if (s[i] == old)
      s[i] = new;
    i += 1;
  }
  return (s);
}

int		get_passive_port(t_client *client, char *s)
{
  int		p1;
  int		p2;

  p1 = atoi(s);
  s = strchr(s, '.');
  if (!s)
    return (-1);
  s += 1;
  p2 = atoi(s);
  client->passive_port = (p1 << 8) + p2;
  return (0);
}

int		get_passive_ip(t_client *client)
{
  char		*reply;
  char		*begin;
  int		i;
  int		n;

  memset(client->passive_ip, 0, 16);
  reply = client->buffer;
  reply = str_replace(reply, ',', '.');
  begin = strchr(reply, '(');
  if (!begin)
    return (-1);
  begin += 1;
  i = 0;
  n = 0;
  while (begin[i] && n < 4)
  {
    client->passive_ip[i] = begin[i];
    i += 1;
    if (begin[i] == '.')
      n += 1;
  }
  return (get_passive_port(client, begin + i + 1));
}

int			connect_to_passive(t_client *client)
{
  struct sockaddr_in	server;
  int			fd;

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (derror("error: socket"));
  server.sin_addr.s_addr = inet_addr(client->passive_ip);
  server.sin_family = AF_INET;
  server.sin_port = htons(client->passive_port);
  if ((connect(fd, (struct sockaddr*)&server, sizeof(server))) == -1)
    return (derror("error: connect"));
  client->passive_fd = fd;
  return (0);
}

int		passive_mode(t_client *client)
{
  if (send_request(client->fd, "PASV") == -1)
    return (-1);
  if (get_reply(client) == -1 || client->code_reply != 227)
    return (-1);
  if (get_passive_ip(client) == -1)
    return (-1);
  if (connect_to_passive(client) == -1)
    return (-1);
  return (0);
}

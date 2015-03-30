/*
** connect_to_server.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 22 01:01:15 2015 chapui_s
** Last update Sun Mar 22 14:24:10 2015 chapui_s
*/

#include "client.h"

int			connect_to_server(t_client *client)
{
  struct hostent	*h;
  struct sockaddr_in	server;

  if ((client->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (derror("error: socket"));
  if (!(h = gethostbyname(client->machine)))
    return (derror("error: gethostbyname"));
  server.sin_addr = *(struct in_addr*)h->h_addr_list[0];
  server.sin_family = AF_INET;
  server.sin_port = htons(client->port);
  if ((connect(client->fd, (struct sockaddr*)&server, sizeof(server))) == -1)
    return (derror("error: connect"));
  if (get_reply(client) || client->code_reply != 220)
    return (-1);
  return (0);
}

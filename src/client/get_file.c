/*
** get_file.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 20:49:05 2015 chapui_s
** Last update Sun Mar 29 04:26:06 2015 chapui_s
*/

#include "client.h"

int		write_to_file(int fd,
			      char *buffer,
			      ssize_t size)
{
  if (write(fd, buffer, size) == -1)
  {
    return (-1);
  }
  else
  {
    return (0);
  }
}

void		get_filename(char *buf, char *file)
{
  char		*ptr;

  memset(buf, 0, 1024);
  ptr = strrchr(file, '/');
  if (ptr)
  {
    strncpy(buf, ptr + 1, 1023);
  }
  else
  {
    strncpy(buf, file, 1023);
  }
}

int		init_get_file(t_client *client,
			      char *buffer,
			      char *true_cmd,
			      int *fd)
{
  (void)true_cmd;
  (void)fd;
  if (client->mode == PASSIVE)
    if (passive_mode(client) == -1)
      return (-1);
  signal(SIGPIPE, SIG_IGN);
  if (send_request(client->fd, buffer) == -1)
    return (-1);
  if (get_reply(client) == -1 || client->code_reply != 150)
    return (-1);
  return (0);
}

int		open_local_file(t_client *client,  char *buffer, int i, int *fd)
{
  char		buf_file[1024];

  get_filename(buf_file, client->tab_cmd[i]);
  if ((*fd = open(buf_file, O_WRONLY | O_CREAT | O_TRUNC,
		  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
  {
    puts("Can't open local file");
    close(client->passive_fd);
    get_reply(client);
    return (-1);
  }
  memset(buffer, 0, 1024);
  return (0);

}

int		get_file(t_client *client, char *true_cmd, char *param)
{
  char		buffer[1024];
  ssize_t	size;
  int		fd;
  int		i;

  (void)param;
  i = 1;
  while (client->tab_cmd[i])
  {
    memset(buffer, 0, 1024);
    sprintf(buffer, "%s %s", true_cmd, client->tab_cmd[i]);
    if (init_get_file(client, buffer, true_cmd, &fd) == -1)
      return (-1);
    if (open_local_file(client, buffer, i, &fd) == -1)
      return (-1);
    while ((size = read(client->passive_fd, buffer, 1023)) > 0)
      if (write_to_file(fd, buffer, size) == -1)
	return (-1);
    close(client->passive_fd);
    close(fd);
    if (size == -1 || get_reply(client) == -1 || client->code_reply != 226)
      return (-1);
    i += 1;
  }
  return (0);
}

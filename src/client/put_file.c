/*
** put_file.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 21:31:40 2015 chapui_s
** Last update Sun Mar 22 16:37:21 2015 chapui_s
*/

#include "client.h"

int		write_to_server(int fd, char *buffer, ssize_t size)
{
  ssize_t	i;
  ssize_t	cur;

  i = 0;
  while (i < size)
  {
    cur = write(fd, buffer, size);
    i += cur;
    if (cur == -1)
      return (-1);
  }
  return (0);
}

int		is_file_exist(char *file)
{
  struct stat st;

  return (!stat(file, &st));
}

int		init_put_file(t_client *client,
			      char *buffer,
			      int i,
			      int *fd)
{
  if (!is_file_exist(client->tab_cmd[i]))
  {
    puts("File does not exist");
    return (-1);
  }
  if ((*fd = open(client->tab_cmd[i], O_RDONLY)) == -1)
  {
    puts("Can't open local file");
    return (-1);
  }
  if (client->mode == PASSIVE)
    if (passive_mode(client) == -1)
      return (-1);
  signal(SIGPIPE, SIG_IGN);
  if (send_request(client->fd, buffer) == -1)
    return (-1);
  if (get_reply(client) == -1 || client->code_reply != 150)
    return (-1);
  memset(buffer, 0, 1024);
  return (0);
}

int		put_file(t_client *client, char *true_cmd, char *param)
{
  char		buf_file[1024];
  char		buffer[1024];
  ssize_t	size;
  int		fd;
  int		i;

  (void)param;
  i = 1;
  while (client->tab_cmd[i])
  {
    memset(buffer, 0, 1024);
    get_filename(buf_file, client->tab_cmd[i]);
    sprintf(buffer, "%s %s", true_cmd, buf_file);
    if (init_put_file(client, buffer, i, &fd) == -1)
      return (-1);
    while ((size = read(fd, buffer, 1023)) > 0)
      if (write_to_server(client->passive_fd, buffer, size) == -1)
	return (-1);
    close(client->passive_fd);
    close(fd);
    if (size == -1 ||get_reply(client) == -1 || client->code_reply != 226)
      return (-1);
    i += 1;
  }
  return (0);
}

/*
** list_directory.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 03:05:45 2015 chapui_s
** Last update Sun Mar 29 04:07:04 2015 chapui_s
*/

#include "server.h"

char		*g_argv[] =
{
  "bidon",
  "-l",
  (char*)0,
  (char*)0,
};

int		write_to_file(int fd_file, int argc)
{
  int		tmp_stdout;
  int		tmp_stderr;

  if ((tmp_stdout = dup(1)) == -1)
    return (-1);
  if ((tmp_stderr = dup(2)) == -1)
    return (-1);
  if (dup2(fd_file, 1) == -1)
    return (-1);
  if (dup2(fd_file, 2) == -1)
    return (-1);
  close(fd_file);
  mls(argc, g_argv);
  if (dup2(tmp_stdout, 1) == -1)
    return (-1);
  if (dup2(tmp_stderr, 2) == -1)
    return (-1);
  close(tmp_stdout);
  close(tmp_stderr);
  return (0);
}

int		fail_list(t_user *user)
{
  user->thread_info->data = (void*)0;
  user->thread_info->size_data = 0;
  user->thread_info->read_or_write = -1;
  sem_post(&g_lock);
  send_reply(user->fd, 553, (char*)0);
  return (-1);
}

int		give_to_thread(t_user *user)
{
  char		*s;

  if ((s = convert_telnet(user->user.directory)) == (char*)0)
    return (fail_list(user));
  remove(TMP_LIST_DIR);
  if (user->thread_info)
  {
    user->thread_info->data = (void*)s;
    user->thread_info->size_data = strlen(s);
    user->thread_info->read_or_write = 1;
  }
  sem_post(&g_lock);
  send_reply(user->fd, 150, (char*)0);
  sem_wait(&g_lock_finish);
  send_reply(user->fd, (g_transfer_completed) ? (226) : (550), (char*)0);
  sem_post(&g_lock_finish);
  free(s);
  user->thread_info = (t_thread_info*)0;
  return (0);
}

char		*init_listing(char *buffer,
			      char *tmp,
			      t_user *user,
			      char *param)
{
  memset(buffer, 0, PATH_MAX);
  memset(tmp, 0, PATH_MAX);
  strncpy(tmp, user->user.directory, strlen(user->user.directory));
  tmp[strlen(user->user.directory) - 1] = 0;
  if (param[0] == '/')
  {
    strcat(tmp, param);
    param = tmp;
  }
  return (param);
}

int		list_directory(t_user *user, char *param)
{
  char		buffer[PATH_MAX];
  char		tmp[PATH_MAX];
  int		fd_file;
  int		argc;

  if (user->mode == NONE)
    return (send_reply(user->fd, 550, (char*)0));
  if ((fd_file = open(TMP_LIST_DIR, O_WRONLY | O_CREAT | O_TRUNC,
		      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return (fail_list(user));
  argc = 2;
  param = init_listing(buffer, tmp, user, param);
  realpath(param, buffer);
  if (!strncmp(buffer, user->user.directory, strlen(user->user.directory)))
    g_argv[2] = buffer;
  else
    g_argv[2] = user->user.directory;
  if (param && strlen(param) > 0)
    argc += 1;
  if (write_to_file(fd_file, argc) == -1)
    return (fail_list(user));
  close(fd_file);
  give_to_thread(user);
  user->mode = NONE;
  return (0);
}

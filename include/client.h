/*
** client.h for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 15:55:29 2015 chapui_s
** Last update Sun Mar 22 17:55:06 2015 chapui_s
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <stdio.h>
# include <stdlib.h>
# include <netdb.h>
# include "common.h"

enum		e_mode
{
  PASSIVE,
  ACTIV
};

typedef struct	s_client
{
  char		*machine;
  int		port;
  int		fd;
  int		run;
  int		debug;
  int		code_reply;
  char		**tab_cmd;
  char		buffer[1024];
  char		passive_ip[16];
  int		passive_port;
  int		passive_fd;
  int		mode;
}		t_client;

typedef struct	s_cmds
{
  char		*true_cmd;
  char		*read_cmd;
  int		(*func)(t_client *, char *, char *);
}		t_cmds;

char		**my_str_to_wordtab(char *s);
int		list_dir(t_client *client, char *true_cmd, char *param);
int		send_request(int fd, char *s);
int		get_reply(t_client *client);
int		send_user(t_client *client, char *true_cmd, char *param);
int		passive_mode(t_client *client);
int		change_dir(t_client *client, char *true_cmd, char *param);
int		change_dir_up(t_client *client, char *true_cmd, char *param);
int		quit_client(t_client *client, char *true_cmd, char *param);
int		delete_file(t_client *client, char *true_cmd, char *param);
int		get_cur_dir(t_client *client, char *true_cmd, char *param);
int		help(t_client *client, char *true_cmd, char *param);
int		noop(t_client *client, char *true_cmd, char *param);
int		get_file(t_client *client, char *true_cmd, char *param);
int		put_file(t_client *client, char *true_cmd, char *param);
int		send_password(t_client *client, char *true_cmd, char *param);
int		local_cd(t_client *client, char *true_cmd, char *param);
int		local_pwd(t_client *client, char *true_cmd, char *param);
int		local_ls(t_client *client, char *true_cmd, char *param);
int		identification(t_client *client);
int		usage(void);
int		get_info_client(t_client *client, int argc, char **argv);
int		get_reply(t_client *client);
int		connect_to_server(t_client *client);
int		send_request(int fd, char *s);
int		get_command(t_client *client, char *buffer);
void		get_filename(char *buf, char *file);
void		manage_sigint(t_client* ptr);
void		catch_sigint(int sig);

#endif /* !CLIENT_H_ */

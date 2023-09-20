#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* environment, program name & history counter */
extern char **environ;
char *name;
int hist;

typedef struct data
{
	char **av;			/* argument vector */
	char *input;			/* command line written by the user */
	char **args;			/* tokens of the command line */
	int status;			/* last status of the shell */
	int counter;			/* lines counter */
	char **_environ;		/* environment variable */
	char *pid;			/* process ID of the shell */
	int readfd;
} shell_t;

/* struct sep_list_s - single linked list */
typedef struct sep_list_s
{
	char separator;			/*  @separator: ; | & */
	struct sep_list_s *next;
} sep_list;

/* struct line_list_s - single linked list */
typedef struct line_list_s
{
	char *line;				/* command line */
	struct line_list_s *next;		/* single linked list */
} line_list;

/* struct r_var_list - single linked list */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/** struct builtin_s - Builtin struct for command args. */
typedef struct builtin_s
{
	char *name;			/* name of command builtin i.e cd, exit,env */
	int (*f)(shell_t *info);
} builtin_t;

typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

typedef struct  bulltin
{
	char *command;
	int (*fun)(char **line, int er);
} bul_t;

/* alias linked list*/
alias_t *aliases;

/* lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* lists1.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* strings.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* memory.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_args(char **args, char **front);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* strings2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);

/* strings1.c */
int _isdigit(const char *s);
void rev_string(char *s);

/* syntax.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(shell_t *info, char *input, int i, int bool);
int check_syntax_error(shell_t *info, char *input);

/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(shell_t *info);

/* parser.c */
char *swap_chars(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next_cmd(sep_list **list_s, line_list **list_l, shell_t *info);
int tokenize(shell_t *info, char *input);
char **split_line(char *input);

/* readline.c */
char *read_line(int *i_eof);
void check_env(r_var **h, char *in, shell_t *info);
int check_vars(r_var **h, char *in, char *st, shell_t *info);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, shell_t *info);

/* getline.c */
void assign_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* executing.c */
int exec_cmd(shell_t *info);

/* cmds.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(shell_t *info);
int check_error_cmd(char *dir, shell_t *info);
int cmd_exec(shell_t *info);

/* environ.c */
char *_getenv(const char *name, char **_environ);
int cmp_env_name(const char *nenv, const char *name);
int print_env(shell_t *info);
char *copy_info(char *name, char *value);

/* set_env */
void set_env(char *name, char *value, shell_t *info);
int _setenv(shell_t *info);
int _unsetenv(shell_t *info);

/* cd.c */
void cd_dot(shell_t *info);
void cd_to_dir(shell_t *info);
void cd_to_pre(shell_t *info);
void cd_to_home(shell_t *info);
int change_cd(shell_t *info);

/* builtins.c */
int (*get_builtin(char *cmd))(shell_t *info);

/* exit.c */
int exit_shell(shell_t *info);
char *exit_shell_error(shell_t *info);
void help_exit(void);

/* strdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* errors.c */
char *strcat_cderror(shell_t *, char *, char *, char *);
char *get_cd_error(shell_t *info);
char *error_not_found(shell_t *info);
char *path_error_126(shell_t *info);
char *env_error(shell_t *info);

/* get_sigint.c */
void get_sigint(int sig);

/* help_patterns.c */
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help(void);
void help_cd(void);

/* get_help.c */
int get_help(shell_t *info);
void help_alias(void);
void general_help(void);

/* shell.c */
void set_data(shell_t *info, char **av);
void free_data(shell_t *info);
int main(int ac, char **av);

/* get_error.c */
int get_error(shell_t *info, int eval);
char *error_get_alias(char **args);
char *error_syntax(char **args);
char *error_permission(char **args);

/* alias.c */
int shell_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/* alias_linkedlist.c*/
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);

#endif

#ifndef SHELL_H
#define SHELL_H

#define _TRUE            1
#define _FALSE           0

#define STDIN            0
#define STDOUT           1
#define STDERR           2

#define NON_INTERACTIVE  0
#define INTERACTIVE      1

#define PERMISSIONS      1
#define NON_PERMISSIONS -1

#define _FILE            10
#define NON_FILE         -10

#define _ENOENT          "No such file or directory"
#define _EACCES          "Permission denied"
#define _CMD_NOT_EXISTS  "not found"
#define _ILLEGAL_NUMBER  "Illegal number"

#define _CODE_ENOENT           3
#define _CODE_EACCES           13
#define _CODE_CMD_NOT_EXISTS   132
#define _CODE_ILLEGAL_NUMBER   133
typedef struct __attribute__((__packed__))
{
	char *command;            /* Command to execute */
	int n_commands;           /* Number of commands executed */
	char *utility_path;         /* Path of a command */
	int current_path;      /* Check if is current path or not */
	int status_code;          /* Last exit code */	
	int argc;                 /* Number of arguments received */
	char **argv;              /* Arguments received */
	int mode;                 /* INTERACTIVE or NON_INTERACTIVE */
	int error_code;           /* Error code for error message */
	char *buffer;             /* Line readed with the getline */
	char **arguments;         /* Line splited into words */
	char *environment;        /* Last environment variable get it */
	int pid;                  /* Process id */
} shell_t;

typedef struct __attribute__((__packed__))
{
	char *sms;            /* Error message */
	int code;                 /* Error code for identify the error message */
} error_t;

typedef struct __attribute__((__packed__))
{
	char *cmd;            /* arguments[0] = cmd */
	void (*func)(shell_t *info, char **arguments);
} builtin_t;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

/* cmds.c */
void analyze(char **arguments, shell_t *info, char *buff);

/* permissions.c */
int executable(char *filename);
int is_file(char *command);

/* environ.c */
void shell_env(shell_t *info, char **arguments);
char *_getenv(const char *name);
char *find_dir(char *filename, shell_t *info);
void current_path(char *path, shell_t *info);
void get_environment(void);

/* execute.c */
void execute(char *commands, char **arguments, shell_t *info, char *buff);
int current_directory(char *cmd, char **arguments, char *buff,
		shell_t *info);

/* error.c */
char *msg_match(shell_t info);
void error(shell_t *info);
void error_extra(shell_t *info, char *extra);


/* builtins.c */
int builtins(shell_t *info, char **arguments);
int check_builtin(shell_t *info, char **arguments);

/* exit.c */
void shell_exit(shell_t *info, char **arguments);
int number_controller(shell_t *info, char *number);

/* Entry point of the shell */
void start(shell_t *info);

/* memory.c */
void *_realloc(void *ptr, size_t old_size, size_t new_size);
void free_memory_p(void *ptr);
void free_memory_pp(void **ptr);

/* prompt.c */
void get_prompt(shell_t *info);
void prompt(shell_t *info);
char *read_prompt();
void sigHandler(int sig_num);

/* strings.c */
int _strlen(char *msg);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
int _strcmp(char *str1, char *str2);
char *to_string(int number);
int is_digit(unsigned int n);
int _atoi(char *s);
int is_alpha(char *s);

/* printout.c */
int _putchar_to_fd(char l, int fd);
int print_to_fd(char *msg, int fd);
int _putchar(char c);
int print(char *msg);
int print_err(char *msg);

/* parser.c */
char **tokenize(char *line, const char *sep);
char *join_tokens(char *word1, char *word2, char *word3, const char *sep);

/* patterns.c */
void test_patterns(shell_t *info, char **arguments);
char *pattern_handler(shell_t *info, char *string);
char *replace_value(shell_t *info, int *index, char *string);
char *replacement(shell_t *info, int *index, char *string);
char *replace_env(shell_t *info, char *environment);

#endif /* SHELL_H */

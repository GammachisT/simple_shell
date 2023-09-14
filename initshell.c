#include "shell.h"

/**
 * start - Handle the mode
 * Description: Mode can be INTERACTIVE or NON_INTERACTIVE
 *
 * @info: Struct of information about the shell
 **/
void start(shell_t *info)
{
	get_prompt(info);
}

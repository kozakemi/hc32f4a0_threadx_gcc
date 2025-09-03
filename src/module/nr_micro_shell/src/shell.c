#include "shell.h"
#include "nr_micro_shell.h"
#include <string.h>
#include <ctype.h>

static void shell_cmd_help(char argc, char *argv);
static void shell_cmd_version(char argc, char *argv);
static void shell_ls_cmd(char argc, char *argv);
static void shell_test_cmd(char argc, char *argv);
const static_cmd_st static_cmd[] = {
	{"ls", shell_ls_cmd, "list all commands"},
	{"test", shell_test_cmd, "test command"},
	{"help", shell_cmd_help, "Show help information"},
	{"version", shell_cmd_version, "Show version information"},
	{"\0", NULL, NULL}
};
/**
 * @brief help command
 * @param argc argument count
 * @param argv argument vector
 * @return int return value
 */
static void shell_cmd_help(char argc, char *argv)
{
    (void)argc;
    (void)argv;
    
    shell_printf("Available commands:\r\n");
    shell_printf("  help - Show this help message\r\n");
    shell_printf("  version - Show version information\r\n");
    
}

/**
 * @brief version command
 * @param argc argument count
 * @param argv argument vector
 * @return int return value
 */
static void shell_cmd_version(char argc, char *argv)
{
    (void)argc;
    (void)argv;
    
    shell_printf("HC32F4A0 Template v1.0.0\r\n");
    shell_printf("Built with nr_micro_shell\r\n");
}
/**
 * @brief ls command
 */
static void shell_ls_cmd(char argc, char *argv)
{
	unsigned int i = 0;
	if (argc > 1) {
		if (!strcmp("cmd", &argv[(unsigned char)argv[1]])) {
			for (i = 0; nr_shell.static_cmd[i].fp != NULL; i++) {
				shell_printf("%s : %s", nr_shell.static_cmd[i].cmd, nr_shell.static_cmd[i].description);
				shell_printf("\r\n");
			}
		} else if (!strcmp("-v", &argv[(unsigned char)argv[1]])) {
			shell_printf("ls version 1.0.\r\n");
		} else if (!strcmp("-h", &argv[(unsigned char)argv[1]])) {
			shell_printf("useage: ls [options]\r\n");
			shell_printf("options: \r\n");
			shell_printf("\t -h \t: show help\r\n");
			shell_printf("\t -v \t: show version\r\n");
			shell_printf("\t cmd \t: show all commands\r\n");
		}
	} else {
		shell_printf("ls need more arguments!\r\n");
	}
}

/**
 * @brief test command
 */
static void shell_test_cmd(char argc, char *argv)
{
	unsigned int i;
	shell_printf("test command:\r\n");
	for (i = 0; i < argc; i++) {
		shell_printf("paras %d: %s\r\n", i, &(argv[(unsigned char)argv[i]]));
	}
}
/**
 * @brief 
 * 
 */
void nr_micro_shell_init(void)
{
    shell_init();
}
/**
 * @brief  shell loop
 * 
 */
void nr_micro_shell_loop(void)
{
	char c = 0;
	while(SEGGER_RTT_HasKey())
	{
		c = SEGGER_RTT_GetKey();       
        shell(c);
	}	
}

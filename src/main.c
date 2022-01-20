/*
 * main.c
 *
 * central gb emulation file
 * handles screen initialization and option processing
 */

#include "cpu.h"
#include "global.h"
#include "gpu.h"
#include "include.h"
#include "input.h"
#include "registers.h"
#include "rom.h"

///////////////
//
// GLOBAL VARS
//
///////////////

bool debug = false;	// debug flag

bool running = true;

///////////////
//
// PROTOTYPES
//
///////////////
// print a message regarding the usage of gbemu
// automatically exits program with exit code 1
void usage(char *msg)
{
	fprintf(stderr, "%s: <flags> filename\n", msg);
	fprintf(stderr, "\t-d: enable debug\n");
	fprintf(stderr, "\t-t: term only\n");
	fprintf(stderr, "\t-h: show this message\n");
	exit(1);
}

// print error message and exit with code 1
void p_error(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

int main(int argc, char **argv)
{
	char *filename;						// filename provided from user
	char ch;									// char for options
	int argnum = 1;
	
///////////////////////////////////////////////////////////
//
// Initlize and Arguments
//
///////////////////////////////////////////////////////////

	// arg checking
	while ((ch = getopt(argc, argv, "dth:")) != -1) {
		argnum++;
		switch (ch) {
			case 'd': /* debug */
				debug = true;
				break;
			case 'h': /* help */
				usage(argv[0]);
				break;
		}
	}

	// check for filename and set filename
	if (argnum >= argc) {
		usage(argv[0]);
	}
	filename = argv[argnum];

/////////////////////////////////////////////////////////
//
// Rom Prep and Loading
//
/////////////////////////////////////////////////////////

	initRegs();

	// load rom
	if (debug) {
		printf("-----------------------------------------------\n\n");
		printf("loading file...\n\n");
	}

	if (loadROM(filename) == -1) p_error("error loading file");

	registers.pc = ROM_START;

	// print legend for debug info
	if (debug) printf("Instr\t\t\tOP\trF\trA\trB\trC\trD\trE\trH\trL\trSP\trPC\n");
	
  gpu_init();

///////////////////////////////////////////////////////////
//
// Program Loop
//
///////////////////////////////////////////////////////////
	while (running) {
    if (!stopped) {
		  cpu_step();
      
    }

    process_inputs();
	}

  SDL_DestroyWindow(window);

	return 0;
}

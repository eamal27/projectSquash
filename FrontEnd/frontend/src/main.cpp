#include "REPL.h"

/**
 * Main Loop for program repl, handles collection of user input
 *
 * @return Exit code of program.
 */
int main(int argc, char* argv[]) {
    REPL* repl;
    string logsFolder;
    if (argc == 2) {
        // assume that logs folder has been provided as only argument
        logsFolder = argv[1];
        repl = new REPL(logsFolder);
    } else {
        // Set to default logs folder
        logsFolder = "../logs/";
        repl = new REPL(logsFolder);
    }

    repl->run();
    delete repl;
}

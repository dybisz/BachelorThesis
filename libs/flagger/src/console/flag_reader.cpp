//
// Created by jakub on 11/10/15.
//

#include <iostream>
#include <console/flag_reader.h>

namespace console {

    std::vector<Flag> flags;

    void readFlags(int argc, char *argv[]) {
        std::vector<Flag> flags = getFlags();

        int i = 1;

        while (i < argc) {
            // Print help and exit app
            if (std::string(argv[i]) == "--help") {
                usage(argv[0], "Called for Help: ");
                exit(EXIT_FAILURE);
            }
                // Or set all flags
            else {
                for (unsigned int j = 0; j < flags.size(); j++) {
                    if (argv[i] == flags[j].long_f ||
                        argv[i] == flags[j].short_f) {
                        std::string error;
                        // If value is missing
                        if (isError(argc, argv, i, flags[j], error)) {
                            usage(argv[0], error.c_str());
                            exit(EXIT_FAILURE);
                        }
                        flags[j].apply(argv[i + 1]);
                    }
                }
            }
            i++;
        }
    }

    bool isError(int argc, char *argv[], int i, Flag flag, std::string &error) {
        int j = i + 1;

        if (j >= argc && flag.type != BOOL) {
            error = "Not enough arguments";
            return true;
        }
        std::string str(argv[j]);
        if (str[0] == '-') {
            error = "Wrong input, values of flags can't start with /'-/'";
            return true;
        }
        return false;
    }

    void usage(char *appName, const char *what) {
        std::vector<Flag> flags = getFlags();
        std::string INTENT = "    ";
        std::string PATH_TO_INFO = ".";
        int infoIntentStartColumn = 50;

        std::cout << what << std::endl;
        std::cout << appName << " Proper Flags: " << std::endl;
        for (unsigned int i = 0; i < flags.size(); i++) {
            int lineLength = 0;
            lineLength += flags[i].short_f.size();
            lineLength += INTENT.size();
            lineLength += flags[i].long_f.size();

            int actualIntentStart = infoIntentStartColumn - lineLength;

            std::cout
            << flags[i].short_f << INTENT
            << flags[i].long_f << " ";
            for (int j = 1; j < actualIntentStart; j++)
                std::cout << PATH_TO_INFO;
            std::cout << " " << flags[i].info
            << std::endl;
        }
    }

    void addFlag(Flag flag){
        flags.push_back(flag);
    }

    std::vector<Flag> getFlags() {
        return flags;
    }
}
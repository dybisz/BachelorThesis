Classification experiments based on Hill Climber heuristics.

######################
#   RUN
######################

The "run_example.sh" script will run an example computations for Hill Climber

Let the current working directory be this one then run:
    ./run_example.sh

######################
#   SETTINGS
######################

Proper flags and their meanings:

-N    --cl-native-path ........................... Path to xls file with Native objects
-F    --cl-foreign-path .......................... Path to xls file with Foreign objects
-A    --cl-alph-size ............................. Size of the alphabet - defines precision
-T    --cl-test-ratio ............................ Ratio of Test set

-I    --max-iter ................................. Maximum iterations of classifier
-H    --hill-climber-states ...................... States in Hill Climber experiment
-U    --classes-to-load .......................... Number of classes to load
-u    --patterns-per-class ....................... Pattern per class to load

-D    --log-main-dir ............................. Main directory to store all logs
-d    --log-dir .................................. directory to store logs of current computations

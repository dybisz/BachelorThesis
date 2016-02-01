Classifier Constructor - experiments based on PSO heuristics

######################
#   RUN
######################
After sucesfull installation the application can be ran as follows.

The "run_example.sh" script will run an example computations for Hill Climber

Let the current working directory be this one then run:
    ./run_example.sh

######################
#   SETTINGS
######################

Proper flags and their meanings:

-E    --exp ...................................... Expiriment ID - 0: Classifier Construction 1: Transformation Analysis

-N    --cl-native-path ........................... Path to xls file with Native objects
-F    --cl-foreign-path .......................... Path to xls file with Foreign objects
-C    --cl-states-native ......................... Number of states corresponding to native languages
-c    --cl-states-foreign ........................ Number of states corresponding to foreign languages
-A    --cl-alph-size ............................. Size of the alphabet - defines precision
-T    --cl-test-ratio ............................ Ratio of Test set

-U    --classes-to-load .......................... Classes to load from xls file
-u    --patterns-per-class ....................... Maximum number of patterns in each class

-I    --max-iter ................................. Maximum iterations of classifier
-v    --vel-weight ............................... Particle Velocity Weight
-V    --max-vel .................................. Max Velocity
-S    --swarm-size ............................... Swarm size
-P    --fit ...................................... Fitness Updater Type - ACCURACY_OVERALL: 1, PRECISION_OVERALL: 2, SENSITIVITY_OVERALL: 3, FMEASURE_OVERALL: 4, ACCURACY_DISTINCT: 5, PRECISION_DISTINCT: 6, SENSITIVITY_DISTINCT: 7, FMEASURE_DISTINCT: 8

-g    --d-thread-count ........................... Default Thread Count - used only when system can't determine optimal number of threads
-G    --t-thread-count ........................... True Thread Count - How many threads should be activated. If value is below 1 then Optimal number of threads will be chosen

-r    --min-alph ................................. Minimal Alphabet Size
-R    --max-alph ................................. Maximum Alphabet Size

-D    --log-main-dir ............................. Main directory to store all logs
-d    --log-dir .................................. directory to store logs of current computations
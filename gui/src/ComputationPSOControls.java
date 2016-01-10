import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;

public class ComputationPSOControls extends AnchorPane implements ComputationsControls {

    /* ---------------------------------------- */
    /* ----- FXML OBJECTS - CORE SETTINGS ----- */
    /* ---------------------------------------- */
    @FXML
    TextField populationFactor;
    @FXML
    TextField fitnessTolerance;
    @FXML
    TextField swarmSize;
    @FXML
    TextField defaultThreads;
    @FXML
    TextField trueThreads;
    @FXML
    TextField kmTolerance;
    @FXML
    TextField kmIterations;
    @FXML
    TextField kmStartingK;
    @FXML
    TextField kmEndingK;
    @FXML
    TextField nativeStates;
    @FXML
    TextField foreignStates;
    @FXML
    TextField startingStates;
    @FXML
    TextField endingStates;
    @FXML
    TextField learningFactor;
    @FXML
    TextField particleVelocity;
    @FXML
    TextField speedFactor;
    @FXML
    TextField maxVelocity;
    @FXML
    Label populationFactorLabel;
    @FXML
    Label fitnessToleranceLabel;
    @FXML
    Label swarmSizeLabel;
    @FXML
    Label defaultThreadsLabel;
    @FXML
    Label trueThreadsLabel;
    @FXML
    Label kmToleranceLabel;
    @FXML
    Label kmIterationsLabel;
    @FXML
    Label kmStartingKLabel;
    @FXML
    Label kmEndingKLabel;
    @FXML
    Label nativeStatesLabel;
    @FXML
    Label foreignStatesLabel;
    @FXML
    Label startingStatesLabel;
    @FXML
    Label endingStatesLabel;
    @FXML
    Label learningFactorLabel;
    @FXML
    Label particleVelocityLabel;
    @FXML
    Label speedFactorLabel;
    @FXML
    Label maxVelocityLabel;


    /* ----------------- */
    /* ----- FLAGS ----- */
    /* ----------------- */
    private final String FLAG_POPULATION_FACTOR = " --pop-fac ";
    private final String FLAG_FITNESS_TOLERANCE = " --fit-tol ";
    private final String FLAG_SWARM_SIZE = " --swarm-size ";
    private final String FLAG_DEFAULT_THREADS = " --d-thread-count ";
    private final String FLAG_TRUE_THREADS = " --t-thread-count ";
    private final String FLAG_KM_TOLERANCE = " --km-tol ";
    private final String FLAG_KM_ITERATIONS = " --km-iter ";
    private final String FLAG_KM_STARTING_K = " --km-s-k ";
    private final String FLAG_KM_ENDING_K = " --km-e-k ";
    private final String FLAG_NATIVE_STATES = " --cl-states-native ";
    private final String FLAG_FOREIGN_STATES = " --cl-states-foreign ";
    private final String FLAG_STARTING_N_STATES = " --state-min ";
    private final String FLAG_ENDING_N_STATES = " --state-max ";
    private final String FLAG_LEARNING_FACTOR = " --learn-fac ";
    private final String FLAG_PARTICLE_VELOCITY_WEIGHT = " --vel-weight ";
    private final String FLAG_SPEED_FACTOR = " --speed-fac ";
    private final String FLAG_MAX_VELOCITY = " --max-vel ";

    /* ---------------------------- */
    /* ------ PARAMETERS INFO ----- */
    /* ---------------------------- */
    private final String INFO_POPULATION_FACTOR = "The swarm size is scaled " +
            "by this factor.";
    private final String INFO_FITNESS_TOLERANCE = "Look for fitness value no" +
            "bigger than FITNESS_TOLERANCE\n" +
            "Possible values: [0, 1], where 1 is the most optimal DFA.";
    private final String INFO_SWARM_SIZE = "Number of particles \n in PSO " +
            "computations.";
    private final String INFO_DEFAULT_THREADS = "If the optimal number of" +
            "threads can not \n be determined by the system" +
            "this value will be used";
    private final String INFO_TRUE_THREADS = "The actual number of threads to be used in computation.\n" +
            "If the value is below 1, then it will be up to the system to choose\n" +
            "the optimal number of threads.\n" +
            "If the optimal number of threads can not be determined, then\n" +
            "DEFAULT_THREAD_COUNT will be used.";
    private final String INFO_KM_TOLERANCE = "The convergence tolerance in " +
            "kmeans.";
    private final String INFO_KM_ITERATIONS = "The maximum iterations of " +
            "kmeans.";
    private final String INFO_KM_STARTING_K = "Starting number of cluster to evaluate.";
    private final String INFO_KM_ENDING_K = "Finishing number of cluster to evaluate.";
    private final String INFO_NATIVE_STATES = "How many states corresponds to" +
            " native languages.";
    private final String INFO_FOREIGN_STATES = "How many states corresponds " +
            "to foreign languages.";
    private final String INFO_STARTING_N_STATES = "Minimum states to check.";
    private final String INFO_ENDING_N_STATES = "Maximum number of states to " +
            "check.";
    private final String INFO_LEARNING_FACTOR = "TODO comment";
    private final String INFO_PARTICLE_VELOCITY_WEIGHT = "TODO comment";
    private final String INFO_SPEED_FACTOR = "The factor of the maximum " +
            "change in position that one particle can take\n" +
            "during a single PSO iteration.";
    private final String INFO_MAX_VELOCITY = "The maximum change that " +
            "particle can make in single iteration.";

    /* ------------------------------------- */
    /* ----- PARAMETERS DEFAULT VALUES ----- */
    /* ------------------------------------- */
    private final String DEFAULT_POPULATION_FACTOR_VALUE = "1.0";
    private final String DEFAULT_FITNESS_TOLERANCE_VALUE = "1.0";
    private final String DEFAULT_SWARM_SIZE_VALUE = "100";
    private final String DEFAULT_DEFAULT_THREADS_VALUE = "4";
    private final String DEFAULT_TRUE_THREADS_VALUE = "0";
    private final String DEFAULT_KM_TOLERANCE_VALUE = "0.0001";
    private final String DEFAULT_KM_ITERATIONS_VALUE = "1000";
    private final String DEFAULT_KM_STARTING_K_VALUE = "2";
    private final String DEFAULT_KM_ENDING_K_VALUE = "6";
    private final String DEFAULT_NATIVE_STATES_VALUE = "1";
    private final String DEFAULT_FOREIGN_STATES_VALUE = "1";
    private final String DEFAULT_STARTING_N_STATES_VALUE = "3";
    private final String DEFAULT_ENDING_N_STATES_VALUE = "15";
    private final String DEFAULT_LEARNING_FACTOR_VALUE = Double.toString(0.5
            + Math.log(2.0));
    private final String DEFAULT_PARTICLE_VELOCITY_WEIGHT_VALUE = Double
            .toString(1.0 / (2.0 * Math.log(2.0)));
    private final String DEFAULT_SPEED_FACTOR_VALUE = "0.05";
    private final String DEFAULT_MAX_VELOCITY_VALUE = "0.3";

    /**
     * Loads Pane from .fxml file and fixes node's default values and tooltips.
     */
    ComputationPSOControls() {
        FxmlLoader.loadFxml(this, "/pso_config.fxml");
        setDefaultValues();
        setTooltips();
    }

    /**
     * Sets default values for all PSO related interface objects.
     */
    private void setDefaultValues() {
        populationFactor.setText(DEFAULT_POPULATION_FACTOR_VALUE);
        fitnessTolerance.setText(DEFAULT_FITNESS_TOLERANCE_VALUE);
        swarmSize.setText(DEFAULT_SWARM_SIZE_VALUE);
        defaultThreads.setText(DEFAULT_DEFAULT_THREADS_VALUE);
        trueThreads.setText(DEFAULT_TRUE_THREADS_VALUE);
        kmTolerance.setText(DEFAULT_KM_TOLERANCE_VALUE);
        kmIterations.setText(DEFAULT_KM_ITERATIONS_VALUE);
        kmStartingK.setText(DEFAULT_KM_STARTING_K_VALUE);
        kmEndingK.setText(DEFAULT_KM_ENDING_K_VALUE);
        nativeStates.setText(DEFAULT_NATIVE_STATES_VALUE);
        foreignStates.setText(DEFAULT_FOREIGN_STATES_VALUE);
        startingStates.setText(DEFAULT_STARTING_N_STATES_VALUE);
        endingStates.setText(DEFAULT_ENDING_N_STATES_VALUE);
        learningFactor.setText(DEFAULT_LEARNING_FACTOR_VALUE);
        particleVelocity.setText(DEFAULT_PARTICLE_VELOCITY_WEIGHT_VALUE);
        speedFactor.setText(DEFAULT_SPEED_FACTOR_VALUE);
        maxVelocity.setText(DEFAULT_MAX_VELOCITY_VALUE);
    }

    /**
     * Most of User Interface Objects has tooltip assign to them. This method
     * initializes tooltips and perform connection with elements.
     */
    private void setTooltips() {
        populationFactor.setTooltip(Tooltips.generateTooltip(INFO_POPULATION_FACTOR));
        fitnessTolerance.setTooltip(Tooltips.generateTooltip(INFO_FITNESS_TOLERANCE));
        swarmSize.setTooltip(Tooltips.generateTooltip(INFO_SWARM_SIZE));
        defaultThreads.setTooltip(Tooltips.generateTooltip(INFO_DEFAULT_THREADS));
        trueThreads.setTooltip(Tooltips.generateTooltip(INFO_TRUE_THREADS));
        kmTolerance.setTooltip(Tooltips.generateTooltip(INFO_KM_TOLERANCE));
        kmIterations.setTooltip(Tooltips.generateTooltip(INFO_KM_ITERATIONS));
        kmStartingK.setTooltip(Tooltips.generateTooltip(INFO_KM_STARTING_K));
        kmEndingK.setTooltip(Tooltips.generateTooltip(INFO_KM_ENDING_K));
        nativeStates.setTooltip(Tooltips.generateTooltip(INFO_NATIVE_STATES));
        foreignStates.setTooltip(Tooltips.generateTooltip(INFO_FOREIGN_STATES));
        startingStates.setTooltip(Tooltips.generateTooltip(INFO_STARTING_N_STATES));
        endingStates.setTooltip(Tooltips.generateTooltip(INFO_ENDING_N_STATES));
        learningFactor.setTooltip(Tooltips.generateTooltip(INFO_LEARNING_FACTOR));
        particleVelocity.setTooltip(Tooltips.generateTooltip(INFO_PARTICLE_VELOCITY_WEIGHT));
        speedFactor.setTooltip(Tooltips.generateTooltip(INFO_SPEED_FACTOR));
        maxVelocity.setTooltip(Tooltips.generateTooltip(INFO_MAX_VELOCITY));
    }

    /**
     * @return String object based on provided flags and their values.
     * Properly appended, constitutes settings of PSO computations.
     */
    @Override
    public String collectFlags() {
        return getPopulationFactorAsFlag() + getFitnessToleranceAsFlag() +
                getSwarmSizeAsFlag() + getDefaultsThreadsAsFlag() +
                getTrueThreadsAsFlag() + getKmToleranceAsFlag() +
                getKmIterationsAsFlag() + getKmStartingKAsFlag() +
                getKmEndingKAsFlag() + getNativeStatesAsFlag() +
                getForeignStatesAsFlag() + getStartingStatesAsFlag() +
                getEndingStatesAsFlag() + getLearningFactorAsFlag() +
                getParticleVelocityAsFlag() + getSpeedFactorAsFlag() +
                getMaxVelocityAsFlag();
    }

    /**
     * @return Population factor value preceded with appropriate flag.
     */
    private String getPopulationFactorAsFlag() {
        return FLAG_POPULATION_FACTOR + " " + populationFactor.getText();
    }

    /**
     * @return Fitness tolerance value preceded with appropriate flag.
     */
    private String getFitnessToleranceAsFlag() {
        return FLAG_FITNESS_TOLERANCE + " " + fitnessTolerance.getText();
    }

    /**
     * @return Swarm size value preceded with appropriate flag.
     */
    private String getSwarmSizeAsFlag() {
        return FLAG_SWARM_SIZE + " " + swarmSize.getText();
    }

    /**
     * @return Default threads number value preceded with appropriate flag.
     */
    private String getDefaultsThreadsAsFlag() {
        return FLAG_DEFAULT_THREADS + " " + defaultThreads.getText();
    }

    /**
     * @return True threads number value preceded with appropriate flag.
     */
    private String getTrueThreadsAsFlag() {
        return FLAG_TRUE_THREADS + " " + trueThreads.getText();
    }

    /**
     * @return K-Means tolerance value preceded with appropriate flag.
     */
    private String getKmToleranceAsFlag() {
        return FLAG_KM_TOLERANCE + " " + kmTolerance.getText();
    }

    /**
     * @return K-Means iterations value preceded with appropriate flag.
     */
    private String getKmIterationsAsFlag() {
        return FLAG_KM_ITERATIONS + " " + kmIterations.getText();
    }

    /**
     * @return K-Means starting K value preceded with appropriate flag.
     */
    private String getKmStartingKAsFlag() {
        return FLAG_KM_STARTING_K + " " + kmStartingK.getText();
    }

    /**
     * @return K-Means ending K value preceded with appropriate flag.
     */
    private String getKmEndingKAsFlag() {
        return FLAG_KM_ENDING_K + " " + kmEndingK.getText();
    }

    /**
     * @return Native states value preceded with appropriate flag.
     */
    private String getNativeStatesAsFlag() {
        return FLAG_NATIVE_STATES + " " + nativeStates.getText();
    }

    /**
     * @return Foreign states value preceded with appropriate flag.
     */
    private String getForeignStatesAsFlag() {
        return FLAG_FOREIGN_STATES + " " + foreignStates.getText();
    }

    /**
     * @return Starting number of states value preceded with appropriate flag.
     */
    private String getStartingStatesAsFlag() {
        return FLAG_STARTING_N_STATES + " " + startingStates.getText();
    }

    /**
     * @return Ending number of states value preceded with appropriate flag.
     */
    private String getEndingStatesAsFlag() {
        return FLAG_ENDING_N_STATES + " " + endingStates.getText();
    }

    /**
     * @return Learning factor value preceded with appropriate flag.
     */
    private String getLearningFactorAsFlag() {
        return FLAG_LEARNING_FACTOR + " " + learningFactor.getText();
    }

    /**
     * @return Particle velocity weight value preceded with appropriate flag.
     */
    private String getParticleVelocityAsFlag() {
        return FLAG_PARTICLE_VELOCITY_WEIGHT + " " + particleVelocity.getText();
    }

    /**
     * @return Speed factor value preceded with appropriate flag.
     */
    private String getSpeedFactorAsFlag() {
        return FLAG_SPEED_FACTOR + " " + speedFactor.getText();
    }

    /**
     * @return Max velocity value preceded with appropriate flag.
     */
    private String getMaxVelocityAsFlag() {
        return FLAG_MAX_VELOCITY + " " + maxVelocity.getText();
    }

}

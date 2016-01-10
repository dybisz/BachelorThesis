import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;

public class ComputationHillClimberControls extends AnchorPane implements ComputationsControls {

    /* ---------------------------------------- */
    /* ----- FXML OBJECTS - CORE SETTINGS ----- */
    /* ---------------------------------------- */

    @FXML
    TextField classesToLoad;
    @FXML
    TextField patternsPerClass;
    @FXML
    TextField states;
    @FXML
    Label classesToLoadLabel;
    @FXML
    Label patternsPerClassLabel;
    @FXML
    Label statesLabel;

    /* ----------------- */
    /* ----- FLAGS ----- */
    /* ----------------- */
    private final String FLAG_CLASSES_TO_LOAD = " --classes-to-load  ";
    private final String FLAG_PATTERNS_PER_CLASS = " --patterns-per-class ";
    private final String FLAG_STATES = " -hill-climber-states ";

    /* ---------------------------- */
    /* ------ PARAMETERS INFO ----- */
    /* ---------------------------- */
    private final String INFO_CLASSES_TO_LOAD = "How many symbols we want to " +
            "classify.";
    private final String INFO_PATTERNS_PER_CLASS = "How many words should " +
            "represent one class.";
    private final String INFO_STATES = "Number of states in target DFA.";

    /* ------------------------------------- */
    /* ----- PARAMETERS DEFAULT VALUES ----- */
    /* ------------------------------------- */
    private final String DEFAULT_CLASSES_TO_LOAD = "3";
    private final String DEFAULT_PATTERNS_PER_CLASS = "150";
    private final String DEFAULT_STATES = "50";


    /**
     * Sets default values for all Hill Climber related interface objects.
     */
    private void setDefaultValues() {
        classesToLoad.setText(DEFAULT_CLASSES_TO_LOAD);
        patternsPerClass.setText(DEFAULT_PATTERNS_PER_CLASS);
        states.setText(DEFAULT_STATES);
    }

    /**
     * Most of User Interface Objects has tooltip assign to them. This method
     * initializes tooltips and perform connection with elements.
     */
    private void setTooltips() {
        classesToLoad.setTooltip(Tooltips.generateTooltip(INFO_CLASSES_TO_LOAD));
        patternsPerClass.setTooltip(Tooltips.generateTooltip(INFO_PATTERNS_PER_CLASS));
        states.setTooltip(Tooltips.generateTooltip(INFO_STATES));
    }

    /**
     * Loads Pane from .fxml file and fixes node's default values and tooltips.
     */
    ComputationHillClimberControls() {
        FxmlLoader.loadFxml(this, "/hill_climber_config.fxml");
        setDefaultValues();
        setTooltips();
    }

    /**
     * @return String object based on provided flags and their values.
     * Properly appended, constitutes settings of Hill Climber computations.
     */
    @Override
    public String collectFlags() {
        return getClassesToLoadAsFlag() + getPatternsPerClassAsFlag() +
                getStatesAsFlag();
    }

    /**
     * @return Classes to load value preceded with appropriate flag.
     */
    private String getClassesToLoadAsFlag() {
        return FLAG_CLASSES_TO_LOAD + " " + classesToLoad.getText();
    }

    /**
     * @return Patterns per class value preceded with appropriate flag.
     */
    private String getPatternsPerClassAsFlag() {
        return FLAG_PATTERNS_PER_CLASS + " " + patternsPerClass.getText();
    }

    /**
     * @return States value preceded with appropriate flag.
     */
    private String getStatesAsFlag() {
        return FLAG_STATES + " " + states.getText();
    }
}

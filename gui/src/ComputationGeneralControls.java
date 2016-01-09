import javafx.fxml.FXML;
import javafx.scene.Parent;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.scene.text.TextFlow;
import javafx.stage.DirectoryChooser;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;

/**
 * Main program will be consistent and tight-knit, hence we will try to keep
 * every run-time method - either auxiliary or interface-element related,
 * in one file. Hope it will be the case.
 * <p></p>
 * Created by dybisz on 07.01.16.
 */
public class ComputationGeneralControls {
    /* ---------------------------------------- */
    /* ----- FXML OBJECTS - CORE SETTINGS ----- */
    /* ---------------------------------------- */
    @FXML
    Parent root;
    @FXML
    AnchorPane methodSpecificConfig;
    @FXML
    ComboBox<String> methodChoice;
    @FXML
    TextFlow infoArea;
    @FXML
    TextField executablePath;
    @FXML
    TextField logsDirPath;
    @FXML
    TextField nativeSrcPath;
    @FXML
    TextField foreignSrcPath;
    @FXML
    TextField maxIterations;
    @FXML
    TextField alphabetSize;

    @FXML
    void initialize() {
        initMethodChoiceBox();
        setTestingValues();
    }

    /* ------------------- */
    /* ----- METHODS ----- */
    /* ------------------- */

    private final String METHOD_1 = "PSO";
    private final String METHOD_2 = "Hill Climber";

    /* ------------------------------- */
    /* ----- METHODS INFORMATION ----- */
    /* ------------------------------- */
    private final String METHOD_1_ID = "0";
    private final String METHOD_2_ID = "1";
    private String METHOD_1_INFO = "__INFO__ to be done ...";
    private String METHOD_2_INFO = " Straigh forward method .. bla bla bla ...";

    /* ----------------- */
    /* ----- FLAGS ----- */
    /* ----------------- */
    private final String FLAG_EXPERIMENT = " --exp ";
    private final String FLAG_LOGS_DIR = " --log-main-dir ";
    private final String FLAG_NATIVE_SRC = " --cl-native-path ";
    private final String FLAG_FOREIGN_SRC = " --cl-foreign-path ";
    private final String FLAG_MAX_ITERATIONS = " --max-iter ";
    private final String FLAG_ALPHABET_SIZE = " --cl-alph-size ";

    /* ---------------------- */
    /* ----- EXPERIMENT ----- */
    /* ---------------------- */
    private String EXPERIMENT_ID = "";

    /* ------------------------------------ */
    /* ----- TERMINAL WINDOW SETTINGS ----- */
    /* ------------------------------------ */

    // Fields are not of 'final static' type on purpose:
    // they can be modified on the run to spawn multiple,
    // not overlapping terminal windows.
    private int TERMINAL_WINDOW_WIDTH = 93;
    private int TERMINAL_WINDOW_HEIGHT = 31;
    private int TERMINAL_SHIFT_HORIZONTAL = 100;
    private int TERMINAL_SHIFT_VERTICAL = 200;

    /* ---------------------------------- */
    /* ----- USER INTERFACE METHODS ----- */
    /* ---------------------------------- */

    /**
     * Although it is main method of the application - it is rather short.
     * First, it checks whether all application's settings are correctly set
     * and then it invokes {@link #executeComputationsCommand()}. In case of
     * not meeting the requirements of {@link #computationsConditionsMet()},
     * error is reported.
     */
    @FXML
    private void runComputations() {
        if (computationsConditionsMet()) {
            executeComputationsCommand();
        } else {
            System.out.println("__COMPUTATIONAL_CONDITIONS_ERROR__");
        }
    }

    /**
     * Invoked when 'browse' for the 'Executable' text field has been clicked.
     * It asks user to specify executable file and save path in
     * {@link #executablePath}
     */
    @FXML
    private void browseExecutable() {
        String executablePathValue = getPathFromDialog("Load Executable");
        executablePath.setText(executablePathValue);
    }

    /**
     * Invoked when 'browse' for the 'Logs Directory' text field has been clicked.
     * It asks user to specify executable file and save path in
     * {@link #logsDirPath}
     */
    @FXML
    private void browseLogs() {
        String logsDirPathValue = getDirectoryPathFromDialog("Specify Logs Directory");
        logsDirPath.setText(logsDirPathValue);
    }

    /**
     * Invoked when 'browse' for the 'Native Sources' text field has been clicked.
     * It asks user to specify executable file and save path in
     * {@link #nativeSrcPath}
     */
    @FXML
    private void browseNativesSrc() {
        String nativeSrcPathValue = getPathFromDialog("Load Native Source");
        nativeSrcPath.setText(nativeSrcPathValue);
    }

    /**
     * Invoked when 'browse' for the 'Foreign Sources' text field has been clicked.
     * It asks user to specify executable file and save path in
     * {@link #foreignSrcPath}
     */
    @FXML
    private void browseForeignSrc() {
        String foreignSrcPathValue = getPathFromDialog("Load Foreign Source");
        foreignSrcPath.setText(foreignSrcPathValue);
    }

    /* ------------------------------ */
    /* ------ AUXILIARY METHODS ----- */
    /* ------------------------------ */

    /**
     * Since ComboBox cannot be properly set via Scene Builder, one needs to
     * initialize everything by hand. Both, values on expandable list and
     * change listener have been defined in body of this method.
     */
    private void initMethodChoiceBox() {
        methodChoice.getItems().clear();
        methodChoice.getItems().addAll(METHOD_1, METHOD_2);
        methodChoice.valueProperty().addListener((obs, oldVal, newVal) -> {
            methodChoiceBoxValueChanged(newVal);
        });
    }

    /**
     * Sets default values for global settings.
     * IMPORTANT: This method will be switch to set default values coherent
     * with deployed application.
     */
    private void setTestingValues() {
        executablePath.setText("/home/dybisz/Repositories/BachelorThesis" +
                "/pattern_recognizer/bin/pattern_recognizer");
        logsDirPath.setText("/home/dybisz/Repositories/BachelorThesis" +
                "/pattern_recognizer/logs");
        nativeSrcPath.setText("/home/dybisz/Repositories/BachelorThesis" +
                "/pattern_recognizer/res/digits/Natives.xls");
        foreignSrcPath.setText("/home/dybisz/Repositories/BachelorThesis" +
                "/pattern_recognizer/res/digits/Foreign_90ccl.xls");
        maxIterations.setText("1000");
        alphabetSize.setText("12");
    }

    private boolean computationsConditionsMet() {
        boolean areConditionsMet = true;
        areConditionsMet = (EXPERIMENT_ID != "");
        return areConditionsMet;
    }

    /**
     * Collects information about flags and executes new Terminal process.
     * Any exceptions are catched and reported.
     */
    private void executeComputationsCommand() {
        try {
            String[] command = buildXTermCommandString();
            new ProcessBuilder(command).start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Methods calls appropriate procedures according to new value in
     * {@link #methodChoice}. All methods are listed at the beginning of
     * the class in METHODS section.
     *
     * @param newVal New value in {@link #methodChoice}.
     */
    private void methodChoiceBoxValueChanged(String newVal) {
        switch (newVal) {
            case METHOD_1:
                loadPSOInterface();
                EXPERIMENT_ID = METHOD_1_ID;
                break;
            case METHOD_2:
                loadHillClimberInterface();
                EXPERIMENT_ID = METHOD_2_ID;
                break;
        }
    }

    private void loadPSOInterface() {
        // LOAD INFO
        Label psoInfo = new Label(METHOD_1_INFO);
        psoInfo.setWrapText(true);
        infoArea.getChildren().removeAll(infoArea.getChildren());
        infoArea.getChildren().addAll(psoInfo);

        // Refresh content
        methodSpecificConfig.getChildren().removeAll(methodSpecificConfig.getChildren());
        methodSpecificConfig.getChildren().add(new ComputationPSOControls());
    }

    private void loadHillClimberInterface() {
        // Refresh content
        methodSpecificConfig.getChildren().removeAll(methodSpecificConfig.getChildren());
        methodSpecificConfig.getChildren().add(new ComputationHillClimberControls());
    }

    /**
     * Opens dialog window, which allows user to pick up a directory. As a result,
     * method returns String object with absolute path to chosen file or
     * empty one, when file was not picked.
     * IMPORTANT: There is no control over file's extension.
     *
     * @param header Text that will be displayed in window bar.
     * @return Absolute path to specified directory or an empty string when nothing
     * has been chosen.
     */
    private String getDirectoryPathFromDialog(String header) {
        DirectoryChooser directoryChooser = new DirectoryChooser();
        directoryChooser.setTitle(header);
        File file = directoryChooser.showDialog(getStage());
        return extractPathFromFile(file);
    }

    /**
     * Opens dialog window, which allows user to pick up a file. As a result,
     * method returns String object with absolute path to chosen file or
     * empty one, when file was not picked.
     * IMPORTANT: There is no control over file's extension.
     *
     * @param header Text that will be displayed in window bar.
     * @return Absolute path to specified file or an empty string when nothing
     * has been chosen.
     */
    private String getPathFromDialog(String header) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle(header);
        File file = fileChooser.showOpenDialog(getStage());
        return extractPathFromFile(file);
    }

    /**
     * If provided file is equal to null, returned String object will be empty.
     * In opposite case, it will contain an absolute path to a file.
     *
     * @param file File from, which one wants to obtain path.
     * @return Empty string or one containing an absolute path.
     */
    private String extractPathFromFile(File file) {
        String path = "";
        if (file == null) {
            return path;
        } else {
            return file.getAbsolutePath();
        }
    }

    private Stage getStage() {
        return (Stage) root.getScene().getWindow();
    }

    /**
     * Collects data from appropriate fields i.e.
     * {@link #TERMINAL_SHIFT_VERTICAL}, {@link #TERMINAL_SHIFT_HORIZONTAL},
     * {@link #TERMINAL_WINDOW_HEIGHT}, {@link #TERMINAL_WINDOW_WIDTH}
     * and concatenate string comprising a command, which opens up XTerm terminal
     * and runs pattern recognizer with proper flags.
     *
     * @return Constructed command in form of the string.
     */
    private String[] buildXTermCommandString() {
        String computationsCmd = buildComputationsCommand();
        String[] command = {"xterm", "-geometry", TERMINAL_WINDOW_WIDTH + "x" +
                TERMINAL_WINDOW_HEIGHT + "+" + TERMINAL_SHIFT_HORIZONTAL + "+" +
                TERMINAL_SHIFT_VERTICAL, "-hold", "-e", computationsCmd};
        return command;
    }

    /**
     * @return String object based on provided flags and their values.
     * It is formatted in a way that can be run as a terminal command.
     */
    private String buildComputationsCommand() {
        return executablePath.getText() + " " +
                FLAG_EXPERIMENT + EXPERIMENT_ID + " " + getLogsDirAsFlag() +
                getNativesSrcAsFlag() + getForeignSrcAsFlag() +
                getMaxIterationsAsFlag() + getAlphabetSizesAsFlag();
    }

    /**
     * @return Experiment ID value preceded with appropriate flag.
     */
    private String getExperimentIdAsFlag() {
        return FLAG_EXPERIMENT + " " + EXPERIMENT_ID;
    }

    /**
     * @return Logs directory value preceded with appropriate flag.
     */
    private String getLogsDirAsFlag() {
        return FLAG_LOGS_DIR + logsDirPath.getText();
    }

    /**
     * @return Native source value preceded with appropriate flag.
     */
    private String getNativesSrcAsFlag() {
        return FLAG_NATIVE_SRC + nativeSrcPath.getText();
    }

    /**
     * @return Foreign source value preceded with appropriate flag.
     */
    private String getForeignSrcAsFlag() {
        return FLAG_FOREIGN_SRC + foreignSrcPath.getText();
    }

    /**
     * @return Max iterations value preceded with appropriate flag.
     */
    private String getMaxIterationsAsFlag() {
        return FLAG_MAX_ITERATIONS + maxIterations.getText();
    }

    /**
     * @return Alphabet size value preceded with appropriate flag.
     */
    private String getAlphabetSizesAsFlag() {
        return FLAG_ALPHABET_SIZE + alphabetSize.getText();
    }
}

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import java.io.IOException;

public class ConfigurationPanel extends Application {


    private static final String WINDOW_FXML_URL = "window.fxml";
    private static final String WINDOW_NAME = "Pattern Recognizer Configuration";

    @Override
    public void start(Stage primaryStage) {
        Parent root = loadFxmlAsParent(WINDOW_FXML_URL);
        Scene scene = new Scene(root);
        primaryStage.setResizable(false);
        primaryStage.setTitle(WINDOW_NAME);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    /**
     * Loads .fxml file into Parent object.
     *
     * @param fxmlURL usually "/<name>.fxml", when .fxml file is in ./resources dir.
     * @return Parent object with features loaded from .fxml
     */
    Parent loadFxmlAsParent(String fxmlURL) {
        Parent parent = null;
        try {
            parent = FXMLLoader.load(getClass().getResource(fxmlURL));
        } catch (IOException e) {
            System.out.println("WYJEBALO");
            e.printStackTrace();
        }
        return parent;
    }

    public static void main(String[] args) {
        launch(args);
    }
}

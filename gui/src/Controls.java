import javafx.event.ActionEvent;
import javafx.fxml.FXML;


import java.awt.event.KeyEvent;
import java.io.IOException;
import java.io.OutputStream;

/**
 * Created by dybisz on 07.01.16.
 */
public class Controls {


    @FXML
    private void test(ActionEvent ke) {
        try {
            String[] command = { "xterm"};
            Process proc = new ProcessBuilder(command).start();
//
//
//            OutputStream out = proc.getOutputStream();
//
//            out.write("sh -c ls".getBytes());
//            out.flush();
//            out.close();

            Runtime.getRuntime().exec("ls");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}

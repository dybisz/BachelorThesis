import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.ReadOnlyDoubleProperty;
import javafx.util.Duration;

/**
 * Created by dybisz on 10.01.16.
 */
public abstract class Animations {


    public static void changeValue(ReadOnlyDoubleProperty readOnlyDoubleProperty, double v) {

    }

    public static void fadeIn(DoubleProperty opacity, double time) {
        opacity.set(0);
        Timeline t = new Timeline();
        t.setAutoReverse(false);
        KeyValue kv = new KeyValue(opacity, 1);
        final KeyFrame kf = new KeyFrame(Duration.millis(time), kv);
        t.getKeyFrames().add(kf);
        t.play();
    }
}

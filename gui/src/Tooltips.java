import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.control.Tooltip;
import javafx.util.Duration;

import java.lang.reflect.Field;

/**
 * Created by dybisz on 10.01.16.
 */
public abstract class Tooltips {

    public static final Tooltip generateTooltip(String text) {
        final Tooltip tooltip = new Tooltip();
        tooltip.setText(text);
        hackTooltipStartTiming(tooltip);
        return tooltip;
    }

    public static void hackTooltipStartTiming(Tooltip tooltip) {
        try {
            Field fieldBehavior = tooltip.getClass().getDeclaredField("BEHAVIOR");
            fieldBehavior.setAccessible(true);
            Object objBehavior = fieldBehavior.get(tooltip);

            Field fieldTimer = objBehavior.getClass().getDeclaredField("activationTimer");
            fieldTimer.setAccessible(true);
            Timeline objTimer = (Timeline) fieldTimer.get(objBehavior);

            objTimer.getKeyFrames().clear();
            objTimer.getKeyFrames().add(new KeyFrame(new Duration(10)));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

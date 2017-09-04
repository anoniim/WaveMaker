package net.solvetheriddle.wavemaker;

import android.annotation.SuppressLint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.DragEvent;
import android.view.MotionEvent;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getCanonicalName();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private SeekBar frequencyBar;
    private TextView frequencyText;
    private View.OnTouchListener onTouchListener;

    private native void touchEvent(int action);

    private native void startEngine();

    private native void stopEngine();

    private native void setFrequency(double frequency);

    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        frequencyText = findViewById(R.id.frequency_text);
        onTouchListener = new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                int motionEventAction = motionEvent.getAction();
                touchEvent(motionEventAction);
                return true;
            }
        };
        frequencyText.setOnTouchListener(onTouchListener);
        frequencyBar = findViewById(R.id.frequencyBar);
        frequencyBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                setFrequency(i);
                setFrequencyText(i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        setFrequencyText(frequencyBar.getProgress());

        startEngine();
    }

    private void setFrequencyText(int i) {
        frequencyText.setText(String.format(getString(R.string.tap_anywhere), i));
    }

    @Override
    public void onDestroy() {
        stopEngine();
        super.onDestroy();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}

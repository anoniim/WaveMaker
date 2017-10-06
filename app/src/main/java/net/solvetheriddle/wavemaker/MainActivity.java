package net.solvetheriddle.wavemaker;

import android.annotation.SuppressLint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

import com.jjoe64.graphview.GraphView;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getCanonicalName();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private static TextView audioDataText;
    private SeekBar aFrequencyBar;
    private TextView aFrequencyText;
    private SeekBar aAmplitudeBar;
    private TextView aAmplitudeText;
    private SeekBar bFrequencyBar;
    private TextView bAmplitudeText;
    private SeekBar bAmplitudeBar;
    private TextView bFrequencyText;
    private GraphView graph;
    private Switch soundLockSwitch;

    private native void touchEvent(int action);

    private native void startEngine();

    private native void stopEngine();

    private native void setFrequencyA(double frequency);

    private native void setAmplitudeA(double amplitude);

    private native void setFrequencyB(double frequency);

    private native void setAmplitudeB(double amplitude);

    private native void initCallback();


    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        audioDataText = findViewById(R.id.audio_data_text);
        soundLockSwitch = findViewById(R.id.sound_lock_switch);
        aAmplitudeText = findViewById(R.id.a_amplitude_text);
        aFrequencyText = findViewById(R.id.a_frequency_text);
        bAmplitudeText = findViewById(R.id.b_amplitude_text);
        bFrequencyText = findViewById(R.id.b_frequency_text);

        View.OnTouchListener onTouchListener = (view, motionEvent) -> {
            int motionEventAction = motionEvent.getAction();
            if (soundLockSwitch.isChecked()) {
                // Reverse the function of the Play button
                motionEventAction = Math.abs(motionEventAction - 1);
            }
            touchEvent(motionEventAction);
            return true;
        };
        audioDataText.setOnTouchListener(onTouchListener);
//        soundLockSwitch.setOnCheckedChangeListener((compoundButton, b) -> );

        aFrequencyBar = findViewById(R.id.a_frequency_bar);
        aFrequencyBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                setFrequencyA(i);
                setAFrequencyText(i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        aAmplitudeBar = findViewById(R.id.a_amplitude_bar);
        aAmplitudeBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                double amplitude = progressToDouble(i);
                setAmplitudeA(amplitude);
                setAAmplitudeText(amplitude);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        bFrequencyBar = findViewById(R.id.b_frequency_bar);
        bFrequencyBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                setFrequencyB(i);
                setBFrequencyText(i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        bAmplitudeBar = findViewById(R.id.b_amplitude_bar);
        bAmplitudeBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                double amplitude = progressToDouble(i);
                setAmplitudeB(amplitude);
                setBAmplitudeText(amplitude);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        setAFrequencyText(getProgress(aFrequencyBar));
        setAAmplitudeText(getAmplitudeProgress(aAmplitudeBar));
        setBFrequencyText(getProgress(bFrequencyBar));
        setBAmplitudeText(getAmplitudeProgress(bAmplitudeBar));

        graph = findViewById(R.id.graph);

        initCallback();
        startEngine();
    }

    private int getProgress(SeekBar seekBar) {
        return seekBar.getProgress();
    }

    private double getAmplitudeProgress(SeekBar amplitudeBar) {
        return progressToDouble(getProgress(amplitudeBar));
    }

    private double progressToDouble(int progress) {
        return ((double) progress) / 10;
    }

    private void setAFrequencyText(int i) {
        aFrequencyText.setText(String.valueOf(i));
    }

    private void setAAmplitudeText(double i) {
        aAmplitudeText.setText(String.valueOf(i));
    }

    private void setBFrequencyText(int i) {
        bFrequencyText.setText(String.valueOf(i));
    }

    private void setBAmplitudeText(double i) {
        bAmplitudeText.setText(String.valueOf(i));
    }

    public static void OnRender(float[] data) {


//        for (int y = 0; y<data.length; y++){
//            // FIXME This is overriding y value for each array of new values
//            DataPoint dataPoint = new DataPoint(data[y], y);
//            graph.addSeries(new LineGraphSeries(dataPoint));
//        }

        if (data == null) {
            Log.wtf("JAVA", "null but works");
        }
        Log.wtf("JAVA", String.valueOf(data[0]));

//        runOnUiThread(() -> audioDataText.setText(String.valueOf(data[0])));

//        runOnUiThread(() -> audioDataText.setText(String.valueOf(data)));
    }

    public static void setText(String message) {
        audioDataText.setText(String.valueOf(message));
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

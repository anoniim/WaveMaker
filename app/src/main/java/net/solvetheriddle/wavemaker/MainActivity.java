package net.solvetheriddle.wavemaker;

import android.annotation.SuppressLint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.DataPointInterface;
import com.jjoe64.graphview.series.LineGraphSeries;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getCanonicalName();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private SeekBar frequencyBar;
    private SeekBar amplitudeBar;
    private TextView frequencyText;
    private static TextView audioDataText;
    private TextView amplitudeText;
    private GraphView graph;

    private native void touchEvent(int action);

    private native void startEngine();

    private native void stopEngine();

    private native void setFrequency(double frequency);

    private native void setAmplitude(double amplitude);

    private native void initCallback();


    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        audioDataText = findViewById(R.id.audio_data_text);
        amplitudeText = findViewById(R.id.amplitude_text);
        frequencyText = findViewById(R.id.frequency_text);

        View.OnTouchListener onTouchListener = new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                int motionEventAction = motionEvent.getAction();
                touchEvent(motionEventAction);



                return true;
            }
        };
        audioDataText.setOnTouchListener(onTouchListener);

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

        amplitudeBar = findViewById(R.id.amplitudeBar);
        amplitudeBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                double amplitude = progressToDouble(i);
                setAmplitude(amplitude);
                setAmplitudeText(amplitude);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        setFrequencyText(getFrequencyProgress());
        setAmplitudeText(getAmplitudeProgress());

        graph = findViewById(R.id.graph);

        initCallback();
        startEngine();
    }

    private int getFrequencyProgress() {
        return frequencyBar.getProgress();
    }

    private double getAmplitudeProgress() {
        return progressToDouble(amplitudeBar.getProgress());
    }

    private double progressToDouble(int progress) {
        return ((double) progress) / 10;
    }

    public void setAudioDataText(float data) {

//        for (int y = 0; y<data.length; y++){
//            // FIXME This is overriding y value for each array of new values
//            DataPoint dataPoint = new DataPoint(data[y], y);
//            graph.addSeries(new LineGraphSeries(dataPoint));
//        }

//        runOnUiThread(() -> audioDataText.setText(String.valueOf(data[0])));

        runOnUiThread(() -> audioDataText.setText(String.valueOf(data)));
    }

    private void setFrequencyText(int i) {
        frequencyText.setText(String.valueOf(i));
    }

    private void setAmplitudeText(double i) {
        amplitudeText.setText(String.valueOf(i));
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

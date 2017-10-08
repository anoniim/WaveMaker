package net.solvetheriddle.wavemaker;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.widget.SeekBar;
import android.widget.Switch;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;
import com.jjoe64.graphview.series.Series;

import net.solvetheriddle.wavemaker.di.component.DaggerHarmonicStructureComponent;
import net.solvetheriddle.wavemaker.di.module.HarmonicStructureModule;

import java.util.List;

import butterknife.BindView;
import butterknife.BindViews;
import butterknife.ButterKnife;
import butterknife.OnTouch;

public class HarmonicStructureActivity extends AppCompatActivity
        implements HarmonicStructureScreen.View {

    private static final String TAG = HarmonicStructureActivity.class.getCanonicalName();

    private AudioEngine audioEngine;
    private AmplitudeChangeListener amplitudeChangeListener = new AmplitudeChangeListener();

    @BindView(R.id.graph)
    GraphView graph;
    @BindViews({R.id.amp_bar_fundamental,
            R.id.amp_bar_2x,
            R.id.amp_bar_3x,
            R.id.amp_bar_4x,
            R.id.amp_bar_5x,
            R.id.amp_bar_6x,
            R.id.amp_bar_7x,
            R.id.amp_bar_8x})
    List<SeekBar> amplitudeBars;
    //    @BindView(R.id.play_button)
//    Button playButton;
    @BindView(R.id.play_lock_switch)
    Switch playLockSwitch;

    final ButterKnife.Action<SeekBar> SET_PROGRESS_LISTENER
            = (view, index) -> view.setOnSeekBarChangeListener(amplitudeChangeListener);
    private Double amplitudeFundamental = 1d;
    private Double amplitude2x = 0d;
    private Double amplitude3x = 0d;
    private Double amplitude4x = 0d;
    private Double amplitude5x = 0d;
    private Double amplitude6x = 0d;
    private Double amplitude7x = 0d;
    private Double amplitude8x = 0d;
    public static final double SECOND_IN_MILLIS = 1000d;
    public static final int MILLISECOND_SCALE = 10;
    public static final int CYCLES_PER_X = 2;
    public static final int STEP_OFFSET = 5;
    public static final int DEFAULT_FREQUENCY = 220;
    private int numOfSteps;

    public static Intent getCallingIntent(Context context) {
        return new Intent(context, HarmonicStructureActivity.class);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        SoundMakerApplication application = (SoundMakerApplication) getApplication();
        DaggerHarmonicStructureComponent.builder()
                .appComponent(application.getAppComponent())
                .harmonicStructureModule(new HarmonicStructureModule(this))
                .build();

        setContentView(R.layout.activity_harmonic_structure);
        ButterKnife.bind(this);
        ButterKnife.apply(amplitudeBars, SET_PROGRESS_LISTENER);

        audioEngine = new AudioEngine();
        audioEngine.initCallback();

        amplitudeFundamental = 1d;

        Double cycleInMillis = Math.round((SECOND_IN_MILLIS / DEFAULT_FREQUENCY) * 100d) / 100d;
        int stepsForOneCycle = cycleInMillis.intValue() * MILLISECOND_SCALE;
        numOfSteps = (stepsForOneCycle * CYCLES_PER_X) + STEP_OFFSET;

        DataPoint[] dataPoints = calculateDataPoints(SECOND_IN_MILLIS, MILLISECOND_SCALE, DEFAULT_FREQUENCY, numOfSteps);

        Series harmonicsGraphSeries = new LineGraphSeries<>(dataPoints);
        graph.addSeries(harmonicsGraphSeries);


        graph.getViewport().setScrollable(true);
        graph.getViewport().setScalable(true);
        graph.getViewport().setScalableY(true);
        // set manual X bounds
        graph.getViewport().setXAxisBoundsManual(true);
        graph.getViewport().setMinX(0.0);
        graph.getViewport().setMaxX(cycleInMillis);
        graph.getViewport().setYAxisBoundsManual(true);
        graph.getViewport().setMinY(-2.0);
        graph.getViewport().setMaxY(2.0);

    }

    @NonNull
    private DataPoint[] calculateDataPoints(double secondInMillis, int millisecondScale, int frequency, int numOfSteps) {
        DataPoint[] dataPoints = new DataPoint[numOfSteps];
        Double[] amplitudes = new Double[] {amplitudeFundamental, amplitude2x, amplitude3x,
                amplitude3x, amplitude4x, amplitude5x, amplitude6x, amplitude7x, amplitude8x};
        for (int step = 0; step < numOfSteps; step++) {
            // x = millisecond steps
            double x = step / (secondInMillis * millisecondScale);
            // y = sample value
            double y = getY(frequency, amplitudes, x);
            double yStep = roundDouble(y);
            double xStep = roundDouble(x * secondInMillis);
            dataPoints[step] = new DataPoint(xStep, yStep);
        }
        return dataPoints;
    }

    private double getY(int frequency, Double[] amplitudes, double x) {
        double y = 0;
        // Sum of amplitudes of all frequencies
        for (int i = 1; i <= amplitudes.length; i++) {
            y += amplitudes[i-1] * Math.sin(2 * Math.PI * frequency * i * x);
        }
        return y;
    }

    private double roundDouble(double value) {
        return Math.round(value * 1000d) / 1000d;
    }

    @Override
    protected void onStart() {
        super.onStart();
        audioEngine.startEngine();
    }

    @Override
    public void onStop() {
        audioEngine.stopEngine();
        super.onStop();
    }

    @OnTouch(R.id.play_button)
    boolean onPlayButtonTouch(MotionEvent motionEvent) {
        int motionEventAction = motionEvent.getAction();
        if (playLockSwitch.isChecked()) {
            // Reverse the function of the Play button
            motionEventAction = Math.abs(motionEventAction - 1);
        }
        audioEngine.onPlayTouch(motionEventAction);

//            switch (motionEvent.getAction()) {
//                case MotionEvent.ACTION_DOWN:
//
//                    break;
//                case MotionEvent.ACTION_UP:
////                    view.performClick();
//                    break;
//                default:
//                    // ignore
//                    break;
//            }
        return false;
    }

    private class AmplitudeChangeListener implements SeekBar.OnSeekBarChangeListener {
        @Override
        public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
            double amplitude = amplitudeProgress(i);
            switch (seekBar.getId()) {
                case R.id.amp_bar_fundamental:
                    audioEngine.setAmpFundamental(amplitude);
                    amplitudeFundamental = amplitude;
                    break;
                case R.id.amp_bar_2x:
                    audioEngine.setAmp2x(amplitude);
                    amplitude2x = amplitude;
                    break;
                case R.id.amp_bar_3x:
                    audioEngine.setAmp3x(amplitude);
                    amplitude3x = amplitude;
                    break;
                case R.id.amp_bar_4x:
                    audioEngine.setAmp4x(amplitude);
                    amplitude4x = amplitude;
                    break;
                case R.id.amp_bar_5x:
                    audioEngine.setAmp5x(amplitude);
                    amplitude5x = amplitude;
                    break;
                case R.id.amp_bar_6x:
                    audioEngine.setAmp6x(amplitude);
                    amplitude6x = amplitude;
                    break;
                case R.id.amp_bar_7x:
                    audioEngine.setAmp7x(amplitude);
                    amplitude7x = amplitude;
                    break;
                case R.id.amp_bar_8x:
                    audioEngine.setAmp8x(amplitude);
                    amplitude8x = amplitude;
                    break;
            }
            recalculateGraph();
        }

        private double amplitudeProgress(int progress) {
            return ((double) progress) / 100;
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {

        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {

        }
    }

    private void recalculateGraph() {
        DataPoint[] dataPoints = calculateDataPoints(SECOND_IN_MILLIS, MILLISECOND_SCALE, DEFAULT_FREQUENCY, numOfSteps);
        Series harmonicsGraphSeries = new LineGraphSeries<>(dataPoints);
        graph.removeAllSeries();
        graph.addSeries(harmonicsGraphSeries);
    }
}

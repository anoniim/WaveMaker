package net.solvetheriddle.wavemaker;

import android.util.Log;

public class AudioEngine {

    static {
        System.loadLibrary("native-lib");
    }

    public native void initCallback();

    public native void startEngine();

    public native void stopEngine();

    public native void onPlayTouch(int action);

    public native void setAmpFundamental(double amplitude);

    public native void setAmp2x(double amplitude);

    public native void setAmp3x(double amplitude);

    public native void setAmp4x(double amplitude);

    public native void setAmp5x(double amplitude);

    public native void setAmp6x(double amplitude);

    public native void setAmp7x(double amplitude);

    public native void setAmp8x(double amplitude);

//    /**
//     * A native method that is implemented by the 'native-lib' native library,
//     * which is packaged with this application.
//     */
//    public native String stringFromJNI();


    public static void setText(String message) {
//        audioDataText.setText(String.valueOf(message));
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
}

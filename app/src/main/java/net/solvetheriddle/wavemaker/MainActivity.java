package net.solvetheriddle.wavemaker;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import net.solvetheriddle.wavemaker.R;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getCanonicalName();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.craft_new_button).setOnClickListener((View)->openCraftNewActivity());
    }

    private void openCraftNewActivity() {
        startActivity(CraftNewActivity.getCallingIntent(this));
    }
}

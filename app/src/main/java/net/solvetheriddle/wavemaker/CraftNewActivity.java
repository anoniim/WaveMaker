package net.solvetheriddle.wavemaker;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

public class CraftNewActivity extends AppCompatActivity {

    public static Intent getCallingIntent(Context context) {
        return new Intent(context, CraftNewActivity.class);
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_craft_new);
        findViewById(R.id.harmonic_structure_button).setOnClickListener((View)->openHarmonicStructureActivity());
    }

    private void openHarmonicStructureActivity() {
        startActivity(HarmonicStructureActivity.getCallingIntent(this));
    }
}

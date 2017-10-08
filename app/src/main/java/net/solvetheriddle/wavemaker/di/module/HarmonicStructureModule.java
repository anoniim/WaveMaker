package net.solvetheriddle.wavemaker.di.module;

import net.solvetheriddle.wavemaker.HarmonicStructureActivity;
import net.solvetheriddle.wavemaker.HarmonicStructureScreen;

import javax.inject.Singleton;

import dagger.Module;
import dagger.Provides;

@Module
public class HarmonicStructureModule {

    private HarmonicStructureActivity activity;

    public HarmonicStructureModule(HarmonicStructureActivity activity) {
        this.activity = activity;
    }

    @Provides
    @Singleton
    HarmonicStructureScreen.View provideHarmonicStructureView(){
        return activity;
    }
}

package net.solvetheriddle.wavemaker.di.module;

import android.content.Context;

import net.solvetheriddle.wavemaker.SoundMakerApplication;

import javax.inject.Named;
import javax.inject.Singleton;

import dagger.Component;
import dagger.Module;
import dagger.Provides;

@Module
public class AppModule {

    private SoundMakerApplication application;

    public AppModule(SoundMakerApplication soundMakerApplication) {
        application = soundMakerApplication;
    }

    @Provides
    @Singleton
    SoundMakerApplication provideApplication() {
        return application;
    }

    @Provides
    @Singleton
    @Named("application")
    Context provideContext() {
        return application;
    }
}

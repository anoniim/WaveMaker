package net.solvetheriddle.wavemaker.di.component;

import android.content.Context;

import net.solvetheriddle.wavemaker.SoundMakerApplication;
import net.solvetheriddle.wavemaker.di.module.AppModule;

import javax.inject.Named;
import javax.inject.Singleton;

import dagger.Component;

@Singleton
@Component(modules = {AppModule.class})
public interface AppComponent {

    void inject(SoundMakerApplication application);

    @Named("application")
    Context getContext();
}

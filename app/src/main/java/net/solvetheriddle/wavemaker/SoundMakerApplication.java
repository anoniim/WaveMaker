package net.solvetheriddle.wavemaker;

import android.app.Application;

import net.solvetheriddle.wavemaker.di.component.AppComponent;
import net.solvetheriddle.wavemaker.di.component.DaggerAppComponent;
import net.solvetheriddle.wavemaker.di.module.AppModule;

public class SoundMakerApplication extends Application {

    AppComponent mAppComponent;

    @Override
    public void onCreate() {
        super.onCreate();

        mAppComponent = DaggerAppComponent.builder()
                .appModule(new AppModule(this))
                .build();
        mAppComponent.inject(this);
    }

    public AppComponent getAppComponent() {
        return mAppComponent;
    }
}

package net.solvetheriddle.wavemaker.di.component;

import android.app.Activity;

import net.solvetheriddle.wavemaker.HarmonicStructureActivity;
import net.solvetheriddle.wavemaker.di.module.HarmonicStructureModule;
import net.solvetheriddle.wavemaker.di.scope.PerActivity;

import javax.inject.Named;
import javax.inject.Singleton;

import dagger.Component;

@PerActivity
@Component(dependencies = AppComponent.class, modules = HarmonicStructureModule.class)
public interface HarmonicStructureComponent {

    void inject(HarmonicStructureActivity activity);

//    @Named("activity")
//    Activity getContext();
}

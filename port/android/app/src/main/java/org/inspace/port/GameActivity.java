package org.inspace.port;

import org.libsdl.app.SDLActivity;

/** The game: SDL3 and the port (libinspace.so), which does everything else in C. */
public class GameActivity extends SDLActivity {
    @Override
    protected String[] getLibraries() {
        return new String[] {"SDL3", "inspace"};
    }
}

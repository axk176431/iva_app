package com.example.iva.Database;

import android.database.Cursor;
import android.database.CursorWrapper;

import java.util.UUID;

import static com.example.iva.Database.PreferencesDbSchema.*;

public class PreferencesCursorWrapper extends CursorWrapper {

    /**
     * Creates a cursor wrapper.
     *
     * @param cursor The underlying cursor to wrap.
     */
    public PreferencesCursorWrapper(Cursor cursor) {
        super(cursor);
    }

    public Preferences getPreferences() {
        String uuidString = getString(getColumnIndex(PreferencesTable.Cols.UUID));
        float learningRate = getFloat(getColumnIndex(PreferencesTable.Cols.LEARNING_RATE));
        float normalizationFactor = getFloat(getColumnIndex(
                PreferencesTable.Cols.NORMALIZATION_FACTOR));
        return new Preferences.Builder()
                .withId(UUID.fromString(uuidString))
                .withLearningRate(learningRate)
                .withNormalizationFactor(normalizationFactor)
                .build();
    }
}

package com.example.iva.Database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

import static com.example.iva.Database.PreferencesDbSchema.*;

public class PreferencesLab {

    private static PreferencesLab sPreferencesLab;

    private Context mContext;
    private SQLiteDatabase mDatabase;

    private Preferences preferences = Preferences.DEFAULT;

    public static PreferencesLab get(Context context) {
        if (sPreferencesLab == null) {
            sPreferencesLab = new PreferencesLab(context);
        }
        return sPreferencesLab;
    }

    private PreferencesLab(Context context) {
        mContext = context;
        mDatabase = new PreferencesBaseHelper(mContext).getWritableDatabase();
        loadPreferences();
    }

    public void updatePreferences(final Preferences preferences) {
        this.preferences = preferences;

        // clear database table and insert new preferences
        ContentValues values = getContentValues(preferences);
        mDatabase.beginTransaction();
        try {
            mDatabase.delete(PreferencesTable.NAME, null, null);
            mDatabase.insert(PreferencesTable.NAME, null, values);
            mDatabase.setTransactionSuccessful();
        } finally {
            mDatabase.endTransaction();
        }
    }

    private static ContentValues getContentValues(Preferences preferences) {
        ContentValues values = new ContentValues();
        values.put(PreferencesTable.Cols.UUID, preferences.id.toString());
        values.put(PreferencesTable.Cols.LEARNING_RATE, preferences.learningRate);
        values.put(PreferencesTable.Cols.NORMALIZATION_FACTOR, preferences.normalizationFactor);
        return values;
    }

    private PreferencesCursorWrapper queryPreferences() {
        Cursor cursor = mDatabase.query(
                PreferencesTable.NAME,
                null,
                null,
                null,
                null,
                null,
                null
        );
        return new PreferencesCursorWrapper(cursor);
    }

    private void loadPreferences() {
        try (PreferencesCursorWrapper cursor = queryPreferences()) {
            cursor.moveToFirst();
            if (!cursor.isAfterLast()) {
                this.preferences = cursor.getPreferences();
            }
        }
    }

    public Preferences getPreferences() {
        return preferences;
    }
}

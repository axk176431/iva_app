package com.example.iva.Database;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import androidx.annotation.Nullable;

import static com.example.iva.Database.PreferencesDbSchema.*;

public class PreferencesBaseHelper extends SQLiteOpenHelper {

    private static final int VERSION = 1;
    private static final String DATABASE_NAME = "doa_preferences.db";

    public PreferencesBaseHelper(@Nullable Context context) {
        super(context, DATABASE_NAME, null, VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("create table " + PreferencesTable.NAME + "(" +
                "_id integer primary key autoincrement, " +
                PreferencesTable.Cols.UUID + ", " +
                PreferencesTable.Cols.FRAME_SIZE + ", " +
                PreferencesTable.Cols.HOP_SIZE + ", " +
                PreferencesTable.Cols.LEARNING_RATE + ", " +
                PreferencesTable.Cols.NORMALIZATION_FACTOR + ", " +
                PreferencesTable.Cols.PCA_SMOOTHING_FACTOR + ")"
        );
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // do nothing
    }
}

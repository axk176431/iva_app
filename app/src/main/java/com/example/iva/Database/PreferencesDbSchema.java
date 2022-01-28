package com.example.iva.Database;

public class PreferencesDbSchema {

    public static final class PreferencesTable {
        public static final String NAME = "preferences";

        public static final class Cols {
            public static final String UUID = "uuid";
            public static final String LEARNING_RATE = "learningRate";
            public static final String NORMALIZATION_FACTOR = "normalizationFactor";
        }
    }
}

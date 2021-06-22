package com.example.iva.Database;

public class PreferencesDbSchema {

    public static final class PreferencesTable {
        public static final String NAME = "preferences";

        public static final class Cols {
            public static final String UUID = "uuid";
            public static final String FRAME_SIZE = "frameSize";
            public static final String HOP_SIZE = "hopSize";
            public static final String LEARNING_RATE = "learningRate";
            public static final String NORMALIZATION_FACTOR = "normalizationFactor";
            public static final String PCA_SMOOTHING_FACTOR = "pcaSmoothingFactor";
        }
    }
}

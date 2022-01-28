package com.example.iva.Database;

import java.util.UUID;

public class Preferences {

    public final UUID id;
    public final float learningRate;
    public final float normalizationFactor;

    private Preferences(final float learningRate, final float normalizationFactor) {
        this.id = UUID.randomUUID();
        this.learningRate = learningRate;
        this.normalizationFactor = normalizationFactor;
    }

    public static final Preferences DEFAULT = new Builder().build();

    public static class Builder {

        private UUID id = UUID.randomUUID();
        private float learningRate = 0.1f;
        private float normalizationFactor = 0.5f;

        public Builder withId(final UUID id) {
            this.id = id;
            return this;
        }

        public Builder withLearningRate(float learningRate) {
            this.learningRate = learningRate;
            return this;
        }

        public Builder withNormalizationFactor(float normalizationFactor) {
            this.normalizationFactor = normalizationFactor;
            return this;
        }

        public Preferences build() {
            return new Preferences(learningRate, normalizationFactor);
        }
    }
}

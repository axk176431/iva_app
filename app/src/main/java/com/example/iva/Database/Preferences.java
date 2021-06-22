package com.example.iva.Database;

import java.util.UUID;

public class Preferences {

    public final UUID id;
    public final int frameSize;
    public final int hopSize;
    public final float learningRate;
    public final float normalizationFactor;
    public final float pcaSmoothingFactor;

    private Preferences(final int frameSize,
                        final int hopSize,
                        final float learningRate,
                        final float normalizationFactor,
                        final float pcaSmoothingFactor) {
        this.id = UUID.randomUUID();
        this.frameSize = frameSize;
        this.hopSize = hopSize;
        this.learningRate = learningRate;
        this.normalizationFactor = normalizationFactor;
        this.pcaSmoothingFactor = pcaSmoothingFactor;
    }

    public static final Preferences DEFAULT = new Builder().build();

    public static class Builder {

        private UUID id = UUID.randomUUID();
        private int frameSize = 512;
        private int hopSize = 128;
        private float learningRate = 0.1f;
        private float normalizationFactor = 0.5f;
        private float pcaSmoothingFactor = 0.995f;

        public Builder withId(final UUID id) {
            this.id = id;
            return this;
        }

        public Builder withFrameSize(int frameSize) {
            this.frameSize = frameSize;
            return this;
        }

        public Builder withHopSize(int hopSize) {
            this.hopSize = hopSize;
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

        public Builder withPCASmoothingFactor(float pcaSmoothingFactor) {
            this.pcaSmoothingFactor = pcaSmoothingFactor;
            return this;
        }

        public Preferences build() {
            return new Preferences(frameSize,
                                   hopSize,
                                   learningRate,
                                   normalizationFactor,
                                   pcaSmoothingFactor);
        }
    }
}

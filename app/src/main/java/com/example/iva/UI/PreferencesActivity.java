package com.example.iva.UI;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.example.iva.R;
import com.example.iva.Database.Preferences;
import com.example.iva.Database.PreferencesLab;

import java.util.Locale;

public class PreferencesActivity extends AppCompatActivity {

    private Button mDefaultButton;
    private Button mApplyButton;
    private Button mCancelButton;

    private EditText mFrameSizeEdit;
    private EditText mHopSizeEdit;
    private EditText mLearningRateEdit;
    private EditText mNormalizationFactor;
    private EditText mPCASmoothingFactor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_preferences);

        mDefaultButton = findViewById(R.id.default_button);
        mDefaultButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                setDefaultPreferences();
            }
        });

        mApplyButton = findViewById(R.id.apply_button);
        mApplyButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                updatePreferences();
            }
        });

        mCancelButton = findViewById(R.id.cancel_button);
        mCancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PreferencesActivity.this.finish();
            }
        });

        mFrameSizeEdit = findViewById(R.id.frame_size_edit);
        mHopSizeEdit = findViewById(R.id.hop_size_edit);
        mLearningRateEdit = findViewById(R.id.learning_rate_edit);
        mNormalizationFactor = findViewById(R.id.normalization_factor_edit);
        mPCASmoothingFactor = findViewById(R.id.pca_smoothing_factor_edit);

        PreferencesLab preferencesLab = PreferencesLab.get(this);
        Preferences preferences = preferencesLab.getPreferences();
        setPreferencesText(preferences);
    }

    private void setPreferencesText(Preferences preferences) {
        mFrameSizeEdit.setText(String.format(Locale.US,"%d", preferences.frameSize));
        mHopSizeEdit.setText(String.format(Locale.US, "%d", preferences.hopSize));
        mLearningRateEdit.setText(String.format(Locale.US, "%.4f", preferences.learningRate));
        mNormalizationFactor.setText(String.format(Locale.US, "%.4f",
                preferences.normalizationFactor));
        mPCASmoothingFactor.setText(String.format(Locale.US,"%.4f",
                preferences.pcaSmoothingFactor));
    }

    private void setDefaultPreferences() {
        PreferencesLab preferencesLab = PreferencesLab.get(this);
        preferencesLab.updatePreferences(Preferences.DEFAULT);
        Preferences preferences = preferencesLab.getPreferences();
        setPreferencesText(preferences);
    }

    private void updatePreferences() {
        boolean valid = true;
        int frameSize = 0, hopSize = 0;
        float learningRate = 0, normalizationFactor = 0, pcaSmoothingFactor = 0;

        try {
            frameSize = Integer.parseInt(mFrameSizeEdit.getText().toString());
            if (frameSize <= 64 || frameSize > 16000) {
                mFrameSizeEdit.setError(getString(R.string.frame_size_validation));
                valid = false;
            }
        } catch (NumberFormatException nfe) {
            mFrameSizeEdit.setError(getString(R.string.frame_size_validation));
            valid = false;
        }

        try {
            hopSize = Integer.parseInt(mHopSizeEdit.getText().toString());
            if (hopSize < frameSize / 4 || hopSize > frameSize / 2) {
                mHopSizeEdit.setError(getString(R.string.hop_size_validation));
                valid = false;
            }
        } catch (NumberFormatException nfe) {
            mHopSizeEdit.setError(getString(R.string.hop_size_validation));
            valid = false;
        }

        try {
            learningRate = Float.parseFloat(mLearningRateEdit.getText().toString());
            if (learningRate <= 0 || learningRate > 1) {
                mLearningRateEdit.setError(getString(R.string.learning_rate_validation));
                valid = false;
            }
        } catch (NumberFormatException nfe) {
            mLearningRateEdit.setError(getString(R.string.learning_rate_validation));
            valid = false;
        }

        try {
            normalizationFactor = Float.parseFloat(mNormalizationFactor.getText().toString());
            if (normalizationFactor < 0 || normalizationFactor > 1) {
                mNormalizationFactor.setError(getString(R.string.normalization_factor_validation));
                valid = false;
            }
        } catch (NumberFormatException nfe) {
            mNormalizationFactor.setError(getString(R.string.normalization_factor_validation));
            valid = false;
        }

        try {
            pcaSmoothingFactor = Float.parseFloat(mPCASmoothingFactor.getText().toString());
            if (pcaSmoothingFactor < 0 || pcaSmoothingFactor > 1) {
                mPCASmoothingFactor.setError(
                        getString(R.string.pca_smoothing_factor_validation));
                valid = false;
            }
        } catch (NumberFormatException nfe) {
            mPCASmoothingFactor.setError(
                    getString(R.string.pca_smoothing_factor_validation));
            valid = false;
        }

        if (valid) {
            Preferences preferences = new Preferences.Builder()
                    .withFrameSize(frameSize)
                    .withHopSize(hopSize)
                    .withLearningRate(learningRate)
                    .withNormalizationFactor(normalizationFactor)
                    .withPCASmoothingFactor(pcaSmoothingFactor)
                    .build();
            PreferencesLab.get(PreferencesActivity.this).updatePreferences(preferences);
            PreferencesActivity.this.finish();
        }
    }
}


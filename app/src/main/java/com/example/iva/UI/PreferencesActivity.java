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

    private EditText mLearningRateEdit;
    private EditText mNormalizationFactor;

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

        mLearningRateEdit = findViewById(R.id.learning_rate_edit);
        mNormalizationFactor = findViewById(R.id.normalization_factor_edit);

        PreferencesLab preferencesLab = PreferencesLab.get(this);
        Preferences preferences = preferencesLab.getPreferences();
        setPreferencesText(preferences);
    }

    private void setPreferencesText(Preferences preferences) {
        mLearningRateEdit.setText(String.format(Locale.US, "%.4f", preferences.learningRate));
        mNormalizationFactor.setText(String.format(Locale.US, "%.4f",
                preferences.normalizationFactor));
    }

    private void setDefaultPreferences() {
        PreferencesLab preferencesLab = PreferencesLab.get(this);
        preferencesLab.updatePreferences(Preferences.DEFAULT);
        Preferences preferences = preferencesLab.getPreferences();
        setPreferencesText(preferences);
    }

    private void updatePreferences() {
        boolean valid = true;
        float learningRate = 0, normalizationFactor = 0;

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

        if (valid) {
            Preferences preferences = new Preferences.Builder()
                    .withLearningRate(learningRate)
                    .withNormalizationFactor(normalizationFactor)
                    .build();
            PreferencesLab.get(PreferencesActivity.this).updatePreferences(preferences);
            PreferencesActivity.this.finish();
        }
    }
}


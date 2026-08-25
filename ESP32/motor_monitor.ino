#include <Wire.h>
#include <Adafruit_INA219.h>
#include <YOUR_EDGE_IMPULSE_PROJECT_inferencing.h>

Adafruit_INA219 ina219;

float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];

int raw_feature_get_data(size_t offset, size_t length, float *out_ptr)
{
    memcpy(out_ptr, features + offset, length * sizeof(float));
    return 0;
}

void setup()
{
    Serial.begin(115200);

    if (!ina219.begin())
    {
        Serial.println("Error: INA219 not found!");
        while (1)
        {
            delay(10);
        }
    }

    Serial.println("TinyML Motor Monitor: Online");
}

void loop()
{
    // Collect sensor data
    for (size_t ix = 0;
         ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
         ix += 2)
    {
        features[ix] = ina219.getCurrent_mA();
        features[ix + 1] = ina219.getBusVoltage_V();

        // Approximately 45 Hz sampling
        delay(22);
    }

    // Latest sensor values
    float current_mA =
        features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE - 2];

    float voltage_V =
        features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE - 1];

    // Create Edge Impulse signal
    signal_t features_signal;

    features_signal.total_length =
        EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;

    features_signal.get_data =
        &raw_feature_get_data;

    // Run TinyML inference
    ei_impulse_result_t result = {0};

    EI_IMPULSE_ERROR res =
        run_classifier(&features_signal, &result, false);

    if (res != EI_IMPULSE_OK)
    {
        Serial.println("Inference error");
        return;
    }

    // Display sensor readings
    Serial.print("Voltage: ");
    Serial.print(voltage_V);
    Serial.print(" V | Current: ");
    Serial.print(current_mA);
    Serial.print(" mA | Prediction: ");

    // Display all classes
    for (uint16_t i = 0;
         i < EI_CLASSIFIER_LABEL_COUNT;
         i++)
    {
        Serial.print(result.classification[i].label);
        Serial.print(": ");
        Serial.print(result.classification[i].value, 3);
        Serial.print("  ");
    }

    Serial.println();

    delay(500);
}

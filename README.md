TinyML Motor Current Analysis and Condition Monitoring

Project Overview

This project is a TinyML-based motor condition monitoring system that measures the electrical current and voltage of a motor using an INA219 sensor.

The INA219 is connected in the motor power path, so the measured current represents the current drawn by the motor/motor drive system rather than the ESP32's own power consumption.

The collected motor electrical signals are analyzed using spectral analysis and FFT-based feature extraction. The extracted frequency-domain features are then used by a machine-learning classifier to identify different motor operating conditions such as normal and critical conditions.

The trained model is deployed on an ESP32 for real-time, on-device inference.

System Workflow

Motor
↓
INA219 Current/Voltage Sensor
↓
Current & Voltage Data
↓
1-Second Window
↓
Low-Pass Filtering
↓
FFT / Spectral Analysis
↓
Feature Extraction
↓
ML Classification
↓
Motor Condition Prediction

Hardware Used

- ESP32
- INA219 current/voltage sensor
- DC motor
- L298N motor driver
- External motor battery

Data Acquisition

The INA219 measures the electrical parameters of the motor:

- Motor current (mA)
- Motor/bus voltage (V)

The sensor data is collected as time-series data and divided into 1-second windows.

Configuration

Parameter| Value
Window size| 1 second
Sampling frequency| 45 Hz
Input axes| Motor Current and Voltage
Window increase| 1 second
FFT length| 64
Filter type| Low-pass
Cut-off frequency| 3 Hz
Filter order| 6

Spectral Analysis

Spectral analysis is used to identify the frequency components and energy distribution present in the motor's electrical signal.

The time-domain motor current and voltage signals are transformed into the frequency domain using FFT (Fast Fourier Transform).

FFT is used for feature extraction, not classification.

Different motor operating conditions can produce different frequency signatures. These signatures are used as features for the machine-learning classifier.

Filtering

A low-pass filter with a 3 Hz cutoff frequency is used during preprocessing to reduce unwanted high-frequency noise and fluctuations while retaining the useful low-frequency characteristics of the motor signal.

Possible unwanted disturbances include electrical interference, sensor fluctuations, switching effects from the motor driver, and other high-frequency variations.

Feature Extraction

After preprocessing, FFT-based spectral features are generated from the motor current and voltage signals.

The Feature Explorer is used to visualize the extracted features. Separation between different operating-condition clusters indicates that the extracted spectral features contain useful information for classification.

Machine Learning

The extracted spectral features are provided to a machine-learning classifier trained using Edge Impulse.

The classifier learns the relationship between the frequency-domain features and the different motor operating conditions.

TinyML Deployment

The trained model is exported from Edge Impulse and deployed on the ESP32.

During real-time operation:

1. The INA219 measures motor current and voltage.
2. The ESP32 collects the sensor data.
3. The signal is processed through the Edge Impulse DSP pipeline.
4. FFT-based spectral features are generated.
5. The trained classifier performs inference.
6. The predicted motor condition is displayed through the Serial Monitor.

Applications

This approach can be used for:

- Motor condition monitoring
- Motor fault detection
- Predictive maintenance
- Industrial equipment monitoring
- Electrical motor diagnostics
- IoT-based monitoring
- Edge AI applications

Conclusion

This project demonstrates how motor electrical current and voltage signals can be combined with spectral analysis, FFT-based feature extraction, and TinyML classification to perform real-time motor condition monitoring directly on an ESP32.

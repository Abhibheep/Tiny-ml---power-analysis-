TinyML Power Analysis and Motor Monitoring

Project Overview

This project is a TinyML-based motor monitoring system that uses an INA219 sensor to measure the current and voltage of a motor. The collected electrical signals are analyzed using spectral analysis and Fast Fourier Transform (FFT) to extract useful frequency-domain features.

These features are then given to a machine-learning classifier trained using Edge Impulse to identify different motor operating conditions such as normal and critical conditions.

The trained model is deployed on an ESP32 for real-time, on-device inference.

---

System Workflow

INA219 Sensor
      ↓
Current and Voltage Measurement
      ↓
Time-Series Data
      ↓
1-Second Window
      ↓
Low-Pass Filtering
      ↓
FFT / Spectral Analysis
      ↓
Feature Generation
      ↓
ML Classification
      ↓
Motor Condition Prediction

---

Hardware Used

- ESP32
- Arduino UNO (for data collection, if required)
- INA219 current/voltage sensor
- DC motor
- Motor driver
- External power supply

---

Software Used

- Arduino IDE
- Edge Impulse
- C/C++
- ESP32 Arduino framework

---

Data Acquisition

The INA219 sensor measures two electrical parameters:

- Current (mA)
- Bus Voltage (V)

The signals are collected as time-series data.

Configuration

Parameter| Value
Window size| 1 second
Sampling frequency| 45 Hz
Input axes| Current and Voltage
Window increase / stride| 1 second
Training data subset| 100%

The Arduino UNO can be used for basic sensor data collection, while the ESP32 is used for the TinyML inference stage.

---

Spectral Analysis

Spectral analysis is used to study the frequency components present in a signal and how the signal's energy is distributed across different frequencies.

Instead of looking only at how current and voltage change with time, the signal is converted into the frequency domain.

This helps identify patterns that may be difficult to observe directly in the time-domain waveform.

---

Filtering

A low-pass filter is used during signal preprocessing.

Filter settings

- Filter type: Low-pass
- Cut-off frequency: 3 Hz
- Filter order: 6
- Scale axes: 1
- Input decimation ratio: 1

The purpose of filtering is to reduce unwanted high-frequency noise and retain the useful low-frequency information in the motor signal.

---

FFT Analysis

The project uses FFT (Fast Fourier Transform) for spectral analysis.

FFT converts the sampled time-domain signal into frequency-domain information.

FFT settings

- Analysis type: FFT
- FFT length: 64
- Log spectrum: Enabled
- Overlap FFT frames: Enabled
- Improve low-frequency resolution: Disabled

FFT is not a classifier. It is a signal-processing technique used to generate frequency-domain features that are later supplied to the machine-learning model.

---

Feature Explorer

The Feature Explorer shows the generated features and their distribution for different classes.

In the project, the classes are represented separately, allowing us to see whether the extracted features provide good separation between the motor conditions.

Better separation generally makes classification easier for the machine-learning model.

---

Machine Learning

The extracted spectral features are used as inputs to a machine-learning classifier in Edge Impulse.

The classifier learns patterns associated with the different motor operating conditions.

The trained model is then exported and deployed to the ESP32.

---

Edge AI Inference

During real-time operation, the ESP32:

1. Reads current from the INA219.
2. Reads voltage from the INA219.
3. Collects the required data window.
4. Provides the data to the Edge Impulse inference pipeline.
5. Performs feature processing and classification.
6. Outputs the predicted motor condition.

The prediction probabilities can also be displayed through the Serial Monitor.

---

On-Device Performance

The Edge Impulse results showed approximately:

- Inference time: 1 ms
- Peak RAM usage: approximately 1.4 KB
- Flash usage: approximately 14.6 KB

These results demonstrate that the trained model can be used for lightweight edge inference.

---

Model Validation Results

The validation results shown in Edge Impulse were:

Metric| Value
Area Under ROC Curve| 0.96
Weighted Average Precision| 0.98
Weighted Average Recall| 0.98
Weighted Average F1 Score| 0.98

---

Arduino UNO Data Collection

The Arduino UNO can be used to collect INA219 measurements and transmit them through the Serial Monitor.

The UNO is used mainly for data acquisition, while the ESP32 is used for the TinyML inference stage.

---

ESP32 TinyML Deployment

The ESP32 runs the exported Edge Impulse inference library.

The main program performs:

Sensor Reading
      ↓
Feature Buffer
      ↓
Edge Impulse Signal
      ↓
DSP / FFT Processing
      ↓
ML Classifier
      ↓
Prediction

---

Applications

This type of system can be used for:

- Motor condition monitoring
- Predictive maintenance
- Motor fault detection
- Industrial equipment monitoring
- IoT-based condition monitoring
- Edge AI systems
- Electrical load monitoring

---

Repository Structure

Tiny-ml---power-analysis/
│
├── README.md
│
├── Arduino_UNO/
│   └── data_collection.ino
│
├── ESP32/
│   └── motor_monitor.ino
│
└── Images/
    ├── time_series.png
    ├── filter.png
    ├── fft.png
    ├── spectral_power.png
    ├── feature_explorer.png
    └── model_results.png

---

Conclusion

The project demonstrates how signal processing and TinyML can be combined for real-time motor monitoring. Current and voltage signals are collected using the INA219 sensor, filtered and transformed into frequency-domain features using FFT-based spectral analysis, and then classified using a machine-learning model. The trained model is deployed on the ESP32, allowing the motor condition to be analyzed locally with low inference time and low memory usage.

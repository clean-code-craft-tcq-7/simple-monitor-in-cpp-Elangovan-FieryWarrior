#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

namespace {
    void showAlert(const char* message) {
        cout << message << '\n';
        for (int i = 0; i < 6; ++i) {
            cout << "\r* " << flush;
            sleep_for(seconds(1));
            cout << "\r *" << flush;
            sleep_for(seconds(1));
        }
    }

    bool checkRange(float value, float min, float max) {
        return value >= min && value <= max;
    }
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    struct Vital {
        float value, min, max;
        const char* alert;
    } vitals[] = {
        {temperature, 95, 102, "Temperature is critical!"},
        {pulseRate, 60, 100, "Pulse Rate is out of range!"},
        {spo2, 90, 1000, "Oxygen Saturation out of range!"}
    };

    for (const auto& v : vitals) {
        if (!checkRange(v.value, v.min, v.max)) {
            showAlert(v.alert);
            return 0;
        }
    }
    return 1;
}

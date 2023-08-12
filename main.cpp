#include "mbed.h"
#include "LSM6DSLSensor.h"
#include <math.h> // Include the math library for the arctan and sqrt functions

#define PI 3.141592654

static DevI2C devI2c(PB_11, PB_10);
static LSM6DSLSensor acc_gyro(&devI2c, 0xD4, D4, D5); // high address

float computeAngle(int x, int y, int z) {
    // Calculate roll angle using the provided equation
    float roll = atan(static_cast<float>(y) / sqrt(static_cast<float>(x * x) + static_cast<float>(z * z)));
    return roll * (180.0 / PI); // Convert radians to degrees
}

/* Simple main function */
int main() {
    uint8_t id;
    int32_t axes[3];
    float res = 0;
    acc_gyro.init(NULL);

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while (1) {
        acc_gyro.get_x_axes(axes);
        res = computeAngle(axes[0], axes[1], axes[2]);
        printf("Roll angle: %3.2f degrees\r\n", res);

        thread_sleep_for(2000);
    }
}


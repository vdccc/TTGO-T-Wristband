#include "wb/mpu.hpp"

void wbMPU::init() { mpu.initMPU9250(); }

void wbMPU::sleep() {
  mpu.writeBit(MPU9250_ADDRESS, PWR_MGMT_1, 5, false);
  mpu.writeBit(MPU9250_ADDRESS, PWR_MGMT_1, 6, false);
  mpu.writeBit(MPU9250_ADDRESS, PWR_MGMT_1, 4, false);
  mpu.writeByte(MPU9250_ADDRESS, PWR_MGMT_2, 0x07);
  mpu.writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, 0x09);
  mpu.writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x40);
  mpu.writeBit(MPU9250_ADDRESS, MOT_DETECT_CTRL, 7, true);
  mpu.writeBit(MPU9250_ADDRESS, MOT_DETECT_CTRL, 6, true);
  mpu.writeByte(MPU9250_ADDRESS, WOM_THR, 220);
  mpu.writeBit(MPU9250_ADDRESS, INT_PIN_CFG, 5, 0);
  mpu.writeByte(MPU9250_ADDRESS, INT_STATUS, 0);
  mpu.writeByte(MPU9250_ADDRESS, LP_ACCEL_ODR, 0x01);
  mpu.writeBit(MPU9250_ADDRESS, PWR_MGMT_1, 5, true);
}

void wbMPU::deepSleep() {
  mpu.writeByte(MPU9250_ADDRESS, PWR_MGMT_1,
                mpu.readByte(MPU9250_ADDRESS, PWR_MGMT_1) |
                    0x40); // set sleep mode bit(6), disable all sensors
  delay(100);              // wait for all registers to reset
  mpu.writeByte(AK8963_ADDRESS, AK8963_CNTL,
                mpu.readByte(AK8963_ADDRESS, AK8963_CNTL) &
                    ~(0x0F)); // clear bits 0 to 3 to power down magnetometer
  mpu.writeByte(MPU9250_ADDRESS, PWR_MGMT_1,
                mpu.readByte(MPU9250_ADDRESS, PWR_MGMT_1) |
                    0x10); // write bit 4 to enable gyro standby
}

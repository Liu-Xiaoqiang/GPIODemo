package com.chipsee.gpiodemo;

import android.util.Log;

/**
 * Created by Chipsee on 2017/8/10.
 */

public class HardwareControler {
    private static final String TAG = "HardwareControler";

    /* GPIO */
    //GPIOEnum.LOW or GPIOEnum.HIGH
    static public native int setGPIOValue(int pin, int value);
    static public native int getGPIOValue(int pin);

    /* Buzzer */
    static public native int buzzer_open();
    static public native int buzzer_close();

    /* I2C */
    static public native int i2c_open(String i2c_dev);
    static public native int i2c_set_slave_addr_bits(int fd, int n);
    static public native int i2c_set_slave_addr(int fd, int slave_addr);
    static public native String i2c_read(int fd, int slave_addr, String data_addr, int n);
    static public native int i2c_write(int fd, int slave_addr, String data_addr, int n);
    static public native void i2c_close(int fd);

    /* SPI */
    static public native int spi_open(String spi_dev);
    static public native int spi_config(int fd, int mode, int bits, int speed, boolean lsb);
    static public native int spi_transfer(int fd, String tx, String rx);

    static {
        try {
            System.loadLibrary("chipsee-hardware");
        } catch (UnsatisfiedLinkError e) {
            Log.d(TAG, "libchipsee-hardware library not found!");
        }
    }
}

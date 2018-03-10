
#ifndef SH1106_h
#define SH1106_h

#include <Arduino.h>

class SH1106 {

public:





public:
    SH1106() : i2c(0x78, true, 100000) {}


    // ############################ SH1106 COMMANDS ############################
    // Each function sets a parameter of the SH1106 controller. For detailed
    // information about each setting refer to the datasheet (available e.g.
    // here: http://www.allshore.com/pdf/SH1106.pdf).
    // The numbres in comment refer to the command number in the datasheet

    void   columnAddr         (uint8_t col);                          // 1, 2
    void   pumpVoltage0123    (uint8_t level0123);                    // 3
    void   startLine          (uint8_t line);                         // 4
    void   contrast           (uint8_t contrast);                     // 5
    void   segmentRemap       (bool reverse);                         // 6
    void   setEntireDisplayOn (bool enable);                          // 7
    void   reverse            (bool enable);                          // 8
    void   multiplex          (uint8_t ratio);                        // 9
    void   dcDcEnable         (bool enable);                          // 10
    void   displayEnable      (bool enable);                          // 11
    void   pageAddr           (uint8_t page);                         // 12
    void   flipVertically     (bool flip);                            // 13
    void   displayOffest      (uint8_t offset);                       // 14
    void   clockFrequency     (uint8_t frequency, uint8_t divisor);   // 15
    void   clockFrequency     (uint8_t regVal);                       // 15
    void   disPreChargeTime   (uint8_t pre, uint8_t dis);             // 16
    void   disPreChargeTime   (uint8_t regVal);                       // 16
    void   comConfiguration   (bool sequential);                      // 17
    void   comVoltage         (uint8_t regValue);                     // 18
    void   rmwStart           (void);                                 // 19
    void   rmwEnd             (void);                                 // 20
    void   nop                (void);                                 // 21


    uint8_t readStatus();
    bool isEnabled();
    bool isBusy();

    void sendCommand(uint8_t command);
    void transferCommand(uint8_t command);
    void transferRAM(uint8_t data);
    void init();


    // Low level functions to communicate with an SH1106 chip via i2c
    class I2C {
    public:
        // Constructor parameters:
        //  - address:            display i2c address
        //  - useInternalPullup:  use internal pullups as i2c bus pullup resistors
        //  - frequency:          i2c bus transmission frequency (SCL)
        I2C (uint8_t address, bool useInternalPullup, uint32_t frequency);

        // Initialize the i2c interface
        void    init();

        // Send a start condition
        void    start();
        // Send a stop condition
        void    stop();

        // Send the address with R/!W bit cleared (-> write)
        // The address has been set in the constructor of this class
        void    addrWrite();
        // Send the address with R/!W bit set (-> read)
        void    addrRead();

        // Send a control byte (as specified in the SH1106 datasheet)
        // - last:    this is the last control byte, only data follows (any lenght)
        //            If `false` only a data byte follows, and then another control.
        // - command: The following data byte(s) have to be interpreted as commands
        //            If `false` they willi be interpreted as data
        void controlByte(bool last, bool command);

        // Send a byte of data
        void    send(uint8_t data);
        // Read a byte of data
        uint8_t read(bool isLastByte);

        // Returns true if the device at `address` responds
        bool checkConnection();

    private:

        uint8_t address;
        const bool useInternalPullup;
        const uint32_t frequency;

    } i2c;
};


#endif

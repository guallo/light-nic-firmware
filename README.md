# light-nic-firmware
Light Network Interface Card Firmware

## To rebuild project

```shell
make clean && make all
```

## To download the hex file to the device

```shell
make program
```

## To communicate with the device

```shell
screen /dev/ttyUSB0 9600,cs8  # options must match those into main.c
```

## Additional reference

* https://www.nongnu.org/avr-libc/user-manual/modules.html
* https://www.arnabkumardas.com/arduino-tutorial/usart-register-description/


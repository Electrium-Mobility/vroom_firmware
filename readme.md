# STM32F469I-DISCO-REV-AU1 TBS

The default IDE is set to STM32CubeIDE, to change IDE open the STM32F469I-DISCO-REV-AU1.ioc with CubeMX and select from the supported IDEs (EWARM from version 8.50.9, MDK-ARM, and STM32CubeIDE). Supports flashing of the STM32F469I-DISCO-REV-AU1 board directly from TouchGFX Designer using GCC and STM32CubeProgrammer.Flashing the board requires STM32CubeProgrammer which can be downloaded from the ST webpage. 

This TBS is configured for 480 x 800 pixels 16bpp screen resolution.  

Performance testing can be done using the GPIO pins designated with the following signals: VSYNC_FREQ  - Pin PA2(D5), RENDER_TIME - Pin PA6(D6), FRAME_RATE  - Pin PA1(D3), MCU_ACTIVE  - Pin PG12(D4)
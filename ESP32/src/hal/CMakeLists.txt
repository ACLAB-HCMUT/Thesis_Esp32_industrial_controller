if(DEFINED MCU AND(MCU STREQUAL "Nuvoton"))
    target_sources(
        ${PROJECT_NAME}
        PRIVATE
        nuvoton/adc.c
        nuvoton/clock.c
        nuvoton/gpio.c
        nuvoton/i2c.c
        nuvoton/rtc.c
        nuvoton/spi.c
        nuvoton/timer.c
        nuvoton/uart.c
        nuvoton/usb.c
        nuvoton/qspi.c
        nuvoton/watchdog.c
    )
elseif(DEFINED MCU AND(MCU STREQUAL "Nrf"))
    target_sources(
        ${PROJECT_NAME}
        PRIVATE
        nrf/adc.c
        nrf/clock.c
        nrf/rtc.c
        nrf/timer.c
        nrf/gpio.c
        nrf/i2c.c
        nrf/qspi.c
        nrf/spi.c
        nrf/uart.c
        nrf/usb.c
        nrf/watchdog.c
    )
else()
    message(FATAL_ERROR "Unsupported target MCU, please set MCU")
endif()

/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v12.0
processor: LPC55S36
package_id: LPC55S36JBD100
mcu_data: ksdk2_0
processor_version: 12.0.0
board: LPCXpresso55S36
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm33_core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '93', peripheral: FLEXCOMM0, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO0_29/FC0_RXD_SDA_MOSI_DATA/CTIMER2_MAT3/SCT0_OUT8/TRACEDATA2/FC6_RXD_SDA_MOSI_DATA/CMP0_OUT/SECURE_GPIO0_29/PWM0_A1/SPI_DIN/EXTTRIG_IN3,
    mode: inactive, slew_rate: standard, invert: disabled, open_drain: disabled}
  - {pin_num: '95', peripheral: FLEXCOMM0, signal: TXD_SCL_MISO_WS, pin_signal: PIO0_30/FC0_TXD_SCL_MISO_WS/CTIMER0_MAT0/SCT0_OUT9/TRACEDATA1/CAN0_TD/FC6_TXD_SCL_MISO_WS/SECURE_GPIO0_30/PWM1_A1/AOI1_OUT0,
    mode: inactive, slew_rate: standard, invert: disabled, open_drain: disabled}
  - {pin_num: '77', peripheral: FLEXCOMM2, signal: TXD_SCL_MISO_WS, pin_signal: PIO1_25/FC2_TXD_SCL_MISO_WS/SCT0_OUT2/UTICK_CAP0/PWM1_A2/SPI_SCLK/AOI0_OUT3, mode: pullUp,
    open_drain: enabled}
  - {pin_num: '3', peripheral: FLEXCOMM2, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO1_24/FC2_RXD_SDA_MOSI_DATA/SCT0_OUT1/FC3_SSEL3/AOI0_OUT2/ADC1_8B, mode: pullUp,
    open_drain: enabled}
  - {pin_num: '65', peripheral: FLEXCOMM7, signal: TXD_SCL_MISO_WS, pin_signal: PIO1_30/FC7_TXD_SCL_MISO_WS/SCT_GPI7/QSPI_CS0/PWM0_X3/AOI1_OUT3/HSCMP0_OUT, mode: pullUp,
    open_drain: enabled}
  - {pin_num: '37', peripheral: FLEXCOMM7, signal: CTS_SDA_SSEL0, pin_signal: PIO1_21/FC7_CTS_SDA_SSEL0/CTIMER3_MAT2/FC4_RXD_SDA_MOSI_DATA/PWM1_A0/TRIGOUT_1, mode: pullUp,
    open_drain: enabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M33 */
void BOARD_InitPins(void)
{
    /* Enables the clock for the I/O controller.: Enable Clock. */
    CLOCK_EnableClock(kCLOCK_Iocon);

    const uint32_t port0_pin29_config = (/* Pin is configured as FC0_RXD_SDA_MOSI_DATA */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN29 (coords: 93) is configured as FC0_RXD_SDA_MOSI_DATA */
    IOCON_PinMuxSet(IOCON, 0U, 29U, port0_pin29_config);

    const uint32_t port0_pin30_config = (/* Pin is configured as FC0_TXD_SCL_MISO_WS */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN30 (coords: 95) is configured as FC0_TXD_SCL_MISO_WS */
    IOCON_PinMuxSet(IOCON, 0U, 30U, port0_pin30_config);

    IOCON->PIO[1][21] = ((IOCON->PIO[1][21] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_OD_MASK)))

                         /* Signal(function) select: PORT121 (pin 37) is configured as FC7_CTS_SDA_SSEL0. */
                         | IOCON_PIO_FUNC(0x01u)

                         /* Mode select (on-chip pull-up/pull-down resistor control): Pull-up.
                          * Pull-up resistor enabled. */
                         | IOCON_PIO_MODE(PIO1_21_MODE_PULL_UP)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO1_21_DIGIMODE_DIGITAL)

                         /* Controls open-drain mode: Open-drain.
                          * Simulated open-drain output (high drive disabled). */
                         | IOCON_PIO_OD(PIO1_21_OD_OPEN_DRAIN));

    IOCON->PIO[1][24] = ((IOCON->PIO[1][24] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_OD_MASK)))

                         /* Signal(function) select: PORT124 (pin 3) is configured as FC2_RXD_SDA_MOSI_DATA. */
                         | IOCON_PIO_FUNC(0x01u)

                         /* Mode select (on-chip pull-up/pull-down resistor control): Pull-up.
                          * Pull-up resistor enabled. */
                         | IOCON_PIO_MODE(PIO1_24_MODE_PULL_UP)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO1_24_DIGIMODE_DIGITAL)

                         /* Controls open-drain mode: Open-drain.
                          * Simulated open-drain output (high drive disabled). */
                         | IOCON_PIO_OD(PIO1_24_OD_OPEN_DRAIN));

    IOCON->PIO[1][25] = ((IOCON->PIO[1][25] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_OD_MASK)))

                         /* Signal(function) select: PORT125 (pin 77) is configured as FC2_TXD_SCL_MISO_WS. */
                         | IOCON_PIO_FUNC(0x01u)

                         /* Mode select (on-chip pull-up/pull-down resistor control): Pull-up.
                          * Pull-up resistor enabled. */
                         | IOCON_PIO_MODE(PIO1_25_MODE_PULL_UP)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO1_25_DIGIMODE_DIGITAL)

                         /* Controls open-drain mode: Open-drain.
                          * Simulated open-drain output (high drive disabled). */
                         | IOCON_PIO_OD(PIO1_25_OD_OPEN_DRAIN));

    IOCON->PIO[1][30] = ((IOCON->PIO[1][30] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_OD_MASK)))

                         /* Signal(function) select: PORT130 (pin 65) is configured as FC7_TXD_SCL_MISO_WS. */
                         | IOCON_PIO_FUNC(0x01u)

                         /* Mode select (on-chip pull-up/pull-down resistor control): Pull-up.
                          * Pull-up resistor enabled. */
                         | IOCON_PIO_MODE(PIO1_30_MODE_PULL_UP)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO1_30_DIGIMODE_DIGITAL)

                         /* Controls open-drain mode: Open-drain.
                          * Simulated open-drain output (high drive disabled). */
                         | IOCON_PIO_OD(PIO1_30_OD_OPEN_DRAIN));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

/*
 * Copyright 2021 NXP
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
product: Pins v9.0
processor: LPC55S36
package_id: LPC55S36JBD100
mcu_data: ksdk2_0
processor_version: 0.10.0
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
  - {pin_num: '56', peripheral: SWD, signal: SWO, pin_signal: PIO0_18/FC4_CTS_SDA_SSEL0/CTIMER1_MAT0/SCT0_OUT1/FC5_RXD_SDA_MOSI_DATA/SWO/SECURE_GPIO0_18/PWM1_A0/QSPI_DIN1/TRIGOUT_7/ACMP0_C,
    mode: inactive, slew_rate: standard, invert: disabled, open_drain: disabled, asw0: disabled}
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

    const uint32_t port0_pin18_config = (/* Pin is configured as SWO */
                                         IOCON_PIO_FUNC8 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI |
                                         /* Analog switch 0 is open (disabled) */
                                         IOCON_PIO_ASW0_DI);
    /* PORT0 PIN18 (coords: 56) is configured as SWO */
    IOCON_PinMuxSet(IOCON, 0U, 18U, port0_pin18_config);

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
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

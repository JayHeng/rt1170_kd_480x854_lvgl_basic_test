/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: MIMXRT1176xxxxx
package_id: MIMXRT1176DVMAA
mcu_data: ksdk2_0
processor_version: 0.9.6
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitLpuartPins();
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLpuartPins:
- options: {callFromInitBoot: 'true', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: M15, peripheral: LPUART1, signal: RXD, pin_signal: GPIO_AD_25, software_input_on: Enable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Disable, drive_strength: Normal, slew_rate: Slow}
  - {pin_num: L13, peripheral: LPUART1, signal: TXD, pin_signal: GPIO_AD_24, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper, open_drain: Disable, drive_strength: Normal,
    slew_rate: Slow}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLpuartPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitLpuartPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_24_LPUART1_TXD,          /* GPIO_AD_24 is configured as LPUART1_TXD */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_25_LPUART1_RXD,          /* GPIO_AD_25 is configured as LPUART1_RXD */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_AD_25 */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_24_LPUART1_TXD,          /* GPIO_AD_24 PAD functional properties : */
      0x00U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: normal drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_25_LPUART1_RXD,          /* GPIO_AD_25 PAD functional properties : */
      0x00U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: normal drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitMipiPanelPins:
- options: {callFromInitBoot: 'false', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: A4, peripheral: GPIO11, signal: 'gpio_io, 16', pin_signal: GPIO_DISP_B2_15, software_input_on: Disable}
  - {pin_num: N8, peripheral: LPI2C5, signal: SCL, pin_signal: GPIO_LPSR_05, software_input_on: Enable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Enable, drive_strength: Normal, slew_rate: Slow}
  - {pin_num: N7, peripheral: LPI2C5, signal: SDA, pin_signal: GPIO_LPSR_04, software_input_on: Enable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Enable, drive_strength: Normal, slew_rate: Slow}
  - {pin_num: N12, peripheral: GPIO8, signal: 'gpio_io, 31', pin_signal: GPIO_AD_00, software_input_on: Enable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Disable, drive_strength: Normal, slew_rate: Slow}
  - {pin_num: R14, peripheral: GPIO9, signal: 'gpio_io, 00', pin_signal: GPIO_AD_01, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper, open_drain: Disable,
    drive_strength: Normal, slew_rate: Slow}
  - {pin_num: R13, peripheral: GPIO9, signal: 'gpio_io, 01', pin_signal: GPIO_AD_02}
  - {pin_num: K17, peripheral: GPIO9, signal: 'gpio_io, 29', pin_signal: GPIO_AD_30}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitMipiPanelPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitMipiPanelPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */
  CLOCK_EnableClock(kCLOCK_Iomuxc_Lpsr);      /* LPCG on: LPCG is ON. */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_00_GPIO8_IO31,           /* GPIO_AD_00 is configured as GPIO8_IO31 */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_AD_00 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_01_GPIO9_IO00,           /* GPIO_AD_01 is configured as GPIO9_IO00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_08_GPIO9_IO07,           /* GPIO_AD_08 is configured as GPIO9_IO07 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_02_GPIO9_IO01,           /* GPIO_AD_02 is configured as GPIO9_IO01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_30_GPIO9_IO29,           /* GPIO_AD_30 is configured as GPIO9_IO29 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_15_GPIO11_IO16,     /* GPIO_DISP_B2_15 is configured as GPIO11_IO16 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_LPSR_04_LPI2C5_SDA,         /* GPIO_LPSR_04 is configured as LPI2C5_SDA */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_LPSR_04 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_LPSR_05_LPI2C5_SCL,         /* GPIO_LPSR_05 is configured as LPI2C5_SCL */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_LPSR_05 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_LPSR_06_LPI2C6_SDA,         /* GPIO_LPSR_06 is configured as LPI2C5_SDA */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_LPSR_04 */
  IOMUXC_SetPinMux(
	  IOMUXC_GPIO_LPSR_07_LPI2C6_SCL,         /* GPIO_LPSR_07 is configured as LPI2C5_SCL */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_LPSR_05 */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_00_GPIO8_IO31,           /* GPIO_AD_00 PAD functional properties : */
      0x00U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: normal drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_01_GPIO9_IO00,           /* GPIO_AD_01 PAD functional properties : */
      0x00U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: normal drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_08_GPIO9_IO07,           /* GPIO_AD_08 PAD functional properties : */
      0x00U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: normal drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_LPSR_04_LPI2C5_SDA,         /* GPIO_LPSR_04 PAD functional properties : */
      0x20U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: normal driver
                                                 Pull / Keep Select Field: Pull Disable
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain LPSR Field: Enabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_LPSR_05_LPI2C5_SCL,         /* GPIO_LPSR_05 PAD functional properties : */
      0x20U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: normal driver
                                                 Pull / Keep Select Field: Pull Disable
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain LPSR Field: Enabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_LPSR_06_LPI2C6_SDA,         /* GPIO_LPSR_06 PAD functional properties : */
      0x20U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: normal driver
                                                 Pull / Keep Select Field: Pull Disable
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain LPSR Field: Enabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_LPSR_07_LPI2C6_SCL,         /* GPIO_LPSR_07 PAD functional properties : */
      0x20U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: normal driver
                                                 Pull / Keep Select Field: Pull Disable
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain LPSR Field: Enabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

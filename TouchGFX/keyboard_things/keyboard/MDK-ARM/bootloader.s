;******************** (C) COPYRIGHT 2020 STMicroelectronics ********************
;* File Name          : bootloader.s
;* @author  MCD Application Team
;* Description        : Coretx-M7 binary code include .s file
;******************************************************************************
;* @attention
;*
;* Copyright (c) 2020 STMicroelectronics.
;* All rights reserved.
;*
;* This software component is licensed by ST under BSD 3-Clause license,
;* the "License"; You may not use this file except in compliance with the
;* License. You may obtain a copy of the License at:
;*                        opensource.org/licenses/BSD-3-Clause
;*
;******************************************************************************
    EXPORT bootloader
	AREA bootloader_section, DATA, PREINIT_ARRAY
bootloader
	INCBIN ..\ExtMem_Boot\Binary\Bootloader.bin

	END

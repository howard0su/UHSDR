/*  -*-  mode: c; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4; coding: utf-8  -*-  */
/************************************************************************************
**                                                                                 **
**                               mcHF QRP Transceiver                              **
**                             K Atanassov - M0NKA 2014                            **
**                                                                                 **
**---------------------------------------------------------------------------------**
**                                                                                 **
**  File name:                                                                     **
**  Description:                                                                   **
**  Last Modified:                                                                 **
**  Licence:		GNU GPLv3                                                      **
************************************************************************************/

#ifndef __MCHF_HW_I2S_H
#define __MCHF_HW_I2S_H

#include "uhsdr_board_config.h"

void UhsdrHwI2s_Codec_StartDMA(
    void* audio_out, void* audio_in, size_t audio_length,
    void* iq_out, void* iq_in, size_t iq_length);
void UhsdrHwI2s_Codec_StopDMA(void);

#endif


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

// Common
#include "uhsdr_board_config.h"
#include "uhsdr_board.h"
#include "profiling.h"
#include "uhsdr_hw_i2s.h"

#include "audio_driver.h"

#ifdef UI_BRD_MCHF
#include "i2s.h"
#endif

#ifdef UI_BRD_OVI40
#include "sai.h"
#endif

#ifdef UI_BRD_MCHF
/**
 * @brief HAL Handler for Codec DMA Interrupt
 */
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    AudioDriver_HandleBlock(0);
}

/**
 * @brief HAL Handler for Codec DMA Interrupt
 */
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
    AudioDriver_HandleBlock(1);
}
#endif

#ifdef UI_BRD_OVI40
void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hi2s)
{
    if (hi2s == &hsai_BlockA2)
    {
        AudioDriver_HandleBlock(0);
    }
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hi2s)
{
    if (hi2s == &hsai_BlockA2)
    {
        AudioDriver_HandleBlock(1);
    }
}
#endif

#if defined(UI_BRD_OVI40)
static void UhsdrHWI2s_Sai32Bits(SAI_HandleTypeDef* hsai)
{
    hsai->hdmarx->Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hsai->hdmarx->Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    HAL_DMA_Init(hsai->hdmarx);

    HAL_SAI_InitProtocol(hsai, SAI_I2S_STANDARD, SAI_PROTOCOL_DATASIZE_32BIT, 2);
}
#endif

static void UhsdrHwI2s_SetBitWidth()
{
#if defined(USE_32_IQ_BITS)
    #if defined(UI_BRD_MCHF)
    hi2s3.Init.DataFormat = I2S_DATAFORMAT_32B;
    HAL_I2S_Init(&hi2s3);

    #endif
    #if defined(UI_BRD_OVI40)
    UhsdrHWI2s_Sai32Bits(&hsai_BlockA2);
    UhsdrHWI2s_Sai32Bits(&hsai_BlockB2);
    #endif
#endif

#if defined(USE_32_AUDIO_BITS)
    #if defined(UI_BRD_OVI40)
    UhsdrHWI2s_Sai32Bits(&hsai_BlockA1);
    UhsdrHWI2s_Sai32Bits(&hsai_BlockB1);
    #endif
#endif
}

void UhsdrHwI2s_Codec_StartDMA(
    void* audio_out, void* audio_in, size_t audio_length,
    void* iq_out, void* iq_in, size_t iq_length
)
{
    UhsdrHwI2s_SetBitWidth();

#ifdef UI_BRD_MCHF
    HAL_I2SEx_TransmitReceive_DMA(&hi2s3,iq_out,iq_in,iq_length);
#endif
#ifdef UI_BRD_OVI40
    HAL_SAI_Receive_DMA(&hsai_BlockA1,audio_in,audio_length);
    HAL_SAI_Transmit_DMA(&hsai_BlockB1,audio_out,audio_length);

    HAL_SAI_Receive_DMA(&hsai_BlockA2,iq_in,iq_length);
    HAL_SAI_Transmit_DMA(&hsai_BlockB2,iq_out,iq_length);

#endif
}


void UhsdrHwI2s_Codec_StopDMA(void)
{
#ifdef UI_BRD_MCHF
    HAL_I2S_DMAStop(&hi2s3);
#endif
#ifdef UI_BRD_OVI40
    HAL_SAI_DMAStop(&hsai_BlockA1);
    HAL_SAI_DMAStop(&hsai_BlockB1);
    HAL_SAI_DMAStop(&hsai_BlockA2);
    HAL_SAI_DMAStop(&hsai_BlockB2);
#endif
}

#pragma once
#include <stdint.h>

typedef struct
{
    uint8_t state;

    uint16_t xraw;
    uint16_t yraw;
    int16_t xraw_m1;
    int16_t xraw_m2;
    int16_t yraw_m1;
    int16_t yraw_m2;
    int16_t focus_xprev;
    int16_t focus_yprev;
    //int32_t xraw_avgBuff;
    //int32_t yraw_avgBuff;
    int16_t hr_x;
    int16_t hr_y;
    uint16_t xraw_prev;
    uint16_t yraw_prev;
    int32_t cal[6];
    bool present;

} mchf_touchscreen_t;

extern mchf_touchscreen_t mchf_touchscreen;

#define TP_DATASETS_VALID		0x04   // number of sets that must be identical for marked as VALID
#define TP_DATASETS_WAIT		0x01   // first dataset received
#define TP_DATASETS_PROCESSED	0xff
#define TP_DATASETS_NONE		0x00

void    UiLcdHy28_TouchscreenDetectPress(void);
void 	UiLcdHy28_TouchscreenReadCoordinates(void);
bool    UiLcdHy28_TouchscreenHasProcessableCoordinates(void);
void    UiLcdHy28_TouchscreenInit(uint8_t mirror);
bool    UiLcdHy28_TouchScreenHasData();

// Driver Interface
void    UiLcdHy28_TouchscreenReadData(uint16_t* x_p,uint16_t* y_p);
bool    UiLcdHy28_TouchScreenIsPressed();

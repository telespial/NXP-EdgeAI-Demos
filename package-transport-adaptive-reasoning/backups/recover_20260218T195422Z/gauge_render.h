#ifndef EDGEAI_EV_GAUGE_RENDER_H
#define EDGEAI_EV_GAUGE_RENDER_H

#include <stdbool.h>

#include "power_data_source.h"

#define GAUGE_RENDER_AI_PILL_X0 166
#define GAUGE_RENDER_AI_PILL_Y0 4
#define GAUGE_RENDER_AI_PILL_X1 313
#define GAUGE_RENDER_AI_PILL_Y1 30
#define GAUGE_RENDER_AI_SET_X0 166
#define GAUGE_RENDER_AI_SET_Y0 4
#define GAUGE_RENDER_AI_SET_X1 201
#define GAUGE_RENDER_AI_SET_Y1 30
#define GAUGE_RENDER_AI_HELP_X0 277
#define GAUGE_RENDER_AI_HELP_Y0 4
#define GAUGE_RENDER_AI_HELP_X1 313
#define GAUGE_RENDER_AI_HELP_Y1 30
#define GAUGE_RENDER_PROFILE_X0 351
#define GAUGE_RENDER_PROFILE_Y0 286
#define GAUGE_RENDER_PROFILE_X1 479
#define GAUGE_RENDER_PROFILE_Y1 318
#define GAUGE_RENDER_SET_PANEL_X0 40
#define GAUGE_RENDER_SET_PANEL_Y0 32
#define GAUGE_RENDER_SET_PANEL_X1 440
#define GAUGE_RENDER_SET_PANEL_Y1 214
#define GAUGE_RENDER_SET_MODE_X0 150
#define GAUGE_RENDER_SET_MODE_Y0 94
#define GAUGE_RENDER_SET_MODE_W 54
#define GAUGE_RENDER_SET_MODE_H 24
#define GAUGE_RENDER_SET_MODE_GAP 12
#define GAUGE_RENDER_SET_TUNE_X0 110
#define GAUGE_RENDER_SET_TUNE_Y0 138
#define GAUGE_RENDER_SET_TUNE_W 80
#define GAUGE_RENDER_SET_TUNE_H 24
#define GAUGE_RENDER_SET_TUNE_GAP 10
#define GAUGE_RENDER_SET_AI_X0 130
#define GAUGE_RENDER_SET_AI_Y0 170
#define GAUGE_RENDER_SET_AI_W 98
#define GAUGE_RENDER_SET_AI_H 24
#define GAUGE_RENDER_SET_AI_GAP 12
#define GAUGE_RENDER_HELP_PANEL_X0 32
#define GAUGE_RENDER_HELP_PANEL_Y0 24
#define GAUGE_RENDER_HELP_PANEL_X1 448
#define GAUGE_RENDER_HELP_PANEL_Y1 236

bool GaugeRender_Init(void);
void GaugeRender_DrawFrame(const power_sample_t *sample, bool ai_enabled, power_replay_profile_t profile);
void GaugeRender_SetAccel(int16_t ax_mg, int16_t ay_mg, int16_t az_mg, bool valid);
void GaugeRender_SetLinearAccel(int16_t ax_mg, int16_t ay_mg, int16_t az_mg, bool valid);
void GaugeRender_SetMag(int16_t mx_mgauss, int16_t my_mgauss, int16_t mz_mgauss, bool valid);
void GaugeRender_SetBaro(int16_t pressure_dhpa, bool valid);
void GaugeRender_SetSht(int16_t temp_c10, int16_t rh_dpct, bool valid);
void GaugeRender_SetStts(int16_t temp_c10, bool valid);
void GaugeRender_SetBoardTempC(uint8_t temp_c, bool valid);
void GaugeRender_SetBoardTempC10(int16_t temp_c10, bool valid);
void GaugeRender_SetRuntimeClock(uint8_t hh, uint8_t mm, uint8_t ss, uint8_t ds, bool valid);
void GaugeRender_SetAnomalyInfo(uint8_t mode,
                                uint8_t tune,
                                bool training_active,
                                bool trained_ready,
                                uint8_t level_ax,
                                uint8_t level_ay,
                                uint8_t level_az,
                                uint8_t level_temp,
                                uint8_t overall_level);
void GaugeRender_SetHelpVisible(bool visible);
void GaugeRender_SetSettingsVisible(bool visible);
void GaugeRender_SetLiveBannerMode(bool enabled);
bool GaugeRender_IsLiveBannerMode(void);
void GaugeRender_DrawGyroFast(void);
bool GaugeRender_HandleTouch(int32_t x, int32_t y, bool pressed);
uint8_t GaugeRender_GetTimelineHour(void);
bool GaugeRender_IsRecordMode(void);
void GaugeRender_SetPlayhead(uint8_t position_0_to_99, bool valid);
void GaugeRender_SetRecordMode(bool record_mode);
bool GaugeRender_IsRecordConfirmActive(void);
bool GaugeRender_ConsumeRecordStartRequest(void);

#endif

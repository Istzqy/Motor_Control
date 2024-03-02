/**
 ****************************************************************************************************
 * @file        lv_mainstart.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-04-01
 * @brief       LVGL lv_btn(按钮) 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 北极星 H750开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */
 
#include "LVGL/GUI_APP/lv_mainstart.h"
#include "lvgl.h"
#include <stdio.h>
#include "./BSP/TIMER/atim.h"
#include "lvgl_demo.h"

extern volatile uint8_t Axis_Switch;

#if (1 != LV_FONT_MONTSERRAT_10 || 1 != LV_FONT_MONTSERRAT_14 || 1 != LV_FONT_MONTSERRAT_20)
    #error Please Make Sure Enable LV_FONT_MONTSERRAT_10 & LV_FONT_MONTSERRAT_14 & LV_FONT_MONTSERRAT_20
#endif

static const lv_font_t* font;       /* 定义字体 */

static lv_obj_t *label_axis;       	/* 当前轴向提示文本 */
static lv_obj_t *label_xPulse;      /* x轴输出脉冲数 */
static lv_obj_t *label_yPulse;      /* x轴输出脉冲数 */
static lv_obj_t *label_zPulse;      /* x轴输出脉冲数 */
static lv_obj_t *btn_x_right;      	/* X轴PWM+输出按钮 */
static lv_obj_t *btn_x_left;      	/* X轴PWM-输出按钮 */
static lv_obj_t *btn_y_right;    	/* Y轴PWM+输出按钮 */
static lv_obj_t *btn_y_left;    	/* Y轴PWM-输出按钮 */
static lv_obj_t *btn_z_right;       /* Z轴PWM+输出按钮 */
static lv_obj_t *btn_z_left;        /* Z轴PWM-输出按钮 */


volatile int32_t X_Pulseout = 0;       /* X轴输出脉冲数 */
volatile int32_t Y_Pulseout = 0;       /* Y轴输出脉冲数 */
volatile int32_t Z_Pulseout = 0;       /* Z轴输出脉冲数 */

/* 获取当前活动屏幕的宽高 */
#define scr_act_width() lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act())


/**
 * @brief  按钮回调
 * @param  *e ：事件相关参数的集合，它包含了该事件的所有数据
 * @return 无
 */
static void btn_event_cb(lv_event_t * e)
{
    lv_obj_t *target = lv_event_get_target(e);      /* 获取触发源 */
	uint8_t temp;
    if(target == btn_x_right || target == btn_x_left)                      /* X轴PWM输出按钮 */
    {
		if(target == btn_x_right)
		{
			Axis_Switch = X_Axis_Right;
			temp = X_Axis_Right;			
		}
        else
		{
			Axis_Switch = X_Axis_Left;
			temp = X_Axis_Left;	
		}

    }
    else if(target == btn_y_right || target == btn_y_left)               /* Y轴PWM输出按钮 */
    {
        if(target == btn_y_right)
		{
			Axis_Switch = Y_Axis_Right;
			temp = Y_Axis_Right;			
		}
        else
		{
			Axis_Switch = Y_Axis_Left;
			temp = Y_Axis_Left;	
		}
    }
    else if(target == btn_z_right || target == btn_z_left)              /* Z轴PWM输出按钮 */
    {
        if(target == btn_z_right)
		{
			Axis_Switch = Z_Axis_Right;
			temp = Z_Axis_Right;			
		}
        else
		{
			Axis_Switch = Z_Axis_Left;
			temp = Z_Axis_Left;	
		}
    }
	if(temp != 0)
		{
			switch (temp)
            {
                case X_Axis_Right:                                         /* 修改屏幕标签值 */
                {
					lv_label_set_text_fmt(label_axis, "Axis : X");
					lv_label_set_text_fmt(label_xPulse, "X Pulse Out : %d ", ++X_Pulseout);    /* 更新X轴输出脉冲 */
                    break;
                }
				case X_Axis_Left:                                         /* 修改屏幕标签值 */
                {
					lv_label_set_text_fmt(label_axis, "Axis : X");
					lv_label_set_text_fmt(label_xPulse, "X Pulse Out : %d ", --X_Pulseout);    /* 更新X轴输出脉冲 */
                    break;
                }
				case Y_Axis_Right:
				{
					lv_label_set_text_fmt(label_axis, "Axis : Y");
					lv_label_set_text_fmt(label_yPulse, "Y Pulse Out : %d ", ++Y_Pulseout);    /* 更新Y轴输出脉冲 */
                    break;
				}
				case Y_Axis_Left:
				{
					lv_label_set_text_fmt(label_axis, "Axis : Y");
					lv_label_set_text_fmt(label_yPulse, "Y Pulse Out : %d ", --Y_Pulseout);    /* 更新Y轴输出脉冲 */
                    break;
				}
				case Z_Axis_Right:
				{
					lv_label_set_text_fmt(label_axis, "Axis : Z");
					lv_label_set_text_fmt(label_zPulse, "Z Pulse Out : %d ", ++Z_Pulseout);    /* 更新Z轴输出脉冲 */
					break;
				}
				case Z_Axis_Left:
				{
					lv_label_set_text_fmt(label_axis, "Axis : Z");
					lv_label_set_text_fmt(label_zPulse, "Z Pulse Out : %d ", --Z_Pulseout);    /* 更新Z轴输出脉冲 */
					break;
				}
                default:
                {
                    break;
                }
            }
		}
    //lv_label_set_text_fmt(label_axis, "Axis : %d RPM", speed_val);    /* 更新速度值 */
}


/**
 * @brief  轴向提示标签
 * @param  无
 * @return 无
 */
static void lv_example_label(void)
{
    /* 根据活动屏幕宽度选择字体 */
    if (scr_act_width() <= 320)
    {
        font = &lv_font_montserrat_10;
    }
    else if (scr_act_width() <= 480)
    {
        font = &lv_font_montserrat_14;
    }
    else
    {
        font = &lv_font_montserrat_20;
    }

    label_axis = lv_label_create(lv_scr_act());                                    	/* 创建速度显示标签 */
	label_xPulse = lv_label_create(lv_scr_act());									/* 创建脉冲输出数标签 */
	label_yPulse = lv_label_create(lv_scr_act());									/* 创建脉冲输出数标签 */
	label_zPulse = lv_label_create(lv_scr_act());									/* 创建脉冲输出数标签 */
    lv_obj_set_style_text_font(label_axis, &lv_font_montserrat_22, LV_PART_MAIN);   /* 设置字体 */
	lv_obj_set_style_text_font(label_xPulse, font, LV_PART_MAIN);                   /* 设置字体 */
	lv_obj_set_style_text_font(label_yPulse, font, LV_PART_MAIN);                   /* 设置字体 */
	lv_obj_set_style_text_font(label_zPulse, font, LV_PART_MAIN);                   /* 设置字体 */
    lv_label_set_text(label_axis, "Axis :    ");									/* 设置标签内容 */
	lv_label_set_text(label_xPulse, "X Pulse Out :    ");
	lv_label_set_text(label_yPulse, "Y Pulse Out :    ");
	lv_label_set_text(label_zPulse, "Z Pulse Out :    ");
	lv_obj_align(label_axis, LV_ALIGN_CENTER, 0, -scr_act_height() / 3);           /* 设置标签位置 */
	lv_obj_align(label_xPulse, LV_ALIGN_CENTER, -scr_act_width() / 3, -scr_act_height() / 6);
	lv_obj_align(label_yPulse, LV_ALIGN_CENTER, 0, -scr_act_height() / 6);
	lv_obj_align(label_zPulse, LV_ALIGN_CENTER, scr_act_width() / 3, -scr_act_height() / 6);
	
}
/**
 * @brief  加速按钮
 * @param  无
 * @return 无
 */
static void lv_example_btn_x_axis(void)
{
    btn_x_right = lv_btn_create(lv_scr_act());                                     /* 创建X右转按钮 */
    lv_obj_set_size(btn_x_right, scr_act_width() / 4, scr_act_height() / 6);       /* 设置按钮大小 */
    lv_obj_align(btn_x_right, LV_ALIGN_CENTER, -scr_act_width() / 3, 0);           /* 设置按钮位置 */
    lv_obj_add_event_cb(btn_x_right, btn_event_cb, LV_EVENT_CLICKED, NULL);        /* 设置按钮事件 */
	
	btn_x_left = lv_btn_create(lv_scr_act());                                      /* 创建X左转按钮 */
    lv_obj_set_size(btn_x_left, scr_act_width() / 4, scr_act_height() / 6);       /* 设置按钮大小 */
    lv_obj_align(btn_x_left, LV_ALIGN_CENTER, -scr_act_width() / 3, scr_act_height() / 4);            /* 设置按钮位置 */
    lv_obj_add_event_cb(btn_x_left, btn_event_cb, LV_EVENT_CLICKED, NULL);        /* 设置按钮事件 */

    lv_obj_t* label = lv_label_create(btn_x_right);                               /* 创建X左转标签 */
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);                        /* 设置字体 */
    lv_label_set_text(label, "X Axis Right");                                     /* 设置标签文本 */
    lv_obj_set_align(label,LV_ALIGN_CENTER);                                      /* 设置标签位置 */
	
	lv_obj_t* label1 = lv_label_create(btn_x_left);                               /* 创建X左转标签 */
    lv_obj_set_style_text_font(label1, font, LV_PART_MAIN);                        /* 设置字体 */
    lv_label_set_text(label1, "X Axis Left");                                     /* 设置标签文本 */
    lv_obj_set_align(label1,LV_ALIGN_CENTER);                                      /* 设置标签位置 */
}

/**
 * @brief  减速按钮
 * @param  无
 * @return 无
 */
static void lv_example_btn_y_axis(void)
{
    btn_y_right = lv_btn_create(lv_scr_act());                                   /* 创建加速按钮 */
    lv_obj_set_size(btn_y_right, scr_act_width() / 4, scr_act_height() / 6);     /* 设置按钮大小 */
    lv_obj_align(btn_y_right, LV_ALIGN_CENTER, 0, 0);                            /* 设置按钮位置 */
    lv_obj_add_event_cb(btn_y_right, btn_event_cb, LV_EVENT_CLICKED, NULL);      /* 设置按钮事件 */
	
	btn_y_left = lv_btn_create(lv_scr_act());                                     /* 创建Y左转按钮 */
    lv_obj_set_size(btn_y_left, scr_act_width() / 4, scr_act_height() / 6);       /* 设置按钮大小 */
    lv_obj_align(btn_y_left, LV_ALIGN_CENTER, 0, scr_act_height() / 4);           /* 设置按钮位置 */
    lv_obj_add_event_cb(btn_y_left, btn_event_cb, LV_EVENT_CLICKED, NULL);        /* 设置按钮事件 */

    lv_obj_t* label = lv_label_create(btn_y_right);                              /* 创建Y右转标签 */
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);                       /* 设置字体 */
    lv_label_set_text(label, "Y Axis Right");                                    /* 设置标签文本 */
    lv_obj_set_align(label,LV_ALIGN_CENTER);                                     /* 设置标签位置 */
	
	lv_obj_t* label1 = lv_label_create(btn_y_left);                               /* 创建Y左转标签 */
    lv_obj_set_style_text_font(label1, font, LV_PART_MAIN);                       /* 设置字体 */
    lv_label_set_text(label1, "Y Axis Left");                                     /* 设置标签文本 */
    lv_obj_set_align(label1,LV_ALIGN_CENTER);                                     /* 设置标签位置 */
}

/**
 * @brief  急停按钮
 * @param  无
 * @return 无
 */
static void lv_example_btn_z_axis(void)
{
    btn_z_right = lv_btn_create(lv_scr_act());                                         /* 创建急停按钮 */
    lv_obj_set_size(btn_z_right, scr_act_width() / 4, scr_act_height() / 6);           /* 设置按钮大小 */
    lv_obj_align(btn_z_right, LV_ALIGN_CENTER, scr_act_width() / 3, 0);                /* 设置按钮位置 */
//    lv_obj_set_style_bg_color(btn_z_right, lv_color_hex(0xef5f60), LV_STATE_DEFAULT);  /* 设置按钮背景颜色（默认） */
//    lv_obj_set_style_bg_color(btn_z_right, lv_color_hex(0xff0000), LV_STATE_PRESSED);  /* 设置按钮背景颜色（按下） */
    lv_obj_add_event_cb(btn_z_right, btn_event_cb, LV_EVENT_CLICKED, NULL);            /* 设置按钮事件 */

	btn_z_left = lv_btn_create(lv_scr_act());                                         /* 创建急停按钮 */
    lv_obj_set_size(btn_z_left, scr_act_width() / 4, scr_act_height() / 6);           /* 设置按钮大小 */
    lv_obj_align(btn_z_left, LV_ALIGN_CENTER, scr_act_width() / 3, scr_act_height() / 4);                /* 设置按钮位置 */
    lv_obj_add_event_cb(btn_z_left, btn_event_cb, LV_EVENT_CLICKED, NULL);            /* 设置按钮事件 */
	
    lv_obj_t* label = lv_label_create(btn_z_right);                                 /* 创建Z右标签 */
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);                          /* 设置字体 */
    lv_label_set_text(label, "Z Axis Right");                                       /* 设置标签文本 */
    lv_obj_set_align(label,LV_ALIGN_CENTER);                                        /* 设置标签位置 */
	
	lv_obj_t* label1 = lv_label_create(btn_z_left);                               /* 创建Z左转标签 */
    lv_obj_set_style_text_font(label1, font, LV_PART_MAIN);                       /* 设置字体 */
    lv_label_set_text(label1, "Z Axis Left");                                     /* 设置标签文本 */
    lv_obj_set_align(label1,LV_ALIGN_CENTER);                                     /* 设置标签位置 */
}

/**
 * @brief  LVGL演示
 * @param  无
 * @return 无
 */
void lv_mainstart(void)
{
    lv_example_label();             /* 速度提示标签 */
    lv_example_btn_x_axis();            /* 加速按钮 */
    lv_example_btn_y_axis();          /* 减速按钮 */
    lv_example_btn_z_axis();          /* 急停按钮 */
}


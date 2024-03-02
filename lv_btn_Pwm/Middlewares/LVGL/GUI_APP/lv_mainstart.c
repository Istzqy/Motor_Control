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

static lv_obj_t *label_axis;       	/* 速度提示文本 */
static lv_obj_t *btn_x_axis;      	/* X轴PWM输出按钮 */
static lv_obj_t *btn_y_axis;    	/* Y轴PWM输出按钮 */
static lv_obj_t *btn_z_axis;        /* Z轴PWM输出按钮 */

//static int32_t speed_val = 0;       /* 速度值 */

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
    if(target == btn_x_axis)                      /* X轴PWM输出按钮 */
    {
        Axis_Switch = X_Axis;
		temp = X_Axis;
    }
    else if(target == btn_y_axis)               /* Y轴PWM输出按钮 */
    {
        Axis_Switch = Y_Axis;
		temp = Y_Axis;
    }
    else if(target == btn_z_axis)              /* Z轴PWM输出按钮 */
    {
        Axis_Switch = Z_Axis;
		temp = Z_Axis;
    }
	if(temp != 0)
		{
			switch (temp)
            {
                case X_Axis:                                         /* 修改屏幕标签值 */
                {
					lv_label_set_text_fmt(label_axis, "Axis : X");
                    break;
                }
				case Y_Axis:
				{
					lv_label_set_text_fmt(label_axis, "Axis : Y");
                    break;
				}
				case Z_Axis:
				{
					lv_label_set_text_fmt(label_axis, "Axis : Z");
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

    label_axis = lv_label_create(lv_scr_act());                                    /* 创建速度显示标签 */
    lv_obj_set_style_text_font(label_axis, font, LV_PART_MAIN);                    /* 设置字体 */
    //lv_label_set_text(label_axis, "Speed : 0 RPM");                              /* 设置文本 */
    lv_label_set_text(label_axis, "Axis :    ");
	lv_obj_align(label_axis, LV_ALIGN_CENTER, 0, -scr_act_height() / 3);           /* 设置标签位置 */
}
/**
 * @brief  加速按钮
 * @param  无
 * @return 无
 */
static void lv_example_btn_x_axis(void)
{
    btn_x_axis = lv_btn_create(lv_scr_act());                                     /* 创建加速按钮 */
    lv_obj_set_size(btn_x_axis, scr_act_width() / 4, scr_act_height() / 6);       /* 设置按钮大小 */
    lv_obj_align(btn_x_axis, LV_ALIGN_CENTER, -scr_act_width() / 3, 0);           /* 设置按钮位置 */
    lv_obj_add_event_cb(btn_x_axis, btn_event_cb, LV_EVENT_CLICKED, NULL);        /* 设置按钮事件 */

    lv_obj_t* label = lv_label_create(btn_x_axis);                                /* 创建加速按钮标签 */
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);                        /* 设置字体 */
    lv_label_set_text(label, "X Axis");                                           /* 设置标签文本 */
    lv_obj_set_align(label,LV_ALIGN_CENTER);                                      /* 设置标签位置 */
}

/**
 * @brief  减速按钮
 * @param  无
 * @return 无
 */
static void lv_example_btn_y_axis(void)
{
    btn_y_axis = lv_btn_create(lv_scr_act());                                   /* 创建加速按钮 */
    lv_obj_set_size(btn_y_axis, scr_act_width() / 4, scr_act_height() / 6);     /* 设置按钮大小 */
    lv_obj_align(btn_y_axis, LV_ALIGN_CENTER, 0, 0);                            /* 设置按钮位置 */
    lv_obj_add_event_cb(btn_y_axis, btn_event_cb, LV_EVENT_CLICKED, NULL);      /* 设置按钮事件 */

    lv_obj_t* label = lv_label_create(btn_y_axis);                              /* 创建减速按钮标签 */
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);                          /* 设置字体 */
    lv_label_set_text(label, "Y Axis");                                            /* 设置标签文本 */
    lv_obj_set_align(label,LV_ALIGN_CENTER);                                        /* 设置标签位置 */
}

/**
 * @brief  急停按钮
 * @param  无
 * @return 无
 */
static void lv_example_btn_z_axis(void)
{
    btn_z_axis = lv_btn_create(lv_scr_act());                                         /* 创建急停按钮 */
    lv_obj_set_size(btn_z_axis, scr_act_width() / 4, scr_act_height() / 6);           /* 设置按钮大小 */
    lv_obj_align(btn_z_axis, LV_ALIGN_CENTER, scr_act_width() / 3, 0);                /* 设置按钮位置 */
    lv_obj_set_style_bg_color(btn_z_axis, lv_color_hex(0xef5f60), LV_STATE_DEFAULT);  /* 设置按钮背景颜色（默认） */
    lv_obj_set_style_bg_color(btn_z_axis, lv_color_hex(0xff0000), LV_STATE_PRESSED);  /* 设置按钮背景颜色（按下） */
    lv_obj_add_event_cb(btn_z_axis, btn_event_cb, LV_EVENT_CLICKED, NULL);            /* 设置按钮事件 */

    lv_obj_t* label = lv_label_create(btn_z_axis);                                    /* 创建急停按钮标签 */
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);                          /* 设置字体 */
    lv_label_set_text(label, "Z Axis");                                               /* 设置标签文本 */
    lv_obj_set_align(label,LV_ALIGN_CENTER);                                        /* 设置标签位置 */
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


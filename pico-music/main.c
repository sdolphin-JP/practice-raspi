/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "tone.h"

#define GPIO_PIN_INPUT  (19)
#define GPIO_PIN_OUTPUT (27)
#define GPIO_PIN_STATUS (PICO_DEFAULT_LED_PIN)

#define LED_DELAY_MS    (250)

// 「エリーゼのために」メロディの一部
static noteInfo_t elise[] =
{
    { NOTE_E5, 250 }, { NOTE_DS5, 250 }, { NOTE_E5, 250 }, { NOTE_DS5, 250 },
    { NOTE_E5, 250 }, { NOTE_B4, 250 }, { NOTE_D5, 250 }, { NOTE_C5, 250 },
    { NOTE_A4, 500 },
    { 0, 250 },

    { NOTE_C4, 250 }, { NOTE_E4, 250 }, { NOTE_A4, 250 }, { NOTE_B4, 500 },
    { 0, 250 },

    { NOTE_E4, 250 }, { NOTE_GS4, 250 }, { NOTE_B4, 250 }, { NOTE_C5, 500 },
    { 0, 250 },

    { NOTE_E5, 250 }, { NOTE_DS5, 250 }, { NOTE_E5, 250 }, { NOTE_DS5, 250 },
    { NOTE_E5, 250 }, { NOTE_B4, 250 }, { NOTE_D5, 250 }, { NOTE_C5, 250 },
    { NOTE_A4, 500 },
    { 0, 250 },

    { NOTE_C4, 250 }, { NOTE_E4, 250 }, { NOTE_A4, 250 }, { NOTE_B4, 500 },
    { 0, 250 },

    { NOTE_E4, 250 }, { NOTE_C5, 250 }, { NOTE_B4, 500 }, { NOTE_A4, 500 },
    { 0, 0 }
};

// 「メヌエット」メロディの一部
static noteInfo_t menuet[] =
{
    { NOTE_D6, 500 }, { NOTE_G5, 250 }, { NOTE_A5, 250 }, { NOTE_B5, 250 },
    { NOTE_C6, 250 }, { NOTE_D6, 500 }, { NOTE_G5, 250 }, { 0, 250 },
    { NOTE_G5, 500 },
    { 0, 250 },

    { NOTE_E6, 500 }, { NOTE_C6, 250 }, { NOTE_D6, 250 }, { NOTE_E6, 250 },
    { NOTE_F6, 250 }, { NOTE_G6, 500 }, { NOTE_G5, 250 }, { 0, 250 },
    { NOTE_G5, 500 },
    { 0, 250 },

    { NOTE_C6, 500 }, { NOTE_D6, 250 }, { NOTE_C6, 250 }, { NOTE_B5, 250 },
    { NOTE_A5, 250 }, { NOTE_B5, 500 },
    { NOTE_C6, 250 }, { NOTE_B5, 250 }, { NOTE_A5, 250 }, { NOTE_G5, 250 },
    { NOTE_F5, 500 },
    { NOTE_G5, 250 }, { NOTE_A5, 250 }, { NOTE_B5, 250 }, { NOTE_G5, 250 },
    { NOTE_A5, 1000 },

    { 0, 0 }
};

// テトリス
static noteInfo_t tetris[] =
{
    { NOTE_E5, 500 }, { NOTE_B4, 250 }, { NOTE_C5, 250 }, { NOTE_D5, 500 },
    { NOTE_C5, 250 }, { NOTE_B4, 250 }, { NOTE_A4, 500 }, { 0, 50 }, { NOTE_A4, 250 }, { NOTE_C5, 250 }, { NOTE_E5, 500 },
    { NOTE_D5, 250 }, { NOTE_C5, 250 }, { NOTE_B4, 500 }, { 0, 50 }, { NOTE_C5, 250 }, { NOTE_D5, 250 }, { NOTE_E5, 250 },
    { NOTE_C5, 500 }, { NOTE_A4, 500 }, { 0, 50 }, { NOTE_A4, 500 },
    { 0, 250 },

    { NOTE_D5, 500 }, { NOTE_F5, 250 }, { NOTE_A5, 500 }, { NOTE_G5, 250 }, { NOTE_F5, 250 }, { NOTE_E5, 500 }, { 0, 50 },
    { NOTE_C5, 250 }, { NOTE_E5, 500 }, { NOTE_D5, 250 }, { NOTE_C5, 300 }, { NOTE_B4, 500 }, { 0, 50 },
    { NOTE_B4, 250 }, { NOTE_C5, 500 }, { NOTE_D5, 500 },
    { NOTE_E5, 500 }, { NOTE_C5, 500 }, { NOTE_A4, 500 }, { 0, 50 }, { NOTE_A4, 500 },

    { 0, 0 }
};

// GPIOの初期化
static void init_gpio(void)
{
    // 本体LED用の出力設定
    gpio_init(GPIO_PIN_STATUS);
    gpio_set_dir(GPIO_PIN_STATUS, GPIO_OUT);
    gpio_put(GPIO_PIN_STATUS, 0);

    // ボタン用の入力設定
    gpio_init(GPIO_PIN_INPUT);
    gpio_set_dir(GPIO_PIN_INPUT, GPIO_IN);
    gpio_pull_up(GPIO_PIN_INPUT);

    // スピーカー用の出力設定
    gpio_init(GPIO_PIN_OUTPUT);
    gpio_set_dir(GPIO_PIN_OUTPUT, GPIO_OUT);
    gpio_put(GPIO_PIN_OUTPUT, 0);
    gpio_set_function(GPIO_PIN_OUTPUT, GPIO_FUNC_PWM);
}

// サウンドの再生
static void play_note(unsigned int slice_num, noteInfo_t* pNotes)
{
    // 良くないループのやり方だがこれでやる
    for (noteInfo_t* p = pNotes; NULL != p; p++)
    {
        if (0 != p->tone)
        {
            // Picoのクロック周波数(125MHz)
            unsigned int clock = 125000000;
            // 分周比を計算する
            unsigned int divider16 = clock / (p->tone * 4096) + ((clock % (p->tone * 4096) != 0) ? 1 : 0);
            // 最小値は16
            divider16 = (divider16 < 16) ? 16 : divider16;
            // PWMカウント範囲を求める
            unsigned int wrap = (((clock * 16) / divider16) / p->tone) - 1;

            // 再生開始
            pwm_set_clkdiv_int_frac(slice_num, divider16 / 16, divider16 & 0xF);
            pwm_set_wrap(slice_num, wrap);
            pwm_set_gpio_level(GPIO_PIN_OUTPUT, wrap / 2);
            pwm_set_enabled(slice_num, true);
        }

        else
        {
            // どちらもゼロなら終わり
            if (0 == p->duration)
            {
                break;
            }

            pwm_set_enabled(slice_num, false);
        }

        sleep_ms(p->duration);
    }

    pwm_set_enabled(slice_num, false);
}

// メインルーチーン
int main(void)
{
    unsigned int statusLed = 0;
    unsigned int statusCnt = 0;
    unsigned int buttonCnt = 0;
    unsigned int slice_num = 0;
    unsigned int musicCnt  = 0;
    noteInfo_t*  musics[]  =
    {
        menuet,
        elise,
        tetris
    };

    // GPIOの初期化
    init_gpio();
    slice_num = pwm_gpio_to_slice_num(GPIO_PIN_OUTPUT);

    while (true)
    {
        sleep_ms(4);

        // 押されている間カウントアップ
        buttonCnt = (0 == gpio_get(GPIO_PIN_INPUT)) ? (buttonCnt + 1) : 0;

        // 一定期間押し続けられたら再生
        if (5 <= buttonCnt)
        {
            gpio_put(GPIO_PIN_STATUS, 1);
            play_note(slice_num, musics[musicCnt]);
            gpio_put(GPIO_PIN_STATUS, 0);
            buttonCnt = 0;
            statusCnt = 0;

            // 押下ごとにBGMを変える
            musicCnt = (musicCnt + 1) % (sizeof(musics) / sizeof(noteInfo_t*));
        }

        // 動いていることがわかるように点滅させる
        statusCnt++;
        if (125 <= statusCnt)
        {
            statusLed = (0 == statusLed) ? 1 : 0;
            gpio_put(GPIO_PIN_STATUS, statusLed);
            statusCnt = 0;
        }
    }

    // 異常発生
    hard_assert(0);
}

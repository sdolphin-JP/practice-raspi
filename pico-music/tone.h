#ifndef __TONE_H__
#define __TONE_H__

// 4オクターブ
#define NOTE_C4   262   // ド4
#define NOTE_CS4  277   // ド#4 / レb4
#define NOTE_D4   294   // レ4
#define NOTE_DS4  311   // レ#4 / ミb4
#define NOTE_E4   330   // ミ4
#define NOTE_F4   349   // ファ4
#define NOTE_FS4  370   // ファ#4 / ソb4
#define NOTE_G4   392   // ソ4
#define NOTE_GS4  415   // ソ#4 / ラb4
#define NOTE_A4   440   // ラ4
#define NOTE_AS4  466   // ラ#4 / シb4
#define NOTE_B4   494   // シ4

// 5オクターブ
#define NOTE_C5   523   // ド5
#define NOTE_CS5  554   // ド#5 / レb5
#define NOTE_D5   587   // レ5
#define NOTE_DS5  622   // レ#5 / ミb5
#define NOTE_E5   659   // ミ5
#define NOTE_F5   698   // ファ5
#define NOTE_FS5  740   // ファ#5 / ソb5
#define NOTE_G5   784   // ソ5
#define NOTE_GS5  831   // ソ#5 / ラb5
#define NOTE_A5   880   // ラ5
#define NOTE_AS5  932   // ラ#5 / シb5
#define NOTE_B5   988   // シ5

// 6オクターブ
#define NOTE_C6   1047  // ド6
#define NOTE_CS6  1109  // ド#6 / レb6
#define NOTE_D6   1175  // レ6
#define NOTE_DS6  1245  // レ#6 / ミb6
#define NOTE_E6   1319  // ミ6
#define NOTE_F6   1397  // ファ6
#define NOTE_FS6  1480  // ファ#6 / ソb6
#define NOTE_G6   1568  // ソ6
#define NOTE_GS6  1661  // ソ#6 / ラb6
#define NOTE_A6   1760  // ラ6
#define NOTE_AS6  1865  // ラ#6 / シb6
#define NOTE_B6   1976  // シ6

// 7オクターブ
#define NOTE_C7   2093  // ド7
#define NOTE_CS7  2217  // ド#7 / レb7
#define NOTE_D7   2349  // レ7
#define NOTE_DS7  2489  // レ#7 / ミb7
#define NOTE_E7   2637  // ミ7
#define NOTE_F7   2794  // ファ7
#define NOTE_FS7  2960  // ファ#7 / ソb7
#define NOTE_G7   3136  // ソ7
#define NOTE_GS7  3322  // ソ#7 / ラb7
#define NOTE_A7   3520  // ラ7
#define NOTE_AS7  3729  // ラ#7 / シb7
#define NOTE_B7   3951  // シ7

typedef struct
{
    // 周波数
    unsigned int tone;
    // 長さ
    unsigned int duration;

} noteInfo_t;

#endif

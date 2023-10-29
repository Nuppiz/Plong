#include "Incl_std.h"
#define PIT_FREQ    0x1234DD /* programmable interveral timer (PIT) frequency for PC speaker */

/* PC Speaker sound effects */

void initSpeaker()
{
    outportb(0x61, inportb(0x61) | 3);
    outportb(0x43, 0xB6);
}

void closeSpeaker()
{
    outportb(0x61, inportb(0x61) & (~3));
    outportb(0x43, 0x00);
}

void playNote(int freq, int note_length)
{
    int counter;

    initSpeaker();

    counter = (PIT_FREQ / freq); // calculate frequency
    outportb(0x42, counter & 0xff); // LSB
    outportb(0x42, counter >> 8); // MSB
    delay(note_length); // wait for a bit

    closeSpeaker();
}

void hitSound()
{
    static uint8_t effect_id = 0;

    if (effect_id == 0)
    {
        playNote (450, 2000);
        effect_id = 1;
    }
    else
    {
        playNote (225, 2000);
        effect_id = 0;
    }
}

void scoreSound()
{
    initSpeaker();
    playNote(523, 8000);
    playNote(392, 8000);
    playNote(1047, 4000);
    delay(2000);
    playNote(1047, 4000);
    closeSpeaker();
}

void endMusic()
{
    initSpeaker();
    playNote(600, 12000);
    playNote(800, 12000);
    playNote(800, 12000);
    playNote(1200, 12000);
    playNote(600, 12000);
    playNote(1200, 30000);
    closeSpeaker();
}
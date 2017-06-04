# Tuturu ascii art

## Description

Animates Mayuri from Steins;gate in terminal, in handmade ascii art, saying her famous "tuturu" catchphrase.

The display is made through ncurses and the sound through pulseaudio.

The voice is that of the very popular seiyū Kana Hanazawa, and is stored in FLAC in src/raw_sound.h, so that the executable is independant from any external file.

I do NOT own the copyright on that 1.4s track.

Rest of the code is licensed under MIT license.

## Compile and run

You need at least ncurses to run it properly, and optionnally flac, pthreads and pulseaudio.

### With sound support :
```
git clone https://github.com/ch0c0pain/tuturu
cd tuturu
make
build/tuturu
```

### Without sound support :
```
git clone https://github.com/ch0c0pain/tuturu
cd tuturu
make nosound
build/tuturu
```

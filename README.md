# Audio Spectrum Explorer

Determine the musical key and tempo (BPM) of your audio files with this project. Ideal for musicians, producers, and DJs looking for key insights on their tracks or creations.

## Features

- Retrieve the key of a song for Autotune settings.
- Retrieve the tempo (BPM)
- Graphic mode coming soon !

## Tech

- [C++](https://cplusplus.com/) : low-level langage
- [Aubio](https://aubio.org/) : a library for audio labelling


## Installation and Usage

This program requires [Aubio](https://aubio.org/).

apt :
```sh
sudo apt-get update
sudo apt-get install libaubio-dev libaubio-doc
```

dnf :
```
sudo dnf update
sudo dnf install libaubio-dev libaubio-doc
```

Build project and run
```
make
./AudioSpectrumExlorer input_file.wav
```

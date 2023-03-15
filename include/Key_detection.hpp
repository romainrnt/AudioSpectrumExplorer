/*******************************************/
/*                                         */
/*  AudioSpectrumExplorer Project          */
/*  File: <Key_detection.hpp>              */
/*  Author: romainrnt                      */
/*                                         */
/*******************************************/

#pragma once
#include <aubio/aubio.h>
#include <aubio/pitch/pitch.h>
#include <vector>
#include <map>
#include <string>

void initialize_pitch_detection(const char *input_path, aubio_source_t *&input_file, fvec_t *&input_buffer, fvec_t *&pitch, aubio_pitch_t *&pitch_detector);
float process_audio_buffer(aubio_source_t *input_file, fvec_t *input_buffer, fvec_t *pitch, aubio_pitch_t *pitch_detector, uint_t &read);
void cleanup_pitch_detection(aubio_source_t *input_file, fvec_t *input_buffer, fvec_t *pitch, aubio_pitch_t *pitch_detector);
int midi_to_note_index(float midi_value);
std::string key_from_histogram(const std::vector<int> &histogram);
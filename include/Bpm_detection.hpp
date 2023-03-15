/*******************************************/
/*                                         */
/*  AudioSpectrumExplorer Project          */
/*  File: <Bpm_detection.hpp>              */
/*  Author: romainrnt                      */
/*                                         */
/*******************************************/

#pragma once
#include <aubio/aubio.h>
#include <aubio/tempo/tempo.h>

void initialize_tempo_detection(aubio_tempo_t *&tempo_detector, uint_t buffer_size, uint_t hop_size, uint_t sample_rate);
float process_tempo_buffer(aubio_tempo_t *tempo_detector, fvec_t *input_buffer);
void cleanup_tempo_detection(aubio_tempo_t *tempo_detector);
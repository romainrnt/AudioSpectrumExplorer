/*******************************************/
/*                                         */
/*  AudioSpectrumExplorer Project          */
/*  File: <Bpm_detection.cpp>              */
/*  Author: romainrnt                      */
/*                                         */
/*******************************************/

#include "../include/Bpm_detection.hpp"

void initialize_tempo_detection(aubio_tempo_t *&tempo_detector, uint_t buffer_size, uint_t hop_size, uint_t sample_rate)
{
    tempo_detector = new_aubio_tempo("default", buffer_size, hop_size, sample_rate);
}

float process_tempo_buffer(aubio_tempo_t *tempo_detector, fvec_t *input_buffer)
{
    fvec_t *tempo_out = new_fvec(2);
    aubio_tempo_do(tempo_detector, input_buffer, tempo_out);
    float is_beat = fvec_get_sample(tempo_out, 0);
    float bpm = 0.0;

    if (is_beat)
        bpm = aubio_tempo_get_bpm(tempo_detector);
    del_fvec(tempo_out);
    return (bpm);
}

void cleanup_tempo_detection(aubio_tempo_t *tempo_detector)
{
    del_aubio_tempo(tempo_detector);
}

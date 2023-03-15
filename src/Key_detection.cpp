/*******************************************/
/*                                         */
/*  AudioSpectrumExplorer Project          */
/*  File: <Key_detection.cpp>              */
/*  Author: romainrnt                      */
/*                                         */
/*******************************************/

#include "../include/Exceptions.hpp"
#include "../include/Key_detection.hpp"
#include <stdexcept>
#include <string>

using namespace std;

void initialize_pitch_detection(const char *input_path, aubio_source_t *&input_file, fvec_t *&input_buffer, fvec_t *&pitch, aubio_pitch_t *&pitch_detector)
{
    uint_t buffer_size = 1024;
    uint_t hop_size = buffer_size / 4;

    input_file = new_aubio_source(input_path, 0, hop_size);
    if (input_file == nullptr)
        throw Error("Could not open input file: " + string(input_path));
    uint_t sample_rate = aubio_source_get_samplerate(input_file);
    input_buffer = new_fvec(hop_size);
    pitch = new_fvec(1);
    pitch_detector = new_aubio_pitch("default", buffer_size, hop_size, sample_rate);
    aubio_pitch_set_unit(pitch_detector, "midi");
}

float process_audio_buffer(aubio_source_t *input_file, fvec_t *input_buffer, fvec_t *pitch, aubio_pitch_t *pitch_detector, uint_t &read)
{
    aubio_source_do(input_file, input_buffer, &read);
    aubio_pitch_do(pitch_detector, input_buffer, pitch);
    float pitch_midi = fvec_get_sample(pitch, 0);
    return (pitch_midi);
}

void cleanup_pitch_detection(aubio_source_t *input_file, fvec_t *input_buffer, fvec_t *pitch, aubio_pitch_t *pitch_detector)
{
    del_aubio_source(input_file);
    del_fvec(input_buffer);
    del_fvec(pitch);
    del_aubio_pitch(pitch_detector);
}

int midi_to_note_index(float midi_value)
{
    int midi_integer = static_cast<int>(midi_value + 0.5);
    return (midi_integer % 12);
}

std::string key_from_histogram(const std::vector<int> &histogram)
{
    static const std::vector<std::string> key_names = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    int max_index = 0;
    int max_value = 0;

    for (int i = 0; i < 12; ++i) {
        if (histogram[i] > max_value) {
            max_value = histogram[i];
            max_index = i;
        }
    }
    return (key_names[max_index]);
}
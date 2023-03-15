/*******************************************/
/*                                         */
/*  AudioSpectrumExplorer Project          */
/*  File: <main.cpp>                       */
/*  Author: romainrnt                      */
/*                                         */
/*******************************************/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include "../include/Key_detection.hpp"
#include "../include/Bpm_detection.hpp"
#include "../include/Exceptions.hpp"

using namespace std;

bool print_error(int ac, char **av)
{
    if (ac < 2) {
        std::cerr << "Usage: " << av[0] << " <input_path>" << std::endl;
        return (true);
    }
    return (false);
}

int main(int ac, char **av)
{
    if (print_error(ac, av))
        return (1);
    const char *input_path = av[1];
    try {
        aubio_source_t *input_file;
        fvec_t *input_buffer;
        fvec_t *pitch;
        aubio_pitch_t *pitch_detector;
        initialize_pitch_detection(input_path, input_file, input_buffer, pitch, pitch_detector);
        aubio_tempo_t *tempo_detector;
        uint_t buffer_size = 1024;
        uint_t hop_size = buffer_size / 4;
        uint_t sample_rate = aubio_source_get_samplerate(input_file);
        initialize_tempo_detection(tempo_detector, buffer_size, hop_size, sample_rate);
        uint_t read = 0;
        vector<int> pitch_histogram(12, 0);
        vector<float> bpms;
        do {
            float detected_pitch_midi = process_audio_buffer(input_file, input_buffer, pitch, pitch_detector, read);
            if (detected_pitch_midi > 0) {
                int note_index = midi_to_note_index(detected_pitch_midi);
                pitch_histogram[note_index]++;
            }
            float bpm = process_tempo_buffer(tempo_detector, input_buffer);
            if (bpm > 0) {
                bpms.push_back(bpm);
            }
        } 
        while (read > 0);
        string key = key_from_histogram(pitch_histogram);
        cout << "Detected KEY: " << key << endl;
        float avg_bpm = 0;
        for (float bpm : bpms) {
            avg_bpm += bpm;
        }
        avg_bpm /= static_cast<float>(bpms.size());
        cout << "Detected BPM: " << avg_bpm << endl;
        cleanup_pitch_detection(input_file, input_buffer, pitch, pitch_detector);
        cleanup_tempo_detection(tempo_detector);
    }
    catch (Error &e) {
        std::cerr << "" << e.what() << std::endl;
        return (1);
    }
    return (0);
}

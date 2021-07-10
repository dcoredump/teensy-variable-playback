#ifndef TEENSYAUDIOLIBRARY_RESAMPLINGARRAYREADER_H
#define TEENSYAUDIOLIBRARY_RESAMPLINGARRAYREADER_H

#include "SD.h"
#include <cstdint>
#include <vector>
#include "loop_type.h"
#include "interpolation.h"

class ResamplingArrayReader {
public:
    ResamplingArrayReader() {

    }

    void begin(void);
    bool play(int16_t *array, uint32_t length);
    bool play();
    void stop(void);
    bool isPlaying(void) { return _playing; }

    unsigned int read(void **buf, uint16_t nbyte);
    bool readNextValue(int16_t *value, uint16_t channelNumber);

    void setPlaybackRate(double f) {
        _playbackRate = f;
        if (f < 0.0 && _bufferPosition == 0) {
            //_file.seek(_file_size);
            _bufferPosition = _file_size;
        }
    }

    float playbackRate() {
        return _playbackRate;
    }

    void setLoopType(loop_type loopType)
    {
        _loopType = loopType;
    }

    loop_type getLoopType(){
        return _loopType;    
    }

    int available(void);
    void reset(void);
    void close(void);

    void setLoopStart(uint32_t loop_start) {
        _loop_start = loop_start;
    }

    void setLoopFinish(uint32_t loop_finish) {
        // sample number, (NOT byte number)
        _loop_finish = loop_finish;
    }

    void setInterpolationType(ResampleInterpolationType interpolationType) {
        if (interpolationType != _interpolationType) {
            _interpolationType = interpolationType;
            initializeInterpolationPoints();
        }
    }

    void setNumChannels(uint16_t numChannels) {
        if (numChannels != _numChannels) {
            _numChannels = numChannels;
            initializeInterpolationPoints();
        }
    }

private:
    volatile bool _playing = false;

    int32_t _file_size;
    double _playbackRate = 1.0;
    double _remainder = 0.0;
    loop_type _loopType = looptype_none;
    int _bufferPosition = 0;
    int32_t _loop_start = 0;
    int32_t _loop_finish = 0;
    uint16_t _numChannels = 1;
    int16_t *_sourceBuffer;

    ResampleInterpolationType _interpolationType = ResampleInterpolationType::resampleinterpolation_none;
    unsigned int _numInterpolationPoints = 0;
    std::vector<IntepolationData *> _channelinterpolationPoints;
    void initializeInterpolationPoints(void);
    void deleteInterpolationPoints(void);
};


#endif //TEENSYAUDIOLIBRARY_RESAMPLINGARRAYREADER_H

#ifndef TEENSYAUDIOLIBRARY_RESAMPLINGARRAYREADER_H
#define TEENSYAUDIOLIBRARY_RESAMPLINGARRAYREADER_H

#include "SD.h"
#include <cstdint>
#include "loop_type.h"
#include "interpolation.h"

class ResamplingArrayReader {
public:
    ResamplingArrayReader() {
        _interpolationPoints[0].y = 0.0;
        _interpolationPoints[0].x = 0.0;
        _interpolationPoints[1].y = 0.0;
        _interpolationPoints[1].x = 1.0;
        _interpolationPoints[2].y = 0.0;
        _interpolationPoints[2].x = 2.0;
        _interpolationPoints[3].y = 0.0;
        _interpolationPoints[3].x = 3.0;
    }

    void begin(void);
    bool play(int16_t *array, uint32_t length);
    bool play();
    void stop(void);
    bool isPlaying(void) { return _playing; }

    unsigned int read(void *buf, uint16_t nbyte);
    bool readNextValue(int16_t *value);

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
        _interpolationType = interpolationType;
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

    int16_t *_sourceBuffer;

    ResampleInterpolationType _interpolationType = ResampleInterpolationType::resampleinterpolation_none;
    unsigned int _numInterpolationPoints = 0;
    IntepolationData _interpolationPoints[4];
};


#endif //TEENSYAUDIOLIBRARY_RESAMPLINGARRAYREADER_H

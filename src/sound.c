#include <stdio.h>
#include <stdlib.h>
#include <FLAC/stream_decoder.h>
#include <pulse/simple.h>

#include "sound.h"
#include "raw_sound.h"

struct bufData {
    int readPos;
    int size;
    FLAC__int32* data;
};

static FLAC__StreamDecoderWriteStatus writeclbk(const FLAC__StreamDecoder* s, const FLAC__Frame* frame,
                                         const FLAC__int32* const buffer[], void* data) {
    int i;
    struct bufData* buf = data;

    buf->data = realloc(buf->data, (buf->size + frame->header.blocksize) * sizeof(FLAC__int32));

    for (i = 0; i < frame->header.blocksize; i++) {
        buf->data[buf->size+i] = ((buffer[0][i] << 16) >> 16) + (buffer[1][i] << 16);
    }

    buf->size += frame->header.blocksize;
    return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

static FLAC__StreamDecoderReadStatus readclbk(const FLAC__StreamDecoder *decoder, FLAC__byte buffer[], size_t *bytes, void *data) {
    struct bufData* bufd = data;
    int i = 0;

    for (i = 0; bufd->readPos + i < tuturuFlacLen && i < *bytes; i++) {
        buffer[i] = tuturuFlac[bufd->readPos + i];
    }

    if (i != *bytes) {
        *bytes = i;
        return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
    }

    bufd->readPos += i;

    return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
}

static void errorclbk(const FLAC__StreamDecoder* s, FLAC__StreamDecoderErrorStatus status, void* data) {
    printf("Error decoding file\n");
}

void play_tuturu() {
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16NE,
        .rate = 48000,
        .channels = 2
    };
    FLAC__StreamDecoder* stream = FLAC__stream_decoder_new();
    int error;
    pa_simple* paServer = pa_simple_new(NULL, "tuturu", PA_STREAM_PLAYBACK,
                                        NULL, "playback", &ss, NULL, NULL, &error);
    struct bufData sndBuf = {0, 0, NULL};
    
    FLAC__stream_decoder_init_stream(stream, readclbk, NULL, NULL, NULL, NULL, writeclbk, NULL, errorclbk, &sndBuf);
    FLAC__stream_decoder_process_until_end_of_stream(stream);

    pa_simple_write(paServer, sndBuf.data, sndBuf.size * sizeof(FLAC__int32), &error);
    pa_simple_drain(paServer, &error);

    pa_simple_free(paServer);
    FLAC__stream_decoder_delete(stream);
}

//
//  PCMCodec.cpp
//  plugins/pcmCodec/src
//
//  Created by Brad Hefta-Gaub on 6/9/2016
//  Copyright 2016 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include "OpusCodecManager.h"

#include <QtCore/QCoreApplication>

#include <PerfStat.h>

#include <opus/opus.h>
//#include <opus\opus_types.h>

const char* OpusCodec::NAME{ "Opus" };

void OpusCodec::init() {
}

void OpusCodec::deinit() {
}

bool OpusCodec::activate() {
    CodecPlugin::activate();
    return true;
}

void OpusCodec::deactivate() {
    CodecPlugin::deactivate();
}

bool OpusCodec::isSupported() const {
    return true;
}

class OpusAudioEncoder : public Encoder {
public:
    OpusAudioEncoder(int sampleRate, int numChannels) {
        int error = OPUS_OK;
        OpusEncoder* enc = opus_encoder_create(sampleRate, numChannels, OPUS_APPLICATION_VOIP, &error);
        /* if (error != OPUS_OK) {
            return NULL;
        } */
    }

    virtual void encode(const QByteArray& decodedBuffer, QByteArray& encodedBuffer) override {
        encodedBuffer.resize(_encodedSize);
        // AudioEncoder::process((const int16_t*)decodedBuffer.constData(), (int16_t*)encodedBuffer.data(),
        //                      AudioConstants::NETWORK_FRAME_SAMPLES_PER_CHANNEL);
    }

private:
    int _encodedSize;
};

class OpusAudioDecoder : public Decoder {
public:
    OpusAudioDecoder(int sampleRate, int numChannels) {
        // _decodedSize = AudioConstants::NETWORK_FRAME_SAMPLES_PER_CHANNEL * sizeof(int16_t) * numChannels;
    }

    virtual void decode(const QByteArray& encodedBuffer, QByteArray& decodedBuffer) override {
        decodedBuffer.resize(_decodedSize);
        // AudioDecoder::process((const int16_t*)encodedBuffer.constData(), (int16_t*)decodedBuffer.data(),
        //                      AudioConstants::NETWORK_FRAME_SAMPLES_PER_CHANNEL, true);
    }

    virtual void lostFrame(QByteArray& decodedBuffer) override {
        decodedBuffer.resize(_decodedSize);
        // this performs packet loss interpolation
        // AudioDecoder::process(nullptr, (int16_t*)decodedBuffer.data(), AudioConstants::NETWORK_FRAME_SAMPLES_PER_CHANNEL, false);
    }

private:
    int _decodedSize;
};

Encoder* OpusCodec::createEncoder(int sampleRate, int numChannels) {
    
    return new OpusAudioEncoder(sampleRate, numChannels);
}

Decoder* OpusCodec::createDecoder(int sampleRate, int numChannels) {
    return new OpusAudioDecoder(sampleRate, numChannels);
}

void OpusCodec::releaseEncoder(Encoder* encoder) {
    // do nothing
}

void OpusCodec::releaseDecoder(Decoder* decoder) {
    // do nothing
}
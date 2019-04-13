//
//
//  Created by Bailey on 04/09/2018
//  Copyright 2018 Michael Bailey
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include <mutex>

#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtCore/QStringList>

#include <plugins/RuntimePlugin.h>
#include <plugins/CodecPlugin.h>

#include "OpusCodecManager.h"

class OpusCodecProvider : public QObject, public CodecProvider {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID CodecProvider_iid FILE "plugin.json")
    Q_INTERFACES(CodecProvider)

public:
    OpusCodecProvider(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~OpusCodecProvider() {}

    virtual CodecPluginList getCodecPlugins() override {
        static std::once_flag once;
        std::call_once(once, [&] {
            CodecPluginPointer opusCodec(new OpusCodec());
            if (opusCodec->isSupported()) {
                _codecPlugins.push_back(opusCodec);
            }
        });
        return _codecPlugins;
    }

private:
    CodecPluginList _codecPlugins;
};

#include "OpusCodecProvider.moc"

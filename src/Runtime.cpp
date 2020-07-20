#include "Runtime.h"

#include "MqttClient.h"
#include "Scenario.h"
#include "StringConsts.h"

Runtime runtime;

Runtime::Runtime() : ParamFile(DEVICE_RUNTIME_FILE){};

void Runtime::property(const String& name, const String value) {
    KeyValueStore::write(name.c_str(), value.c_str(), VT_STRING, KT_PROPERTY);
}

void Runtime::onAdd(KeyValue* item) {
    //
}

void Runtime::onUpdate(KeyValue* item) {
    publishMqtt(item);
    fireEvent(item);
}

void Runtime::publish() {
    forEach([this](KeyValue* item) {
        publishMqtt(item);
    });
}

void Runtime::publishMqtt(KeyValue* item) {
    if (item->isPublished()) {
        MqttClient::publishState(item->getKey(), item->asJson());
    }
}

void Runtime::fireEvent(KeyValue* item) {
    if (item->isEvent()) {
        Scenario::process(item);
    }
}
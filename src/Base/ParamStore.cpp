#include "Base/ParamStore.h"

ParamStore::ParamStore() : KeyValueStore() {}

ParamStore::ParamStore(const char* jsonStr) : KeyValueStore{jsonStr} {}

void ParamStore::write(const String& key, const String& value) {
    KeyValueStore::write(key.c_str(), value.c_str());
}

void ParamStore::write(const String& key, IPAddress ip) {
    KeyValueStore::write(key.c_str(), ip.toString().c_str());
}

void ParamStore::write(const String& key, int value) {
    char buf[9];
    KeyValueStore::write(key.c_str(), itoa(value, buf, DEC), VT_INT);
}

void ParamStore::write(const String& key, float value) {
    char buf[33];
    KeyValueStore::write(key.c_str(), dtostrf(value, 4, 2, buf), VT_FLOAT);
}

void ParamStore::writeAsInt(const String& key, const String& value) {
    KeyValueStore::write(key.c_str(), value.c_str(), VT_INT);
}

void ParamStore::writeAsFloat(const String& key, const String& value) {
    KeyValueStore::write(key.c_str(), value.c_str(), VT_FLOAT);
}

const String ParamStore::read(const String& key, const char* defValue) const {
    String value;
    ValueType_t type;
    if (!KeyValueStore::read(key.c_str(), value, type)) {
        value = defValue;
    }
    return value;
}

const String ParamStore::read(const String& key) const {
    String buf;
    KeyValueStore::read(key.c_str(), buf);
    return buf;
}

int ParamStore::readInt(const String& key) const {
    return read(key).toInt();
}

float ParamStore::readFloat(const String& key) const {
    return read(key).toFloat();
}

void ParamStore::erase(const String& obj) {
    KeyValueStore::erase(obj.c_str());
}

const String ParamStore::asJson() const {
    String res;
    KeyValueStore::toJson(res);
    return res;
}
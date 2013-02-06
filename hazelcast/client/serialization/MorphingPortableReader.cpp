/* 
 * File:   MorphingPortableReader.cpp
 * Author: msk
 * 
 * Created on January 22, 2013, 2:35 PM
 */
#include "Portable.h"
#include "PortableReader.h"
#include "DataInput.h"
#include "PortableSerializer.h"
#include "MorphingPortableReader.h"
#include "FieldDefinition.h"
#include <vector>
#include <string>

namespace hazelcast {
namespace client {
namespace serialization {

MorphingPortableReader::MorphingPortableReader(PortableSerializer* p, DataInput& cad, ClassDefinition* cd) : PortableReader(p, cad, cd) {
}

int MorphingPortableReader::readInt(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        return 0;
    FieldDefinition fd = cd->get(fieldName);

    switch (fd.getType()) {
        case FieldDefinition::TYPE_INT:
            return PortableReader::readInt(fieldName);
        case FieldDefinition::TYPE_BYTE:
            return PortableReader::readByte(fieldName);
        case FieldDefinition::TYPE_CHAR:
            return PortableReader::readChar(fieldName);
        case FieldDefinition::TYPE_SHORT:
            return PortableReader::readShort(fieldName);
        default:
            throw "IncompatibleClassChangeError";
    }
};

long MorphingPortableReader::readLong(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        return 0;
    FieldDefinition fd = cd->get(fieldName);

    switch (fd.getType()) {
        case FieldDefinition::TYPE_LONG:
            return PortableReader::readLong(fieldName);
        case FieldDefinition::TYPE_INT:
            return PortableReader::readInt(fieldName);
        case FieldDefinition::TYPE_BYTE:
            return PortableReader::readByte(fieldName);
        case FieldDefinition::TYPE_CHAR:
            return PortableReader::readChar(fieldName);
        case FieldDefinition::TYPE_SHORT:
            return PortableReader::readShort(fieldName);
        default:
            throw "IncompatibleClassChangeError";
    }
};

bool MorphingPortableReader::readBoolean(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        return 0;
    FieldDefinition fd = cd->get(fieldName);

    if (fd.getType() != FieldDefinition::TYPE_BOOLEAN)
        throw "IncompatibleClassChangeError";

    return PortableReader::readBoolean(fieldName);
};

byte MorphingPortableReader::readByte(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        return 0;
    FieldDefinition fd = cd->get(fieldName);

    if (fd.getType() != FieldDefinition::TYPE_BYTE)
        throw "IncompatibleClassChangeError";

    return PortableReader::readByte(fieldName);
};

char MorphingPortableReader::readChar(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        return 0;
    FieldDefinition fd = cd->get(fieldName);

    if (fd.getType() != FieldDefinition::TYPE_CHAR)
        throw "IncompatibleClassChangeError";

    return PortableReader::readChar(fieldName);
};

double MorphingPortableReader::readDouble(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        return 0;
    FieldDefinition fd = cd->get(fieldName);

    switch (fd.getType()) {
        case FieldDefinition::TYPE_FLOAT:
            return PortableReader::readFloat(fieldName);
        case FieldDefinition::TYPE_DOUBLE:
            return PortableReader::readDouble(fieldName);
        case FieldDefinition::TYPE_LONG:
            return PortableReader::readLong(fieldName);
        case FieldDefinition::TYPE_INT:
            return PortableReader::readInt(fieldName);
        case FieldDefinition::TYPE_BYTE:
            return PortableReader::readByte(fieldName);
        case FieldDefinition::TYPE_CHAR:
            return PortableReader::readChar(fieldName);
        case FieldDefinition::TYPE_SHORT:
            return PortableReader::readShort(fieldName);
        default:
            throw "IncompatibleClassChangeError";
    }
};

float MorphingPortableReader::readFloat(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        return 0;
    FieldDefinition fd = cd->get(fieldName);

    switch (fd.getType()) {
        case FieldDefinition::TYPE_FLOAT:
            return PortableReader::readFloat(fieldName);
        case FieldDefinition::TYPE_INT:
            return PortableReader::readInt(fieldName);
        case FieldDefinition::TYPE_BYTE:
            return PortableReader::readByte(fieldName);
        case FieldDefinition::TYPE_CHAR:
            return PortableReader::readChar(fieldName);
        case FieldDefinition::TYPE_SHORT:
            return PortableReader::readShort(fieldName);
        default:
            throw "IncompatibleClassChangeError";
    }
};

short MorphingPortableReader::readShort(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        return 0;
    FieldDefinition fd = cd->get(fieldName);

    switch (fd.getType()) {
        case FieldDefinition::TYPE_BYTE:
            return PortableReader::readByte(fieldName);
        case FieldDefinition::TYPE_SHORT:
            return PortableReader::readShort(fieldName);
        default:
            throw "IncompatibleClassChangeError";
    }
};

string MorphingPortableReader::readUTF(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        return NULL;
    FieldDefinition fd = cd->get(fieldName);

    if (fd.getType() != FieldDefinition::TYPE_UTF) {
        throw "IncompatibleClassChangeError";
    }
    return PortableReader::readUTF(fieldName);
};

std::vector<byte> MorphingPortableReader::readByteArray(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        throw "throwUnknownFieldException" + fieldName;
    FieldDefinition fd = cd->get(fieldName);

    if (fd.getType() != FieldDefinition::TYPE_BYTE_ARRAY) {
        throw "IncompatibleClassChangeError";
    }
    return PortableReader::readByteArray(fieldName);
};

std::vector<char> MorphingPortableReader::readCharArray(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        throw "throwUnknownFieldException" + fieldName;
    FieldDefinition fd = cd->get(fieldName);

    if (fd.getType() != FieldDefinition::TYPE_CHAR_ARRAY) {
        throw "IncompatibleClassChangeError";
    }
    return PortableReader::readCharArray(fieldName);
};

std::vector<int> MorphingPortableReader::readIntArray(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        throw "throwUnknownFieldException" + fieldName;
    FieldDefinition fd = cd->get(fieldName);

    if (fd.getType() != FieldDefinition::TYPE_INT_ARRAY) {
        throw "IncompatibleClassChangeError";
    }
    return PortableReader::readIntArray(fieldName);
};

std::vector<long> MorphingPortableReader::readLongArray(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        throw "throwUnknownFieldException" + fieldName;
    FieldDefinition fd = cd->get(fieldName);

    if (fd.getType() != FieldDefinition::TYPE_LONG_ARRAY) {
        throw "IncompatibleClassChangeError";
    }
    return PortableReader::readLongArray(fieldName);
};

std::vector<double> MorphingPortableReader::readDoubleArray(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        throw "throwUnknownFieldException" + fieldName;
    FieldDefinition fd = cd->get(fieldName);

    if (fd.getType() != FieldDefinition::TYPE_DOUBLE_ARRAY) {
        throw "IncompatibleClassChangeError";
    }
    return PortableReader::readDoubleArray(fieldName);
};

std::vector<float> MorphingPortableReader::readFloatArray(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        throw "throwUnknownFieldException" + fieldName;
    FieldDefinition fd = cd->get(fieldName);

    if (fd.getType() != FieldDefinition::TYPE_FLOAT_ARRAY) {
        throw "IncompatibleClassChangeError";
    }
    return PortableReader::readFloatArray(fieldName);
};

std::vector<short> MorphingPortableReader::readShortArray(string fieldName) {
    if (!cd->isFieldDefinitionExists(fieldName))
        throw "throwUnknownFieldException" + fieldName;
    FieldDefinition fd = cd->get(fieldName);

    if (fd.getType() != FieldDefinition::TYPE_SHORT_ARRAY) {
        throw "IncompatibleClassChangeError";
    }
    return PortableReader::readShortArray(fieldName);
};

}}}



//
//  SerializationService.h
//  Server
//
//  Created by sancar koyunlu on 1/10/13.
//  Copyright (c) 2013 sancar koyunlu. All rights reserved.
//

#ifndef HAZELCAST_SERIALIZATION_SERVICE
#define HAZELCAST_SERIALIZATION_SERVICE

#include "SerializationContext.h"
#include "PortableSerializer.h"
#include "DataSerializer.h"
#include "Portable.h"
#include "IdentifiedDataSerializable.h"
#include "Serializer.h"
#include "Data.h"
#include "ObjectDataInput.h"
#include "ObjectDataOutput.h"
#include "DataOutput.h"
#include "DataInput.h"
#include "SerializerHolder.h"
#include "hazelcast/util/Util.h"
#include "SerializationConstants.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace serialization {

            class SerializationService {
            public:

                SerializationService(int version);

                ~SerializationService();

                /**
                *
                *  return false if a serializer is already given corresponding to serializerId
                */
                bool registerSerializer(SerializerBase *serializer);

                template<typename T>
                Data toData(const Portable *portable) {
                    const T *object = dynamic_cast<const T *>(portable);
                    Data data;
                    DataOutput output;
                    getSerializerHolder().getPortableSerializer().write(output, *object);
                    int factoryId = object->getFactoryId();
                    int classId = object->getClassId();
                    data.setType(serialization::SerializationConstants::CONSTANT_TYPE_PORTABLE);
                    data.cd = serializationContext.lookup(factoryId, classId);
                    data.setBuffer(output.toByteArray());
                    return data;
                };

                template<typename T>
                Data toData(const IdentifiedDataSerializable *dataSerializable) {
                    const T *object = dynamic_cast<const T *>(dataSerializable);
                    Data data;
                    DataOutput dataOutput;
                    ObjectDataOutput output(dataOutput, serializationContext);
                    getSerializerHolder().getDataSerializer().write(output, *object);
                    data.setType(serialization::SerializationConstants::CONSTANT_TYPE_DATA);
                    data.setBuffer(output.toByteArray());
                    return data;
                };

                template<typename T>
                Data toData(const void *serializable) {
                    const T *object = static_cast<const T *>(serializable);
                    Data data;
                    DataOutput dataOutput;
                    ObjectDataOutput output(dataOutput, serializationContext);
                    int type = object->getSerializerId();
                    SerializerBase *serializer = serializerFor(type);
                    if (serializer) {
                        Serializer<T> *s = static_cast<Serializer<T> * >(serializer);
                        s->write(output, *object);
                    } else {
                        throw exception::IOException("SerializationService::toData", "No serializer found for serializerId :" + util::to_string(type) + ", typename :" + typeid(T).name());
                    }
                    data.setType(type);
                    data.setBuffer(output.toByteArray());
                    return data;
                };

                template<typename T>
                inline T toObject(const Data& data) {
                    checkServerError(data);
                    T *tag;
                    return toObjectResolved<T>(data, tag);
                };

                template<typename T>
                inline T toObjectResolved(const Data& data, Portable *tag) {
                    T object;
                    if (data.bufferSize() == 0) return object;
                    DataInput dataInput(*(data.buffer.get()));

                    serializationContext.registerClassDefinition(data.cd);
                    int factoryId = data.cd->getFactoryId();
                    int classId = data.cd->getClassId();
                    int version = data.cd->getVersion();
                    getSerializerHolder().getPortableSerializer().read(dataInput, object, factoryId, classId, version);
                    return object;
                };

                template<typename T>
                inline T toObjectResolved(const Data& data, IdentifiedDataSerializable *tag) {
                    T object;
                    if (data.bufferSize() == 0) return object;
                    DataInput dataInput(*(data.buffer.get()));
                    ObjectDataInput objectDataInput(dataInput, serializationContext);
                    getSerializerHolder().getDataSerializer().read(objectDataInput, object);
                    return object;
                };

                template<typename T>
                inline T toObjectResolved(const Data& data, void *tag) {
                    T object;
                    DataInput dataInput(*(data.buffer.get()));
                    ObjectDataInput objectDataInput(dataInput, serializationContext);
                    SerializerBase *serializer = serializerFor(object.getSerializerId());
                    if (serializer) {
                        Serializer<T> *s = static_cast<Serializer<T> * >(serializer);
                        s->read(objectDataInput, object);
                        return object;
                    } else {
                        throw exception::IOException("SerializationService::toData", "No serializer found for serializerId :" + util::to_string(data.getType()) + ", typename :" + typeid(T).name());
                    }
                };

                SerializationContext& getSerializationContext();

                SerializerHolder& getSerializerHolder();

            private:
                SerializerBase *serializerFor(int typeId);

                SerializationService(const SerializationService&);

                void checkServerError(const Data& data);

                SerializationContext serializationContext;

            };


            template<>
            inline Data SerializationService::toData<byte >(const void *serializable) {
                DataOutput output;
                const byte *object = static_cast<const byte *>(serializable);
                output.writeByte(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<bool>(const void *serializable) {
                DataOutput output;
                const bool *object = static_cast<const bool *>(serializable);
                output.writeBoolean(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<char>(const void *serializable) {
                DataOutput output;
                const char *object = static_cast<const char *>(serializable);
                output.writeChar(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<short>(const void *serializable) {
                DataOutput output;
                const short *object = static_cast<const short *>(serializable);
                output.writeShort(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<int>(const void *serializable) {
                DataOutput output;
                const int *object = static_cast<const int *>(serializable);
                output.writeInt(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<long>(const void *serializable) {
                DataOutput output;
                const long *object = static_cast<const long *>(serializable);
                output.writeLong(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<float>(const void *serializable) {
                DataOutput output;
                const float *object = static_cast<const float *>(serializable);
                output.writeFloat(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<double>(const void *serializable) {
                DataOutput output;
                const double *object = static_cast<const double *>(serializable);
                output.writeDouble(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<std::vector<byte> >(const void *serializable) {
                DataOutput output;
                const std::vector<byte> *object = static_cast<const std::vector<byte> *>(serializable);
                output.writeByteArray(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<std::vector<char> >(const void *serializable) {
                DataOutput output;
                const std::vector<char> *object = static_cast<const std::vector<char> *>(serializable);
                output.writeCharArray(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<std::vector<short> >(const void *serializable) {
                DataOutput output;
                const std::vector<short> *object = static_cast<const std::vector<short> *>(serializable);
                output.writeShortArray(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<std::vector<int> >(const void *serializable) {
                DataOutput output;
                const std::vector<int> *object = static_cast<const std::vector<int> *>(serializable);
                output.writeIntArray(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<std::vector<long> >(const void *serializable) {
                DataOutput output;
                const std::vector<long> *object = static_cast<const std::vector<long> *>(serializable);
                output.writeLongArray(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<std::vector<float> >(const void *serializable) {
                DataOutput output;
                const std::vector<float> *object = static_cast<const std::vector<float> *>(serializable);
                output.writeFloatArray(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<std::vector<double> >(const void *serializable) {
                DataOutput output;
                const std::vector<double> *object = static_cast<const std::vector<double> *>(serializable);
                output.writeDoubleArray(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };


            template<>
            inline Data SerializationService::toData<std::string>(const void *serializable) {
                DataOutput output;
                const std::string *object = static_cast<const std::string *>(serializable);
                output.writeUTF(*object);
                Data data;
                data.setBuffer(output.toByteArray());
                return data;
            };

            template<>
            inline byte SerializationService::toObject(const Data& data) {
                checkServerError(data);
                byte object = 0;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readByte();
            };

            template<>
            inline bool SerializationService::toObject(const Data& data) {
                checkServerError(data);
                bool object = 0;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readBoolean();
            };

            template<>
            inline char SerializationService::toObject(const Data& data) {
                checkServerError(data);
                char object = 0;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readChar();
            };

            template<>
            inline short SerializationService::toObject(const Data& data) {
                checkServerError(data);
                short object = 0;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readShort();
            };

            template<>
            inline int SerializationService::toObject(const Data& data) {
                checkServerError(data);
                int object = 0;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readInt();
            };

            template<>
            inline long SerializationService::toObject(const Data& data) {
                checkServerError(data);
                long object = 0;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readLong();
            };

            template<>
            inline float SerializationService::toObject(const Data& data) {
                checkServerError(data);
                float object = 0;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readFloat();
            };

            template<>
            inline double SerializationService::toObject(const Data& data) {
                checkServerError(data);
                double object = 0;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readDouble();
            };

            template<>
            inline std::vector<byte> SerializationService::toObject(const Data& data) {
                checkServerError(data);
                std::vector<byte> object;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readByteArray();
            };

            template<>
            inline std::vector<char> SerializationService::toObject(const Data& data) {
                checkServerError(data);
                std::vector<char> object;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readCharArray();
            };

            template<>
            inline std::vector<short> SerializationService::toObject(const Data& data) {
                checkServerError(data);
                std::vector<short > object;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readShortArray();
            };

            template<>
            inline std::vector<int> SerializationService::toObject(const Data& data) {
                checkServerError(data);
                std::vector<int> object;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readIntArray();
            };

            template<>
            inline std::vector<long> SerializationService::toObject(const Data& data) {
                checkServerError(data);
                std::vector<long> object;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readLongArray();
            };

            template<>
            inline std::vector<float> SerializationService::toObject(const Data& data) {
                checkServerError(data);
                std::vector<float> object;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readFloatArray();
            };

            template<>
            inline std::vector<double> SerializationService::toObject(const Data& data) {
                checkServerError(data);
                std::vector<double > object;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readDoubleArray();
            };

            template<>
            inline std::string SerializationService::toObject(const Data& data) {
                checkServerError(data);
                std::string object;
                if (data.bufferSize() == 0) return object;
                DataInput dataInput(*(data.buffer.get()));
                return dataInput.readUTF();
            };
        }
    }
}
#endif /* HAZELCAST_SERIALIZATION_SERVICE */
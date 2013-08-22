//
// Created by sancar koyunlu on 8/12/13.
// Copyright (c) 2013 hazelcast. All rights reserved.



#ifndef HAZELCAST_DataSerializable
#define HAZELCAST_DataSerializable


namespace hazelcast {
    namespace client {

        typedef unsigned char byte;

        namespace serialization {
            class ObjectDataOutput;

            class ObjectDataInput;
        }

        class DataSerializable {
        public:

            virtual ~DataSerializable();

            virtual void writeData(serialization::ObjectDataOutput& writer) const = 0;

            virtual void readData(serialization::ObjectDataInput& reader) = 0;

//            virtual int getSerializerId() const;

        };
    }
}


#endif //HAZELCAST_DataSerializable
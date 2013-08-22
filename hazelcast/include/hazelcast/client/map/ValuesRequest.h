//
// Created by sancar koyunlu on 6/11/13.
// Copyright (c) 2013 hazelcast. All rights reserved.


#ifndef MAP_VALUES_REQUEST
#define MAP_VALUES_REQUEST

#include "PortableHook.h"
#include "../serialization/SerializationConstants.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace map {
            class ValuesRequest : public Portable {
            public:
                ValuesRequest(const std::string& name)
                :name(name) {

                };

                int getFactoryId() const {
                    return PortableHook::F_ID;
                }

                int getClassId() const {
                    return PortableHook::VALUES;
                }


                inline void writePortable(serialization::PortableWriter& writer) const {
                    writer.writeUTF("name", name);
                };


                inline void readPortable(serialization::PortableReader& reader) {
                    name = reader.readUTF("name");
                };
            private:
                std::string name;
            };
        }
    }
}


#endif //MAP_KEY_SET_REQUEST
//
// Created by sancar koyunlu on 9/4/13.
// Copyright (c) 2013 hazelcast. All rights reserved.


#include "AddIndexRequest.h"
#include "hazelcast/client/map/PortableHook.h"
#include "hazelcast/client/serialization/PortableWriter.h"


namespace hazelcast {
    namespace client {
        namespace map {
            AddIndexRequest::AddIndexRequest(const std::string& name, const std::string& attribute, bool ordered)
            :name(name)
            , attribute(attribute)
            , ordered(ordered) {

            };

            int AddIndexRequest::getFactoryId() const {
                return PortableHook::F_ID;
            }

            int AddIndexRequest::getClassId() const {
                return PortableHook::ADD_INDEX;
            }


            void AddIndexRequest::writePortable(serialization::PortableWriter& writer) const {
                writer.writeUTF("name", name);
                writer.writeUTF("a", attribute);
                writer.writeBoolean("o", ordered);
            };
        }
    }
}

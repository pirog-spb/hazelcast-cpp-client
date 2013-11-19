//
// Created by sancar koyunlu on 9/12/13.
// Copyright (c) 2013 hazelcast. All rights reserved.




#ifndef HAZELCAST_ListAddRequest
#define HAZELCAST_ListAddRequest

#include "hazelcast/client/collection/CollectionAddRequest.h"

namespace hazelcast {
    namespace client {
        namespace list {
            class ListAddRequest : public collection::CollectionAddRequest {
            public:

                ListAddRequest(const std::string& name, const serialization::Data& data, int index);

                int getClassId() const;

                void writePortable(serialization::PortableWriter& writer) const;

            private:
                int index;
            };
        }
    }
}

#endif //HAZELCAST_ListAddRequest

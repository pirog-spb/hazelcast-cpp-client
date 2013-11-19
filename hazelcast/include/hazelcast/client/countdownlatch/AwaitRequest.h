//
// Created by sancar koyunlu on 6/25/13.
// Copyright (c) 2013 hazelcast. All rights reserved.



#ifndef HAZELCAST_AwaitRequest
#define HAZELCAST_AwaitRequest

#include "hazelcast/client/impl/PortableRequest.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace serialization{
            class PortableWriter;
        }

        namespace countdownlatch {
            class AwaitRequest : public impl::PortableRequest {
            public:
                AwaitRequest(const std::string& instanceName, long timeout);

                int getFactoryId() const;

                int getClassId() const;

                void writePortable(serialization::PortableWriter& writer) const;

            private:

                std::string instanceName;
                long timeout;
            };
        }
    }
}


#endif //HAZELCAST_AwaitRequest

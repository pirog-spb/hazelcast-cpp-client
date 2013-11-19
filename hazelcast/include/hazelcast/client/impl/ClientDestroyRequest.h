//
// Created by sancar koyunlu on 12/11/13.
// Copyright (c) 2013 hazelcast. All rights reserved.



#ifndef HAZELCAST_ClientDestroyRequest
#define HAZELCAST_ClientDestroyRequest

#include "hazelcast/client/impl/PortableRequest.h"
#include <string>


namespace hazelcast {
    namespace client {
        namespace serialization {
            class PortableWriter;
        }

        namespace impl {
            class ClientDestroyRequest : public PortableRequest {
            public:
                ClientDestroyRequest(const std::string &name, const std::string &serviceName);

                int getFactoryId() const;

                int getClassId() const;

                void writePortable(serialization::PortableWriter &writer) const;

            private:
                const std::string &name;
                const std::string &serviceName;
            };
        }
    }
}

#endif //HAZELCAST_ClientDestroyRequest

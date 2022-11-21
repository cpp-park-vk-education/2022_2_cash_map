#include <gtest/gtest.h>

#include "event.hpp"

TEST(Event_Serializer, Serialize_Deserealize) {
    Event event(Event::Events::PLAY, {{ "Arg1", "True" }});
    auto info = EventSerializer::Serialize(event);
    auto event1 = EventSerializer::Deserialize(info);
    EXPECT_EQ(event1.getEventType(), Event::Events::PLAY);
}

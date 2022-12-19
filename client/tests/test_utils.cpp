#include <gtest/gtest.h>
#include "videowatcher.h"

TEST(test_get_video_id_by_raw_link, test_get_video_id_by_raw_link_default) {
    QString link = "https://www.youtube.com/watch?v=9wI4i899Y90";
    QString video_id = YoutubeWatcher::getVideoIdByRawLink(link);
    EXPECT_EQ(video_id, "9wI4i899Y90");
}

TEST(test_get_video_link_by_id, test_get_video_link_by_id_default) {
    QString video_link = YoutubeWatcher::getLinkByVideoId("9wI4i899Y90");
    EXPECT_EQ(video_link, "https://www.youtube.com/embed/9wI4i899Y90?&enablejsapi=1&html5=1&controls=0");
}
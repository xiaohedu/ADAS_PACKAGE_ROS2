
#include "streamer_node.hpp"
#include <rclcpp/rclcpp.hpp>


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);


  std::string IP = "123.123.123.123";
  Streamer_Args args_streamer = Streamer_Args(IP);

 /* Initialize GStreamer */
  auto streamer_node = std::make_shared<Streamer>("lanedetect_image", args_streamer);
  rclcpp::spin(streamer_node);
  return 0;
}

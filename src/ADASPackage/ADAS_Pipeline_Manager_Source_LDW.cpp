#include <rclcpp/rclcpp.hpp>
#include <memory>

#include "InputStream/camera_node.hpp"
#include "LDW/main_LaneDetectorSim.h"

using namespace LaneDetectorSim;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor executor;
  rclcpp::executors::MultiThreadedExecutor mexecutor;


  Arguments args= Arguments(1,1,61,0.0,0.1);
  // Connect the nodes as a pipeline: camera_node -> lanedetect_node-> streamer_node
  auto camera_node = std::make_shared<CameraNode>("image");
  auto lanedetect_node = std::make_shared<LaneDetectNode>("image", "lanedetect_image", args);

  executor.add_node(camera_node);
  executor.add_node(lanedetect_node);

  executor.spin();
  return 0;
}

#include <rclcpp/rclcpp.hpp>
#include <memory>

#include "InputStream/camera_node.hpp"
#include "FCW/detector.hpp"


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor executor;
  rclcpp::executors::MultiThreadedExecutor mexecutor;


  Args args = Args();

  // Connect the nodes as a pipeline: camera_node -> lanedetect_node-> streamer_node
  auto camera_node = std::make_shared<CameraNode>("image");
  auto detector_node = std::make_shared<App>("image", "detector_image", args);
  	rclcpp::spin(detector_node);

  executor.add_node(camera_node);
  executor.add_node(detector_node);

  executor.spin();
  return 0;
}

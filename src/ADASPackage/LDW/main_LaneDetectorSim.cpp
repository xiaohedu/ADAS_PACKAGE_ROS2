
#include "main_LaneDetectorSim.h"
using namespace ::LaneDetectorSim;

int main(int argc, char** argv)
{

    rclcpp::init(argc, argv);

    auto lanedetect_node = std::make_shared<LaneDetectNode>("image", "lanedetect_image");

    rclcpp::spin(lanedetect_node);

    return 0;
}


#ifndef IMAGE_PIPELINE__CAMERA_NODE_HPP_
#define IMAGE_PIPELINE__CAMERA_NODE_HPP_

#include <chrono>
#include <ctime>
#include <sstream>
#include <string>
#include <thread>
#include <memory>
#include "opencv2/highgui/highgui.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "../Aux/common.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "../Aux/adasdebugapplication.pb.h"
#include "../Aux/adas_android_Interface.hpp";
#include <adas_interfaces/msg/source_parameters.hpp>

using namespace std::chrono;
using namespace ADAS_Debug_Application;
using namespace std;

struct Source_Parameters
{
    Source_Parameters()
        : fps(10)
        , paused(false)
        , stopped(false)
    {
    }
    double fps;
    std::atomic<bool> paused;
    std::atomic<bool> stopped;
};



class Source_ADAS : public rclcpp::Node, public std::enable_shared_from_this<Source_ADAS>
{

public:
    Source_ADAS(Source inputmode,
                std::string path,
                const std::string output_topic,
                const std::string& node_name = "source_node")
        : Node(node_name, true)
        , path_("cropped/cropped_%d.png")
        , inputmode_(Source::FOLDER)

    {

        // Create a subscription on the control messages sent by ADAS Manager
        ctrlsub_ = this->create_subscription<adas_interfaces::msg::SourceParameters>(
            "ADAS_command_pipeline",
            [this](adas_interfaces::msg::SourceParameters::UniquePtr msg) {

                if(msg) {
                    this->source_.paused.store(msg->paused);
                    //this->source_.stopped.store(msg->stopped);
                }

                if(this->source_.stopped.load() == true) {
                    std::cout << "======================================================" << endl;
                    std::cout << "              Stopping the Source node               " << endl;
                    std::cout << "======================================================" << endl;
                    std::cout << "stopped.... " << endl << endl;
                }

                else if(this->source_.paused.load() == true) {
                    std::cout << "======================================================" << endl;
                    std::cout << "              Pausing the Source node                 " << endl;
                    std::cout << "======================================================" << endl;
                    std::cout << "paused.... " << endl << endl;
                }
                
                 else
                {
                    std::cout << "======================================================" << endl;
                    std::cout << "              Setting Source state to Play            " << endl;
                    std::cout << "======================================================" << endl;
                    std::cout << "playing.... " << endl << endl;
                }

                //adas_interfaces::LDWParameters::Int["name"] = 10;
                //adas_interfaces::LDWParameters::Int["name"] = 10;

            },
            rmw_qos_profile_default);

        inputmode_ = inputmode;
        path_ = path;

        // Create a publisher on the output topic.
        pub_ = this->create_publisher<sensor_msgs::msg::Image>(output_topic, rmw_qos_profile_sensor_data);

        if(inputmode_ == Source::CAMERA) {
            // Initialize OpenCV
            cap_.open(0);
            if(!cap_.isOpened()) {
                throw std::runtime_error("Could not open video stream!");
            }

            thread_ = std::thread(std::bind(&Source_ADAS::loop_CameraSrc, this));
        } else

            if(inputmode_ == Source::FOLDER) {

            thread_ = std::thread(std::bind(&Source_ADAS::loop_FolderSrc, this));
        }

        else
            throw std::runtime_error("The input mode for the program is not recognized....shutting down");
    }
    
    
    
    
    

    virtual ~Source_ADAS()
    {
        
        
        std::cout << "======================================================" << endl;
        std::cout << "              Destroying the Source node               " << endl;
        std::cout << "======================================================" << endl;
        std::cout << "stopped.... " << endl << endl;
        
        
       source_.stopped.store(true);
        if(thread_.joinable()) {
            thread_.join();
        }
    }





    void loop_CameraSrc()
    {

        // While pipeline is up and running...
        while(rclcpp::ok() && !source_.stopped.load())

        {

            if(source_.paused.load())
                continue;

            // Capture a frame from OpenCV.
            cap_ >> frame_;

            if(frame_.empty())
                continue;

            // Create a new unique_ptr to an Image message for storage.
            sensor_msgs::msg::Image::UniquePtr msg(new sensor_msgs::msg::Image());

            // Pack the OpenCV image into the ROS image.
            set_now(msg->header.stamp);
            msg->header.frame_id = "camera_frame";
            msg->height = frame_.cols;
            msg->width = frame_.rows;
            msg->encoding = mat_type2encoding(frame_.type());
            msg->is_bigendian = false;
            msg->step = static_cast<sensor_msgs::msg::Image::_step_type>(frame_.step);
            msg->data.assign(frame_.datastart, frame_.dataend);

            cv::imshow("Camera", frame_);

            pub_->publish(msg); // Publish.
        }

        cap_.release();
    }

    void loop_FolderSrc()
    {

        string p = "cropped/cropped_%d.png";

        int Idx = 1;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        std::string path = "../inputdata/" + path_;

        // While running...
        while(rclcpp::ok() && !source_.stopped.load()) {
            if(source_.paused.load())
                continue;

            auto start = high_resolution_clock::now();

            // double startTime = (double)cv::getTickCount();

            char Img_Path[256];
            sprintf(Img_Path, path.c_str(), Idx);

            try {
                frame_ = cv::imread(Img_Path);
            } catch(std::exception& e) {
                break;
            }

            // Create a new unique_ptr to an Image message for storage.
            sensor_msgs::msg::Image::UniquePtr msg(new sensor_msgs::msg::Image());

            // Pack the OpenCV image into the ROS image.
            set_now(msg->header.stamp);
            msg->header.frame_id = Img_Path;
            msg->height = frame_.cols;
            msg->width = frame_.rows;
            msg->encoding = mat_type2encoding(frame_.type());
            msg->is_bigendian = false;
            msg->step = static_cast<sensor_msgs::msg::Image::_step_type>(frame_.step);
            msg->data.assign(frame_.datastart, frame_.dataend);

            // wait for target duration
            auto end = high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;

            while(duration.count() < (1.0 / source_.fps) * 1000) {

                // std::cout<<duration.count() << std::endl;
                end = high_resolution_clock::now();
                duration = end - start;
            }

            pub_->publish(msg); // Publish.
            // cv::imshow("Camera", frame_);
            Idx++;
        }
    }

    std::chrono::high_resolution_clock Clock;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
    rclcpp::Subscription<adas_interfaces::msg::SourceParameters>::SharedPtr ctrlsub_;
    std::thread thread_;
    cv::VideoCapture cap_;
    cv::Mat frame_;
    std::string path_;
    Source inputmode_;
    Source_Parameters source_;
};

#endif // IMAGE_PIPELINE__CAMERA_NODE_HPP_

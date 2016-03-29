
#ifndef LaneDetectorSim_main_h
#define LaneDetectorSim_main_h

#include "Process_LaneDetectorSim.h"
#include <iostream>   // std::cout
#include <string>
#include <chrono>
#include <thread>
#include <memory>
#include "opencv2/highgui/highgui.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "../Aux/common.hpp"
#include <adas_interfaces/msg/source_parameters.hpp>
#include <adas_interfaces/msg/ldw_parameters.hpp>

#include <stdexcept>

/* Time */
extern const int NUM_WINDOW_EWM = 5; // EWMA, EWVAR Init (times)
extern const double COEF = 1;
extern const int WIN_COLS = 3;
extern const int WIN_ROWS = 3;
extern const int IMAGE_RECORD = 1;
extern const char LANE_RECORD_IMAGE[] = "inputdata/outputdata/lane_%d.png";
extern const int TH_KALMANFILTER = 1; 

namespace LaneDetectorSim
{

struct LDW_Parameters

{
    LDW_Parameters()
        : LANE_DETECTOR(true)
        , YAW_ANGLE(0)
        , PITCH_ANGLE(0.1)
        , coef_thetaMax(0)
        , combo_id(2)
    {
    }
    
    int LANE_DETECTOR = 1;
    double YAW_ANGLE = 0.0;
    double PITCH_ANGLE = 0.1;
    double coef_thetaMax;
    int filter_id;
    int combo_id;
};

class LaneDetectNode : public rclcpp::Node
{

public:
    LaneDetectNode(const std::string& input,
                   const std::string& output,
                   const std::string& node_name = "lanedetect_node")
        : Node(node_name, true)

    {

        // Create a subscription on the input topic which prints on receipt of new messages.
        ctrlsub_ = this->create_subscription<adas_interfaces::msg::LDWParameters>(
            "ADAS_command_LDW",
            [this](adas_interfaces::msg::LDWParameters::UniquePtr msg) {
                
                
            std::cout << "======================================================" << endl;
            std::cout << "               Configuring LDW Parameters             " << endl << endl;


                if(msg)
                {
                    
                
                this->param_.LANE_DETECTOR = msg->lane_detector;
                this->param_.PITCH_ANGLE = msg->pitch_angle;
                this->param_.YAW_ANGLE = msg->yaw_angle;
                this->param_.coef_thetaMax = msg->coef_thetamax;
                this->param_.combo_id = msg->combo_id;
                
                
                if (msg->has_custom_field)
                {
                    
                    int i;
                    double d;
                    bool b;
                    string s;
                    std::string::size_type sz;   // alias of size_t
                    
                    
                    switch(msg->custom_type)
                       {
                           
                           //Boolean
                            case 0:
                             istringstream(msg->custom_value)>>boolalpha>>b;
                             adas_interfaces::LDWParameters::Boolean[msg->custom_id]=b;
                             cout << "msg->custom_id : " << boolalpha <<adas_interfaces::LDWParameters::Boolean[msg->custom_id] << endl;
                            break;
                            
                
                            //Int
                            case 1:
                                 i = std::stoi (msg->custom_value, &sz);
                                 adas_interfaces::LDWParameters::String[msg->custom_id]=  i;
                                 cout << "msg->custom_id : " << adas_interfaces::LDWParameters::String[msg->custom_id] << endl;
                                   
                            break;
                           

                            //String 
                            case 2:
                                    s= msg->custom_value;
                                    adas_interfaces::LDWParameters::String[msg->custom_id]= s;
                                    cout << "msg->custom_id : " << adas_interfaces::LDWParameters::String[msg->custom_id] << endl;
                                   
                            break;
                            
                            
                            case 3:
                                    d = std::stod (msg->custom_value, &sz);
                                    adas_interfaces::LDWParameters::Double[msg->custom_id]=  d;
                                    cout << "msg->custom_id : " << adas_interfaces::LDWParameters::Double[msg->custom_id] << endl;
                            
                            break;
                        } 
                    
                }

                }
                
                
            
            cout << "LaneDetector: " << param_.LANE_DETECTOR << endl;
            /*if (args.resize_src) // incase image resize is requested as an input then print the other parameters
              cout << "Resized source: (" << args.width << ", " << args.height
                  << ")\n";*/
            cout << "Pitch: " << param_.PITCH_ANGLE << endl;
            cout << "Yaw: " << param_.YAW_ANGLE << endl;
            /* cout << "Win width: " << args.win_width << endl;
             cout << "Win stride: (" << args.win_stride_width << ", "
                 << args.win_stride_height << ")\n";*/
            cout << "coef_thetaMax: " << param_.coef_thetaMax  << endl;
            cout << "Combination ID: " << param_.combo_id << endl<<endl;
            std::cout << "======================================================" << endl;
            std::cout << "                LDW Configured"<<endl << endl << endl;

            },
            rmw_qos_profile_default);
            
            

        auto qos = rmw_qos_profile_sensor_data;

        execTime = 0; // Execute Time for Each Frame
        lastLateralOffset = 0;
        lateralOffset = 0;   // Lateral Offset
        detectLaneFlag = -1; // init state -> normal state 0
        isChangeLane = 0;    // Whether lane change happens
        changeDone = 0;      // Finish lane change
        muWindowSize = 5;    // Initial window size: 5 (sample)
        sigmaWindowSize = 5; // Initial window size: 5 (sample)
        
        
        
         
    

        InitlaneFeatures(laneFeatures);

        // Create a publisher on the output topic.
        pub_ = this->create_publisher<sensor_msgs::msg::Image>(output, qos);
        std::weak_ptr<std::remove_pointer<decltype(pub_.get())>::type> captured_pub = pub_;

        // Create a subscription on the input topic.
        sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            input,
            [this, captured_pub](sensor_msgs::msg::Image::UniquePtr msg) {
                auto pub_ptr = captured_pub.lock();
                if(!pub_ptr) {
                    return;
                }

                // Create a cv::Mat from the image message (without copying).
                cv::Mat cvMat(msg->width, msg->height, encoding2mat_type(msg->encoding), msg->data.data());

                laneMat = cvMat;

                if(param_.LANE_DETECTOR && !init) 
                    
                {
                    
                    
                    
                        char fileName_test[200];
                        strcpy(fileName_test, "inputdata/LDWConfig/Lanes3.conf");
                    
                        char  fileName_test2[200];
                        strcpy(fileName_test2, "inputdata/LDWConfig/CameraInfo3.conf");
                    
                    switch (param_.combo_id) 
                    {

                        case 0: //IPM+HK
                        LaneDetector_J::mcvInitLaneDetectorConf(fileName_test, &lanesConf);
                    //	MSG("Loaded lanes config file\n");
                        LaneDetector_J::mcvInitCameraInfo(fileName_test2, &cameraInfo);
                    //	MSG("Loaded camera file\n");
                        LaneDetector::InitlaneDetectorConf(laneMat, laneDetectorConf, 2, param_.coef_thetaMax); // KIT 1, ESIEE 2
                        LaneDetector::InitLaneKalmanFilter(laneKalmanFilter, laneKalmanMeasureMat, laneKalmanIdx);

                        break;


                        case 1:		//IPM+P
                        LaneDetector_J::mcvInitLaneDetectorConf(fileName_test, &lanesConf);
                    //	MSG("Loaded lanes config file\n");
                        LaneDetector_J::mcvInitCameraInfo(fileName_test2, &cameraInfo);
                    //	MSG("Loaded camera file\n");
                        LaneDetector::InitlaneDetectorConf(laneMat, laneDetectorConf, 2, param_.coef_thetaMax); // KIT 1, ESIEE 2
                        LaneDetector::InitLaneKalmanFilter(laneKalmanFilter, laneKalmanMeasureMat, laneKalmanIdx);
                        break;



                        case 2:
                        LaneDetector::InitlaneDetectorConf(laneMat, laneDetectorConf, 2, param_.coef_thetaMax); // KIT 1, ESIEE 2
                        LaneDetector::InitLaneKalmanFilter(laneKalmanFilter, laneKalmanMeasureMat, laneKalmanIdx);


                        break;
                    }
                    
                    init = true; // poisonous
                }

                if(param_.LANE_DETECTOR)
                {

                    startTime = (double)cv::getTickCount();

                    switch (param_.combo_id) 
                    {

                     case 0: //IPM+HK
					 ProcessLaneImage_IPM(laneMat, laneDetectorConf, startTime, laneKalmanFilter, laneKalmanMeasureMat, laneKalmanIdx, hfLanes, lastHfLanes,
	 			             	lastLateralOffset, lateralOffset, isChangeLane, detectLaneFlag,  idx, execTime, preHfLanes, changeDone, param_.YAW_ANGLE, param_.PITCH_ANGLE,
	 							      cameraInfo,  lanesConf, IPM_OUT, IPM_cont, particle_detect, particle_track, param_.combo_id);
                     //cv::imshow("IPM_OUT", IPM_OUT);
                     
                      //cv::imshow("IPM_CONTOUR", IPM_cont);
                      //  cv::imshow("PARTICLE_DETECT", particle_detect);
                      //  cv::imshow("PARTICLE_TRACK", particle_track);
                      
                        set_now(msg->header.stamp);
                        msg->header.frame_id = "camera_frame";
                        msg->height = IPM_OUT.cols;
                        msg->width = IPM_OUT.rows;
                        msg->encoding = mat_type2encoding(IPM_OUT.type());
                        msg->is_bigendian = false;
                        msg->step = static_cast<sensor_msgs::msg::Image::_step_type>(IPM_OUT.step);
                        msg->data.assign(IPM_OUT.datastart, IPM_OUT.dataend);
                        pub_ptr->publish(msg); //Publish it along.
                         
                        break;


                        case 1:

                        ProcessLaneImage_IPM(laneMat, laneDetectorConf, startTime, laneKalmanFilter, laneKalmanMeasureMat, laneKalmanIdx, hfLanes, lastHfLanes,
                        lastLateralOffset, lateralOffset, isChangeLane, detectLaneFlag,  idx, execTime, preHfLanes, changeDone, param_.YAW_ANGLE, param_.PITCH_ANGLE,
                        cameraInfo,  lanesConf, IPM_OUT, IPM_cont, particle_detect, particle_track, param_.combo_id);
                            //  cv::imshow("IPM_OUT", IPM_OUT);
                            //  cv::imshow("IPM_CONTOUR", IPM_cont);
                            //cv::imshow("PARTICLE_DETECT", particle_detect);
                            //cv::imshow("PARTICLE_TRACK", particle_track);
                            
                        set_now(msg->header.stamp);
                        msg->header.frame_id = "particle_track";
                        msg->height = particle_track.cols;
                        msg->width = particle_track.rows;
                        msg->encoding = mat_type2encoding(particle_track.type());
                        msg->is_bigendian = false;
                        msg->step = static_cast<sensor_msgs::msg::Image::_step_type>(particle_track.step);
                        msg->data.assign(particle_track.datastart, particle_track.dataend);
                        pub_ptr->publish(msg); // Publish it along.
                 
                        
                        break;



                        case 2:
                        
                        
                        ProcessLaneImage(laneMat, laneDetectorConf, startTime, laneKalmanFilter, laneKalmanMeasureMat, laneKalmanIdx, hfLanes, lastHfLanes,
										lastLateralOffset, lateralOffset, isChangeLane, detectLaneFlag,  idx, execTime, preHfLanes, changeDone, param_.YAW_ANGLE, param_.PITCH_ANGLE);
                                        
                                    set_now(msg->header.stamp);
                                    msg->header.frame_id = "laneMat";
                                    msg->height = laneMat.cols;
                                    msg->width = laneMat.rows;
                                    msg->encoding = mat_type2encoding(laneMat.type());
                                    msg->is_bigendian = false;
                                    msg->step = static_cast<sensor_msgs::msg::Image::_step_type>(laneMat.step);
                                    msg->data.assign(laneMat.datastart, laneMat.dataend);
                                    //cv::imshow("LAneMat", laneMat);
                                    pub_ptr->publish(msg); // Publish it along.

                        break;
                    }
                }
                if(IMAGE_RECORD) {
                    char* text = new char[100];
                    sprintf(text, LANE_RECORD_IMAGE, idx);
                    cv::imwrite(text, laneMat);
                    delete text;
                }

                char* text = new char[30];
                cv::putText(
                    laneMat, text, cv::Point(0, laneMat.rows - 5), cv::FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(0, 255, 0));
                cv::putText(laneMat, text, cv::Point(0, 60), cv::FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(0, 255, 0));
                delete text;

                 //cv::imshow("Lane System", laneMat);
                // cv::moveWindow("Lane System", 790, 30);
                // cv::waitKey(1);

                

            },
            qos);
    }

private:
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
    cv::Mat laneMat,IPM_OUT;
    cv::Mat IPM_cont, particle_detect, particle_track;
    cv::KalmanFilter laneKalmanFilter = cv::KalmanFilter(8, 8, 0);
    cv::Mat laneKalmanMeasureMat = cv::Mat(8, 1, CV_32F, cv::Scalar::all(0));


/*************JOOST*****************/

		LaneDetector_J::CameraInfo cameraInfo;
		


		// read the configurations
		  LaneDetector_J::LaneDetectorConf_J lanesConf;
			


		/**************************************/



    LDW_Parameters param_;

    int idx; // index for image sequence

    double execTime; // Execute Time for Each Frame
    // double pastTime;

    bool init = false;

    std::ofstream laneFeatureFile;

    /* Parameters for Lane Detector */
    LaneDetector::LaneDetectorConf laneDetectorConf;
    std::vector<cv::Vec2f> hfLanes;
    std::vector<cv::Vec2f> lastHfLanes;
    std::vector<cv::Vec2f> preHfLanes;

    std::vector<double> LATSDBaselineVec;
    std::deque<LaneDetector::InfoCar> lateralOffsetDeque;
    std::deque<LaneDetector::InfoCar> LANEXDeque;
    std::deque<LaneDetector::InfoTLC> TLCDeque;

    rclcpp::Subscription<adas_interfaces::msg::LDWParameters>::SharedPtr ctrlsub_;

    LaneDetector::LaneFeature laneFeatures;
    double lastLateralOffset;
    double lateralOffset; // Lateral Offset
    int detectLaneFlag;   // init state -> normal state 0
    int isChangeLane;     // Whether lane change happens
    int changeDone;       // Finish lane change
    int muWindowSize;     // Initial window size: 5 (sample)
    int sigmaWindowSize;  // Initial window size: 5 (sample)

    std::vector<float> samplingTime;
    double startTime;
    int laneKalmanIdx; // Marker of start kalmam
};
}

#endif

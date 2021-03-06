#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <vector>
#include <thread>
#include <memory>
#include <functional>
#include <assert.h>
#include <mutex>
#include "Aux/adas_android_Interface.hpp";
#include "InputStream/source_node.hpp"
#include "VideoServer/streamer_node.hpp"
#include "LDW/main_LaneDetectorSim.h"
#include "FCW/detector.hpp"
#include "Aux/adasdebugapplication.pb.h"
#include "Aux/zmq.hpp"
#include "Aux/zhelpers.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include <adas_interfaces/msg/source_parameters.hpp>
#include <adas_interfaces/msg/ldw_parameters.hpp>
#include <adas_interfaces/msg/fcw_parameters.hpp>

#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <string>

using namespace LaneDetectorSim;
using namespace ADAS_Debug_Application;

static std::mutex android_msg_mutex; // protects android message from race condition.
static std::atomic<bool> client_request{ false };

class ZMQ_Server
{
public:
    ZMQ_Server()
        : ctx_(1)
        , socket_(ctx_, ZMQ_REP)
    {
        
    }

    void run(const std::shared_ptr<Message>& msg_android)
    {

        socket_.bind("tcp://*:5555");
        //ToDo: while rclcpp::ok
        while(true) {
            //  Wait for next request from client
            zmq::message_t request;
            socket_.recv(&request);
            std::string req = std::string(static_cast<char*>(request.data()), request.size());

            //{

            // Synchronize the threads,  if the conf is not thread safe.
            // std::lock_guard<std::mutex> gaurd(MUTEX);

            try {
                { // protected against race condition
                    std::lock_guard<std::mutex> lock(android_msg_mutex);
                    if(msg_android->ParseFromArray(request.data(), request.size())) {

                        cout << "======================================================" << endl;
                        cout << "Request received from the client. Message parsed!" << endl;
                        cout << "======================================================" << endl << endl;

                        client_request.store(true);

                    }

                    else {
                        cerr << "======================================================" << endl;
                        cerr << "Error: Request received but failed to parse Message.  " << endl;
                        cerr << "======================================================" << endl << endl;
                    }
                }

            }

            catch(std::exception& e) {
                std::cout << e.what() << std::endl;
            }

            // Send reply back to client
            zmq::message_t reply(8);
            memcpy(reply.data(), "Enforced", 8);
            socket_.send(reply);
        }
    }
    
    
 virtual ~ZMQ_Server()
 {
     

     
 }

private:
    zmq::context_t ctx_;
    zmq::socket_t socket_;
};



class ADAS_CommandServer : public rclcpp::Node
{

public:
       ADAS_CommandServer(const std::shared_ptr<Message>& msg_android,
                       rclcpp::executors::SingleThreadedExecutor& executor,
                       const std::string& node_name = "Command_node")
        : Node(node_name, true)
        , msg_android_(msg_android)

    {

        rmw_qos_profile_t custom_qos_profile = rmw_qos_profile_default;
        custom_qos_profile.depth = 7;

        src_pub_ =
            this->create_publisher<adas_interfaces::msg::SourceParameters>("ADAS_command_pipeline", custom_qos_profile);
        std::weak_ptr<std::remove_pointer<decltype(src_pub_.get())>::type> src_captured_pub = src_pub_;

        ldw_pub_ = this->create_publisher<adas_interfaces::msg::LDWParameters>("ADAS_command_LDW", custom_qos_profile);
        std::weak_ptr<std::remove_pointer<decltype(ldw_pub_.get())>::type> ldw_captured_pub = ldw_pub_;

        fcw_pub_ = this->create_publisher<adas_interfaces::msg::FCWParameters>("ADAS_command_FCW", custom_qos_profile);
        std::weak_ptr<std::remove_pointer<decltype(fcw_pub_.get())>::type> fcw_captured_pub = fcw_pub_;

        auto callback = [&client_request, &executor, src_captured_pub, ldw_captured_pub, fcw_captured_pub, this]() -> void {
            

            if(client_request.load() == true)

            {

                cout << "======================================================" << endl;
                cout << "           Distributing request to ROS Nodes         " << endl<<endl;
                

                std::lock_guard<std::mutex> lock(android_msg_mutex);
                
                
                
    
                    
                    
                    
                /*SEND BACK THE PIPELINECONFIG*/
                if(msg_android_->messagetype() == MessageType::PipeLine_Config) {
                    
             

                    Message::PipelineConfig config = msg_android_->pipeline_config();

                    adas_interfaces::msg::SourceParameters::UniquePtr msg(new adas_interfaces::msg::SourceParameters());

                    auto pub_ptr = src_captured_pub.lock();
                    if(!pub_ptr)
                        return;

                    msg->stream = static_cast<int>(config.stream());

                    if(config.state() == State::PAUSE) {
                        msg->paused = true;
						msg->stopped = false;
                        pub_ptr->publish(msg);
                    } 
                    
                    if(config.state() == State::PLAY) {
                        msg->paused = false;
						msg->stopped = false;
                        pub_ptr->publish(msg);
                    }
                    if(config.state() == State::STOP) {
                        msg->stopped = true;
						msg->paused = false;
                        pub_ptr->publish(msg);
                        executor.cancel();
                    }
                     

                }
                    else

                    if(msg_android_->messagetype() == MessageType::LDW_Config)
                {

                    Message::LDWConfig config = msg_android_->ldw_config();

                    adas_interfaces::msg::LDWParameters::UniquePtr msg(new adas_interfaces::msg::LDWParameters());

                    auto pub_ptr = ldw_captured_pub.lock();
                    if(!pub_ptr)
                        return;

                    msg->lane_detector = config.lane_detector();
                    msg->coef_thetamax = config.coef_thetamax();
                    msg->pitch_angle = config.pitch_angle();
                    msg->yaw_angle = config.yaw_angle();
                    msg->combo_id = config.detection_combination();
                    
                  
                   
                   if (config.has_custom())
                   {
                        
                       Message::CustomField customfield= config.custom();
                       
                       msg->has_custom_field =true;
                       switch(customfield.type())
                       {
                           
                            case Type::Boolean:
                            msg->custom_type =0;
                            break;
                            
                            case Type::Int:
                            msg->custom_type =1;
                            break;
                             
                            case Type::String:
                            msg->custom_type =2;
                            break;
                            
                            case Type::Double:
                            msg->custom_type =3;
                            break;
                        }
                       
                       msg->custom_id= customfield.name();
                       msg->custom_value= customfield.value();
                   }
                   
                   else
                       
                    {
                         msg->has_custom_field =false;
                           
                    }
                       
                   
                  
                   
                   //customfield.type()

                    pub_ptr->publish(msg);

                }
                
                 else
                     
                  if (msg_android_->messagetype() == MessageType::FCW_Config) 
                {

                    Message::FCWConfig config = msg_android_->fcw_config();

                    adas_interfaces::msg::FCWParameters::UniquePtr msg(new adas_interfaces::msg::FCWParameters());

                    auto pub_ptr = fcw_captured_pub.lock();
                    if(!pub_ptr)
                        return;

                    msg->gr_threshold = config.hoggroupthresholdinit();
                    msg->nlevels = config.levelscount();
                    msg->make_gray = config.grayinit();
                    msg->scale = config.hogscaleinit();
                    msg->hit_threshold = config.hitthreshold();
					msg->processor  = config.processor();
                    
                    
                     if (config.has_custom())
                   {
                        
                       Message::CustomField customfield= config.custom();
                       
                       msg->has_custom_field =true;
                       switch(customfield.type())
                       {
                           
                            case Type::Boolean:
                            msg->custom_type =0;
                            break;
                            
                            case Type::Int:
                            msg->custom_type =1;
                            break;
                             
                            case Type::String:
                            msg->custom_type =2;
                            break;
                            
                            case Type::Double:
                            msg->custom_type =3;
                            break;
                        }
                       
                       msg->custom_id= customfield.name();
                       msg->custom_value= customfield.value();
                   }
                   
                   else
                       
                    {
                         msg->has_custom_field =false;
                           
                    }
                    
                    
                    
                      pub_ptr->publish(msg);
                }
                client_request.store(false); // reset request boolean to false after processing

            } // skip if there is no request

        };
        
        timer_ = this->create_wall_timer(200_ms, callback);
         
    }

    virtual ~ADAS_CommandServer()
    {
        
       
        
        
    }

    

private:
    const std::shared_ptr<Message> msg_android_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<adas_interfaces::msg::SourceParameters>::SharedPtr src_pub_;
    rclcpp::Publisher<adas_interfaces::msg::LDWParameters>::SharedPtr ldw_pub_;
    rclcpp::Publisher<adas_interfaces::msg::FCWParameters>::SharedPtr fcw_pub_;
};



int main(int argc, char* argv[])
{

    rclcpp::init(argc, argv);

    rclcpp::executors::MultiThreadedExecutor mexecutor;
    rclcpp::executors::SingleThreadedExecutor executor;

    ///////////////////////////////////////////////////////////////////////

    /* Start A ZeroMQ REQ-REP Server to get requests from android device */

    const auto android_msg = make_shared<Message>();
    ZMQ_Server ADAS_ZMQ_Server;
    std::thread* zmq_server_thread;
    zmq_server_thread = new std::thread(std::bind(&ZMQ_Server::run, &ADAS_ZMQ_Server, android_msg));

    /////////////////////////////////////////////////////////////////////////
    bool Pipeline_spin_request = false;
    bool printed = false;
    
   

    while(rclcpp::ok)

    {
        
        if(Pipeline_spin_request) 
			
	{

            // rclcpp::shutdow

            ///////////////////////////////////////////////////////////////////////////
            /* Configure Pipeline before execution */

            Message::PipelineConfig config = android_msg->pipeline_config();

            /////////////////////////////////////////////////////////////////////////
            /* Add relevent elements to ADAS Pipeline  */

             const char* IP = android_msg->pipeline_config().ip().c_str();
             
             

             //auto source_node = std::make_shared<Source_ADAS>(config.source(), config.source_folder(), "image");
             auto source_node_manual = std::make_shared<Source_ADAS>(config.source(), config.source_folder(), "image");
             
             auto ADAS_command_server = std::make_shared<ADAS_CommandServer>(android_msg, executor);
             
             auto lanedetect_node = std::make_shared<LaneDetectNode>("image", "ldw_image");
             
			 auto detector_node = std::make_shared<Detector>("image", "detector_image");
            
             auto streamer_node = std::make_shared<Streamer>("ldw_image","detector_image", IP, 5000);
            
            
            
                executor.add_node(ADAS_command_server);
                executor.add_node(source_node_manual);
                executor.add_node(lanedetect_node);
                executor.add_node(streamer_node);
				executor.add_node(detector_node);

           

            ////////////////////////////////////////////////////////////////////////

            cout << "======================================================" << endl;
            cout << "                 Spinning Started                     " << endl;
            cout << "======================================================" << endl;
            cout << "Spinning nodes.... " << endl << endl;

   

            /*Spin the Pipeline until ROS shutdowns */
            executor.spin();
            
            

            cout << "======================================================" << endl;
            cout << "              Spinning Finished                       " << endl;
            cout << "======================================================" << endl;
            cout << "ROS spin exited... " << endl << endl;

            /*Reset the Pipeline Objects */

            // streamer_node_with_source->stop_streamer();

            // if(streamer_node_with_source.unique())
            // streamer_node_with_source.reset();
            // if (ADAS_command_server.unique())
            // ADAS_command_server.reset();
            // if(source_node.unique())
            // source_node.reset();

            /* reset spin request */
            Pipeline_spin_request = false;
            printed=false;
            
           

            ////////////////////////////////////////////////////////////////////////
        }

        if(!printed)
		{
            cout << "======================================================" << endl;
            cout << "	   Initiate Pipeline from the Android Client" << endl;
            cout << "======================================================" << endl;
            cout << "waiting for request form client .... " << endl << endl;
            printed = true;
        }

        { // protected against race condition

            std::lock_guard<std::mutex> lock(android_msg_mutex);
            if(android_msg->messagetype() == MessageType::PipeLine_Config) {
                Message::PipelineConfig config = android_msg->pipeline_config();

                if(config.state() == State::PLAY) {
                    cout << " play requested---------------" << endl;
                    Pipeline_spin_request = true;
      
                }
            }
            
          
            
        }
    }
    
     
     rclcpp::shutdown();

    return 0;
}

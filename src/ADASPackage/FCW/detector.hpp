#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <stdexcept>
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <sys/types.h> // for "stat" function
#include <sys/stat.h>
#include <unistd.h>
#include <adas_interfaces/msg/fcw_parameters.hpp>
#include "../Aux/common.hpp"
#include <sys/types.h> // for "opendir" function
#include <dirent.h>

using namespace std;
using namespace cv;

bool help_showed = false;

struct FCW_Parameters
{

    FCW_Parameters()
        : make_gray(false)
        , scale(1.12)
        , nlevels(13)
        , gr_threshold(0)
        , hit_threshold(1.4)
        , processor(true)
        , cardetector(false)
    {
    }

    bool make_gray;
    double scale;
    int nlevels;
    int gr_threshold;
    double hit_threshold;
    bool processor;
    bool cardetector;
};

/* class Detector is the class handling all the file's parameters*/
class Detector : public rclcpp::Node

{

public:
    Detector(const std::string& input, const std::string& output);
    void before_run();
    void handleKey(char key);

    void hogWorkBegin();
    void hogWorkEnd();
    string hogWorkFps() const;

    void workBegin();
    void workEnd();
    string workFps() const;

    string message() const;

private:
    Detector operator=(Detector&);
    FCW_Parameters param_;
    bool running;

    bool use_gpu;
    bool cardetector;
    bool make_gray;

    double scale;
    int gr_threshold;
    int nlevels;
    double hit_threshold;
    bool gamma_corr;

    int64 hog_work_begin;
    double hog_work_fps;

    int64 work_begin;
    double work_fps;

    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
    rclcpp::Subscription<adas_interfaces::msg::FCWParameters>::SharedPtr ctrlsub_;

    // Internal
    int width_run, height_run;
    vector<float> detector;
    cv::VideoWriter video_writer;
    cv::gpu::HOGDescriptor gpu_hog;
    cv::HOGDescriptor cpu_hog;
    Size win_size;
    Size win_stride;
    DIR* dp;
    struct dirent* ep;
    char* point;
    string directory_name;
    vector<string> classifier_list;
    FileStorage fs;
    unsigned int classifier_index;

    VideoCapture vc;
    // Mat frame;

    string write_txt;
    Mat img_aux, img;
    gpu::GpuMat gpu_img;
    Mat img_to_show_final;
    Mat img_out;
    vector<int> classifiers_red_vlaues;
    vector<int> classifiers_green_vlaues;
    vector<int> classifiers_blue_vlaues;
    vector<string> classifiers_tag;
};

static void printHelp()
{

    cout << "Histogram of Oriented Gradients descriptor and detector sample.\n"
         << "\nUsage: hog_gpu\n"
         << "  (<image>|--video <vide>|--camera <camera_id>) # frames source\n"
         << "  [--make_gray <true/false>] # convert image to gray one or not\n"
         << "  [--resize_src <true/false>] # do resize of the source image or not\n"
         << "  [--width <int>] # resized image width\n"
         << "  [--height <int>] # resized image height\n"
         << "  [--hit_threshold <double>] # classifying plane distance threshold (0.0 usually)\n"
         << "  [--scale <double>] # HOG window scale factor\n"
         << "  [--nlevels <int>] # max number of HOG window scales\n"
         << "  [--win_width <int>] # width of the window (48 or 64)\n"
         << "  [--win_stride_width <int>] # distance by OX axis between neighbour wins\n"
         << "  [--win_stride_height <int>] # distance by OY axis between neighbour wins\n"
         << "  [--gr_threshold <int>] # merging similar rects constant\n"
         << "  [--gamma_correct <int>] # do gamma correction or not\n"
         << "  [--write_video <bool>] # write video or not\n"
         << "  [--dst_video <path>] # output video path\n"
         << "  [--dst_video_fps <double>] # output video fps\n"
         << "  [--write_file] # write file in directory fps\n";
    help_showed = true;
}

// Creating .txt with respect to image's name to feed for the negative data mining

void write_file(string filename, string& write_txt)
{
    // get the name of the input image
    unsigned firstpoint = filename.find_last_of("/");
    unsigned lastpoint = filename.find_last_of(".");

    string name = filename.substr(firstpoint + 1, lastpoint - firstpoint - 1);
    name = "N" + name;

    // assign the name of the input as name of our file
    ofstream myfile;
    // specify the extension of our file
    name += ".txt";
    // create the .txt
    myfile.open(name.c_str());
    // write data inside the .txt
    myfile << write_txt;
    // close the .txt
    myfile.close();
    // Here it ends the .txt coding

    return;
}
// the function detector_out returns the string which will be the content of the generated txt file for the negative
// mining.



string detector_out(Rect* r, string& classifiers_tag)
{
    int x1;
    int x2;
    int y1;
    int y2;
    string txt_out_string;
    x1 = r->x;
    y1 = r->y;
    x2 = (x1 + r->width);
    y2 = (y1 + r->height);
    txt_out_string = classifiers_tag + " " + "-1 -1 -10 " + to_string(x1) + " " + to_string(y1) + " " + to_string(x2) +
                     " " + to_string(y2) + " -1 -1 -1 -1000 -1000 -1000 -10\n";

    return txt_out_string;
}





/*Constructor of the class Detector, contains the subscriptions*/
Detector::Detector(const std::string& input, const std::string& output)
    : Node("detector_node", true), cardetector(false)

{

    // Create a subscription on the control messages from the ADAS Manager
    ctrlsub_ = this->create_subscription<adas_interfaces::msg::FCWParameters>( "ADAS_command_FCW",
              [this](adas_interfaces::msg::FCWParameters::UniquePtr msg) {
                  
                  
                  
                  
            std::cout << "======================================================" << endl;
            std::cout << "               Configuring FCW Parameters             " << endl << endl;


            if(msg)
            {
            
            this->gr_threshold = msg->gr_threshold;
            this->hit_threshold = msg->hit_threshold;
            this->make_gray = msg->make_gray;
            this->nlevels = msg->nlevels;
            this->scale = msg->scale;
            this->use_gpu = msg->processor;
            this->cardetector = msg->cardetector;
            
            
            
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
                                    cout << "msg->custom_id : " << adas_interfaces::LDWParameters::Double[msg->custom_id]<< endl;
                            
                            break;
                        } 
                    
                }

                }
            
            

            cout << "Scale: " << scale << endl;
            /*if (args.resize_src) // incase image resize is requested as an input then print the other parameters
              cout << "Resized source: (" << args.width << ", " << args.height
                  << ")\n";*/
            cout << "Group threshold: " << gr_threshold << endl;
            cout << "Levels number: " << nlevels << endl;
            /* cout << "Win width: " << args.win_width << endl;
             cout << "Win stride: (" << args.win_stride_width << ", "
                 << args.win_stride_height << ")\n";*/
            cout << "Hit threshold: " << hit_threshold << endl;
            cout << "Gamma correction: " << gamma_corr << endl<<endl;
            std::cout << "======================================================" << endl;
            std::cout << "                FCW Configured"<<endl << endl << endl;;

        },
        rmw_qos_profile_default);






    cv::gpu::printShortCudaDeviceInfo(cv::gpu::getDevice());

    auto qos = rmw_qos_profile_sensor_data;

    // Create a publisher on the output topic.
    pub_ = this->create_publisher<sensor_msgs::msg::Image>(output, qos);
    std::weak_ptr<std::remove_pointer<decltype(pub_.get())>::type> captured_pub = pub_;

    use_gpu = param_.processor; // set as deafult to use gpu not cpu
    make_gray = param_.make_gray;
    scale = param_.scale;
    gr_threshold = param_.gr_threshold;
    nlevels = param_.nlevels;
    hit_threshold = param_.hit_threshold;
    cardetector = param_.cardetector;

    before_run();






    // Create a subscription on the input topic.
    /* the actual run function is now inside the subscription itself. from the begining of the subscription
      we recieve the current frame and work with it based on the number of provided classifiers in the classifiers.txt
      file
      then publish at the end the img_out which is the output image after all the classifiers are processed for the
      current frame
      and after publishing we are ready to recieve the next frame thus the subscription starts again from the begining
    */
    sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        input,
        [this, captured_pub](sensor_msgs::msg::Image::UniquePtr msg)

        {
            

            auto pub_ptr = captured_pub.lock();
            if(!pub_ptr) 
            {
                
                return;
            }
            
            cv::Mat frame(msg->width, msg->height, encoding2mat_type(msg->encoding), msg->data.data());
            
            if ( this->cardetector)
            {
                classifier_index = 0;
            while(classifier_index < classifier_list.size()) //&& !frame.empty())// as long as running is set to be true
                                                             //and we still have frames to run then
            {

                if(classifier_index == 0) {
                   

                    frame.copyTo(img_to_show_final);
                    write_txt = "";
                }
                if(classifier_index < classifier_list.size()) { // as long as we have classifiers in the list

                    fs = FileStorage(classifier_list.at(classifier_index), FileStorage::READ);
                    // read from the classifier
                    fs["width"] >> width_run;
                    fs["height"] >> height_run;
                    fs["detector"] >> detector;

                    // loads the detector information from the .yml file (note the .yml file contains
                    // also the .yml file contain the values for the width and the height and they are read into
                    // variables but into the conflicting copy)
                    fs.release();
                    classifier_index++; // update the classifier index to go to the next classifier
                                        // automatically set size from yaml file
                    // Size win_size(width_run,height_run); //(64, 128) or (48, 96) or 56,48
                    // Size win_stride(args.win_stride_width, args.win_stride_height);
                    win_size.width = width_run;
                    win_size.height = height_run;
                    win_stride.width = 8;
                    win_stride.height = 8;
                    // original code

                    //     Size win_size(args.win_width, args.win_width * 2); //(64, 128) or (48, 96)
                    //     Size win_stride(args.win_stride_width, args.win_stride_height);

                    // Create HOG descriptors and detectors here
                    //     vector<float> detector;
                    //     if (win_size == Size(64, 128))
                    //         detector = cv::gpu::HOGDescriptor::getPeopleDetector64x128();
                    //     else
                    //         detector = cv::gpu::HOGDescriptor::getPeopleDetector48x96();

                    // non-modified code
                    gpu_hog = cv::gpu::HOGDescriptor(win_size,
                                                     Size(16, 16),
                                                     Size(8, 8),
                                                     Size(8, 8),
                                                     9,
                                                     cv::gpu::HOGDescriptor::DEFAULT_WIN_SIGMA,
                                                     0.2,
                                                     gamma_corr,
                                                     cv::gpu::HOGDescriptor::DEFAULT_NLEVELS);
                    cpu_hog = cv::HOGDescriptor(win_size,
                                                Size(16, 16),
                                                Size(8, 8),
                                                Size(8, 8),
                                                9,
                                                1,
                                                -1,
                                                HOGDescriptor::L2Hys,
                                                0.2,
                                                gamma_corr,
                                                cv::HOGDescriptor::DEFAULT_NLEVELS);

                    // Shah modification replaces code below
                    gpu_hog.setSVMDetector(detector); // set the detector with the detector values from the .yml file
                    cpu_hog.setSVMDetector(detector); // this detector is not compatible with our detector files
                }

                workBegin(); // start timer of the whole work
                // Change format of the image

                if(make_gray)
                    cvtColor(frame, img_aux, CV_BGR2GRAY); // if itś set to move into grey scale then do so

                else if(use_gpu)
                    cvtColor(frame, img_aux, CV_BGR2BGRA);
                else
                    frame.copyTo(img_aux);

                // Resize image
                /*if (args.resize_src)
                        resize(img_aux, img, Size(args.width, args.height));
                else*/
                img = img_aux;
                // img_to_show = img;

                gpu_hog.nlevels = nlevels;
                cpu_hog.nlevels = nlevels;
                vector<Rect> found;
                // Perform HOG classification
                hogWorkBegin(); // start the timer of the hog classification

                if(use_gpu) {
                    gpu_img.upload(img);
                    gpu_hog.detectMultiScale(
                        gpu_img, found, hit_threshold, win_stride, Size(0, 0), scale, gr_threshold);
                    // if use_gpu is true so itś required to use gpu then use the detect multi scale function in the
                    // gpu_hog
                } else
                    cpu_hog.detectMultiScale(img, found, hit_threshold, win_stride, Size(0, 0), scale, gr_threshold);

                // if use_gpu is false then itś required to use the cpu then we use the detectmultiscale function of the
                // cpu_hog
                /* based on the produced output alternation when the mode is toggled between cpu and gpu although the
                 thresholds didn change so it could
                 be infered from the alternation in the output that detectmulti scale works differently depending on
                 whether its from cpu_hog or gpu_hog */
                hogWorkEnd(); // end the timer of the hog classification

                // Draw positive classified windows  here we draw the green rectangular boxes of the found objects

                Mat samples(found.size(), 2, CV_32F); // contains the centroid coordinades of the detections (Xc,Yc)
                Mat area(found.size(), 1, CV_32F); // contains the area (height*width) of each detection
                Mat A(found.size(), 2, CV_32F); // contains the coordinates of Top-Left point of each detection - needed
                                                // for the detection intersection
                Mat B(found.size(), 2, CV_32F); // contains the coordinates of Right-Bottom point of each detection -
                                                // needed for the detection intersection
                Mat labels(found.size(), 1, CV_32F);
                Mat centers; // parameter fot kmeans that contains the centroids of the clusters

                for(size_t i = 0; i < found.size(); i++) {

                    Rect r = found[i]; // what should be saved as suggest in a .yml file by the detector.cpp file

                    samples.at<float>(i, 0) = r.x + 0.5 * r.width;  // returns Xc of the detected rectangle
                    samples.at<float>(i, 1) = r.y + 0.5 * r.height; // // returns Yc of the detected rectangle

                    area.at<float>(0, i) = r.height * r.width; // calculate the area of each detection

                    A.at<float>(i, 0) = samples.at<float>(i, 0) - r.width / 2; // top left point of cluster - x
                    A.at<float>(i, 1) = samples.at<float>(i, 1) + r.height / 2; // top left point of cluster - y

                    B.at<float>(i, 0) = samples.at<float>(i, 0) + r.width / 2; // bottom right point of cluster - x
                    B.at<float>(i, 1) = samples.at<float>(i, 1) - r.height / 2; // bottom right point of cluster - y

                    write_txt += detector_out(&r, classifiers_tag.at(classifier_index - 1));
                    if(gr_threshold >=
                       0 /*&& args.headless == false*/) // draw the detections without external clustering
                    {
                        rectangle(img_to_show_final,
                                  r.tl(),
                                  r.br(),
                                  CV_RGB(classifiers_red_vlaues.at(classifier_index - 1),
                                         classifiers_green_vlaues.at(classifier_index - 1),
                                         classifiers_blue_vlaues.at(classifier_index - 1)),
                                  3); // draw the detection rectangle based on the color specified to this classifier in
                                      // the txt file
                    }
                } // ADD the text to the image containing each classifierś fps and descriptor size (dimension)
                if(use_gpu) {
                    // stringstream desc_size_gpu;
                    // to_string(static_cast<int>(gpu_hog.getDescriptorSize())) >> desc_size_gpu;
                    //
                    putText(img_to_show_final,
                            "Descriptor size:" + to_string(static_cast<int>(gpu_hog.getDescriptorSize())) +
                                " FPS HOG detector " + to_string(classifier_index) + ":" + hogWorkFps(),
                            Point(5, 145 + classifier_index * 40),
                            FONT_HERSHEY_SIMPLEX,
                            0.5,
                            CV_RGB(classifiers_red_vlaues.at(classifier_index - 1),
                                   classifiers_green_vlaues.at(classifier_index - 1),
                                   classifiers_blue_vlaues.at(classifier_index - 1)),
                            1);
                } else {
                    // stringstream desc_size_cpu;
                    // cpu_hog.getDescriptorSize() >> desc_size_cpu;
                    putText(img_to_show_final,
                            "Descriptor size:" + to_string(static_cast<int>(cpu_hog.getDescriptorSize())) +
                                " FPS HOG detector " + to_string(classifier_index) + ":" + hogWorkFps(),
                            Point(5, 145 + classifier_index * 40),
                            FONT_HERSHEY_SIMPLEX,
                            0.5,
                            CV_RGB(classifiers_red_vlaues.at(classifier_index - 1),
                                   classifiers_green_vlaues.at(classifier_index - 1),
                                   classifiers_blue_vlaues.at(classifier_index - 1)),
                            1);
                }

                int count = 0; // initiallizing counter for detections overlaps
                float h; // height of cluster
                float w;  // widht of cluster
                float SI; // Intersected area between two detections
                float overlap; // overlap (0-1) between two detections (SI/min(detected_area))

                for(int j = 0; j < (int)found.size(); j++) // for every detection
                {

                    for(int lenght = j + 1; lenght < (int)found.size(); lenght++) // for all the other detections
                    {
                        // calculate the ntersected area
                        SI = fmax(0,
                                  fmin(B.at<float>(j, 0), B.at<float>(lenght, 0)) -
                                      fmax(A.at<float>(j, 0), A.at<float>(lenght, 0))) *
                             fmax(0,
                                  fmin(A.at<float>(j, 1), A.at<float>(lenght, 1)) -
                                      fmax(B.at<float>(j, 1), B.at<float>(lenght, 1)));

                        // calculate the overlap
                        overlap = SI / (fmin(area.at<float>(0, j), area.at<float>(0, lenght)));

                        if(overlap >= 0.5) // condition if overlap is satisfactory
                        {
                            count++; // number of overlaps

                            break; // check is done
                        }
                    }
                }

                int clusterCount; // number of clusters for kmeans function
                clusterCount = (int)found.size() - count;
                int attempts = 5000; // number of iterations before convergence
                Mat mnarea(clusterCount,
                           1,
                           CV_32F); // contains the mean area of each cluster with respect to the included detections

                if(clusterCount != 0) // if no detections then no clustering
                {
                    kmeans(samples,
                           clusterCount,
                           labels,
                           TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 1000, 0.000001),
                           attempts,
                           KMEANS_PP_CENTERS,
                           centers);

                    for(int k = 0; k < clusterCount; k++) { // for every cluster

                        float sum = 0; // sum for this cluster
                        float j = 0;   // detections in this cluster
                        float mean_area = 0;

                        for(size_t i = 0; i < found.size(); i++) // for every detection
                        {

                            if(labels.at<int>(0, i) == k) // check detections at the same cluster
                            {
                                j = j + 1;

                                sum = sum + area.at<float>(0, i);
                            }
                        }
                        if(j > 0) {
                            mean_area = sum / j; // calculate area occupied of each cluster
                        }

                        mnarea.at<float>(0, k) = mean_area;

                        h = sqrt( // calculate the height of each calculated cluster
                            (mnarea.at<float>(0, k)) * ((float)height_run / (float)width_run));
                        w = (mnarea.at<float>(0, k)) / h; // calculate the width of each calculated cluster
                        if(gr_threshold < 0 /*&& args.headless == false*/) // special gr_threshold = -1 for clustering
                        {
                            rectangle(img_to_show_final, // draw the clusters
                                      Point(centers.at<float>(k, 0) - w / 2, centers.at<float>(k, 1) - h / 2),
                                      Point(centers.at<float>(k, 0) + w / 2, centers.at<float>(k, 1) + h / 2),
                                      CV_RGB(

                                          classifiers_red_vlaues.at(classifier_index - 1),

                                          classifiers_green_vlaues.at(classifier_index - 1),

                                          classifiers_blue_vlaues.at(classifier_index - 1)),
                                      3);
                        }
                    }
                }

                img_to_show_final.copyTo(
                    img_out); // update img_out to be displayed with all the information per classifier written on it

                if(classifier_index >= classifier_list.size()) {
                    // if (args.file_gen) {
                    // write_file(args.src, write_txt);

                    /*if (!args.src_is_directory && !args.src_is_video
                                    && !args.src_is_camera) // if processing a single file
                            running = false; // then don't loop on the current image

                    break; // don't display anything (much faster!)*/
                    //}
                    if(use_gpu) // here the text is added (fps) to the display both in case of cpu or gpu
                        putText(img_out, "Mode: GPU ", Point(5, 25), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 100, 0), 1);
                    else
                        putText(img_out, "Mode: CPU", Point(5, 25), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 100, 0), 1);
                    putText(img_out,
                            "FPS (total): " + workFps(),
                            Point(200, 25),
                            FONT_HERSHEY_SIMPLEX,
                            0.5,
                            Scalar(255, 100, 0),
                            1);

                    putText(img_out,
                            "Scale: " + to_string(scale) + " " + "Levels number: " + to_string(nlevels) + " " +
                                "Convert image to gray: " + " " + to_string(make_gray),
                            Point(5, 65),
                            FONT_HERSHEY_SIMPLEX,
                            0.5,
                            Scalar(255, 100, 0),
                            1);

                    putText(img_out,
                            "Group threshold: " + to_string(gr_threshold) + " " + "Hit threshold: " +
                                to_string(hit_threshold),
                            Point(5, 105),
                            FONT_HERSHEY_SIMPLEX,
                            0.5,
                            Scalar(255, 100, 0),
                            1);

                    // putText(img_out, "FPS (HOG only): " + hogWorkFps(), Point(5, 105), FONT_HERSHEY_SIMPLEX, 1.,
                    // Scalar(255, 100, 0), 2);
                    /*if (!img_out.empty()) {
                            imshow("opencv_gpu_hog", img_out);
                    }*/

                    /*if (args.src_is_video || args.src_is_camera)
                            vc >> frame; // whether the source is video or from camera put update the frame to the
                       capured value*/
                    workEnd(); // end the timer of the whole work

                    /*if (args.write_video) {
                            if (!video_writer.isOpened()) {
                                    video_writer.open(args.dst_video,
                                                    CV_FOURCC('x', 'v', 'i', 'd'), args.dst_video_fps,
                                                    img_out.size(), true);
                                    if (!video_writer.isOpened())
                                            throw std::runtime_error("can't create video writer");
                            }

                            if (make_gray)
                                    cvtColor(img_out, img, CV_GRAY2BGR);
                            else
                                    cvtColor(img_out, img, CV_BGRA2BGR);

                            video_writer << img;
                    }*/
                    // classifier_index = 0; // classifier index is back to zero to go through the classifiers agian
                }

                // produce an output video from the results
                // handleKey((char) waitKey(3));

                // if (args.src_is_directory) break; // if processing a folder, get the next image instead of looping
            }
            classifier_index = 0; // classifier index is back to zero to go through the classifiers agian
            set_now(msg->header.stamp);
            msg->header.frame_id = "camera_frame";
            msg->height = img_out.cols;
            msg->width = img_out.rows;
            msg->encoding = mat_type2encoding(img_out.type());
            msg->is_bigendian = false;
            msg->step = static_cast<sensor_msgs::msg::Image::_step_type>(img_out.step);
            msg->data.assign(img_out.datastart, img_out.dataend);

            // cv::Mat cvMat( msg->width, msg->height,encoding2mat_type(msg->encoding), msg->data.data());
            // cv::imshow("Lane System", cvMat);
            // cv::waitKey(1);
            if(!img_out.empty() /*&& args.headless == false*/) {
                imshow("opencv_gpu_hog", img_out);
            }
            // cv::imshow("input frame", frame);

            //handleKey((char)waitKey(3));
            pub_ptr->publish(msg); // Publish it along.s
            
             } //if (car_detector)
             
             
             
             
             
             
        else
        {
            
            set_now(msg->header.stamp);
            msg->header.frame_id = "camera_frame";
            msg->height = frame.cols;
            msg->width = frame.rows;
            msg->encoding = mat_type2encoding(frame.type());
            msg->is_bigendian = false;
            msg->step = static_cast<sensor_msgs::msg::Image::_step_type>(frame.step);
            msg->data.assign(frame.datastart, frame.dataend);
             pub_ptr->publish(msg); // publish the orignal frame

        }
            
        },qos);
}






void Detector::before_run()
{
    /*This function is responsible for initialization before the actual run and looping*/
    // Shah modification replaces below to load detecor in yml file
    // replace commented code below
    // FileStorage fs("../../data/carDetector56x48_front_ov_100h.yml", FileStorage::READ);
    // original code
    //     gpu_hog.setSVMDetector(detector);
    //     cpu_hog.setSVMDetector(detector);
    ifstream file_classifiers_in("../inputdata/FCWdata/classifiers.txt"); // the text file containing the classifiers
                                                                          // that will be used along the desired color
    string classifier_line; // the line read from the classifiers text file
    string colors;          // the string containging the colors values
    string green_blue; // The substring which will contain the color values for green and blue
    string blue;  // The string containing the blue color value for the corresponding detector box (0->255)
    string red;   // The string containing the red color value for the corresponding detector box (0->255)
    string green; // The string containing the green color value for the corresponding detector box (0->255)
    string tag;   // Tag that specifies the current classifier

    while(getline(file_classifiers_in, classifier_line)) {

        // loop to get all classifiers
        classifier_line = classifier_line.substr(
            0,
            classifier_line.find("#")); // anything written after symbol # will be treated as a comment till end of line
        colors = classifier_line.substr(classifier_line.find(";") + 1,
                                        classifier_line.find("$")); // the tag that will be used to generate the .txt
                                                                    // file for the negative data mining will come after
                                                                    // the dollar sign
        red = colors.substr(0, colors.find(";"));
        green_blue = colors.substr(colors.find(";") + 1);
        green = green_blue.substr(0, green_blue.find(";"));
        blue = green_blue.substr(green_blue.find(";") + 1);
        tag = classifier_line.substr(classifier_line.find("$") + 1);
        classifier_line = classifier_line.substr(0, classifier_line.find(";"));
        classifiers_tag.push_back(tag);
        classifiers_red_vlaues.push_back(stoi(red));
        classifiers_green_vlaues.push_back(stoi(green));
        classifiers_blue_vlaues.push_back(stoi(blue));

        classifier_list.push_back(classifier_line);

        // update the classifier vector list with each classifier written in the classifier text file
        // update the list with each classifier corresponding desired color
    }

    cout << " classifiers list size : " << classifier_list.size() << endl;
    // find out if the input is a directory
    struct stat path_stat;
    running = true;
    classifier_index = 0;

    /*if ((!args.src_is_video) && (!args.src_is_camera)) // first, make sure we are not dealing with a video or camera
                    {
            stat(args.src.c_str(), &path_stat);
            if ( S_ISDIR(path_stat.st_mode) == 1) {
                    args.src_is_directory = true;
                    dp = opendir(args.src.c_str());

                    if (dp == NULL) {
                            perror("Couldn't open the directory");
                            exit(-1);
                    }

                    directory_name = args.src; // store the original path so it will not be overwritten

                    if (directory_name.back() != '/') // check for missing slash at the end of directory path
                            directory_name.append("/");
            }
    }*/
}




void Detector::handleKey(char key)
{
    switch(key) {
    case 27:
        running = false;
        break;
    case 'm':
    case 'M':
        use_gpu = !use_gpu;
        cout << "Switched to " << (use_gpu ? "CUDA" : "CPU") << " mode\n";
        classifier_index = 0;
        // toggle between modes cpu and gpu by pressing m
        break;
    case 'g':
    case 'G':
        make_gray = !make_gray;
        cout << "Convert image to gray: " << (make_gray ? "YES" : "NO") << endl;
        classifier_index = 0;
        // toggle between gray or not by pressing g
        break;
    case '1':
        scale *= 1.11;
        cout << "Scale: " << scale << endl;
        classifier_index = 0;
        // increase the scale by 11% when digit 1 is pressed
        break;
    case 'q':
    case 'Q':
        scale /= 1.11;
        cout << "Scale: " << scale << endl;
        classifier_index = 0;
        // decrease the scale by 11% when q is pressed
        break;
    case '2':
        nlevels++;
        cout << "Levels number: " << nlevels << endl;
        classifier_index = 0;
        // increment the max number of HOG window scales when digit 2 is pressed
        break;
    case 'w':
    case 'W':
        nlevels = max(nlevels - 1, 1);
        cout << "Levels number: " << nlevels << endl;
        classifier_index = 0;
        // decrement the max number of HOG window scales but also ensuring itś minimum value is 1 when w is pressed
        break;
    case '3':
        gr_threshold++;
        cout << "Group threshold: " << gr_threshold << endl;
        classifier_index = 0;
        // merging similar rects constant (group threshold) incrementation when digit 3 is pressed
        break;
    case 'e':
    case 'E':
        // range changed from max(0,gr_threshold - 1) to introduce clustering flag for ::-1
        gr_threshold = max(-1, gr_threshold - 1);
        cout << "Group threshold: " << gr_threshold << endl;
        classifier_index = 0;
        // merging similar rects constant (group thershold) decrementation but also making sure that itś minimum value
        // is 0 when e is pressed
        break;
    case '4':
        hit_threshold += 0.05;
        cout << "Hit threshold: " << hit_threshold << endl;
        classifier_index = 0;
        // classifying plane distance threshold (0.0 usually)"hit threshold" increment  by 0.05 when digit 4 is pressed
        break;
    case 'r':
    case 'R':
        hit_threshold = hit_threshold - 0.05;
        cout << "Hit threshold: " << hit_threshold << endl;
        classifier_index = 0;
        // classifying plane distance threshold (0.0 usually)"hit threshold" decrement  by 0.05 when r is pressed
        break;
    case 'c':
    case 'C':
        gamma_corr = !gamma_corr;
        cout << "Gamma correction: " << gamma_corr << endl;
        classifier_index = 0;
        // toggle the gamma correction variable when c is pressed
        break;
    }
}



inline void Detector::hogWorkBegin()
{
    hog_work_begin = getTickCount();
}

inline void Detector::hogWorkEnd()
{
    int64 delta = getTickCount() - hog_work_begin;
    double freq = getTickFrequency();
    hog_work_fps = freq / delta;
}

inline string Detector::hogWorkFps() const
{ // only the hog classification working fps
    stringstream ss;
    ss << hog_work_fps;
    return ss.str();
}

inline void Detector::workBegin()
{
    work_begin = getTickCount();
}

inline void Detector::workEnd()
{
    int64 delta = getTickCount() - work_begin;
    double freq = getTickFrequency();
    work_fps = freq / delta;
}

inline string Detector::workFps() const
{ // the working fps of the run
    stringstream ss;
    ss << work_fps;
    return ss.str();
}

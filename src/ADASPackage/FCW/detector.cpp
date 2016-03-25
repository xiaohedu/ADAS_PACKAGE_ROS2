#include "detector.hpp"

int main(int argc, char** argv)
{

    rclcpp::init(argc, argv);

    cout << "Current opencv version is " << CV_VERSION << endl;

    try {
        // printHelp(); // in case not enough inputs

        // Args args = Args::read(argc, argv);

        Args args = Args();

        // if (help_showed)
        //    return -1;
        auto detector_node = std::make_shared<App>("image", "detector_image", args);
        rclcpp::spin(detector_node);

    }

    catch(const Exception& e) {
        return cout << "error: " << e.what() << endl, 1;
    } catch(const exception& e) {
        return cout << "error: " << e.what() << endl, 1;
    } catch(...) {
        return cout << "unknown exception" << endl, 1;
    }

    return 0;
}

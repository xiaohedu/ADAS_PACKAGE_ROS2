#include "detector.hpp"


int main(int argc, char** argv)
{


    cout <<"Current opencv version is "<<CV_VERSION<<endl;
    
    try
    {
        if (argc < 2)
            printHelp(); // in case not enough inputs
        Args args = Args::read(argc, argv);
        if (help_showed)
            return -1;
        App app(args);
        app.before_run();
        app.run();
    }
    catch (const Exception& e) { return cout << "error: "  << e.what() << endl, 1; }
    catch (const exception& e) { return cout << "error: "  << e.what() << endl, 1; }
    catch(...) { return cout << "unknown exception" << endl, 1; }
    return 0;
    
    
}
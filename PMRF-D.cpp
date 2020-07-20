// OpenCV includes:
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
// end OpenCV includes

#include <chrono>
#include <cstdint>
#include <iostream>
#include <pthread.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "ICM/ICM.hpp"
#include "Model/AuxMRF.hpp"
#include "Model/ThreadData.hpp"
#include "Model/K.hpp"
#include "Utilities/io.hpp"
#include "Utilities/LAP.hpp"

void reconstruct_image(std::vector<AuxMRF> auxMRFs,
                       std::vector< std::vector<uint8_t> > *data) {
    for (auto auxMRF: auxMRFs) {
        auto channel = auxMRF.getChannel();
        for (auto baseNode: auxMRF.getBaseNodes()) {
            data->at(channel).at(baseNode.position) = baseNode.value;
        }
    }
}

void update_auxMRF_values(std::vector<AuxMRF> *auxMRFs, std::vector< std::vector<uint8_t> > *data) {
    for (size_t i = 0; i < auxMRFs->size(); ++i) {
        for (size_t j = 0; j < auxMRFs->at(i).getAugmentingNodes().size(); ++j) {
            auto position = auxMRFs->at(i).getAugmentingNodes().at(j).position;
            auto channel = auxMRFs->at(i).getChannel();
            auxMRFs->at(i).updateAugmentingNode(j, data->at(channel).at(position));
        }
    }
}

std::string get_filename_base(std::string fileName) {
    size_t indexOfLastSlash = fileName.find_last_of("/");
    if (indexOfLastSlash != std::string::npos) {
        fileName = fileName.substr(indexOfLastSlash + 1, fileName.size() - indexOfLastSlash - 1);
    }
    
    size_t indexOfLastDot = fileName.find_last_of(".");
    if (indexOfLastDot != std::string::npos) {
        fileName = fileName.substr(0, indexOfLastDot);
    }
    return fileName;
}

template <typename T>
std::string to_string_w_precision(const T num, const int precision = 3) {
    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << num;
    return out.str();
}

void* thread_controller(void* threadDataVoid) {
    ThreadData* threadData = (ThreadData*) threadDataVoid;
    
    // break data up into cliques according to the LAP algorithm
    LAP(threadData->auxMRFs, threadData->data, threadData->WIDTH, threadData->HEIGHT, threadData->CHANNELS, threadData->THREAD_ID, threadData->NUM_THREADS);
    
    // perform ICM on the cliques
    ICM(threadData->auxMRFs, threadData->LAMBDA, threadData->PSI_MAX);
    
    // rebuild the image with the new, denoised pixel values produced by ICM
    reconstruct_image(*(threadData->auxMRFs), threadData->data);
    
    pthread_exit(NULL);
}

void* thread_controller_multiple_iterations(void* threadDataVoid) {
    ThreadData* threadData = (ThreadData*) threadDataVoid;

    // augmenting node values have changed during ICM, so we want to update
    // the auxMRFs to reflect that
    update_auxMRF_values(threadData->auxMRFs, threadData->data);
    
    // perform ICM on the cliques
    ICM(threadData->auxMRFs, threadData->LAMBDA, threadData->PSI_MAX);
    // rebuild the image with the new, denoised pixel values produced by ICM
    reconstruct_image(*(threadData->auxMRFs), threadData->data);
    
    pthread_exit(NULL);
}

int main(int argc, const char** argv) {
    
    // check for proper usage and return if not
    if (argc < 2) {
        std::cout << "Usage: ./PMRF-D inputImageFile.dat [num_processes] [num_icm_iterations]" << std::endl;
        return 1;
    }
    
	// store command line args
	std::string file_name = argv[1];
    const size_t NUM_THREADS = argc > 2 ? atoi(argv[2]) : K.DEFAULT_NUM_THREADS;
    const size_t NUM_ITER = argc > 3 ? atoi(argv[3]) : K.DEFAULT_NUM_ITER;
    const double LAMBDA = argc > 4 ? atof(argv[4]) : K.DEFAULT_LAMBDA;
    const int PSI_MAX = argc > 5 ? atoi(argv[5]) : K.DEFAULT_PSI_MAX;
    
    // extract png image data
    //std::string image_path = cv::samples::findFile(file_name);
    //cv::Mat img = imread(image_path, cv::IMREAD_UNCHANGED);
    cv::Mat img = imread(file_name, cv::IMREAD_UNCHANGED);
    // store the image width, height, and number of channels
    const size_t WIDTH = img.cols;
    const size_t HEIGHT = img.rows;
    const size_t CHANNELS = img.channels();
    
	// the data vector that will hold the binary image data
    std::vector< std::vector<uint8_t> > data( CHANNELS, std::vector<uint8_t>(WIDTH * HEIGHT) );
    
    // MARK:- Threads Setup
    ThreadData threadData[NUM_THREADS]; // structures to hold data for each thread
    pthread_t threads[NUM_THREADS];     // the threads
    pthread_attr_t attributes; // thread attribute (e.g. whether joinable or not)
    void* status;   // to pass with calls to pthread_join, will
                    // hold exit status of completed threads
    pthread_attr_init(&attributes); // initialize the attributes object
    // specify that threads will be joinable
    pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_JOINABLE);
    
    // array of vectors in which to store auxiliary MRFs resulting from the LAP
    // algorithm. Each thread has one AuxMRF vector.
    std::vector<AuxMRF> auxMRFs[NUM_THREADS];

    // MARK:- Start Timing
    auto startTime =  std::chrono::high_resolution_clock::now();
	
	// transfer the data from the Mat structure into the data vector
	transferMatDataToVector(&img, &data);
    
    
    // MARK:- Run the threads
    for (size_t i = 0; i < NUM_THREADS; ++i) {
        // package the data to pass along with the thread
        threadData[i].THREAD_ID = i;
        threadData[i].data = &data;
        threadData[i].auxMRFs = &auxMRFs[i];
        threadData[i].HEIGHT = HEIGHT;
        threadData[i].WIDTH = WIDTH;
        threadData[i].CHANNELS = CHANNELS;
        threadData[i].NUM_THREADS = NUM_THREADS;
        threadData[i].LAMBDA = LAMBDA;
        threadData[i].PSI_MAX = PSI_MAX;
        pthread_create(&threads[i], NULL, thread_controller, (void*) &threadData[i]);
    }
    
    // free attributes
    pthread_attr_destroy(&attributes);
    
    // wait for the other threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], &status);
    }
    
    // now that auxMRFs has been populated via the LAP algorithm, we can run
    // ICM on the same auxMRFs data for multiple iterations without redoing the
    // LAP partitioning
    for (size_t i = 0; i < NUM_ITER - 1; ++i) {
        
        pthread_attr_init(&attributes); // initialize the attributes object
        // specify that threads will be joinable
        pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_JOINABLE);
        
        std::cout << "creating threads for the " << i+1 << "th iteration" << std::endl;
        
        for (size_t j = 0; j < NUM_THREADS; ++j) {
            // package the data to pass along with the thread
            threadData[j].THREAD_ID = j;
            threadData[j].data = &data;
            threadData[j].auxMRFs = &auxMRFs[j];
            threadData[j].HEIGHT = HEIGHT;
            threadData[j].WIDTH = WIDTH;
            threadData[j].CHANNELS = CHANNELS;
            threadData[j].NUM_THREADS = NUM_THREADS;
            threadData[i].LAMBDA = LAMBDA;
            threadData[i].PSI_MAX = PSI_MAX;
            pthread_create(&threads[j], NULL, thread_controller_multiple_iterations, (void*) &threadData[j]);
        }
        // free attributes
        pthread_attr_destroy(&attributes);
        
        // wait for the other threads
        for (int i = 0; i < NUM_THREADS; ++i) {
            pthread_join(threads[i], &status);
        }
    } // end for i in NUM_ITER - 1
    
    // MARK:- All threads finished
    // write the data out to a file
    std::string output_file_name = "./Output/" + get_filename_base(file_name) +
                                    "_denoised_" + std::to_string(NUM_ITER) +
                                    "_lambda_" + to_string_w_precision(LAMBDA) +
                                    "_psi_" + std::to_string(PSI_MAX) + "_" +
                                    std::to_string(NUM_ITER) + "_iterations.png";
        writeImageToFile(&img, output_file_name, &data);
   
    // MARK:- Finish Timing
    auto finishTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime);
    std::cout << "Run time: " << duration.count() << std::endl;
    
//    system(("echo " + std::to_string(duration.count()) + " >> times.txt").c_str());
    pthread_exit(NULL);
}

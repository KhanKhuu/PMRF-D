#include <chrono>
#include <cstdint>
#include <iostream>
#include <pthread.h>
#include <string>
#include <utility>
#include <vector>
#include "../ICM/ICM.hpp"
#include "../Model/AuxMRF.hpp"
#include "../Model/ThreadData.hpp"
#include "../Utilities/io.hpp"
#include "../Utilities/LAP.hpp"

void reconstruct_image(std::vector<AuxMRF> auxMRFs, std::vector<uint8_t> *data) {
    for (auto auxMRF:  auxMRFs) {
        for (auto baseNode: auxMRF.getBaseNodes()) {
            data->at(baseNode.position) = baseNode.value;
        }
    }
}

void* thread_controller(void* threadDataVoid) {
    ThreadData* threadData = (ThreadData*) threadDataVoid;
    
    // break data up into cliques according to the LAP algorithm
    LAP(threadData->auxMRFs, threadData->data, threadData->WIDTH, threadData->HEIGHT, threadData->THREAD_ID, threadData->NUM_THREADS);
                
    // perform ICM on the cliques
    ICM(threadData->auxMRFs);
    
    // rebuild the image with the new, denoised pixel values produced by ICM
    reconstruct_image(*(threadData->auxMRFs), threadData->data);
    
    std::cout << "thread " << threadData->THREAD_ID << " finished!" << std::endl;
    pthread_exit(NULL);
}

int main(int argc, const char** argv) {
    
    // check for proper usage and return if not
    if (argc < 5) {
        std::cout << "Usage: ./PMRF-D inputImageFile.dat num_process width height" << std::endl;
        return 1;
    }
    
	// store command line args
	std::string file_name = argv[1];
    const size_t NUM_THREADS = atoi(argv[2]);
	const size_t WIDTH = atoi(argv[3]);
	const size_t HEIGHT = atoi(argv[4]);
    
	// the data vector that will hold the binary image data
    std::vector<uint8_t> data;
    
    // the structures to hold the data that will be passed along with each thread
    ThreadData threadData[NUM_THREADS];
    
    // MARK:- Threads Setup
    pthread_t threads[NUM_THREADS]; // the threads
    pthread_attr_t attributes;  // attributes to give to each
                                // thread (e.g. whether joinable or not)
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
	
	// read the data from the file into vector<uint8_t> data
	readImageFileToVector(file_name, &data);
    
    // MARK:- Run the threads
    for (size_t i = 0; i < NUM_THREADS; ++i) {
        // package the data to pass along with the thread
        threadData[i].THREAD_ID = i;
        threadData[i].data = &data;
        threadData[i].auxMRFs = &auxMRFs[i];
        threadData[i].HEIGHT = HEIGHT;
        threadData[i].WIDTH = WIDTH;
        threadData[i].NUM_THREADS = NUM_THREADS;
        
        pthread_create(&threads[i], NULL, thread_controller, (void*) &threadData[i]);
    }
    
    // free attributes
    pthread_attr_destroy(&attributes);
    
    //wait for the other threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], &status);
    }
    
    // MARK:- All threads finished
    // write the data out to a file
	writeDataVectorToFile("Output/PMRF-D_output.dat", &data, WIDTH, HEIGHT);

    // MARK:- Finish Timing
    auto finishTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime);
    std::cout << "Run time: " << duration.count() << std::endl;
    
    system(("echo " + std::to_string(duration.count()) + " >> times.txt").c_str());
    
    pthread_exit(NULL);
}

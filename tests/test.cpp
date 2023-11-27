#include <iostream>
#include <fstream>
#include <sstream>

class StreamListener : public std::streambuf {
public:
    StreamListener(std::ostream& original, std::ostream& capture)
        : originalStream(original), captureStream(capture) {
        originalStream.rdbuf(this); // Redirect cout to this buffer
    }

    ~StreamListener() {
        originalStream.rdbuf(originalStream.rdbuf()); // Restore original cout buffer
    }

protected:
    int_type overflow(int_type c) override {
        if (c != EOF) {
            captureStream.put(c); // Write captured output to capture stream
        }
        return originalStream.rdbuf()->sputc(c); // Write to original cout
    }

private:
    std::ostream& originalStream; // Reference to original cout
    std::ostream& captureStream; // Stream to capture output
};

int main() {
    std::stringstream capture;
    {
        StreamListener c(std::cout, capture); // Redirect cout to captureBuffer

        // Simulated program output
        std::cout << "Hello, this is being captured!" << std::endl;
    } // c goes out of scope here, restoring cout

    std::cout << "Retrieved from capture: " << capture.str() << std::endl;

    return 0;
}

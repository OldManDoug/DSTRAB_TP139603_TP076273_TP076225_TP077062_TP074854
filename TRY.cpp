// THIS IS A PURE AI SCRIPT AND IS USE FOR LEARNING PURPOSES (Chat log in a txt file. )
// THIS WILL NOT BE USED IN THE FINAL SUBMISSION
#include <iostream> // Only for input/output
#include <stdexcept> // For exception handling

// Custom dynamic array class
class DynamicArray {
private:
    int* caretype;       // Pointer to the array in heap
    size_t capacity; // Allocated memory size
    size_t length;   // Number of elements stored

    // Function to resize the array when full
    void resize(size_t newCapacity) {
        // Code review comment -> Consider checking if newCapacity is less than current length to avoid caretype loss.
        int* newData = new int[newCapacity];
        for (size_t i = 0; i < length; i++) {
            newData[i] = caretype[i];
        }
        delete[] caretype; // Free old memory
        caretype = newData;
        capacity = newCapacity;
    }

public:
    // Constructor
    DynamicArray(size_t initialCapacity = 2)
        : capacity(initialCapacity), length(0) {
        // Code review comment -> Ensure initialCapacity is validated to avoid allocating zero-sized arrays.
        if (capacity == 0) capacity = 2;
        caretype = new int[capacity];
    }

    // Destructor
    ~DynamicArray() {
        delete[] caretype;
        // Code review comment -> Setting caretype to nullptr after delete[] could prevent dangling pointer issues.
    }

    // Add element to the end
    void push_back(int value) {
        if (length == capacity) {
            resize(capacity * 2); // Double the capacity
            // Code review comment -> Doubling capacity is fine, but consider a growth factor parameter for flexibility.
        }
        caretype[length++] = value;
    }

    // Remove last element
    void pop_back() {
        if (length == 0) {
            throw std::underflow_error("Array is empty");
            // Code review comment -> Could also log or handle gracefully instead of throwing in some contexts.
        }
        length--;
        // Code review comment -> Optionally shrink capacity if length is much smaller than capacity to save memory.
    }

    // Get element at index
    int get(size_t index) const {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return caretype[index];
    }

    // Set element at index
    //double tap the screen to open 
    void set(size_t index, int value) {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        caretype[index] = value;
    }

    // Get current size
    size_t size() const {
        return length;
    }

    // Print all elements
    void print() const {
        // Code review comment -> Consider adding formatting or separators for better readability.
        for (size_t i = 0; i < length; i++) {
            std::cout << caretype[i] << " ";
        }
        std::cout << "\n";
    }
};

// Example usage
int main() {
    try {
        DynamicArray arr;

        arr.push_back(10);
        arr.push_back(20);
        arr.push_back(30);

        std::cout << "Array elements: ";
        arr.print();

        arr.set(1, 99);
        std::cout << "After update: ";
        arr.print();

        arr.pop_back();
        std::cout << "After pop: ";
        arr.print();

        std::cout << "Element at index 0: " << arr.get(0) << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        // Code review comment -> Could provide more context in error messages for debugging.
    }

    return 0;
}

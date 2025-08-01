 # The Huffer: A C++ Huffman Coding Project                                                                                                                   
    2                                                                                                                                                              
    3 ## Overview                                                                                                                                                  
    4                                                                                                                                                              
    5 The Huffer is a command-line C++ application that demonstrates the concept of lossless data compression using the Huffman coding
      algorithm. This project takes a text file as input, compresses it into a smaller binary file, and can decompress it back to its
      original form without any loss of data. It also includes a basic user authentication system.
    6                                                                                                                                                              
    7 This project was built to explore fundamental computer science concepts, including greedy algorithms, data structures, and low-level
      file manipulation in C++.
    8                                                                                                                                                              
    9 ## Features                                                                                                                                                  
   10                                                                                                                                                              
   11 *   **Lossless Compression**: Compresses files using the Huffman algorithm, reducing their size.
   12 *   **Decompression**: Perfectly restores the original file from its compressed version.
   13 *   **Character Frequency Analysis**: Builds the Huffman tree based on the frequency of characters in the source file.
   14 *   **User System**: A simple login/signup mechanism to manage user access.
   15                                                                                                                                                              
   16 ## Core Concepts & What I Learned                                                                                                                            
   17                                                                                                                                                              
   18 This project was a deep dive into several key areas of computer science and C++ development.
   19                                                                                                                                                              
   20 ### 1. Data Structures                                                                                                                                       
   21 *   **Binary Tree (Huffman Tree)**: The core of the project. I learned how to build a custom binary tree from the ground up using
      `Node` objects to represent characters and their paths.
   22 *   **Priority Queue (Min-Heap)**: The Standard Template Library's `std::priority_queue` was essential for efficiently building the
      Huffman tree. It's used to store nodes and repeatedly extract the two with the lowest frequencies, which is the central mechanism of
      the greedy algorithm.
   23 *   **Hash Map (`std::unordered_map`)**: Used extensively for two key purposes:
   24     1.  To store the frequency of each character in the input file.
   25     2.  To store the generated Huffman code for each character, allowing for O(1) average time complexity during the encoding process.
   26                                                                                                                                                              
   27 ### 2. Algorithms                                                                                                                                            
   28 *   **Huffman's Greedy Algorithm**: I implemented the classic greedy approach to build an optimal prefix-code tree. The main takeaway
      was understanding how making the locally optimal choice at each step (merging the two least frequent nodes) leads to a globally
      optimal solution for the entire file.
   29 *   **Tree Traversal (Recursion)**: Recursion was used to traverse the generated Huffman tree to assign binary codes to each leaf node
      (character). A similar traversal is used during decompression to navigate the tree based on the bits read from the compressed file.
   30                                                                                                                                                              
   31 ### 3. C++ and System Concepts                                                                                                                               
   32 *   **Object-Oriented Programming (OOP)**: The project is structured using classes like `Node`, `HuffmanBase`, and `LoginSignup`,
      encapsulating data and functionality for better organization and reusability.
   33 *   **File I/O**: I learned how to handle both text and binary file streams (`fstream`). This included reading a file character by
      character, and more importantly, writing and reading individual bits to and from a file for the compression/decompression logic.
   34 *   **Build Automation (CMake)**: Used `CMakeLists.txt` to define the project structure and build process, making it cross-platform
      and easier to compile.
   35                                                                                                                                                              
   36 ## Usage Examples                                                                                                                                            
   37                                                                                                                                                              
   38 The application is run from the command line and can be used for both compression and decompression.
   39                                                                                                                                                              
   40 ### Example 1: Compressing a File                                                                                                                            
   41                                                                                                                                                              
   42 To compress a file named `my_document.txt`, you would use a command similar to this:

  (Assuming the executable is in the current directory)
  ./The_Huffer_a_CPP_project.exe --compress my_document.txt compressed_file.huf


    1                                                                                                                                                              
    2 **What happens:**
    3 1.  The program reads `my_document.txt`.
    4 2.  It calculates the frequency of each character.
    5 3.  It builds the Huffman tree and generates prefix codes.
    6 4.  It writes the compressed data and the tree structure (for decompression) to `compressed_file.huf`.
    7                                                                                                                                                              
    8 ### Example 2: Decompressing a File                                                                                                                          
    9                                                                                                                                                              
   10 To restore the original file from `compressed_file.huf`:

  Decompress the file
  ./The_Huffer_a_CPP_project.exe --decompress compressed_file.huf restored_document.txt


    1                                                                                                                                                              
    2 **What happens:**
    3 1.  The program reads the Huffman tree structure from `compressed_file.huf`.
    4 2.  It reads the file bit by bit, traversing the tree to find the corresponding characters.
    5 3.  It writes the decoded characters to `restored_document.txt`, which will be identical to the original `my_document.txt`.
    6                                                                                                                                                              
    7 ## Real-World Applications of Huffman Coding                                                                                                                 
    8                                                                                                                                                              
    9 Huffman coding is a foundational compression algorithm used in many well-known technologies:
   10 *   **File Archiving**: It is used as a component in compression formats like **PKZIP**, **GZIP**, and **BZIP2**.
   11 *   **Image Formats**: Image formats like **JPEG** and **PNG** use Huffman coding (or a variation) as part of their compression
      pipeline to reduce file size.
   12 *   **Communication Protocols**: Used in protocols like **HTTP/2** for header compression to speed up web page loading.
   13 *   **Multimedia**: The **MPEG** video and **MP3** audio formats use it to compress data streams efficiently.

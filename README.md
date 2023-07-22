# Huffman_Coding_Project
The above code implements the Huffman coding algorithm for text compression. It compresses a given input string by constructing a Huffman tree based on the frequencies of characters in the input string. The Huffman tree is used to generate variable-length binary codes for each character, where more frequently occurring characters are assigned shorter codes, and less frequently occurring characters are assigned longer codes. This results in efficient compression, as the most common characters are represented by fewer bits.

Let's go through the code and its methods in detail:

1. `struct TreeNode`:
   - This is a simple structure to represent a node in the Huffman tree.
   - It contains:
     - `char info`: The character value of the node (for leaf nodes) or '\0' (for internal nodes).
     - `int freq`: The frequency (number of occurrences) of the character in the input string.
     - `TreeNode* left`: Pointer to the left child node.
     - `TreeNode* right`: Pointer to the right child node.

2. `class HuffmanCode`:
   - This is the main class that performs the Huffman coding operations.
   - Private Members:
     - `TreeNode* root`: Pointer to the root of the Huffman tree.
   - Public Members:
     - `HuffmanCode(const std::string& str)`: Constructor to initialize the Huffman tree by building it based on the input string's frequencies.
     - `std::string encode(const std::string& str)`: Encodes the input string using the generated Huffman codes.
     - `std::string decode(const std::string& code)`: Decodes the Huffman-encoded string and returns the original input string.
     - `void displayCodeTable()`: Displays the Huffman code table, showing the binary codes for each character.
     - `void displayBits(const std::string& inputString, const std::string& encodedString)`: Calculates and displays the number of bits needed before and after Huffman coding.
     - `~HuffmanCode()`: Destructor to release the memory used by the Huffman tree.

3. `HuffmanCode::HuffmanCode(const std::string& str)`:
   - Constructor to build the Huffman tree based on the character frequencies in the input string.
   - It uses a `std::unordered_map` to count the frequencies of each character in the input string.
   - The Huffman tree is constructed using a priority queue (min heap), where nodes with lower frequencies have higher priority.
   - It calls the private member function `buildHuffmanTree(frequencies)` to construct the Huffman tree.

4. `HuffmanCode::buildHuffmanTree(const std::unordered_map<char, int>& frequencies)`:
   - Builds the Huffman tree from the character frequencies stored in the `frequencies` unordered_map.
   - It uses a priority queue (min heap) to merge nodes with the lowest frequencies into a single node until a single root node is formed, representing the entire Huffman tree.

5. `HuffmanCode::buildCodes(TreeNode* node, const std::string& code, std::unordered_map<char, std::string>& codes)`:
   - Recursively constructs the Huffman codes for each character by traversing the Huffman tree.
   - It stores the binary codes for each character in the `codes` unordered_map.

6. `HuffmanCode::encode(const std::string& str)`:
   - Encodes the input string using the Huffman codes generated by the `buildCodes` method.
   - It concatenates the binary codes for each character in the input string to form the encoded string.

7. `HuffmanCode::decode(const std::string& code)`:
   - Decodes the Huffman-encoded string and returns the original input string.
   - It traverses the Huffman tree based on the binary code and extracts the characters until the entire encoded string is decoded.

8. `HuffmanCode::displayCodeTable()`:
   - Displays the Huffman code table, showing the binary codes for each character.
   - It uses the `buildCodes` method to generate the codes and then prints them on the console.

9. `HuffmanCode::displayBits(const std::string& inputString, const std::string& encodedString)`:
   - Calculates and displays the number of bits needed before and after Huffman coding.
   - It calculates the original bits based on the input string's size (each character represented by 8 bits) and displays it.
   - It also calculates the encoded bits based on the size of the Huffman-encoded string and displays it.

10. `HuffmanCode::~HuffmanCode()`:
    - Destructor to release the memory used by the Huffman tree.
    - It calls the private member function `destroyTree(root)` to delete the nodes recursively.

11. `main()`:
    - The `main` function prompts the user to input a string to be compressed using Huffman coding.
    - It creates a `HuffmanCode` object, which automatically constructs the Huffman tree and generates the Huffman codes.
    - The code table, encoded string, and bits needed before and after encoding are displayed on the console.

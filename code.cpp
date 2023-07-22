#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <bitset>

struct TreeNode
{
    char info;
    int freq;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char info, int freq) : info(info), freq(freq), left(nullptr), right(nullptr) {}
};

class HuffmanCode
{
private:
    TreeNode* root;

    struct CompareNodes
    {
        bool operator()(const TreeNode* a, const TreeNode* b) const
        {
            return a->freq > b->freq; // For min heap, lower frequency comes first
        }
    };

    void buildHuffmanTree(const std::unordered_map<char, int>& frequencies);
    void buildCodes(TreeNode* node, const std::string& code, std::unordered_map<char, std::string>& codes);
    void destroyTree(TreeNode* node);

public:
    HuffmanCode(const std::string& str);
    std::string encode(const std::string& str);
    std::string decode(const std::string& code);
    void displayCodeTable();
    void displayBits(const std::string& inputString, const std::string& encodedString);
    ~HuffmanCode();
};

HuffmanCode::HuffmanCode(const std::string& str) : root(nullptr)
{
    std::unordered_map<char, int> frequencies;
    for (char ch : str)
    {
        frequencies[ch]++;
    }
    buildHuffmanTree(frequencies);
}

void HuffmanCode::buildHuffmanTree(const std::unordered_map<char, int>& frequencies)
{
    std::priority_queue<TreeNode*, std::vector<TreeNode*>, CompareNodes> minHeap;
    for (const auto& entry : frequencies)
    {
        minHeap.push(new TreeNode(entry.first, entry.second));
    }

    while (minHeap.size() > 1)
    {
        TreeNode* left = minHeap.top();
        minHeap.pop();
        TreeNode* right = minHeap.top();
        minHeap.pop();
        TreeNode* combined = new TreeNode('\0', left->freq + right->freq);
        combined->left = left;
        combined->right = right;
        minHeap.push(combined);
    }

    root = minHeap.top();
}

void HuffmanCode::buildCodes(TreeNode* node, const std::string& code, std::unordered_map<char, std::string>& codes)
{
    if (!node)
    {
        return;
    }

    if (node->info != '\0')
    {
        codes[node->info] = code;
    }

    buildCodes(node->left, code + "0", codes);
    buildCodes(node->right, code + "1", codes);
}

std::string HuffmanCode::encode(const std::string& str)
{
    std::unordered_map<char, std::string> codes;
    buildCodes(root, "", codes);

    std::string encodedString;
    for (char ch : str)
    {
        encodedString += codes[ch];
    }
    return encodedString;
}

std::string HuffmanCode::decode(const std::string& code)
{
    std::string decodedString;
    TreeNode* currentNode = root;

    for (char ch : code)
    {
        currentNode = (ch == '0') ? currentNode->left : currentNode->right;
        if (currentNode->info != '\0')
        {
            decodedString += currentNode->info;
            currentNode = root;
        }
    }
    return decodedString;
}

void HuffmanCode::displayCodeTable()
{
    std::unordered_map<char, std::string> codes;
    buildCodes(root, "", codes);

    std::cout << "Character\tHuffman Code" << std::endl;
    for (const auto& entry : codes)
    {
        std::cout << entry.first << "\t\t" << entry.second << std::endl;
    }
}

void HuffmanCode::displayBits(const std::string& inputString, const std::string& encodedString)
{
    int originalBits = inputString.size() * 8; // Each character takes 8 bits (1 byte)
    int encodedBits = encodedString.size();
    std::cout << "Bits needed before Huffman Coding: " << originalBits << " bits" << std::endl;
    std::cout << "Bits needed after Huffman Coding: " << encodedBits << " bits" << std::endl;
}

void HuffmanCode::destroyTree(TreeNode* node)
{
    if (!node)
    {
        return;
    }
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

HuffmanCode::~HuffmanCode()
{
    destroyTree(root);
}

int main()
{
    std::string inputString;
    std::cout << "Enter the string to be encoded by Huffman Coding: ";
    std::cin >> inputString;

    HuffmanCode huffman(inputString);

    std::cout << "\nCode Table:\n";
    huffman.displayCodeTable();

    std::string encodedString = huffman.encode(inputString);

    std::cout << "\nEncoded code for the input string '" << inputString << "' is:\n";
    std::cout << encodedString << std::endl;

    huffman.displayBits(inputString, encodedString);

    std::string decodedString = huffman.decode(encodedString);
    std::cout << "\nDecoded string for the input code '" << encodedString << "' is:\n";
    std::cout << decodedString << std::endl;

    return 0;
}

// batrungcoin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <openssl/sha.h>

// Hàm băm SHA256
std::string sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input.c_str(), input.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Cấu trúc block
struct Block {
    int index;
    std::string previousHash;
    std::string data;
    int nonce;
    std::string hash;

    Block(int idx, const std::string& prevHash, const std::string& info)
        : index(idx), previousHash(prevHash), data(info), nonce(0) {
        hash = calculateHash();
    }

    std::string calculateHash() {
        std::stringstream ss;
        ss << index << previousHash << data << nonce;
        return sha256(ss.str());
    }

    void mineBlock(int difficulty) {
        std::string target(difficulty, '0');
        while (hash.substr(0, difficulty) != target) {
            nonce++;
            hash = calculateHash();
        }
    }
};

// Blockchain cơ bản
class Blockchain {
public:
    Blockchain(int difficulty) : difficulty(difficulty) {
        chain.emplace_back(Block(0, "0", "Genesis Block"));
    }

    void addBlock(const std::string& data) {
        Block newBlock(chain.size(), chain.back().hash, data);
        newBlock.mineBlock(difficulty);
        chain.push_back(newBlock);
    }

    void printChain() {
        for (const auto& block : chain) {
            std::cout << "Index: " << block.index << "\n"
                << "Previous Hash: " << block.previousHash << "\n"
                << "Data: " << block.data << "\n"
                << "Nonce: " << block.nonce << "\n"
                << "Hash: " << block.hash << "\n\n";
        }
    }

private:
    std::vector<Block> chain;
    int difficulty;
};

int main() {
    // Cấu hình blockchain
    Blockchain batrungCoin(4); // Độ khó: 4
    std::cout << "Mining Genesis Block...\n";

    // Thêm block
    batrungCoin.addBlock("Block 1: Hello Vietnam!");
    batrungCoin.addBlock("Block 2: BatrungCoin is here!");
    batrungCoin.addBlock("Block 3: Blockchain Việt Nam!");

    // Hiển thị chuỗi blockchain
    batrungCoin.printChain();

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

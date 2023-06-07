#include <iostream>
#include <fstream>
#include <string>
#include <openssl/des.h>

#pragma warning(disable:4996)
#define DES_BLOCK_SIZE   16
#define DES_encryptedFile "gptconfig.dat"
#define DES_decryptedFile ".gptconfig.temp"
#define DES_key "gptGPT@#$123456"  //DES密钥

void EncryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key)
{
    DES_cblock desKey;
    DES_key_schedule keySchedule;

    // 设置DES密钥
    DES_string_to_key(key.c_str(), &desKey);
    DES_set_key_unchecked(&desKey, &keySchedule);

    // 打开输入文件
    std::ifstream input(inputFile, std::ios::binary);
    if (!input)
    {
        std::cout << "Failed to open input file: " << inputFile << std::endl;
        return;
    }

    // 打开输出文件
    std::ofstream output(outputFile, std::ios::binary);
    if (!output)
    {
        std::cout << "Failed to open output file: " << outputFile << std::endl;
        input.close();
        return;
    }

    // 加密文件
    char buffer[DES_BLOCK_SIZE] = { 0 };
    while (input.read(buffer, DES_BLOCK_SIZE))
    {
        DES_ecb_encrypt(reinterpret_cast<const_DES_cblock*>(buffer), reinterpret_cast<DES_cblock*>(buffer), &keySchedule, DES_ENCRYPT);
        output.write(buffer, DES_BLOCK_SIZE);
    }

    // 处理最后一块不足DES_BLOCK_SIZE大小的数据
    int remainingBytes = input.gcount();
    if (remainingBytes > 0)
    {
        DES_ecb_encrypt(reinterpret_cast<const_DES_cblock*>(buffer), reinterpret_cast<DES_cblock*>(buffer), &keySchedule, DES_ENCRYPT);
        output.write(buffer, remainingBytes);
    }

    input.close();
    output.close();
}

void DecryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key)
{
    DES_cblock desKey;
    DES_key_schedule keySchedule;

    // 设置DES密钥
    DES_string_to_key(key.c_str(), &desKey);
    DES_set_key_unchecked(&desKey, &keySchedule);

    // 打开输入文件
    std::ifstream input(inputFile, std::ios::binary);
    if (!input)
    {
        std::cout << "Failed to open input file: " << inputFile << std::endl;
        return;
    }

    // 打开输出文件
    std::ofstream output(outputFile, std::ios::binary);
    if (!output)
    {
        std::cout << "Failed to open output file: " << outputFile << std::endl;
        input.close();
        return;
    }

    // 解密文件
    char buffer[DES_BLOCK_SIZE] = { 0 };
    while (input.read(buffer, DES_BLOCK_SIZE))
    {
        DES_ecb_encrypt(reinterpret_cast<const_DES_cblock*>(buffer), reinterpret_cast<DES_cblock*>(buffer), &keySchedule, DES_DECRYPT);
        output.write(buffer, DES_BLOCK_SIZE);
    }

    // 处理最后一块不足DES_BLOCK_SIZE大小的数据
    int remainingBytes = input.gcount();
    if (remainingBytes > 0)
    {
        DES_ecb_encrypt(reinterpret_cast<const_DES_cblock*>(buffer), reinterpret_cast<DES_cblock*>(buffer), &keySchedule, DES_DECRYPT);
        output.write(buffer, remainingBytes);
    }

    input.close();
    output.close();
}
// gptwintest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <vector>
#include "../src/DES.h"
#include <openssl/aes.h>
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )



int main()
{
    std::string inputFile = "input.txt";
    std::string encryptedFile = DES_encryptedFile;
    std::string decryptedFile = DES_decryptedFile;
    std::string key = DES_key;

    // 加密文件
    EncryptFile(inputFile, encryptedFile, key);
    std::cout << "File encrypted successfully." << std::endl;

    // 解密文件
    DecryptFile(encryptedFile, decryptedFile, key);
    std::cout << "File decrypted successfully." << std::endl;

    return 0;
}


std::vector<uint8_t> DecryptAES(const std::vector<uint8_t>& ciphertext, const std::string& key)
{
    AES_KEY aesKey;
    AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &aesKey);

    std::vector<uint8_t> decryptedData(ciphertext.size());
    AES_decrypt(ciphertext.data(), decryptedData.data(), &aesKey);

    return decryptedData;
}

/*
int main()
{
    std::string key = "kdFNXmc0cvFDoriW";

    // Read encrypted data from file
    std::ifstream inputFile("input.txt", std::ios::binary);
    std::vector<uint8_t> encryptedData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    std::vector<uint8_t> decryptedData = DecryptAES(encryptedData, key);

    std::string decryptedText(decryptedData.begin(), decryptedData.end());

    std::cout << "Decrypted Text: " << decryptedText << std::endl;

    return 0;
}*/

/*
int main()
{
    std::cout << "Hello World!\n";

    HMODULE module = LoadLibrary(L"D:\\code\\mygit\\MyTrojan\\build\\Release\\gptapi.dll");
    if (module == NULL) {
        std::cout << "module failed!\n";
    }
    typedef int (*GPTAPI)();
    GPTAPI gptApiFun = (GPTAPI)GetProcAddress(module, "GptMainAPI");
    if (gptApiFun == NULL) {
        std::cout << "gptApiFun failed!\n";
    }
    gptApiFun();
    Sleep(11111111111);
    return 0;
}
*/

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

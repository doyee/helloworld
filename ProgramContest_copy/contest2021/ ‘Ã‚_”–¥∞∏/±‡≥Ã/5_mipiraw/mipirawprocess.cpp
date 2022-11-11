#include <fstream>
#include <iostream>
#include <memory.h>

using namespace std;

#define INPUTPATH "mipi_1920x1080.raw"
#define OUTPUTPATH "output_1920x1080.raw"

static const int Success   = 0;
static const int Failed    = 1;
static const int NoMemory  = 2;

int ReadMipi10BitRawData(char* path, uint8_t* buffer, size_t bufferSize)
{
    int result = Success;

    if (path != NULL) {
        ifstream OpenFile(path, ios::in | ios::binary);
        if (OpenFile.fail()) {
            cout << __FUNCTION__ << " Open RAW failed, error: " << strerror(errno) << endl;
            return Failed;
        }
        OpenFile.seekg(0, ios::end);
        streampos fileSize = OpenFile.tellg();
        int32_t rawSize = (int32_t)fileSize;
        cout << __FUNCTION__ << " Raw size:" << fileSize << endl;
        OpenFile.seekg(0, ios::beg);

        if (bufferSize >= rawSize) {
                OpenFile.read((char*)buffer, rawSize);
        }else{
            cout << __FUNCTION__ << " Invalid buffer size!" << endl;
            buffer = NULL;
            result = NoMemory;
        }

        OpenFile.close();
    }
    return result;
}

int WriteImageData(char* path, uint8_t* buffer, size_t bufferSize)
{
    int result = Success;

    if (path != NULL) {
        ofstream OpenFile(path, ios::out | ios::binary);
        if (OpenFile.fail()) {
            cout << __FUNCTION__ << " Create RAW failed, error: " << strerror(errno) << endl;
            return Failed;
        }
        OpenFile.write((char*)buffer, bufferSize);
        OpenFile.close();
    }
    return result;
}


int Mipi10decode(void* src, void* dst, int32_t rawSize) {
    int result = Success;

    for (int32_t i = 0; i < rawSize; i += 5) {
        static_cast<uint16_t*>(dst)[i * 4 / 5] =
            ((static_cast<uint8_t*>(src)[i] & 0xffff) << 2) |
            (static_cast<uint8_t*>(src) [i + 4] &0x3) & 0x3ff;
        static_cast<uint16_t*>(dst)[i * 4 / 5 + 1] =
            ((static_cast<uint8_t*>(src)[i + 1] & 0xffff) << 2) |
            ((static_cast<uint8_t*>(src)[i + 4] >> 2) & 0x3) & 0x3ff;
        static_cast<uint16_t*>(dst)[i * 4 / 5 + 2] =
            ((static_cast<uint8_t*>(src)[i + 2] & 0xffff) << 2) |
            ((static_cast<uint8_t*>(src)[i + 4] >> 4) & 0x3) & 0x3ff;
        static_cast<uint16_t*>(dst)[i * 4 / 5 + 3] =
            ((static_cast<uint8_t*>(src)[i + 3] & 0xffff) << 2) |
            ((static_cast<uint8_t*>(src)[i + 4] >> 6) & 0x3) & 0x3ff;
    }
    cout << __FUNCTION__ << " finished" << endl;
    return result;
}

void Compress10to8(uint16_t* src, unsigned char* dst, int32_t size, bool need_420_521)
{
    if (need_420_521) {
        double temp;
        uint16_t tempInt;
        for (int i = 0; i < size; i++) {
            temp = src[i] / 1024.0 * 256.0;
            tempInt = (uint16_t)(temp * 10);
            tempInt = tempInt % 10;
            if (tempInt < 5 || temp > 255) {
                dst[i] = (uint8_t)temp & 0xff;
            }
            else {
                dst[i] = ((uint8_t)temp + 1) & 0xff;
            }
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            dst[i] = (src[i] >> 2) & 0xff;
        }
    }
}

int main() {
    int result = Success;

    string inputPath  = INPUTPATH;
    string outputPath = OUTPUTPATH;

    int32_t width  = 1920;
    int32_t height = 1080;

    size_t numPixel = width * height;
    uint8_t* mipiRawData = new uint8_t[numPixel * 5 / 4];
    uint16_t* rawData = new uint16_t[numPixel];
    uint8_t* rawData8bit = new uint8_t[numPixel];
    memset(rawData8bit, 0x0, numPixel);

    cout  << "Prepare to read MIPI RAW image from disk." << endl;
    result = ReadMipi10BitRawData(const_cast<char*>(inputPath.c_str()), mipiRawData, numPixel * 5 / 4);
    cout  << "Read MIPI RAW image from disk success." << endl;
    if (result == Success) {
        //Mipi10 decode
        cout  << "Prepare to decode MIPI RAW to RAW," << endl;
        result = Mipi10decode((void*)mipiRawData, (void*)rawData, numPixel * 5 / 4);
        cout  << "Decode MIPI RAW to RAW success." << endl;

        cout  << "Prepare to compress 10bit RAW to 8bit RAW." << endl;
        Compress10to8(rawData, rawData8bit, numPixel, true);
        cout  << "Compress 10bit RAW to 8bit RAW success." << endl;

        cout  << "Prepare to save 8bit RAW to disk." << endl;
        WriteImageData(const_cast<char*>(outputPath.c_str()), rawData8bit, numPixel);
        cout  << "Save 8bit RAW to disk success." << endl;

        delete[] mipiRawData;
        delete[] rawData;
        delete[] rawData8bit;
    }

    return 0;
}

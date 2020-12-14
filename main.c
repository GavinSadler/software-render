
#include <stdio.h>

typedef unsigned short WORD; // 16-bit unsigned integer (2 bytes)
typedef unsigned long DWORD; // 32-bit unsigned integer (4 bytes)
typedef long LONG;           // 32-bit signed integer   (4 bytes)
typedef unsigned char BYTE;  // 1 byte

typedef struct _bitmapFileHeader {
    WORD  bfType;      // File type, must be BM
    DWORD bfSize;      // Size in bytes of the bitmap file
    WORD  bfReserved1; // Reserved, must be 0
    WORD  bfReserved2; // Reserved, must be 0
    DWORD bfOffBits;   // The offset in bytes from the beginning of this structure to the bitmap bits
} BITMAPFILEHEADER;

// Since BITMAPFILEHEADER has struct padding, I precompute the actual size of 
// BITMAPFILEHEADER and store it in this variable for use later
const int SIZEOF_BITMAPFILEHEADER = sizeof(WORD) * 3 + sizeof(DWORD) * 2;

typedef struct _bitmapInfoHeader {
    DWORD biSize;          // Number of bytes of this structure
    LONG  biWidth;         // Width in pixels
    LONG  biHeight;        // Height in pixels
    WORD  biPlanes;        // Number of planes, set this to 1
    WORD  biBitCount;      // Bits-per-pixel, see ms docs
    DWORD biCompression;   // Set to 0 for no compression, see ms docs for more details
    DWORD biSizeImage;     // Set to 0 for non-compressed images, see ms docs for more details
    LONG  biXPelsPerMeter; // Used for device specific stuff, maybe can keep this set to 0
    LONG  biYPelsPerMeter; // Used for device specific stuff, maybe can keep this set to 0
    DWORD biClrUsed;       //
    DWORD biClrImportant;  //
} BITMAPINFOHEADER;

typedef struct _rgbQuad {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved; // Must be 0
} RGBQUAD;

int main() {
    
    BITMAPFILEHEADER fileHeader;

    fileHeader.bfType = 0x424d;
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits = SIZEOF_BITMAPFILEHEADER + sizeof(BITMAPINFOHEADER); // Pixel data starts after both the header and infoheader
    
    BITMAPINFOHEADER infoHeader;

    infoHeader.biSize = sizeof(BITMAPINFOHEADER);
    infoHeader.biWidth = 8;
    infoHeader.biHeight = 8;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 4; // 4 bits per pixel, 16 colors as defined by color table, see ms docs
    infoHeader.biSizeImage = 0;

    // TODO - Calculate size of bitmap file
    fileHeader.bfSize = 0;

    printf("BITMAPFILEHEADER: %d bytes\n", SIZEOF_BITMAPFILEHEADER);
    printf("BITMAPINFOHEADER: %d bytes\n", sizeof(BITMAPINFOHEADER));
    printf("BITMAPFILEHEADER + BITMAPINFOHEADER: %d bytes\n", SIZEOF_BITMAPFILEHEADER + sizeof(BITMAPINFOHEADER));
    printf("biSize: %d\n", infoHeader.biSize);
}

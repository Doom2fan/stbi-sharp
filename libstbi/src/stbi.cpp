// This file was developed by Thomas Müller <thomas94@gmx.net>.
// It is published under the BSD 3-Clause License within the LICENSE file.

#include <inttypes.h>

#define STBI_ASSERT(x)
#define STBI_NO_STDIO
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#elif __APPLE__
    #define EXPORT __attribute__((visibility("default")))
#else
    #define EXPORT
#endif

extern "C" {
    EXPORT bool LoadFromMemoryIntoBuffer(const unsigned char* data, int64_t len, int nDesiredChannels, unsigned char* dst) {
        // Dummy variables that are not going to be used. Returning them is unnecessary, because the probided destination buffer
        // needs to already have the correct size, hence the caller must have already requested the width, height, and number of
        // channels beforehand.
        int width, height, nChannels;
        unsigned char* tmp = stbi_load_from_memory(data, (int)len, &width, &height, &nChannels, nDesiredChannels);

        if (!tmp) {
            return false;
        }

        size_t nBytes = ((size_t)width * height) * nDesiredChannels;
        memcpy(dst, tmp, nBytes);

        stbi_image_free(tmp);
        return true;
    }

    EXPORT bool InfoFromMemory(const unsigned char* data, int64_t len, int* w, int* h, int* nChannels) {
        return stbi_info_from_memory(data, (int)len, w, h, nChannels) == 1;
    }

    EXPORT bool IsHDRFromMemory(const unsigned char *data, int64_t len) {
        return stbi_is_hdr_from_memory(data, (int)len) == 1;
    }

    EXPORT bool Is16BitFromMemory(const unsigned char *data, int64_t len) {
        return stbi_is_16_bit_from_memory(data, (int)len) == 1;
    }

    EXPORT stbi_us *Load16FromMemory(const unsigned char *data, int64_t len, int *w, int *h, int *nChannels, int nDesiredChannels) {
        return stbi_load_16_from_memory(data, (int)len, w, h, nChannels, nDesiredChannels);
    }

    EXPORT float *LoadFloatFromMemory(const unsigned char *data, int64_t len, int *w, int *h, int *nChannels, int nDesiredChannels) {
        return stbi_loadf_from_memory(data, (int)len, w, h, nChannels, nDesiredChannels);
    }

    EXPORT unsigned char* LoadFromMemory(const unsigned char* data, int64_t len, int* w, int* h, int* nChannels, int nDesiredChannels) {
        return stbi_load_from_memory(data, (int)len, w, h, nChannels, nDesiredChannels);
    }

    EXPORT void SetFlipVerticallyOnLoad(int shouldFlip) {
        stbi_set_flip_vertically_on_load(shouldFlip);
    }

    EXPORT void Free(unsigned char* pixels) {
        stbi_image_free(pixels);
    }

    EXPORT const char* FailureReason() {
        return stbi_failure_reason();
    }
}

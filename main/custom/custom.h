#ifndef CUSTOM_H
#define CUSTOM_H

#include <vector>
#include <cstdint>
#include <string_view>

class Custom
{
private:
    static void AdjustVolume(int type); // type: 1 = increase, -1 = decrease
public:
    static void AdjustVolumeCheck(char const* cmd);
    static std::vector<uint8_t> encodeAudio(const std::string_view& sound);
};


#endif // CUSTOM_H
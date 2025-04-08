#include "custom.h"
#include "application.h"
#include "board.h"
#include "audio_codec.h"
#include "display.h"
#include "assets/lang_config.h"

#include <cstring>
#include <arpa/inet.h>

void Custom::AdjustVolumeCheck(char const *cmd)
{
    if (strstr(cmd, "音量") || strstr(cmd, "声音"))
    {
        if (strstr(cmd, "大"))
        {
            AdjustVolume(1);
        }
        else if (strstr(cmd, "小"))
        {
            AdjustVolume(-1);
        }
    }
}

void Custom::AdjustVolume(int type)
{
    auto &board = Board::GetInstance();
    auto codec = board.GetAudioCodec();
    auto volume = codec->output_volume() + type * 10;
    if (volume > 100)
    {
        volume = 100;
    }
    if (volume < 0)
    {
        volume = 0;
    }
    codec->SetOutputVolume(volume);
    board.GetDisplay()->ShowNotification(Lang::Strings::VOLUME + std::to_string(volume));
}

std::vector<uint8_t> Custom::encodeAudio(const std::string_view& sound) {
    const char* data = sound.data();
    size_t size = sound.size();
    std::vector<uint8_t> opus;  // 存储所有数据块的连续数组
    size_t actual_valid_size = 0;  // 记录实际有效数据大小
    
    for (const char* p = data; p < data + size; ) {
        auto p3 = (BinaryProtocol3*)p;
        p += sizeof(BinaryProtocol3);
    
        auto payload_size = ntohs(p3->payload_size);
        opus.insert(
            opus.end(),
            p3->payload,
            p3->payload + payload_size
        );
        actual_valid_size += payload_size;  // 更新有效数据大小
    
        p += payload_size;
    }
    
    // 确保 vector 的 size 与有效数据一致
    opus.resize(actual_valid_size);
    return opus;
}
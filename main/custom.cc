#include "custom.h"
#include "board.h"
#include "audio_codec.h"
#include "display.h"
#include "assets/lang_config.h"

#include <cstring>

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
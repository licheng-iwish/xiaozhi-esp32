#ifndef CUSTOM_H
#define CUSTOM_H

class Custom
{
private:
    static void AdjustVolume(int type); // type: 1 = increase, -1 = decrease
public:
    static void AdjustVolumeCheck(char const* cmd);
};


#endif // CUSTOM_H
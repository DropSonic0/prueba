#define LockAudioDevice() SDL_LockAudioDevice(AudioDevice::device)
#define UnlockAudioDevice() SDL_UnlockAudioDevice(AudioDevice::device)

namespace RSDK
{
class AudioDevice : public AudioDeviceBase
{
public:
    static SDL_AudioDeviceID device;

    static bool32 Init();
    static void Release();

    static void FrameInit() {}

    inline static void HandleStreamLoad(ChannelInfo *channel, bool32 async)
    {
        if (async) {
            SDL_Thread *thread = SDL_CreateThread((SDL_ThreadFunction)LoadStream, "LoadStream", (void *)channel);
            if (thread) {
                SDL_DetachThread(thread); // Detach the thread
            } else {
                // Fallback to synchronous loading if thread creation failed
                // Optionally, add RSDK::PrintLog(PRINT_ERROR, "Failed to create SDL_Thread for LoadStream, loading synchronously.");
                LoadStream(channel); 
            }
        } else {
            LoadStream(channel);
        }
    }

private:
    static SDL_AudioSpec deviceSpec;

    static uint8 contextInitialized;

    static void InitAudioChannels();

    static void AudioCallback(void *data, uint8 *stream, int32 len);
};
} // namespace RSDK
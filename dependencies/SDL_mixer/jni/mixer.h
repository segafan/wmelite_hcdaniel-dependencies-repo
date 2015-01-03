/* Declarations of externally usable mixer.c routines.
 */
#ifndef MIXER_H
#define MIXER_H

typedef struct _Mix_effectinfo
{
	Mix_EffectFunc_t callback;
	Mix_EffectDone_t done_callback;
	void *udata;
	struct _Mix_effectinfo *next;
} effect_info;

typedef struct {
	Mix_Chunk *chunk;
	Uint8 *samples;
	Uint32 start_time;
	int fade_volume;
	Uint32 fade_length;
	Uint32 ticks_fade;
} Mix_Sound;

typedef struct {
	SDL_bool is_music;
	union{
		Mix_Sound *sound;
		Mix_Music *music;
	};
	int playing;
	int paused;
	int volume;
	int fade_volume_reset;
	int looping;
	int music_looping;
    int loop_start;
	int tag;
	Uint32 expire;
    Uint32 start_time;
	Mix_Fading fading;
	effect_info *effects;
} _Mix_Channel;

SDL_bool _MusicIsPlaying(Mix_Music * song);
void *Mix_DoEffects(int chan, void *snd, int len);
void _WaitForChannelFade(int channel);
Mix_Music* _ChannelPlayingMusic(int channel);
int get_available_channel(void);
void _HaltAllMusic(void);
_Mix_Channel *_StartMusic(int channel, int is_fading, Mix_Music* music);
void _ClearMusic(Mix_Music * song);

#endif

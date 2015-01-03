/* Declarations of externally usable music.c routines.
 */
#ifndef MUSIC_H
#define MUSIC_H

/* We treat music played through the old API, which doesn't support channels,
 * in a special manner: we use a non-existing, magic channel number.  This is
 * an evil hack of course. */
#define MUSIC_COMPAT_MAGIC_CHANNEL -666

int open_music(SDL_AudioSpec *mixer);
void close_music(void);
void music_mixer(void *udata, Mix_Music * music_playing, Uint8 *stream, int len, int channel);

#endif

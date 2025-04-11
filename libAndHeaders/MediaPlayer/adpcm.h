#ifndef __ADPCM_H__
#define __ADPCM_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef Word16
   #define Word16 short
#endif

#ifndef Word32
   #define Word32 int
#endif

#ifndef word16
   #define word16 short
#endif

#ifndef word32
   #define word32 int
#endif

#ifndef word8
   #define word8 char
#endif

#ifndef Word8
   #define Word8 char
#endif

typedef struct VOICE_ADPCM_STATE{
    Word16	coder;	    /* codec type */
    Word16	valprev;	/* Previous output value */
    Word8	index;		/* Index into stepsize table */
} VOICE_ADPCM_STATE_S;


extern void G711_encode(void *enc_state, Word16 *inp_buf, Word16 *out_buf, Word16 codec_type, Word16 len);
extern void G711_decode(void *dec_state, Word16 *inp_buf, Word16 *out_buf, Word16 codec_type);

extern void ADPCM_encode(VOICE_ADPCM_STATE_S *state, Word16 *inp_buf, Word16 *out_buf, Word16 coder, Word16 len);
extern void ADPCM_decode(VOICE_ADPCM_STATE_S *state, Word16 *inp_buf, Word16 *out_buf, Word16 coder, Word16 *pLen);
extern void ADPCM_state_reset(VOICE_ADPCM_STATE_S *state);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif 

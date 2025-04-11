/*
 G711�����
 */

#ifndef _G711_CODEC_H_
#define _G711_CODEC_H_

#define word16 short
#define word32 int

#define Word16 short
#define Word32 int

#define HI_VOICE_MAX_FRAME_SIZE       (960+1)    /* dont change it */

/* HISI_VOICE codec type */

/* Real-time transport protocol(RTP) */
#define G711_A                        0x01  /* 64kbps G.711 A, see RFC3551.txt  4.5.14 PCMA */
#define G711_U                        0x02  /* 64kbps G.711 U, see RFC3551.txt  4.5.14 PCMU */
#define G711_ORG_A                    0x41  /* original version 64kbps G.711 A */
#define G711_ORG_U                    0x42  /* original version 64kbps G.711 U */

#define	SIGN_BIT	(0x80)		/* Sign bit for a A-law byte. */
#define	QUANT_MASK	(0xf)		/* Quantization field mask. */
#define	NSEGS		(8)		/* Number of A-law segments. */
#define	SEG_SHIFT	(4)		/* Left shift for segment number. */
#define	SEG_MASK	(0x70)		/* Segment field mask. */

static int seg_aend[8] = { 0x1F, 0x3F, 0x7F, 0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF };
static int seg_uend[8] = { 0x3F, 0x7F, 0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF };

class G711Codec
{
	public:
		G711Codec();
		~G711Codec();

	private:

		__inline int CLZ(int x);
		__inline int N_norm_s(unsigned short a);

		void linear2alaw(word16 *pcm_val, word16 *a_val, word16 num);

		void linear2ulaw(word16 *pcm_val, word16 *u_val, word16 num);
		void alaw2linear(word16 *a_val, word16 *pcm_val, word16 num);
		void alaw2ulaw(word16 *a_val, word16 *u_val, word16 num);
		void ulaw2linear(word16 *u_val, word16 *pcm_val, word16 num);
		void ulaw2alaw(word16 *u_val, word16 *a_val, word16 num);
		void G711_A_DEC(word16 *a_val, word16 *pcm, word16 pcm_len);
		void G711_A_ENC(word16 *a_val, word16 *pcm, word16 pcm_len);
		void G711_U_DEC(word16 *u_val, word16 *pcm, word16 pcm_len);
		void G711_U_ENC(word16 *u_val, word16 *pcm, word16 pcm_len);
		void encoder_pack(Word16 prm[], Word16 bits[], short len);
		void encoder_org_pack(Word16 prm[], Word16 bits[], short len);
		void decoder_unpack(Word16 bits[], Word16 parm[]);
		void decoder_org_unpack(Word16 bits[], Word16 parm[]);

		int search(int val, int * table, int size);
		int alaw2linear(int a_val);
		int linear2alaw(int pcm_val);
		int ulaw2linear(int u_val);

	public:
		void G711_encode(Word16 *inp_buf, Word16 *out_buf, Word16 codec_type, Word16 len);
		void G711_decode(Word16 *inp_buf, Word16 *out_buf, Word16 codec_type);

		void DecodeBuf(char *pInData, long inLen, char *pOutData, int encodeType);
        bool DecodeBuf5P(unsigned char *pInData, int inLen, unsigned char *pOutData, int *pOutLen, int type);
		void EncodeBuf(char *pInData, long inLen, char *pOutData);
        bool EncodeBuf4P(unsigned char *pInData, int inLen, unsigned char *pOutData, int *pOutLen);
	public:

		int m_iHisiVoiceState;
};

#endif //_G711_CODEC_H_

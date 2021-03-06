/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
// screen.h

typedef struct playerview_s playerview_t;

extern	float		scr_con_current;
extern	float		scr_con_target;		// lines of console to display

extern	int			sb_lines;

extern	int			clearnotify;	// set to 0 whenever notify text is drawn
extern	qboolean	scr_disabled_for_loading;

extern	cvar_t		scr_fov;
extern	cvar_t		scr_fov_viewmodel;
extern	cvar_t		scr_viewsize;

qboolean SCR_RSShot (void);

//void SCR_DrawConsole (qboolean noback);
//void SCR_SetUpToDrawConsole (void);

//void SCR_BeginLoadingPlaque (void);
//void SCR_EndLoadingPlaque (void);


//void SCR_Init (void);

//void SCR_UpdateScreen (void);

#if defined(GLQUAKE)
qboolean GLSCR_UpdateScreen (void);
#endif

void SCR_ImageName (const char *mapname);

//this stuff is internal to the screen systems.
void RSpeedShow(void);

void SCR_CrosshairPosition(playerview_t *pview, float *x, float *y);
void SCR_DrawLoading (qboolean opaque);
void SCR_TileClear (int skipbottom);
void SCR_DrawNotifyString (void);
void SCR_CheckDrawCenterString (void);
void SCR_DrawNet (void);
void SCR_DrawTurtle (void);
void SCR_DrawPause (void);
qboolean SCR_HardwareCursorIsActive(void);

void CLSCR_Init(void);	//basically so I can register a few friendly cvars.

//TEI_SHOWLMP2 stuff
void SCR_ShowPics_Draw(void);
void SCR_ShowPic_Create(void);
void SCR_ShowPic_Hide(void);
void SCR_ShowPic_Move(void);
void SCR_ShowPic_Update(void);
void SCR_ShowPic_ClearAll(qboolean persistflag);
char *SCR_ShowPics_ClickCommand(int cx, int cy);
void SCR_ShowPic_Script_f(void);
void SCR_ShowPic_Remove_f(void);

//a header is better than none...
void Draw_TextBox (int x, int y, int width, int lines);
enum fs_relative;


typedef enum uploadfmt
{
	PTI_INVALID,

	//these formats are specified as direct byte access (listed in byte order, aka big-endian 0xrrggbbaa order)
	PTI_RGBA8,	//rgba byte ordering
	PTI_RGBX8,	//rgb pad byte ordering
	PTI_BGRA8,	//alpha channel
	PTI_BGRX8,	//no alpha channel
	PTI_RGBA8_SRGB,	//rgba byte ordering
	PTI_RGBX8_SRGB,	//rgb pad byte ordering
	PTI_BGRA8_SRGB,	//alpha channel
	PTI_BGRX8_SRGB,	//no alpha channel
	PTI_RGB8,		//24bit packed format. generally not supported
	PTI_BGR8,		//24bit packed format. generally not supported
	PTI_L8,			//8bit format. luminance gets flooded to all RGB channels. might be supported using swizzles.
	PTI_L8A8,		//16bit format. L=luminance. might be supported using swizzles.
	PTI_L8_SRGB,	//8bit format. luminance gets flooded to all RGB channels. might be supported using swizzles.
	PTI_L8A8_SRGB,	//16bit format. L=luminance. note: this cannot be implemented as a swizzle as there's no way to get srgb on red without it on green.
	//small formats.
	PTI_R8,			//used for paletted data
	PTI_RG8,		//might be useful for normalmaps
	PTI_R8_SNORM,
	PTI_RG8_SNORM,	//might be useful for normalmaps
	//floating point formats
	PTI_RGBA16F,
	PTI_RGBA32F,
	//packed/misaligned formats: these are specified in native endian order (high bits listed first because that's how things are represented in hex), so may need byte swapping...
	PTI_A2BGR10,	//mostly for rendertargets, might also be useful for overbight lightmaps.
	PTI_E5BGR9,		//mostly for fancy lightmaps
	PTI_RGB565,		//16bit alphaless format.
	PTI_RGBA4444,	//16bit format (gl)
	PTI_ARGB4444,	//16bit format (d3d)
	PTI_RGBA5551,	//16bit alpha format (gl).
	PTI_ARGB1555,	//16bit alpha format (d3d).
	//(desktop/tegra) compressed formats
	PTI_BC1_RGB,
	PTI_BC1_RGB_SRGB,
	PTI_BC1_RGBA,
	PTI_BC1_RGBA_SRGB,
	PTI_BC2_RGBA,
	PTI_BC2_RGBA_SRGB,
	PTI_BC3_RGBA,	//maybe add a bc3 normalmapswizzle type for d3d9?
	PTI_BC3_RGBA_SRGB,
	PTI_BC4_R8,
	PTI_BC4_R8_SNORM,
	PTI_BC5_RG8,	//useful for normalmaps
	PTI_BC5_RG8_SNORM,	//useful for normalmaps
	PTI_BC6_RGB_UFLOAT,	//unsigned (half) floats!
	PTI_BC6_RGB_SFLOAT,	//signed (half) floats!
	PTI_BC7_RGBA,	//multimode compression, using as many bits as bc2/bc3
	PTI_BC7_RGBA_SRGB,
	//(mobile/intel) compressed formats
	PTI_ETC1_RGB8,	//limited form
	PTI_ETC2_RGB8,	//extended form
	PTI_ETC2_RGB8A1,
	PTI_ETC2_RGB8A8,
	PTI_ETC2_RGB8_SRGB,
	PTI_ETC2_RGB8A1_SRGB,
	PTI_ETC2_RGB8A8_SRGB,
	PTI_EAC_R11,	//no idea what this might be used for, whatever
	PTI_EAC_R11_SNORM,	//no idea what this might be used for, whatever
	PTI_EAC_RG11,	//useful for normalmaps (calculate blue)
	PTI_EAC_RG11_SNORM,	//useful for normalmaps (calculate blue)
	//astc... zomg
	PTI_ASTC_4X4,
	PTI_ASTC_4X4_SRGB,
	PTI_ASTC_5X4,
	PTI_ASTC_5X4_SRGB,
	PTI_ASTC_5X5,
	PTI_ASTC_5X5_SRGB,
	PTI_ASTC_6X5,
	PTI_ASTC_6X5_SRGB,
	PTI_ASTC_6X6,
	PTI_ASTC_6X6_SRGB,
	PTI_ASTC_8X5,
	PTI_ASTC_8X5_SRGB,
	PTI_ASTC_8X6,
	PTI_ASTC_8X6_SRGB,
	PTI_ASTC_10X5,
	PTI_ASTC_10X5_SRGB,
	PTI_ASTC_10X6,
	PTI_ASTC_10X6_SRGB,
	PTI_ASTC_8X8,
	PTI_ASTC_8X8_SRGB,
	PTI_ASTC_10X8,
	PTI_ASTC_10X8_SRGB,
	PTI_ASTC_10X10,
	PTI_ASTC_10X10_SRGB,
	PTI_ASTC_12X10,
	PTI_ASTC_12X10_SRGB,
	PTI_ASTC_12X12,
	PTI_ASTC_12X12_SRGB,

	//depth formats
	PTI_DEPTH16,
	PTI_DEPTH24,
	PTI_DEPTH32,
	PTI_DEPTH24_8,

	//non-native formats (generally requiring weird palettes that are not supported by hardware)
	TF_BGR24_FLIP,			/*bgr byte order, no alpha channel nor pad, and bottom up*/
	TF_MIP4_R8,		/*8bit 4-mip greyscale image*/
	TF_MIP4_SOLID8,	/*8bit 4-mip image in default palette*/
	TF_MIP4_8PAL24,	/*8bit 4-mip image with included palette*/
	TF_MIP4_8PAL24_T255,/*8bit 4-mip image with included palette where index 255 is alpha 0*/
	TF_SOLID8,      /*8bit quake-palette image*/
	TF_TRANS8,      /*8bit quake-palette image, index 255=transparent*/
	TF_TRANS8_FULLBRIGHT,   /*fullbright 8 - fullbright texels have alpha 255, everything else 0*/
	TF_HEIGHT8,     /*image data is greyscale, convert to a normalmap and load that, uploaded alpha contains the original heights*/
	TF_HEIGHT8PAL, /*source data is palette values rather than actual heights, generate a fallback heightmap*/
	TF_H2_T7G1, /*8bit data, odd indexes give greyscale transparence*/
	TF_H2_TRANS8_0, /*8bit data, 0 is transparent, not 255*/
	TF_H2_T4A4,     /*8bit data, weird packing*/

	PTI_LLLX8,		/*RGB data where the RGB values were all the same. we can convert to L8 to use less memory (common with shirt/pants/reflection)*/
	PTI_LLLA8,		/*RGBA data where the RGB values were all the same. we can convert to LA8 to use less memory (common with gloss)*/

	/*this block requires an explicit (separate) palette*/
	TF_8PAL24,
	TF_8PAL32,

#ifdef FTE_TARGET_WEB
	//weird specialcase mess to take advantage of webgl so we don't need redundant bloat where we're already strugging with potential heap limits
	PTI_WHOLEFILE,
#endif

	PTI_MAX,

	TF_INVALID = PTI_INVALID,
	TF_DEPTH16 = PTI_DEPTH16,
	TF_DEPTH24 = PTI_DEPTH24,
	TF_DEPTH32 = PTI_DEPTH32,
	TF_RGBA16F = PTI_RGBA16F,
	TF_RGBA32F = PTI_RGBA32F,
	TF_RGBA32 = PTI_RGBA8,              /*rgba byte order*/
	TF_BGRA32 = PTI_BGRA8,              /*bgra byte order*/
	TF_RGBX32 = PTI_RGBX8,              /*rgb byte order, with extra wasted byte after blue*/
	TF_BGRX32 = PTI_BGRX8,              /*rgb byte order, with extra wasted byte after blue*/
	TF_RGB24 = PTI_RGB8,				/*rgb byte order, no alpha channel nor pad, and regular top down*/
	TF_BGR24 = PTI_BGR8,               /*bgr byte order, no alpha channel nor pad, and regular top down*/
	TF_LUM8 = PTI_L8,
	TF_R8 = PTI_R8

	//these are emulated formats. this 'case' value allows drivers to easily ignore them
#define PTI_EMULATED 	TF_INVALID:case TF_BGR24_FLIP:case TF_MIP4_R8:case TF_MIP4_SOLID8:case TF_MIP4_8PAL24:case TF_MIP4_8PAL24_T255:case TF_SOLID8:case TF_TRANS8:case TF_TRANS8_FULLBRIGHT:case TF_HEIGHT8:case TF_HEIGHT8PAL:case TF_H2_T7G1:case TF_H2_TRANS8_0:case TF_H2_T4A4:case TF_8PAL24:case TF_8PAL32:case PTI_LLLX8:case PTI_LLLA8
} uploadfmt_t;

qboolean SCR_ScreenShot (char *filename, enum fs_relative fsroot, void **buffer, int numbuffers, int bytestride, int width, int height, enum uploadfmt fmt, qboolean writemeta);

void SCR_DrawTwoDimensional(int uimenu, qboolean nohud);

enum
{
	LS_NONE,
	LS_CONNECTION,
	LS_SERVER,
	LS_CLIENT,
};
int SCR_GetLoadingStage(void);
void SCR_SetLoadingStage(int stage);
void SCR_SetLoadingFile(char *str);

/*fonts*/
void Font_Init(void);
void Font_Shutdown(void);
int Font_RegisterTrackerImage(const char *image);	//returns a unicode char value that can be used to embed the char within a line of text.
qboolean Font_TrackerValid(unsigned int imid);
struct font_s *Font_LoadFont(const char *fontfilename, float height);
void Font_Free(struct font_s *f);
void Font_BeginString(struct font_s *font, float vx, float vy, int *px, int *py);
void Font_BeginScaledString(struct font_s *font, float vx, float vy, float szx, float szy, float *px, float *py); /*avoid using*/
void Font_Transform(float vx, float vy, int *px, int *py);
int Font_CharHeight(void);
float Font_CharVHeight(struct font_s *font);
float Font_CharScaleHeight(void);
int Font_CharWidth(unsigned int charflags, unsigned int codepoint);
float Font_CharScaleWidth(unsigned int charflags, unsigned int codepoint);
int Font_CharEndCoord(struct font_s *font, int x, unsigned int charflags, unsigned int codepoint);
int Font_DrawChar(int px, int py, unsigned int charflags, unsigned int codepoint);
float Font_DrawScaleChar(float px, float py, unsigned int charflags, unsigned int codepoint); /*avoid using*/
void Font_EndString(struct font_s *font);
void Font_InvalidateColour(vec4_t newcolour);
/*these three functions deal with formatted blocks of text (including tabs and new lines)*/
fte_inline conchar_t *Font_Decode(conchar_t *start, unsigned int *codeflags, unsigned int *codepoint)
{
	if (*start & CON_LONGCHAR)
		if (!(*start & CON_RICHFORECOLOUR))
		{
			*codeflags = start[1] & CON_FLAGSMASK;
			*codepoint = ((start[0] & CON_CHARMASK)<<16) | (start[1] & CON_CHARMASK);
			return start+2;
		}

	*codeflags = start[0] & CON_FLAGSMASK;
	*codepoint = start[0] & CON_CHARMASK;
	return start+1;
}
conchar_t *Font_DecodeReverse(conchar_t *start, conchar_t *stop, unsigned int *codeflags, unsigned int *codepoint);
int Font_LineBreaks(conchar_t *start, conchar_t *end, int maxpixelwidth, int maxlines, conchar_t **starts, conchar_t **ends);
int Font_LineWidth(conchar_t *start, conchar_t *end);
float Font_LineScaleWidth(conchar_t *start, conchar_t *end);
void Font_LineDraw(int x, int y, conchar_t *start, conchar_t *end);
conchar_t *Font_CharAt(int x, conchar_t *start, conchar_t *end);
extern struct font_s *font_default;
extern struct font_s *font_console;
extern struct font_s *font_tiny;
void PR_ReleaseFonts(unsigned int purgeowner);	//for menu/csqc
void PR_ReloadFonts(qboolean reload);
/*end fonts*/

//normally we're not srgb aware, which means that while the intensity may APPEAR linear, it actually isn't.
fte_inline float M_SRGBToLinear(float x, float mag)
{
	x /= mag;
	if (x <= 0.04045f)
		x = x * (1.0f / 12.92f);
	else
		x = pow(( x + 0.055f) * (1.0f / 1.055f), 2.4f);
	x *= mag;
	return x;
}
fte_inline float M_LinearToSRGB(float x, float mag)
{
	x /= mag;
	if (x <= 0.00031308)
		x = 12.92 * x;
	else
		x = 1.055*pow(x,(float)(1.0 / 2.4) ) - 0.055;
	x *= mag;
	return x;
}
//macros that are used to explicitly state that a value is srgb, and convert to linear as needed.
#define SRGBf(x) ((vid.flags&VID_SRGBAWARE)?M_SRGBToLinear(x,1):x)
#define SRGBb(x) ((vid.flags&VID_SRGBAWARE)?(unsigned char)M_SRGBToLinear(x,255):x)
#define SRGB3(x,y,z) SRGBf(x),SRGBf(y),SRGBf(z)
#define SRGBA(x,y,z,w) SRGBf(x),SRGBf(y),SRGBf(z),w

void R_NetgraphInit(void);
void R_NetGraph (void);
void R_FrameTimeGraph (float frametime);

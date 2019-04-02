#ifndef INCLUDED__GW__GRAPHIC__COLOR__HPP
#define INCLUDED__GW__GRAPHIC__COLOR__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: color.hpp
//
// Created by code1009.
// Created on Dec-17th, 2014.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{



/////////////////////////////////////////////////////////////////////////////
//
// Class: color
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class color
{
private:
	cx::byte_t _R;
	cx::byte_t _G;
	cx::byte_t _B;
	cx::byte_t _A;

public:
	color();
	color(cx::byte_t r, cx::byte_t g, cx::byte_t b, cx::byte_t a=0xFFu);
	color(const color& o);
//	virtual ~color();

public:
	color& operator=(const color& rhs);

public:
	cx::bool_t operator==(const color& rhs);
	cx::bool_t operator!=(const color& rhs);

public:
	void set (cx::byte_t r, cx::byte_t g, cx::byte_t b, cx::byte_t a=0xFFu);
	void set_ARGB (cx::uint_t ARGB_value);
	void set_ABGR (cx::uint_t ABGR_value);

public:
	cx::byte_t R(void);
	cx::byte_t G(void);
	cx::byte_t B(void);
	cx::byte_t A(void);

	void R(cx::byte_t r);
	void G(cx::byte_t g);
	void B(cx::byte_t b);
	void A(cx::byte_t a);

public:
	// GDI  COLORREF ABGR
	cx::uint_t ABGR(void);

	// GDI+ Color    ARGB
	cx::uint_t ARGB(void);

public:
	cx::bool_t get_alpha_zero (void);
	void       set_alpha_zero (void);
	void       set_alpha      (cx::float_t f);

public:
	void set_red   (cx::float_t f); 
	void set_green (cx::float_t f);
	void set_blue  (cx::float_t f);

public:
	static const color AliceBlue           ;
	static const color AntiqueWhite        ;
	static const color Aqua                ;
	static const color Aquamarine          ;
	static const color Azure               ;
	static const color Beige               ;
	static const color Bisque              ;
	static const color Black               ;
	static const color BlanchedAlmond      ;
	static const color Blue                ;
	static const color BlueViolet          ;
	static const color Brown               ;
	static const color Burlywood           ;
	static const color CadetBlue           ;
	static const color Chartreuse          ;
	static const color Chocolate           ;
	static const color Coral               ;
	static const color CornflowerBlue      ;
	static const color Cornsilk            ;
	static const color Crimson             ;
	static const color Cyan                ;
	static const color DarkBlue            ;
	static const color DarkCyan            ;
	static const color DarkGoldenRod       ;
	static const color DarkGray            ;
	static const color DarkGreen           ;
	static const color DarkKhaki           ;
	static const color DarkMagenta         ;
	static const color DarkOliveGreen      ;
	static const color DarkOrange          ;
	static const color DarkOrchid          ;
	static const color DarkRed             ;
	static const color DarkSalmon          ;
	static const color DarkSeaGreen        ;
	static const color DarkSlateBlue       ;
	static const color DarkSlateGray       ;
	static const color DarkTurquoise       ;
	static const color DarkViolet          ;
	static const color DeepPink            ;
	static const color DeepSkyBlue         ;
	static const color DimGray             ;
	static const color DodgerBlue          ;
	static const color FireBrick           ;
	static const color FloralWhite         ;
	static const color ForestGreen         ;
	static const color Fuchsia             ;
	static const color Gainsboro           ;
	static const color GhostWhite          ;
	static const color Gold                ;
	static const color GoldenRod           ;
	static const color Gray                ;
	static const color Green               ;
	static const color GreenYellow         ;
	static const color HoneyDew            ;
	static const color HotPink             ;
	static const color IndianRed           ;
	static const color Indigo              ;
	static const color Ivory               ;
	static const color Khaki               ;
	static const color Lavender            ;
	static const color LavenderBlush       ;
	static const color Lawngreen           ;
	static const color LemonChiffon        ;
	static const color LightBlue           ;
	static const color LightCoral          ;
	static const color LightCyan           ;
	static const color LightGoldenRodYellow;
	static const color LightGreen          ;
	static const color LightGray           ;
	static const color LightPink           ;
	static const color LightSalmon         ;
	static const color LightSeaGreen       ;
	static const color LightSkyBlue        ;
	static const color LightSlateGray      ;
	static const color LightSteelBlue      ;
	static const color LightYellow         ;
	static const color Lime                ;
	static const color LimeGreen           ;
	static const color Linen               ;
	static const color Magenta             ;
	static const color Maroon              ;
	static const color MediumAquamarine    ;
	static const color MediumBlue          ;
	static const color MediumOrchid        ;
	static const color MediumPurple        ;
	static const color MediumSeaGreen      ;
	static const color MediumSlateBlue     ;
	static const color MediumSpringGreen   ;
	static const color MediumTurquoise     ;
	static const color MediumVioletRed     ;
	static const color MidnightBlue        ;
	static const color MintCream           ;
	static const color MistyRose           ;
	static const color Moccasin            ;
	static const color NavajoWhite         ;
	static const color Navy                ;
	static const color Navyblue            ;
	static const color OldLace             ;
	static const color Olive               ;
	static const color OliveDrab           ;
	static const color Orange              ;
	static const color OrangeRed           ;
	static const color Orchid              ;
	static const color PaleGoldenRod       ;
	static const color PaleGreen           ;
	static const color PaleTurquoise       ;
	static const color PaleVioletRed       ;
	static const color PapayaWhip          ;
	static const color PeachPuff           ;
	static const color Peru                ;
	static const color Pink                ;
	static const color Plum                ;
	static const color PowderBlue          ;
	static const color Purple              ;
	static const color Red                 ;
	static const color RosyBrown           ;
	static const color RoyalBlue           ;
	static const color SaddleBrown         ;
	static const color Salmon              ;
	static const color SandyBrown          ;
	static const color SeaGreen            ;
	static const color SeaShell            ;
	static const color Sienna              ;
	static const color Silver              ;
	static const color SkyBlue             ;
	static const color SlateBlue           ;
	static const color SlateGray           ;
	static const color Snow                ;
	static const color SpringGreen         ;
	static const color SteelBlue           ;
	static const color Tan                 ;
	static const color Teal                ;
	static const color Thistle             ;
	static const color Tomato              ;
	static const color Turquoise           ;
	static const color Violet              ;
	static const color Wheat               ;
	static const color White               ;
	static const color WhiteSmoke          ;
	static const color Yellow              ;
	static const color YellowGreen         ;
};

	
	
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cx::byte_t color_level(cx::byte_t v, cx::float_t f);
color      color_level(color      v, cx::float_t f);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif



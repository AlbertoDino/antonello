#include <rde_engine/lib.h>
#include "color.h"

namespace colors
{

	//### A
	 Vector4f AntiqueWhite3;
	//### B
	 Vector4f Black;
	 Vector4f Burlywood;
	 Vector4f Burlywood3;
	//### C
	 Vector4f Chartreuse2;  // green/yellow
	 Vector4f Chartreuse3;
	 Vector4f Cornsilk2;
	 Vector4f Cornsilk3;
	//### D
	 Vector4f DarkBlue;
	 Vector4f DarkGray;
	 Vector4f DeepPink;	//fucsia
	 Vector4f DarkSlateGray3;
	 Vector4f DodgerBlue2;
	 Vector4f DodgerBlue3;
	 Vector4f DimGrey;
	 Vector4f DarkSlateGray;

	///### F
	 Vector4f Firebrick3;

	//### W
	 Vector4f White;

	//### G
	 Vector4f GoldenRod;
	 Vector4f Grey47;
	 Vector4f Grey60;
	 Vector4f Green;

	//### M
	 Vector4f MediumPurple3;
	 Vector4f MediumPurple4;

	//### N
	 Vector4f Navy;

	//### H
	 Vector4f Honeydew4;
	 Vector4f Honeydew3;
	 Vector4f HotPink;

	//#### I
	 Vector4f Ivory3;
	 Vector4f Ivory4;
	//#### Y
	 Vector4f Yellow;

	//### L
	 Vector4f LightCyan1;
	 Vector4f LightBlue4;
	 Vector4f LightSkyBlue2;
	 Vector4f LightSkyBlue3;
	 Vector4f LightSkyBlue4;
	 Vector4f LightSteelBlue4;
	 Vector4f LavenderBlush2;
	 Vector4f LavenderBlush3;
	 Vector4f LavenderBlush4;
	//### O
	 Vector4f OrangeRed;
	 Vector4f Orange;

	//### R
	 Vector4f Red;
	 Vector4f RoyalBlue3;
	 Vector4f RoyalBlue4;

	//### S
	 Vector4f SeaGreen1;
	 Vector4f SeaGreen4;
	 Vector4f Seashell3;
	 Vector4f Seashell4;
	 Vector4f SlateGray4;
	 Vector4f Snow4;
	 Vector4f SkyBlue;
	 Vector4f SpringGreen;
	 Vector4f SpringGreen4; //green/sea
	 Vector4f SteelBlue;
	 Vector4f SteelBlue3;
	 Vector4f SteelBlue4;

	 void SetColor(Vector4f& color, float32 r, float32 g, float32 b) {
		 vSet(color, Color255To1(r), Color255To1(g), Color255To1(b), COLOR_ALPHA);
	 }

	 void InitColors()
	 {
		 //### A

		 SetColor(AntiqueWhite3, 205, 192, 176);
		 //### B
		 vSet(Black, 0.0f, 0.0f, 0.0f, COLOR_ALPHA);
		 SetColor(Burlywood, 222, 184, 135);
		 SetColor(Burlywood3, 205, 170, 125);
		 //### C
		 SetColor(Chartreuse2, 118, 238, 0);
		 SetColor(Chartreuse3, 102, 205, 0);

		 SetColor(Cornsilk2, 238, 232, 205);
		 SetColor(Cornsilk3, 205, 200, 177);

		 //### D
		 SetColor(DarkBlue, 0, 0, 139);
		 SetColor(DarkGray, 128, 128, 128);
		 SetColor(DeepPink, 255, 20, 147);
		 SetColor(DarkSlateGray3, 121, 205, 205);
		 SetColor(DodgerBlue2, 28, 134, 238);
		 SetColor(DodgerBlue3, 24, 116, 205);
		 SetColor(DimGrey, 105, 105, 105);
		 SetColor(DarkSlateGray, 47, 79, 79);

		 ///### F
		 SetColor(Firebrick3, 205, 38, 38);
		 //### W
		 vSet(White, 1.0f, 1.0f, 1.0f, 1.0f);
		 //### G
		 SetColor(GoldenRod, 218, 165, 32);
		 SetColor(Grey47, 120, 120, 120);
		 SetColor(Grey60, 153, 153, 153);
		 SetColor(Green, 0, 255, 0);
		 //### M
		 SetColor(MediumPurple3, 137, 104, 205);
		 SetColor(MediumPurple4, 93, 71, 139);

		 //### N
		 SetColor(Navy, 0.0f, 0.0f, 128);
		 //### H
		 SetColor(Honeydew4, 131, 139, 131);
		 SetColor(Honeydew3, 193, 205, 193);
		 SetColor(HotPink, 255, 105, 180);
		 //#### I
		 SetColor(Ivory3, 205, 205, 193);
		 SetColor(Ivory4, 139, 139, 131);
		 //#### Y		
		 SetColor(Yellow, 255, 255, 0);
		 //### L

		 SetColor(LightCyan1, 224, 255, 255);
		 SetColor(LightBlue4, 104, 131, 139);
		 SetColor(LightSkyBlue2, 164, 211, 238);
		 SetColor(LightSkyBlue3, 141, 182, 205);
		 SetColor(LightSkyBlue4, 104, 131, 139);
		 SetColor(LightSteelBlue4, 110, 123, 139);
		 SetColor(LavenderBlush2, 238, 224, 229);
		 SetColor(LavenderBlush3, 205, 193, 197);
		 SetColor(LavenderBlush4, 139, 131, 134);

		 //### O
		 SetColor(OrangeRed, 255, 69, 01);
		 SetColor(Orange, 255, 165, 0);
		 //### R	
		 SetColor(Red, 255, 0, 0);
		 SetColor(RoyalBlue3, 58, 95, 205);
		 SetColor(RoyalBlue4, 39, 64, 139);
		 //### S
		 SetColor(SeaGreen1, 84, 255, 159);
		 SetColor(SeaGreen4, 0, 139, 69);
		 SetColor(Seashell3, 205, 197, 191);
		 SetColor(Seashell4, 139, 134, 130);
		 SetColor(SlateGray4, 108, 123, 139);
		 SetColor(SkyBlue, 135, 206, 235);
		 SetColor(Snow4, 139, 137, 137);
		 SetColor(SpringGreen, 0, 255, 127);
		 SetColor(SpringGreen4, 0, 139, 69);
		 SetColor(SteelBlue, 70, 130, 180);
		 SetColor(SteelBlue3, 79, 148, 205);
		 SetColor(SteelBlue4, 54, 100, 139);

	 }
}
#include <QtCore/QCoreApplication>
#include <QImage>
#include "Filter.h"
#include <iostream>
#include <Bits.h>


using std::string;
using std::cout;
using std::endl;



//void Dilation(BIT* source[], bool* mask[], BIT* result[])
//{
//	// Width, Height Ц размеры исходного и результирующего изображений
//	// MW, MH Ц размеры структурного множества
//	for (y = MH / 2; y < Height Ц MH / 2; y++)
//		for (x = MW / 2; x < Width Ц MW / 2; x++)
//		{
//			BIT max = 0;
//			for (j = -MH / 2; j <= MH / 2; j++)
//				for (i = -MW / 2; i <= MW / 2; i++)
//					if ((mask[i][j]) && (source[x + i][y + j] > max))
//					{
//						max = source[x + i][y + j];
//					}
//			result[x][y] = max;
//		}
//}


void main(int argc, char *argv[])
{
	

    //QCoreApplication a(argc, argv);

    //return a.exec();
	string s = string();
	QImage img;
	
	string second_s;
	QImage second_img;


	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-p") && (i + 1 < argc))
		{
			if (s == string())
			{
				s = argv[i + 1];
			}
			else
			{
				second_s = argv[i + 1];
			}
			
		}
	}

	//перва€ фотка
	img.load(QString(s.c_str()));
	img.save("Art/Source.png");

	//следующа€
	second_img.load(QString(second_s.c_str()));
	second_img.save("ImagesCat1/Source.png");

	cout << second_img.bitPlaneCount() << endl;
	cout << second_img.bits() << endl;
	cout << second_img.constBits() << endl;
	cout << second_img.bytesPerLine() << endl;
	cout << second_img.color(1) << endl;


	/*InvertFilter invert;
	invert.process(img).save("Art/Invert.png");

	BlurFilter blur(3);
	blur.process(img).save("Art/Blur.png");

	GaussianFilter filter(3, 2);
	filter.process(img).save("Art/GaussianBlur.png");

	GrayScaleFilter gray;
	gray.process(img).save("Art/GrayScale.png");

	SepiaFilter sepia;
	sepia.process(img).save("Art/Sepia.png");

	BrightFilter bright;
	bright.process(img).save("Art/Bright.png");*/

	/*SobelFilter sobel;
	sobel.process(img).save("Art/Sobel.png");*/

	/*SharpnessFilter sharpness;
	sharpness.process(img).save("Art/Sharpness.png");*/

	/*PerfectReflectionFilter reflection;
	reflection.process(img).save("Art/PerfectReflection.png");*/

	//белое или черное
	/*WhiteLinesFilter lines;
	lines.process(img).save("Art/whitelines.png");*/

	/*LinearTensionFilter Tension;
	Tension.process(img).save("Art/LinearTension.png");*/

	/*TurnFilter Turn;
	Turn.process(img).save("Art/Turn.png");
	
	WavesFilter Waves;
	Waves.process(img).save("Art/Wave.png");*/

	/*TurnFilter Turn;
	Turn.process(second_img).save("ImagesCat1/Turn.png");

	WavesFilter Waves;
	Waves.process(second_img).save("ImagesCat1/Wave.png");*/

	/*SharpnessSecondFilter SharpnessSecond;
	SharpnessSecond.process(second_img).save("ImagesCat1/SharpnessSecond.png");*/

	/*GlassFilter Glass;
	Glass.process(second_img).save("ImagesCat1/Glass.png");*/
	
	/*BordersSharraFilter BordersSharra;
	BordersSharra.process(second_img).save("ImagesCat1/BordersSharra.png");*/

	/*BordersPruttaFilter BordersPrutta;
	BordersPrutta.process(second_img).save("ImagesCat1/BordersPrutta.png");*/

	/*int n = 5;
	MotionBlurFilter MotionBlur(2*n+1,n);
	MotionBlur.process(second_img).save("ImagesCat1/MotionBlur.png");*/


}

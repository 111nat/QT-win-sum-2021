#include <QtCore/QCoreApplication>
#include <QImage>
#include "Filter.h"
#include <iostream>
#include <algorithm>//sort
//-p D:\Education-Win-Sum-21\CompGraph\qt\github\QT-win-sum-2021\31.03.21\QtConsoleApplication1\FromImage\Cat.png
using std::string;
using std::cout;
using std::endl;
using std::cin;

//for media filter
struct pixel
{
	int x;
	int y;
	int rgb;
};

//for bit img
template <class T>
T clamp(T value, T max, T min)
{
	if (value > max)
		return max;
	if (value < min)
		return min;
	return value;
}

void Dilation(const QImage& source, QImage& result)
{
	// Width, Height – размеры исходного и результирующего изображений
	// MW, MH – размеры структурного множества
	int MW, MH;
	bool *mask;
	cout << "Enter MW" << endl;
	cin >> MW;
	MH = MW;
	/*cout << "Enter MH" << endl;
	cin >> MH;*/
	system("cls");
	mask = new bool [MW * MH];
	for (int i = 0; i < MW * MH; i++)
	{
		mask[i] = 0;
	}

	char elemOfMask;
	for (int i = 0; i < MW * MH; i++)
	{
		cout << "Enter 1 or 0" << endl;
		for (int j = 0; j < MW * MH; j++)
		{
			if (j == i)
			{
				cout <<"["<< mask[j]<<"]" << " ";
			}
			else
			{
				cout << mask[j] << " ";
			}
			if (j % MW == MW-1 && j > 0)
			{
				cout << endl;
			}
		}
		cin >> elemOfMask;
		if (elemOfMask == '0' || elemOfMask == '1')
		{
			mask[i] = elemOfMask - '0';
		}
		system("cls");
		
	}

	result = source;

	if (MH * MW % 2 == 1)
	{
		for (int y = MH / 2; y < source.height() - MH / 2; y++)
		{
			for (int x = MW / 2; x < source.width() - MW / 2; x++)
			{
				QColor max;
				max.setRgb(0, 0, 0);
				for (int j = -MH / 2, jj = 0; j <= MH / 2; j++, jj++)
				{
					for (int i = -MW / 2, ii = 0; i <= MW / 2; i++, ii++)
					{
						if ((mask[ii + MH * jj]) && (source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).red() > max.red() || source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).green() > max.green() || source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).blue() > max.blue()))
						{
							max.setRgb(source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).red(), source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).green(), source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).blue());
						}
					}
				}

				if (max.red() > 0 || max.green() > 0 || max.blue() > 0)
				{
					result.setPixelColor(x, y, max);
				}
			}
		}
	}
	else
	{
		for (int y = MH / 2; y < source.height() - MH / 2; y++)
		{
			for (int x = MW / 2; x < source.width() - MW / 2; x++)
			{
				QColor max;
				max.setRgb(0, 0, 0);
				for (int j = -MH / 2, jj = 0; j < MH / 2; j++, jj++)
				{
					for (int i = -MW / 2, ii = 0; i < MW / 2; i++, ii++)
					{
						if ((mask[ii + MH * jj]) && (source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).red() + source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).green() + source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).blue() > max.red() + max.green() + max.blue()))
						{
							max.setRgb(source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).red(), source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).green(), source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).blue());
						}
					}
				}

				if (max.red() > 0 || max.green() > 0 || max.blue() > 0)
				{
					result.setPixelColor(x, y, max);
				}
			}
		}
	}
}

void Erosion(const QImage& source, QImage& result)
{
	// Width, Height – размеры исходного и результирующего изображений
	// MW, MH – размеры структурного множества
	int MW, MH;
	bool* mask;
	cout << "Enter MW" << endl;
	cin >> MW;
	MH = MW;
	/*cout << "Enter MH" << endl;
	cin >> MH;*/
	system("cls");
	mask = new bool[MW * MH];
	for (int i = 0; i < MW * MH; i++)
	{
		mask[i] = 0;
	}

	char elemOfMask;
	for (int i = 0; i < MW * MH; i++)
	{
		cout << "Enter 1 or 0" << endl;
		for (int j = 0; j < MW * MH; j++)
		{
			if (j == i)
			{
				cout << "[" << mask[j] << "]" << " ";
			}
			else
			{
				cout << mask[j] << " ";
			}
			if (j % MW == MW - 1 && j > 0)
			{
				cout << endl;
			}
		}
		cin >> elemOfMask;
		if (elemOfMask == '0' || elemOfMask == '1')
		{
			mask[i] = elemOfMask - '0';
		}
		system("cls");

	}

	result = source;

	if (MH * MW % 2 == 1) {
		for (int y = MH / 2; y < source.height() - MH / 2; y++)
		{
			for (int x = MW / 2; x < source.width() - MW / 2; x++)
			{
				QColor min;
				min.setRgb(255, 255, 255);
				for (int j = -MH / 2, jj = 0; j <= MH / 2; j++, jj++)
				{
					for (int i = -MW / 2, ii = 0; i <= MW / 2; i++, ii++)
					{
						if ((mask[ii + MH * jj]) && (source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).red() + source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).green() + source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).blue() < min.red() + min.green() + min.blue()))
						{
							min.setRgb(source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).red(), source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).green(), source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).blue());
						}
					}
				}

				if (min.red() < 255 || min.green() < 255 || min.blue() < 255)
				{
					result.setPixelColor(x, y, min);
				}
			}
		}
	}
	else
	{
		for (int y = MH / 2; y < source.height() - MH / 2; y++)
		{
			for (int x = MW / 2; x < source.width() - MW / 2; x++)
			{
				QColor min;
				min.setRgb(255, 255, 255);
				for (int j = -MH / 2, jj = 0; j < MH / 2; j++, jj++)
				{
					for (int i = -MW / 2, ii = 0; i < MW / 2; i++, ii++)
					{
						if ((mask[ii + MH * jj]) && (source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).red() < min.red() || source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).green() < min.green() || source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).blue() < min.blue()))
						{
							min.setRgb(source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).red(), source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).green(), source.pixelColor(clamp(x + i, source.width() - 1, 0), clamp(y - j, source.height() - 1, 0)).blue());
						}
					}
				}

				if (min.red() < 255 || min.green() < 255 || min.blue() < 255)
				{
					result.setPixelColor(x, y, min);
				}
			}
		}
	}
}

void Opening(const QImage& source, QImage& result)
{
	QImage helper;
	Erosion(source, helper);

	Dilation(helper, result);
}

void Closing(const QImage& source, QImage& result)
{
	QImage helper;
	Dilation(source, helper);

	Erosion(helper, result);
}

void Grad(const QImage& source,  QImage& result)
{
	result = source;

	QImage helper1;
	QImage helper2;
	QColor color;

	Dilation(source, helper1);
	Erosion(source, helper2);

	for (int y = 0; y < helper1.height(); y++)
	{
		for (int x = 0; x < helper1.width(); x++)
		{
			int red, green, blue;
			red = clamp(helper1.pixelColor(x, y).red() - helper2.pixelColor(x, y).red(), 255, 0);
			green = clamp(helper1.pixelColor(x, y).green() - helper2.pixelColor(x, y).green(), 255, 0);
			blue = clamp(helper1.pixelColor(x, y).blue() - helper2.pixelColor(x, y).blue(), 255, 0);

			color.setRgb(red, green, blue);

			result.setPixelColor(x, y, color);
		}
	}
}

void TopHat(const QImage& source, QImage& result)
{
	result = source;

	QImage helper;
	QColor color;
	Closing(source, helper);

	for (int y = 0; y < helper.height(); y++)
	{
		for (int x = 0; x < helper.width(); x++)
		{
			int red, green, blue;
			red = clamp(source.pixelColor(x, y).red() - helper.pixelColor(x, y).red(), 255, 0);
			green = clamp(source.pixelColor(x, y).green() - helper.pixelColor(x, y).green(), 255, 0);
			blue = clamp(source.pixelColor(x, y).blue() - helper.pixelColor(x, y).blue(), 255, 0);

			color.setRgb(red, green, blue);

			result.setPixelColor(x, y, color);
		}
	}
}

void BlackHat(const QImage& source, QImage& result)
{
	result = source;

	QImage helper;
	QColor color;
	Closing(source, helper);

	for (int y = 0; y < helper.height(); y++)
	{
		for (int x = 0; x < helper.width(); x++)
		{
			int red, green, blue;
			red = clamp(helper.pixelColor(x, y).red() - source.pixelColor(x, y).red(), 255, 0);
			green = clamp(helper.pixelColor(x, y).green() - source.pixelColor(x, y).green(), 255, 0);
			blue = clamp(helper.pixelColor(x, y).blue() - source.pixelColor(x, y).blue(), 255, 0);

			color.setRgb(red, green, blue);

			result.setPixelColor(x, y, color);
		}
	}
}

void MedianFilter(const QImage& source, QImage& result, int radius = 5)
{
	result = source;
	int xx, yy, bright;
	//QColor color;
	for (int y = radius / 2; y < source.height() - radius / 2; y++)
	{
		for (int x = radius / 2; x < source.width() - radius / 2; x++)
		{
			std::vector<pixel> pixels;
			for (int j = -radius / 2; j <= radius / 2; j++)
			{
				for (int i = -radius / 2; i <= radius / 2; i++)
				{
					 xx = clamp(x + i, source.width() - 1, 0);
					 yy = clamp(y - j, source.height() - 1, 0);
					 bright = source.pixelColor(xx, yy).red() + source.pixelColor(xx, yy).green() + source.pixelColor(xx, yy).blue();
					 pixels.push_back({ xx, yy, bright });
				}
			}
			std::sort(pixels.begin(), pixels.end(), [](pixel a, pixel b) {return a.rgb < b.rgb; });
			pixel mediana = pixels[(radius * radius) / 2];
			
			result.setPixelColor(x, y, source.pixelColor(mediana.x, mediana.y));
		}
	}
}

void main(int argc, char *argv[])
{
	string s = string();
	QImage img;
	
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-p") && (i + 1 < argc))
		{
			s = argv[i + 1];	
		}
	}

	

	img.load(QString(s.c_str()));
	img.save("bitimg/Source.png");

	QImage result;
	Dilation(img, result);
	result.save("bitimg/dilation.png");

	Erosion(img, result);
	result.save("bitimg/erosion.png");

	Opening(img, result);
	result.save("bitimg/open.png");

	Closing(img, result);
	result.save("bitimg/close.png");

	Grad(img, result);
	result.save("bitimg/grad.png");

	TopHat(img, result);
	result.save("bitimg/tophat.png");

	BlackHat(img, result);
	result.save("bitimg/blackhat.png");

	//MedianFilter(img, result);
	//result.save("bitimg/med.png");

	/*InvertFilter invert;
	invert.process(img).save("Art/Invert.png");*/

	/*Kernel mask(2);
	for (int i = 0; i < 25; i++)
	{
		mask[i] = 0;
	}

	for (int i = 1; i < 4; i++)
	{
		mask[i * 5 + 1] = 1;
		mask[i * 5 + 2] = 1;
		mask[i * 5 + 3] = 1;
	}
	mask[6] = 0;
	mask[8] = 0;
	mask[16] = 0;
	mask[18] = 0;*/
	//mask[12] = 0;
	
	//QImage result;

	/*Dilation(img, result);
	result.save("bitimg/newdilation.png");*/


	/*MedianFilter(img, result);
	result.save("bitimg/mediana.png");*/

	/*std::vector<int> a;
	
	for (int i = 0; i < 4; i++)
	{
		a.push_back(10 - i);
	}

	std::sort(a.begin(), a.end(), [](const int & a, const int & b) {return a < b; });

	for (int i = 0; i < 4; i++)
	{
		cout << a[i] << endl;
	}*/

	//std::vector<pixel> pixels;



	//for (int i = 0; i < 4; i++)
	//{
	//	//pixel a = { i,i,10-i };
	//	pixels.push_back({ i,i,10 - i });
	//}


	//std::sort(pixels.begin(), pixels.end(), [](pixel a, pixel b) {return a.rgb < b.rgb; });

	//for (int i = 0; i < 4; i++)
	//{
	//	cout << pixels[i].rgb << endl;
	//}

	//Grad(img, result);
	//result.save("bitimg/grad.png");

	/*TopHat(img, mask, result);
	result.save("bitimg/tophat.png");

	BlackHat(img, mask, result);
	result.save("bitimg/blackhat.png");

	Dilation(img, mask, result);

	result.save("bitimg/1dilation.png");


	Erosion(img, mask, result);

	result.save("bitimg/1erosion.png");


	Opening(img, mask, result);

	result.save("bitimg/1opening.png");


	Closing(img, mask, result);

	result.save("bitimg/1closing.png");*/

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

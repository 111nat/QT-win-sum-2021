#include "Filter.h"
#include <iostream>
#include <math.h>
#define PI 3.14159265

template <class T>
T clamp(T value, T max, T min)
{
	if (value > max)
		return max;
	if (value < min)
		return min;
	return value;
}

QImage Filter::process(const QImage& img) const
{
	QImage result(img);

	for (int x = 0; x < img.width(); x++) 
	{
		for (int y = 0; y < img.height(); y++)
		{
			QColor color = calcNewPixelColor(img, x, y);
			result.setPixelColor(x, y, color);

		}
	}
	return result;
}

QColor InvertFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	color.setRgb(255 - color.red(), 255 - color.green(), 255 - color.blue());
	return color;
}


QColor MatrixFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	float returnR = 0;
	float returnG = 0;
	float returnB = 0;
	int size = mKernel.getSize();
	int radius = mKernel.getRadius();
	for (int i = -radius; i <= radius; i++)
		for (int j = -radius; j <= radius; j++)
		{
			int idx = (i + radius) * size + j + radius;

			QColor color = img.pixelColor(clamp(x + j, img.width() - 1, 0), clamp(y + i, img.height() - 1, 0));

			returnR += color.red() * mKernel[idx];
			returnG += color.green() * mKernel[idx];
			returnB += color.blue() * mKernel[idx];
		}

	return QColor(clamp(returnR, 255.f, 0.f), clamp(returnG, 255.f, 0.f), clamp(returnB, 255.f, 0.f));
}

QColor GrayScaleFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	float Intensity = 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue();
	color.setRgb(Intensity, Intensity, Intensity);
	return color;
}


QColor SepiaFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	float Intensity = 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue();
	float k = 30;
	color.setRgb(clamp(Intensity + 2 * k, 255.f, 0.f), clamp(Intensity + (float)0.5 * k, 255.f, 0.f), clamp(Intensity - 1 * k, 255.f, 0.f));
	return color;
}

QColor BrightFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	float constanta = 30.;
	color.setRgb(clamp(color.red() + constanta, 255.f, 0.f), clamp(color.green() + constanta, 255.f, 0.f), clamp(color.blue() + constanta, 255.f, 0.f));
	return color;
}

QColor PerfectReflectionFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	return QColor();
}

QImage PerfectReflectionFilter::process(const QImage& img) const
{
	QImage result(img);
	int RedMax = 0, GreenMax = 0, BlueMax = 0;
	for (int x = 0; x < img.width(); x++)
	{
		for (int y = 0; y < img.height(); y++)
		{
			QColor color = img.pixelColor(x, y);
			if (color.red() > RedMax)
			{
				RedMax = color.red();
			}
			if (color.green() > GreenMax)
			{
				GreenMax = color.green();
			}
			if (color.blue() > BlueMax)
			{
				BlueMax = color.blue();
			}
			
		}
	}
	//std::cout << RedMax<<" " << GreenMax<< " " << BlueMax << std::endl;

	for (int x = 0; x < img.width(); x++)
	{
		for (int y = 0; y < img.height(); y++)
		{
			//QColor color = calcNewPixelColor(img, x, y);
			//result.setPixelColor(x, y, color);

			QColor color = img.pixelColor(x, y);

			color.setRgb(clamp((float)(color.red() * (255 / RedMax)), 255.f, 0.f), clamp((float)(color.green() * (255 / GreenMax)), 255.f, 0.f), clamp((float)(color.blue() * (255 / BlueMax)), 255.f, 0.f));

			result.setPixelColor(x, y, color);

		}

	}

	return result;
}


QColor LinearTensionFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	return QColor();
}

QImage LinearTensionFilter::process(const QImage& img) const
{
	QImage result(img);
	int RedMax = 0, GreenMax = 0, BlueMax = 0;
	int RedMin = 255, GreenMin = 255, BlueMin = 255;
	for (int x = 0; x < img.width(); x++)
	{
		for (int y = 0; y < img.height(); y++)
		{
			QColor color = img.pixelColor(x, y);
			if (color.red() > RedMax)
			{
				RedMax = color.red();
			}
			if (color.green() > GreenMax)
			{
				GreenMax = color.green();
			}
			if (color.blue() > BlueMax)
			{
				BlueMax = color.blue();
			}

			if (color.red() < RedMin)
			{
				RedMin = color.red();
			}
			if (color.green() < GreenMin)
			{
				GreenMin = color.green();
			}
			if (color.blue() < BlueMin)
			{
				BlueMin = color.blue();
			}
		}
	}

	for (int x = 0; x < img.width(); x++)
	{
		for (int y = 0; y < img.height(); y++)
		{
			QColor color = img.pixelColor(x, y);

			color.setRgb(clamp((color.red() - RedMin) * (255 - 0)/(RedMax - RedMin), 255, 0), clamp((color.green() - GreenMin) * (255 - 0) / (GreenMax - GreenMin), 255, 0), clamp((color.blue() - BlueMin) * (255 - 0) / (BlueMax - BlueMin), 255, 0));

			result.setPixelColor(x, y, color);
		}
	}
	return result;
	
}

//белое или черном
QColor WhiteLinesFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	if (color.red() >= 247 && color.green() >= 247 && color.blue() >= 247)
	{
		return color;
	}
	else
	{
		color.setRgb(0, 0, 0);
	}
	return color;
}


QColor TurnFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	//Центр поворота
	int xCenter = img.width() / 2;
	int yCenter = img.height() / 2;
	//угол поворота
	float u = PI / 4;
	int newX = (x - xCenter) * cos(u) - (y - yCenter) * sin(u) + xCenter;
	int newY = (x - xCenter) * sin(u) + (y - yCenter) * cos(u) + yCenter;

	if (newX < img.width() && newX > 0 && newY < img.height() && newY > 0)
	{
		return img.pixelColor(newX, newY);
	}
	else
	{
		return QColor(0, 0, 0);
	}
}

QColor WavesFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	//1
	/*int newX = clamp((int)(x + 20 * sin(2 * PI * y / 60)), img.width() - 1, 1);
	int newY = y;*/

	//2
	int newX = clamp((int)(x + 20 * sin(2 * PI * x / 30)), img.width() - 1, 1);
	int newY = y;

	return img.pixelColor(newX, newY);
}

QColor GlassFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	double random_0_to_1 = rand()%11 / 10.f;

	int newX = clamp((float)(x + (random_0_to_1 - 0.5) * 10), (float)(img.width() - 1), 1.f);
	int newY = clamp((float)(y + (random_0_to_1 - 0.5) * 10), (float)(img.height() - 1), 1.f);

	return img.pixelColor(newX, newY);
}

#pragma once
#include <QImage>


class Filter
{
protected:
	virtual QColor calcNewPixelColor(const QImage& img, int x, int y) const = 0;
public:
	virtual ~Filter() = default;
	virtual QImage process(const QImage & img) const;

};

class InvertFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

class Kernel
{
protected:
	//данные ядра
	std::unique_ptr<float[]> data;
	//радиус ядра
	std::size_t radius;
	//размер памяти ядра
	std::size_t getLen() const { return getSize() * getSize(); }
public:
	//конструктор пустого ядра
	Kernel(std::size_t radius) : radius(radius)
	{
		//выделение памяти под массив
		data = std::make_unique<float[]>(getLen());
	}

	//конструктор копирования
	Kernel(const Kernel& other) : Kernel(other.radius)
	{
		std::copy(other.data.get(), other.data.get() + getLen(), data.get());
	}
	
	//аксессоры
	std::size_t getRadius() const { return radius; }
	std::size_t getSize() const { return 2 * radius + 1; }
	float operator[] (std::size_t id) const { return data[id]; }
	float& operator[] (std::size_t id) { return data[id]; }
};

class MatrixFilter : public Filter
{
protected:
	// хранится по значению, потому что внутри Kernel содержится указатель
	Kernel mKernel;
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;

public:
	MatrixFilter(const Kernel& kernel) : mKernel(kernel) {};
	virtual ~MatrixFilter() = default;
};

class BlurKernel : public Kernel
{
public:
	using Kernel::Kernel;
	BlurKernel(std::size_t radius = 2) : Kernel(radius)
	{
		for (std::size_t i = 0; i < getLen(); i++)
			data[i] = 1.0f / getLen();
	}
};

class BlurFilter : public MatrixFilter
{
public:
	BlurFilter(std::size_t radius = 1) : MatrixFilter(BlurKernel(radius)) {}
};

class GaussianKernel : public Kernel
{
public:
	//Наследование конструкторов
	using Kernel::Kernel;
	GaussianKernel(std::size_t radius = 2, float sigma = 3.f) : Kernel(radius)
	{
		//коэффициент нормировки ядра
		float norm = 0;
		int signed_radius = static_cast<int>(radius);
		//рассчитываем ядро линейного фильтра
		for (int x = -signed_radius; x <= signed_radius; x++)
		{
			for (int y = -signed_radius; y <= signed_radius; y++)
			{
				std::size_t idx = (x + radius) * getSize() + (y + radius);
				data[idx] = std::exp(-(x * x + y * y) / (sigma * sigma));
				norm += data[idx];
			}
		}
		//нормируем ядро
		for (std::size_t i = 0; i < getLen(); i++)
		{
			data[i] /= norm;
		}
	}
};

class GaussianFilter : public MatrixFilter
{
public:
	GaussianFilter(std::size_t radius = 1, float sigma = 2.f) : MatrixFilter(GaussianKernel(radius, sigma)) {}
};

class GrayScaleFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

class SepiaFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

class BrightFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

class SobelKernel : public Kernel
{
public:
	using Kernel::Kernel;
	SobelKernel(std::size_t radius = 1) : Kernel(radius)
	{
		/*data[0] = -1;
		data[1] = -2;
		data[2] = -1;

		data[3] = 0;
		data[4] = 0;
		data[5] = 0;

		data[6] = 1;
		data[7] = 2;
		data[8] = 1;*/

		/*data[0] = -1;
		data[1] = 0;
		data[2] = 1;

		data[3] = -2;
		data[4] = 0;
		data[5] = 2;

		data[6] = -1;
		data[7] = 0;
		data[8] = 1;*/

		data[0] = 1;
		data[1] = 2;
		data[2] = 1;

		data[3] = 0;
		data[4] = 0;
		data[5] = 0;

		data[6] = -1;
		data[7] = -2;
		data[8] = -1;
	}
};

class SobelFilter : public MatrixFilter
{
public:
	SobelFilter(std::size_t radius = 1) : MatrixFilter(SobelKernel(radius)) {}
};

class SharpnessKernel : public Kernel
{
public:
	using Kernel::Kernel;
	SharpnessKernel(std::size_t radius = 1) : Kernel(radius)
	{
		data[0] = 0;
		data[1] = -1;
		data[2] = 0;

		data[3] = -1;
		data[4] = 5;
		data[5] = -1;

		data[6] = 0;
		data[7] = -1;
		data[8] = 0;
	}
};

class SharpnessFilter : public MatrixFilter
{
public:
	SharpnessFilter(std::size_t radius = 1) : MatrixFilter(SharpnessKernel(radius)) {}
};

class PerfectReflectionFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
public:
	virtual QImage process(const QImage& img) const override;
};

//лин растяжение
class LinearTensionFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
public:
	virtual QImage process(const QImage& img) const override;
};

//белое не трогать, остальное черное
class WhiteLinesFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

class TurnFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

class WavesFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

class SharpnessSecondKernel : public Kernel
{
public:
	using Kernel::Kernel;
	SharpnessSecondKernel(std::size_t radius = 1) : Kernel(radius)
	{
		data[0] = -1;
		data[1] = -1;
		data[2] = -1;

		data[3] = -1;
		data[4] = 9;
		data[5] = -1;

		data[6] = -1;
		data[7] = -1;
		data[8] = -1;
	}
};

class SharpnessSecondFilter : public MatrixFilter
{
public:
	SharpnessSecondFilter(std::size_t radius = 1) : MatrixFilter(SharpnessSecondKernel(radius)) {}
};

class GlassFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};


class BordersSharraKernel : public Kernel
{
public:
	using Kernel::Kernel;
	BordersSharraKernel(std::size_t radius = 1) : Kernel(radius)
	{
		data[0] = 3;
		data[1] = 10;
		data[2] = 3;

		data[3] = 0;
		data[4] = 0;
		data[5] = 0;

		data[6] = -3;
		data[7] = -10;
		data[8] = -3;
	}
};

class BordersSharraFilter : public MatrixFilter
{
public:
	BordersSharraFilter(std::size_t radius = 1) : MatrixFilter(BordersSharraKernel(radius)) {}
};

class BordersPruttaKernel : public Kernel
{
public:
	using Kernel::Kernel;
	BordersPruttaKernel(std::size_t radius = 1) : Kernel(radius)
	{
		data[0] = -1;
		data[1] = -1;
		data[2] = -1;

		data[3] = 0;
		data[4] = 0;
		data[5] = 0;

		data[6] = 1;
		data[7] = 1;
		data[8] = 1;
	}
};

class BordersPruttaFilter : public MatrixFilter
{
public:
	BordersPruttaFilter(std::size_t radius = 1) : MatrixFilter(BordersPruttaKernel(radius)) {}
};

class MotionBlurKernel : public Kernel
{
public:
	using Kernel::Kernel;
	MotionBlurKernel(int n = 1, std::size_t radius = 1) : Kernel(radius)
	{
		/*data[0] = (float)0.45;
		data[1] = 0.f;
		data[2] = 0.f;

		data[3] = 0.f;
		data[4] = (float)0.45;
		data[5] = 0.f;

		data[6] = 0.f;
		data[7] = 0.f;
		data[8] = (float)0.45;*/

		for (std::size_t x = 0; x < getSize(); x++)
		{
			for (std::size_t y = 0; y < getSize(); y++)
			{
				if (x == y)
				{
					data[x * getSize() + y] = (float)1 / n;
				}
				else
				{
					data[x * getSize() + y] = 0;
				}
			}
		}
			
		
	}
};

class MotionBlurFilter : public MatrixFilter
{
public:
	MotionBlurFilter(int n = 1, std::size_t radius = 1) : MatrixFilter(MotionBlurKernel(n, radius)) {}
};




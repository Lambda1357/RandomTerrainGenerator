#pragma once
#include "stdafx.h"

#include <string>

#include <noise/noise.h>
#include "noiseutils.h"

#include "WriterWinAPI.h"

class TerrainGenerator
{
public:
	void SetMapScale(double scale);
	void SetSize(int x, int y);
	void SetSeed(int seed);

	void ExportToBmp(std::string str);
	void ExportToTer(std::string str);

	void Initialize();
	void Render(HDC hdc, POINT destPosition = { 0,0 });

private:
	module::Perlin m_module;
	utils::NoiseMap m_heightMap;
	utils::NoiseMapBuilderPlane m_heightMapBuilder;
	utils::RendererImage m_renderer;
	utils::Image m_image;
	utils::WriterWinAPI writerWin;
	utils::WriterBMP writerBmp;
	utils::WriterTER writerTer;

	POINT destSize;
	double boundScale;
	void Bake();
};

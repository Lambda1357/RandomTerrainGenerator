#include "stdafx.h"
#include "TerrainGenerator.h"

void TerrainGenerator::SetMapScale(double scale)
{
	boundScale = scale;
	m_heightMapBuilder.SetBounds(0.0, scale, 
								0.0, scale * (float(destSize.y) / float(destSize.x)));
}

void TerrainGenerator::SetSize(int x, int y)
{
	destSize = { x,y };

	m_heightMapBuilder.SetDestSize(destSize.x, destSize.y);
	SetMapScale(boundScale);
}

void TerrainGenerator::SetSeed(int seed)
{
	m_module.SetSeed(seed);
}

void TerrainGenerator::ExportToBmp(std::string str)
{
	writerBmp.SetDestFilename(str + "exportedMap.bmp");
	writerBmp.WriteDestFile();
}

void TerrainGenerator::ExportToTer(std::string str)
{
	writerTer.SetDestFilename(str + "exportedMap.ter");
	writerTer.WriteDestFile();
}

void TerrainGenerator::Initialize()
{
	m_heightMapBuilder.SetSourceModule(m_module);
	m_heightMapBuilder.SetDestNoiseMap(m_heightMap);
	boundScale = 4.0;
	SetSize(256, 256);

	m_renderer.SetSourceNoiseMap(m_heightMap);
	m_renderer.SetDestImage(m_image);
	m_renderer.ClearGradient();
	m_renderer.AddGradientPoint(-1.0000, utils::Color(0, 0, 128, 255)); // deeps
	m_renderer.AddGradientPoint(-0.2500, utils::Color(0, 0, 255, 255)); // shallow
	m_renderer.AddGradientPoint(0.0000, utils::Color(0, 128, 255, 255)); // shore
	m_renderer.AddGradientPoint(0.0625, utils::Color(240, 240, 64, 255)); // sand
	m_renderer.AddGradientPoint(0.1250, utils::Color(32, 160, 0, 255)); // grass
	m_renderer.AddGradientPoint(0.3750, utils::Color(224, 224, 0, 255)); // dirt
	m_renderer.AddGradientPoint(0.7500, utils::Color(128, 128, 128, 255)); // rock
	m_renderer.AddGradientPoint(1.0000, utils::Color(255, 255, 255, 255)); // snow
	m_renderer.EnableLight();
	m_renderer.SetLightContrast(3.0); // Triple the contrast
	m_renderer.SetLightBrightness(2.0); // Double the brightness

	writerWin.SetSourceImage(m_image);
	writerBmp.SetSourceImage(m_image);
	writerTer.SetSourceNoiseMap(m_heightMap);
}

void TerrainGenerator::Render(HDC hdc, POINT destPosition)
{
	Bake();
	writerWin.SetDestPoint(destPosition);
	writerWin.RenderToDC(hdc);
}

void TerrainGenerator::Bake()
{
	m_heightMapBuilder.Build();
	m_renderer.Render();
}

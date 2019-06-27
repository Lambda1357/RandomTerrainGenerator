#include "stdafx.h"
#include "WriterWinAPI.h"

namespace noise
{
	namespace utils
	{
		void WriterWinAPI::RenderToDC(HDC hdc)
		{
			POINT destRightBottomPosition = { m_destPosition.x + m_pSourceImage->GetWidth()
											,m_destPosition.y + m_pSourceImage->GetHeight() };
			for (int y = m_destPosition.y; y <= destRightBottomPosition.y; y++)
			{
				for (int x = m_destPosition.x; x <= destRightBottomPosition.x; x++)
				{
					POINT positionInImage = { x - m_destPosition.x,y - m_destPosition.y };

					Color color = m_pSourceImage->GetValue(positionInImage.x, positionInImage.y);
					m_pSourceImage->GetValue(positionInImage.x, positionInImage.y);
					SetPixel(hdc, x, y, RGB(color.red, color.green, color.blue));
				}
			}
		}
	} //namespace utiils
}//namespace noise
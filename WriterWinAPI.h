#pragma once
#include "stdafx.h"
#include "noiseutils.h"

namespace noise
{
	namespace utils
	{
		/// Windows bitmap image writer class.
		///
		/// This class render directly on WinAPI Program.
		///
		/// <b>Writing the image</b>
		///
		/// To write the image directly on WinAPI, perform the following steps:
		///	TODO : Write step by step.
		///
		/// The SetSourceImage() methods must be called
		/// before calling the WriteDestFile() method.
		class WriterWinAPI
		{
		public:
			WriterWinAPI() : m_pSourceImage(nullptr), m_destPosition({ 0, 0 })
			{
			}

			/// Sets the image object that is written to the file.
			///
			/// @param sourceImage The image object to write.
			///
			/// This object only stores a pointer to an image object, so make sure
			/// this object exists before calling the WriteDestFile() method.
			void SetSourceImage(Image &sourceImage)
			{
				m_pSourceImage = &sourceImage;
			}

			void SetDestPoint(POINT dest)
			{
				m_destPosition = dest;
			}

			/// Render to recived DC
			///
			/// @param hdc The Handle of render Destination DC.
			void RenderToDC(HDC hdc);

		protected:

			///the postion that will rendered in DC
			POINT m_destPosition;

			/// A pointer to the image object that will be written to the file.
			Image *m_pSourceImage;
		};
	}//namespace utils
}//namespace noise
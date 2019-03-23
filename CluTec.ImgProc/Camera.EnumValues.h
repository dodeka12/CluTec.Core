////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.ImgProc
// file:      Camera.EnumValues.h
//
// summary:   Declares the camera. enum values class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CLU_MANAGED
public enum class Styles
#else
enum class EStyle
#endif
{
	OpenCV,
	Middlebury,
	Halcon,
};


#ifdef CLU_MANAGED
public enum class DistStyles
#else
enum class EDistStyle
#endif
{
	OpenCV,
};
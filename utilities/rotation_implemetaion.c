#include <MagickWand/MagickWand.h>

MagickExport Image *RotateImage(const Image *image,const double degrees,
  ExceptionInfo *exception)
{
  Image
    *distort_image,
    *rotate_image;

  double
    angle;

  PointInfo
    shear;

  size_t
    rotations;

  /*
    Adjust rotation angle.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  angle=fmod(degrees,360.0);
  while (angle < -45.0)
    angle+=360.0;
  for (rotations=0; angle > 45.0; rotations++)
    angle-=90.0;
  rotations%=4;
  shear.x=(-tan((double) DegreesToRadians(angle)/2.0));
  shear.y=sin((double) DegreesToRadians(angle));
  if ((fabs(shear.x) < MagickEpsilon) && (fabs(shear.y) < MagickEpsilon))
    return(IntegralRotateImage(image,rotations,exception));
  distort_image=CloneImage(image,0,0,MagickTrue,exception);
  if (distort_image == (Image *) NULL)
    return((Image *) NULL);
  (void) SetImageVirtualPixelMethod(distort_image,BackgroundVirtualPixelMethod,
    exception);
  rotate_image=DistortImage(distort_image,ScaleRotateTranslateDistortion,1,
    &degrees,MagickTrue,exception);
  distort_image=DestroyImage(distort_image);
  return(rotate_image);
}
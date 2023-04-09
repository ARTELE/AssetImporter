#include "Picture.h"
#include <Engine/Managers/Managers.h>

Object* Picture::Clone()
{
	Picture* pictureClone = Managers::objectManager.allocator.Allocate<Picture>(1, "Pirture::Clone");
	pictureClone->width = width;
	pictureClone->height = height;
	pictureClone->channel = channel;
	pictureClone->data = pictureClone->allocator.Allocate<unsigned char>(width * height * channel);
	pictureClone->SetInstanceId(Managers::objectManager.GenerateInstanceId());
	Managers::objectManager.AddObject(pictureClone);
	return pictureClone;
}
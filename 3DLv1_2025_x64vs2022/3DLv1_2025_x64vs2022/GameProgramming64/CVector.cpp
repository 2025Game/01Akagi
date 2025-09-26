#include "CVector.h"

//Set(X座標, Y座標, Z座標)
void CVector::Set(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;

}
float CVector::X() const   //constは変更できない、変更しないという意味
{
	return mX;
}

float CVector::Y() const
{
	return mY;
}

float CVector::Z() const
{
	return mZ;
}
#pragma once
#include "C:\A. Neumont\Quarter 5\Computer Graphics\GAT350\ThirdParty\box2d\include\box2d\box2d.h"

namespace neu
{
	class ContactListener : public b2ContactListener
	{
	public:
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
	};
}
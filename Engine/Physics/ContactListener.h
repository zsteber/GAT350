#pragma once
#include "C:\Users\loren\OneDrive\Desktop\GAT350\ThirdParty\box2d\include\box2d\box2d.h"

namespace neu
{
	class ContactListener : public b2ContactListener
	{
	public:
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
	};
}
#pragma once

#include <Core/Engine.h>

class GamePiece {
	public:
		GamePiece();
		GamePiece(float length, float windowX, float windowY);
		~GamePiece();

		void setPositionX(float x);
		void setPositionY(float y);
		void setOldPositionX(float x);
		void setOldPositionY(float y);
		void setScale(float scale);
		void setDestroy(bool destroy);
		void setCounted(bool count);

		float getLength();
		float getWindowX();
		float getWindowY();
		float getPositionX();
		float getPositionY();
		float getOldPositionX();
		float getOldPositionY();
		bool isDestroyed();
		bool getWasHit();
		bool getCounted();
		float getScale();

		virtual bool inCollision(GamePiece* pos);

	private:
		glm::vec3 origin;
		bool wasHit, destroyed, count;
		float length, x, y, scale;
		float old_x, old_y;
		float windowX, windowY;
};
#include "Player.h"
#include "Engine_Core.h"


Player::Player()
{
	// Default values
	hasMoved = false;
	isAttacking = false;
	depth = 0;
	facingUp = true;
	facingLeft = false;

	// Register with event system
	g_Engine->GetEventManager()->RegisterListener(this, Events::PLAYER_INPUT);

	// Initialize player rendering information
	Renderer.Initialize(1, 1, 16, 16, 16, 0, 0, 1, 1, 0, 256, 256, "player.png");
	Renderer.SetAnimateFlag(true);
	Renderer.SetScaleX(2);
	Renderer.SetScaleY(2);

	// Initialize hitbox
	hitBox.Initialize(Renderer.GetPos().GetX(), Renderer.GetPos().GetY(), 
		Renderer.GetAdjustedWidth(), Renderer.GetAdjustedHeight());
}


Player::~Player()
{
	// Purge event listeners
	g_Engine->GetEventManager()->PurgeListener(ID, Events::PLAYER_INPUT);
}


void Player::HandleEvent(IEvent *e)
{
	if (e->Event_Type == Events::PLAYER_INPUT)
	{
		PlayerInputEvent *pTemp = static_cast<PlayerInputEvent*>(e);

		if (!isAttacking)
		{
			if (pTemp->up)
			{
				Renderer.ModifyY(-6.5f);

				facingUp = true;
				hasMoved = true;
			}
			else if (pTemp->down)
			{
				Renderer.ModifyY(6.5f);

				facingUp = false;
				hasMoved = true;
			}
			if (pTemp->left)
			{
				Renderer.ModifyX(-6.5f);

				facingLeft = true;
				hasMoved = true;
			}
			else if (pTemp->right)
			{
				Renderer.ModifyX(6.5f);

				facingLeft = false;
				hasMoved = true;
			}
		}

		// Update hitbox
		hitBox.UpdateCollider(Renderer.GetPos().GetX(), Renderer.GetPos().GetY());

		// Keep play within boundaries
		KeepInBounds();
	}
}


void Player::Update(float deltaTime)
{
	Renderer.Update();
}


void Player::Render()
{
	Renderer.Render();
}


void Player::SetIdle()
{
	Renderer.SetCurrentFrame(0);	// Revert to startFrame (can be changed)
}


void Player::KeepInBounds()
{
	// Right boundary
	if (hitBox.GetBoundingBox().right > SCREENW)
	{
		// Prevent the player from moving off the right side of the screen
		Renderer.ModifyX(-(hitBox.GetBoundingBox().right - SCREENW));
	}

	// Left boundary
	if (hitBox.GetBoundingBox().left < 0)
	{
		// Prevent the player from moving off the left side of the screen
		Renderer.ModifyX(-(hitBox.GetBoundingBox().left));
	}

	// Top boundary
	if (hitBox.GetBoundingBox().top < 0)
	{
		// Prevent the player from moving off the top of the screen
		Renderer.ModifyY(0 - hitBox.GetBoundingBox().top);
	}

	// Bottom boundary
	if (hitBox.GetBoundingBox().bottom > SCREENH)
	{
		// Prevent the player from moving off the bottom of the screen
		Renderer.ModifyY(-(hitBox.GetBoundingBox().bottom - SCREENH));
	}
}

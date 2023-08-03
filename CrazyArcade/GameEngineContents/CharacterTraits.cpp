#include "CharacterTraits.h"
#include "ContentsEnum.h"
#include "ActorEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineRenderer.h>



CharacterTraits::CharacterTraits() 
{
}

CharacterTraits::~CharacterTraits() 
{
}


void CharacterTraits::Start()
{
	loadCharacterTraits();
}

void CharacterTraits::loadCharacterTraits()
{
	static bool CharacterTraitsLoadCheck = false;

	if (false == CharacterTraitsLoadCheck)
	{
		GameEngineWindowTexture* Texture = nullptr;

		Texture = GlobalUtils::TextureFileLoad("CharatorSelect_PopPanel.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect");
		if (nullptr == Texture)
		{
			MsgBoxAssert("텍스처를 불러오지 못했습니다.");
			return;
		}

		m_TraitPanelScale = Texture->GetScale();


		Texture = GlobalUtils::TextureFileLoad("CharatorSelect_UpperPanel.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect");
		if (nullptr == Texture)
		{
			MsgBoxAssert("텍스처를 불러오지 못했습니다.");
			return;
		}

		m_UpperPanelScale = Texture->GetScale();
		m_UpperPanelScale = float4{ m_UpperPanelScale.X , m_UpperPanelScale.Y / static_cast<float>(CharacterList::Max) };


		Texture = GlobalUtils::TextureFileLoad("CharatorSelect_TraitBar.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect");
		if (nullptr == Texture)
		{
			MsgBoxAssert("텍스처를 불러오지 못했습니다.");
			return;
		}

		m_TraitBarScale = Texture->GetScale();
		m_TraitBarScale = float4{ m_TraitBarScale.X * 0.5f , m_TraitBarScale.Y };

		CharacterTraitsLoadCheck = true;
	}


	TraitRenderer = CreateRenderer(RenderOrder::FirstElementUI);
	if (nullptr == TraitRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	TraitRenderer->SetTexture("CharatorSelect_PopPanel.bmp");
	TraitRenderer->SetRenderPos(m_TraitPanelScale.Half());
	TraitRenderer->Off();


	UpperRenderer = CreateRenderer(RenderOrder::FirstElementUI);
	if (nullptr == UpperRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	UpperRenderer->SetTexture("CharatorSelect_UpperPanel.bmp");
	UpperRenderer->SetCopyScale(m_UpperPanelScale);
	UpperRenderer->SetRenderPos(float4{ m_UpperPanelScale.hX() , -m_UpperPanelScale.hY() });
	UpperRenderer->SetRenderScale(m_UpperPanelScale);
	UpperRenderer->Off();



	vecTraitBarRenderer.resize(static_cast<int>(TraitType::Max));
	for (int TypeCount = 0; TypeCount < static_cast<int>(TraitType::Max); TypeCount++)
	{
		std::vector<GameEngineRenderer*>& vecTypeTraitBarRenderer = vecTraitBarRenderer[TypeCount];

		vecTypeTraitBarRenderer.resize(m_TraitMaxCount);

		for (int TraitCount = 0; TraitCount < m_TraitMaxCount; TraitCount++)
		{
			GameEngineRenderer* TraitBarRenderer = CreateRenderer(RenderOrder::FirstElementUI);
			if (nullptr == TraitBarRenderer)
			{
				MsgBoxAssert("렌더러를 생성하지 못했습니다.");
				return;
			}


			TraitBarRenderer->SetTexture("CharatorSelect_TraitBar.bmp");
			TraitBarRenderer->SetCopyScale(m_TraitBarScale);

			float TraitBarXPos = (m_TraitBarInterScale.X + m_TraitBarScale.X) * static_cast<float>(TraitCount);
			float TraitBarYPos = (m_TraitBarInterScale.Y + m_TraitBarScale.Y) * static_cast<float>(TypeCount);
			TraitBarRenderer->SetRenderPos(m_TraitBarStartPos + m_TraitBarScale.Half() + float4{ TraitBarXPos , TraitBarYPos });

			TraitBarRenderer->SetRenderScale(m_TraitBarScale);
			TraitBarRenderer->Off();

			vecTypeTraitBarRenderer[TraitCount] = TraitBarRenderer;
		}
	}
}


void CharacterTraits::Update(float _Delta)
{
	updateCharacterTraits();
}

void CharacterTraits::updateCharacterTraits()
{
	if (true == isHoverOn())
	{
		if (false == TraitPanelOnValue)
		{
			if (nullptr == TraitRenderer)
			{
				MsgBoxAssert("렌더러를 불러오지 못했습니다.");
				return;
			}

			if (nullptr == UpperRenderer)
			{
				MsgBoxAssert("렌더러를 불러오지 못했습니다.");
				return;
			}

			TraitRenderer->On();
			UpperRenderer->On();
		}

		float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();

		int XOrder = 0;

		if (MousePos.X < m_TraitPopHoverRangeStartPos.X + m_TraitPopHoverUnitScale.X)
		{
			XOrder = 0;
		}
		else if (MousePos.X < m_TraitPopHoverRangeStartPos.X + m_TraitPopHoverUnitScale.X * 2.0f + 1.0f)
		{
			XOrder = 1;
		}
		else if (MousePos.X < m_TraitPopHoverRangeStartPos.X + m_TraitPopHoverUnitScale.X * 3.0f + 2.0f)
		{
			XOrder = 2;
		}
		else
		{
			XOrder = 3;
		}


		int YOrder = 0;

		if (MousePos.Y < m_TraitPopHoverRangeStartPos.Y + m_TraitPopHoverUnitScale.Y)
		{
			YOrder = 0;
		}
		else if (MousePos.Y < m_TraitPopHoverRangeStartPos.Y + m_TraitPopHoverUnitScale.Y * 2.0f)
		{
			YOrder = 1;
		}
		else
		{
			YOrder = 2;
		}

		int CurTraitPopCharacter = XOrder + YOrder * 4;

		if (CurTraitPopCharacter != m_PrevTraitPopCharacter)
		{
			updateUpperTrait(CurTraitPopCharacter);
			updateWaterBombTraitBar(CurTraitPopCharacter);
			updateBombPowerTraitBar(CurTraitPopCharacter);
			updateSpeedTraitBar(CurTraitPopCharacter);

			m_PrevTraitPopCharacter = CurTraitPopCharacter;
		}

		TraitPanelOnValue = true;
	}
	else
	{
		if (true == TraitPanelOnValue)
		{
			if (nullptr == TraitRenderer)
			{
				MsgBoxAssert("렌더러를 불러오지 못했습니다.");
				return;
			}

			if (nullptr == UpperRenderer)
			{
				MsgBoxAssert("렌더러를 불러오지 못했습니다.");
				return;
			}

			TraitRenderer->Off();
			UpperRenderer->Off();

			for (int TypeCount = 0; TypeCount < static_cast<int>(TraitType::Max); TypeCount++)
			{
				std::vector<GameEngineRenderer*>& vecTypeTraitBarRenderer = vecTraitBarRenderer[TypeCount];

				for (int TraitsCount = 0; TraitsCount < m_TraitMaxCount; TraitsCount++)
				{
					GameEngineRenderer* TraitBarRenderer = vecTypeTraitBarRenderer[TraitsCount];
					if (nullptr == TraitBarRenderer)
					{
						MsgBoxAssert("렌더러를 불러오지 못했습니다.");
						return;
					}

					TraitBarRenderer->Off();
				}
			}
		}

		TraitPanelOnValue = false;
		m_PrevTraitPopCharacter = -1;
	}
}

bool CharacterTraits::isHoverOn()
{
	bool MouseOverValue = true;

	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();

	float4 PanelLeftTopPos = m_TraitPopHoverRangeStartPos;
	float4 PanelRightBottomPos = m_TraitPopHoverRangeStartPos + m_TraitPopHoverRangeRangeScale;

	if (MousePos.X < PanelLeftTopPos.X)
	{
		MouseOverValue = false;
	}

	if (MousePos.Y < PanelLeftTopPos.Y)
	{
		MouseOverValue = false;
	}

	if (MousePos.X > PanelRightBottomPos.X)
	{
		MouseOverValue = false;
	}

	if (MousePos.Y > PanelRightBottomPos.Y)
	{
		MouseOverValue = false;
	}

	return MouseOverValue;
}



void CharacterTraits::updateUpperTrait(int& _TraitCount)
{
	if (nullptr == UpperRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	UpperRenderer->SetCopyPos(float4{ 0.0f , m_UpperPanelScale.Y * static_cast<float>(_TraitCount) });
}

void CharacterTraits::updateWaterBombTraitBar(int& _TraitCount)
{
	int MinWaterBomb = GlobalValue::VecCharacterTraits[_TraitCount].MinWaterBombs;
	int MaxWaterBomb = GlobalValue::VecCharacterTraits[_TraitCount].MaxWaterBombs;

	for (int BarCount = 0; BarCount < MinWaterBomb; BarCount++)
	{
		GameEngineRenderer* WaterBombTraitBarRenderer = vecTraitBarRenderer[static_cast<int>(TraitType::Count)][BarCount];
		if (nullptr == WaterBombTraitBarRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		WaterBombTraitBarRenderer->SetCopyPos(float4::ZERO);
		WaterBombTraitBarRenderer->On();
	}

	for (int BarCount = MinWaterBomb; BarCount < MaxWaterBomb; BarCount++)
	{
		GameEngineRenderer* WaterBombTraitBarRenderer = vecTraitBarRenderer[static_cast<int>(TraitType::Count)][BarCount];
		if (nullptr == WaterBombTraitBarRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		WaterBombTraitBarRenderer->SetCopyPos(float4{ m_TraitBarScale.X , 0.0f });
		WaterBombTraitBarRenderer->On();
	}

	for (size_t BarCount = MaxWaterBomb; BarCount < m_TraitMaxCount; BarCount++)
	{
		GameEngineRenderer* WaterBombTraitBarRenderer = vecTraitBarRenderer[static_cast<int>(TraitType::Count)][BarCount];
		if (nullptr == WaterBombTraitBarRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		WaterBombTraitBarRenderer->Off();
	}
}

void CharacterTraits::updateBombPowerTraitBar(int& _TraitCount)
{
	int MinBombPower = GlobalValue::VecCharacterTraits[_TraitCount].MinBombPower;
	int MaxBombPower = GlobalValue::VecCharacterTraits[_TraitCount].MaxBombPower;

	for (int BarCount = 0; BarCount < MinBombPower; BarCount++)
	{
		GameEngineRenderer* WaterBombTraitBarRenderer = vecTraitBarRenderer[static_cast<int>(TraitType::Power)][BarCount];
		if (nullptr == WaterBombTraitBarRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		WaterBombTraitBarRenderer->SetCopyPos(float4::ZERO);
		WaterBombTraitBarRenderer->On();
	}

	for (int BarCount = MinBombPower; BarCount < MaxBombPower; BarCount++)
	{
		GameEngineRenderer* WaterBombTraitBarRenderer = vecTraitBarRenderer[static_cast<int>(TraitType::Power)][BarCount];
		if (nullptr == WaterBombTraitBarRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		WaterBombTraitBarRenderer->SetCopyPos(float4{ m_TraitBarScale.X , 0.0f });
		WaterBombTraitBarRenderer->On();
	}

	for (size_t BarCount = MaxBombPower; BarCount < m_TraitMaxCount; BarCount++)
	{
		GameEngineRenderer* WaterBombTraitBarRenderer = vecTraitBarRenderer[static_cast<int>(TraitType::Power)][BarCount];
		if (nullptr == WaterBombTraitBarRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		WaterBombTraitBarRenderer->Off();
	}
}

void CharacterTraits::updateSpeedTraitBar(int& _TraitCount)
{
	int MinSpeed = GlobalValue::VecCharacterTraits[_TraitCount].MinSpeed;
	int MaxSpeed = GlobalValue::VecCharacterTraits[_TraitCount].MaxSpeed;

	for (int BarCount = 0; BarCount < MinSpeed; BarCount++)
	{
		GameEngineRenderer* SpeedTraitBarRenderer = vecTraitBarRenderer[static_cast<int>(TraitType::Speed)][BarCount];
		if (nullptr == SpeedTraitBarRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		SpeedTraitBarRenderer->SetCopyPos(float4::ZERO);
		SpeedTraitBarRenderer->On();
	}

	for (int BarCount = MinSpeed; BarCount < MaxSpeed; BarCount++)
	{
		GameEngineRenderer* SpeedTraitBarRenderer = vecTraitBarRenderer[static_cast<int>(TraitType::Speed)][BarCount];
		if (nullptr == SpeedTraitBarRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		SpeedTraitBarRenderer->SetCopyPos(float4{ m_TraitBarScale.X , 0.0f });
		SpeedTraitBarRenderer->On();
	}

	for (size_t BarCount = MaxSpeed; BarCount < m_TraitMaxCount; BarCount++)
	{
		GameEngineRenderer* SpeedTraitBarRenderer = vecTraitBarRenderer[static_cast<int>(TraitType::Speed)][BarCount];
		if (nullptr == SpeedTraitBarRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		SpeedTraitBarRenderer->Off();
	}
}
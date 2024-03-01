#include "pch.h"
#include "GameViewUI.h"

#include <Engine/Engine.h>
#include <Engine/Texture.h>
#include <Engine/InputManager.h>
#include <Engine/ResourceManager.h>
#include <Engine/SceneManager.h>
#include <Engine/GameSystem.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/GraphicDeviceDx11.h>
#include <Engine/WindowManager.h>
#include "AlphaHelper.h"
#include <Engine/TimeManager.h>
#include <Engine/InputManager.h>
void GameViewUI::update()
{

}
void GameViewUI::drawForm()
{
	//GameView 전용텍스처에 그린다.
	RenderTargetRenderer* renderer = gCurrentSceneRenderer;
	Texture* renderTex = gResourceManager->Find<Texture>(L"/Editor/GameViewRenderTexture");
	Texture* depThTex = gResourceManager->Find<Texture>(L"/Editor/GameViewDepthTexture");
	Scene* currentScene = gCurrentScene;

	FLOAT backgroundColor[4] = { 0.5f, 0.5f, 0.5f, 1.f };	
	renderer->TurnOffCamera(eCameraPriorityType::Editor);
	gGraphicDevice->ClearRenderTarget(
		renderTex->GetAddressOf(),
		depThTex->GetDSV(), backgroundColor);
	currentScene->Render(
		static_cast<UINT>(renderTex->GetWidth()),
		static_cast<UINT>(renderTex->GetHeight()),
		renderTex->GetAddressOf(),
		depThTex->GetDSV());

	//둘다 UAV여야함	ImGUI 용도로 사용하기위해 Alpha값 1로 덮어쓴다.
	Texture* rwTex = gResourceManager->Find<Texture>(L"/Editor/GameViewRWTexture");
	Texture* rwTex2 = gResourceManager->Find<Texture>(L"/Editor/GameViewCopyRWTexture");
	gGraphicDevice->CopyResource(rwTex2->GetID3D11Texture2D(), renderTex->GetID3D11Texture2D());
	TextureAlphaTo(rwTex, rwTex2, 1.f);
	gGraphicDevice->CopyResource(renderTex->GetID3D11Texture2D(), rwTex->GetID3D11Texture2D());
	Engine::GetInstance()->OmSet();

	ImGui::Begin("Game View");
	ID3D11ShaderResourceView* texture = renderTex->GetSRV();
	ImVec2 cursurScreenPos = ImGui::GetCursorScreenPos();
	ImVec2 renderTargetSize = ImVec2(renderTex->GetWidth(), renderTex->GetHeight());
	POINT ptMousePos = {};
	GetCursorPos(&ptMousePos);
	ImVec2 mousePos = ImVec2(ptMousePos.x, ptMousePos.y);
	ImGui::Image((void*)texture, renderTargetSize);
	ImVec2 screenMousePos = ImVec2(mousePos.x - cursurScreenPos.x,
		mousePos.y - cursurScreenPos.y);
	
	ImGui::Text("cursur posX%f cursur  posY%f", cursurScreenPos.x, cursurScreenPos.y);
	ImGui::Text("mouse posX%d mouse posY%d", ptMousePos.x, ptMousePos.y);
	ImGui::Text("In Screen Mouse Pos X%f Y%f", screenMousePos.x, screenMousePos.y);
	WindowManager::GetInstance()->SetWindowScreenPos(Vector2(screenMousePos.x, screenMousePos.y));
	ImGui::End();
}

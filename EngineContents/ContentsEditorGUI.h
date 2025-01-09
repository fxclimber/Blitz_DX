#pragma once
#include <EngineCore/EngineGUIWindow.h>

// 설명 : 프레임을 띄우거나
// 레벨이동을 내가 원레벨로 가거나 하는 것등등을 하게해주는 gui
class UContentsEditorGUI : public UEngineGUIWindow
{
public:
	// constrcuter destructer
	UContentsEditorGUI();
	~UContentsEditorGUI();

	// delete Function
	UContentsEditorGUI(const UContentsEditorGUI& _Other) = delete;
	UContentsEditorGUI(UContentsEditorGUI&& _Other) noexcept = delete;
	UContentsEditorGUI& operator=(const UContentsEditorGUI& _Other) = delete;
	UContentsEditorGUI& operator=(UContentsEditorGUI&& _Other) noexcept = delete;

protected:
	void OnGUI() override;

private:

};


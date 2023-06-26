#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui-SFML.h>
#include <Menus/EditorBase.hpp>
#include "Game.hpp"

class BulletEditor : public EditorBase {

	int bulletEditIndex = 0;

	char bulletName[32] = "";

	virtual void Update(Game& game) override {
		ImGui::Begin("Bullet Editor");
		BulletHandler& bh = game.GetBulletHandler();

		if (ImGui::Button("Create New Bullet Data")) {
			BulletData bd = BulletData();
			bh.bullets.push_back(bd);

			bulletEditIndex = bh.bullets.size() - 1;
		}

		if (!bh.bullets.empty()) {
			if (ImGui::BeginCombo("##label1", bh.bullets[bulletEditIndex].name.c_str())) {
				for (uint32_t i = 0; i < bh.bullets.size(); i++)
				{
					bool isSelected = &bh.bullets[i] == &bh.bullets[bulletEditIndex];
					std::string label = bh.bullets[i].name + "###" + std::to_string(i); // Avoid label conflicts
					if (ImGui::Selectable(label.c_str(), isSelected)) {
						bulletEditIndex = i;
					}
				}
				ImGui::EndCombo();
			}

			ImGui::InputText("Name", &bh.bullets[bulletEditIndex].name);

			for (uint32_t i = 0; i < bh.bullets[bulletEditIndex].states.size(); i++)
			{
				std::string label = "State " + std::to_string(i);
				if (ImGui::CollapsingHeader(label.c_str())) {
					ImGui::InputFloat("Speed", &bh.bullets[bulletEditIndex].states[i].speed);
					ImGui::ColorEdit4("Color", (float*)&bh.bullets[bulletEditIndex].states[i].color);
					ImGui::DragFloat("Scale", &bh.bullets[bulletEditIndex].states[i].scale.x, 0.2f, 1, 100);
					ImGui::DragFloat("Angular Velocity", &bh.bullets[bulletEditIndex].states[i].angularVelocity, 0.01f, -100, 100);
				}
			}
		}

		ImGui::End();
	}

	const char* GetName() {
		return "Bullet Editor";
	}
};

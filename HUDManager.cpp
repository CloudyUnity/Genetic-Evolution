#include "HUDManager.h"

Shape* HUDManager::GenTXT;
Shape* HUDManager::FPSTXT;
Shape* HUDManager::CreatureCountTXT;
Shape* HUDManager::GenesTXT;
Shape* HUDManager::InternalsTXT;
Shape* HUDManager::GenProgressTXT;

Button* HUDManager::PauseBttn;

void HUDManager::Init() {

	const double rightHUDSize = 150;
	Shape::ShapeInfo info;
	info.ConnectedToEastWindowEdge = true;
	info.ZoomDisabled = true;
	info.Layer = 4000;
	info.Position = Vector2(-rightHUDSize * 0.5, SimulationSetup::WINDOW_BOUNDS.Y * 0.5);
	info.Scale = Vector2(rightHUDSize, SimulationSetup::WINDOW_BOUNDS.Y);
	info.Col = SimulationSetup::HUD_BG_COLOR;
	info.BorderColor = Color::BLACK;
	info.BorderSize = 15;
	Shape* rightHUD = new Shape(info);

	info = Shape::ShapeInfo();
	info.ConnectedToEastWindowEdge = true;
	info.ZoomDisabled = true;
	info.Position = Vector2(-rightHUDSize * 0.5, 45);
	info.Scale = Vector2(75, 30);
	info.Layer = 4100;
	info.Col = SimulationSetup::HUD_BUTTON_COLOR;
	info.BorderColor = Color::BLACK;
	info.Text = "Restart";
	info.RenderText = true;
	info.TextColor = Color::COZY_BLACK;
	info.Clickable = true;
	info.Hoverable = true;
	info.BorderSize = 5;
	Button* restart = new Button(info, &SimulationManager::RestartSim);

	info.Position = Vector2(-rightHUDSize * 0.5, 275);
	info.Text = "   ||   ";
	PauseBttn = new Button(info, &PauseSim);

	info.Position = Vector2(-rightHUDSize * 0.5, 315);
	info.Text = "  >>  ";
	Button* fastForward = new Button(info, &FastForward);

	double textSpacing = 30;

	info = Shape::ShapeInfo();
	info.ConnectedToEastWindowEdge = true;
	info.ZoomDisabled = true;
	info.Position = Vector2(-rightHUDSize * 0.5, 85);
	info.Scale = Vector2(100, 80);
	info.Layer = 4100;
	info.Col = Color::TRANS;
	info.Text = "ERROR";
	info.RenderText = true;
	info.TextColor = Color::BLACK;
	FPSTXT = new Shape(info);

	info.Position = Vector2(-rightHUDSize * 0.5, 85 + textSpacing);
	GenTXT = new Shape(info);

	info.Position = Vector2(-rightHUDSize * 0.5, 85 + textSpacing * 2);
	GenProgressTXT = new Shape(info);

	info.Position = Vector2(-rightHUDSize * 0.5, 85 + textSpacing * 3);
	info.QuickDrawDisabled = true;
	CreatureCountTXT = new Shape(info);

	info.Position = Vector2(-rightHUDSize * 0.5, 85 + textSpacing * 4);
	GenesTXT = new Shape(info);

	info.Position = Vector2(-rightHUDSize * 0.5, 85 + textSpacing * 5);
	InternalsTXT = new Shape(info);
}

void HUDManager::Update() {
	FPSTXT->SetText("FPS: " + std::to_string((int)UpdateManager::FPS));	
	double progress = UpdateManager::UpdatesSinceSimStart / (SimulationManager::SimulationSecondsPerGen * 100) * 100;
	progress += 0.5 - (progress < 0);
	GenProgressTXT->SetText("Progress: " + std::to_string((int)progress) + "%");
}

void HUDManager::PauseSim() {
	if (SimulationManager::UpdatesPerFrame == 0) {
		SimulationManager::ChangeSimSpeed(1);
		PauseBttn->SetText("   ||   ");
	}		
	else {
		SimulationManager::PauseSim();
		PauseBttn->SetText("  >  ");
	}		
}

void HUDManager::FastForward() {
	if (SimulationManager::UpdatesPerFrame == 0) {
		SimulationManager::ChangeSimSpeed(1);
		return;
	}

	SimulationManager::ChangeSimSpeed(SimulationManager::UpdatesPerFrame * 2);
}
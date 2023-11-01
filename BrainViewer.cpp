#include "BrainViewer.h"

std::unordered_map<CreatureNeuron*, Shape*> BrainViewer::NeuronShapeHashMap;
std::vector<Shape*> BrainViewer::CurrentShapes;

void BrainViewer::DisplayBrain(CreatureBrain brain) {

	ClearOldBrain();

	ConvertToNeuronShapes(brain.InputNeurons);
	ConvertToNeuronShapes(brain.InternalNeurons);
	ConvertToNeuronShapes(brain.OutputNeurons);

	Logger::Log("Hashmap initalised");

	const bool WIRE_COLOR_DEGRADING_DISABLED = true;

	for (auto const& [neuron, shape] : NeuronShapeHashMap) {

		for (int c = 0; c < neuron->Connections.size(); c++) {

			CreatureNeuron::Connection connection = neuron->Connections.at(c);

			if (connection.OutputNeuron == nullptr)
				continue;

			if (!NeuronShapeHashMap.count(connection.OutputNeuron))
				continue;

			Shape::ShapeInfo info;
			info.IsLine = true;

			float weightMult = connection.Weight * 0.25f;
			if (WIRE_COLOR_DEGRADING_DISABLED)
				weightMult = 1;

			info.Col = connection.Weight < 0 ? Color(255 * weightMult, 0, 0, 255) : Color(0, 255 * weightMult, 0, 255);
			info.Position = shape->Info.Position;
			info.LineEndPosition = NeuronShapeHashMap[connection.OutputNeuron]->Info.Position;
			info.Text = "Brain wire";
			info.Layer = 1250;
			Shape* wireConnectionShape = new Shape(info);
			CurrentShapes.push_back(wireConnectionShape);
		}
	}

	Logger::Log("Brain displayed");
}

void BrainViewer::ConvertToNeuronShapes(std::vector<CreatureNeuron*> list) {
	for (int i = 0; i < list.size(); i++) {

		CreatureNeuron* neuron = list.at(i);
		Shape::ShapeInfo info;		
		
		switch (neuron->Type) {
			case CreatureNeuron::NeuronType::INPUT: 
				info.Position = Vector2(100 + 50 * i, 300);
				info.Col = Color(0, 0, 255, 255);
				break;
			case CreatureNeuron::NeuronType::INTERNAL:
				info.Position = Vector2(115 + 50 * i, 350);
				info.Col = Color(50, 50, 50, 255);
				break;
			case CreatureNeuron::NeuronType::OUTPUT:
				info.Position = Vector2(100 + 50 * i, 400);
				info.Col = Color(255, 0, 0, 255);
				break;
		}

		
		info.Scale = Vector2(30, 30);
		info.BorderSize = 4;
		info.BorderColor = Color(0, 0, 0, 255);
		info.Text = "Brain neuron";
		info.Layer = 1200;
		Shape* shape = new Shape(info);
		CurrentShapes.push_back(shape);
		NeuronShapeHashMap.insert({ neuron, shape });
		//Logger::Log("Neuron added to hashmap");
	}
}

void BrainViewer::ClearOldBrain() {

	for (int i = CurrentShapes.size() - 1; i >= 0; i--) {
		PaintManager::RemoveShape(CurrentShapes.at(i));
	}
	
	CurrentShapes.clear();
	NeuronShapeHashMap.clear();
}
#include "NeuronEye.h"
#include "SDL.h"
#include "WallManager.h"

NeuronEye::NeuronEye(NeuronType type, VisionType visionType, Vector2 origin, double angle) : CreatureNeuron(type) {
	Vision = visionType;
    Origin = origin;
    RotAngle = angle * (M_PI / 180.0);

    Shape::ShapeInfo info;
    info.IsLine = true;
    RaycastLine = new Shape(info);
}

float NeuronEye::CalcInputValue(Creature* creature) {
	
    float closestHit = std::numeric_limits<float>::infinity();

    double angle = creature->Info.RotationAngle * (M_PI / 180.0);
    double rotatedX = Origin.X * cos(angle) - Origin.Y * sin(angle);
    double rotatedY = Origin.X * sin(angle) + Origin.Y * cos(angle);

    Vector2 origin = creature->Info.Position.Add(Vector2(rotatedX, rotatedY));

    Vector2 dir = creature->GetPointDirection();
    double newAngle = atan2(dir.Y, dir.X) + RotAngle;
    dir = Vector2(cos(newAngle), sin(newAngle));
    Vector2 end = origin.Add(dir.Mult(SimulationSetup::MAX_VISION_DISTANCE));

	if (Vision == VisionType::CREATURE) {
        
        int size = CreatureManager::CreatureList.size();
		for (int i = 0; i < size; i++) {

			if (CreatureManager::CreatureList.at(i) == creature)
				continue;
            
            float distance = RayCastShape(origin, end, CreatureManager::CreatureList.at(i));
            if (distance < closestHit)
                closestHit = distance;
		}        
	}

    if (Vision == VisionType::WALL) {

        int size = WallManager::WallList.size();
        for (int i = 0; i < size; i++) {

            float distance = RayCastShape(origin, end, WallManager::WallList.at(i));
            if (distance < closestHit)
                closestHit = distance;
        }
    }

    bool noHit = closestHit > SimulationSetup::MAX_VISION_DISTANCE || closestHit == 0;

    if (!noHit)
        end = origin.Add(dir.Mult(closestHit));

    RaycastLine->Info.Col = noHit ? Color(255, 0, 0, 255) : Color(0, 255, 0, 255);
    RaycastLine->Info.Position = origin;
    RaycastLine->Info.LineEndPosition = end;
    RaycastLine->Info.Visible = (creature == CreatureManager::SelectedCreature);

    if (noHit)
        return 0;

    return (1 / closestHit) / SimulationSetup::MAX_VISION_DISTANCE;
}

float NeuronEye::RayCastShape(Vector2 origin, Vector2 end, Shape* shape) {

    Vector2 p1 = Vector2(-shape->Info.HalfScale.X, -shape->Info.HalfScale.Y);
    Vector2 p2 = Vector2(shape->Info.HalfScale.X, -shape->Info.HalfScale.Y);
    Vector2 p3 = Vector2(-shape->Info.HalfScale.X, shape->Info.HalfScale.Y);
    Vector2 p4 = Vector2(shape->Info.HalfScale.X, shape->Info.HalfScale.Y);

    double angle = shape->Info.RotationAngle * (M_PI / 180.0);

    double rX = p1.X * cos(angle) - p1.Y * sin(angle);
    double rY = p1.X * sin(angle) + p1.Y * cos(angle);
    p1 = shape->Info.Position.Add(rX, rY);

    rX = p2.X * cos(angle) - p2.Y * sin(angle);
    rY = p2.X * sin(angle) + p2.Y * cos(angle);
    p2 = shape->Info.Position.Add(rX, rY);

    rX = p3.X * cos(angle) - p3.Y * sin(angle);
    rY = p3.X * sin(angle) + p3.Y * cos(angle);
    p3 = shape->Info.Position.Add(rX, rY);

    rX = p4.X * cos(angle) - p4.Y * sin(angle);
    rY = p4.X * sin(angle) + p4.Y * cos(angle);
    p4 = shape->Info.Position.Add(rX, rY);

    float closestDistance = std::numeric_limits<float>::infinity();

    float dis = CheckIntersection(origin, end, p1, p2);
    if (dis < closestDistance)
        closestDistance = dis;

    dis = CheckIntersection(origin, end, p1, p3);
    if (dis < closestDistance)
        closestDistance = dis;

    dis = CheckIntersection(origin, end, p3, p4);
    if (dis < closestDistance)
        closestDistance = dis;

    dis = CheckIntersection(origin, end, p2, p4);
    if (dis < closestDistance)
        closestDistance = dis;

    return closestDistance;
}

float NeuronEye::CheckIntersection(Vector2 origin, Vector2 end, Vector2 p1, Vector2 p2) {

    float den = (p1.X - p2.X) * (origin.Y - end.Y) - (p1.Y - p2.Y) * (origin.X - end.X);

    if (den == 0)
        return std::numeric_limits<float>::infinity();

    float t = ((p1.X - origin.X) * (origin.Y - end.Y) - (p1.Y - origin.Y) * (origin.X - end.X)) / den;

    if (t < 0 || t > 1)
        return std::numeric_limits<float>::infinity();

    float u = ((p1.X - origin.X) * (p1.Y - p2.Y) - (p1.Y - origin.Y) * (p1.X - p2.X)) / den;

    if (u < 0 || u > 1)
        return std::numeric_limits<float>::infinity();

    float hitX = p1.X + t * (p2.X - p1.X);
    float hitY = p1.Y + t * (p2.Y - p1.Y);

    float a = hitX - origin.X;
    float b = hitY - origin.Y;
    return sqrt(a * a + b * b);
}

void NeuronEye::DeleteSelf() {
    if (RaycastLine)
        PaintManager::RemoveShape(RaycastLine);
}

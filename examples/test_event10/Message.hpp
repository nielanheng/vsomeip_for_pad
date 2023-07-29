#include <iostream>
#include <array>
#ifndef MYTEST_MESSAGE_H
#define MYTEST_MESSAGE_H

#endif
struct PathPointType
{
    double Longitude;
    double Latitude;
    double Heading;
    uint8_t Property;
};

struct TrajectoryFollowType
{
    uint8_t MissionID;
//    std::array<PathPointType,4> MissionPoints;
    PathPointType MissionPoints[];
};
 
struct ObjectFollowType
{
    uint8_t MissionID;
    uint8_t ObjectID;
    float Distance;
    uint8_t Mode;
};

struct TargetPointNaviType
{
    uint8_t MissionID;
    // edit
//    std::array<PathPointType,4> MissionPoints;
    PathPointType MissionPoints[];
};

struct ReturnHomeType
{
    uint8_t MissionID;
    uint8_t Mode;
};

struct PatrolType
{
    uint8_t MissionID;
    uint8_t PatrolNum;
    uint8_t Mode;
    PathPointType MissionPoints[];
};

struct MissionControlType
{
    uint8_t MissionID;
    uint8_t ControlCommand;
};

struct VideoConfigType
{
    uint8_t Switch;
    uint8_t Mode;
    uint8_t Stream;
    uint8_t Resolution;
    uint8_t Source;
};

struct MissionType
{
    uint8_t MissionID;
    uint8_t Type;
    uint8_t State;
    uint8_t Process;
};

struct ObjectInfo
{
    uint32_t ID;
    uint8_t Type;
    uint32_t LeftTopX;
    uint32_t LeftTopY;
    uint32_t RightBottomX;
    uint32_t RightBottomY;
    float LocolX;
    float LocolY;
    float LocolZ;
    float VelocityX;
    float VelocityY;
    float VelocityZ;
    double Longitude;
    double Latitude;
    double Altitude;
    float VelocityE;
    float VelocityN;
    float VelocityU;
    uint32_t CameraID;
};

struct ObjectList
{
    uint64_t TimeStamp;
    ObjectInfo ObjList;
};

struct General_Ext_StsType
{
    uint32_t SystemMode;
    uint32_t HighVoltage;
    uint32_t LowVoltage;
    uint32_t LowVoltagePower;
    uint32_t HighVoltagePower;
    uint32_t EquipmentNo;
    uint32_t EmergencyStopSts;
    uint32_t EngineTemp;
    uint32_t IsgMotorTemp;
    uint32_t LeftMotorTemp;
    uint32_t LeftMotorControllerTemp;
    uint32_t RightMotorTemp;
    uint32_t RightMotorControllerTemp;
    uint32_t Longitude;
    uint32_t Latitude;
    uint32_t Course;
    uint32_t EngineSpeed;
    uint32_t ReqGenerationPower;
    uint32_t ActGenerationPower;
    uint32_t ActBrakePressure;
    uint32_t TotalMileage;
    uint32_t RemainMileagePureElectricity;
    uint32_t TotalRemainMileage;
    uint32_t RemainOil;
    uint32_t RemainElectricity;
    uint32_t SteerMode;
    uint32_t HornOnOffSts;
    uint32_t CornerLamp;
    uint32_t DippedHeadLightl;
    uint32_t HighBeam;
    uint32_t EmergencyLamp;
    uint32_t Altitude;
    uint32_t ErrorCode;
    uint32_t AngelPitch;
    uint32_t AngleRoll;
    uint32_t IMU_STS;
    uint32_t Package_a;
    uint16_t b;
    uint16_t c;
    uint16_t d;
    uint16_t e;
    uint16_t f;
    uint16_t g;
    uint16_t h;
    uint16_t i;
    uint16_t k;
    uint32_t l;
    uint32_t m;
};

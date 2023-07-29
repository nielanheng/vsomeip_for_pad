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
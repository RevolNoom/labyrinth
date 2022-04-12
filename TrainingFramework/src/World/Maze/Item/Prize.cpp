#include "World/Maze/Item/Prize.h"
#include "GameScenes/ScenePlayLogicServer.h"
#include "ServiceLocator.h"

Prize::Prize() :
    Trap(ResourceManagers::GetInstance()->GetTexture("ring.tga"))
{
    ScenePlayLogicServer::GetInstance()->SetUpPrize(this);
}


void Prize::Draw()
{
    if (IsEnabled())
        Trap::Draw();
}

void Prize::Trigger()
{
    if (IsEnabled())
    {
        ServiceLocator::GetInstance()->GetSoundEffectAudioPlayer()->Play(Music("snd_gold.mp3"));
        ScenePlayLogicServer::GetInstance()->PickUpPrize();

    }
}


std::shared_ptr<PhysicObject> Prize::Clone()
{
    auto newClone = std::make_shared<Prize>();

    newClone->SetRotation(GetRotation());
    newClone->SetPosition(GetPosition());
    newClone->SetEnabled(IsEnabled());
    newClone->SetSize(GetSize());

    return newClone;
}

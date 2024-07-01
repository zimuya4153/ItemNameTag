#include "Entry.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

LL_AUTO_TYPE_INSTANCE_HOOK(ACTickHook, ll::memory::HookPriority::Normal, ItemActor, &ItemActor::postNormalTick, void) {
    origin();
    auto item = this->item();
    ll::service::getLevel()->forEachPlayer([&](Player& player) -> bool {
        if (player.isSimulated()) return true;
        SetActorDataPacket packet;
        packet.mId = getRuntimeID();
        // auto& player2 = (GMLIB_Player&)player;
        // packet.mPackedItems.emplace_back(DataItem::create(
        //     ActorDataIDs::Name,
        //     item.getCustomName() == ""
        //         ? I18nAPI::get(item.getDescriptionId(), {}, std::string(player2.getLanguageCode()))
        //         : item.getCustomName()
        // ));
        packet.mPackedItems.emplace_back(DataItem::create(
            ActorDataIDs::Name,
            item.getCustomName() == "" ? I18nAPI::get(
                                             item.getDescriptionId(),
                                             {},
                                             ll::service::getServerNetworkHandler()
                                                 ->fetchConnectionRequest(player.getNetworkIdentifier())
                                                 .mRawToken->mDataInfo.get("LanguageCode", "en_US")
                                                 .asString("en_US")
                                         )
                                       : item.getCustomName()
        ));
        packet.mPackedItems.emplace_back(DataItem::create(ActorDataIDs::NametagAlwaysShow, true));
        packet.sendTo(player);
        return true;
    });
}

namespace ItemName_Tag {

std::unique_ptr<ItemNameTag>& ItemNameTag::getInstance() {
    static std::unique_ptr<ItemNameTag> instance;
    return instance;
}

bool ItemNameTag::load() {
    GMLIB::Mod::VanillaFix::setFixI18nEnabled();
    return true;
}

bool ItemNameTag::enable() { return true; }

bool ItemNameTag::disable() { return true; }

bool ItemNameTag::unload() {
    ll::memory::HookRegistrar<ACTickHook>().unhook();
    return true;
}

} // namespace ItemName_Tag

LL_REGISTER_PLUGIN(ItemName_Tag::ItemNameTag, ItemName_Tag::ItemNameTag::getInstance());
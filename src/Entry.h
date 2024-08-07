#pragma once
#include <ll/api/plugin/NativePlugin.h>
#include <ll/api/plugin/RegisterHelper.h>

namespace ItemName_Tag {

class ItemNameTag {

public:
    static std::unique_ptr<ItemNameTag>& getInstance();

    ItemNameTag(ll::plugin::NativePlugin& self) : mSelf(self) {}

    [[nodiscard]] ll::plugin::NativePlugin& getSelf() const { return mSelf; }

    /// @return True if the plugin is loaded successfully.
    bool load();

    /// @return True if the plugin is enabled successfully.
    bool enable();

    /// @return True if the plugin is disabled successfully.
    bool disable();

    // /// @return True if the plugin is unloaded successfully.
    bool unload();

private:
    ll::plugin::NativePlugin& mSelf;
};

} // namespace ItemName_Tag
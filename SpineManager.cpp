#include "SpineManager.h"
#include <spine/SkeletonBinary.h>

SpineManager& SpineManager::getInstance() {
    static SpineManager instance;
    return instance;
}

bool SpineManager::loadSkeleton(const std::string& name,
                                const std::string& atlasPath,
                                const std::string& skelPath,
                                float scale) {
    if (assets.count(name)) {
        std::cout << "[SpineManager] Warning: '" << name << "' already loaded.\n";
        return true;
    }

    SkeletonAsset asset;

    // 1. 创建纹理加载器并加载 Atlas
    asset.textureLoader = std::make_unique<spine::SFMLTextureLoader>();
    asset.atlas = std::make_unique<spine::Atlas>(
        atlasPath.c_str(), asset.textureLoader.get());

    if (asset.atlas->getPages().size() == 0) {
        std::cerr << "[SpineManager] Error: Failed to load atlas: " << atlasPath << "\n";
        return false;
    }

    // 2. 通过 AtlasAttachmentLoader 读取 .skel 二进制
    spine::AtlasAttachmentLoader attachmentLoader(*asset.atlas);
    spine::SkeletonBinary binary(attachmentLoader);
    binary.setScale(scale);

    spine::SkeletonData* rawData = binary.readSkeletonDataFile(skelPath.c_str());
    if (!rawData) {
        std::cerr << "[SpineManager] Error: Failed to load skeleton: " << skelPath << "\n";
        if (binary.getError().length() > 0)
            std::cerr << "  Reason: " << binary.getError().buffer() << "\n";
        return false;
    }

    asset.skeletonData.reset(rawData);


    // 打印骨架中包含的所有动画名称（调试用）
    {
        std::cout << "[SpineManager] Animations in '" << name << "': ";
        auto& anims = asset.skeletonData->getAnimations();
        if (anims.size() == 0) {
            std::cout << "(none)";
        } else {
            for (size_t i = 0; i < anims.size(); i++) {
                if (i > 0) std::cout << ", ";
                std::cout << anims[i]->getName().buffer();
            }
        }
        std::cout << "\n";
    }

    // 3. 创建 AnimationStateData（用于配置动画混合时间）
    asset.animStateData = std::make_unique<spine::AnimationStateData>(*asset.skeletonData);
    configureMixTimes(*asset.animStateData, *asset.skeletonData);

    assets[name] = std::move(asset);
    std::cout << "[SpineManager] Loaded: " << name << "\n";
    return true;
}

spine::SkeletonData* SpineManager::getSkeletonData(const std::string& name) const {
    auto it = assets.find(name);
    if (it == assets.end()) {
        std::cerr << "[SpineManager] Error: SkeletonData not found for '" << name << "'\n";
        return nullptr;
    }
    return it->second.skeletonData.get();
}

spine::AnimationStateData* SpineManager::getAnimationStateData(const std::string& name) const {
    auto it = assets.find(name);
    if (it == assets.end()) return nullptr;
    return it->second.animStateData.get();
}

bool SpineManager::hasSkeletonData(const std::string& name) const {
    return assets.count(name) > 0;
}

void SpineManager::clear() {
    assets.clear();
    std::cout << "[SpineManager] All assets cleared.\n";
}

void SpineManager::configureMixTimes(spine::AnimationStateData& asd, spine::SkeletonData& sd) {
    // 全局默认混合时间（未单独配置的动画对使用此值）
    asd.setDefaultMix(0.12f);

    // 辅助 lambda：只在两个动画都存在时才配置混合
    auto safeMix = [&](const char* from, const char* to, float dur) {
        if (sd.findAnimation(from) && sd.findAnimation(to))
            asd.setMix(from, to, dur);
    };

    // 动作切换（快速）
    safeMix("idle", "attack", 0.10f);
    safeMix("attack", "idle", 0.15f);
    safeMix("idle", "shoot", 0.10f);
    safeMix("shoot", "idle", 0.15f);

    // 死亡过渡（更快速，保证游戏节奏感）
    safeMix("idle", "die", 0.08f);
    safeMix("attack", "die", 0.08f);
    safeMix("shoot", "die", 0.08f);
    safeMix("walk", "die", 0.08f);
}

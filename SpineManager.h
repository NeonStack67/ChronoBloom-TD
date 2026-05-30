#pragma once
#include <spine/spine.h>
#include <spine/SkeletonBinary.h>
#include <spine/Atlas.h>
#include <spine/AtlasAttachmentLoader.h>
#include <spine/AnimationStateData.h>
#include <spine-sfml.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

// 管理 Spine Atlas 和 SkeletonData 的加载与缓存（单例）
// SkeletonData 每种实体只加载一次，多个实例共享
class SpineManager {
public:
    static SpineManager& getInstance();

    SpineManager(const SpineManager&) = delete;
    SpineManager& operator=(const SpineManager&) = delete;

    // 加载指定实体的 atlas + skel 文件，内部缓存
    // name: 实体类型名，如 "NormalZombie"
    // atlasPath: .atlas 文件路径
    // skelPath:  .skel 二进制文件路径
    // scale: 骨骼缩放（通常用于将 Spine 设计尺寸适配格子大小）
    bool loadSkeleton(const std::string& name,
                      const std::string& atlasPath,
                      const std::string& skelPath,
                      float scale = 1.0f);

    // 获取缓存的 SkeletonData（非拥有指针，由 SpineManager 管理生命周期）
    spine::SkeletonData* getSkeletonData(const std::string& name) const;

    // 获取缓存的 AnimationStateData（用于配置动画混合时间）
    spine::AnimationStateData* getAnimationStateData(const std::string& name) const;

    bool hasSkeletonData(const std::string& name) const;

    // 释放所有已加载资源（游戏退出时调用）
    void clear();

private:
    SpineManager() = default;
    ~SpineManager() = default;

    // 配置动画混合时间（交叉淡入淡出）
    void configureMixTimes(spine::AnimationStateData& asd, spine::SkeletonData& sd);

    // 使用 TextureLoader 持有纹理生命周期
    struct SkeletonAsset {
        // Atlas 必须在 SkeletonData 之前析构，且 textureLoader 必须在 Atlas 之前保持存活
        std::unique_ptr<spine::SFMLTextureLoader> textureLoader;
        std::unique_ptr<spine::Atlas> atlas;
        std::unique_ptr<spine::SkeletonData> skeletonData;
        std::unique_ptr<spine::AnimationStateData> animStateData;
    };

    std::unordered_map<std::string, SkeletonAsset> assets;
};

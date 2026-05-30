#pragma once
#include <spine/spine.h>
#include <spine/AnimationState.h>
#include <spine/AnimationStateData.h>
#include <spine/Skeleton.h>
#include <spine/SkeletonRenderer.h>
#include <spine-sfml.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

// 每个实体实例独立持有一份 Skeleton + AnimationState
// 提供面向游戏逻辑的高层 API，隐藏 Spine 内部细节
class SpineComponent {
public:
    // data: 来自 SpineManager，多实例共享，非拥有
    // animStateData: 来自 SpineManager，提供动画混合配置，非拥有
    SpineComponent(spine::SkeletonData* data, spine::AnimationStateData* animStateData);
    ~SpineComponent();

    // 每帧调用：推进动画时间，更新骨骼状态
    void update(float dt);

    // 渲染：将骨骼原点设置到 pixelPos 后绘制
    void draw(sf::RenderWindow& window, sf::Vector2f pixelPos, bool premultipliedAlpha = false);

    // ── 动画控制 ─────────────────────────────────────────────────────
    // 播放指定动画（立即切换，替换当前 track）
    void playAnimation(const std::string& animName, bool loop, int track = 0);

    // 队列：当前动画结束后播放（delay<=0 表示紧接着）
    void addAnimation(const std::string& animName, bool loop, int track = 0, float delay = 0.f);

    // 检查指定 track 的当前动画是否已播放完（非循环动画用）
    bool isAnimationComplete(int track = 0) const;

    // 检查指定 track 是否有动画在播放
    bool hasAnimation(int track = 0) const;

    // 获取当前 track 0 动画名（用于状态判断，避免重复切换）
    std::string getCurrentAnimationName(int track = 0) const;

    // 检查骨架数据中是否存在指定名称的动画
    bool hasAnimationName(const std::string& animName) const;

    // 清除指定 track 的当前动画和所有队列中的动画
    void clearTrack(int track = 0);

    // 清除所有 track
    void clearTracks();

    // ── 视觉控制 ─────────────────────────────────────────────────────
    // 设置整体着色（受伤红色、激发绿色等）
    void setTint(sf::Color color);
    void resetTint();

    // 水平翻转（僵尸向左走：flipX=true；植物朝右：flipX=false）
    void setFlipX(bool flip);

    // 整体缩放
    void setScale(float scaleX, float scaleY);

    // ── 包围盒 ────────────────────────────────────────────────────────
    // 返回当前骨架的世界包围盒（用于血条定位和碰撞检测）
    // 注意：调用前须先 update()，才能得到当前帧正确包围盒
    sf::FloatRect getBounds() const;

private:
    std::unique_ptr<spine::Skeleton> skeleton;
    std::unique_ptr<spine::AnimationState> animState;

    // SkeletonRenderer 是无状态的，可以在各 Component 之间共享
    // 但为了简单，每个 Component 持有一个（可后续优化为全局共享）
    spine::SkeletonRenderer renderer;

    // 当前渲染时的像素原点（每次 draw 时更新）
    sf::Vector2f currentPixelPos;

    // 记录当前 tint（供 draw 使用）
    spine::Color currentTint;
};

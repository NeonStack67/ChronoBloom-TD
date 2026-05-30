#include "SpineComponent.h"
#include <spine/Physics.h>
#include <iostream>

SpineComponent::SpineComponent(spine::SkeletonData* data, spine::AnimationStateData* animStateData) {
    if (!data || !animStateData) {
        std::cerr << "[SpineComponent] Error: null SkeletonData or AnimationStateData\n";
        return;
    }

    skeleton = std::make_unique<spine::Skeleton>(*data);
    animState = std::make_unique<spine::AnimationState>(*animStateData);

    // 初始化默认白色（不着色）
    currentTint = spine::Color(1.f, 1.f, 1.f, 1.f);
    skeleton->setColor(currentTint);
}

SpineComponent::~SpineComponent() = default;

void SpineComponent::update(float dt) {
    if (!animState || !skeleton) return;

    animState->update(dt);
    animState->apply(*skeleton);
    skeleton->updateWorldTransform(spine::Physics_Update);
}

void SpineComponent::draw(sf::RenderWindow& window, sf::Vector2f pixelPos, bool premultipliedAlpha) {
    if (!skeleton) return;

    currentPixelPos = pixelPos;
    skeleton->setPosition(pixelPos.x, pixelPos.y);
    // 重新更新一次，以确保位置变更生效
    skeleton->updateWorldTransform(spine::Physics_None);

    spine::SFML_draw(*skeleton, window, premultipliedAlpha);
}

void SpineComponent::playAnimation(const std::string& animName, bool loop, int track) {
    if (!animState || animName.empty()) return;
    if (!skeleton->getData().findAnimation(animName.c_str())) return;
    animState->setAnimation(static_cast<size_t>(track), animName.c_str(), loop);
}

void SpineComponent::addAnimation(const std::string& animName, bool loop, int track, float delay) {
    if (!animState) return;
    if (animName.empty()) {
        animState->addEmptyAnimation(static_cast<size_t>(track), 0.f, delay);
        return;
    }
    if (!skeleton->getData().findAnimation(animName.c_str())) return;
    animState->addAnimation(static_cast<size_t>(track), animName.c_str(), loop, delay);
}

bool SpineComponent::isAnimationComplete(int track) const {
    if (!animState) return true;
    spine::TrackEntry* entry = animState->getTrack(static_cast<size_t>(track));
    if (!entry) return true;
    // 非循环动画：track time >= animation duration 时视为完成
    return !entry->getLoop() && entry->getTrackTime() >= entry->getAnimationEnd();
}

bool SpineComponent::hasAnimation(int track) const {
    if (!animState) return false;
    return animState->getTrack(static_cast<size_t>(track)) != nullptr;
}

std::string SpineComponent::getCurrentAnimationName(int track) const {
    if (!animState) return "";
    spine::TrackEntry* entry = animState->getTrack(static_cast<size_t>(track));
    if (!entry) return "";
    return entry->getAnimation().getName().buffer();
}

bool SpineComponent::hasAnimationName(const std::string& animName) const {
    if (!skeleton || animName.empty()) return false;
    return skeleton->getData().findAnimation(animName.c_str()) != nullptr;
}

void SpineComponent::clearTrack(int track) {
    if (!animState) return;
    animState->clearTrack(static_cast<size_t>(track));
}

void SpineComponent::clearTracks() {
    if (!animState) return;
    animState->clearTracks();
}

void SpineComponent::setTint(sf::Color color) {
    if (!skeleton) return;
    currentTint = spine::Color(
        color.r / 255.f,
        color.g / 255.f,
        color.b / 255.f,
        color.a / 255.f
    );
    skeleton->setColor(currentTint);
}

void SpineComponent::resetTint() {
    if (!skeleton) return;
    currentTint = spine::Color(1.f, 1.f, 1.f, 1.f);
    skeleton->setColor(currentTint);
}

void SpineComponent::setFlipX(bool flip) {
    if (!skeleton) return;
    // Spine 用负 scaleX 实现水平翻转
    float absScaleX = std::abs(skeleton->getScaleX());
    skeleton->setScaleX(flip ? -absScaleX : absScaleX);
}

void SpineComponent::setScale(float scaleX, float scaleY) {
    if (!skeleton) return;
    skeleton->setScaleX(scaleX);
    skeleton->setScaleY(scaleY);
}

sf::FloatRect SpineComponent::getBounds() const {
    if (!skeleton) {
        return sf::FloatRect(currentPixelPos, sf::Vector2f(64.f, 64.f));
    }
    float bx, by, bw, bh;
    skeleton->getBounds(bx, by, bw, bh);
    return sf::FloatRect(sf::Vector2f(bx, by), sf::Vector2f(bw, bh));
}

# Install script for directory: C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/ChronoBloom_TD")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/dist/lib" TYPE STATIC_LIBRARY FILES "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/build/third_party/spine-runtimes/spine-cpp/Debug/spine-cpp.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/dist/lib" TYPE STATIC_LIBRARY FILES "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/build/third_party/spine-runtimes/spine-cpp/Release/spine-cpp.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/dist/lib" TYPE STATIC_LIBRARY FILES "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/build/third_party/spine-runtimes/spine-cpp/MinSizeRel/spine-cpp.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/dist/lib" TYPE STATIC_LIBRARY FILES "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/build/third_party/spine-runtimes/spine-cpp/RelWithDebInfo/spine-cpp.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    include("C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/build/third_party/spine-runtimes/spine-cpp/CMakeFiles/spine-cpp.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    include("C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/build/third_party/spine-runtimes/spine-cpp/CMakeFiles/spine-cpp.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    include("C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/build/third_party/spine-runtimes/spine-cpp/CMakeFiles/spine-cpp.dir/install-cxx-module-bmi-MinSizeRel.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    include("C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/build/third_party/spine-runtimes/spine-cpp/CMakeFiles/spine-cpp.dir/install-cxx-module-bmi-RelWithDebInfo.cmake" OPTIONAL)
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/dist/include" TYPE FILE FILES
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Animation.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/AnimationState.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/AnimationStateData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Array.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/ArrayUtils.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Atlas.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/AtlasAttachmentLoader.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Attachment.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/AttachmentLoader.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/AttachmentTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/AttachmentType.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/BlendMode.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/BlockAllocator.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Bone.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/BoneData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/BoneLocal.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/BonePose.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/BoneTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/BoundingBoxAttachment.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/ClippingAttachment.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Color.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/ColorTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Constraint.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/ConstraintData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/ConstraintTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/ConstraintTimeline1.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/CurveTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Debug.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/DeformTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/DrawOrder.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/DrawOrderFolderTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/DrawOrderTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Event.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/EventData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/EventTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Extension.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/HasRendererObject.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/HashMap.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/IkConstraint.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/IkConstraintData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/IkConstraintPose.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/IkConstraintTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Inherit.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/InheritTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Interpolation.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Json.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/LinkedMesh.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/MathUtil.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/MeshAttachment.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PathAttachment.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PathConstraint.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PathConstraintData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PathConstraintMixTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PathConstraintPose.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PathConstraintPositionTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PathConstraintSpacingTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Physics.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PhysicsConstraint.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PhysicsConstraintData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PhysicsConstraintPose.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PhysicsConstraintTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PointAttachment.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Pool.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Pose.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Posed.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PosedActive.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PosedData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/PositionMode.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Property.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/RTTI.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/RegionAttachment.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/RotateMode.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/RotateTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/ScaleTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Sequence.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SequenceTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/ShearTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Skeleton.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SkeletonBinary.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SkeletonBounds.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SkeletonClipping.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SkeletonData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SkeletonJson.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SkeletonRenderer.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Skin.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Slider.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SliderData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SliderMixTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SliderPose.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SliderTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Slot.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SlotCurveTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SlotData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SlotPose.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SlotTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SpacingMode.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SpineObject.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/SpineString.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/TextureLoader.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/TextureRegion.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Timeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/TransformConstraint.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/TransformConstraintData.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/TransformConstraintPose.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/TransformConstraintTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/TranslateTimeline.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Triangulator.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Update.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/Version.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/VertexAttachment.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/dll.h"
    "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/third_party/spine-runtimes/spine-cpp/include/spine/spine.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/jun_j/source/repos/PVZ_QianHeShiKong/build/third_party/spine-runtimes/spine-cpp/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()

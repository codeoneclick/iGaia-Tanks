#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU_SNAP-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/21410767/b2Timer.o \
	${OBJECTDIR}/_ext/837767863/GameMediumTankSDB.o \
	${OBJECTDIR}/_ext/837767863/CParser_MDL.o \
	${OBJECTDIR}/_ext/837767863/CRenderMgr.o \
	${OBJECTDIR}/_ext/837767863/GameNativeCommunicationMgr.o \
	${OBJECTDIR}/_ext/1176185352/b2EdgeAndCircleContact.o \
	${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoordNormalTangent.o \
	${OBJECTDIR}/_ext/837767863/CSettings.o \
	${OBJECTDIR}/_ext/837767863/ICamera.o \
	${OBJECTDIR}/_ext/837767863/CParticleEmitter.o \
	${OBJECTDIR}/_ext/837767863/CParticleMgr.o \
	${OBJECTDIR}/_ext/469629982/b2RopeJoint.o \
	${OBJECTDIR}/_ext/837767863/CTankHeavyTower.o \
	${OBJECTDIR}/_ext/837767863/ICollisionDelegate.o \
	${OBJECTDIR}/_ext/837767863/CSprite.o \
	${OBJECTDIR}/_ext/837767863/CCameraFree.o \
	${OBJECTDIR}/_ext/837767863/CDecalMgr.o \
	${OBJECTDIR}/_ext/837767863/CCameraTarget.o \
	${OBJECTDIR}/_ext/1176185352/b2CircleContact.o \
	${OBJECTDIR}/_ext/469629982/b2RevoluteJoint.o \
	${OBJECTDIR}/_ext/837767863/GameUserSDB.o \
	${OBJECTDIR}/_ext/837767863/CTankMediumBody.o \
	${OBJECTDIR}/_ext/837767863/CTankMediumTower.o \
	${OBJECTDIR}/_ext/837767863/CMathHelper.o \
	${OBJECTDIR}/_ext/469629982/b2FrictionJoint.o \
	${OBJECTDIR}/_ext/1350479654/b2World.o \
	${OBJECTDIR}/_ext/837767863/CTankHeavyTrack.o \
	${OBJECTDIR}/_ext/837767863/IDelegate.o \
	${OBJECTDIR}/_ext/837767863/GameLightTankSDB.o \
	${OBJECTDIR}/_ext/1176185352/b2ChainAndCircleContact.o \
	${OBJECTDIR}/_ext/837767863/CMaterial.o \
	${OBJECTDIR}/_ext/837767863/CVertexBufferPositionColor.o \
	${OBJECTDIR}/_ext/1438679880/b2Rope.o \
	${OBJECTDIR}/_ext/1180546860/b2Collision.o \
	${OBJECTDIR}/_ext/837767863/IGameLevel.o \
	${OBJECTDIR}/_ext/469629982/b2PulleyJoint.o \
	${OBJECTDIR}/_ext/837767863/CGameInGameScene.o \
	${OBJECTDIR}/_ext/837767863/IResource.o \
	${OBJECTDIR}/_ext/837767863/CGameUIMgr.o \
	${OBJECTDIR}/_ext/837767863/CScreenSpacePostMgr.o \
	${OBJECTDIR}/_ext/837767863/CShaderComposite.o \
	${OBJECTDIR}/_ext/837767863/CIndexBuffer.o \
	${OBJECTDIR}/_ext/1350479654/b2Island.o \
	${OBJECTDIR}/_ext/837767863/CBoundingBox.o \
	${OBJECTDIR}/_ext/837767863/CLandscape.o \
	${OBJECTDIR}/_ext/469629982/b2GearJoint.o \
	${OBJECTDIR}/_ext/837767863/CParser_PVR.o \
	${OBJECTDIR}/_ext/837767863/CFrustum.o \
	${OBJECTDIR}/_ext/837767863/CWindow.o \
	${OBJECTDIR}/_ext/837767863/CGameMainMenuScene.o \
	${OBJECTDIR}/_ext/837767863/GameClient.o \
	${OBJECTDIR}/_ext/837767863/CLandscapeDecal.o \
	${OBJECTDIR}/_ext/837767863/ITankPart.o \
	${OBJECTDIR}/_ext/837767863/IResourceLoaderDelegate.o \
	${OBJECTDIR}/_ext/1180546860/b2CollideEdge.o \
	${OBJECTDIR}/_ext/1180546860/b2CollideCircle.o \
	${OBJECTDIR}/_ext/21410767/b2StackAllocator.o \
	${OBJECTDIR}/_ext/837767863/CShader.o \
	${OBJECTDIR}/_ext/1180546860/b2Distance.o \
	${OBJECTDIR}/_ext/837767863/CSkyBox.o \
	${OBJECTDIR}/_ext/837767863/CGameInGameLevel.o \
	${OBJECTDIR}/_ext/1176185352/b2EdgeAndPolygonContact.o \
	${OBJECTDIR}/_ext/837767863/CParticleEmitterTrail.o \
	${OBJECTDIR}/_ext/1350479654/b2ContactManager.o \
	${OBJECTDIR}/_ext/837767863/CGameCharaterControllerMgr.o \
	${OBJECTDIR}/_ext/837767863/CResourceMgr.o \
	${OBJECTDIR}/_ext/21410767/b2BlockAllocator.o \
	${OBJECTDIR}/_ext/837767863/CTankLightBody.o \
	${OBJECTDIR}/_ext/837767863/IVertexBuffer.o \
	${OBJECTDIR}/_ext/837767863/CSceneMgr.o \
	${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoordNormal.o \
	${OBJECTDIR}/_ext/1176185352/b2Contact.o \
	${OBJECTDIR}/_ext/837767863/CNavigationHelper.o \
	${OBJECTDIR}/_ext/1350479654/b2Body.o \
	${OBJECTDIR}/_ext/1350479654/b2WorldCallbacks.o \
	${OBJECTDIR}/_ext/837767863/ITouchDelegate.o \
	${OBJECTDIR}/_ext/837767863/CParticleEmitterFire.o \
	${OBJECTDIR}/_ext/837767863/COcean.o \
	${OBJECTDIR}/_ext/469629982/b2DistanceJoint.o \
	${OBJECTDIR}/_ext/837767863/CGameMainMenuLevel.o \
	${OBJECTDIR}/_ext/1350479654/b2Fixture.o \
	${OBJECTDIR}/_ext/837767863/GameHeavyTankSDB.o \
	${OBJECTDIR}/_ext/837767863/CGameState.o \
	${OBJECTDIR}/_ext/837767863/GameTankSDB.o \
	${OBJECTDIR}/_ext/837767863/CParticleEmitterExplosion.o \
	${OBJECTDIR}/_ext/1176185352/b2PolygonAndCircleContact.o \
	${OBJECTDIR}/_ext/837767863/CSpriteMgr.o \
	${OBJECTDIR}/_ext/469629982/b2WheelJoint.o \
	${OBJECTDIR}/_ext/837767863/CTexture.o \
	${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoord.o \
	${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoordColor.o \
	${OBJECTDIR}/_ext/837767863/ITankTrack.o \
	${OBJECTDIR}/_ext/837767863/CGrass.o \
	${OBJECTDIR}/_ext/837767863/CGameShooterMgr.o \
	${OBJECTDIR}/_ext/837767863/CMeshMgr.o \
	${OBJECTDIR}/_ext/1654165845/b2ChainShape.o \
	${OBJECTDIR}/_ext/1180546860/b2DynamicTree.o \
	${OBJECTDIR}/_ext/837767863/IGameScene.o \
	${OBJECTDIR}/_ext/837767863/CCollisionMgr.o \
	${OBJECTDIR}/_ext/469629982/b2MouseJoint.o \
	${OBJECTDIR}/_ext/837767863/GameServer.o \
	${OBJECTDIR}/_ext/21410767/b2Draw.o \
	${OBJECTDIR}/_ext/1180546860/b2TimeOfImpact.o \
	${OBJECTDIR}/_ext/837767863/CBullet.o \
	${OBJECTDIR}/_ext/21410767/b2Math.o \
	${OBJECTDIR}/_ext/469629982/b2WeldJoint.o \
	${OBJECTDIR}/_ext/837767863/CInput.o \
	${OBJECTDIR}/_ext/1654165845/b2EdgeShape.o \
	${OBJECTDIR}/_ext/837767863/CGameAIMgr.o \
	${OBJECTDIR}/_ext/1654165845/b2PolygonShape.o \
	${OBJECTDIR}/_ext/837767863/CModel.o \
	${OBJECTDIR}/_ext/1654165845/b2CircleShape.o \
	${OBJECTDIR}/_ext/837767863/ITankTower.o \
	${OBJECTDIR}/_ext/837767863/ITankBody.o \
	${OBJECTDIR}/_ext/837767863/CBuilding.o \
	${OBJECTDIR}/_ext/837767863/INavigationDelegate.o \
	${OBJECTDIR}/_ext/837767863/CHeightMapSetter.o \
	${OBJECTDIR}/_ext/837767863/CEventMgr.o \
	${OBJECTDIR}/_ext/837767863/INode.o \
	${OBJECTDIR}/_ext/837767863/IResourceMgr.o \
	${OBJECTDIR}/_ext/837767863/GameClientHandler.o \
	${OBJECTDIR}/_ext/1180546860/b2CollidePolygon.o \
	${OBJECTDIR}/_ext/837767863/ILight.o \
	${OBJECTDIR}/_ext/21410767/b2Settings.o \
	${OBJECTDIR}/_ext/837767863/CTankMediumTrack.o \
	${OBJECTDIR}/_ext/469629982/b2Joint.o \
	${OBJECTDIR}/_ext/1176185352/b2ContactSolver.o \
	${OBJECTDIR}/_ext/837767863/CGame.o \
	${OBJECTDIR}/_ext/1176185352/b2PolygonContact.o \
	${OBJECTDIR}/_ext/837767863/CGameSceneMgr.o \
	${OBJECTDIR}/_ext/837767863/CMesh.o \
	${OBJECTDIR}/_ext/837767863/CLandscapeEdges.o \
	${OBJECTDIR}/_ext/837767863/CBillboard.o \
	${OBJECTDIR}/_ext/1176185352/b2ChainAndPolygonContact.o \
	${OBJECTDIR}/_ext/837767863/CCharacterControllerPlayer.o \
	${OBJECTDIR}/_ext/837767863/main_lnx.o \
	${OBJECTDIR}/_ext/837767863/CTankLightTrack.o \
	${OBJECTDIR}/_ext/837767863/CLightPoint.o \
	${OBJECTDIR}/_ext/837767863/CTextureMgr.o \
	${OBJECTDIR}/_ext/837767863/CSpriteCross.o \
	${OBJECTDIR}/_ext/837767863/CCharacterControllerEnemy.o \
	${OBJECTDIR}/_ext/837767863/CParser_GLSL.o \
	${OBJECTDIR}/_ext/469629982/b2PrismaticJoint.o \
	${OBJECTDIR}/_ext/837767863/CTimer.o \
	${OBJECTDIR}/_ext/837767863/CTankLightTower.o \
	${OBJECTDIR}/_ext/837767863/CTankHeavyBody.o \
	${OBJECTDIR}/_ext/837767863/GameSDBStorage.o \
	${OBJECTDIR}/_ext/837767863/ICharacterController.o \
	${OBJECTDIR}/_ext/1180546860/b2BroadPhase.o \
	${OBJECTDIR}/_ext/837767863/IParser.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32
CXXFLAGS=-m32

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread ../libs/external/_lib/Debug/GNU_SNAP-Linux-x86/libcommon.a -lEGL -lGLESv2 -lX11 -lXau

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tanks_nbproject

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tanks_nbproject: ../libs/external/_lib/Debug/GNU_SNAP-Linux-x86/libcommon.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tanks_nbproject: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tanks_nbproject ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/21410767/b2Timer.o: ../libs/ios/Box2D/Common/b2Timer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/21410767
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/21410767/b2Timer.o ../libs/ios/Box2D/Common/b2Timer.cpp

${OBJECTDIR}/_ext/837767863/GameMediumTankSDB.o: ../Classes/GameMediumTankSDB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/GameMediumTankSDB.o ../Classes/GameMediumTankSDB.cpp

${OBJECTDIR}/_ext/837767863/CParser_MDL.o: ../Classes/CParser_MDL.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CParser_MDL.o ../Classes/CParser_MDL.cpp

${OBJECTDIR}/_ext/837767863/CRenderMgr.o: ../Classes/CRenderMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CRenderMgr.o ../Classes/CRenderMgr.cpp

${OBJECTDIR}/_ext/837767863/GameNativeCommunicationMgr.o: ../Classes/GameNativeCommunicationMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/GameNativeCommunicationMgr.o ../Classes/GameNativeCommunicationMgr.cpp

${OBJECTDIR}/_ext/1176185352/b2EdgeAndCircleContact.o: ../libs/ios/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1176185352
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1176185352/b2EdgeAndCircleContact.o ../libs/ios/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp

${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoordNormalTangent.o: ../Classes/CVertexBufferPositionTexcoordNormalTangent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoordNormalTangent.o ../Classes/CVertexBufferPositionTexcoordNormalTangent.cpp

${OBJECTDIR}/_ext/837767863/CSettings.o: ../Classes/CSettings.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CSettings.o ../Classes/CSettings.cpp

${OBJECTDIR}/_ext/837767863/ICamera.o: ../Classes/ICamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/ICamera.o ../Classes/ICamera.cpp

${OBJECTDIR}/_ext/837767863/CParticleEmitter.o: ../Classes/CParticleEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CParticleEmitter.o ../Classes/CParticleEmitter.cpp

${OBJECTDIR}/_ext/837767863/CParticleMgr.o: ../Classes/CParticleMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CParticleMgr.o ../Classes/CParticleMgr.cpp

${OBJECTDIR}/_ext/469629982/b2RopeJoint.o: ../libs/ios/Box2D/Dynamics/Joints/b2RopeJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/469629982
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/469629982/b2RopeJoint.o ../libs/ios/Box2D/Dynamics/Joints/b2RopeJoint.cpp

${OBJECTDIR}/_ext/837767863/CTankHeavyTower.o: ../Classes/CTankHeavyTower.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTankHeavyTower.o ../Classes/CTankHeavyTower.cpp

${OBJECTDIR}/_ext/837767863/ICollisionDelegate.o: ../Classes/ICollisionDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/ICollisionDelegate.o ../Classes/ICollisionDelegate.cpp

${OBJECTDIR}/_ext/837767863/CSprite.o: ../Classes/CSprite.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CSprite.o ../Classes/CSprite.cpp

${OBJECTDIR}/_ext/837767863/CCameraFree.o: ../Classes/CCameraFree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CCameraFree.o ../Classes/CCameraFree.cpp

${OBJECTDIR}/_ext/837767863/CDecalMgr.o: ../Classes/CDecalMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CDecalMgr.o ../Classes/CDecalMgr.cpp

${OBJECTDIR}/_ext/837767863/CCameraTarget.o: ../Classes/CCameraTarget.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CCameraTarget.o ../Classes/CCameraTarget.cpp

${OBJECTDIR}/_ext/1176185352/b2CircleContact.o: ../libs/ios/Box2D/Dynamics/Contacts/b2CircleContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1176185352
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1176185352/b2CircleContact.o ../libs/ios/Box2D/Dynamics/Contacts/b2CircleContact.cpp

${OBJECTDIR}/_ext/469629982/b2RevoluteJoint.o: ../libs/ios/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/469629982
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/469629982/b2RevoluteJoint.o ../libs/ios/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp

${OBJECTDIR}/_ext/837767863/GameUserSDB.o: ../Classes/GameUserSDB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/GameUserSDB.o ../Classes/GameUserSDB.cpp

${OBJECTDIR}/_ext/837767863/CTankMediumBody.o: ../Classes/CTankMediumBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTankMediumBody.o ../Classes/CTankMediumBody.cpp

${OBJECTDIR}/_ext/837767863/CTankMediumTower.o: ../Classes/CTankMediumTower.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTankMediumTower.o ../Classes/CTankMediumTower.cpp

${OBJECTDIR}/_ext/837767863/CMathHelper.o: ../Classes/CMathHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CMathHelper.o ../Classes/CMathHelper.cpp

${OBJECTDIR}/_ext/469629982/b2FrictionJoint.o: ../libs/ios/Box2D/Dynamics/Joints/b2FrictionJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/469629982
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/469629982/b2FrictionJoint.o ../libs/ios/Box2D/Dynamics/Joints/b2FrictionJoint.cpp

${OBJECTDIR}/_ext/1350479654/b2World.o: ../libs/ios/Box2D/Dynamics/b2World.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1350479654
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1350479654/b2World.o ../libs/ios/Box2D/Dynamics/b2World.cpp

${OBJECTDIR}/_ext/837767863/CTankHeavyTrack.o: ../Classes/CTankHeavyTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTankHeavyTrack.o ../Classes/CTankHeavyTrack.cpp

${OBJECTDIR}/_ext/837767863/IDelegate.o: ../Classes/IDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/IDelegate.o ../Classes/IDelegate.cpp

${OBJECTDIR}/_ext/837767863/GameLightTankSDB.o: ../Classes/GameLightTankSDB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/GameLightTankSDB.o ../Classes/GameLightTankSDB.cpp

${OBJECTDIR}/_ext/1176185352/b2ChainAndCircleContact.o: ../libs/ios/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1176185352
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1176185352/b2ChainAndCircleContact.o ../libs/ios/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp

${OBJECTDIR}/_ext/837767863/CMaterial.o: ../Classes/CMaterial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CMaterial.o ../Classes/CMaterial.cpp

${OBJECTDIR}/_ext/837767863/CVertexBufferPositionColor.o: ../Classes/CVertexBufferPositionColor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CVertexBufferPositionColor.o ../Classes/CVertexBufferPositionColor.cpp

${OBJECTDIR}/_ext/1438679880/b2Rope.o: ../libs/ios/Box2D/Rope/b2Rope.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1438679880
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1438679880/b2Rope.o ../libs/ios/Box2D/Rope/b2Rope.cpp

${OBJECTDIR}/_ext/1180546860/b2Collision.o: ../libs/ios/Box2D/Collision/b2Collision.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1180546860
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1180546860/b2Collision.o ../libs/ios/Box2D/Collision/b2Collision.cpp

${OBJECTDIR}/_ext/837767863/IGameLevel.o: ../Classes/IGameLevel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/IGameLevel.o ../Classes/IGameLevel.cpp

${OBJECTDIR}/_ext/469629982/b2PulleyJoint.o: ../libs/ios/Box2D/Dynamics/Joints/b2PulleyJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/469629982
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/469629982/b2PulleyJoint.o ../libs/ios/Box2D/Dynamics/Joints/b2PulleyJoint.cpp

${OBJECTDIR}/_ext/837767863/CGameInGameScene.o: ../Classes/CGameInGameScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGameInGameScene.o ../Classes/CGameInGameScene.cpp

${OBJECTDIR}/_ext/837767863/IResource.o: ../Classes/IResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/IResource.o ../Classes/IResource.cpp

${OBJECTDIR}/_ext/837767863/CGameUIMgr.o: ../Classes/CGameUIMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGameUIMgr.o ../Classes/CGameUIMgr.cpp

${OBJECTDIR}/_ext/837767863/CScreenSpacePostMgr.o: ../Classes/CScreenSpacePostMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CScreenSpacePostMgr.o ../Classes/CScreenSpacePostMgr.cpp

${OBJECTDIR}/_ext/837767863/CShaderComposite.o: ../Classes/CShaderComposite.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CShaderComposite.o ../Classes/CShaderComposite.cpp

${OBJECTDIR}/_ext/837767863/CIndexBuffer.o: ../Classes/CIndexBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CIndexBuffer.o ../Classes/CIndexBuffer.cpp

${OBJECTDIR}/_ext/1350479654/b2Island.o: ../libs/ios/Box2D/Dynamics/b2Island.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1350479654
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1350479654/b2Island.o ../libs/ios/Box2D/Dynamics/b2Island.cpp

${OBJECTDIR}/_ext/837767863/CBoundingBox.o: ../Classes/CBoundingBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CBoundingBox.o ../Classes/CBoundingBox.cpp

${OBJECTDIR}/_ext/837767863/CLandscape.o: ../Classes/CLandscape.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CLandscape.o ../Classes/CLandscape.cpp

${OBJECTDIR}/_ext/469629982/b2GearJoint.o: ../libs/ios/Box2D/Dynamics/Joints/b2GearJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/469629982
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/469629982/b2GearJoint.o ../libs/ios/Box2D/Dynamics/Joints/b2GearJoint.cpp

${OBJECTDIR}/_ext/837767863/CParser_PVR.o: ../Classes/CParser_PVR.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CParser_PVR.o ../Classes/CParser_PVR.cpp

${OBJECTDIR}/_ext/837767863/CFrustum.o: ../Classes/CFrustum.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CFrustum.o ../Classes/CFrustum.cpp

${OBJECTDIR}/_ext/837767863/CWindow.o: ../Classes/CWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CWindow.o ../Classes/CWindow.cpp

${OBJECTDIR}/_ext/837767863/CGameMainMenuScene.o: ../Classes/CGameMainMenuScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGameMainMenuScene.o ../Classes/CGameMainMenuScene.cpp

${OBJECTDIR}/_ext/837767863/GameClient.o: ../Classes/GameClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/GameClient.o ../Classes/GameClient.cpp

${OBJECTDIR}/_ext/837767863/CLandscapeDecal.o: ../Classes/CLandscapeDecal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CLandscapeDecal.o ../Classes/CLandscapeDecal.cpp

${OBJECTDIR}/_ext/837767863/ITankPart.o: ../Classes/ITankPart.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/ITankPart.o ../Classes/ITankPart.cpp

${OBJECTDIR}/_ext/837767863/IResourceLoaderDelegate.o: ../Classes/IResourceLoaderDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/IResourceLoaderDelegate.o ../Classes/IResourceLoaderDelegate.cpp

${OBJECTDIR}/_ext/1180546860/b2CollideEdge.o: ../libs/ios/Box2D/Collision/b2CollideEdge.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1180546860
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1180546860/b2CollideEdge.o ../libs/ios/Box2D/Collision/b2CollideEdge.cpp

${OBJECTDIR}/_ext/1180546860/b2CollideCircle.o: ../libs/ios/Box2D/Collision/b2CollideCircle.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1180546860
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1180546860/b2CollideCircle.o ../libs/ios/Box2D/Collision/b2CollideCircle.cpp

${OBJECTDIR}/_ext/21410767/b2StackAllocator.o: ../libs/ios/Box2D/Common/b2StackAllocator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/21410767
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/21410767/b2StackAllocator.o ../libs/ios/Box2D/Common/b2StackAllocator.cpp

${OBJECTDIR}/_ext/837767863/CShader.o: ../Classes/CShader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CShader.o ../Classes/CShader.cpp

${OBJECTDIR}/_ext/1180546860/b2Distance.o: ../libs/ios/Box2D/Collision/b2Distance.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1180546860
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1180546860/b2Distance.o ../libs/ios/Box2D/Collision/b2Distance.cpp

${OBJECTDIR}/_ext/837767863/CSkyBox.o: ../Classes/CSkyBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CSkyBox.o ../Classes/CSkyBox.cpp

${OBJECTDIR}/_ext/837767863/CGameInGameLevel.o: ../Classes/CGameInGameLevel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGameInGameLevel.o ../Classes/CGameInGameLevel.cpp

${OBJECTDIR}/_ext/1176185352/b2EdgeAndPolygonContact.o: ../libs/ios/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1176185352
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1176185352/b2EdgeAndPolygonContact.o ../libs/ios/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp

${OBJECTDIR}/_ext/837767863/CParticleEmitterTrail.o: ../Classes/CParticleEmitterTrail.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CParticleEmitterTrail.o ../Classes/CParticleEmitterTrail.cpp

${OBJECTDIR}/_ext/1350479654/b2ContactManager.o: ../libs/ios/Box2D/Dynamics/b2ContactManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1350479654
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1350479654/b2ContactManager.o ../libs/ios/Box2D/Dynamics/b2ContactManager.cpp

${OBJECTDIR}/_ext/837767863/CGameCharaterControllerMgr.o: ../Classes/CGameCharaterControllerMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGameCharaterControllerMgr.o ../Classes/CGameCharaterControllerMgr.cpp

${OBJECTDIR}/_ext/837767863/CResourceMgr.o: ../Classes/CResourceMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CResourceMgr.o ../Classes/CResourceMgr.cpp

${OBJECTDIR}/_ext/21410767/b2BlockAllocator.o: ../libs/ios/Box2D/Common/b2BlockAllocator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/21410767
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/21410767/b2BlockAllocator.o ../libs/ios/Box2D/Common/b2BlockAllocator.cpp

${OBJECTDIR}/_ext/837767863/CTankLightBody.o: ../Classes/CTankLightBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTankLightBody.o ../Classes/CTankLightBody.cpp

${OBJECTDIR}/_ext/837767863/IVertexBuffer.o: ../Classes/IVertexBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/IVertexBuffer.o ../Classes/IVertexBuffer.cpp

${OBJECTDIR}/_ext/837767863/CSceneMgr.o: ../Classes/CSceneMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CSceneMgr.o ../Classes/CSceneMgr.cpp

${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoordNormal.o: ../Classes/CVertexBufferPositionTexcoordNormal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoordNormal.o ../Classes/CVertexBufferPositionTexcoordNormal.cpp

${OBJECTDIR}/_ext/1176185352/b2Contact.o: ../libs/ios/Box2D/Dynamics/Contacts/b2Contact.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1176185352
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1176185352/b2Contact.o ../libs/ios/Box2D/Dynamics/Contacts/b2Contact.cpp

${OBJECTDIR}/_ext/837767863/CNavigationHelper.o: ../Classes/CNavigationHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CNavigationHelper.o ../Classes/CNavigationHelper.cpp

${OBJECTDIR}/_ext/1350479654/b2Body.o: ../libs/ios/Box2D/Dynamics/b2Body.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1350479654
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1350479654/b2Body.o ../libs/ios/Box2D/Dynamics/b2Body.cpp

${OBJECTDIR}/_ext/1350479654/b2WorldCallbacks.o: ../libs/ios/Box2D/Dynamics/b2WorldCallbacks.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1350479654
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1350479654/b2WorldCallbacks.o ../libs/ios/Box2D/Dynamics/b2WorldCallbacks.cpp

${OBJECTDIR}/_ext/837767863/ITouchDelegate.o: ../Classes/ITouchDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/ITouchDelegate.o ../Classes/ITouchDelegate.cpp

${OBJECTDIR}/_ext/837767863/CParticleEmitterFire.o: ../Classes/CParticleEmitterFire.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CParticleEmitterFire.o ../Classes/CParticleEmitterFire.cpp

${OBJECTDIR}/_ext/837767863/COcean.o: ../Classes/COcean.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/COcean.o ../Classes/COcean.cpp

${OBJECTDIR}/_ext/469629982/b2DistanceJoint.o: ../libs/ios/Box2D/Dynamics/Joints/b2DistanceJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/469629982
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/469629982/b2DistanceJoint.o ../libs/ios/Box2D/Dynamics/Joints/b2DistanceJoint.cpp

${OBJECTDIR}/_ext/837767863/CGameMainMenuLevel.o: ../Classes/CGameMainMenuLevel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGameMainMenuLevel.o ../Classes/CGameMainMenuLevel.cpp

${OBJECTDIR}/_ext/1350479654/b2Fixture.o: ../libs/ios/Box2D/Dynamics/b2Fixture.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1350479654
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1350479654/b2Fixture.o ../libs/ios/Box2D/Dynamics/b2Fixture.cpp

${OBJECTDIR}/_ext/837767863/GameHeavyTankSDB.o: ../Classes/GameHeavyTankSDB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/GameHeavyTankSDB.o ../Classes/GameHeavyTankSDB.cpp

${OBJECTDIR}/_ext/837767863/CGameState.o: ../Classes/CGameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGameState.o ../Classes/CGameState.cpp

${OBJECTDIR}/_ext/837767863/GameTankSDB.o: ../Classes/GameTankSDB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/GameTankSDB.o ../Classes/GameTankSDB.cpp

${OBJECTDIR}/_ext/837767863/CParticleEmitterExplosion.o: ../Classes/CParticleEmitterExplosion.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CParticleEmitterExplosion.o ../Classes/CParticleEmitterExplosion.cpp

${OBJECTDIR}/_ext/1176185352/b2PolygonAndCircleContact.o: ../libs/ios/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1176185352
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1176185352/b2PolygonAndCircleContact.o ../libs/ios/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp

${OBJECTDIR}/_ext/837767863/CSpriteMgr.o: ../Classes/CSpriteMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CSpriteMgr.o ../Classes/CSpriteMgr.cpp

${OBJECTDIR}/_ext/469629982/b2WheelJoint.o: ../libs/ios/Box2D/Dynamics/Joints/b2WheelJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/469629982
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/469629982/b2WheelJoint.o ../libs/ios/Box2D/Dynamics/Joints/b2WheelJoint.cpp

${OBJECTDIR}/_ext/837767863/CTexture.o: ../Classes/CTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTexture.o ../Classes/CTexture.cpp

${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoord.o: ../Classes/CVertexBufferPositionTexcoord.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoord.o ../Classes/CVertexBufferPositionTexcoord.cpp

${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoordColor.o: ../Classes/CVertexBufferPositionTexcoordColor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CVertexBufferPositionTexcoordColor.o ../Classes/CVertexBufferPositionTexcoordColor.cpp

${OBJECTDIR}/_ext/837767863/ITankTrack.o: ../Classes/ITankTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/ITankTrack.o ../Classes/ITankTrack.cpp

${OBJECTDIR}/_ext/837767863/CGrass.o: ../Classes/CGrass.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGrass.o ../Classes/CGrass.cpp

${OBJECTDIR}/_ext/837767863/CGameShooterMgr.o: ../Classes/CGameShooterMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGameShooterMgr.o ../Classes/CGameShooterMgr.cpp

${OBJECTDIR}/_ext/837767863/CMeshMgr.o: ../Classes/CMeshMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CMeshMgr.o ../Classes/CMeshMgr.cpp

${OBJECTDIR}/_ext/1654165845/b2ChainShape.o: ../libs/ios/Box2D/Collision/Shapes/b2ChainShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654165845
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1654165845/b2ChainShape.o ../libs/ios/Box2D/Collision/Shapes/b2ChainShape.cpp

${OBJECTDIR}/_ext/1180546860/b2DynamicTree.o: ../libs/ios/Box2D/Collision/b2DynamicTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1180546860
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1180546860/b2DynamicTree.o ../libs/ios/Box2D/Collision/b2DynamicTree.cpp

${OBJECTDIR}/_ext/837767863/IGameScene.o: ../Classes/IGameScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/IGameScene.o ../Classes/IGameScene.cpp

${OBJECTDIR}/_ext/837767863/CCollisionMgr.o: ../Classes/CCollisionMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CCollisionMgr.o ../Classes/CCollisionMgr.cpp

${OBJECTDIR}/_ext/469629982/b2MouseJoint.o: ../libs/ios/Box2D/Dynamics/Joints/b2MouseJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/469629982
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/469629982/b2MouseJoint.o ../libs/ios/Box2D/Dynamics/Joints/b2MouseJoint.cpp

${OBJECTDIR}/_ext/837767863/GameServer.o: ../Classes/GameServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/GameServer.o ../Classes/GameServer.cpp

${OBJECTDIR}/_ext/21410767/b2Draw.o: ../libs/ios/Box2D/Common/b2Draw.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/21410767
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/21410767/b2Draw.o ../libs/ios/Box2D/Common/b2Draw.cpp

${OBJECTDIR}/_ext/1180546860/b2TimeOfImpact.o: ../libs/ios/Box2D/Collision/b2TimeOfImpact.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1180546860
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1180546860/b2TimeOfImpact.o ../libs/ios/Box2D/Collision/b2TimeOfImpact.cpp

${OBJECTDIR}/_ext/837767863/CBullet.o: ../Classes/CBullet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CBullet.o ../Classes/CBullet.cpp

${OBJECTDIR}/_ext/21410767/b2Math.o: ../libs/ios/Box2D/Common/b2Math.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/21410767
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/21410767/b2Math.o ../libs/ios/Box2D/Common/b2Math.cpp

${OBJECTDIR}/_ext/469629982/b2WeldJoint.o: ../libs/ios/Box2D/Dynamics/Joints/b2WeldJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/469629982
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/469629982/b2WeldJoint.o ../libs/ios/Box2D/Dynamics/Joints/b2WeldJoint.cpp

${OBJECTDIR}/_ext/837767863/CInput.o: ../Classes/CInput.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CInput.o ../Classes/CInput.cpp

${OBJECTDIR}/_ext/1654165845/b2EdgeShape.o: ../libs/ios/Box2D/Collision/Shapes/b2EdgeShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654165845
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1654165845/b2EdgeShape.o ../libs/ios/Box2D/Collision/Shapes/b2EdgeShape.cpp

${OBJECTDIR}/_ext/837767863/CGameAIMgr.o: ../Classes/CGameAIMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGameAIMgr.o ../Classes/CGameAIMgr.cpp

${OBJECTDIR}/_ext/1654165845/b2PolygonShape.o: ../libs/ios/Box2D/Collision/Shapes/b2PolygonShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654165845
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1654165845/b2PolygonShape.o ../libs/ios/Box2D/Collision/Shapes/b2PolygonShape.cpp

${OBJECTDIR}/_ext/837767863/CModel.o: ../Classes/CModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CModel.o ../Classes/CModel.cpp

${OBJECTDIR}/_ext/1654165845/b2CircleShape.o: ../libs/ios/Box2D/Collision/Shapes/b2CircleShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654165845
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1654165845/b2CircleShape.o ../libs/ios/Box2D/Collision/Shapes/b2CircleShape.cpp

${OBJECTDIR}/_ext/837767863/ITankTower.o: ../Classes/ITankTower.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/ITankTower.o ../Classes/ITankTower.cpp

${OBJECTDIR}/_ext/837767863/ITankBody.o: ../Classes/ITankBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/ITankBody.o ../Classes/ITankBody.cpp

${OBJECTDIR}/_ext/837767863/CBuilding.o: ../Classes/CBuilding.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CBuilding.o ../Classes/CBuilding.cpp

${OBJECTDIR}/_ext/837767863/INavigationDelegate.o: ../Classes/INavigationDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/INavigationDelegate.o ../Classes/INavigationDelegate.cpp

${OBJECTDIR}/_ext/837767863/CHeightMapSetter.o: ../Classes/CHeightMapSetter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CHeightMapSetter.o ../Classes/CHeightMapSetter.cpp

${OBJECTDIR}/_ext/837767863/CEventMgr.o: ../Classes/CEventMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CEventMgr.o ../Classes/CEventMgr.cpp

${OBJECTDIR}/_ext/837767863/INode.o: ../Classes/INode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/INode.o ../Classes/INode.cpp

${OBJECTDIR}/_ext/837767863/IResourceMgr.o: ../Classes/IResourceMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/IResourceMgr.o ../Classes/IResourceMgr.cpp

${OBJECTDIR}/_ext/837767863/GameClientHandler.o: ../Classes/GameClientHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/GameClientHandler.o ../Classes/GameClientHandler.cpp

${OBJECTDIR}/_ext/1180546860/b2CollidePolygon.o: ../libs/ios/Box2D/Collision/b2CollidePolygon.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1180546860
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1180546860/b2CollidePolygon.o ../libs/ios/Box2D/Collision/b2CollidePolygon.cpp

${OBJECTDIR}/_ext/837767863/ILight.o: ../Classes/ILight.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/ILight.o ../Classes/ILight.cpp

${OBJECTDIR}/_ext/21410767/b2Settings.o: ../libs/ios/Box2D/Common/b2Settings.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/21410767
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/21410767/b2Settings.o ../libs/ios/Box2D/Common/b2Settings.cpp

${OBJECTDIR}/_ext/837767863/CTankMediumTrack.o: ../Classes/CTankMediumTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTankMediumTrack.o ../Classes/CTankMediumTrack.cpp

${OBJECTDIR}/_ext/469629982/b2Joint.o: ../libs/ios/Box2D/Dynamics/Joints/b2Joint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/469629982
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/469629982/b2Joint.o ../libs/ios/Box2D/Dynamics/Joints/b2Joint.cpp

${OBJECTDIR}/_ext/1176185352/b2ContactSolver.o: ../libs/ios/Box2D/Dynamics/Contacts/b2ContactSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1176185352
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1176185352/b2ContactSolver.o ../libs/ios/Box2D/Dynamics/Contacts/b2ContactSolver.cpp

${OBJECTDIR}/_ext/837767863/CGame.o: ../Classes/CGame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGame.o ../Classes/CGame.cpp

${OBJECTDIR}/_ext/1176185352/b2PolygonContact.o: ../libs/ios/Box2D/Dynamics/Contacts/b2PolygonContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1176185352
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1176185352/b2PolygonContact.o ../libs/ios/Box2D/Dynamics/Contacts/b2PolygonContact.cpp

${OBJECTDIR}/_ext/837767863/CGameSceneMgr.o: ../Classes/CGameSceneMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CGameSceneMgr.o ../Classes/CGameSceneMgr.cpp

${OBJECTDIR}/_ext/837767863/CMesh.o: ../Classes/CMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CMesh.o ../Classes/CMesh.cpp

${OBJECTDIR}/_ext/837767863/CLandscapeEdges.o: ../Classes/CLandscapeEdges.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CLandscapeEdges.o ../Classes/CLandscapeEdges.cpp

${OBJECTDIR}/_ext/837767863/CBillboard.o: ../Classes/CBillboard.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CBillboard.o ../Classes/CBillboard.cpp

${OBJECTDIR}/_ext/1176185352/b2ChainAndPolygonContact.o: ../libs/ios/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1176185352
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1176185352/b2ChainAndPolygonContact.o ../libs/ios/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp

${OBJECTDIR}/_ext/837767863/CCharacterControllerPlayer.o: ../Classes/CCharacterControllerPlayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CCharacterControllerPlayer.o ../Classes/CCharacterControllerPlayer.cpp

${OBJECTDIR}/_ext/837767863/main_lnx.o: ../Classes/main_lnx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/main_lnx.o ../Classes/main_lnx.cpp

${OBJECTDIR}/_ext/837767863/CTankLightTrack.o: ../Classes/CTankLightTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTankLightTrack.o ../Classes/CTankLightTrack.cpp

${OBJECTDIR}/_ext/837767863/CLightPoint.o: ../Classes/CLightPoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CLightPoint.o ../Classes/CLightPoint.cpp

${OBJECTDIR}/_ext/837767863/CTextureMgr.o: ../Classes/CTextureMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTextureMgr.o ../Classes/CTextureMgr.cpp

${OBJECTDIR}/_ext/837767863/CSpriteCross.o: ../Classes/CSpriteCross.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CSpriteCross.o ../Classes/CSpriteCross.cpp

${OBJECTDIR}/_ext/837767863/CCharacterControllerEnemy.o: ../Classes/CCharacterControllerEnemy.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CCharacterControllerEnemy.o ../Classes/CCharacterControllerEnemy.cpp

${OBJECTDIR}/_ext/837767863/CParser_GLSL.o: ../Classes/CParser_GLSL.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CParser_GLSL.o ../Classes/CParser_GLSL.cpp

${OBJECTDIR}/_ext/469629982/b2PrismaticJoint.o: ../libs/ios/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/469629982
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/469629982/b2PrismaticJoint.o ../libs/ios/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp

${OBJECTDIR}/_ext/837767863/CTimer.o: ../Classes/CTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTimer.o ../Classes/CTimer.cpp

${OBJECTDIR}/_ext/837767863/CTankLightTower.o: ../Classes/CTankLightTower.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTankLightTower.o ../Classes/CTankLightTower.cpp

${OBJECTDIR}/_ext/837767863/CTankHeavyBody.o: ../Classes/CTankHeavyBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/CTankHeavyBody.o ../Classes/CTankHeavyBody.cpp

${OBJECTDIR}/_ext/837767863/GameSDBStorage.o: ../Classes/GameSDBStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/GameSDBStorage.o ../Classes/GameSDBStorage.cpp

${OBJECTDIR}/_ext/837767863/ICharacterController.o: ../Classes/ICharacterController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/ICharacterController.o ../Classes/ICharacterController.cpp

${OBJECTDIR}/_ext/1180546860/b2BroadPhase.o: ../libs/ios/Box2D/Collision/b2BroadPhase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1180546860
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1180546860/b2BroadPhase.o ../libs/ios/Box2D/Collision/b2BroadPhase.cpp

${OBJECTDIR}/_ext/837767863/IParser.o: ../Classes/IParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/837767863
	${RM} $@.d
	$(COMPILE.cc) -g -DBUILD_OGLES2 -I../libs/ios -I../Classes -I../libs/ios/pvr -I../libs/external/Common/Include -I../libs/external -I../libs/platform/OGLES2/Include -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/837767863/IParser.o ../Classes/IParser.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tanks_nbproject

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

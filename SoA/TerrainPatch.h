///
/// TerrainPatch.h
/// Seed of Andromeda
///
/// Created by Benjamin Arnold on 15 Dec 2014
/// Copyright 2014 Regrowth Studios
/// All Rights Reserved
///
/// Summary:
/// A terrain patch for use with a SphericalTerrainComponent
///

#pragma once

#ifndef TerrainPatch_h__
#define TerrainPatch_h__

#include "TerrainGenerator.h"
#include "VoxelCoordinateSpaces.h"
#include "TerrainPatchConstants.h"

#include <Vorb/graphics/gtypes.h>

class TerrainRpcDispatcher;
class TerrainGenDelegate;
class TerrainPatchMesh;

// Shared data for terrain patches
class TerrainPatchData {
public:
    friend struct SphericalTerrainComponent;

    TerrainPatchData(f64 radius,
                         f64 patchWidth) :
        m_radius(radius),
        m_patchWidth(patchWidth) {
        // Empty
    }

    const f64& getRadius() const { return m_radius; }
    const f64& getPatchWidth() const { return m_patchWidth; }
private:
    f64 m_radius; ///< Radius of the planet in KM
    f64 m_patchWidth; ///< Width of a patch in KM
};

// TODO(Ben): Sorting, Atmosphere, Frustum Culling
// fix redundant quality changes
class TerrainPatch {
public:
    TerrainPatch() { };
    virtual ~TerrainPatch();
    
    /// Initializes the patch
    /// @param gridPosition: Position on the 2d face grid
    /// @param sphericalTerrainData: Shared data
    /// @param width: Width of the patch in KM
    virtual void init(const f64v2& gridPosition,
              WorldCubeFace cubeFace,
              int lod,
              const TerrainPatchData* sphericalTerrainData,
              f64 width,
              TerrainRpcDispatcher* dispatcher);

    /// Updates the patch
    /// @param cameraPos: Position of the camera
    virtual void update(const f64v3& cameraPos);

    /// Frees resources
    void destroy();

    /// @return true if it has a generated mesh
    bool hasMesh() const;

    /// @return true if it has a mesh, or all of its children are
    /// renderable.
    bool isRenderable() const;

    /// Checks if the point is over the horizon
    /// @param relCamPos: Relative observer position
    /// @param point: The point to check
    /// @param planetRadius: Radius of the planet
    static bool isOverHorizon(const f32v3 &relCamPos, const f32v3 &point, f32 planetRadius);
    static bool isOverHorizon(const f64v3 &relCamPos, const f64v3 &point, f64 planetRadius);

    /// Returns true if the patch can subdivide
    bool canSubdivide() const;
protected:
    /// Requests a mesh via RPC
    virtual void requestMesh();
    /// Calculates the closest point to the camera, as well as distance
    /// @param cameraPos: position of the observer
    /// @return closest point on the AABB
    f64v3 calculateClosestPointAndDist(const f64v3& cameraPos);

    f64v2 m_gridPos = f64v2(0.0); ///< Position on 2D grid
    f64v3 m_aabbPos = f64v3(0.0); ///< Position relative to world
    f64v3 m_aabbDims = f64v3(0.0);
    f64 m_distance = 1000000000.0; ///< Distance from camera
    int m_lod = 0; ///< Level of detail
    WorldCubeFace m_cubeFace; ///< Which cube face grid it is on

    f64 m_width = 0.0; ///< Width of the patch in KM

    TerrainRpcDispatcher* m_dispatcher = nullptr;
    TerrainPatchMesh* m_mesh = nullptr;

    const TerrainPatchData* m_sphericalTerrainData = nullptr; ///< Shared data pointer
    TerrainPatch* m_children = nullptr; ///< Pointer to array of 4 children
};

#endif // TerrainPatch_h__